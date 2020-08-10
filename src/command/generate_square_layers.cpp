#include "generate_square_layers.h"

#include "../struct/layers.h"

GENERATE_SQUARE_LAYERS::GENERATE_SQUARE_LAYERS(){
    numberOfAdditionalSites = 0;
    setup(NUMBER_OF_PARTICLES, D_WALL, DENSITY);
}

GENERATE_SQUARE_LAYERS::GENERATE_SQUARE_LAYERS(int N, double dWall, double density){
    numberOfAdditionalSites = 0;
    setup(N, dWall, density);
}

GENERATE_SQUARE_LAYERS& GENERATE_SQUARE_LAYERS::setup(int N, double dWall, double density){
    simBox = SLIT_PORE_BOX(N / density, dWall);
    particle.resize(N);
    numberOfLayers = round(simBox.getDimensions().z);
    numberOfSites = sqrt(particle.size() / numberOfLayers);
    particleTemplate.charge = CHARGE;
    particleTemplate.diameter = DIAMETER;
    particleTemplate.species = 0;
    return *this;
}

CONFINED_BROWNIAN_PARTICLES GENERATE_SQUARE_LAYERS::generate(){
    setLatticePeriodicity();
    particle.clear();

    for(int i = 0; i < numberOfLayers - 1; ++i) {
        addLayer(i);
    }
    addIncommensurableLayer(numberOfLayers - 1);
    
    CONFINED_BROWNIAN_PARTICLES sys;
    *(sys.simulationBox()) = simBox;
    sys.setParticleList(particle);
    
    return sys;
}

void GENERATE_SQUARE_LAYERS::setLatticePeriodicity(){
    LAYERS layers(simBox);
    zMin = layers.getZMin();
    dx = simBox.getDimensions().x / numberOfSites;
    dy = simBox.getDimensions().y / numberOfSites;
    dz = layers.getLayerThickness();

    dxAdd = simBox.getDimensions().x / (numberOfSites + numberOfAdditionalSites);
    dyAdd = dxAdd;
}

void GENERATE_SQUARE_LAYERS::addLayer(int layerIndex){
    for(int j = 0; j < numberOfSites; ++j){ //j=index in y-direction
        for(int k = 0; k < numberOfSites; ++k){ //k=index in x-direction
            CHARGED_PARTICLE newParticle(particleTemplate);
            newParticle.position = REAL_C(
                    dx * k + layerIndex * dx / 2, //displaced by dx/2 from lower layer
                    dy * j + layerIndex * dy / 2, //displaced by dy/2 from lower layer
                    zMin + layerIndex * dz
                    );
            particle.push_back(newParticle);
        }
    }
}

void GENERATE_SQUARE_LAYERS::addIncommensurableLayer(int layerIndex){
    for(int j = 0; j < numberOfSites + numberOfAdditionalSites; ++j){
        for(int k = 0; k < numberOfSites + numberOfAdditionalSites; ++k){
            CHARGED_PARTICLE newParticle(particleTemplate);
            newParticle.position = REAL_C(
                    dxAdd * k + layerIndex * dxAdd / 2,
                    dyAdd * j + layerIndex * dyAdd / 2,
                    zMin + layerIndex * dz
                    );
            particle.push_back(newParticle);
        }
    }
}

GENERATE_SQUARE_LAYERS& GENERATE_SQUARE_LAYERS::setParticleProperties(const CHARGED_PARTICLE& particle){
    particleTemplate = particle;
    return *this;
}

GENERATE_SQUARE_LAYERS& GENERATE_SQUARE_LAYERS::setParticleProperties(double charge, double diameter, int species){
    particleTemplate.charge = charge;
    particleTemplate.diameter = diameter;
    particleTemplate.species = species;
    return *this;
}

