 
#include "particle_angular_bond.h"

PARTICLE_ANGULAR_BOND::PARTICLE_ANGULAR_BOND(){
}

PARTICLE_ANGULAR_BOND::PARTICLE_ANGULAR_BOND(CONFINED_BROWNIAN_PARTICLES& sys){
    setup(sys);
}

PARTICLE_ANGULAR_BOND& PARTICLE_ANGULAR_BOND::setup(CONFINED_BROWNIAN_PARTICLES& sys){
    numberOfParticles = sys.getParticleList().size();
    angularBond4.assign(numberOfParticles, double(0.));
    angularBond6.assign(numberOfParticles, double(0.));
    //nearestNeighbors.assign(numberOfParticles, double(0.));
    return *this;
}

PARTICLE_ANGULAR_BOND& PARTICLE_ANGULAR_BOND::calculateParticleAngularBond(CONFINED_BROWNIAN_PARTICLES& sys){
    ANGULAR_BOND_PARAMETER ABP(sys,4);
    NNRadius=ABP.getNextNeighborShellRadius();
    for(int j = 0; j < numberOfParticles; j++){
        ABP.setN(4);
        angularBond4[j]=ABP.calculateForSingleParticle(j);
        ABP.setN(6);
        angularBond6[j]=ABP.calculateForSingleParticle(j);
        //nearestNeighbors[j]=ABP.getNearestNeighborIndices(j).size();

    }
    return *this;
}