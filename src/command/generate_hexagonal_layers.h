#ifndef GENERATE_HEXAGONAL_LAYERS_H
#define GENERATE_HEXAGONAL_LAYERS_H

#include "../systems/confined_brownian_particles.h"
#include "../struct/slit_pore_box.h"

class GENERATE_HEXAGONAL_LAYERS{
    // Class to calculate particle positions for Hexagonal Layers with given parameters
    // Used in executable generateHexagonalLayers. Input is number of particles, density
    // and wall diameter. After initialisation particle positions are stored in
    // particles[i].position.
public:
    int numberOfLayers;
    int numberOfSites;
    int numberOfAdditionalSites;
    int Nx;
    int Ny;
    double SitesLength;
private:
    vector<CHARGED_PARTICLE> particle;
    SLIT_PORE_BOX simBox;
    double dx, dy, dz, dxAdd, dyAdd;
    double zMin;
    CHARGED_PARTICLE particleTemplate;
    int particleIndex = 0;

    void setLatticePeriodicity();
    void addLayer(int layerIndex);
    void addIncommensurableLayer(int layerIndex);

public:
    //constructors
    GENERATE_HEXAGONAL_LAYERS();
    GENERATE_HEXAGONAL_LAYERS(int N, double dWall, double density);

    GENERATE_HEXAGONAL_LAYERS& setup(int N, double dWall, double density);

    CONFINED_BROWNIAN_PARTICLES generate();

    //setter
    GENERATE_HEXAGONAL_LAYERS& setParticleProperties(const CHARGED_PARTICLE& particle);
    GENERATE_HEXAGONAL_LAYERS& setParticleProperties(double charge, double diameter, int species);

    //getter
    int getNumberOfParticles() const;
    CHARGED_PARTICLE getParticleTemplate() const;
    SLIT_PORE_BOX getSimBox() const;

    friend ostream& operator<<(ostream& os, const GENERATE_HEXAGONAL_LAYERS& gsl);
};

#endif // GENERATE_HEXAGONAL_LAYERS_H
