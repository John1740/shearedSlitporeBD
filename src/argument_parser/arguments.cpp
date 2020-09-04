//
// Created by mhuels on 4/8/20.
//

#include "arguments.h"

#include <iostream>

void ARGUMENTS::print() {
    if(seed == 0){
        cout << "RNG seed: not set" << endl;
    }
    else{
        cout << "RNG seed: " << seed << endl;
    }
    if(rngCounter != 0 ){
        cout << "RNG counter: " << rngCounter << endl;
    }
    cout << endl;
    
    cout << "Configuration file: " << configurationIn << endl << endl;

    cout << "shearRate: " << shearRate << endl;
    cout << "amplitude: " << amplitude << endl;
    cout << "oscillationPeriod: " << oscillationPeriod << endl;
    cout << "phaseOffset: " << phaseOffset << endl;
    cout << "dt: " << dt << endl;
    cout << "temperature: " << temperature << endl;
    cout << "D0: " << D0 << endl;
    cout << "ssInteractionStrength: " << ssInteractionStrength << "\t\t" << "wallInteractionStrength = " << wallInteractionStrength << endl << endl;

    cout << "TotalNumberOfTimesteps: " << totalNumberOfTimesteps << endl;
    if(snapshotInterval > 0){
        cout << "snapshotInterval: " << snapshotInterval << endl;
    }
    if(printPairCorrelation > 0){
        cout << "printPairCorrelation: " << printPairCorrelation << endl;
    }
    if(printVelocity > 0){
        cout << "printVelocity: " << printVelocity << endl;
    }
    if(printStress > 0){
        cout << "printStress: " << printStress << endl;
    }
    if(stressFourier > 0){
        cout << "stressFourier: " << stressFourier << endl;
    }
    if(printEnergy > 0){
        cout << "printEnergy: " << printEnergy << endl;
        cout << "Energy print-outs not yet implemented!" << endl;
    }
    if(printAngularBond > 0){
        cout << "printAngularBond: " << printAngularBond << endl;
    }
    if(clear){
        cout << "Clearing all existing output-files!" << endl;
    }
}

ARGUMENTS& ARGUMENTS::setSeparator(string sep){
    this->sep = sep;
    return *this;
}

string ARGUMENTS::getSeparator() const{
    return sep;
}
