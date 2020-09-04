//
// Created by mhuels on 4/8/20.
//

#include "arguments.h"

#include <iostream>
#include "../printer/printer.h"
#include <boost/algorithm/string.hpp>
namespace bo = boost;

ARGUMENTS::ARGUMENTS(){

}

ARGUMENTS::ARGUMENTS(string filename){
    readFromFile(filename);
}

ostream& operator<<(ostream& os, const ARGUMENTS& args){
    if(args.seed == 0){
        os << "seed" << args.sep << "not set" << endl;
    }
    else{
        os << "seed" << args.sep << args.seed << endl;
    }
    if(args.rngCounter != 0 ){
        os << "rngCounter" << args.sep << args.rngCounter << endl;
    }
    os << endl;
    os << "configuration" << args.sep << args.configurationIn << endl;
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
    os << "totalNumberOfTimesteps" << args.sep << args.totalNumberOfTimesteps << endl;
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

bool str_is_empty(string str){
    return str.empty();
}

ARGUMENTS& ARGUMENTS::readFromFile(string filename){
    ifstream f;
    f.open(filename.c_str());
    string line;
    while(getline(f, line)){
        vector<string> linesplit;
        //skip empty lines
        if(line.empty()){
            continue;
        }
        bo::split(linesplit, line, bo::is_any_of(sep));
        //remove empty strings
        auto new_end = remove_if(linesplit.begin(), linesplit.end(), str_is_empty);
        linesplit.erase(new_end, linesplit.end());
        if(line.find("seed") != string::npos){
            amplitude = stod(linesplit[1]);
        }
        else if(line.find("shearRate") != string::npos){
            shearRate = stod(linesplit[1]);
        }
        else if(line.find("amplitude") != string::npos){
            amplitude = stod(linesplit[1]);
        }
        else{
            cout << line << " unrecognized!" << endl;
        }
    }
    f.close();
    return *this;
}

ARGUMENTS& ARGUMENTS::writeToFile(string filename){
    PRINTER printer(filename);
    printer.reset();
    printer << *this;
    return *this;
}
