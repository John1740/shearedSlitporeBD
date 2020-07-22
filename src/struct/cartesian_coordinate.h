//
// Created by mhuels on 7/22/20.
//

#ifndef SHEAREDSLITPOREBD_CARTESIAN_COORDINATE_H
#define SHEAREDSLITPOREBD_CARTESIAN_COORDINATE_H

#include <iostream>
#include <math.h>
#include <vector>
#include "boost/array.hpp"
using namespace std;

template<typename dtype>
class CARTESIAN_COORDINATE{
    //This is completely hard-coded to improve performance.
    //Other (slower) concepts, that have been tried, are (in ascending order):
    //private dtype r[3], access via (*this)[i] (overloaded operator[])
    //same as above but with out-of-range check within operator[]
    //inherit from boost::array<dtype, 3>, access via (*this)[i] (out-of-range check included)
    //hard-coded as done here, but access via wrapped (*this)[i]
    //inherit from std::array<dtype, 3>, access via (*this)[i] (out-of-range check included)
public:
    dtype x, y, z;
    
    //constructors
    CARTESIAN_COORDINATE();
    CARTESIAN_COORDINATE(dtype c);
    CARTESIAN_COORDINATE(dtype x, dtype y, dtype z);
    CARTESIAN_COORDINATE(const CARTESIAN_COORDINATE<dtype>& other);
    
    //index operators
    dtype operator[](int i) const;
    dtype& operator[](int i);
    
    //assignment operators
    CARTESIAN_COORDINATE<dtype>& operator=(const CARTESIAN_COORDINATE<dtype>& other);
    CARTESIAN_COORDINATE<dtype>& operator=(const dtype& c);
    
    CARTESIAN_COORDINATE<dtype>& operator+=(const CARTESIAN_COORDINATE<dtype>& other);
    CARTESIAN_COORDINATE<dtype>& operator+=(const dtype& c);
    
    CARTESIAN_COORDINATE<dtype>& operator-=(const CARTESIAN_COORDINATE<dtype>& other);
    CARTESIAN_COORDINATE<dtype>& operator-=(const dtype& c);
    
    CARTESIAN_COORDINATE<dtype>& operator*=(const CARTESIAN_COORDINATE<dtype>& other);
    CARTESIAN_COORDINATE<dtype>& operator*=(const dtype& c);
    
    CARTESIAN_COORDINATE<dtype>& operator/=(const CARTESIAN_COORDINATE<dtype>& other);
    CARTESIAN_COORDINATE<dtype>& operator/=(const dtype& c);
    
    //arithmetic operators
    friend CARTESIAN_COORDINATE<dtype> operator+(const CARTESIAN_COORDINATE<dtype>& lhs, const CARTESIAN_COORDINATE<dtype>& rhs);
    friend CARTESIAN_COORDINATE<dtype> operator+(const CARTESIAN_COORDINATE<dtype>& lhs, const dtype& rhs);
    friend CARTESIAN_COORDINATE<dtype> operator+(const dtype& lhs, const CARTESIAN_COORDINATE<dtype>& rhs);
    
    friend CARTESIAN_COORDINATE<dtype> operator-(const CARTESIAN_COORDINATE<dtype>& lhs, const CARTESIAN_COORDINATE<dtype>& rhs);
    friend CARTESIAN_COORDINATE<dtype> operator-(const CARTESIAN_COORDINATE<dtype>& lhs, const dtype& rhs);
    friend CARTESIAN_COORDINATE<dtype> operator-(const dtype& lhs, const CARTESIAN_COORDINATE<dtype>& rhs);
    
    friend CARTESIAN_COORDINATE<dtype> operator*(const CARTESIAN_COORDINATE<dtype>& lhs, const CARTESIAN_COORDINATE<dtype>& rhs);
    friend CARTESIAN_COORDINATE<dtype> operator*(const CARTESIAN_COORDINATE<dtype>& lhs, const dtype& rhs);
    friend CARTESIAN_COORDINATE<dtype> operator*(const dtype& lhs, const CARTESIAN_COORDINATE<dtype>& rhs);
    
    friend CARTESIAN_COORDINATE<dtype> operator/(const CARTESIAN_COORDINATE<dtype>& lhs, const CARTESIAN_COORDINATE<dtype>& rhs);
    friend CARTESIAN_COORDINATE<dtype> operator/(const CARTESIAN_COORDINATE<dtype>& lhs, const dtype& rhs);
    friend CARTESIAN_COORDINATE<dtype> operator/(const dtype& lhs, const CARTESIAN_COORDINATE<dtype>& rhs);
    
    //logical operators
    friend bool operator==(const CARTESIAN_COORDINATE<dtype>& lhs, const CARTESIAN_COORDINATE<dtype>& rhs);
    friend bool operator!=(const CARTESIAN_COORDINATE<dtype>& lhs, const CARTESIAN_COORDINATE<dtype>& rhs);
    
    //conversions
    vector<dtype> asVector() const;
    boost::array<dtype, 3> asArray() const;
    
    //stream handling
    friend ostream& operator<<(ostream& os, const CARTESIAN_COORDINATE<dtype>& r);
};


#endif //SHEAREDSLITPOREBD_CARTESIAN_COORDINATE_H
