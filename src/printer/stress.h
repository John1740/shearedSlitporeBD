//
// Created by mhuels on 4/20/20.
//

#ifndef SHEAREDSLITPOREBD_STRESS_H
#define SHEAREDSLITPOREBD_STRESS_H

#include <string>
#include <cstdio>
#include "../systems/sheared_slitpore_system.h"
using namespace std;

class STRESS_PRINTER{
private:
    SHEARED_SLITPORE_SYSTEM* sys;
    CARTESIAN_MATRIX meanStress;    //ensemble average/mean

public:
    STRESS_PRINTER(SHEARED_SLITPORE_SYSTEM* sysIn);
    STRESS_PRINTER(SHEARED_SLITPORE_SYSTEM* sysIn, fs::path filename);
    ~STRESS_PRINTER();
    
    PRINTER printer;
    string format_l = "% 4.5f\t";   //line format
    string format_h = "%8s\t";  //header format

    void printHeader();
    void printLine();

    //getter
};


#endif //SHEAREDSLITPOREBD_STRESS_H
