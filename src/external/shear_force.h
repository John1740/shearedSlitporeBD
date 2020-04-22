#ifndef SHEAR_FORCE_H
#define SHEAR_FORCE_H

#include "../interfaces/force_template_interfaces.h"
#include "../struct/particle.h"
#include "../struct/cartesian_coordinate.h"
#include "../defaults.h"

class SHEAR_FORCE:  FORCE<PARTICLE>{
private:
    CARTESIAN_COORDINATE direction;
public:
    double shearRate = SHEAR_RATE;

    SHEAR_FORCE();
    SHEAR_FORCE(double shearRate);
    SHEAR_FORCE(double shearRate, const CARTESIAN_COORDINATE& direction);

    //setter functions
    void setDirection(const CARTESIAN_COORDINATE& directionIn);

    //getter functions
    CARTESIAN_COORDINATE getDirection();

    CARTESIAN_COORDINATE forceOnParticle(PARTICLE& particle);
};

#endif // SHEAR_FORCE_H
