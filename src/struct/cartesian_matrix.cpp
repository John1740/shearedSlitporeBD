//
// Created by mhuelsberg on 30.07.20.
//

#include "cartesian_matrix.h"
#include <complex>

template<>
CARTESIAN_MATRIX<double> CARTESIAN_MATRIX<double>::real() const{
    return *this;
}

template<>
CARTESIAN_MATRIX<double> CARTESIAN_MATRIX<double>::imag() const{
    return CARTESIAN_MATRIX<double>(0);
}

template<>
CARTESIAN_MATRIX<double> CARTESIAN_MATRIX<complex<double>>::real() const{
    CARTESIAN_MATRIX<double> result;
    result.xx = xx.real();
    result.xy = xy.real();
    result.xz = xz.real();
    result.yx = yx.real();
    result.yy = yy.real();
    result.yz = yz.real();
    result.zx = zx.real();
    result.zy = zy.real();
    result.zz = zz.real();
    return result;
}

template<>
CARTESIAN_MATRIX<double> CARTESIAN_MATRIX<complex<double>>::imag() const {
    CARTESIAN_MATRIX<double> result;
    result.xx = xx.imag();
    result.xy = xy.imag();
    result.xz = xz.imag();
    result.yx = yx.imag();
    result.yy = yy.imag();
    result.yz = yz.imag();
    result.zx = zx.imag();
    result.zy = zy.imag();
    result.zz = zz.imag();
    return result;
}