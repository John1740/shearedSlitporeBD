//
// Created by mhuels on 5/20/20.
//

#ifndef SHEAREDSLITPOREBD_INTRA_LAYER_PAIR_CORRELATION_FUNCTION_H
#define SHEAREDSLITPOREBD_INTRA_LAYER_PAIR_CORRELATION_FUNCTION_H

#include "../struct/layers.h"
#include "../systems/confined_brownian_particles.h"

class INTRA_LAYER_PAIR_CORRELATION_FUNCTION{
private:
    LAYERS layers;
    SLIT_PORE_BOX simBox;
    vector<CHARGED_PARTICLE> particle;
    double maximalRadius;
    double dr;
    int length;
    vector<double> radius;
    vector<double> correlationFunction;
    
    int findNextUpCrossing(int pos, double threshold, int averageRange);
    int findNextDownCrossing(int pos, double threshold, int averageRange);
    int findLastUpCrossing(int pos, double threshold, int posMax);
    int findLastDownCrossing(int pos, double threshold, int posMax);
public:
    INTRA_LAYER_PAIR_CORRELATION_FUNCTION();
    INTRA_LAYER_PAIR_CORRELATION_FUNCTION(CONFINED_BROWNIAN_PARTICLES& sys);
    INTRA_LAYER_PAIR_CORRELATION_FUNCTION(CONFINED_BROWNIAN_PARTICLES& sys, double dr);
    
    INTRA_LAYER_PAIR_CORRELATION_FUNCTION& setup(CONFINED_BROWNIAN_PARTICLES& sys, double dr);
    
    INTRA_LAYER_PAIR_CORRELATION_FUNCTION& calculate();
    double findPositionOfMinimum(int n, int smoothRange = 0, double lowerBound = 0);
    
    double calculateMeanCorrelation();
    
    //getter
    double getMaximalRadius() const;
    double getResolution() const;
    int getLength() const;
    vector<double> getRadii() const;
    vector<double> getPairCorrelations() const;
    
    //setter
    INTRA_LAYER_PAIR_CORRELATION_FUNCTION& setMaximalRadius(double rMax);
    INTRA_LAYER_PAIR_CORRELATION_FUNCTION& setResolution(double dr);
    
    //printer
    INTRA_LAYER_PAIR_CORRELATION_FUNCTION& print(string filename);
    friend ostream& operator<<(ostream& os, const INTRA_LAYER_PAIR_CORRELATION_FUNCTION& pairCorrelation);
};

#endif //SHEAREDSLITPOREBD_INTRA_LAYER_PAIR_CORRELATION_FUNCTION_H
