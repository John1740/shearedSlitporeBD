//
// Created by mhuels on 4/30/20.
//

#include "velocity.h"
#include "boost/format.hpp"
using namespace boost;


VELOCITY_PRINTER::VELOCITY_PRINTER(SHEARED_SLITPORE_SYSTEM* sysIn){
    sys = sysIn;
    printer.setFilename(VELOCITIES_OUT);
    printHeader();
}

VELOCITY_PRINTER::VELOCITY_PRINTER(SHEARED_SLITPORE_SYSTEM* sysIn, string filename){
    sys = sysIn;
    printer.setFilename(filename);
    printHeader();
}

VELOCITY_PRINTER::~VELOCITY_PRINTER(){

}

void VELOCITY_PRINTER::printHeader(){
    char comment = printer.getComment();
    printer << comment << "v_i: average velocity of all particles (in direction i=x,y,z)" << endl;
    printer << comment << "v_i(n): average velocity of layer n (in direction i=x,y,z)" << endl;
    printer << comment << format("%5s\t") % "i";
    printer << format(format_h.c_str()) % "shearRate";
    numberOfLayers = round(sys->getSimulationBox().getDimensions().z);
    vector<string> dir{"x", "y", "z"};
    for(int j = 0; j < dir.size(); j++){
        printer << format(format_h.c_str()) % ("v_" + dir[j]).c_str();
    }
    for(int i = 0; i < numberOfLayers; i++){
        for(int j = 0; j < dir.size(); j++){
            printer << format(format_h.c_str()) % ("v_" + dir[j] + "(" + to_string(i) + ")");
        }
    }
    printer << "\n";
}

void VELOCITY_PRINTER::printLine(){
    meanVelocity = sys->getMeanVelocity();
    meanLayerVelocities = sys->getMeanLayerVelocities();
    long timestep = sys->getTimestep() - 2; //previous timestep + equationOfMotion already incremented timestep by one
    printer << format("%6ld\t") % timestep;
    printer << format(format_l.c_str()) % sys->getCurrentShearRate();
    printer << format(format_l.c_str()) % meanVelocity.x;
    printer << format(format_l.c_str()) % meanVelocity.y;
    printer << format(format_l.c_str()) % meanVelocity.z;
    for(int i = 0; i < meanLayerVelocities.size(); i++){
        printer << format(format_l.c_str()) % meanLayerVelocities[i].x;
        printer << format(format_l.c_str()) % meanLayerVelocities[i].y;
        printer << format(format_l.c_str()) % meanLayerVelocities[i].z;
    }
    printer << "\n";
}
