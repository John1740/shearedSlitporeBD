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

    string format_f = "% 4.5f\t";   //float format
    string format_i = "%6i\t";   //integer format
    string format_li = "%12li\t";   //long integer format
    string format_h = "%8s\t";  //header format

    void printHeader();
    void printLine(SHEARED_SLITPORE_SYSTEM& sys);
};

#endif //SHEAREDSLITPOREBD_ANGULAR_BOND_H
