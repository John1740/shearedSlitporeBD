//
// Created by mhuels on 4/8/20.
//

#include "arguments.h"

#include <iostream>
#include "../printer/printer.h"
#include <boost/algorithm/string.hpp>
namespace bo = boost;
#include <experimental/filesystem>
namespace fs = experimental::filesystem;
#include <cmath>

bool str_is_empty(string str){
    return str.empty();
}

ARGUMENTS::ARGUMENTS(){
    setup();
}

ARGUMENTS::ARGUMENTS(string filename){
    setup();
    readFromFile(filename);
    settingsIn = filename;
}

ARGUMENTS& ARGUMENTS::setup(){
    printStress = PRINT_INTERVAL(&numberOfTimesteps, &dt, &oscillationPeriod);
    printStressFourier = PRINT_INTERVAL(&numberOfTimesteps, &dt, &oscillationPeriod);
    printEnergy = PRINT_INTERVAL(&numberOfTimesteps, &dt, &oscillationPeriod);
    printAngularBond = PRINT_INTERVAL(&numberOfTimesteps, &dt, &oscillationPeriod);
    printSnapshots = PRINT_INTERVAL(&numberOfTimesteps, &dt, &oscillationPeriod);
    printPairCorrelation = PRINT_INTERVAL(&numberOfTimesteps, &dt, &oscillationPeriod);
    return *this;
}

ARGUMENTS& ARGUMENTS::update(const ARGUMENTS& other){
    //only update if non-default values
    if(other.seed != 0) seed = other.seed;
    if(other.rngCounter != 0) rngCounter = other.rngCounter;
    if(other.settingsIn != SETTINGS_IN) settingsIn = other.settingsIn;
    if(other.configurationIn != CONFIGURATION_IN) configurationIn = other.configurationIn;
    if(other.shearRate != SHEAR_RATE) shearRate = other.shearRate;
    if(other.amplitude != AMPLITUDE) amplitude = other.amplitude;
    if(other.oscillationPeriod != OSCILLATION_PERIOD) oscillationPeriod = other.oscillationPeriod;
    if(other.phaseOffset != PHASE_OFFSET) phaseOffset = other.phaseOffset;
    if(other.dt != 0) dt = other.dt;
    if(other.temperature != TEMPERATURE) temperature = other.temperature;
    if(other.D0 != DIFFUSION_CONSTANT) D0 = other.D0;
    if(other.ssInteractionStrength != SS_INTERACTION_STRENGTH) ssInteractionStrength = other.ssInteractionStrength;
    if(other.wallInteractionStrength != WALL_INTERACTION_STRENGTH) wallInteractionStrength = other.wallInteractionStrength;
    if(other.numberOfTimesteps != 0){
        numberOfTimesteps = other.numberOfTimesteps;
        duration = 0;   //other.numberOfTimesteps has priority
        numberOfPeriods = 0;
    }
    if(other.duration != 0){
        duration = other.duration;
        numberOfPeriods = 0;    //other.duration has priority
    }
    if(other.numberOfPeriods != 0) numberOfPeriods = other.numberOfPeriods;
    if(other.printAll != PRINT_ALL) printAll = other.printAll;
    printStress.update(other.printStress);
    printStressFourier.update(other.printStressFourier);
    printEnergy.update(other.printEnergy);
    if(other.printVelocity != PRINT_VELOCITY) printVelocity = other.printVelocity;
    printAngularBond.update(other.printAngularBond);
    printSnapshots.update(other.printSnapshots);
    printPairCorrelation.update(other.printPairCorrelation);

    //defaults don't matter for these options
    clear = other.clear;
    dry = other.dry;
    printVersion = other.printVersion;
    finalized = false;
    return *this;
}

