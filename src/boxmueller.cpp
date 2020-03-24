/*
 * boxmueller.cpp
 *
 *  Created on: Jul 10, 2012
 *  Author: Tarlan Vezirov
 */
#include "boxmueller.h"
#include "randomc.h"
extern CRandomMersenne random_event;


double  boxmueller( double  mu, double  sigma )
{
   const double pi = 3.14159;
   double  u1, u2;
   double  random_variable;
   u1 = 1 - random_event.Random();
   u2 = 1 - random_event.Random();
   random_variable = mu + sigma * sqrt( -2 * log( u1 ) ) * cos( 2 * pi * u2 );
   return random_variable;
}



