//
// Created by mhuels on 7/9/20.
//

#ifndef SHEAREDSLITPOREBD_REAL_COORDINATE_H
#define SHEAREDSLITPOREBD_REAL_COORDINATE_H

#include "cartesian_coordinate.h"

class REAL_C: public CARTESIAN_COORDINATE<double>{
public:
    //constructors
    REAL_C();
    REAL_C(double c);
    REAL_C(double x, double y, double z);
    REAL_C(const REAL_C& other);

    //functions
    double abs() const;
};


#endif //SHEAREDSLITPOREBD_REAL_COORDINATE_H