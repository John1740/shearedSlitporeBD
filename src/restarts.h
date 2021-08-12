//
// Created by mhuelsberg on 30.07.21.
//

#ifndef SHEAREDSLITPOREBD_RESTARTS_H
#define SHEAREDSLITPOREBD_RESTARTS_H

#include "systems/confined_brownian_particles.h"
#include "tools/clock.h"
using namespace std;

bool restartFromConfiguration(string filename, CONFINED_BROWNIAN_PARTICLES& sys, long timestepIn, long numberOfTimesteps, bool verbose=true);

bool restartSimulation(CONFINED_BROWNIAN_PARTICLES& sys, long numberOfTimesteps, bool verbose=true);

void saveMilestone(CONFINED_BROWNIAN_PARTICLES& sys, bool verbose=false);

#endif //SHEAREDSLITPOREBD_RESTARTS_H
