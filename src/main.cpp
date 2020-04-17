#include "global.h"
#include "tools/printer.h"

#include "systems/sheared_slitpore_system.h"
#include "command/average_stress.h"

#include <ctime>
#include "tools/clock.h"
#include "version.h"
#include <experimental/filesystem>
namespace fs = experimental::filesystem;

int main(int argc, const char *argv[]){
    CLOCK clock;

    // parse command line inputs
    ARGUMENT_PARSER parser(argc, argv);
    ARGUMENTS args = parser.parseArgs();

    if(args.printVersion){
        cout << PROJECT_VERSION << endl;
        exit(0);
    }

    cout << "Task started at " << clock.readTimePoint(0) << endl << endl;

    //print version details
    cout << "Version: " << PROJECT_VERSION << endl;
    cout << "Git branch: " << GIT_BRANCH << endl;
    cout << "Git commit: " << GIT_COMMIT_HASH << endl;
    cout << "Git version: " << GIT_VERSION << endl << endl;

    srand(getpid() * time(0));

    //print parsed arguments
    args.print();

    if(args.dryRun){
        cout << "This was a dry run. To do an actual run, remove the '--dry' option!" << endl;
        exit(0);
    }

    // initialize Slitpore System
    SHEARED_SLITPORE_SYSTEM sys(args);
//    sys.readEnsembleSystem(0);

    // create container for stresses
    AVERAGE_STRESS averageStress;

    cout << endl;
    cout << "#i" << "\t";
    cout << "xx" << "\t";
    cout << "xy" << "\t";
    cout << "xz" << "\t";
    cout << "yy" << "\t";
    cout << "yz" << "\t";
    cout << "zz" << "\t";
    cout << endl;
    const char* format_f = "% .5f\t";

    for(int i = 0; i < 10; ++i){ //100000
        sys.simulateForSteps(1);
        averageStress.doForSystem(sys);
        if(i%1==0){
            printf("%6d\t", i);
            printf(format_f, averageStress.getStress().xx);
            printf(format_f, averageStress.getStress().xy);
            printf(format_f, averageStress.getStress().xz);
            printf(format_f, averageStress.getStress().yy);
            printf(format_f, averageStress.getStress().yz);
            printf(format_f, averageStress.getStress().zz);
            cout << endl;
        }
        if(i%1==0){
            //save particle positions to file
            fs::create_directory("snapshots");
            sys.printConfigurationToFile("snapshots/configuration_" + to_string(i) + ".out");
        }
    }
    sys.printConfigurationToFile("configuration.out");

    clock.addTimePoint();
    cout << endl << "Task finished at " << clock.readTimePoint(-1) << endl;
    printf("Task finished in %.3f seconds (%s)", clock.getDuration(0, -1), clock.readDuration(0, -1).c_str());

    return 0;
}

