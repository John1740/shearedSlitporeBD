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
    maximalRadius = sqrt(pow(simBox.getDimensions().x / 2, 2) + pow(simBox.getDimensions().y / 2, 2));
    setResolution(dr);
    particle = sys.getParticleList();
    return *this;
}

// Good explanation in: http://www.physics.emory.edu/faculty/weeks/idl/gofr2.html
INTRA_LAYER_PAIR_CORRELATION_FUNCTION& INTRA_LAYER_PAIR_CORRELATION_FUNCTION::calculateLayerCorrelation(){
    int numberOfLayers = layers.getNumberOfLayers();
    layerCorrelation.clear();
    layerCorrelation.resize(numberOfLayers);
    for(int i = 0; i < numberOfLayers; i++){
        layerCorrelation[i].clear();
        layerCorrelation[i].resize(numberOfBins);
    }
    int numberOfParticles = particle.size();
    vector<vector<int>> particleLayerMap = layers.getParticleLayerMap(particle);
    for(int l = 0; l < numberOfLayers; l++){
        for(const int& i: particleLayerMap[l]){
            for(const int& j: particleLayerMap[l]){
                if(i == j){
                    continue;
                }
                CARTESIAN_COORDINATE relative = particle[i].boxPosition - particle[j].boxPosition;
                relative = simBox.convertToBoxPosition(relative);
                //distance within layer
                double currentRadius = sqrt(pow(relative.x, 2.0) + pow(relative.y, 2.0));
                //assign current radius to nearest index (only works for intervals starting at 0)
                int r = round(currentRadius / dr);
                layerCorrelation[l][r] += 1;
            }
        }
    }
    //add prefactor and set radii
    for(int l = 0; l < numberOfLayers; l++){
        for(int r = 0; r < numberOfBins; r++){
            radius[r] = r * dr;
            //NEEDED: add correction to radii beyond L/2
            double annulusArea = 2 * M_PI * radius[r] * dr;
            double averageParticleDensity = particleLayerMap[l].size() / layers.getLayerArea();
            // average over all particles in layer (1/numberOfParticlesInLayer[i])
            // so far: layerCorrelation[i][j] = numberOfParticlesInAnnulus
            // ratio of densityInAnnulus (=numberOfParticlesInAnnulus/annulusArea) to averageParticleDensity
            double normalization = particleLayerMap[l].size() * averageParticleDensity * annulusArea;
            layerCorrelation[l][r] /= normalization;
        }
    }
    return *this;
}

INTRA_LAYER_PAIR_CORRELATION_FUNCTION& INTRA_LAYER_PAIR_CORRELATION_FUNCTION::calculateAverageLayerCorrelation(){
    calculateLayerCorrelation();
    averageLayerCorrelation.clear();
    averageLayerCorrelation.resize(numberOfBins);
    for(int l = 0; l < layerCorrelation.size(); l++){   //i = layer index
        for(int r = 0; r < numberOfBins; r++){    //j = bin index
            averageLayerCorrelation[r] += layerCorrelation[l][r];
        }
    }
    //normalize
    for(int r = 0; r < numberOfBins; r++){
        averageLayerCorrelation[r] /= layerCorrelation.size();
    }
    return *this;
}

