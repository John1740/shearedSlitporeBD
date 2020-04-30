//
// Created by mhuels on 4/30/20.
//

#ifndef SHEAREDSLITPOREBD_VELOCITY_H
#define SHEAREDSLITPOREBD_VELOCITY_H

#include "../struct/cartesian_coordinate.h"
#include "../systems/confined_brownian_particles.h"
#include <vector>

class VELOCITY{
private:
    CARTESIAN_COORDINATE meanVelocity;
    vector<CARTESIAN_COORDINATE> meanLayerVelocities;
    string filename = "velocities.out";
    string format_l = "% 4.5f\t";   //line format
    string format_h = "%8s\t";  //header format
    FILE* pFile;
public:
    VELOCITY();
    VELOCITY(string filename);
    VELOCITY(string filename, string format_l);
    VELOCITY(string filename, string format_l, string format_h);
    ~VELOCITY();
    
    void printHeader();
    void printLine(CONFINED_BROWNIAN_PARTICLES& sys, int timeStep);
};

#endif //SHEAREDSLITPOREBD_VELOCITY_H
