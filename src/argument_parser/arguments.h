//
// Created by mhuels on 4/8/20.
//

#ifndef SHEAREDSLITPOREBD_ARGUMENTS_H
#define SHEAREDSLITPOREBD_ARGUMENTS_H

#include <string>
#include "../defaults.h"
using namespace std;

class ARGUMENTS{
private:
    string sep = ": ";
    double duration = 0;    //placeholder in case dt is not set yet
    double numberOfPeriods = 0; //placeholder
public:
    unsigned int seed = 0;
    unsigned long long rngCounter = 0;
    
    string configurationIn = CONFIGURATION_IN;
    string settingsIn = SETTINGS_IN;

    double shearRate = SHEAR_RATE;
    double amplitude = AMPLITUDE;
    double oscillationPeriod = OSCILLATION_PERIOD;
    double phaseOffset = PHASE_OFFSET;

    double dt = 0;
    double temperature = TEMPERATURE;
    double D0 = DIFFUSION_CONSTANT;
    double ssInteractionStrength = SS_INTERACTION_STRENGTH;
    double wallInteractionStrength = WALL_INTERACTION_STRENGTH;

    int numberOfTimesteps = NUMBER_OF_TIMESTEPS;
    
    int printVelocity = PRINT_VELOCITY;
    int printStress = PRINT_STRESS;
    int printStressFourier = PRINT_STRESS_FOURIER;
    int printEnergy = PRINT_ENERGY;
    int printAngularBond = PRINT_ANGULAR_BOND;
    int printSnapshots = PRINT_SNAPSHOTS;
    int printPairCorrelation = PRINT_PAIR_CORRELATION;
    int printAll = PRINT_ALL;
    
    bool clear = CLEAR;
    bool dry = false;
    bool printVersion = false;
    
    // constructors
    ARGUMENTS();
    ARGUMENTS(string filename);
    
    // update with other instance of this class
    ARGUMENTS& update(const ARGUMENTS& other);
    ARGUMENTS& polish();

    friend ostream& operator<<(ostream& os, const ARGUMENTS& args);

    // getter
    double getDuration() const;
    double getNumberOfPeriods() const;

    //setter
    ARGUMENTS& setDuration(double duration);
    ARGUMENTS& recoverDuration();   //can be used once dt-defaulting is done
    ARGUMENTS& recoverNumberOfPeriods();
    ARGUMENTS& setNumberOfPeriods(double numberOfPeriods);
    ARGUMENTS& setDefaultDt();
    ARGUMENTS& setSeparator(string sep);
    string getSeparator() const;
    
    // file-handling
    bool readFromFile(string filename, char comment='#', bool twice=true);
    ARGUMENTS& writeToFile(string filename);
};


#endif //SHEAREDSLITPOREBD_ARGUMENTS_H
