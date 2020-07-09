//
// Created by mhuels on 7/9/20.
//

#ifndef SHEAREDSLITPOREBD_CARTESIAN_COORDINATE_NEW_H
#define SHEAREDSLITPOREBD_CARTESIAN_COORDINATE_NEW_H

#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

class CARTESIAN_COORDINATE_NEW{
private:
    int size = 3;
public:
    double x, y, z;
    
    //constructors
    CARTESIAN_COORDINATE_NEW();
    CARTESIAN_COORDINATE_NEW(double c);
    CARTESIAN_COORDINATE_NEW(double x, double y, double z);
    CARTESIAN_COORDINATE_NEW(const CARTESIAN_COORDINATE_NEW& other);
    
    //index operators
    double operator[] (int i) const;
    double& operator[] (int i);
    
    //functions
    double getAbs() const;
    
    //assignment operators
    CARTESIAN_COORDINATE_NEW& operator=(const CARTESIAN_COORDINATE_NEW& other);
    CARTESIAN_COORDINATE_NEW& operator=(const double& c);
    
    CARTESIAN_COORDINATE_NEW& operator+=(const CARTESIAN_COORDINATE_NEW& other);
    CARTESIAN_COORDINATE_NEW& operator+=(const double& c);
    
    CARTESIAN_COORDINATE_NEW& operator-=(const CARTESIAN_COORDINATE_NEW& other);
    CARTESIAN_COORDINATE_NEW& operator-=(const double& c);
    
    CARTESIAN_COORDINATE_NEW& operator*=(const CARTESIAN_COORDINATE_NEW& other);
    CARTESIAN_COORDINATE_NEW& operator*=(const double& c);
    
    CARTESIAN_COORDINATE_NEW& operator/=(const CARTESIAN_COORDINATE_NEW& other);
    CARTESIAN_COORDINATE_NEW& operator/=(const double& c);
    
    //combination operators
    friend CARTESIAN_COORDINATE_NEW operator+(const CARTESIAN_COORDINATE_NEW& lhs, const CARTESIAN_COORDINATE_NEW& rhs);
    friend CARTESIAN_COORDINATE_NEW operator+(const CARTESIAN_COORDINATE_NEW& lhs, const double& rhs);
    friend CARTESIAN_COORDINATE_NEW operator+(const double& lhs, const CARTESIAN_COORDINATE_NEW& rhs);
    
    friend CARTESIAN_COORDINATE_NEW operator-(const CARTESIAN_COORDINATE_NEW& lhs, const CARTESIAN_COORDINATE_NEW& rhs);
    friend CARTESIAN_COORDINATE_NEW operator-(const CARTESIAN_COORDINATE_NEW& lhs, const double& rhs);
    friend CARTESIAN_COORDINATE_NEW operator-(const double& lhs, const CARTESIAN_COORDINATE_NEW& rhs);
    
    friend CARTESIAN_COORDINATE_NEW operator*(const CARTESIAN_COORDINATE_NEW& lhs, const CARTESIAN_COORDINATE_NEW& rhs);
    friend CARTESIAN_COORDINATE_NEW operator*(const CARTESIAN_COORDINATE_NEW& lhs, const double& rhs);
    friend CARTESIAN_COORDINATE_NEW operator*(const double& lhs, const CARTESIAN_COORDINATE_NEW& rhs);
    
    friend CARTESIAN_COORDINATE_NEW operator/(const CARTESIAN_COORDINATE_NEW& lhs, const CARTESIAN_COORDINATE_NEW& rhs);
    friend CARTESIAN_COORDINATE_NEW operator/(const CARTESIAN_COORDINATE_NEW& lhs, const double& rhs);
    friend CARTESIAN_COORDINATE_NEW operator/(const double& lhs, const CARTESIAN_COORDINATE_NEW& rhs);
    
    //bool operators
    friend bool operator==(const CARTESIAN_COORDINATE_NEW& lhs, const CARTESIAN_COORDINATE_NEW& rhs);
    friend bool operator!=(const CARTESIAN_COORDINATE_NEW& lhs, const CARTESIAN_COORDINATE_NEW& rhs);
    
    //conversions
    vector<double> convertToVector() const;
    
    //stream handling
    friend ostream& operator<<(ostream& os, const CARTESIAN_COORDINATE_NEW& r);
};


#endif //SHEAREDSLITPOREBD_CARTESIAN_COORDINATE_NEW_H
