//
// Created by mhuels on 5/25/20.
//

#ifndef SHEAREDSLITPOREBD_ANGULAR_BOND_H
#define SHEAREDSLITPOREBD_ANGULAR_BOND_H

#include "printer.h"
#include "../systems/sheared_slitpore_system.h"

class ANGULAR_BOND_PRINTER: public PRINTER{
private:
    SHEARED_SLITPORE_SYSTEM* sys;

public:
    ANGULAR_BOND_PRINTER(SHEARED_SLITPORE_SYSTEM* sysIn);
    ANGULAR_BOND_PRINTER(SHEARED_SLITPORE_SYSTEM* sysIn, fs::path filename);

    void printHeader();
    void printLine();
};

#endif //SHEAREDSLITPOREBD_ANGULAR_BOND_H
