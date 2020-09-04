//
// Created by mhuels on 4/8/20.
//

#include "arguments.h"

#include <iostream>
#include "../printer/printer.h"

ostream& operator<<(ostream& os, const ARGUMENTS& args){
    if(args.seed == 0){
        os << "RNG seed" << args.sep << "not set" << endl;
    }
    else{
        os << "RNG seed" << args.sep << args.seed << endl;
    }
    if(args.rngCounter != 0 ){
        os << "RNG counter" << args.sep << args.rngCounter << endl;
    }
    os << endl;
    os << "Configuration file" << args.sep << args.configurationIn << endl;
    os << endl;
    os << "shearRate" << args.sep << args.shearRate << endl;
    os << "amplitude" << args.sep << args.amplitude << endl;
    os << "oscillationPeriod" << args.sep << args.oscillationPeriod << endl;
    os << "phaseOffset" << args.sep << args.phaseOffset << endl;
    os << "dt" << args.sep << args.dt << endl;
    os << "temperature" << args.sep << args.temperature << endl;
    os << "D0" << args.sep << args.D0 << endl;
    os << "ssInteractionStrength" << args.sep << args.ssInteractionStrength << endl;
    os << "wallInteractionStrength" << args.sep << args.wallInteractionStrength << endl;
    os << endl;
    os << "TotalNumberOfTimesteps" << args.sep << args.totalNumberOfTimesteps << endl;
    if(args.snapshotInterval > 0){
        os << "snapshotInterval" << args.sep << args.snapshotInterval << endl;
    }
    if(args.printPairCorrelation > 0){
        os << "printPairCorrelation" << args.sep << args.printPairCorrelation << endl;
    }
    if(args.printVelocity > 0){
        os << "printVelocity" << args.sep << args.printVelocity << endl;
    }
    if(args.printStress > 0){
        os << "printStress" << args.sep << args.printStress << endl;
    }
    if(args.stressFourier > 0){
        os << "stressFourier" << args.sep << args.stressFourier << endl;
    }
    if(args.printEnergy > 0){
        os << "printEnergy" << args.sep << args.printEnergy << " (not yet implemented)" << endl;
    }
    if(args.printAngularBond > 0){
        os << "printAngularBond" << args.sep << args.printAngularBond << endl;
    }
    os << endl;
    return os;
}

ARGUMENTS& ARGUMENTS::setSeparator(string sep){
    this->sep = sep;
    return *this;
}

string ARGUMENTS::getSeparator() const{
    return sep;
}

ARGUMENTS& ARGUMENTS::readFromFile(string filename){
    return *this;
}

ARGUMENTS& ARGUMENTS::writeToFile(string filename){
    PRINTER printer(filename);
    printer << *this;
    return *this;
}
