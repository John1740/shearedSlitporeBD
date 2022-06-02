//
// Created by mhuels on 12/14/20.
//

#include "layer_position.h"
#include "boost/format.hpp"

using namespace boost;

LAYER_POSITION_PRINTER::LAYER_POSITION_PRINTER(SHEARED_SLITPORE_SYSTEM* sysIn): PRINTER(LAYER_POSITIONS_OUT){
    sys = sysIn;
    printHeader();
}

LAYER_POSITION_PRINTER::LAYER_POSITION_PRINTER(SHEARED_SLITPORE_SYSTEM* sysIn, string filename): PRINTER(filename){
    sys = sysIn;
    printHeader();
}

LAYER_POSITION_PRINTER::~LAYER_POSITION_PRINTER(){
}

void LAYER_POSITION_PRINTER::printHeader(){
    char comment = getComment();
    *this << comment << "i: timestep (dt = " << sys->getTimeStepSize() << " tB)" << endl;
    *this << comment << "R_i(n): position of layer n (in direction i=x,y,z) [d]" << endl;
    *this << comment << format(format_lh) % "i";
    numberOfLayers = 2;//round(sys->getSimulationBox().getDimensions().z);
    vector<string> dir{"x", "y", "z"};
    for(int i = 0; i < numberOfLayers; i++){
        for(int j = 0; j < dir.size(); j++){
            *this << format(format_fh) % ("R_" + dir[j] + "(" + to_string(i) + ")");
        }
    }
    *this << "\n";
}

void LAYER_POSITION_PRINTER::printLine(){
    meanLayerPositions = sys->getMeanLayerPositions();
    long timestep = sys->getTimestep();
    *this << format(format_l) % timestep;
    for(int i = 0; i < meanLayerPositions.size(); i++){
        *this << format(format_f) % meanLayerPositions[i].x;
        *this << format(format_f) % meanLayerPositions[i].y;
        *this << format(format_f) % meanLayerPositions[i].z;
    }
    *this << "\n";
}
