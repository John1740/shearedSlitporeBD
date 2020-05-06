//
// Created by mhuels on 4/30/20.
//

#ifndef SHEAREDSLITPOREBD_VELOCITY_H
#define SHEAREDSLITPOREBD_VELOCITY_H

#include "../struct/cartesian_coordinate.h"
#include "../systems/confined_brownian_particles.h"
#include <vector>

class VELOCITY_PRINTER{
private:
    CONFINED_BROWNIAN_PARTICLES* sys;
    CARTESIAN_COORDINATE meanVelocity;
    int numberOfLayers;
    vector<CARTESIAN_COORDINATE> meanLayerVelocities;
public:
    VELOCITY_PRINTER(CONFINED_BROWNIAN_PARTICLES* sysIn);
    VELOCITY_PRINTER(CONFINED_BROWNIAN_PARTICLES* sysIn, string filename);
    ~VELOCITY_PRINTER();
    
    PRINTER printer;
    string format_l = "% 4.5f\t";   //line format
    string format_h = "%8s\t";  //header format
    
    void printHeader();
    void printLine();
};

#endif //SHEAREDSLITPOREBD_VELOCITY_H
