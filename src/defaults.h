//
// Created by mhuels on 4/7/20.
//

#ifndef SHEAREDSLITPOREBD_DEFAULTS_H
#define SHEAREDSLITPOREBD_DEFAULTS_H

#include <string>

const std::string CONFIGURATION_IN = "configuration.in";
const std::string CONFIGURATION_OUT = "configuration.out";
const std::string ANGULAR_BOND_OUT = "angularBond.out";
const std::string PAIR_CORRELATIONS_OUT = "pairCorrelations";
const std::string STRESSES_OUT = "stresses.out";
const std::string VELOCITIES_OUT = "velocities.out";
const std::string SNAPSHOTS = "snapshots.out";

const double SHEAR_RATE = 0.0;
const double AMPLITUDE = 0.0;
const double OSCILLATION_PERIOD = 1.0;
const double PHASE_OFFSET = 0.0;

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

const int PRINT_VELOCITY = 0;
const int PRINT_STRESS = 0;
const int PRINT_STRESS_FOURIER = 0;
const int PRINT_ENERGY = 0;
const int PRINT_ANGULAR_BOND = 0;
const int PRINT_SNAPSHOTS = 0;
const int PRINT_PAIR_CORRELATION = 0;
const int PRINT_ALL = 0;
const bool CLEAR = false;

#endif //SHEAREDSLITPOREBD_DEFAULTS_H
