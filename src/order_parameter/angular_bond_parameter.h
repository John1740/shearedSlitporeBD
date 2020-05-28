//
// Created by mhuels on 5/25/20.
//

#ifndef SHEAREDSLITPOREBD_ANGULAR_BOND_PARAMETER_H
#define SHEAREDSLITPOREBD_ANGULAR_BOND_PARAMETER_H

#include "../systems/confined_brownian_particles.h"
#include "../struct/layers.h"
#include "pair_correlation.h"

class ANGULAR_BOND_PARAMETER{
private:
    vector<CHARGED_PARTICLE> particle;
    SLIT_PORE_BOX simBox;
    LAYERS layers;
    PAIR_CORRELATION pairCorrelation;
    
    int n;  //integer of angular bond symmetry
    double cutoffRadius;
    
    double angleBetweenParticles(const PARTICLE& particle1, const PARTICLE& particle2);
    
    //warnings
    vector<int> erroneousParticles;
    
public:
    ANGULAR_BOND_PARAMETER();
    ANGULAR_BOND_PARAMETER(CONFINED_BROWNIAN_PARTICLES& sysIn);
    ANGULAR_BOND_PARAMETER(CONFINED_BROWNIAN_PARTICLES& sysIn, int n);
    
    ANGULAR_BOND_PARAMETER& setup(CONFINED_BROWNIAN_PARTICLES& sysIn);
    
    double calculateForSingleParticle(int i);
    double calculateAverageOverAllParticles();
    double calculateCutoffRadius();
    
    //setter
    ANGULAR_BOND_PARAMETER& setN(int n);
    
    //getter
    int getN() const;
    double getCutoffRadius() const;
    PAIR_CORRELATION getPairCorrelation() const;
    vector<int> getErroneousParticles() const;
};


#endif //SHEAREDSLITPOREBD_ANGULAR_BOND_PARAMETER_H
