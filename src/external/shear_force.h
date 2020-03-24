#ifndef SHEAR_FORCE_H
#define SHEAR_FORCE_H

#include "../interfaces/force_template_interfaces.h"
#include "../struct/particle.h"
#include "../struct/cartesian_coordinate.h"

class SHEAR_FORCE :  FORCE<PARTICLE>
{
    double shearRate;
    CARTESIAN_COORDINATE direction;

public:
    SHEAR_FORCE();
    void setDirection( CARTESIAN_COORDINATE directionIn );
    void setShearRate( double shearRateIn );
    
    CARTESIAN_COORDINATE forceOnParticle ( PARTICLE& particle );
    
    double getShearRate();
    CARTESIAN_COORDINATE getDirection();
};

#endif // SHEAR_FORCE_H
