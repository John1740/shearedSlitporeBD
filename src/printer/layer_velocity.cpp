//
// Created by mhuels on 4/30/20.
//

#include "layer_velocity.h"
#include "boost/format.hpp"

using namespace boost;

VELOCITY_PRINTER::VELOCITY_PRINTER(SHEARED_SLITPORE_SYSTEM* sysIn): PRINTER(LAYER_VELOCITIES_OUT){
    sys = sysIn;
    printHeader();
}

VELOCITY_PRINTER::VELOCITY_PRINTER(SHEARED_SLITPORE_SYSTEM* sysIn, string filename): PRINTER(filename){
    sys = sysIn;
    printHeader();
}

VELOCITY_PRINTER::~VELOCITY_PRINTER(){
}

void VELOCITY_PRINTER::printHeader(){
    char comment = getComment();
    *this << comment << "i: timestep (dt = " << sys->getTimeStepSize() << " tB)" << endl;
    *this << comment << "dy/dt: shear rate [1/tB]" << endl;
    *this << comment << "v_i: average velocity of all layers (in direction i=x,y,z) [d/tB]" << endl;
    *this << comment << "v_i(n): average velocity of layer n (in direction i=x,y,z) [d/tB]" << endl;
    *this << comment << format("%5s\t") % "i";
    *this << format(format_h.c_str()) % "dy/dt";
    numberOfLayers = round(sys->getSimulationBox().getDimensions().z);
    vector<string> dir{"x", "y", "z"};
    for(int j = 0; j < dir.size(); j++){
        *this << format(format_h.c_str()) % (format("v_%s") % dir[j]); // ("v_" + dir[j]).c_str();
    }
    for(int i = 0; i < numberOfLayers; i++){
        for(int j = 0; j < dir.size(); j++){
            *this << format(format_h.c_str()) % ("v_" + dir[j] + "(" + to_string(i) + ")");
        }
    }
    *this << "\n";
}

void VELOCITY_PRINTER::printLine(){
    meanVelocity = sys->getMeanVelocity();
    meanLayerVelocities = sys->getMeanLayerVelocities();
    long timestep = sys->getTimestep() - 2; //previous timestep + equationOfMotion already incremented timestep by one
    *this << format("%6ld\t") % timestep;
    *this << format(format_l.c_str()) % sys->getCurrentShearRate();
    *this << format(format_l.c_str()) % meanVelocity.x;
    *this << format(format_l.c_str()) % meanVelocity.y;
    *this << format(format_l.c_str()) % meanVelocity.z;
    for(int i = 0; i < meanLayerVelocities.size(); i++){
        *this << format(format_l.c_str()) % meanLayerVelocities[i].x;
        *this << format(format_l.c_str()) % meanLayerVelocities[i].y;
        *this << format(format_l.c_str()) % meanLayerVelocities[i].z;
    }
    *this << "\n";
}
