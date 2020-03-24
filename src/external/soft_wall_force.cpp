#include "soft_wall_force.h"

SOFT_WALL_FORCE::SOFT_WALL_FORCE()
{
   wallInteractionStrength =  1.;
   zPosition = 0.;
   diameter = 1.;
   dWall = 1.;
}

void SOFT_WALL_FORCE::setInteractionParameters( double dWallIN, double wallInteractionStrengthIN )
{
   dWall = dWallIN;
   wallInteractionStrength = wallInteractionStrengthIN;
}

double SOFT_WALL_FORCE::energyOnParticle( PARTICLE &particle )
{
   zPosition = particle.boxPosition.z;
   diameter = 0.5 * ( 1. + particle.diameter );
//   cout << diameter << endl;
   return ( 4 * M_PI / 5 ) * wallInteractionStrength * ( pow( diameter / ( dWall / 2 - zPosition ), 9 ) + pow( diameter / ( dWall / 2 + zPosition ), 9 ) );
}

CARTESIAN_COORDINATE SOFT_WALL_FORCE::forceOnParticle( PARTICLE &particle )
{
   zPosition = particle.boxPosition.z;
   diameter = particle.diameter;
   CARTESIAN_COORDINATE force( 0., 0., forceInZDirection( zPosition, diameter ) );
   return force;
}

double SOFT_WALL_FORCE::forceInZDirection( double zPositionIn, double diameterIn )
{
   diameterIn = 0.5 * ( 1. + diameterIn );
   return  - ( 4 * 9 * M_PI / 5 ) * wallInteractionStrength * ( pow( diameterIn / ( dWall / 2 - zPositionIn ), 10 ) -  pow( diameterIn / ( dWall / 2 + zPositionIn ), 10 ) ) / diameterIn;
}



