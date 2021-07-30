//
// Created by mhuelsberg on 30.07.21.
//

#ifndef SHEAREDSLITPOREBD_RESTARTS_H
#define SHEAREDSLITPOREBD_RESTARTS_H

#include "systems/confined_brownian_particles.h"
using namespace std;

long restartFromConfiguration(string filename, CONFINED_BROWNIAN_PARTICLES& sys, long numberOfTimesteps, bool verbose=true);

long restartSimulation(CONFINED_BROWNIAN_PARTICLES& sys, long numberOfTimesteps, bool verbose=true);

#endif //SHEAREDSLITPOREBD_RESTARTS_H
