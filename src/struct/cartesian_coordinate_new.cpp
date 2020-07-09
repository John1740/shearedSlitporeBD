//
// Created by mhuels on 7/9/20.
//

#include "cartesian_coordinate_new.h"

CARTESIAN_COORDINATE_NEW::CARTESIAN_COORDINATE_NEW(){
    for(int i=0; i < size; i++){
        (*this)[i] = 0;
    }
}

CARTESIAN_COORDINATE_NEW::CARTESIAN_COORDINATE_NEW(double c){
    *this = c;
}

CARTESIAN_COORDINATE_NEW::CARTESIAN_COORDINATE_NEW(double x, double y, double z){
    this->x = x;
    this->y = y;
    this->z = z;
}

CARTESIAN_COORDINATE_NEW::CARTESIAN_COORDINATE_NEW(const CARTESIAN_COORDINATE_NEW& other){
    *this = other;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//const version for the use in assignment operators (e.g. operator=)
double CARTESIAN_COORDINATE_NEW::operator[](int i) const{
    if(i == 0){
        return x;
    }
    else if(i == 1){
        return y;
    }
    else if(i == 2){
        return z;
    }
    else{
        cout << "CARTESIAN_COORDINATE[" << i << "] out of range." << endl;
        exit(0);
    }
}

//non-const version, that can be used for assignment as well
double& CARTESIAN_COORDINATE_NEW::operator[](int i){
    if(i == 0){
        return x;
    }
    else if(i == 1){
        return y;
    }
    else if(i == 2){
        return z;
    }
    else{
        cout << "CARTESIAN_COORDINATE[" << i << "] out of range." << endl;
        exit(0);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double CARTESIAN_COORDINATE_NEW::getAbs() const{
    return sqrt(x * x + y * y + z * z);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CARTESIAN_COORDINATE_NEW& CARTESIAN_COORDINATE_NEW::operator=(const CARTESIAN_COORDINATE_NEW& other){
    for(int i=0; i < size; i++){
        (*this)[i] = other[i];
    }
    return *this;
}

CARTESIAN_COORDINATE_NEW& CARTESIAN_COORDINATE_NEW::operator=(const double& c){
    for(int i=0; i < size; i++){
        (*this)[i] = c;
    }
    return *this;
}

CARTESIAN_COORDINATE_NEW& CARTESIAN_COORDINATE_NEW::operator+=(const CARTESIAN_COORDINATE_NEW& other){
    for(int i=0; i < size; i++){
        (*this)[i] += other[i];
    }
    return *this;
}

CARTESIAN_COORDINATE_NEW& CARTESIAN_COORDINATE_NEW::operator+=(const double& c){
    return (*this) += CARTESIAN_COORDINATE_NEW(c);
}

CARTESIAN_COORDINATE_NEW& CARTESIAN_COORDINATE_NEW::operator-=(const CARTESIAN_COORDINATE_NEW& other){
    for(int i=0; i < size; i++){
        (*this)[i] -= other[i];
    }
    return *this;
}

CARTESIAN_COORDINATE_NEW& CARTESIAN_COORDINATE_NEW::operator-=(const double& c){
    return (*this) -= CARTESIAN_COORDINATE_NEW(c);
}

CARTESIAN_COORDINATE_NEW& CARTESIAN_COORDINATE_NEW::operator*=(const CARTESIAN_COORDINATE_NEW& other){
    for(int i=0; i < size; i++){
        (*this)[i] *= other[i];
    }
    return *this;
}

CARTESIAN_COORDINATE_NEW& CARTESIAN_COORDINATE_NEW::operator*=(const double& c){
    return (*this) *= CARTESIAN_COORDINATE_NEW(c);
}

CARTESIAN_COORDINATE_NEW& CARTESIAN_COORDINATE_NEW::operator/=(const CARTESIAN_COORDINATE_NEW& other){
    for(int i=0; i < size; i++){
        (*this)[i] /= other[i];
    }
    return *this;
}

CARTESIAN_COORDINATE_NEW& CARTESIAN_COORDINATE_NEW::operator/=(const double& c){
    return (*this) /= CARTESIAN_COORDINATE_NEW(c);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CARTESIAN_COORDINATE_NEW operator+(const CARTESIAN_COORDINATE_NEW& lhs, const CARTESIAN_COORDINATE_NEW& rhs){
    return CARTESIAN_COORDINATE_NEW(lhs) += rhs;
}

CARTESIAN_COORDINATE_NEW operator+(const CARTESIAN_COORDINATE_NEW& lhs, const double& rhs){
    return CARTESIAN_COORDINATE_NEW(lhs) += rhs;
}

CARTESIAN_COORDINATE_NEW operator+(const double& lhs, const CARTESIAN_COORDINATE_NEW& rhs){
    return CARTESIAN_COORDINATE_NEW(lhs) += rhs;
}

CARTESIAN_COORDINATE_NEW operator-(const CARTESIAN_COORDINATE_NEW& lhs, const CARTESIAN_COORDINATE_NEW& rhs){
    return CARTESIAN_COORDINATE_NEW(lhs) -= rhs;
}

CARTESIAN_COORDINATE_NEW operator-(const CARTESIAN_COORDINATE_NEW& lhs, const double& rhs){
    return CARTESIAN_COORDINATE_NEW(lhs) -= rhs;
}

CARTESIAN_COORDINATE_NEW operator-(const double& lhs, const CARTESIAN_COORDINATE_NEW& rhs){
    return CARTESIAN_COORDINATE_NEW(lhs) -= rhs;
}

CARTESIAN_COORDINATE_NEW operator*(const CARTESIAN_COORDINATE_NEW& lhs, const CARTESIAN_COORDINATE_NEW& rhs){
    return CARTESIAN_COORDINATE_NEW(lhs) *= rhs;
}

CARTESIAN_COORDINATE_NEW operator*(const CARTESIAN_COORDINATE_NEW& lhs, const double& rhs){
    return CARTESIAN_COORDINATE_NEW(lhs) *= rhs;
}

CARTESIAN_COORDINATE_NEW operator*(const double& lhs, const CARTESIAN_COORDINATE_NEW& rhs){
    return CARTESIAN_COORDINATE_NEW(lhs) *= rhs;
}

CARTESIAN_COORDINATE_NEW operator/(const CARTESIAN_COORDINATE_NEW& lhs, const CARTESIAN_COORDINATE_NEW& rhs){
    return CARTESIAN_COORDINATE_NEW(lhs) /= rhs;
}

CARTESIAN_COORDINATE_NEW operator/(const CARTESIAN_COORDINATE_NEW& lhs, const double& rhs){
    return CARTESIAN_COORDINATE_NEW(lhs) /= rhs;
}

CARTESIAN_COORDINATE_NEW operator/(const double& lhs, const CARTESIAN_COORDINATE_NEW& rhs){
    return CARTESIAN_COORDINATE_NEW(lhs) /= rhs;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool operator==(const CARTESIAN_COORDINATE_NEW& lhs, const CARTESIAN_COORDINATE_NEW& rhs){
    if(lhs.x==rhs.x && lhs.y==rhs.y && lhs.z==rhs.z){
        return true;
    }
    else{
        return false;
    }
}

bool operator!=(const CARTESIAN_COORDINATE_NEW& lhs, const CARTESIAN_COORDINATE_NEW& rhs){
    return !(lhs == rhs);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ostream& operator<< (ostream& os, const CARTESIAN_COORDINATE_NEW& r){
    os << "[" << r.x << ", " << r.y << ", " << r.z << "]";
    return os;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<double> CARTESIAN_COORDINATE_NEW::convertToVector() const{
    vector<double> v;
    for(int i=0; i < size; i++){
        v.push_back((*this)[i]);
    }
    return v;
}
