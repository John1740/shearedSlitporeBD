//
// Created by mhuels on 5/20/20.
//

#include <boost/format.hpp>
#include "intra_layer_pair_correlation_function.h"
namespace b = boost;

INTRA_LAYER_PAIR_CORRELATION_FUNCTION::INTRA_LAYER_PAIR_CORRELATION_FUNCTION(){

}

INTRA_LAYER_PAIR_CORRELATION_FUNCTION::INTRA_LAYER_PAIR_CORRELATION_FUNCTION(CONFINED_BROWNIAN_PARTICLES& sys){
    setup(sys, 0.01);
}

INTRA_LAYER_PAIR_CORRELATION_FUNCTION::INTRA_LAYER_PAIR_CORRELATION_FUNCTION(CONFINED_BROWNIAN_PARTICLES& sys, double dr){
    setup(sys, dr);
}

INTRA_LAYER_PAIR_CORRELATION_FUNCTION& INTRA_LAYER_PAIR_CORRELATION_FUNCTION::setup(CONFINED_BROWNIAN_PARTICLES& sys, double dr){
    simBox = sys.getSimulationBox();
    layers = LAYERS(simBox);
//    maximalRadius = (simBox.getDimensions() / 2).getAbs();
    maximalRadius = sqrt(pow(simBox.getDimensions().x / 2, 2) + pow(simBox.getDimensions().y / 2, 2));
    setResolution(dr);
    particle = sys.getParticleList();
    return *this;
}

INTRA_LAYER_PAIR_CORRELATION_FUNCTION& INTRA_LAYER_PAIR_CORRELATION_FUNCTION::calculate(){
    correlationFunction.clear();
    correlationFunction.resize(length);
    int numberOfLayers = layers.getNumberOfLayers();
    int numberOfParticles = particle.size();
    for(int i = 0; i < numberOfParticles; i++){
        for(int j = i + 1; j < numberOfParticles; j++){
            CARTESIAN_COORDINATE relative = particle[i].boxPosition - particle[j].boxPosition;
            relative = simBox.convertToBoxPosition(relative);
            //distance within layer
            double currentRadius = sqrt(pow(relative.x, 2.0) + pow(relative.y, 2.0));
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
        int numberOfParticlesInLayer = numberOfParticles / numberOfLayers;
        double averageParticleDensity = numberOfParticlesInLayer / layers.getLayerArea();
        // Good explanation in: http://www.physics.emory.edu/faculty/weeks/idl/gofr2.html
        // average over all layers (1/numberOfLayers)
        // average over all particles i (1/numberOfParticlesInLayer)
        // ratio of densityInAnnulus (=numberOfParticlesInAnnulus/annulusArea) to averageParticleDensity
        double normalization = numberOfLayers * numberOfParticlesInLayer * averageParticleDensity * annulusArea;
        correlationFunction[i] /= normalization;
    }
    return *this;
}

vector<double> INTRA_LAYER_PAIR_CORRELATION_FUNCTION::getRadii() const{
    return radius;
}

vector<double> INTRA_LAYER_PAIR_CORRELATION_FUNCTION::getPairCorrelations() const{
    return correlationFunction;
}

INTRA_LAYER_PAIR_CORRELATION_FUNCTION& INTRA_LAYER_PAIR_CORRELATION_FUNCTION::setResolution(double dr){
    this->dr = dr;
    length = int(ceil(maximalRadius / dr));
    radius.clear();
    radius.resize(length);
    correlationFunction.clear();
    correlationFunction.resize(length);
    return *this;
}

INTRA_LAYER_PAIR_CORRELATION_FUNCTION& INTRA_LAYER_PAIR_CORRELATION_FUNCTION::print(string filename){
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

ostream& operator<<(ostream& os, const INTRA_LAYER_PAIR_CORRELATION_FUNCTION& pairCorrelation){
    os << "#r: radius [diameter]" << endl;
    os << "#g(r): in-plane radial pair correlation function [1/diameter]" << endl;
    os << "#" << b::format("%7s") % "r";
    os << "\t" << b::format("%8s") % "g(r)";
    os << "\n";
    
    //data
    for(int i = 0; i < pairCorrelation.length; i++){
        os << b::format("% 2.5f") % pairCorrelation.radius[i];
        os << "\t" << b::format("% 2.5f") % pairCorrelation.correlationFunction[i];
        os << "\n";
    }
    return os;
}

double INTRA_LAYER_PAIR_CORRELATION_FUNCTION::getMaximalRadius() const{
    return maximalRadius;
}

double INTRA_LAYER_PAIR_CORRELATION_FUNCTION::getResolution() const{
    return dr;
}

int INTRA_LAYER_PAIR_CORRELATION_FUNCTION::getLength() const{
    return length;
}

INTRA_LAYER_PAIR_CORRELATION_FUNCTION& INTRA_LAYER_PAIR_CORRELATION_FUNCTION::setMaximalRadius(double rMax){
    this->maximalRadius = rMax;
    return *this;
}

//returns location (radius) of the n-th local minimum based on crossings around the average value
//smoothens crossings by smoothRange * dr
//only radii above lowerBound are considered
double INTRA_LAYER_PAIR_CORRELATION_FUNCTION::findPositionOfMinimum(int n, int smoothRange, double lowerBound){
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

double INTRA_LAYER_PAIR_CORRELATION_FUNCTION::calculateMeanCorrelation(){
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
int INTRA_LAYER_PAIR_CORRELATION_FUNCTION::findNextUpCrossing(int pos, double threshold, int averageRange){
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

int INTRA_LAYER_PAIR_CORRELATION_FUNCTION::findNextDownCrossing(int pos, double threshold, int averageRange){
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
int INTRA_LAYER_PAIR_CORRELATION_FUNCTION::findLastUpCrossing(int pos, double threshold, int posMax){
    int lastUpCrossing = -1;
    for(int i = pos + 1; i < posMax + 1; i++){
        if(correlationFunction[i] >= threshold && correlationFunction[i-1] < threshold){
            lastUpCrossing = i;
        }
    }
    return lastUpCrossing;
}

//returns -1 if there is no down-crossing within [pos, posMax] at all
int INTRA_LAYER_PAIR_CORRELATION_FUNCTION::findLastDownCrossing(int pos, double threshold, int posMax){
    int lastDownCrossing = -1;
    for(int i = pos + 1; i < posMax + 1; i++){
        if(correlationFunction[i] < threshold && correlationFunction[i-1] >= threshold){
            lastDownCrossing = i;
        }
    }
    return lastDownCrossing;
}