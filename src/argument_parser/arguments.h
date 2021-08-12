//
// Created by mhuels on 4/8/20.
//

#ifndef SHEAREDSLITPOREBD_ARGUMENTS_H
#define SHEAREDSLITPOREBD_ARGUMENTS_H

#include <string>
#include "../defaults.h"
#include "print_intervals.h"

using namespace std;

class ARGUMENTS{
private:
    string sep = ": ";
    bool finalized = false;    // toggles whether finalize() needs to be called
    // placeholders
    double duration = 0;
    double numberOfPeriods = 0;
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
    double kT = KT;
    double mu = MU;
    double kappa = KAPPA;
    double yInteractionStrength = Y_INTERACTION_STRENGTH;
    double ssInteractionStrength = SS_INTERACTION_STRENGTH;
    double wallInteractionStrength = WALL_INTERACTION_STRENGTH;

    long numberOfTimesteps = NUMBER_OF_TIMESTEPS;

    PRINT_INTERVAL skip;
    PRINT_INTERVAL printStress;
    PRINT_INTERVAL printStressFourier;
    PRINT_INTERVAL printEnergy;
    PRINT_INTERVAL printLayerPosition;
    PRINT_INTERVAL printLayerVelocity;
    PRINT_INTERVAL printAngularBond;
    PRINT_INTERVAL printSnapshots;
    PRINT_INTERVAL printPairCorrelation;
    int printAll = PRINT_ALL;

    PRINT_INTERVAL milestone;
    double milestoneRuntime = MILESTONE_RUNTIME;
    double milestoneRuntimeOffset = MILESTONE_RUNTIME_OFFSET;

    bool restart = RESTART;
    bool clear = CLEAR;
    bool dry = false;
    bool printVersion = false;

    // constructors
    ARGUMENTS();
    ARGUMENTS(string filename);
    ARGUMENTS(int argc, const char* argv[]);
    ARGUMENTS& setup();

    // update with other instance of this class
    ARGUMENTS& update(const ARGUMENTS& other);

    // choose the prioritized print intervals
    ARGUMENTS& finalize();

    // getter
    double getDuration() const;
    double getNumberOfPeriods() const;
    bool isFinalized() const;
    string getSeparator() const;

    //setter
    ARGUMENTS& setDuration(double duration);
    ARGUMENTS& setNumberOfPeriods(double numberOfPeriods);
    ARGUMENTS& setDefaultDt();
    ARGUMENTS& setDefaultMilestone();
    ARGUMENTS& setDefaultMilestoneRuntimeOffset();
    ARGUMENTS& setSeparator(string sep);

    // operators
    friend ostream& operator<<(ostream& os, const ARGUMENTS& args);

    // file-handling
    bool readFromFile(string filename, char comment = '#');

    ARGUMENTS& writeToFile(string filename);
};

#endif //SHEAREDSLITPOREBD_ARGUMENTS_H
