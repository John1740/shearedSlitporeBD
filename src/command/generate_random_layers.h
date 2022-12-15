#ifndef GENERATE_RANDOM_LAYERS_H
#define GENERATE_RANDOM_LAYERS_H

#include "../systems/confined_brownian_particles.h"
#include "../struct/slit_pore_box.h"
#include "../systems/sheared_slitpore_system.h"

class GENERATE_RANDOM_LAYERS{

public:
    int numberOfLayers;
    int numberOfSites;
    int numberOfAdditionalSites;
    int numberOfParticles;
    int numberOfSitesX;
    int numberOfSitesY;

    double SitesLength;
private:
    vector<CHARGED_PARTICLE> particle;
    SLIT_PORE_BOX simBox;
    double zMin;
    double dz;
    CHARGED_PARTICLE particleTemplate;
    int particleIndex = 0;

    void setLatticePeriodicity();
    void placeRandomParticles();
    void placeRandomLayers();
    void addLayer(int layerIndex);
    void addIncommensurableLayer(int layerIndex);
    bool randomLayers= false;

public:
    //constructors
    GENERATE_RANDOM_LAYERS();
    GENERATE_RANDOM_LAYERS(int N, double dWall, double density, bool layers=false);

    GENERATE_RANDOM_LAYERS& setup(int N, double dWall, double density);

    SHEARED_SLITPORE_SYSTEM generate();

    //setter
    GENERATE_RANDOM_LAYERS& setParticleProperties(const CHARGED_PARTICLE& particle);
    GENERATE_RANDOM_LAYERS& setParticleProperties(double charge, double diameter, int species);

    //getter
    int getNumberOfParticles() const;
    CHARGED_PARTICLE getParticleTemplate() const;
    SLIT_PORE_BOX getSimBox() const;

    friend ostream& operator<<(ostream& os, const GENERATE_RANDOM_LAYERS& gsl);
};

#endif // GENERATE_RANDOM_LAYERS_H
