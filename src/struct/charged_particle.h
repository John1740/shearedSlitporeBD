#ifndef CHARGED_PARTICLE_H
#define CHARGED_PARTICLE_H

#include "particle.h"

class CHARGED_PARTICLE : public PARTICLE
{

public:
   int charge;

   CHARGED_PARTICLE();
   CHARGED_PARTICLE ( const CARTESIAN_COORDINATE& positionIN );
   CHARGED_PARTICLE ( const CHARGED_PARTICLE& other );

   void setChargeAndDiameter ( int chargeIN, double diameterIN );
};

#endif // CHARGED_PARTICLE_H
