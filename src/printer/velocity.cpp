//
// Created by mhuels on 4/30/20.
//

#include "velocity.h"
#include "boost/format.hpp"
using namespace boost;


VELOCITY_PRINTER::VELOCITY_PRINTER(CONFINED_BROWNIAN_PARTICLES* sysIn){
    sys = sysIn;
    printer.setFilename("velocities.out");
    printer.removeFile();
    printHeader();
}

VELOCITY_PRINTER::VELOCITY_PRINTER(CONFINED_BROWNIAN_PARTICLES* sysIn, string filename){
    sys = sysIn;
    printer.setFilename(filename);
    printer.removeFile();
    printHeader();
}

VELOCITY_PRINTER::~VELOCITY_PRINTER(){

}

void VELOCITY_PRINTER::printHeader(){
    printer.printLine("#v_i: average velocity of all particles (in direction i=x,y,z)");
    printer.printLine("#v_i(n): average velocity of layer n (in direction i=x,y,z)");
    printer.print(format("#%5s\t") % "i");
    numberOfLayers = round(sys->getSimulationBox().getDimensions().z);
    vector<string> dir{"x", "y", "z"};
    for(int j = 0; j < dir.size(); j++){
        printer.print(format(format_h.c_str()) % ("v_" + dir[j]).c_str());
    }
    for(int i = 0; i < numberOfLayers; i++){
        for(int j = 0; j < dir.size(); j++){
            printer.print(format(format_h.c_str()) % ("v_" + dir[j] + "(" + to_string(i) + ")"));
        }
    }
    printer.printLine("");
}

void VELOCITY_PRINTER::printLine(){
    meanVelocity = sys->getMeanVelocity();
    meanLayerVelocities = sys->getMeanLayerVelocities();
    long timestep = sys->getTimestep() - 2; //skip first step + equationOfMotion already incremented timestep by one
    printer.print(format("%6ld\t") % timestep);
    printer.print(format(format_l.c_str()) % meanVelocity.x);
    printer.print(format(format_l.c_str()) % meanVelocity.y);
    printer.print(format(format_l.c_str()) % meanVelocity.z);
    for(int i = 0; i < meanLayerVelocities.size(); i++){
        printer.print(format(format_l.c_str()) % meanLayerVelocities[i].x);
        printer.print(format(format_l.c_str()) % meanLayerVelocities[i].y);
        printer.print(format(format_l.c_str()) % meanLayerVelocities[i].z);
    }
    printer.printLine("");
}
