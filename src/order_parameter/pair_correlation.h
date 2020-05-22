//
// Created by mhuels on 5/20/20.
//

#ifndef SHEAREDSLITPOREBD_PAIR_CORRELATION_H
#define SHEAREDSLITPOREBD_PAIR_CORRELATION_H

#include "../struct/layers.h"
#include "../systems/confined_brownian_particles.h"

class PAIR_CORRELATION{
private:
    LAYERS layers;
    SLIT_PORE_BOX simBox;
    vector<CHARGED_PARTICLE> particle;
    double maximalRadius;
    double dr;
    int length;
    vector<double> radius;
    vector<double> correlationFunction;
public:
    PAIR_CORRELATION();
    PAIR_CORRELATION(CONFINED_BROWNIAN_PARTICLES& sys);
    PAIR_CORRELATION(CONFINED_BROWNIAN_PARTICLES& sys, double dr);
    
    void setup(CONFINED_BROWNIAN_PARTICLES& sys, double dr);
    
    void calculate();
    
    //getter
    vector<double> getRadii() const;
    vector<double> getPairCorrelations() const;
    
    //setter
    void setResolution(double dr);
    
    //printer
    void print(string filename);
    friend ostream& operator<<(ostream& os, const PAIR_CORRELATION& pairCorrelation);
};

#endif //SHEAREDSLITPOREBD_PAIR_CORRELATION_H