ostream& operator<<(ostream& os, const ARGUMENTS& args){
    os << "settings" << args.sep << args.settingsIn << endl;
    os << endl;
    if(args.seed == 0){
        os << "seed" << args.sep << "not set" << endl;
    }
    else{
        os << "seed" << args.sep << args.seed << endl;
    }
    os << "rngCounter" << args.sep << args.rngCounter << endl;
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
    os << "numberOfTimesteps" << args.sep << args.numberOfTimesteps << endl;
    os << "duration" << args.sep << args.getDuration() << endl;
    os << "numberOfPeriods" << args.sep << args.getNumberOfPeriods() << endl;
    if(args.printStress > 0){
        os << "printStress" << args.sep << args.printStress << endl;
        os << "printStressDuration" << args.sep << args.printStress.getDuration() << endl;
        os << "printStressPeriod" << args.sep << args.printStress.getPeriod() << endl;
    }
    if(args.printStressFourier > 0){
        os << "printStressFourier" << args.sep << args.printStressFourier << endl;
        os << "printStressFourierDuration" << args.sep << args.printStressFourier.getDuration() << endl;
        os << "printStressFourierPeriod" << args.sep << args.printStressFourier.getPeriod() << endl;
    }
    if(args.printEnergy > 0){
        os << "printEnergy" << args.sep << args.printEnergy << " (not yet implemented)" << endl;
        os << "printEnergyDuration" << args.sep << args.printEnergy.getDuration() << " (not yet implemented)" << endl;
        os << "printEnergyPeriod" << args.sep << args.printEnergy.getPeriod() << " (not yet implemented)" << endl;
    }
    if(args.printVelocity > 0){
        os << "printVelocity" << args.sep << args.printVelocity << endl;
    }
    if(args.printAngularBond > 0){
        os << "printAngularBond" << args.sep << args.printAngularBond << endl;
        os << "printAngularBondDuration" << args.sep << args.printAngularBond.getDuration() << endl;
        os << "printAngularBondPeriod" << args.sep << args.printAngularBond.getPeriod() << endl;
    }
    if(args.printSnapshots > 0){
        os << "printSnapshots" << args.sep << args.printSnapshots << endl;
        os << "printSnapshotsDuration" << args.sep << args.printSnapshots.getDuration() << endl;
        os << "printSnapshotsPeriod" << args.sep << args.printSnapshots.getPeriod() << endl;
    }
    if(args.printPairCorrelation > 0){
        os << "printPairCorrelation" << args.sep << args.printPairCorrelation << endl;
        os << "printPairCorrelationDuration" << args.sep << args.printPairCorrelation.getDuration() << endl;
        os << "printPairCorrelationPeriod" << args.sep << args.printPairCorrelation.getPeriod() << endl;
    }
    return os;
}

