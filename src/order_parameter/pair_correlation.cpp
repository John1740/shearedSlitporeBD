//
// Created by mhuels on 5/20/20.
//

#include <boost/format.hpp>
#include "pair_correlation.h"
namespace b = boost;

PAIR_CORRELATION::PAIR_CORRELATION(){

}

PAIR_CORRELATION::PAIR_CORRELATION(CONFINED_BROWNIAN_PARTICLES& sys){
    setup(sys, 0.01);
}

PAIR_CORRELATION::PAIR_CORRELATION(CONFINED_BROWNIAN_PARTICLES& sys, double dr){
    setup(sys, dr);
}

PAIR_CORRELATION& PAIR_CORRELATION::setup(CONFINED_BROWNIAN_PARTICLES& sys, double dr){
    simBox = sys.getSimulationBox();
    layers = LAYERS(simBox);
    maximalRadius = (simBox.getDimensions() / 2).getAbs();
    setResolution(dr);
    particle = sys.getParticleList();
    return *this;
}

PAIR_CORRELATION& PAIR_CORRELATION::calculate(){
    int numberOfLayers = layers.getNumberOfLayers();
    int numberOfParticles = particle.size();
    for(int i = 0; i < numberOfParticles; i++){
        for(int j = i + 1; j < numberOfParticles; j++){
            CARTESIAN_COORDINATE distance = particle[i].boxPosition - particle[j].boxPosition;
            distance = simBox.convertToBoxPosition(distance);
            double currentRadius = distance.getAbs();
            //check if particles are in same layer
            if(layers.tellLayerNumber(particle[i]) == layers.tellLayerNumber(particle[j])){
                //assign current radius to nearest index (only works for intervals starting at 0)
                int index = round(currentRadius / dr);
                correlationFunction[index] += 2;    //the pair (i,j) also appears as (j,i)
            }
        }
    }
    //add prefactor and set radii
    for(int i = 0; i < length; i++){
        radius[i] = i * dr;
        double annulusArea = 2 * M_PI * radius[i] * dr;
        double prefactor = pow(numberOfLayers  / float(numberOfParticles), 2) * layers.getLayerArea() / annulusArea;
        correlationFunction[i] *= prefactor;
    }
    return *this;
}

vector<double> PAIR_CORRELATION::getRadii() const{
    return radius;
}

vector<double> PAIR_CORRELATION::getPairCorrelations() const{
    return correlationFunction;
}

PAIR_CORRELATION& PAIR_CORRELATION::setResolution(double dr){
    this->dr = dr;
    length = int(ceil(maximalRadius / dr));
    radius.clear();
    radius.resize(length);
    correlationFunction.clear();
    correlationFunction.resize(length);
    return *this;
}

PAIR_CORRELATION& PAIR_CORRELATION::print(string filename){
    PRINTER printer(filename);
    printer.reset();
    //header
    char comment = printer.getComment();
    printer << comment << "r: radius [diameter]" << endl;
    printer << comment << "g(r): in-plane radial pair correlation function [1/diameter]" << endl;
    printer << comment << b::format("%7s") % "r";
    printer << "\t" << b::format("%8s") % "g(r)";
    printer << "\n";
    
    //data
    for(int i = 0; i < length; i++){
        printer << b::format("% 2.5f") % radius[i];
        printer << "\t" << b::format("% 2.5f") % correlationFunction[i];
        printer << "\n";
    }
    return *this;
}

ostream& operator<<(ostream& os, const PAIR_CORRELATION& pairCorrelation){
    cout << "#r: radius [diameter]" << endl;
    cout << "#g(r): in-plane radial pair correlation function [1/diameter]" << endl;
    cout << "#" << b::format("%7s") % "r";
    cout << "\t" << b::format("%8s") % "g(r)";
    cout << "\n";
    
    //data
    for(int i = 0; i < pairCorrelation.length; i++){
        cout << b::format("% 2.5f") % pairCorrelation.radius[i];
        cout << "\t" << b::format("% 2.5f") % pairCorrelation.correlationFunction[i];
        cout << "\n";
    }
    return os;
}

