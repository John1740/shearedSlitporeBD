//
// Created by mhuels on 5/25/20.
//

#ifndef SHEAREDSLITPOREBD_ANGULAR_BOND_H
#define SHEAREDSLITPOREBD_ANGULAR_BOND_H

#include "printer.h"
#include "../systems/sheared_slitpore_system.h"

class ANGULAR_BOND_PRINTER: public PRINTER{
private:

public:
    ANGULAR_BOND_PRINTER();
    ANGULAR_BOND_PRINTER(fs::path filename);

    void printHeader();
    void printLine(SHEARED_SLITPORE_SYSTEM& sys);
};

#endif //SHEAREDSLITPOREBD_ANGULAR_BOND_H
