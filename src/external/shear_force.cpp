#include "shear_force.h"

SHEAR_FORCE::SHEAR_FORCE(){
    direction = CARTESIAN_COORDINATE(1.,0.,0.);
}

SHEAR_FORCE::SHEAR_FORCE(double shearRate) {
    this->shearRate = shearRate;
    direction = CARTESIAN_COORDINATE(1., 0., 0.);
}

SHEAR_FORCE::SHEAR_FORCE(double shearRate, const CARTESIAN_COORDINATE& direction) {
    this->shearRate = shearRate;
    setDirection(direction);
}

void SHEAR_FORCE::setDirection(const CARTESIAN_COORDINATE& directionIn){
    double abs = directionIn.getAbs();
    direction = directionIn / abs;
}

CARTESIAN_COORDINATE SHEAR_FORCE::forceOnParticle(PARTICLE& particle){
    CARTESIAN_COORDINATE forceOnParticle = shearRate * direction * particle.position.z;
    return forceOnParticle;
}

CARTESIAN_COORDINATE SHEAR_FORCE::getDirection(){
    return direction;
}

