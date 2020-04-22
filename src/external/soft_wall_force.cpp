#include "soft_wall_force.h"

SOFT_WALL_FORCE::SOFT_WALL_FORCE(){
}

SOFT_WALL_FORCE::SOFT_WALL_FORCE(const ARGUMENTS &args) {
    wallInteractionStrength = args.wallInteractionStrength;
    diameter = args.diameter;
    dWall = args.dWall;
}

double SOFT_WALL_FORCE::energyOnParticle(PARTICLE &particle){
    zPosition = particle.boxPosition.z;
    diameter = 0.5 * (1. + particle.diameter);
//   cout << diameter << endl;
    return (4 * M_PI / 5) * wallInteractionStrength * (pow(diameter / (dWall / 2 - zPosition), 9) + pow(diameter / (dWall / 2 + zPosition), 9));
}

CARTESIAN_COORDINATE SOFT_WALL_FORCE::forceOnParticle(PARTICLE &particle){
    zPosition = particle.boxPosition.z;
    diameter = particle.diameter;
    CARTESIAN_COORDINATE forceOnParticle;
    forceOnParticle.z = forceInZDirection(zPosition, diameter);
    return forceOnParticle;
}

double SOFT_WALL_FORCE::forceInZDirection(double zPositionIn, double diameterIn){
    diameterIn = 0.5 * (1. + diameterIn);   //?
    double prefactor = - (4 * 9 * M_PI / 5) * wallInteractionStrength / diameterIn;
    double forceZ = prefactor * (pow(diameterIn / (dWall / 2 - zPositionIn), 10) -  pow(diameterIn / (dWall / 2 + zPositionIn), 10));
    return forceZ;
}

