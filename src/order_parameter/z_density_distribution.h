//
// Created by
//

#ifndef SHEAREDSLITPOREBD_Z_DENSITY_DISTRIBUTION_H
#define SHEAREDSLITPOREBD_Z_DENSITY_DISTRIBUTION_H

#include "../struct/layers.h"
#include "../systems/confined_brownian_particles.h"

class Z_DENSITY_DISTRIBUTION{
    // Observable to calculate the particle density over z. Input particle positions via CONFINED_BROWNIAN_PARTICLES
    // class and optional dz. positions are printed via << operator to "zDensity.out"
private:
    LAYERS layers;
    SLIT_PORE_BOX simBox;
    vector<CHARGED_PARTICLE> particle;
    int nob;    // number ob bins
    double db;  // inverse length of one bin
    double dz;  // length of one bin
    double zrange;  // length of z axis
    int numberOfParitcles;
    vector<double> zCoordinate;
    vector<double> zDensityDistribution;

public:
    Z_DENSITY_DISTRIBUTION();
    Z_DENSITY_DISTRIBUTION(CONFINED_BROWNIAN_PARTICLES& sys);
    Z_DENSITY_DISTRIBUTION(CONFINED_BROWNIAN_PARTICLES& sys, double dz);
    Z_DENSITY_DISTRIBUTION& setup(CONFINED_BROWNIAN_PARTICLES& sys, double dz);
    Z_DENSITY_DISTRIBUTION& calculateZDensityDistribution();

    Z_DENSITY_DISTRIBUTION& print(string filename, bool overwrite=false, string header="");
    friend ostream& operator<<(ostream& os, const  Z_DENSITY_DISTRIBUTION& zDistribution);

    };

#endif //SHEAREDSLITPOREBD_Z_DENSITY_DISTRIBUTION_H