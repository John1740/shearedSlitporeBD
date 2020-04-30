//
// Created by mhuels on 4/20/20.
//

#ifndef SHEAREDSLITPOREBD_STRESS_H
#define SHEAREDSLITPOREBD_STRESS_H

#include <string>
#include <cstdio>
#include "../systems/sheared_slitpore_system.h"
using namespace std;

class STRESS{
private:
    CARTESIAN_MATRIX meanStress;    //ensemble average/mean
    string filename = "stresses.out";
    string format_l = "% 4.5f\t";   //line format
    string format_h = "%8s\t";  //header format
    FILE* pFile;

public:
    STRESS();
    STRESS(string filename);
    STRESS(string filename, string format_l);
    STRESS(string filename, string format_l, string format_h);
    ~STRESS();

    void printHeader();
    void printLine(SHEARED_SLITPORE_SYSTEM& sys, int timeStep);

};


#endif //SHEAREDSLITPOREBD_STRESS_H
