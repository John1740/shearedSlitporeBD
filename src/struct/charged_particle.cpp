#include "charged_particle.h"

CHARGED_PARTICLE::CHARGED_PARTICLE()
{
   species = 0;
   position = CARTESIAN_COORDINATE();
   boxPosition = CARTESIAN_COORDINATE();
   setChargeAndDiameter( 1, 1. );
}

CHARGED_PARTICLE::CHARGED_PARTICLE( const CARTESIAN_COORDINATE &positionIN )
{
   species = 0;
   position = positionIN;
   boxPosition = CARTESIAN_COORDINATE();
   setChargeAndDiameter( 1, 1. );
}


CHARGED_PARTICLE::CHARGED_PARTICLE( const CHARGED_PARTICLE &other )
{
   species = other.species;
   position = other.position;
   boxPosition = other.boxPosition;
   setChargeAndDiameter( other.charge, other.diameter );;
}

void CHARGED_PARTICLE::setChargeAndDiameter( int chargeIN, double diameterIN )
{
   charge = chargeIN;
   diameter = diameterIN;
}


