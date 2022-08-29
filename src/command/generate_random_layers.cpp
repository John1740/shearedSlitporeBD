#include "generate_random_layers.h"
#include <time.h>
#include "../struct/layers.h"

GENERATE_RANDOM_LAYERS::GENERATE_RANDOM_LAYERS(){
    numberOfAdditionalSites = 0;
    setup(NUMBER_OF_PARTICLES, D_WALL, DENSITY);
}

GENERATE_RANDOM_LAYERS::GENERATE_RANDOM_LAYERS(int N, double dWall, double density){
    numberOfAdditionalSites = 0;
    setup(N, dWall, density);
}

GENERATE_RANDOM_LAYERS& GENERATE_RANDOM_LAYERS::setup(int N, double dWall, double density){

    numberOfLayers = 2;//round(simBox.getDimensions().z);
    //numberOfSites = sqrt(particle.size() / numberOfLayers);
    numberOfSitesX= round(sqrt(N/2));
    numberOfSitesY=numberOfSitesX;
    //numberOfSitesX=28;
    //numberOfSitesY=26;
    N=2*numberOfSitesX*numberOfSitesY;
    double sitesLength=sqrt(2/density/dWall);
    simBox = SLIT_PORE_BOX(N / density, dWall,numberOfSitesX*sitesLength,numberOfSitesY*sitesLength);
    numberOfParticles=N;

    particle.resize(N);


    particleTemplate.charge = CHARGE;
    particleTemplate.diameter = DIAMETER;
    particleTemplate.species = 0;
    particleIndex = 0;
    return *this;

}

SHEARED_SLITPORE_SYSTEM  GENERATE_RANDOM_LAYERS::generate(){
    setLatticePeriodicity();
    particle.clear();

    placeRandomParticles();

    SHEARED_SLITPORE_SYSTEM  sys;
    *(sys.simulationBox()) = simBox;
    sys.setParticleList(particle);
    for(int i = 0; i < sys.getNumberOfParticles(); ++i){
        sys.particles[i].setBoxPosition(simBox);
        sys.particles[i].position = sys.particles[i].boxPosition;
    }

    return sys;
}

void GENERATE_RANDOM_LAYERS::setLatticePeriodicity(){
    LAYERS layers(simBox);
    srand(time(NULL));
    double xPos,yPos,zPos;
    for(int i = 0; i < numberOfParticles; ++i){


        xPos=(double)rand() / (double)RAND_MAX*simBox.getDimensions().x-simBox.getDimensions().x/2.0;
        yPos=(double)rand() / (double)RAND_MAX*simBox.getDimensions().y-simBox.getDimensions().y/2.0;
        zPos=(double)rand() / (double)RAND_MAX*simBox.getDimensions().z-simBox.getDimensions().z/2.0;

        CHARGED_PARTICLE newParticle(particleTemplate);
        newParticle.position = REAL_C(
                xPos, //displaced by dx/2 from lower layer
                yPos, //displaced by dy/4 from lower layer
                zPos
        );
        newParticle.index = particleIndex;
        particleIndex++;
        particle.push_back(newParticle);


    }
    //dxAdd = simBox.getDimensions().x / (numberOfSites + numberOfAdditionalSites);
    //dyAdd = dxAdd;
}

void GENERATE_RANDOM_LAYERS::placeRandomParticles(){



}


void GENERATE_RANDOM_LAYERS::addLayer(int layerIndex){
    for(int j = 0; j < Ny; ++j){ //j=index in y-direction
        for(int k = 0; k < Nx; ++k){ //k=index in x-direction

            CHARGED_PARTICLE newParticle(particleTemplate);
            newParticle.position = REAL_C(
                    dx * k + layerIndex * dx / 2, //displaced by dx/2 from lower layer
                    dy * j + layerIndex * dy / 4, //displaced by dy/4 from lower layer
                    zMin + layerIndex * dz
            );
            newParticle.index = particleIndex;
            particleIndex++;
            particle.push_back(newParticle);

            CHARGED_PARTICLE newParticle2(particleTemplate);
            newParticle2.position = REAL_C(
                    dx * (k + 0.5) + layerIndex * dx / 2, //displaced by dx/2 from lower layer
                    dy * (j + 0.5) + layerIndex * dy / 4, //displaced by dy/4 from lower layer
                    zMin + layerIndex * dz
            );
            newParticle2.index = particleIndex;
            particleIndex++;
            particle.push_back(newParticle2);
        }
    }
}



void GENERATE_RANDOM_LAYERS::addIncommensurableLayer(int layerIndex){
    for(int j = 0; j < Ny; ++j){ //j=index in y-direction
        for(int k = 0; k < Nx; ++k){ //k=index in x-direction

            CHARGED_PARTICLE newParticle(particleTemplate);
            newParticle.position = REAL_C(
                    dx * k + layerIndex * dx / 2, //displaced by dx/2 from lower layer
                    dy * j + layerIndex * dy / 4, //displaced by dy/4 from lower layer
                    zMin + layerIndex * dz
            );
            newParticle.index = particleIndex;
            particleIndex++;
            particle.push_back(newParticle);

            CHARGED_PARTICLE newParticle2(particleTemplate);
            newParticle2.position = REAL_C(
                    dx * (k + 0.5) + layerIndex * dx / 2, //displaced by dx/2 from lower layer
                    dy * (j + 0.5) + layerIndex * dy / 4, //displaced by dy/4 from lower layer
                    zMin + layerIndex * dz
            );
            newParticle2.index = particleIndex;
            particleIndex++;
            particle.push_back(newParticle2);
        }
    }
}


GENERATE_RANDOM_LAYERS& GENERATE_RANDOM_LAYERS::setParticleProperties(const CHARGED_PARTICLE& particle){
    particleTemplate = particle;
    return *this;
}

GENERATE_RANDOM_LAYERS& GENERATE_RANDOM_LAYERS::setParticleProperties(double charge, double diameter, int species){
    particleTemplate.charge = charge;
    particleTemplate.diameter = diameter;
    particleTemplate.species = species;
    return *this;
}

int GENERATE_RANDOM_LAYERS::getNumberOfParticles() const{
    int totalNumberOfSites = numberOfSites + numberOfAdditionalSites;
    return totalNumberOfSites * totalNumberOfSites * numberOfLayers;
}

CHARGED_PARTICLE GENERATE_RANDOM_LAYERS::getParticleTemplate() const{
    return particleTemplate;
}

SLIT_PORE_BOX GENERATE_RANDOM_LAYERS::getSimBox() const{
    return simBox;
}

ostream& operator<<(ostream& os, const GENERATE_RANDOM_LAYERS& gsl){
    os << "GENERATE_RANDOM_LAYERS(";
    os << "numberOfLayers: " << gsl.numberOfLayers;
    os << ", numberOfSites: " << gsl.numberOfSites;
    os << ", numberOfAdditionalSites: " << gsl.numberOfAdditionalSites;
    os << ")";
    return os;
}
