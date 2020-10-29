//
// Created by mhuels on 5/4/20.
//

#ifndef SHEAREDSLITPOREBD_CONFIGURATION_H
#define SHEAREDSLITPOREBD_CONFIGURATION_H

#include "../argument_parser/arguments.h"
#include "slit_pore_box.h"
#include "charged_particle.h"

class CONFIGURATION{
private:
    SLIT_PORE_BOX box;
    vector<CHARGED_PARTICLE> particles;
    double density = DENSITY;

public:
    CONFIGURATION();
    CONFIGURATION(const ARGUMENTS& args);

    //getter functions
    SLIT_PORE_BOX getBox();

    //setter functions
    void setSimBox(SLIT_PORE_BOX boxIn);

    //file handling
    void writeConfiguration(string filename);
    void readConfiguration(string filename);
};

#endif //SHEAREDSLITPOREBD_CONFIGURATION_H
