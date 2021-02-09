//
// Created by mhuels on 4/20/20.
//

#ifndef SHEAREDSLITPOREBD_STRESS_H
#define SHEAREDSLITPOREBD_STRESS_H

#include <string>
#include "../systems/sheared_slitpore_system.h"

class STRESS_PRINTER: public PRINTER{
private:
    SHEARED_SLITPORE_SYSTEM* sys;
    REAL_M meanStress;    //ensemble average/mean
public:
    STRESS_PRINTER(SHEARED_SLITPORE_SYSTEM* sysIn);
    STRESS_PRINTER(SHEARED_SLITPORE_SYSTEM* sysIn, fs::path filename);
    ~STRESS_PRINTER();

    void printHeader();
    void printLine();

    //getter
};

#endif //SHEAREDSLITPOREBD_STRESS_H
