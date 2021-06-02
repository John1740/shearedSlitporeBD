#ifndef SHEAR_FORCE_H
#define SHEAR_FORCE_H

#include "../interfaces/force_template_interfaces.h"
#include "../struct/particle.h"
#include "../struct/cartesian_c.h"
#include "../defaults.h"
#include "../interfaces/shear_protocol.h"

template<class SHEAR_PROTOCOL_T>
class SHEAR_FORCE: TIME_DEPENDENT_FORCE<PARTICLE>{
private:
    REAL_C direction;
public:
    SHEAR_PROTOCOL_T shearProtocol;

    SHEAR_FORCE();
    SHEAR_FORCE(const SHEAR_PROTOCOL_T& shearProtocol);
    SHEAR_FORCE(const SHEAR_PROTOCOL_T& shearProtocol, const REAL_C& direction);

    //setter functions
    void setDirection(const REAL_C& directionIn);

    //getter functions
    REAL_C getDirection();

    ////////////////////////////////////////// Calculators ///////////////////////////////////////////
    REAL_C forceOnParticle(PARTICLE& particle, double t) override;

    [[nodiscard]] double forceAbs(double z, double t) const;
};

#endif // SHEAR_FORCE_H
