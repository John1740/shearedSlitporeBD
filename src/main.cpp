#include "tools/clock.h"
#include "version.h"
#include "tools/format.h"
#include "boost/format.hpp"
namespace b = boost;

#include "global.h" //contains random_event definition
extern CRandomMersenne random_event;    //use global instance of random_event

#include "systems/sheared_slitpore_system.h"

//#include "printer/printer.h"
#include "printer/stress.h"
#include "printer/velocity.h"
#include "printer/angular_bond.h"
#include "order_parameter/stress_fourier_components.h"
#include "order_parameter/intra_layer_pair_correlation_function.h"

#include <experimental/filesystem>
namespace fs = experimental::filesystem;

int main(int argc, const char *argv[]){
    CLOCK clock;
    
    ARGUMENT_PARSER parser(argc, argv);
    ARGUMENTS argsParsed = parser.parseArgs();
    ARGUMENTS args;
    if(fs::exists(argsParsed.settingsIn)){
        args.readFromFile(argsParsed.settingsIn);
    }
    else{
        argsParsed.settingsIn += string(" (not existing)");
    }
    args.update(argsParsed);    //argsParsed have priority
    args.finalize();  //dt-defaulting and last corrections
    argsParsed.~ARGUMENTS();

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
        args.seed = getpid() * time(0); //dunno where getpid()-definition was imported from (unistd.h)
    }

    //print parsed arguments
    cout << surroundWithSeparator("Parsed arguments/System parameters") << endl;
    cout << args << endl;

    //initialize Slitpore System
    cout << surroundWithSeparator("System Initialization") << endl;
    //initialize RNG with seed (and skip steps if asked for)
    random_event.RandomInit(args.seed);
    if(args.rngCounter != 0){
        for(unsigned long long int i = 0; i < args.rngCounter; i++){
            random_event.Random();
        }
        cout << "Called random number generator " << args.rngCounter << " times." << endl;
    }

    SHEARED_SLITPORE_SYSTEM sys(args);
    sys.writeConfigurationToFile("configuration.in.new", true, true);
    
    //clear
    if(args.clear){
        cout << "Clearing all existing output-files!" << endl;
        fs::remove("configuration.in.new");
        fs::remove(CONFIGURATION_OUT);
        fs::remove(SNAPSHOTS);
        fs::remove(STRESSES_OUT);
        fs::remove(VELOCITIES_OUT);
        fs::remove(ANGULAR_BOND_OUT);
        fs::remove_all(PAIR_CORRELATIONS_OUT);
    }

    if(args.dry){
        cout << "This was a dry run. To do an actual run, remove the '--dry' option!" << endl;
        exit(0);
    }

    //Simulation start
    cout << endl << surroundWithSeparator("Simulation start") << endl;
    
    VELOCITY_PRINTER velocity(&sys);
    STRESS_PRINTER stress(&sys);
    ANGULAR_BOND_PRINTER angularBond;
    STRESS_FOURIER_COMPONENTS fc(args);

    //column description
    for(int i = 0; i < args.numberOfTimesteps; i++){
        if(i % (int)ceil(args.numberOfTimesteps / 100.) == 0){
            cout << b::format("Progress: %.1f%% (timestep %ld)")
                    % (100 * i / float(args.numberOfTimesteps))
                    % sys.getTimestep() << endl;
        }
        if(args.printSnapshots > 0 && i % args.printSnapshots == 0){
            sys.writeConfigurationToFile("snapshots.out", false, false);
        }
        if(args.printAngularBond > 0 && i % args.printAngularBond == 0){
            angularBond.printLine(sys);
        }
        if(args.printPairCorrelation > 0 && i % args.printPairCorrelation == 0){
            INTRA_LAYER_PAIR_CORRELATION_FUNCTION pC(sys);
            pC.calculateAverageLayerCorrelation();
            pC.print(PAIR_CORRELATIONS_OUT + "/pairCorrelation_" + to_string(sys.getTimestep()) + ".out");
        }
        sys.simulateForSteps(1);
        if(args.printStress > 0 && i % args.printStress == 0){
            stress.printLine();
        }
        if(args.printStressFourier > 0 && i % args.printStressFourier == 0){
            fc.addTimestep(sys);
        }
        if(args.printVelocity > 0 && i > 0 && (i - 1) % args.printVelocity == 0){
            velocity.printLine();
        }
    }
    sys.writeConfigurationToFile(CONFIGURATION_OUT, true);
    cout << "rngCounter: " << random_event.rngCounter << endl;
    
    //one more iteration for last velocity step (might cause minor problems if simulation is restarted without same seed and correct RNG counter)
    sys.simulateForSteps(1);
    if(args.printVelocity > 0 && args.numberOfTimesteps > 0 && (args.numberOfTimesteps - 1) % args.printVelocity == 0){
        velocity.printLine();
    }
    
    if(args.printStress > 0){
        cout << b::format("Printed stresses to %s") % stress.printer.getFilename().c_str() << endl;
    }
    if(args.printVelocity > 0){
        cout << b::format("Printed velocities to %s") % velocity.printer.getFilename().c_str() << endl;
    }
    if(args.printAngularBond > 0){
        cout << b::format("Printed angular bond parameters to %s") % angularBond.getFilename().c_str() << endl;
    }
    if(args.printPairCorrelation > 0){
        cout << b::format("Printed pair correlations to %s/") % PAIR_CORRELATIONS_OUT << endl;
    }
    if(args.printStressFourier > 0){
        cout << endl << fc << endl;
        cout << "Storage modulus [kT/d^3]: " << fc.calculateStorageModulus() << endl;
        cout << "Loss modulus [kT/d^3]: " << fc.calculateLossModulus() << endl;
//        cout << "Old Storage modulus [kT/d^3]: " << fc.calculateStorageModulusOld() << endl;
//        cout << "Old Loss modulus [kT/d^3]: " << fc.calculateLossModulusOld() << endl;
        for(int i = 0; i <= 4; i++){
            cout << "Fourier component (xz) (n= " << i << "): " << fc.calculate(i).xz << endl;
            if(i > 0){
                cout << "Fourier component (xz) (n=" << -i << "): " << fc.calculate(-i).xz << endl;
            }
        }
    }
    
    cout << endl << surroundWithSeparator("Simulation end") << endl;
    
    clock.addTimePoint();
    cout << endl << "Task finished at " << clock.readTimePoint(-1) << endl;
    cout << b::format("Task finished in %.3f seconds (%s)") % clock.getDuration(0, -1) % clock.readDuration(0, -1).c_str() << endl;
    cout << endl;
    
    return 0;
}