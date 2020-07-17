//
// Created by mhuels on 7/9/20.
//

#include "cartesian_coordinate.h"

CARTESIAN_COORDINATE::CARTESIAN_COORDINATE(){
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

CARTESIAN_COORDINATE::CARTESIAN_COORDINATE(double c){
    this->x = c;
    this->y = c;
    this->z = c;
}

CARTESIAN_COORDINATE::CARTESIAN_COORDINATE(double x, double y, double z){
    this->x = x;
    this->y = y;
    this->z = z;
}

CARTESIAN_COORDINATE::CARTESIAN_COORDINATE(const CARTESIAN_COORDINATE& other){
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//const version for the use in assignment operators (e.g. operator=)
double CARTESIAN_COORDINATE::operator[](int i) const{
    switch(i){
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            throw std::out_of_range("CARTESIAN_COORDINATE[] out of range.");
    }
}

//non-const version, that can be used for assignment as well
double& CARTESIAN_COORDINATE::operator[](int i){
    switch(i){
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            throw std::out_of_range("CARTESIAN_COORDINATE[] out of range.");
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double CARTESIAN_COORDINATE::abs() const{
    return sqrt(x * x + y * y + z * z);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CARTESIAN_COORDINATE& CARTESIAN_COORDINATE::operator=(const CARTESIAN_COORDINATE& other){
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    return *this;
}

CARTESIAN_COORDINATE& CARTESIAN_COORDINATE::operator=(const double& c){
    this->x = c;
    this->y = c;
    this->z = c;
    return *this;
}

CARTESIAN_COORDINATE& CARTESIAN_COORDINATE::operator+=(const CARTESIAN_COORDINATE& other){
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    return *this;
}

CARTESIAN_COORDINATE& CARTESIAN_COORDINATE::operator+=(const double& c){
    this->x += c;
    this->y += c;
    this->z += c;
    return *this;
}

CARTESIAN_COORDINATE& CARTESIAN_COORDINATE::operator-=(const CARTESIAN_COORDINATE& other){
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    return *this;
}

CARTESIAN_COORDINATE& CARTESIAN_COORDINATE::operator-=(const double& c){
    this->x -= c;
    this->y -= c;
    this->z -= c;
    return *this;
}

CARTESIAN_COORDINATE& CARTESIAN_COORDINATE::operator*=(const CARTESIAN_COORDINATE& other){
    this->x *= other.x;
    this->y *= other.y;
    this->z *= other.z;
    return *this;
}

CARTESIAN_COORDINATE& CARTESIAN_COORDINATE::operator*=(const double& c){
    this->x *= c;
    this->y *= c;
    this->z *= c;
    return *this;
}

CARTESIAN_COORDINATE& CARTESIAN_COORDINATE::operator/=(const CARTESIAN_COORDINATE& other){
    this->x /= other.x;
    this->y /= other.y;
    this->z /= other.z;
    return *this;
}

CARTESIAN_COORDINATE& CARTESIAN_COORDINATE::operator/=(const double& c){
    this->x /= c;
    this->y /= c;
    this->z /= c;
    return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CARTESIAN_COORDINATE operator+(const CARTESIAN_COORDINATE& lhs, const CARTESIAN_COORDINATE& rhs){
    return CARTESIAN_COORDINATE(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

CARTESIAN_COORDINATE operator+(const CARTESIAN_COORDINATE& lhs, const double& rhs){
    return CARTESIAN_COORDINATE(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs);
}

CARTESIAN_COORDINATE operator+(const double& lhs, const CARTESIAN_COORDINATE& rhs){
    return CARTESIAN_COORDINATE(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z);
}

CARTESIAN_COORDINATE operator-(const CARTESIAN_COORDINATE& lhs, const CARTESIAN_COORDINATE& rhs){
    return CARTESIAN_COORDINATE(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

CARTESIAN_COORDINATE operator-(const CARTESIAN_COORDINATE& lhs, const double& rhs){
    return CARTESIAN_COORDINATE(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs);
}

CARTESIAN_COORDINATE operator-(const double& lhs, const CARTESIAN_COORDINATE& rhs){
    return CARTESIAN_COORDINATE(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z);
}

CARTESIAN_COORDINATE operator*(const CARTESIAN_COORDINATE& lhs, const CARTESIAN_COORDINATE& rhs){
    return CARTESIAN_COORDINATE(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
}

CARTESIAN_COORDINATE operator*(const CARTESIAN_COORDINATE& lhs, const double& rhs){
    return CARTESIAN_COORDINATE(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}

CARTESIAN_COORDINATE operator*(const double& lhs, const CARTESIAN_COORDINATE& rhs){
    return CARTESIAN_COORDINATE(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
}

CARTESIAN_COORDINATE operator/(const CARTESIAN_COORDINATE& lhs, const CARTESIAN_COORDINATE& rhs){
    return CARTESIAN_COORDINATE(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
}

CARTESIAN_COORDINATE operator/(const CARTESIAN_COORDINATE& lhs, const double& rhs){
    return CARTESIAN_COORDINATE(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
}

CARTESIAN_COORDINATE operator/(const double& lhs, const CARTESIAN_COORDINATE& rhs){
    return CARTESIAN_COORDINATE(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool operator==(const CARTESIAN_COORDINATE& lhs, const CARTESIAN_COORDINATE& rhs){
    if(lhs.x==rhs.x && lhs.y==rhs.y && lhs.z==rhs.z){
        return true;
    }
    else{
        return false;
    }
}

bool operator!=(const CARTESIAN_COORDINATE& lhs, const CARTESIAN_COORDINATE& rhs){
    return !(lhs == rhs);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<double> CARTESIAN_COORDINATE::asVector() const{
    vector<double> v(3);
    v[0] = x;
    v[1] = y;
    v[2] = z;
    return v;
}

boost::array<double, 3> CARTESIAN_COORDINATE::asArray() const{
    boost::array<double, 3> v;
    v[0] = x;
    v[1] = y;
    v[2] = z;
    return v;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ostream& operator<< (ostream& os, const CARTESIAN_COORDINATE& r){
    os << "[" << r.x << ",\t" << r.y << ",\t" << r.z << "]";
    return os;
}
