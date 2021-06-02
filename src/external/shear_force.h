#ifndef SHEAR_FORCE_H
#define SHEAR_FORCE_H

#include "../interfaces/force_template_interfaces.h"
#include "../struct/particle.h"
#include "../struct/cartesian_c.h"
#include "../defaults.h"
//#include "../interfaces/shear_protocol.h"
#include "oscillatory_shear.h"

class SHEAR_FORCE: TIME_DEPENDENT_FORCE<PARTICLE>{
private:
    REAL_C direction;
public:
    OSCILLATORY_SHEAR shearProtocol;

    SHEAR_FORCE();
    SHEAR_FORCE(const OSCILLATORY_SHEAR& shearProtocol);
    SHEAR_FORCE(const OSCILLATORY_SHEAR& shearProtocol, const REAL_C& direction);

    //setter functions
    void setDirection(const REAL_C& directionIn);

    //getter functions
    REAL_C getDirection();

    ////////////////////////////////////////// Calculators ///////////////////////////////////////////
    REAL_C forceOnParticle(PARTICLE& particle, double t) override;

    double forceAbs(double z, double t);
};

#endif // SHEAR_FORCE_H
