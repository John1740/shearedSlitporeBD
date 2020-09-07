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
public:
    unsigned int seed = 0;
    unsigned long long rngCounter = 0;
    
    string configurationIn = CONFIGURATION_IN;
    string settingsIn = SETTINGS_IN;

    double shearRate = SHEAR_RATE;
    double amplitude = AMPLITUDE;
    double oscillationPeriod = OSCILLATION_PERIOD;
    double phaseOffset = PHASE_OFFSET;

    double dt = DELTA_T;
    double temperature = TEMPERATURE;
    double D0 = DIFFUSION_CONSTANT;
    double ssInteractionStrength = SS_INTERACTION_STRENGTH;
    double wallInteractionStrength = WALL_INTERACTION_STRENGTH;

    int totalNumberOfTimesteps = TOTAL_NUMBER_OF_TIMESTEPS;
    
    int printVelocity = PRINT_VELOCITY;
    int printStress = PRINT_STRESS;
    int printStressFourier = PRINT_STRESS_FOURIER;
    int printEnergy = PRINT_ENERGY;
    int printAngularBond = PRINT_ANGULAR_BOND;
    int printSnapshots = PRINT_SNAPSHOTS;
    int printPairCorrelation = PRINT_PAIR_CORRELATION;
    
    bool clear = CLEAR;
    bool dry = false;
    bool printVersion = false;
    
    // constructors
    ARGUMENTS();
    ARGUMENTS(string filename);
    
    // update with other instance of this class
    ARGUMENTS& update(const ARGUMENTS& other);

    friend ostream& operator<<(ostream& os, const ARGUMENTS& args);

    ARGUMENTS& setSeparator(string sep);
    string getSeparator() const;
    
    // file-handling
    bool readFromFile(string filename, char comment='#');
    ARGUMENTS& writeToFile(string filename);
};


#endif //SHEAREDSLITPOREBD_ARGUMENTS_H
