#include "global.h"
#include <ctime>
#include "tools/clock.h"
#include "version.h"
#include <experimental/filesystem>
#include "tools/format.h"
#include "boost/format.hpp"

#include "systems/sheared_slitpore_system.h"

#include "printer/printer.h"
#include "printer/stress.h"
#include "printer/velocity.h"
#include "printer/angular_bond.h"

namespace fs = experimental::filesystem;

int main(int argc, const char *argv[]){
    cout << surroundWithSeparator("shearedSlitporeBD") << endl << endl;
    CLOCK clock;
    
    ARGUMENT_PARSER parser(argc, argv);
    ARGUMENTS args = parser.parseArgs();

    if(args.printVersion){
        cout << PROJECT_VERSION << endl;
        exit(0);
    }

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

    // initialize Slitpore System
    SHEARED_SLITPORE_SYSTEM sys(args);
    sys.writeConfigurationToFile("configuration.in.new", true);

    if(args.dryRun){
        cout << "This was a dry run. To do an actual run, remove the '--dry' option!" << endl;
        exit(0);
    }

    cout << endl << surroundWithSeparator("Simulation start") << endl;
    
    VELOCITY_PRINTER velocity(&sys);
    STRESS_PRINTER stress(&sys);
    ANGULAR_BOND_PRINTER angularBond;

    //column description
    for(int i = 0; i < args.totalNumberOfTimesteps; i++){
        if(i % (int)ceil(args.totalNumberOfTimesteps / 100.) == 0){
            printf("Progress: %.1f%% (timestep %ld)\n", 100 * i / float(args.totalNumberOfTimesteps), sys.getTimestep());
        }
        if(args.printAngularBond > 0 && i % args.printAngularBond == 0){
            angularBond.printLine(sys);
        }
        sys.simulateForSteps(1);
        if(args.printStress > 0 && i % args.printStress == 0){
            stress.printLine();
        }
        if(args.printVelocity > 0 && i % args.printVelocity == 0 && i > 0){
            velocity.printLine();
        }
        if(args.snapshotInterval != 0 && (i + 1) % args.snapshotInterval == 0){
            //save particle positions to file
            fs::create_directory("snapshots");  //implement this within printer class
            sys.writeConfigurationToFile("snapshots/configuration_" + to_string(sys.getTimestep()) + ".out", false);
        }
    }
    sys.writeConfigurationToFile("configuration.out");
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