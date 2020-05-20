//
// Created by mhuels on 5/20/20.
//

#include <boost/format.hpp>
#include "pair_correlation.h"
namespace b = boost;

PAIR_CORRELATION::PAIR_CORRELATION(){

}

PAIR_CORRELATION::PAIR_CORRELATION(CONFINED_BROWNIAN_PARTICLES* sys){
    setup(sys, 0.01);
}

PAIR_CORRELATION::PAIR_CORRELATION(CONFINED_BROWNIAN_PARTICLES* sys, double dr){
    setup(sys, dr);
}

void PAIR_CORRELATION::setup(CONFINED_BROWNIAN_PARTICLES* sys, double dr){
    simBox = sys->getSimulationBox();
    layers = LAYERS(simBox);
    maximalRadius = (simBox.getDimensions() / 2).getAbs();
    setResolution(dr);
    particle = sys->getParticleList();
}

void PAIR_CORRELATION::calculate(){
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
}

vector<double> PAIR_CORRELATION::getRadii() const{
    return radius;
}

vector<double> PAIR_CORRELATION::getPairCorrelations() const{
    return correlationFunction;
}

void PAIR_CORRELATION::setResolution(double dr){
    this->dr = dr;
    length = int(ceil(maximalRadius / dr));
    radius.clear();
    radius.resize(length);
    correlationFunction.clear();
    correlationFunction.resize(length);
}

void PAIR_CORRELATION::print(string filename){
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
