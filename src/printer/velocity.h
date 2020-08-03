//
// Created by mhuels on 4/30/20.
//

#ifndef SHEAREDSLITPOREBD_VELOCITY_H
#define SHEAREDSLITPOREBD_VELOCITY_H

#include "../struct/cartesian_c.h"
#include "../systems/sheared_slitpore_system.h"
#include <vector>

class VELOCITY_PRINTER{
private:
    SHEARED_SLITPORE_SYSTEM* sys;
    REAL_C meanVelocity;
    int numberOfLayers;
    vector<REAL_C> meanLayerVelocities;
public:
    VELOCITY_PRINTER(SHEARED_SLITPORE_SYSTEM* sysIn);
    VELOCITY_PRINTER(SHEARED_SLITPORE_SYSTEM* sysIn, string filename);
    ~VELOCITY_PRINTER();
    
    PRINTER printer;
    string format_l = "% 4.5f\t";   //line format
    string format_h = "%8s\t";  //header format
    
    void printHeader();
    void printLine();
};

#endif //SHEAREDSLITPOREBD_VELOCITY_H
