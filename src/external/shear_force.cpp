#include "shear_force.h"

SHEAR_FORCE::SHEAR_FORCE()
{
    setDirection( CARTESIAN_COORDINATE(1.,0.,0.) );
    setShearRate( 0. );
}

void SHEAR_FORCE::setDirection ( CARTESIAN_COORDINATE directionIn )
{
    double abs = directionIn.getAbs();
    direction = directionIn / abs;
}

void SHEAR_FORCE::setShearRate ( double shearRateIn )
{
    shearRate = shearRateIn;
}

CARTESIAN_COORDINATE SHEAR_FORCE::forceOnParticle ( PARTICLE& particle )
{
    return shearRate * direction * particle.position.z;
}

CARTESIAN_COORDINATE SHEAR_FORCE::getDirection()
{
    return direction;
}

double SHEAR_FORCE::getShearRate()
{
    return shearRate;
}
