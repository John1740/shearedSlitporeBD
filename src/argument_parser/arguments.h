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
    double shearRate = SHEAR_RATE;

    double dWall = D_WALL;
    double density = DENSITY;
    int numberOfParticles = NUMBER_OF_PARTICLES;

    int charge = CHARGE;
    double diameter = DIAMETER;

    double dt = DELTA_T;
    double temperature = TEMPERATURE;
    double D0 = DIFFUSION_CONSTANT;

    double ssInteractionStrength = SS_INTERACTION_STRENGTH;
    double wallInteractionStrength = WALL_INTERACTION_STRENGTH;

    bool printStress = PRINT_STRESS;
    bool printEnergy = PRINT_ENERGY;

    bool dryRun = false;
    bool printVersion = false;

    void print();

    //void readFromFile(string filename);
    //ARGUMENTS(string filename);
};


#endif //SHEAREDSLITPOREBD_ARGUMENTS_H
