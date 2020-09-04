//
// Created by mhuels on 4/8/20.
//

#include "arguments.h"

#include <iostream>

void ARGUMENTS::print() {
    if(seed == 0){
        cout << "RNG seed" << sep << "not set" << endl;
    }
    else{
        cout << "RNG seed" << sep << seed << endl;
    }
    if(rngCounter != 0 ){
        cout << "RNG counter" << sep << rngCounter << endl;
    }
    cout << endl;
    cout << "Configuration file" << sep << configurationIn << endl;
    cout << endl;
    cout << "shearRate" << sep << shearRate << endl;
    cout << "amplitude" << sep << amplitude << endl;
    cout << "oscillationPeriod" << sep << oscillationPeriod << endl;
    cout << "phaseOffset" << sep << phaseOffset << endl;
    cout << "dt" << sep << dt << endl;
    cout << "temperature" << sep << temperature << endl;
    cout << "D0" << sep << D0 << endl;
    cout << "ssInteractionStrength" << sep << ssInteractionStrength << endl;
    cout << "wallInteractionStrength" << sep << wallInteractionStrength << endl;
    cout << endl;
    cout << "TotalNumberOfTimesteps" << sep << totalNumberOfTimesteps << endl;
    if(snapshotInterval > 0){
        cout << "snapshotInterval" << sep << snapshotInterval << endl;
    }
    if(printPairCorrelation > 0){
        cout << "printPairCorrelation" << sep << printPairCorrelation << endl;
    }
    if(printVelocity > 0){
        cout << "printVelocity" << sep << printVelocity << endl;
    }
    if(printStress > 0){
        cout << "printStress" << sep << printStress << endl;
    }
    if(stressFourier > 0){
        cout << "stressFourier" << sep << stressFourier << endl;
    }
    if(printEnergy > 0){
        cout << "printEnergy" << sep << printEnergy << " (not yet implemented)" << endl;
    }
    if(printAngularBond > 0){
        cout << "printAngularBond" << sep << printAngularBond << endl;
    }
    cout << endl;
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