double INTRA_LAYER_PAIR_CORRELATION_FUNCTION::calculateMeanCorrelation(){
    //error message, if not yet calculated?
    double g_avg = 0;
    int ctr = 0;
    for(int r = 0; r < numberOfBins; r++){
        double currentG = averageLayerCorrelation[r];
        if(isnan(currentG) == false){
            g_avg += averageLayerCorrelation[r];
            ctr++;
        }
    }
    g_avg /= ctr;
    return g_avg;
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

//returns -1 if there is no next up-crossing
//if there are multiple crossings in quick succession (due to noice), the average value between the first and the last
//crossing within the range of <averageRange> is returned
int INTRA_LAYER_PAIR_CORRELATION_FUNCTION::findNextUpCrossing(int pos, double threshold, int averageRange){
    for(int i = pos + 1; i < numberOfBins; i++){
        if(averageLayerCorrelation[i] >= threshold && averageLayerCorrelation[i - 1] < threshold){
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
    for(int i = pos + 1; i < numberOfBins; i++){
        if(averageLayerCorrelation[i] < threshold && averageLayerCorrelation[i - 1] >= threshold){
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
        if(averageLayerCorrelation[i] >= threshold && averageLayerCorrelation[i - 1] < threshold){
            lastUpCrossing = i;
        }
    }
    return lastUpCrossing;
}

//returns -1 if there is no down-crossing within [pos, posMax] at all
int INTRA_LAYER_PAIR_CORRELATION_FUNCTION::findLastDownCrossing(int pos, double threshold, int posMax){
    int lastDownCrossing = -1;
    for(int i = pos + 1; i < posMax + 1; i++){
        if(averageLayerCorrelation[i] < threshold && averageLayerCorrelation[i - 1] >= threshold){
            lastDownCrossing = i;
        }
    }
    return lastDownCrossing;
}

INTRA_LAYER_PAIR_CORRELATION_FUNCTION& INTRA_LAYER_PAIR_CORRELATION_FUNCTION::setResolution(double dr){
    this->dr = dr;
    numberOfBins = int(ceil(maximalRadius / dr));
    radius.clear();
    radius.resize(numberOfBins);
    layerCorrelation.clear();
    layerCorrelation.resize(numberOfBins);
    averageLayerCorrelation.clear();
    averageLayerCorrelation.resize(numberOfBins);
    return *this;
}

vector<double> INTRA_LAYER_PAIR_CORRELATION_FUNCTION::getRadii() const{
    return radius;
}

vector<vector<double>> INTRA_LAYER_PAIR_CORRELATION_FUNCTION::getLayerCorrelations() const{
    return layerCorrelation;
}

vector<double> INTRA_LAYER_PAIR_CORRELATION_FUNCTION::getAverageLayerCorrelations() const{
    return averageLayerCorrelation;
}

double INTRA_LAYER_PAIR_CORRELATION_FUNCTION::getMaximalRadius() const{
    return maximalRadius;
}

double INTRA_LAYER_PAIR_CORRELATION_FUNCTION::getResolution() const{
    return dr;
}

int INTRA_LAYER_PAIR_CORRELATION_FUNCTION::getLength() const{
    return numberOfBins;
}

INTRA_LAYER_PAIR_CORRELATION_FUNCTION& INTRA_LAYER_PAIR_CORRELATION_FUNCTION::setMaximalRadius(double rMax){
    this->maximalRadius = rMax;
    return *this;
}

INTRA_LAYER_PAIR_CORRELATION_FUNCTION& INTRA_LAYER_PAIR_CORRELATION_FUNCTION::print(string filename){
    PRINTER printer(filename);
    printer.reset();
    printer << *this << endl;
    return *this;
}

ostream& operator<<(ostream& os, const INTRA_LAYER_PAIR_CORRELATION_FUNCTION& cor){
    os << "#r: radius [diameter]" << endl;
    os << "#g(r): average in-plane radial pair correlation function [1/diameter]" << endl;
    os << "#g_m(r): in-plane radial pair correlation function of layer m [1/diameter]" << endl;
    os << "#" << b::format("%7s") % "r";
    os << "\t" << b::format("%8s") % "g(r)";
    for(int l = 0; l < cor.layerCorrelation.size(); l++){
        os << "\t" << b::format("%8s") % (b::format("g_%i(r)") % l);
    }
    os << "\n";
    
    //data
    for(int r = 0; r < cor.numberOfBins; r++){
        os << b::format("% 2.5f") % cor.radius[r];
        os << "\t" << b::format("% 2.5f") % cor.averageLayerCorrelation[r];
        for(int l = 0; l < cor.layerCorrelation.size(); l++){
            os << "\t" << b::format("% 2.5f") % cor.layerCorrelation[l][r];
        }
        os << "\n";
    }
    return os;
}