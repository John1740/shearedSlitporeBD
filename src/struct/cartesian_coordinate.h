//
// Created by mhuels on 7/9/20.
//

#ifndef SHEAREDSLITPOREBD_CARTESIAN_COORDINATE_H
#define SHEAREDSLITPOREBD_CARTESIAN_COORDINATE_H

#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

class CARTESIAN_COORDINATE{
public:
    double x, y, z;
    
    //constructors
    CARTESIAN_COORDINATE();
    CARTESIAN_COORDINATE(double c);
    CARTESIAN_COORDINATE(double x, double y, double z);
    CARTESIAN_COORDINATE(const CARTESIAN_COORDINATE& other);
    
    //index operators
    double operator[](int i) const;
    double& operator[](int i);
    
    //functions
    double abs() const;
    
    //assignment operators
    CARTESIAN_COORDINATE& operator=(const CARTESIAN_COORDINATE& other);
    CARTESIAN_COORDINATE& operator=(const double& c);
    
    CARTESIAN_COORDINATE& operator+=(const CARTESIAN_COORDINATE& other);
    CARTESIAN_COORDINATE& operator+=(const double& c);
    
    CARTESIAN_COORDINATE& operator-=(const CARTESIAN_COORDINATE& other);
    CARTESIAN_COORDINATE& operator-=(const double& c);
    
    CARTESIAN_COORDINATE& operator*=(const CARTESIAN_COORDINATE& other);
    CARTESIAN_COORDINATE& operator*=(const double& c);
    
    CARTESIAN_COORDINATE& operator/=(const CARTESIAN_COORDINATE& other);
    CARTESIAN_COORDINATE& operator/=(const double& c);
    
    //arithmetic operators
    friend CARTESIAN_COORDINATE operator+(const CARTESIAN_COORDINATE& lhs, const CARTESIAN_COORDINATE& rhs);
    friend CARTESIAN_COORDINATE operator+(const CARTESIAN_COORDINATE& lhs, const double& rhs);
    friend CARTESIAN_COORDINATE operator+(const double& lhs, const CARTESIAN_COORDINATE& rhs);
    
    friend CARTESIAN_COORDINATE operator-(const CARTESIAN_COORDINATE& lhs, const CARTESIAN_COORDINATE& rhs);
    friend CARTESIAN_COORDINATE operator-(const CARTESIAN_COORDINATE& lhs, const double& rhs);
    friend CARTESIAN_COORDINATE operator-(const double& lhs, const CARTESIAN_COORDINATE& rhs);
    
    friend CARTESIAN_COORDINATE operator*(const CARTESIAN_COORDINATE& lhs, const CARTESIAN_COORDINATE& rhs);
    friend CARTESIAN_COORDINATE operator*(const CARTESIAN_COORDINATE& lhs, const double& rhs);
    friend CARTESIAN_COORDINATE operator*(const double& lhs, const CARTESIAN_COORDINATE& rhs);
    
    friend CARTESIAN_COORDINATE operator/(const CARTESIAN_COORDINATE& lhs, const CARTESIAN_COORDINATE& rhs);
    friend CARTESIAN_COORDINATE operator/(const CARTESIAN_COORDINATE& lhs, const double& rhs);
    friend CARTESIAN_COORDINATE operator/(const double& lhs, const CARTESIAN_COORDINATE& rhs);
    
    //logical operators
    friend bool operator==(const CARTESIAN_COORDINATE& lhs, const CARTESIAN_COORDINATE& rhs);
    friend bool operator!=(const CARTESIAN_COORDINATE& lhs, const CARTESIAN_COORDINATE& rhs);
    
    //conversions
    vector<double> convertToVector() const;
    
    //stream handling
    friend ostream& operator<<(ostream& os, const CARTESIAN_COORDINATE& r);
};


#endif //SHEAREDSLITPOREBD_CARTESIAN_COORDINATE_H
