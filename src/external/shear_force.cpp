#include "shear_force.h"

template<class SHEAR_PROTOCOL_T>
SHEAR_FORCE<SHEAR_PROTOCOL_T>::SHEAR_FORCE(){
    direction = REAL_C(1., 0., 0.);
}

template<class SHEAR_PROTOCOL_T>
SHEAR_FORCE<SHEAR_PROTOCOL_T>::SHEAR_FORCE(const SHEAR_PROTOCOL_T& shearProtocol){
    this->shearProtocol = shearProtocol;
    direction = REAL_C(1., 0., 0.);
}

template<class SHEAR_PROTOCOL_T>
SHEAR_FORCE<SHEAR_PROTOCOL_T>::SHEAR_FORCE(const SHEAR_PROTOCOL_T& shearProtocol, const REAL_C& direction){
    this->shearProtocol = shearProtocol;
    setDirection(direction);
}

template<class SHEAR_PROTOCOL_T>
void SHEAR_FORCE<SHEAR_PROTOCOL_T>::setDirection(const REAL_C& directionIn){
    double abs = directionIn.abs();
    direction = directionIn / abs;
}

template<class SHEAR_PROTOCOL_T>
REAL_C SHEAR_FORCE<SHEAR_PROTOCOL_T>::getDirection(){
    return direction;
}

template<class SHEAR_PROTOCOL_T>
REAL_C SHEAR_FORCE<SHEAR_PROTOCOL_T>::forceOnParticle(PARTICLE& particle, double t){
    REAL_C forceOnParticle = forceAbs(particle.boxPosition.z, t) * direction;
    return forceOnParticle;
}

template<class SHEAR_PROTOCOL_T>
double SHEAR_FORCE<SHEAR_PROTOCOL_T>::forceAbs(double z, double t) const{
    double shearRate = shearProtocol.calculateShearRate(t);
    double force = shearRate * z;
    return force;
}

