

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
    sys.setShearRate(400);

    AVERAGE_STRESS averageStress;

    for(int i = 0; i < 100000; ++i){
        if(i%100==0){
            cout << "i: " << i << endl;
        }
        sys.simulateForSteps(1);
        averageStress.doForSystem(sys);
        if(i%100==0){
            cout << "stress (xz): " << averageStress.getStress().xz << endl;

            //save particle positions to file
            sys.printSystem("test");    //rename printSystem -> writeToFile (or something more meaningful)
        }
    }

    return 0;
}

