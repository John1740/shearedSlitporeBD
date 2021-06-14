//
// Created by mhuels on 5/25/20.
//

#include "angular_bond_parameter.h"
#include <complex>

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
    pairCorrelation = INTRA_LAYER_PAIR_CORRELATION_FUNCTION(sys, 0.05);
    pairCorrelation.calculateAverageLayerCorrelation();
    calculateNextNeighborShellRadius();
    isolatedParticles.clear();
    return *this;
}

vector<int> ANGULAR_BOND_PARAMETER::getNearestNeighborIndices(int i){
    vector<int> nearestNeighborIndices;
    for(int j = 0; j < particle.size(); j++){
        if(i == j){
            continue;
        }
        if(layers.tellLayerNumber(particle[i]) == layers.tellLayerNumber(particle[j])){
            REAL_C relative = particle[i].boxPosition - particle[j].boxPosition;
            relative = simBox.convertToBoxPosition(relative);
            double distance = sqrt(pow(relative.x, 2) + pow(relative.y, 2));
            if(distance <= nextNeighborShellRadius){
                nearestNeighborIndices.push_back(j);
            }
        }
    }
    return nearestNeighborIndices;
}

double ANGULAR_BOND_PARAMETER::calculateForSingleParticle(int i){
    complex<double> psi = 0;
    complex<double> I(0, 1);
    vector<int> neighborIndices = getNearestNeighborIndices(i);
    for(int j = 0; j < neighborIndices.size(); j++){
        double angle = angleBetweenParticles(particle[i], particle[neighborIndices[j]]);
        psi += exp(I * double(n) * angle);
    }
    if(neighborIndices.size() > 0){
        return abs(psi) / neighborIndices.size();
    }
    else{
        //penalty in case neighbors are too far away ->
        return 0;
    }
}

double ANGULAR_BOND_PARAMETER::calculateLayerAverage(int m){
    double average = 0;
    int counter = 0;
    vector<vector<int>> particleLayerMap = layers.getParticleLayerMap(particle);
    vector<int> particleIndices = particleLayerMap[m];
    int i;
    for(int idx = 0; idx < particleIndices.size(); idx++){
        i = particleIndices[idx];   //index in particle
        double increment = calculateForSingleParticle(i);
        //ignore particles which have no adjacent particles (should only happen at low densities)
        if(isnan(increment)){
            isolatedParticles.push_back(i);
            cout << "calculateForSingleParticle(" << i << ") = nan" << endl;
            continue;
        }
        average += increment;
        counter++;
        if(increment == 0){
            isolatedParticles.push_back(i);
        }
    }
    average /= counter; //counter should always be equal to particleIndices.size()
    return average;
}

vector<double> ANGULAR_BOND_PARAMETER::calculateLayerAverages(){
    int numberOfLayers = layers.getNumberOfLayers();
    vector<double> layerAverages(numberOfLayers, 0.);
    isolatedParticles.clear();
    for(int m = 0; m < numberOfLayers; m++){
        layerAverages[m] = calculateLayerAverage(m);
    }
    return layerAverages;
}

double ANGULAR_BOND_PARAMETER::calculateSystemAverage(){
    vector<double> layerAverages = calculateLayerAverages();
    double average = 0;
    for(int m = 0; m < layerAverages.size(); m++){
        average += layerAverages[m];
    }
    average /= layerAverages.size();
    return average;
}

double ANGULAR_BOND_PARAMETER::angleBetweenParticles(const PARTICLE& particle1, const PARTICLE& particle2){
    REAL_C relative = particle2.boxPosition - particle1.boxPosition;
    relative = simBox.convertToBoxPosition(relative);
    double distance = sqrt(pow(relative.x, 2) + pow(relative.y, 2));
    //distance can't be zero, else particles would overlap
    double angle;
    if(relative.y >= 0){
        angle = acos(relative.x / distance);
    }
    else{
        angle = 2 * M_PI - acos(relative.x / distance);
    }
    return angle;
}

ANGULAR_BOND_PARAMETER& ANGULAR_BOND_PARAMETER::setN(int n){
    this->n = n;
    return *this;
}

int ANGULAR_BOND_PARAMETER::getN() const{
    return n;
}

double ANGULAR_BOND_PARAMETER::calculateNextNeighborShellRadius(){
    nextNeighborShellRadius = pairCorrelation.findPositionOfMinimum(1, 0);
    return nextNeighborShellRadius;
}

double ANGULAR_BOND_PARAMETER::getNextNeighborShellRadius() const{
    return nextNeighborShellRadius;
}

INTRA_LAYER_PAIR_CORRELATION_FUNCTION ANGULAR_BOND_PARAMETER::getPairCorrelation() const{
    return pairCorrelation;
}

vector<int> ANGULAR_BOND_PARAMETER::getIsolatedParticles() const{
    return isolatedParticles;
}