bool ARGUMENTS::readFromFile(string filename, char comment){
    if(!fs::exists(filename)){
        cout << filename << " does not exist!" << endl;
        return false;
    }
    ifstream f;
    f.open(filename.c_str());
    string line;
    while(getline(f, line)){
        vector<string> linesplit;
        //skip empty lines and comments
        if(line.empty() || line.find(comment) == 0){
            continue;
        }
        bo::split(linesplit, line, bo::is_any_of(sep));
        //remove empty strings
        auto new_end = remove_if(linesplit.begin(), linesplit.end(), str_is_empty);
        linesplit.erase(new_end, linesplit.end());
        if(line.find("seed") != string::npos){
            seed = stoul(linesplit[1]);
        }
        else if(line.find("rngCounter") != string::npos){
            rngCounter = stoull(linesplit[1]);
        }
        else if(line.find("configuration") != string::npos){
            configurationIn = linesplit[1];
        }
        else if(line.find("shearRate") != string::npos){
            shearRate = stod(linesplit[1]);
        }
        else if(line.find("amplitude") != string::npos){
            amplitude = stod(linesplit[1]);
        }
        else if(line.find("oscillationPeriod") != string::npos){
            oscillationPeriod = stod(linesplit[1]);
        }
        else if(line.find("phaseOffset") != string::npos){
            phaseOffset = stod(linesplit[1]);
        }
        else if(line.find("dt") != string::npos){
            dt = stod(linesplit[1]);
        }
        else if(line.find("temperature") != string::npos){
            temperature = stod(linesplit[1]);
        }
        else if(line.find("D0") != string::npos){
            D0 = stod(linesplit[1]);
        }
        else if(line.find("ssInteractionStrength") != string::npos){
            ssInteractionStrength = stod(linesplit[1]);
        }
        else if(line.find("wallInteractionStrength") != string::npos){
            wallInteractionStrength = stod(linesplit[1]);
        }
        else if(line.find("numberOfTimesteps") != string::npos){
            numberOfTimesteps = long(stod(linesplit[1]));
        }
        else if(line.find("duration") != string::npos){
            duration = stod(linesplit[1]);
        }
        else if(line.find("numberOfPeriods") != string::npos){
            numberOfPeriods = stod(linesplit[1]);
        }
        //needs to be before "printStress"
        else if(line.find("printStressFourierDuration") != string::npos){
            printStressFourier.setDuration(stod(linesplit[1]));
        }
        else if(line.find("printStressFourierPeriod") != string::npos){
            printStressFourier.setPeriod(stod(linesplit[1]));
        }
        else if(line.find("printStressFourier") != string::npos){
            printStressFourier = round(stod(linesplit[1]));
        }
        else if(line.find("printStressDuration") != string::npos){
            printStress.setDuration(stod(linesplit[1]));
        }
        else if(line.find("printStressPeriod") != string::npos){
            printStress.setPeriod(stod(linesplit[1]));
        }
        else if(line.find("printStress") != string::npos){
            printStress = round(stod(linesplit[1]));
        }
        else if(line.find("printEnergyDuration") != string::npos){
            printEnergy.setDuration(stod(linesplit[1]));
        }
        else if(line.find("printEnergyPeriod") != string::npos){
            printEnergy.setPeriod(stod(linesplit[1]));
        }
        else if(line.find("printEnergy") != string::npos){
            printEnergy = round(stod(linesplit[1]));
        }
        else if(line.find("printVelocity") != string::npos){
            printVelocity = round(stod(linesplit[1]));
        }
        else if(line.find("printAngularBondDuration") != string::npos){
            printAngularBond.setDuration(stod(linesplit[1]));
        }
        else if(line.find("printAngularBondPeriod") != string::npos){
            printAngularBond.setPeriod(stod(linesplit[1]));
        }
        else if(line.find("printAngularBond") != string::npos){
            printAngularBond = round(stod(linesplit[1]));
        }
        else if(line.find("printSnapshotsDuration") != string::npos){
            printSnapshots.setDuration(stod(linesplit[1]));
        }
        else if(line.find("printSnapshotsPeriod") != string::npos){
            printSnapshots.setPeriod(stod(linesplit[1]));
        }
        else if(line.find("printSnapshots") != string::npos){
            printSnapshots = round(stod(linesplit[1]));
        }
        else if(line.find("printPairCorrelationDuration") != string::npos){
            printPairCorrelation.setDuration(stod(linesplit[1]));
        }
        else if(line.find("printPairCorrelationPeriod") != string::npos){
            printPairCorrelation.setPeriod(stod(linesplit[1]));
        }
        else if(line.find("printPairCorrelation") != string::npos){
            printPairCorrelation = round(stod(linesplit[1]));
        }
        else if(line.find("printAll") != string::npos){
            printAll = round(stod(linesplit[1]));
        }
        else{
            cout << "Option unrecognized: " << line << endl;
        }
    }
    // overwrite print-statements by printAll if not further specified
    if(printAll > 0){
        if(printStress == PRINT_STRESS && printStress.getDuration() == 0 && printStress.getPeriod() == 0){
            printStress = printAll;
        }
        if(printStressFourier == PRINT_STRESS_FOURIER && printStressFourier.getDuration() == 0 && printStressFourier.getPeriod() == 0){
            printStressFourier = 1;
        }
        if(printEnergy == PRINT_ENERGY && printEnergy.getDuration() == 0 && printEnergy.getPeriod() == 0){
            printEnergy = printAll;
        }
        if(printVelocity == PRINT_VELOCITY){
            printVelocity = printAll;
        }
        if(printAngularBond == PRINT_ANGULAR_BOND && printAngularBond.getDuration() == 0 && printAngularBond.getPeriod() == 0){
            printAngularBond = printAll;
        }
        if(printSnapshots == PRINT_SNAPSHOTS && printSnapshots.getDuration() == 0 && printSnapshots.getPeriod() == 0){
            printSnapshots = printAll;
        }
        if(printPairCorrelation == PRINT_PAIR_CORRELATION && printPairCorrelation.getDuration() == 0 && printPairCorrelation.getPeriod() == 0){
            printPairCorrelation = printAll;
        }
    }
    f.close();
    finalized = false;
    return true;
}

