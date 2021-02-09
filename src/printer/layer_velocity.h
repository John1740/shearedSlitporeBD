//
// Created by mhuels on 4/30/20.
//

#ifndef SHEAREDSLITPOREBD_LAYER_VELOCITY_H
#define SHEAREDSLITPOREBD_LAYER_VELOCITY_H

#include "../struct/cartesian_c.h"
#include "../systems/sheared_slitpore_system.h"
#include <vector>

class LAYER_VELOCITY_PRINTER: public PRINTER{
private:
    SHEARED_SLITPORE_SYSTEM* sys;
    REAL_C meanVelocity;
    int numberOfLayers;
    vector<REAL_C> meanLayerVelocities;
public:
    LAYER_VELOCITY_PRINTER(SHEARED_SLITPORE_SYSTEM* sysIn);
    LAYER_VELOCITY_PRINTER(SHEARED_SLITPORE_SYSTEM* sysIn, string filename);
    ~LAYER_VELOCITY_PRINTER();

    void printHeader();
    void printLine();
};

#endif //SHEAREDSLITPOREBD_LAYER_VELOCITY_H
