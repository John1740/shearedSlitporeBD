#ifndef SOFT_WALL_FORCE_H
#define SOFT_WALL_FORCE_H

#include "../interfaces/force_template_interfaces.h"
#include "../struct/particle.h"
#include "../struct/cartesian_coordinate.h"

class SOFT_WALL_FORCE: public CONSERVATIVE_FORCE<PARTICLE>
{

public:
   double wallInteractionStrength;
   double zPosition;
   double diameter;
   double dWall;

   SOFT_WALL_FORCE();

   void setInteractionParameters ( double dWallIN, double wallInteractionStrengthIN );

   CARTESIAN_COORDINATE forceOnParticle ( PARTICLE& particle );
   double energyOnParticle ( PARTICLE& particle );

   double forceInZDirection ( double zPositionIn, double diameterIn );

};

#endif // SOFT_WALL_FORCE_H
