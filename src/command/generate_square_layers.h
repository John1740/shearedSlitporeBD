#ifndef GENERATE_SQUARE_LAYERS_H
#define GENERATE_SQUARE_LAYERS_H

#include "../systems/confined_brownian_particles.h"
#include "../struct/slit_pore_box.h"

class GENERATE_SQUARE_LAYERS{
public:
    int numberOfLayers;
    int numberOfSites;
    int numberOfAdditionalSites;
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
    GENERATE_SQUARE_LAYERS();
    GENERATE_SQUARE_LAYERS(int N, double dWall, double density);

    GENERATE_SQUARE_LAYERS& setup(int N, double dWall, double density);

    CONFINED_BROWNIAN_PARTICLES generate();

    //setter
    GENERATE_SQUARE_LAYERS& setParticleProperties(const CHARGED_PARTICLE& particle);
    GENERATE_SQUARE_LAYERS& setParticleProperties(double charge, double diameter, int species);

    //getter
    int getNumberOfParticles() const;
    CHARGED_PARTICLE getParticleTemplate() const;
    SLIT_PORE_BOX getSimBox() const;

    friend ostream& operator<<(ostream& os, const GENERATE_SQUARE_LAYERS& gsl);
};

#endif // GENERATE_SQUARE_LAYERS_H
