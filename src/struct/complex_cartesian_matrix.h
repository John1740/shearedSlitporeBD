//
// Created by mhuels on 7/9/20.
//

#ifndef SHEAREDSLITPOREBD_COMPLEX_CARTESIAN_MATRIX_H
#define SHEAREDSLITPOREBD_COMPLEX_CARTESIAN_MATRIX_H

#include <complex>
#include "cartesian_matrix.h"
using namespace std;

class COMPLEX_CARTESIAN_MATRIX{
public:
    complex<double> xx, xy, xz;
    complex<double> yx, yy, yz;
    complex<double> zx, zy, zz;
    
    COMPLEX_CARTESIAN_MATRIX();
    
    //getter
    CARTESIAN_MATRIX real();
    CARTESIAN_MATRIX imag();
    
};


#endif //SHEAREDSLITPOREBD_COMPLEX_CARTESIAN_MATRIX_H
