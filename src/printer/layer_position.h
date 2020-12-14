//
// Created by mhuels on 12/14/20.
//

#ifndef SHEAREDSLITPOREBD_LAYER_POSITION_H
#define SHEAREDSLITPOREBD_LAYER_POSITION_H

#include "../struct/cartesian_c.h"
#include "../systems/sheared_slitpore_system.h"
#include <vector>

class LAYER_POSITION_PRINTER: public PRINTER{
private:
    SHEARED_SLITPORE_SYSTEM* sys;
    int numberOfLayers;
    vector<REAL_C> meanLayerPositions;
public:
    LAYER_POSITION_PRINTER(SHEARED_SLITPORE_SYSTEM* sysIn);
    LAYER_POSITION_PRINTER(SHEARED_SLITPORE_SYSTEM* sysIn, string filename);
    ~LAYER_POSITION_PRINTER();

    string format_l = "% 4.5f\t";   //line format
    string format_h = "%8s\t";  //header format

    void printHeader();
    void printLine();
};

#endif //SHEAREDSLITPOREBD_LAYER_POSITION_H
