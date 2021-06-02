#include "soft_wall_force.h"
#include <boost/format.hpp>

namespace bo = boost;

SOFT_WALL_FORCE::SOFT_WALL_FORCE(){
}

SOFT_WALL_FORCE::SOFT_WALL_FORCE(double wallInteractionStrength, double dWall){
    this->wallInteractionStrength = wallInteractionStrength;
    this->dWall = dWall;
}

double SOFT_WALL_FORCE::energyOnParticle(PARTICLE& particle){
    zPosition = particle.boxPosition.z;
    double diameter = 0.5 * (1. + particle.diameter);
//   cout << diameter << endl;
    return (4 * M_PI / 5) * wallInteractionStrength *
           (pow(diameter / (dWall / 2 - zPosition), 9) + pow(diameter / (dWall / 2 + zPosition), 9));
}

REAL_C SOFT_WALL_FORCE::forceOnParticle(PARTICLE& particle){
    zPosition = particle.boxPosition.z;
    REAL_C forceOnParticle;
    forceOnParticle.z = forceInZDirection(zPosition, particle.diameter);
    return forceOnParticle;
}

double SOFT_WALL_FORCE::forceInZDirection(double zPositionIn, double diameterIn){
    diameterIn = 0.5 * (1. + diameterIn);   //?
    double prefactor = -(4 * 9 * M_PI / 5) * wallInteractionStrength / diameterIn;
    double forceZ = prefactor *
                    (pow(diameterIn / (dWall / 2 - zPositionIn), 10) - pow(diameterIn / (dWall / 2 + zPositionIn), 10));
    return forceZ;
}

ostream& operator<<(ostream& os, const SOFT_WALL_FORCE& swf){
    const char* fmt = "% .8f\t";
    os << "wallInteractionStrength: " << bo::format(fmt) % swf.wallInteractionStrength << "[kT]" << endl;
    os << "dWall: " << bo::format(fmt) % swf.dWall << "[d]";
    return os;
}