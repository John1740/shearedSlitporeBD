#include "shear_force.h"

SHEAR_FORCE::SHEAR_FORCE(){
    direction = REAL_C(1., 0., 0.);
}

SHEAR_FORCE::SHEAR_FORCE(double shearRate) {
    this->shearRate = shearRate;
    direction = REAL_C(1., 0., 0.);
}

SHEAR_FORCE::SHEAR_FORCE(double shearRate, const REAL_C& direction) {
    this->shearRate = shearRate;
    setDirection(direction);
}

void SHEAR_FORCE::setDirection(const REAL_C& directionIn){
    double abs = directionIn.abs();
    direction = directionIn / abs;
}

REAL_C SHEAR_FORCE::forceOnParticle(PARTICLE& particle){
    REAL_C forceOnParticle = shearRate * direction * particle.boxPosition.z;
    return forceOnParticle;
}

REAL_C SHEAR_FORCE::getDirection(){
    return direction;
}

