//
// Created by mhuels on 5/20/20.
// Test

#include <boost/format.hpp>
#include "intra_layer_pair_correlation_function.h"

namespace b = boost;

INTRA_LAYER_PAIR_CORRELATION_FUNCTION::INTRA_LAYER_PAIR_CORRELATION_FUNCTION(){
}

INTRA_LAYER_PAIR_CORRELATION_FUNCTION::INTRA_LAYER_PAIR_CORRELATION_FUNCTION(CONFINED_BROWNIAN_PARTICLES& sys){
    setup(sys, 0.05);
}

INTRA_LAYER_PAIR_CORRELATION_FUNCTION::INTRA_LAYER_PAIR_CORRELATION_FUNCTION(CONFINED_BROWNIAN_PARTICLES& sys,
                                                                             double dr){
    setup(sys, dr);
}

INTRA_LAYER_PAIR_CORRELATION_FUNCTION&
INTRA_LAYER_PAIR_CORRELATION_FUNCTION::setup(CONFINED_BROWNIAN_PARTICLES& sys, double dr){
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
                if(i <= j){
                    continue;
                }
                REAL_C relative = particle[i].boxPosition - particle[j].boxPosition;
                relative = simBox.convertToBoxPosition(relative);
                //distance within layer
                double currentRadius = sqrt(pow(relative.x, 2.0) + pow(relative.y, 2.0));
                //assign current radius to nearest index (only works for intervals starting at 0)
                int r = floor(currentRadius / dr);
                if(r>= numberOfBins){r=numberOfBins-1;}
                layerCorrelation[l][r] += 2;
                currentRadius=ParticlesAreWithinRadiusTwice(abs(relative.x),abs(relative.y));
                if(currentRadius){
                    int r = floor(currentRadius / dr);
                    if(r>= numberOfBins){
                        r=numberOfBins-1;}
                    layerCorrelation[l][r] += 2;
                }

            }
        }
    }
    //add prefactor and set radii
    for(int l = 0; l < numberOfLayers; l++){
        for(int r = 0; r < numberOfBins; r++){
            radius[r] = (r) * dr;
            //NEEDED: add correction to radii beyond L/2
            //double annulusArea = 2 * M_PI * radius[r] * dr;
            double annulusArea = calculateAnnulus(radius[r], dr);
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
double INTRA_LAYER_PAIR_CORRELATION_FUNCTION::ParticlesAreWithinRadiusTwice(double dx, double dy){
    double currentRadius =0;
    double X = simBox.getDimensions().x / 2;
    double Y = simBox.getDimensions().y / 2;
    if((Y-dy)<sqrt(maximalRadius*maximalRadius-dx*dx)-Y){
        currentRadius =sqrt(pow(dx, 2.0) + pow(2*Y-dy, 2.0));
    }
    if((X-dx)<sqrt(maximalRadius*maximalRadius-dy*dy)-X){
        currentRadius =sqrt(pow(2*X-dx, 2.0) + pow(dy, 2.0));
    }
    return currentRadius;
}

double INTRA_LAYER_PAIR_CORRELATION_FUNCTION::calculateAnnulus(double radius, double dr){
    double Annulus = M_PI * (pow(radius+dr,2)-pow(radius,2));//calculateCircleSquareArea(radius)-calculateCircleSquareArea(radius+dr);
    return Annulus;
}


double INTRA_LAYER_PAIR_CORRELATION_FUNCTION::calculateCircleSquareArea(double radius){
// Not needed with ParticlesAreWithinRadiusTwice
    double x = simBox.getDimensions().x/2;
    double y = simBox.getDimensions().y/2;

    double q1x;
    double q2y;

    if (radius<x){q2y=0;}
    else {q2y = radius*sin(acos(x/radius));}
    if (radius<y){q1x=0;}
    else {q1x = radius*cos(asin(y/radius));}

    if (x<q1x){q1x=x;}
    if (y<q2y){q2y=y;}

    double squareArea= x * y;
    double triangle1 = 0.5 * y * q1x;
    double triangle2 = 0.5 * x * q2y;

    double alpha = atan(y/q1x)- atan(q2y/x);
    double circlePart = radius*radius/2.0*alpha;
    double area = 4*(squareArea-triangle1-triangle2-circlePart);

    return area;
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
        //posUp = findNextUpCrossing(posDown + skip, threshold, smoothRange);
    }
    //double minimumPosition = (radius[posUp] + radius[posDown]) / 2;
    double minimumPosition = radius[posDown];
    return minimumPosition;
}
double INTRA_LAYER_PAIR_CORRELATION_FUNCTION::findPositionOfMinimumNew(){
    int minimumWidth = 1;
    int minTolerance = 1;
    int leftBigger;
    int rightBigger;
    int firstNonZero = 0;
    for(int i=0;i<minimumWidth;i++){
        if(averageLayerCorrelation[i]){firstNonZero=1;}
    }

    for(int i=minimumWidth;i<numberOfBins-minimumWidth;i++){
        if(firstNonZero){
            leftBigger = 0;
            rightBigger = 0;
            for(int j = 1; j <= minimumWidth; j++){
                if(averageLayerCorrelation[i] <= averageLayerCorrelation[i - j]){ leftBigger++; }
                if(averageLayerCorrelation[i] <= averageLayerCorrelation[i + j]){ rightBigger++; }
            }
            if(leftBigger >= minTolerance && rightBigger >= minTolerance){
                return radius[i];
            }
        }
        else if(averageLayerCorrelation[i]){firstNonZero=1;}

    }
    return -1;
}

//returns -1 if there is no next up-crossing
//if there are multiple crossings in quick succession (due to noise), the average value between the first and the last
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

INTRA_LAYER_PAIR_CORRELATION_FUNCTION& INTRA_LAYER_PAIR_CORRELATION_FUNCTION::print(string filename, bool overwrite, string header){
    PRINTER printer(filename);
    if(overwrite){
        printer.reset();
    }
    if(header.size() > 0){
        printer << string(3, printer.getComment()) << header << endl;
    }
    printer << *this;
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