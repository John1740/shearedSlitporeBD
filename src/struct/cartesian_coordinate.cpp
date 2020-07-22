//
// Created by mhuels on 7/22/20.
//

#include "CARTESIAN_COORDINATE.h"

template <typename dtype>
CARTESIAN_COORDINATE<dtype>::CARTESIAN_COORDINATE<dtype>(){
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

template <typename dtype>
CARTESIAN_COORDINATE<dtype>::CARTESIAN_COORDINATE<dtype>(dtype c){
    this->x = c;
    this->y = c;
    this->z = c;
}

template <typename dtype>
CARTESIAN_COORDINATE<dtype>::CARTESIAN_COORDINATE<dtype>(dtype x, dtype y, dtype z){
    this->x = x;
    this->y = y;
    this->z = z;
}

template <typename dtype>
CARTESIAN_COORDINATE<dtype>::CARTESIAN_COORDINATE<dtype>(const CARTESIAN_COORDINATE<dtype>& other){
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//const version for the use in assignment operators (e.g. operator=)
template <typename dtype>
dtype CARTESIAN_COORDINATE<dtype>::operator[](int i) const{
    switch(i){
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            throw std::out_of_range("CARTESIAN_COORDINATE<dtype>[] out of range.");
    }
}

//non-const version, that can be used for assignment as well
template <typename dtype>
dtype& CARTESIAN_COORDINATE<dtype>::operator[](int i){
    switch(i){
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            throw std::out_of_range("CARTESIAN_COORDINATE<dtype>[] out of range.");
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename dtype>
CARTESIAN_COORDINATE<dtype>& CARTESIAN_COORDINATE<dtype>::operator=(const CARTESIAN_COORDINATE<dtype>& other){
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    return *this;
}

template <typename dtype>
CARTESIAN_COORDINATE<dtype>& CARTESIAN_COORDINATE<dtype>::operator=(const dtype& c){
    this->x = c;
    this->y = c;
    this->z = c;
    return *this;
}

template <typename dtype>
CARTESIAN_COORDINATE<dtype>& CARTESIAN_COORDINATE<dtype>::operator+=(const CARTESIAN_COORDINATE<dtype>& other){
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    return *this;
}

template <typename dtype>
CARTESIAN_COORDINATE<dtype>& CARTESIAN_COORDINATE<dtype>::operator+=(const dtype& c){
    this->x += c;
    this->y += c;
    this->z += c;
    return *this;
}

template <typename dtype>
CARTESIAN_COORDINATE<dtype>& CARTESIAN_COORDINATE<dtype>::operator-=(const CARTESIAN_COORDINATE<dtype>& other){
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    return *this;
}

template <typename dtype>
CARTESIAN_COORDINATE<dtype>& CARTESIAN_COORDINATE<dtype>::operator-=(const dtype& c){
    this->x -= c;
    this->y -= c;
    this->z -= c;
    return *this;
}

template <typename dtype>
CARTESIAN_COORDINATE<dtype>& CARTESIAN_COORDINATE<dtype>::operator*=(const CARTESIAN_COORDINATE<dtype>& other){
    this->x *= other.x;
    this->y *= other.y;
    this->z *= other.z;
    return *this;
}

template <typename dtype>
CARTESIAN_COORDINATE<dtype>& CARTESIAN_COORDINATE<dtype>::operator*=(const dtype& c){
    this->x *= c;
    this->y *= c;
    this->z *= c;
    return *this;
}

template <typename dtype>
CARTESIAN_COORDINATE<dtype>& CARTESIAN_COORDINATE<dtype>::operator/=(const CARTESIAN_COORDINATE<dtype>& other){
    this->x /= other.x;
    this->y /= other.y;
    this->z /= other.z;
    return *this;
}

template <typename dtype>
CARTESIAN_COORDINATE<dtype>& CARTESIAN_COORDINATE<dtype>::operator/=(const dtype& c){
    this->x /= c;
    this->y /= c;
    this->z /= c;
    return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename dtype>
CARTESIAN_COORDINATE<dtype> operator+(const CARTESIAN_COORDINATE<dtype>& lhs, const CARTESIAN_COORDINATE<dtype>& rhs){
    return CARTESIAN_COORDINATE<dtype>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

template <typename dtype>
CARTESIAN_COORDINATE<dtype> operator+(const CARTESIAN_COORDINATE<dtype>& lhs, const dtype& rhs){
    return CARTESIAN_COORDINATE<dtype>(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs);
}

template <typename dtype>
CARTESIAN_COORDINATE<dtype> operator+(const dtype& lhs, const CARTESIAN_COORDINATE<dtype>& rhs){
    return CARTESIAN_COORDINATE<dtype>(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z);
}

template <typename dtype>
CARTESIAN_COORDINATE<dtype> operator-(const CARTESIAN_COORDINATE<dtype>& lhs, const CARTESIAN_COORDINATE<dtype>& rhs){
    return CARTESIAN_COORDINATE<dtype>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

template <typename dtype>
CARTESIAN_COORDINATE<dtype> operator-(const CARTESIAN_COORDINATE<dtype>& lhs, const dtype& rhs){
    return CARTESIAN_COORDINATE<dtype>(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs);
}

template <typename dtype>
CARTESIAN_COORDINATE<dtype> operator-(const dtype& lhs, const CARTESIAN_COORDINATE<dtype>& rhs){
    return CARTESIAN_COORDINATE<dtype>(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z);
}

template <typename dtype>
CARTESIAN_COORDINATE<dtype> operator*(const CARTESIAN_COORDINATE<dtype>& lhs, const CARTESIAN_COORDINATE<dtype>& rhs){
    return CARTESIAN_COORDINATE<dtype>(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
}

template <typename dtype>
CARTESIAN_COORDINATE<dtype> operator*(const CARTESIAN_COORDINATE<dtype>& lhs, const dtype& rhs){
    return CARTESIAN_COORDINATE<dtype>(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}

template <typename dtype>
CARTESIAN_COORDINATE<dtype> operator*(const dtype& lhs, const CARTESIAN_COORDINATE<dtype>& rhs){
    return CARTESIAN_COORDINATE<dtype>(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
}

template <typename dtype>
CARTESIAN_COORDINATE<dtype> operator/(const CARTESIAN_COORDINATE<dtype>& lhs, const CARTESIAN_COORDINATE<dtype>& rhs){
    return CARTESIAN_COORDINATE<dtype>(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
}

template <typename dtype>
CARTESIAN_COORDINATE<dtype> operator/(const CARTESIAN_COORDINATE<dtype>& lhs, const dtype& rhs){
    return CARTESIAN_COORDINATE<dtype>(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
}

template <typename dtype>
CARTESIAN_COORDINATE<dtype> operator/(const dtype& lhs, const CARTESIAN_COORDINATE<dtype>& rhs){
    return CARTESIAN_COORDINATE<dtype>(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename dtype>
bool operator==(const CARTESIAN_COORDINATE<dtype>& lhs, const CARTESIAN_COORDINATE<dtype>& rhs){
    if(lhs.x==rhs.x && lhs.y==rhs.y && lhs.z==rhs.z){
        return true;
    }
    else{
        return false;
    }
}

template <typename dtype>
bool operator!=(const CARTESIAN_COORDINATE<dtype>& lhs, const CARTESIAN_COORDINATE<dtype>& rhs){
    return !(lhs == rhs);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename dtype>
vector<dtype> CARTESIAN_COORDINATE<dtype>::asVector() const{
    vector<dtype> v(3);
    v[0] = x;
    v[1] = y;
    v[2] = z;
    return v;
}

template <typename dtype>
boost::array<dtype, 3> CARTESIAN_COORDINATE<dtype>::asArray() const{
    boost::array<dtype, 3> v;
    v[0] = x;
    v[1] = y;
    v[2] = z;
    return v;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename dtype>
ostream& operator<< (ostream& os, const CARTESIAN_COORDINATE<dtype>& r){
    os << "[" << r.x << ",\t" << r.y << ",\t" << r.z << "]";
    return os;
}
