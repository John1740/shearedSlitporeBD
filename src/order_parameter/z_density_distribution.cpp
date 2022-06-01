//
// Created by
//

#include <boost/format.hpp>
#include "z_density_distribution.h"

namespace b = boost;

Z_DENSITY_DISTRIBUTION::Z_DENSITY_DISTRIBUTION(){
}

Z_DENSITY_DISTRIBUTION::Z_DENSITY_DISTRIBUTION(CONFINED_BROWNIAN_PARTICLES& sys){
    setup(sys, 10000);
}

Z_DENSITY_DISTRIBUTION::Z_DENSITY_DISTRIBUTION(CONFINED_BROWNIAN_PARTICLES& sys,double nOB){
    setup(sys, nOB);
}
Z_DENSITY_DISTRIBUTION&
Z_DENSITY_DISTRIBUTION::setup(CONFINED_BROWNIAN_PARTICLES& sys, double nob){
    simBox = sys.getSimulationBox();
    layers = LAYERS(simBox);
    particle = sys.getParticleList();
    return *this;
}

Z_DENSITY_DISTRIBUTION& Z_DENSITY_DISTRIBUTION::calculateZDensityDistribution(){
    //int numberOfLayers = layers.getNumberOfLayers();
    double currentZ;
    //zDensityDistribution.clear();
    //zDensityDistribution.resize(nob);
    zDensityDistribution.assign(nob, double(0.));
    zCoordinate.assign(nob, double(0.));
    zrange = simBox.getDimensions().z;
    db = nob / zrange;
    dr = zrange / nob;
    numberOfParitcles = particle.size();
    for(int i = 0; i < numberOfParitcles; i++){
        currentZ = particle[i].boxPosition.z;
        int j = round((currentZ + zrange / 2) * db);
        zDensityDistribution[j] += 1;
        zCoordinate[i]=-zrange/2+dr*i;
    }
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
    os << "first line: z coordinate [diameter]" << endl;
    os << "second line: particle density at z [1/diameter]" << endl;

    //data
    for(int r = 0; r < zdis.nob; r++){
        os << b::format("% 2.5f") % zdis.zCoordinate[r];
        os << "\t";
    }
    os << "\n";

    for(int r = 0; r < zdis.nob; r++){
        os << b::format("% 2.5f") % zdis.zDensityDistribution[r];
        os << "\t";
    }
    os << "\n";

    return os;




}