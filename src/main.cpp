

#include "global.h"
#include "tools/printer.h"
#include "tools/parse_arguments.h"

#include "systems/sheared_slitpore_system.h"
#include "command/average_stress.h"

#include <ctime>
#include <limits>


int main(int argc, char *argv[]){
    srand(getpid()*time(0));

    PARSE_ARGUMENTS parseArguments;
    arguments = parseArguments.getArgumentList(argc, argv);
    parseArguments.checkForInvalidArguments(arguments);
    parseArguments.printArgumentList(arguments);

    ///////////////////////// SLIT-PORE SYSTEM ////////////////////////////////////   

    SHEARED_SLITPORE_PARAMETERS sysParameters;
    sysParameters.setAsBiLayerWithShearRate(0);
    sysParameters.print();

    SHEARED_SLITPORE_SYSTEM sys(sysParameters);
    sys.readEnsembleSystem(0);
    sys.STRESS=true;
    sys.setShearRate(200);

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

    for(int i = 0; i < 100000; ++i){
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

    return 0;
}

