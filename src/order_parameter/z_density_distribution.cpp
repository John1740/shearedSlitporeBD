//
// Created by
//

#include <boost/format.hpp>
#include "z_density_distribution.h"

namespace b = boost;

Z_DENSITY_DISTRIBUTION::Z_DENSITY_DISTRIBUTION(){
}

Z_DENSITY_DISTRIBUTION::Z_DENSITY_DISTRIBUTION(CONFINED_BROWNIAN_PARTICLES& sys){
    setup(sys, 0.014);
}

Z_DENSITY_DISTRIBUTION::Z_DENSITY_DISTRIBUTION(CONFINED_BROWNIAN_PARTICLES& sys,double dz){
    setup(sys, dz);
}
Z_DENSITY_DISTRIBUTION&
Z_DENSITY_DISTRIBUTION::setup(CONFINED_BROWNIAN_PARTICLES& sys, double dz){
    // sets up parameters needed for calculation
    this->dz = dz;
    simBox = sys.getSimulationBox();
    layers = LAYERS(simBox);
    zrange = simBox.getDimensions().z;
    nob =round(zrange/dz)+1;
    particle = sys.getParticleList();
    return *this;
}

Z_DENSITY_DISTRIBUTION& Z_DENSITY_DISTRIBUTION::calculateZDensityDistribution(){
    // calculates z density by dividing z in bins according to dz and counts particles in bins.

    double currentZ;
    zDensityDistribution.assign(nob, double(0.));   // Vector to store density
    zCoordinate.assign(nob, double(0.));            // Vector to store associated z coordinates

    db = nob / zrange;
    numberOfParitcles = particle.size();


    for(int i = 0; i < numberOfParitcles; i++){
        currentZ = particle[i].boxPosition.z;
        int j = round((currentZ + zrange / 2) * db);
        zDensityDistribution[j] += 1;

    }

    for(int r = 0; r < nob; r++){
        zCoordinate[r]=-zrange/2+dz*r;
        zDensityDistribution[r] /= numberOfParitcles; // Normalization
    }
    /*
  */
    return *this;
}

Z_DENSITY_DISTRIBUTION& Z_DENSITY_DISTRIBUTION::print(string filename, bool overwrite, string header){

    PRINTER printer(filename);
    if(overwrite){
        printer.reset();
    }
    if(header.size() > 0){
        printer << string(3, printer.getComment()) << header << endl;
    }
    printer << *this;
    return *this;
}

ostream& operator<<(ostream& os, const Z_DENSITY_DISTRIBUTION& zdis){
    os << "# Number of Bins: " << zdis.nob <<endl;
    os << "# first col: z coordinate [diameter]" << endl;
    os << "# second col: particle density at z [1/diameter]" << endl;

    //data
    for(int r = 0; r < zdis.nob; r++){
        os << b::format("% 2.5f") % zdis.zCoordinate[r];
        os << "\t";
        os << b::format("% 2.5f") % zdis.zDensityDistribution[r];
        os << "\n";
    }


    return os;

}