//
// Created by
//

#ifndef SHEAREDSLITPOREBD_Z_DENSITY_DISTRIBUTION_H
#define SHEAREDSLITPOREBD_Z_DENSITY_DISTRIBUTION_H

#include "../struct/layers.h"
#include "../systems/confined_brownian_particles.h"

class Z_DENSITY_DISTRIBUTION{
private:
    LAYERS layers;
    SLIT_PORE_BOX simBox;
    vector<CHARGED_PARTICLE> particle;
    double nob;
    double db;
    double dr;
    double zrange;
    int numberOfParitcles;
    vector<double> zCoordinate;
    vector<double> zDensityDistribution;

public:
    Z_DENSITY_DISTRIBUTION();
    Z_DENSITY_DISTRIBUTION(CONFINED_BROWNIAN_PARTICLES& sys);
    Z_DENSITY_DISTRIBUTION(CONFINED_BROWNIAN_PARTICLES& sys, double nob);

    Z_DENSITY_DISTRIBUTION& setup(CONFINED_BROWNIAN_PARTICLES& sys, double bob);
    Z_DENSITY_DISTRIBUTION& calculateZDensityDistribution();

    Z_DENSITY_DISTRIBUTION& print(string filename, bool overwrite=false, string header="");
    friend ostream& operator<<(ostream& os, const  Z_DENSITY_DISTRIBUTION& zDistribution);

    };

#endif //SHEAREDSLITPOREBD_Z_DENSITY_DISTRIBUTION_H