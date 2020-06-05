//
// Created by mhuels on 5/25/20.
//

#ifndef SHEAREDSLITPOREBD_ANGULAR_BOND_PARAMETER_H
#define SHEAREDSLITPOREBD_ANGULAR_BOND_PARAMETER_H

#include "../systems/confined_brownian_particles.h"
#include "../struct/layers.h"
#include "intra_layer_pair_correlation_function.h"

class ANGULAR_BOND_PARAMETER{
private:
    vector<CHARGED_PARTICLE> particle;
    SLIT_PORE_BOX simBox;
    LAYERS layers;
    INTRA_LAYER_PAIR_CORRELATION_FUNCTION pairCorrelation;
    
    int n;  //integer of angular bond symmetry
    double nextNeighborShellRadius;
    
    double angleBetweenParticles(const PARTICLE& particle1, const PARTICLE& particle2);
    vector<int> getNeighborIndices(int i);
    
    //warnings
    vector<int> isolatedParticles;
    
public:
    ANGULAR_BOND_PARAMETER();
    ANGULAR_BOND_PARAMETER(CONFINED_BROWNIAN_PARTICLES& sysIn);
    ANGULAR_BOND_PARAMETER(CONFINED_BROWNIAN_PARTICLES& sysIn, int n);
    
    ANGULAR_BOND_PARAMETER& setup(CONFINED_BROWNIAN_PARTICLES& sysIn);
    
    double calculateForSingleParticle(int i);
    double calculateAverageOverAllParticles();
    double calculateNextNeighborShellRadius();
    
    //setter
    ANGULAR_BOND_PARAMETER& setN(int n);
    
    //getter
    int getN() const;
    double getNextNeighborShellRadius() const;
    INTRA_LAYER_PAIR_CORRELATION_FUNCTION getPairCorrelation() const;
    vector<int> getIsolatedParticles() const;
};


#endif //SHEAREDSLITPOREBD_ANGULAR_BOND_PARAMETER_H