ARGUMENTS& ARGUMENTS::writeToFile(string filename){
    PRINTER printer(filename);
    printer.reset();
    printer << *this;
    return *this;
}

// to be called at the very end once oscillationPeriod and dt are chosen
ARGUMENTS& ARGUMENTS::finalize(){
    finalized = true;   // needs to be at beginning because some functions question this
    // default dt if not given
    if(dt == 0){
        setDefaultDt();
    }
    // overwrite totalNumberOfTimesteps with priority numberOfPeriods > duration > totalNumberOfTimesteps
    if(duration != 0){
        setDuration(duration);
        duration = 0;
    }
    if(numberOfPeriods != 0){
        setNumberOfPeriods(numberOfPeriods);
        numberOfPeriods = 0;
    }
    printStress.finalize();
    printStressFourier.finalize();
    printEnergy.finalize();
    printAngularBond.finalize();
    printSnapshots.finalize();
    printPairCorrelation.finalize();
    return *this;
}

string ARGUMENTS::getSeparator() const{
    return sep;
}

double ARGUMENTS::getDuration() const{
    if(duration == 0){
        return numberOfTimesteps * dt;
    }
    else{
        return duration;
    }
}

double ARGUMENTS::getNumberOfPeriods() const{
    if(numberOfPeriods == 0){
        return getDuration() / oscillationPeriod;
    }
    else{
        return numberOfPeriods;
    }
}

bool ARGUMENTS::isFinalized() const {
    return finalized;
}

ARGUMENTS& ARGUMENTS::setSeparator(string sep){
    this->sep = sep;
    return *this;
}

ARGUMENTS& ARGUMENTS::setDuration(double duration){
    if(finalized){
        numberOfTimesteps = round(duration / dt);
    }
    else{
        this->duration = duration;
    }
    return *this;
}

ARGUMENTS& ARGUMENTS::setNumberOfPeriods(double numberOfPeriods){
    if(finalized){
        setDuration(numberOfPeriods * oscillationPeriod);
    }
    else{
        this->numberOfPeriods = numberOfPeriods;
    }
    return *this;
}

ARGUMENTS& ARGUMENTS::setDefaultDt() {
    // minimum due to energy potential (bigger dt lead to particles leaving the box)
    dt = 1e-5;
    // it needs dtDeformation to move the upper wall by the wall distance once
    // need to have at least 1000 sample points for that time
    double dtDeformation = 1 / (abs(shearRate) + abs(amplitude)) / 1000;
    if(dt > dtDeformation){
        dt = dtDeformation;
    }
    // need to have at least 1000 sample points per oscillation period
    double dtOscillation = oscillationPeriod / 1000;
    if(dt > dtOscillation){
        dt = dtOscillation;
    }
    // make dt even split of oscillationPeriod
    dt = oscillationPeriod / round(oscillationPeriod / dt);
    return *this;
}
