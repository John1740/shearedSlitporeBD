//
// Created by mhuels on 5/25/20.
//

#include "angular_bond_parameter.h"
#include <complex>

double ANGULAR_BOND_PARAMETER::angleBetweenParticles(const PARTICLE& particle1, const PARTICLE& particle2){
    CARTESIAN_COORDINATE relative = particle2.boxPosition - particle1.boxPosition;
    relative = simBox.convertToBoxPosition(relative);
    double angle;
    if(relative.y >= 0){
        angle = acos(relative.x / relative.getAbs());
    }
    else{
        angle = 2 * M_PI - acos(relative.x / relative.getAbs());
    }
    return angle;
}

ANGULAR_BOND_PARAMETER::ANGULAR_BOND_PARAMETER(){

}

ANGULAR_BOND_PARAMETER::ANGULAR_BOND_PARAMETER(CONFINED_BROWNIAN_PARTICLES& sys){
    setup(sys);
    setN(1);
}

ANGULAR_BOND_PARAMETER::ANGULAR_BOND_PARAMETER(CONFINED_BROWNIAN_PARTICLES& sys, int n){
    setup(sys);
    setN(n);
}

ANGULAR_BOND_PARAMETER& ANGULAR_BOND_PARAMETER::setup(CONFINED_BROWNIAN_PARTICLES& sys){
    particle = sys.getParticleList();
    simBox = sys.getSimulationBox();
    layers = LAYERS(simBox);
    pairCorrelation = PAIR_CORRELATION(sys, 0.01);
    pairCorrelation.calculate();
    return *this;
}

double ANGULAR_BOND_PARAMETER::calculateForSingleParticle(int i){
    complex<double> psi = 0;
    complex<double> I(0, 1);
    double minimumPosition = pairCorrelation.findPositionOfMinimum(1, 5);
    int numberOfNeighbors = 0;
    for(int j = 0; j < particle.size(); j++){
        if(i == j){
            continue;
        }
        if(layers.tellLayerNumber(particle[i]) == layers.tellLayerNumber(particle[j])){
            CARTESIAN_COORDINATE distance = particle[i].boxPosition - particle[j].boxPosition;
            distance = simBox.convertToBoxPosition(distance);
            if(distance.getAbs() < minimumPosition){
                double angle = angleBetweenParticles(particle[i], particle[j]);
                psi += exp(I * double(n) * angle);
                numberOfNeighbors++;
            }
        }
    }
    return abs(psi) / numberOfNeighbors;
}

double ANGULAR_BOND_PARAMETER::calculateAverageOverAllParticles(){
    double average = 0;
    int counter = 0;
    for(int i = 0; i < particle.size(); i++){
        double increment = calculateForSingleParticle(i);
        //ignore particles which have no adjacent particles (should only happen at low densities)
        if(! isnan(increment)){
            average += increment;
            counter++;
        }
        else{
            cout << "Angular bond parameter of particle " << i << " is nan! It appears to have no adjacent particles." << endl;
        }
    }
    average /= counter;
    return average;
}

ANGULAR_BOND_PARAMETER& ANGULAR_BOND_PARAMETER::setN(int n){
    this->n = n;
    return *this;
}

int ANGULAR_BOND_PARAMETER::getN() const{
    return n;
}
