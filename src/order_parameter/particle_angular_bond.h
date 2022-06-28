#ifndef SHEAREDSLITPOREBD_PARTICLE_ANGULAR_BOND_H
#define SHEAREDSLITPOREBD_PARTICLE_ANGULAR_BOND_H

//#include "printer.h"
#include "../systems/sheared_slitpore_system.h"
#include "../order_parameter/angular_bond_parameter.h"

class PARTICLE_ANGULAR_BOND{
private:
    int numberOfParticles;


public:
    double NNRadius;
    vector<double> angularBond4;
    vector<double> angularBond6;
    //vector<double> nearestNeighbors;
    PARTICLE_ANGULAR_BOND();
    PARTICLE_ANGULAR_BOND(CONFINED_BROWNIAN_PARTICLES& sysIn);
    PARTICLE_ANGULAR_BOND& setup(CONFINED_BROWNIAN_PARTICLES& sysIn);
    PARTICLE_ANGULAR_BOND& calculateParticleAngularBond(CONFINED_BROWNIAN_PARTICLES& sysIn);
};

#endif //SHEAREDSLITPOREBD_PARTICLE_ANGULAR_BOND_H
