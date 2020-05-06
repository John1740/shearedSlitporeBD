//
// Created by mhuels on 4/30/20.
//

#include "velocity.h"

VELOCITY::VELOCITY(CONFINED_BROWNIAN_PARTICLES* sysIn){
    sys = sysIn;
    pFile = fopen(filename.c_str(), "w");
    printHeader();
}

VELOCITY::VELOCITY(CONFINED_BROWNIAN_PARTICLES* sysIn, string filename){
    sys = sysIn;
    this->filename = filename;
    pFile = fopen(filename.c_str(), "w");
    printHeader();
}

VELOCITY::VELOCITY(CONFINED_BROWNIAN_PARTICLES* sysIn, string filename, string format_l){
    sys = sysIn;
    this->filename = filename;
    this->format_l = format_l;
    pFile = fopen(filename.c_str(), "w");
    printHeader();
}

VELOCITY::VELOCITY(CONFINED_BROWNIAN_PARTICLES* sysIn, string filename, string format_l, string format_h){
    sys = sysIn;
    this->filename = filename;
    this->format_l = format_l;
    this->format_h = format_h;
    pFile = fopen(filename.c_str(), "w");
    printHeader();
}

VELOCITY::~VELOCITY(){
    fclose(pFile);
}

void VELOCITY::printHeader(){
    fprintf(pFile, "#v_i: average velocity of all particles (in direction i=x,y,z)\n");
    fprintf(pFile, "#v_i(n): average velocity of layer n (in direction i=x,y,z)\n");
    fprintf(pFile, "#%5s\t", "i");
    numberOfLayers = round(sys->getSimulationBox().getDimensions().z);
    vector<string> dir{"x", "y", "z"};
    for(int j = 0; j < dir.size(); j++){
        fprintf(pFile, format_h.c_str(), ("v_" + dir[j]).c_str());
    }
    for(int i = 0; i < numberOfLayers; i++){
        for(int j = 0; j < dir.size(); j++){
            fprintf(pFile, format_h.c_str(), ("v_" + dir[j] + "(" + to_string(i) + ")").c_str());
        }
    }
    fprintf(pFile, "\n");
}

void VELOCITY::printLine(){
    meanVelocity = sys->getMeanVelocity();
    meanLayerVelocities = sys->getMeanLayerVelocities();
    long timestep = sys->getTimestep() - 2; //skip first step + equationOfMotion already incremented timestep by one
    fprintf(pFile, "%6ld\t", timestep);
    fprintf(pFile, format_l.c_str(), meanVelocity.x);
    fprintf(pFile, format_l.c_str(), meanVelocity.y);
    fprintf(pFile, format_l.c_str(), meanVelocity.z);
    for(int i = 0; i < meanLayerVelocities.size(); i++){
        fprintf(pFile, format_l.c_str(), meanLayerVelocities[i].x);
        fprintf(pFile, format_l.c_str(), meanLayerVelocities[i].y);
        fprintf(pFile, format_l.c_str(), meanLayerVelocities[i].z);
    }
    fprintf(pFile, "\n");
}

string VELOCITY::getFilename() const{
    return filename;
}
