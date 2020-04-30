#include "global.h"
#include "tools/printer.h"

#include "systems/sheared_slitpore_system.h"
#include "command/average_stress.h"

#include <ctime>
#include "tools/clock.h"
#include "version.h"
#include <experimental/filesystem>
#include "tools/format.h"
#include "output/stress.h"
#include "output/velocity.h"
namespace fs = experimental::filesystem;

int main(int argc, const char *argv[]){
    CLOCK clock;
    srand(getpid() * time(0));
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

    //print parsed arguments
    cout << surroundWithSeparator("Parsed arguments") << endl;
    args.print();
    cout << endl;

    cout << surroundWithSeparator("System Initialization") << endl;

    // initialize Slitpore System
    SHEARED_SLITPORE_SYSTEM sys(args);
//    sys.readEnsembleSystem(0);

    if(args.dryRun){
        cout << "This was a dry run. To do an actual run, remove the '--dry' option!" << endl;
        exit(0);
    }

    cout << endl << surroundWithSeparator("Simulation start") << endl;
    
    VELOCITY velocity;
    STRESS stress;  //change something here, such that stresses.out does not get written when not wished for
    if(args.printStress > 0){
        stress.printHeader();
    }

    //column description
    for(int i = 0; i < args.totalNumberOfTimesteps; ++i){
        printf("Progress: %d (%.1f%%)\n", i, 100 * i / float(args.totalNumberOfTimesteps));
        sys.simulateForSteps(1);
        if(args.printStress > 0 && i % args.printStress == 0){
            stress.printLine(sys, i);
        }
        if(args.printVelocity > 0 && i % args.printVelocity == 0 && i>0){
            velocity.printLine(sys, i-1);
        }
        if(args.snapshotInterval != 0 && i % args.snapshotInterval == 0){
            //save particle positions to file
            fs::create_directory("snapshots");  //implement this within printer class
            sys.writeConfigurationToFile("snapshots/configuration_" + to_string(i) + ".out");
        }
    }
    sys.writeConfigurationToFile("configuration.out");
    
    cout << endl << surroundWithSeparator("Simulation end") << endl;
    
    clock.addTimePoint();
    cout << endl << "Task finished at " << clock.readTimePoint(-1) << endl;
    printf("Task finished in %.3f seconds (%s)\n", clock.getDuration(0, -1), clock.readDuration(0, -1).c_str());

    return 0;
}

