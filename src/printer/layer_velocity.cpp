//
// Created by mhuels on 4/30/20.
//

#include "layer_velocity.h"
#include "boost/format.hpp"

using namespace boost;

LAYER_VELOCITY_PRINTER::LAYER_VELOCITY_PRINTER(SHEARED_SLITPORE_SYSTEM* sysIn): PRINTER(LAYER_VELOCITIES_OUT){
    sys = sysIn;
    printHeader();
}

LAYER_VELOCITY_PRINTER::LAYER_VELOCITY_PRINTER(SHEARED_SLITPORE_SYSTEM* sysIn, string filename): PRINTER(filename){
    sys = sysIn;
    printHeader();
}

LAYER_VELOCITY_PRINTER::~LAYER_VELOCITY_PRINTER(){
}

void LAYER_VELOCITY_PRINTER::printHeader(){
    char comment = getComment();
    *this << comment << "i: timestep (dt = " << sys->getTimeStepSize() << " tB)" << endl;
    *this << comment << "V_i(n): average velocity of layer n (in direction i=x,y,z) [d/tB]" << endl;
    *this << comment << format(format_lh) % "i";
    numberOfLayers = round(sys->getSimulationBox().getDimensions().z);
    vector<string> dir{"x", "y", "z"};
    for(int i = 0; i < numberOfLayers; i++){
        for(int j = 0; j < dir.size(); j++){
            *this << format(format_fh) % ("V_" + dir[j] + "(" + to_string(i) + ")");
        }
    }
    *this << "\n";
}

void LAYER_VELOCITY_PRINTER::printLine(){
    meanLayerVelocities = sys->getMeanLayerVelocities();
    long timestep = sys->getTimestep() - 2; //previous timestep + equationOfMotion already incremented timestep by one
    *this << format(format_l) % timestep;
    for(int i = 0; i < meanLayerVelocities.size(); i++){
        *this << format(format_f) % meanLayerVelocities[i].x;
        *this << format(format_f) % meanLayerVelocities[i].y;
        *this << format(format_f) % meanLayerVelocities[i].z;
    }
    *this << "\n";
}
