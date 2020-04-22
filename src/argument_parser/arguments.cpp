//
// Created by mhuels on 4/8/20.
//

#include "arguments.h"

void ARGUMENTS::print() {
    cout << "Configuration file: " << configurationIn << endl << endl;

    cout << "shearRate = " << shearRate << endl;
    cout << "dWall = " << dWall << "\t\t" << "density = " << density << "\t\t" << "numberOfParticles = " << numberOfParticles << endl;
    cout << "charge = " << charge << "\t\t" << "diameter = " << diameter << endl;
    cout << "dt = " << dt << endl;
    cout << "temperature = " << temperature << endl;
    cout << "D0 = " << D0 << endl;
    cout << "ssInteractionStrength = " << ssInteractionStrength << "\t\t" << "wallInteractionStrength = " << wallInteractionStrength << endl << endl;

    cout << "TotalNumberOfTimesteps = " << totalNumberOfTimesteps << endl;
    if(snapshotInterval > 0){
        cout << "snapshotInterval = " << snapshotInterval << endl;
    }
    if(printStress > 0){
        cout << "printStress = " << printStress << endl;
    }
    if(printEnergy > 0){
        cout << "printEnergy = " << printEnergy << endl;
    }
}