double PAIR_CORRELATION::getMaximalRadius() const{
    return maximalRadius;
}

double PAIR_CORRELATION::getResolution() const{
    return dr;
}

int PAIR_CORRELATION::getLength() const{
    return length;
}

PAIR_CORRELATION& PAIR_CORRELATION::setMaximalRadius(double rMax){
    this->maximalRadius = rMax;
    return *this;
}

//returns location (radius) of the n-th local minimum based on crossings around the average value
//smoothens crossings by smoothRange * dr
//only radii above lowerBound are considered
double PAIR_CORRELATION::findPositionOfMinimum(int n, int smoothRange, double lowerBound){
    double threshold = calculateMeanCorrelation();
    int pos0 = floor(lowerBound / dr);
    int skip = ceil(smoothRange / 2.0);    //need to round up, because findNext...Crossing rounds down
    int posDown, posUp;
    posUp = findNextUpCrossing(pos0, threshold, smoothRange); //find the first up-crossing
    for(int i = 0; i < n; i++){
        //start looking for next crossing after the smoothRange to avoid posDown > posUp cases
        posDown = findNextDownCrossing(posUp + skip, threshold, smoothRange);
        posUp = findNextUpCrossing(posDown + skip, threshold, smoothRange);
    }
    double minimumPosition = (radius[posUp] + radius[posDown]) / 2;
    return minimumPosition;
}

double PAIR_CORRELATION::calculateMeanCorrelation(){
    double g_avg = 0;
    int ctr = 0;
    for(int i = 0; i < length; i++){
        double currentG = correlationFunction[i];
        if(isnan(currentG) == false){
            g_avg += correlationFunction[i];
            ctr++;
        }
    }
    g_avg /= ctr;
    return g_avg;
}

//returns -1 if there is no next up-crossing
//if there are multiple crossings in quick succession (due to noice), the average value between the first and the last
//crossing within the range of <averageRange> is returned
int PAIR_CORRELATION::findNextUpCrossing(int pos, double threshold, int averageRange){
    for(int i = pos + 1; i < length; i++){
        if(correlationFunction[i] >= threshold && correlationFunction[i-1] < threshold){
            int lastUpCrossing = findLastUpCrossing(i, threshold, i + averageRange);
            if(lastUpCrossing == -1){
                return i;
            }
            else{
                return int((lastUpCrossing + i) / 2);
            }
        }
    }
    return -1;
}

int PAIR_CORRELATION::findNextDownCrossing(int pos, double threshold, int averageRange){
    for(int i = pos + 1; i < length; i++){
        if(correlationFunction[i] < threshold && correlationFunction[i-1] >= threshold){
            int lastDownCrossing = findLastDownCrossing(i, threshold, i + averageRange);
            if(lastDownCrossing == -1){
                return i;
            }
            else{
                return int((lastDownCrossing + i) / 2);
            }
        }
    }
    return -1;
}

//returns -1 if there is no up-crossing within [pos, posMax] at all
int PAIR_CORRELATION::findLastUpCrossing(int pos, double threshold, int posMax){
    int lastUpCrossing = -1;
    for(int i = pos + 1; i < posMax + 1; i++){
        if(correlationFunction[i] >= threshold && correlationFunction[i-1] < threshold){
            lastUpCrossing = i;
        }
    }
    return lastUpCrossing;
}

//returns -1 if there is no down-crossing within [pos, posMax] at all
int PAIR_CORRELATION::findLastDownCrossing(int pos, double threshold, int posMax){
    int lastDownCrossing = -1;
    for(int i = pos + 1; i < posMax + 1; i++){
        if(correlationFunction[i] < threshold && correlationFunction[i-1] >= threshold){
            lastDownCrossing = i;
        }
    }
    return lastDownCrossing;
}