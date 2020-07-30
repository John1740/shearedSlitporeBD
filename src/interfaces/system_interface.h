#ifndef SYSTEM_INTERFACE_H
#define SYSTEM_INTERFACE_H

#include "../struct/cartesian_c.h"
#include "../struct/cartesian_matrix.h"
#include "../interfaces/box_geometry.h"
#include "../struct/charged_particle.h"

class SYSTEM_INTERFACE{
public:
    virtual void calculateInteractionForce(int i, int j)  = 0;
    virtual void calculateExternalForce(int i) = 0;

    virtual BOX_GEOMETRY* simulationBox() = 0;
    virtual double getInteractionLengthScale() = 0;

    virtual vector<REAL_C> getPositionList() = 0;
    virtual vector<CHARGED_PARTICLE> getParticleList() = 0;
};

#endif // SYSTEM_INTERFACE_H
