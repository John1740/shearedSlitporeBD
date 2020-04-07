//
// Created by mhuels on 4/7/20.
//

#ifndef SHEAREDSLITPOREBD_ARGPARSE_H
#define SHEAREDSLITPOREBD_ARGPARSE_H

#include "boost/program_options.hpp"
#include "../defaults.h"

namespace po = boost::program_options;
using namespace std;

class ARGUMENTS{
public:
    double shearRate = SHEAR_RATE;
    double dWall = D_WALL;
    double density = DENSITY;
    int numberOfParticles = NUMBER_OF_PARTICLES;
    int charge = CHARGE;
    double diameter = DIAMETER;
    double ssInteractionStrength = SS_INTERACTION_STRENGTH;
    double wallInteractionStrength = WALL_INTERACTION_STRENGTH;
    double dt = DELTA_T;
    double temperature = TEMPERATURE;
    bool printStress = PRINT_STRESS;
    bool printEnergy = PRINT_ENERGY;
};

class ARGUMENT_PARSER{
private:
    po::options_description description{"Options"};
    po::variables_map variablesMap;
    void addOptions();
public:
    ARGUMENT_PARSER(int argc, const char* argv[]);

    ARGUMENTS parseArgs();

    //add option to read from config-file
};

#endif //SHEAREDSLITPOREBD_ARGPARSE_H
