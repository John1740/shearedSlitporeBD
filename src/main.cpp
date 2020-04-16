

#include "global.h"
#include "tools/printer.h"

#include "systems/sheared_slitpore_system.h"
#include "command/average_stress.h"

#include <ctime>
#include "tools/clock.h"

int main(int argc, const char *argv[]){
    CLOCK clock;
    cout << "Task started at " << clock.readTimePoint(0) << endl << endl;

    srand(getpid() * time(0));

    // parse command line inputs
    ARGUMENT_PARSER parser(argc, argv);
    ARGUMENTS args = parser.parseArgs();
    args.print();

    // initialize Slitpore System
    SHEARED_SLITPORE_SYSTEM sys(args);
    sys.readEnsembleSystem(0);

    // create container for stresses
    AVERAGE_STRESS averageStress;

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
        if(i%100==0){
            //save particle positions to file
            sys.printSystem("restart");    //rename printSystem -> writeToFile (or something more meaningful)
        }
    }

    clock.addTimePoint();
    cout << endl;
    cout << "Task finished at " << clock.readTimePoint(-1) << endl;
    printf("Task finished in %.3f seconds (%s)", clock.getDuration(0, -1), clock.readDuration(0, -1).c_str());

    return 0;
}

