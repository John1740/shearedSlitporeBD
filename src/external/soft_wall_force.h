#ifndef SOFT_WALL_FORCE_H
#define SOFT_WALL_FORCE_H

#include "../interfaces/force_template_interfaces.h"
#include "../struct/particle.h"
#include "../defaults.h"

class SOFT_WALL_FORCE: public CONSERVATIVE_FORCE<PARTICLE>{
private:

public:
    double wallInteractionStrength = WALL_INTERACTION_STRENGTH;
    double zPosition = 0.;
    double dWall = D_WALL;

    //constructors
    SOFT_WALL_FORCE();
    SOFT_WALL_FORCE(double wallInteractionStrength, double dWall);

    REAL_C forceOnParticle(PARTICLE& particle);
    double energyOnParticle(PARTICLE& particle);

    double forceInZDirection(double zPositionIn, double diameterIn);

};

#endif // SOFT_WALL_FORCE_H
