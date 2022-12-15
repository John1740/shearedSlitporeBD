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

    particle.resize(N);
    numberOfLayers = 2;//round(simBox.getDimensions().z);
    //numberOfSites = sqrt(particle.size() / numberOfLayers);
    numberOfSitesX= round(sqrt(N/2));
    numberOfSitesY=numberOfSitesX;
    //numberOfSitesX=28;
    //numberOfSitesY=26;
    N=2*numberOfSitesX*numberOfSitesY;
    double sitesLength=sqrt(2/density/dWall);
    simBox = SLIT_PORE_BOX(N / density, dWall,numberOfSitesX*sitesLength,numberOfSitesY*sitesLength);
    particleTemplate.charge = CHARGE;
    particleTemplate.diameter = DIAMETER;
    particleTemplate.species = 0;
    particleIndex = 0;
    return *this;
}

SHEARED_SLITPORE_SYSTEM GENERATE_SQUARE_LAYERS::generate(){
    setLatticePeriodicity();
    particle.clear();

    for(int i = 0; i < numberOfLayers - 1; ++i){
        addLayer(i);
    }
    addIncommensurableLayer(numberOfLayers - 1);


    SHEARED_SLITPORE_SYSTEM sys;
    *(sys.simulationBox()) = simBox;
    sys.setParticleList(particle);
    for(int i = 0; i < sys.getNumberOfParticles(); ++i){
        sys.particles[i].setBoxPosition(simBox);
        sys.particles[i].position = sys.particles[i].boxPosition;
    }
    //double angle= 1.2;
    //double newx;
    //double newy;
    //for(int i = 0; i < sys.getNumberOfParticles(); ++i){
    //    newx = sys.particles[i].position.x * cos(angle) - sys.particles[i].position.y * sin(angle)+ simBox.getDimensions().x/2;
    //    newy =sys.particles[i].position.x * sin(angle) + sys.particles[i].position.y * cos(angle)- simBox.getDimensions().y/2 ;
    //    sys.particles[i].position.x=newx;
    //    sys.particles[i].position.y=newy;
    //    sys.particles[i].setBoxPosition(simBox);
    //    sys.particles[i].position = sys.particles[i].boxPosition;
    //}
    return sys;
}

void GENERATE_SQUARE_LAYERS::setLatticePeriodicity(){
    LAYERS layers(simBox);
    zMin = layers.getZMin();
    dx = simBox.getDimensions().x / numberOfSitesX;
    dy = simBox.getDimensions().y / numberOfSitesY;
    dz = layers.getLayerThickness();

    dxAdd = simBox.getDimensions().x / (numberOfSitesX + numberOfAdditionalSites);
    dyAdd = simBox.getDimensions().y / (numberOfSitesY + numberOfAdditionalSites);
}

void GENERATE_SQUARE_LAYERS::addLayer(int layerIndex){
    for(int j = 0; j < numberOfSitesY; ++j){ //j=index in y-direction
        for(int k = 0; k < numberOfSitesX; ++k){ //k=index in x-direction
            CHARGED_PARTICLE newParticle(particleTemplate);
            newParticle.position = REAL_C(
                    dx * k + layerIndex * dx / 2, //displaced by dx/2 from lower layer
                    dy * j + layerIndex * dy / 2, //displaced by dy/2 from lower layer
                    zMin + layerIndex * dz
            );
            newParticle.index = particleIndex;
            particleIndex++;
            particle.push_back(newParticle);
        }
    }
}

void GENERATE_SQUARE_LAYERS::addIncommensurableLayer(int layerIndex){
    for(int j = 0; j < numberOfSitesY + numberOfAdditionalSites; ++j){
        for(int k = 0; k < numberOfSitesX + numberOfAdditionalSites; ++k){
            CHARGED_PARTICLE newParticle(particleTemplate);
            newParticle.position = REAL_C(
                    dxAdd * k + layerIndex * dxAdd / 2,
                    dyAdd * j + layerIndex * dyAdd / 2,
                    zMin + layerIndex *dz
            );
            newParticle.index = particleIndex;
            particleIndex++;
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

int GENERATE_SQUARE_LAYERS::getNumberOfParticles() const{
    int totalNumberOfSites = numberOfSitesX + numberOfAdditionalSites;
    return totalNumberOfSites * totalNumberOfSites * numberOfLayers;
}

CHARGED_PARTICLE GENERATE_SQUARE_LAYERS::getParticleTemplate() const{
    return particleTemplate;
}

SLIT_PORE_BOX GENERATE_SQUARE_LAYERS::getSimBox() const{
    return simBox;
}

ostream& operator<<(ostream& os, const GENERATE_SQUARE_LAYERS& gsl){
    os << "GENERATE_SQUARE_LAYERS(";
    os << "numberOfLayers: " << gsl.numberOfLayers;
    os << ", numberOfSites: " << gsl.numberOfSitesX;
    os << ", numberOfAdditionalSites: " << gsl.numberOfAdditionalSites;
    os << ")";
    return os;
}
