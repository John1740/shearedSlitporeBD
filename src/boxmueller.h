/*
 * boxmueller.h
 *
 *  Created on: Jul 10, 2012
 *  Author: Tarlan Vezirov
 */
#ifndef  boxmueller_h
#define  boxmueller_h

#include <cmath>
#include "randomc.h"
extern CRandomMersenne random_event;

double boxmueller(double mu, double sigma);
void initSeed (unsigned int seed);

#endif

