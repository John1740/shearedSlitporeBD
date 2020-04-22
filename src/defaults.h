//
// Created by mhuels on 4/7/20.
//

#ifndef SHEAREDSLITPOREBD_DEFAULTS_H
#define SHEAREDSLITPOREBD_DEFAULTS_H

#include <string>

const std::string CONFIGURATION_IN = "configuration.in";

const double SHEAR_RATE = 0.0;

const double D_WALL = 2.2;
const double DENSITY = 0.85;

const int NUMBER_OF_PARTICLES = 1058;
const int CHARGE = 35;
const double DIAMETER = 1.;

const double SS_INTERACTION_STRENGTH = 1.0;
const double WALL_INTERACTION_STRENGTH = 1.0;

const double DELTA_T = 1e-5;
const double TEMPERATURE = 1.0;
const double DIFFUSION_CONSTANT = 1.0;

const int TOTAL_NUMBER_OF_TIMESTEPS = 10;

const int PRINT_STRESS = 0;
const int PRINT_ENERGY = 0;
const int SNAPSHOT_INTERVAL = 0;

#endif //SHEAREDSLITPOREBD_DEFAULTS_H
