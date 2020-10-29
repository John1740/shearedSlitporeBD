//
// Created by mhuelsberg on 30.07.20.
//

#include "cartesian_coordinate.h"
#include <complex>

template<>
double CARTESIAN_COORDINATE<int>::abs() const{
    return sqrt(x * x + y * y + z * z);
}

template<>
double CARTESIAN_COORDINATE<float>::abs() const{
    return sqrt(x * x + y * y + z * z);
}

template<>
double CARTESIAN_COORDINATE<double>::abs() const{
    return sqrt(x * x + y * y + z * z);
}

template<>
double CARTESIAN_COORDINATE<long double>::abs() const{
    return sqrt(x * x + y * y + z * z);
}

template<>
double CARTESIAN_COORDINATE<complex<double>>::abs() const{
    double squared = x.real() * x.real() + x.imag() * x.imag()
                     + y.real() * y.real() + y.imag() * y.imag()
                     + z.real() * z.real() + z.imag() * z.imag();
    return sqrt(squared);
}

template<>
CARTESIAN_COORDINATE<double> CARTESIAN_COORDINATE<double>::real() const{
    return *this;
}

template<>
CARTESIAN_COORDINATE<double> CARTESIAN_COORDINATE<double>::imag() const{
    return CARTESIAN_COORDINATE<double>(0);
}

template<>
CARTESIAN_COORDINATE<double> CARTESIAN_COORDINATE<complex<double>>::real() const{
    return CARTESIAN_COORDINATE<double>(x.real(), y.real(), z.real());
}

template<>
CARTESIAN_COORDINATE<double> CARTESIAN_COORDINATE<complex<double>>::imag() const{
    return CARTESIAN_COORDINATE<double>(x.imag(), y.imag(), z.imag());
}

template<>
CARTESIAN_COORDINATE<complex<double>>&
CARTESIAN_COORDINATE<complex<double>>::real(const CARTESIAN_COORDINATE<double>& r){
    x.real(r.x);
    y.real(r.y);
    z.real(r.z);
    return *this;
}

template<>
CARTESIAN_COORDINATE<complex<double>>&
CARTESIAN_COORDINATE<complex<double>>::imag(const CARTESIAN_COORDINATE<double>& i){
    x.imag(i.x);
    y.imag(i.y);
    z.imag(i.z);
    return *this;
}