#include "global.h"
#include <ctime>
#include "tools/clock.h"
#include "version.h"
#include <experimental/filesystem>
#include "tools/format.h"

#include "systems/sheared_slitpore_system.h"

#include "printer/printer.h"
#include "printer/stress.h"
#include "printer/velocity.h"
#include "printer/angular_bond.h"
#include "order_parameter/stress_fourier_components.h"
#include "order_parameter/intra_layer_pair_correlation_function.h"

#include "struct/cartesian_matrix.h"

namespace fs = experimental::filesystem;

int main(int argc, const char *argv[]){
    CLOCK clock;
    
//    cout << "Task started at " << clock.readTimePoint(0) << endl << endl;
//    CARTESIAN_COORDINATE a(1, 2, 3);
//    CARTESIAN_COORDINATE b(4, 5, 6);
//    for(int i = 0; i < 10000000; i++){
//        CARTESIAN_MATRIX A(a, b);
//    }
//    CARTESIAN_MATRIX A(a, b);
//    cout << A << endl;
//    cout << A[0] << endl;
//    cout << A[0][1] << endl;
//    A[0][1] = 0;
//    cout << A[0][1] << endl;
//    clock.addTimePoint();
//    cout << endl << "Task finished at " << clock.readTimePoint(-1) << endl;
//    printf("Task finished in %.3f seconds (%s)\n", clock.getDuration(0, -1), clock.readDuration(0, -1).c_str());
//    cout << endl;
//    exit(0);
    
    ARGUMENT_PARSER parser(argc, argv);
    ARGUMENTS args = parser.parseArgs();

    if(args.printVersion){
        cout << PROJECT_VERSION << endl;
        exit(0);
    }
    cout << surroundWithSeparator("shearedSlitporeBD") << endl << endl;
    cout << "Task started at " << clock.readTimePoint(0) << endl << endl;

    //print version details
    cout << surroundWithSeparator("Version Details") << endl;
    cout << "Version: " << PROJECT_VERSION << endl;
    cout << "Git branch: " << GIT_BRANCH << endl;
    cout << "Git commit: " << GIT_COMMIT_HASH << endl;
    cout << "Git version: " << GIT_VERSION << endl << endl;
    
    //generate or read seed
    if(args.seed == 0){
        args.seed = getpid() * time(0);
    }
    
    //print parsed arguments
    cout << surroundWithSeparator("Parsed arguments/System parameters") << endl;
    args.print();
    cout << endl;

    cout << surroundWithSeparator("System Initialization") << endl;

    //initialize Slitpore System
    SHEARED_SLITPORE_SYSTEM sys(args);
    sys.writeConfigurationToFile("configuration.in.new", true);
    
    //clear
    if(args.clear){
        fs::remove("configuration.in.new");
        fs::remove(CONFIGURATION_OUT);
        fs::remove_all(SNAPSHOTS);
        fs::remove(STRESSES_OUT);
        fs::remove(VELOCITIES_OUT);
        fs::remove(ANGULAR_BOND_OUT);
        fs::remove_all(PAIR_CORRELATIONS_OUT);
    }

    if(args.dryRun){
        cout << "This was a dry run. To do an actual run, remove the '--dry' option!" << endl;
        exit(0);
    }

    cout << endl << surroundWithSeparator("Simulation start") << endl;
    
    VELOCITY_PRINTER velocity(&sys);
    STRESS_PRINTER stress(&sys);
    ANGULAR_BOND_PRINTER angularBond;
    STRESS_FOURIER_COMPONENTS fc(args);

    //column description
    for(int i = 0; i < args.totalNumberOfTimesteps; i++){
        if(i % (int)ceil(args.totalNumberOfTimesteps / 100.) == 0){
            printf("Progress: %.1f%% (timestep %ld)\n", 100 * i / float(args.totalNumberOfTimesteps), sys.getTimestep());
        }
        if(args.snapshotInterval > 0 && i % args.snapshotInterval == 0){
            sys.writeConfigurationToFile(SNAPSHOTS + "/configuration_" + to_string(sys.getTimestep()) + ".out", false);
        }
        if(args.printAngularBond > 0 && i % args.printAngularBond == 0){
            angularBond.printLine(sys);
        }
        if(args.printPairCorrelation > 0 && i % args.printPairCorrelation == 0){
            INTRA_LAYER_PAIR_CORRELATION_FUNCTION pC(sys, 0.05);
            pC.calculateAverageLayerCorrelation();
            pC.print(PAIR_CORRELATIONS_OUT + "/pairCorrelation_" + to_string(sys.getTimestep()) + ".out");
        }
        sys.simulateForSteps(1);
        if(args.printStress > 0 && i % args.printStress == 0){
            stress.printLine();
        }
        if(args.stressFourier > 0 && i % args.stressFourier == 0){
            fc.addTimestep(sys);
        }
        if(args.printVelocity > 0 && i > 0 && (i - 1) % args.printVelocity == 0){
            velocity.printLine();
        }
    }
    sys.writeConfigurationToFile(CONFIGURATION_OUT);
    if(args.stressFourier > 0){
        cout << fc << endl;
        cout << "Storage modulus [kT/d^3]: " << fc.calculateStorageModulus() << endl;
        cout << "Loss modulus [kT/d^3]: " << fc.calculateLossModulus() << endl;
        for(int i = 0; i <= 4; i++){
            cout << i << "-th Fourier component (xz): " << fc.calculate(i).xz << endl;
        }
    }
    
    //one more iteration for last velocity step (might cause minor problems if simulation is restarted without same seed and correct RNG counter)
    sys.simulateForSteps(1);
    if(args.printVelocity > 0 && args.totalNumberOfTimesteps > 0 && (args.totalNumberOfTimesteps - 1) % args.printVelocity == 0){
        velocity.printLine();
    }
    
    if(args.printStress > 0){
        printf("Printed stresses to %s\n", stress.printer.getFilename().c_str());
    }
    if(args.printVelocity > 0){
        printf("Printed velocities to %s\n", velocity.printer.getFilename().c_str());
    }
    if(args.printAngularBond > 0){
        printf("Printed angular bond parameters to %s\n", angularBond.getFilename().c_str());
    }
    
    cout << endl << surroundWithSeparator("Simulation end") << endl;
    
    clock.addTimePoint();
    cout << endl << "Task finished at " << clock.readTimePoint(-1) << endl;
    printf("Task finished in %.3f seconds (%s)\n", clock.getDuration(0, -1), clock.readDuration(0, -1).c_str());
    cout << endl;
    
    return 0;
}

//-a 400 -p 1e-3 --seed 3863985048 -N 10 --printAngularBond 1