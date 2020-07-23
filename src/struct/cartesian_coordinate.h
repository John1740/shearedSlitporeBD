//
// Created by mhuels on 7/22/20.
//

#ifndef SHEAREDSLITPOREBD_CARTESIAN_COORDINATE_H
#define SHEAREDSLITPOREBD_CARTESIAN_COORDINATE_H

#include <iostream>
#include <vector>
#include "boost/array.hpp"
using namespace std;

//Member function definitions follow after the declaration (to preserve some organization).
//Exceptions are friend functions that need to be defined within class declaration (otherwise a cumbersome
//forward declaration would be necessary.
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
    dtype operator[](unsigned int i) const;
    dtype& operator[](unsigned int i);

    //assignment operators
    CARTESIAN_COORDINATE& operator=(const CARTESIAN_COORDINATE& other);
    CARTESIAN_COORDINATE& operator=(const dtype& c);

    CARTESIAN_COORDINATE& operator+=(const CARTESIAN_COORDINATE& other);
    CARTESIAN_COORDINATE& operator+=(const dtype& c);

    CARTESIAN_COORDINATE& operator-=(const CARTESIAN_COORDINATE& other);
    CARTESIAN_COORDINATE& operator-=(const dtype& c);

    CARTESIAN_COORDINATE& operator*=(const CARTESIAN_COORDINATE& other);
    CARTESIAN_COORDINATE& operator*=(const dtype& c);

    CARTESIAN_COORDINATE& operator/=(const CARTESIAN_COORDINATE& other);
    CARTESIAN_COORDINATE& operator/=(const dtype& c);

    //conversions
    vector<dtype> asVector() const;
    boost::array<dtype, 3> asArray() const;

    //arithmetic operators
    friend CARTESIAN_COORDINATE operator+(const CARTESIAN_COORDINATE& lhs, const CARTESIAN_COORDINATE& rhs){
        return CARTESIAN_COORDINATE<dtype>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
    }
    friend CARTESIAN_COORDINATE operator+(const CARTESIAN_COORDINATE& lhs, const dtype& rhs){
        return CARTESIAN_COORDINATE<dtype>(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs);
    }
    friend CARTESIAN_COORDINATE operator+(const dtype& lhs, const CARTESIAN_COORDINATE& rhs){
        return CARTESIAN_COORDINATE<dtype>(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z);
    }

    friend CARTESIAN_COORDINATE operator-(const CARTESIAN_COORDINATE& lhs, const CARTESIAN_COORDINATE& rhs){
        return CARTESIAN_COORDINATE<dtype>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
    }
    friend CARTESIAN_COORDINATE operator-(const CARTESIAN_COORDINATE& lhs, const dtype& rhs){
        return CARTESIAN_COORDINATE<dtype>(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs);
    }
    friend CARTESIAN_COORDINATE operator-(const dtype& lhs, const CARTESIAN_COORDINATE& rhs){
        return CARTESIAN_COORDINATE<dtype>(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z);
    }

    friend CARTESIAN_COORDINATE operator*(const CARTESIAN_COORDINATE& lhs, const CARTESIAN_COORDINATE& rhs){
        return CARTESIAN_COORDINATE<dtype>(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
    }
    friend CARTESIAN_COORDINATE operator*(const CARTESIAN_COORDINATE& lhs, const dtype& rhs){
        return CARTESIAN_COORDINATE<dtype>(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
    }
    friend CARTESIAN_COORDINATE operator*(const dtype& lhs, const CARTESIAN_COORDINATE& rhs){
        return CARTESIAN_COORDINATE<dtype>(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
    }

    friend CARTESIAN_COORDINATE operator/(const CARTESIAN_COORDINATE& lhs, const CARTESIAN_COORDINATE& rhs){
        return CARTESIAN_COORDINATE<dtype>(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
    }
    friend CARTESIAN_COORDINATE operator/(const CARTESIAN_COORDINATE& lhs, const dtype& rhs){
        return CARTESIAN_COORDINATE<dtype>(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
    }
    friend CARTESIAN_COORDINATE operator/(const dtype& lhs, const CARTESIAN_COORDINATE& rhs){
        return CARTESIAN_COORDINATE<dtype>(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z);
    }

    //logical operators
    friend bool operator==(const CARTESIAN_COORDINATE& lhs, const CARTESIAN_COORDINATE& rhs){
        if(lhs.x==rhs.x && lhs.y==rhs.y && lhs.z==rhs.z){
            return true;
        }
        else{
            return false;
        }
    }
    friend bool operator!=(const CARTESIAN_COORDINATE& lhs, const CARTESIAN_COORDINATE& rhs){
        if(lhs.x!=rhs.x || lhs.y!=rhs.y || lhs.z!=rhs.z){
            return true;
        }
        else{
            return false;
        }
    }

    //stream handling
    friend ostream& operator<<(ostream& os, const CARTESIAN_COORDINATE<dtype>& r){
        os << "[" << r.x << ",\t" << r.y << ",\t" << r.z << "]";
        return os;
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename dtype>
CARTESIAN_COORDINATE<dtype>::CARTESIAN_COORDINATE(){
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

template <typename dtype>
CARTESIAN_COORDINATE<dtype>::CARTESIAN_COORDINATE(dtype c){
    this->x = c;
    this->y = c;
    this->z = c;
}

template <typename dtype>
CARTESIAN_COORDINATE<dtype>::CARTESIAN_COORDINATE(dtype x, dtype y, dtype z){
    this->x = x;
    this->y = y;
    this->z = z;
}

template <typename dtype>
CARTESIAN_COORDINATE<dtype>::CARTESIAN_COORDINATE(const CARTESIAN_COORDINATE<dtype>& other){
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//const version for the use in assignment operators (e.g. operator=)
template <typename dtype>
dtype CARTESIAN_COORDINATE<dtype>::operator[](unsigned int i) const{
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
dtype& CARTESIAN_COORDINATE<dtype>::operator[](unsigned int i){
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

#endif //SHEAREDSLITPOREBD_CARTESIAN_COORDINATE_H
