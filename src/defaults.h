//
// Created by mhuels on 4/7/20.
//

#ifndef SHEAREDSLITPOREBD_DEFAULTS_H
#define SHEAREDSLITPOREBD_DEFAULTS_H

#include <string>

//nature constants
const double e0 = 1.602176634e-19;        //unit: C
const double NA = 6.02214076e23;          //unit: mol^-1
const double eps0 = 8.8541878128e-12;     //unit: F m^-1 = C^2 J^-1 m^-1
const double kB = 1.38064852e-23;         //unit: J K^-1

//filenames
const std::string SETTINGS_IN = "settings.in";
const std::string CONFIGURATION_IN = "configuration.in";
const std::string CONFIGURATION_OUT = "configuration.out";
const std::string CONFIGURATION_RESTART = "configuration.restart";
const std::string CONFIGURATION_SKIPPED = "configuration.skipped";
const std::string BACKUP_EXTENSION = ".bak";
const std::string ANGULAR_BOND_OUT = "angularBond.out";
const std::string PAIR_CORRELATION_OUT = "pairCorrelation.out";
const std::string STRESSES_OUT = "stresses.out";
const std::string LAYER_POSITIONS_OUT = "layerPositions.out";
const std::string LAYER_VELOCITIES_OUT = "layerVelocities.out";
const std::string SNAPSHOTS = "snapshots.out";
const std::string ERRONEOUS = "erroneous";

//control parameters
const double SHEAR_RATE = 0.0;
const double AMPLITUDE = 0.0;
const double OSCILLATION_PERIOD = 1.0;
const double PHASE_OFFSET = 0.0;

const double D_WALL = 2.2;
const double DENSITY = 0.85;
const int CHARGE = 35;

//numerical parameters
const int NUMBER_OF_PARTICLES = 1058;
const double DIAMETER = 1.;

//interaction parameters
const double SS_INTERACTION_STRENGTH = 1.0;
const double Y_INTERACTION_STRENGTH = 1.23365892e+02;
//const double Y_INTERACTION_STRENGTH = 123.36619402569552;
const double KAPPA = 3.21623656e+00;
//const double KAPPA = 3.2162381150765986;
const double WALL_INTERACTION_STRENGTH = 1.0;

const double KT = 1.0;
const double MU = 1.0;

//intervals
const long NUMBER_OF_TIMESTEPS = 10;
const int SKIP = 0;
const int MILESTONE = 0;
const double MILESTONE_RUNTIME = 600;   //10min
const double MILESTONE_RUNTIME_OFFSET = -1;
const double WATCHDOG = 0;
const double WATCHDOG_OFFSET = 120;   //2min
const int PRINT_LAYER_POSITION = 0;
const int PRINT_LAYER_VELOCITY = 0;
const int PRINT_STRESS = 0;
const int PRINT_STRESS_FOURIER = 0;
const int PRINT_ENERGY = 0;
const int PRINT_ANGULAR_BOND = 0;
const int PRINT_SNAPSHOTS = 0;
const int PRINT_PAIR_CORRELATION = 0;
const int PRINT_ALL = 0;

//misc
const bool CLEAR = false;
const bool RESTART = false;

#endif //SHEAREDSLITPOREBD_DEFAULTS_H
