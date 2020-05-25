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
    
    double calculateMeanCorrelation();
    int findNextUpCrossing(int pos, double threshold, int averageRange);
    int findNextDownCrossing(int pos, double threshold, int averageRange);
    int findLastUpCrossing(int pos, double threshold, int posMax);
    int findLastDownCrossing(int pos, double threshold, int posMax);
public:
    PAIR_CORRELATION();
    PAIR_CORRELATION(CONFINED_BROWNIAN_PARTICLES& sys);
    PAIR_CORRELATION(CONFINED_BROWNIAN_PARTICLES& sys, double dr);
    
    PAIR_CORRELATION& setup(CONFINED_BROWNIAN_PARTICLES& sys, double dr);
    
    PAIR_CORRELATION& calculate();
    double findPositionOfMinimum(int n, int smoothRange = 0, double lowerBound = 0);
    
    //getter
    double getMaximalRadius() const;
    double getResolution() const;
    int getLength() const;
    vector<double> getRadii() const;
    vector<double> getPairCorrelations() const;
    
    //setter
    PAIR_CORRELATION& setMaximalRadius(double rMax);
    PAIR_CORRELATION& setResolution(double dr);
    
    //printer
    PAIR_CORRELATION& print(string filename);
    friend ostream& operator<<(ostream& os, const PAIR_CORRELATION& pairCorrelation);
};

#endif //SHEAREDSLITPOREBD_PAIR_CORRELATION_H
