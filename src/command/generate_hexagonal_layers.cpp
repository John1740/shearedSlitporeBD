#include "generate_hexagonal_layers.h"

#include "../struct/layers.h"

GENERATE_HEXAGONAL_LAYERS::GENERATE_HEXAGONAL_LAYERS(){
    numberOfAdditionalSites = 0;
    setup(NUMBER_OF_PARTICLES, D_WALL, DENSITY);
}

GENERATE_HEXAGONAL_LAYERS::GENERATE_HEXAGONAL_LAYERS(int N, double dWall, double density){
    numberOfAdditionalSites = 0;
    setup(N, dWall, density);
}

GENERATE_HEXAGONAL_LAYERS& GENERATE_HEXAGONAL_LAYERS::setup(int N, double dWall, double density){
    numberOfLayers = 2; // The number of generated Layers, could be changed but ShearedSliporeBD only works with 2

    // Hexagonal 2D unit-cell is not square with dx*sqrt(3)=dy and includes 2 particles one at (0,0)
    // one at (0.5*dx,0.5*dy). Therefore the number of unit cells in x and y must first be calculated
    // to be as square as possible and to keep the given number of particles N close to its original
    // value.

    Nx= round(sqrt(N/2/numberOfLayers* sqrt(3))); // Number of unit cells in x direction in one layer
    Ny= round(Nx / sqrt(3));                         // Number of unit cells in y direction in one layer
    N=Nx*Ny*2*numberOfLayers;                                             // New total Number of Particles

    //N=((round(sqrt(N/2)/2)*2)*(round(sqrt(N/2)/2)*2))*2;
    SitesLength = sqrt(N / density / (dWall * sqrt(3) * Nx * Ny));  // Unit cell length in x(dx)

    // Initialize Simulation Box to store box parameters
    simBox = SLIT_PORE_BOX(N / density, dWall,SitesLength * Nx,SitesLength * sqrt(3) * Ny);


    particle.resize(N);


    numberOfSites = sqrt(particle.size() / numberOfLayers);
    particleTemplate.charge = CHARGE;
    particleTemplate.diameter = DIAMETER;
    particleTemplate.species = 0;
    particleIndex = 0;
    return *this;

}

CONFINED_BROWNIAN_PARTICLES GENERATE_HEXAGONAL_LAYERS::generate(){
    setLatticePeriodicity();
    particle.clear();

    for(int i = 0; i < numberOfLayers - 1; ++i){
        addLayer(i);
    }
    addIncommensurableLayer(numberOfLayers - 1);

    CONFINED_BROWNIAN_PARTICLES sys;
    *(sys.simulationBox()) = simBox;
    sys.setParticleList(particle);

    return sys;
}

void GENERATE_HEXAGONAL_LAYERS::setLatticePeriodicity(){
    LAYERS layers(simBox);
    zMin = layers.getZMin();
    dx = SitesLength;
    dy = SitesLength * sqrt(3);
    dz = layers.getLayerThickness();

    //dxAdd = simBox.getDimensions().x / (numberOfSites + numberOfAdditionalSites);
    //dyAdd = dxAdd;
}

void GENERATE_HEXAGONAL_LAYERS::addLayer(int layerIndex){
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


void GENERATE_HEXAGONAL_LAYERS::addIncommensurableLayer(int layerIndex){
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


GENERATE_HEXAGONAL_LAYERS& GENERATE_HEXAGONAL_LAYERS::setParticleProperties(const CHARGED_PARTICLE& particle){
    particleTemplate = particle;
    return *this;
}

GENERATE_HEXAGONAL_LAYERS& GENERATE_HEXAGONAL_LAYERS::setParticleProperties(double charge, double diameter, int species){
    particleTemplate.charge = charge;
    particleTemplate.diameter = diameter;
    particleTemplate.species = species;
    return *this;
}

int GENERATE_HEXAGONAL_LAYERS::getNumberOfParticles() const{
    int totalNumberOfSites = numberOfSites + numberOfAdditionalSites;
    return totalNumberOfSites * totalNumberOfSites * numberOfLayers;
}

CHARGED_PARTICLE GENERATE_HEXAGONAL_LAYERS::getParticleTemplate() const{
    return particleTemplate;
}

SLIT_PORE_BOX GENERATE_HEXAGONAL_LAYERS::getSimBox() const{
    return simBox;
}

ostream& operator<<(ostream& os, const GENERATE_HEXAGONAL_LAYERS& gsl){
    os << "GENERATE_HEXAGONAL_LAYERS(";
    os << "numberOfLayers: " << gsl.numberOfLayers;
    os << ", numberOfSites: " << gsl.numberOfSites;
    os << ", numberOfAdditionalSites: " << gsl.numberOfAdditionalSites;
    os << ")";
    return os;
}
