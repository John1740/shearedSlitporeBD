#include "shear_force.h"

SHEAR_FORCE::SHEAR_FORCE(){
    direction = REAL_C(1., 0., 0.);
}

SHEAR_FORCE::SHEAR_FORCE(const SHEAR_PROTOCOL& shearProtocol){
    this->shearProtocol = shearProtocol;
    direction = REAL_C(1., 0., 0.);
}

SHEAR_FORCE::SHEAR_FORCE(const SHEAR_PROTOCOL& shearProtocol, const REAL_C& direction){
    this->shearProtocol = shearProtocol;
    setDirection(direction);
}

void SHEAR_FORCE::setDirection(const REAL_C& directionIn){
    double abs = directionIn.abs();
    direction = directionIn / abs;
}

REAL_C SHEAR_FORCE::getDirection(){
    return direction;
}

REAL_C SHEAR_FORCE::forceOnParticle(PARTICLE& particle, double t){
    REAL_C forceOnParticle = forceAbs(particle.boxPosition.z, t) * direction;
    return forceOnParticle;
}

double SHEAR_FORCE::forceAbs(double z, double t) {
    double shearRate = shearProtocol.calculateShearRate(t);
    double force = shearRate * z;
    return force;
}

