//
// Created by mhuels on 5/18/20.
//

#include "layers.h"

LAYERS::LAYERS(){

}

//need to initialize with this constructor
LAYERS::LAYERS(const SLIT_PORE_BOX& simBox){
    setNumberOfLayers(simBox);
    setZMin(simBox);
    setLayerArea(simBox);
    calculateLayerThickness();
    calculateLayerCenters();
}

int LAYERS::getNumberOfLayers() const{
    return numberOfLayers;
}

double LAYERS::getZMin() const{
    return zMin;
}

double LAYERS::getLayerThickness() const{
    return layerThickness;
}

void LAYERS::setNumberOfLayers(const SLIT_PORE_BOX& simBox){
    numberOfLayers = round(simBox.getDimensions().z);
}

void LAYERS::setZMin(const SLIT_PORE_BOX& simBox){
    zMin = - 0.2 * simBox.getDimensions().z;
}

double LAYERS::calculateLayerThickness(){
    layerThickness = - 2 * zMin / (numberOfLayers - 1);
    return layerThickness;
}

vector<double> LAYERS::calculateLayerCenters(){
    layerCenter.clear();
    layerCenter.resize(numberOfLayers);
    for(int i = 0; i < numberOfLayers; i++){
        layerCenter[i] = (zMin + i * layerThickness);
    }
    return layerCenter;
}

//returns -1 if particle is located outside of layers
int LAYERS::tellLayerNumber(const PARTICLE& particle){
    double z = particle.boxPosition.z;
    for(int j = 0; j < numberOfLayers; j++){
        if(z >= layerCenter[j] - layerThickness / 2 && z < layerCenter[j] + layerThickness / 2){
            return j;
        }
    }
    if(z < layerCenter[0] - layerThickness / 2 || z >= layerCenter[numberOfLayers - 1] + layerThickness / 2){
        printf("Particle with z=%.2f can't be assigned to any layer.\n", z);
    }
    return -1;
}

double LAYERS::getLayerArea() const{
    return layerArea;
}

void LAYERS::setLayerArea(const SLIT_PORE_BOX& simBox){
    layerArea = simBox.getDimensions().x * simBox.getDimensions().y;
}

vector<vector<int>> LAYERS::getParticleLayerMap(const vector<CHARGED_PARTICLE>& particles){
    vector<vector<int>> indices(numberOfLayers);
    for(int i = 0; i < particles.size(); i++){
        int layerNumber = tellLayerNumber(particles[i]);
        indices[layerNumber].push_back(i);
    }
    return indices;
}
