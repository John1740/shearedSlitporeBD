//
// Created by mhuels on 4/8/20.
//

#include "arguments.h"

void ARGUMENTS::print() {
    cout << "Arguments:" << endl;

    cout << "Configuration file: " << configurationIn << endl;

    cout << "shearRate = " << shearRate << endl;

    cout << "dWall = " << dWall << "\t\t" << "density = " << density << "\t\t" << "numberOfParticles = " << numberOfParticles << endl;
    cout << "charge = " << charge << "\t\t" << "diameter = " << diameter << endl;
    cout << "dt = " << dt << endl;
    cout << "temperature = " << temperature << endl;
    cout << "D0 = " << D0 << endl;

    cout << "ssInteractionStrength = " << ssInteractionStrength << "\t\t" << "wallInteractionStrength = " << wallInteractionStrength << endl;

    if(printStress){
        cout << "Printing out stresses!" << endl;
    }
    if(printEnergy){
        cout << "Printing out energies!" << endl;
    }
    cout << endl;
}
