//
// Created by mhuels on 4/8/20.
//

#ifndef SHEAREDSLITPOREBD_ARGUMENTS_H
#define SHEAREDSLITPOREBD_ARGUMENTS_H

#include "../defaults.h"
#include <iostream>

using namespace std;

class ARGUMENTS{
public:
    unsigned int seed = 0;
    
    string configurationIn = CONFIGURATION_IN;

    double shearRate = SHEAR_RATE;
    double amplitude = AMPLITUDE;
    double oscillationPeriod = OSCILLATION_PERIOD;

    double dt = DELTA_T;
    double temperature = TEMPERATURE;
    double D0 = DIFFUSION_CONSTANT;

    double ssInteractionStrength = SS_INTERACTION_STRENGTH;
    double wallInteractionStrength = WALL_INTERACTION_STRENGTH;

    int totalNumberOfTimesteps = TOTAL_NUMBER_OF_TIMESTEPS;
    
    int printVelocity = PRINT_VELOCITY;
    int printStress = PRINT_STRESS;
    int stressFourier = STRESS_FOURIER;
    int printEnergy = PRINT_ENERGY;
    int printAngularBond = PRINT_ANGULAR_BOND;
    int printAll = PRINT_ALL;
    bool clear = CLEAR;
    
    bool dryRun = false;
    bool printVersion = false;

    int snapshotInterval = SNAPSHOT_INTERVAL;

    void print();

    //void readFromFile(string filename);
    //ARGUMENTS(string filename);
};


#endif //SHEAREDSLITPOREBD_ARGUMENTS_H
