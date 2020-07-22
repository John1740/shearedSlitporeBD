#ifndef SHEAR_FORCE_H
#define SHEAR_FORCE_H

#include "../interfaces/force_template_interfaces.h"
#include "../struct/particle.h"
#include "../struct/real_coordinate.h"
#include "../defaults.h"

class SHEAR_FORCE:  FORCE<PARTICLE>{
private:
    REAL_C direction;
public:
    double shearRate = SHEAR_RATE;

    SHEAR_FORCE();
    SHEAR_FORCE(double shearRate);
    SHEAR_FORCE(double shearRate, const REAL_C& direction);

    //setter functions
    void setDirection(const REAL_C& directionIn);

    //getter functions
    REAL_C getDirection();

    REAL_C forceOnParticle(PARTICLE& particle);
};

#endif // SHEAR_FORCE_H
