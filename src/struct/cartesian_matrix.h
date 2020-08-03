//
// Created by mhuelsberg on 30.07.20.
//

#ifndef SHEAREDSLITPOREBD_CARTESIAN_MATRIX_H
#define SHEAREDSLITPOREBD_CARTESIAN_MATRIX_H

#include "cartesian_coordinate.h"
#include <iostream>
#include <vector>
#include "boost/array.hpp"
#include <stdexcept>
using namespace std;

template <typename dtype>
class CARTESIAN_MATRIX{
    //This is completely hard-coded to improve performance. Another (slower) concept, that has been tried, is:
    //CARTESIAN_COORDINATE x, y, z, accessing via (*this).x.x
    //Access of single components is fast, but any operator or constructor that uses a function of CARTESIAN_COORDINATE
    //is much slower.
    //
    //Same goes for the fact that the members here are public. Making them private and using getter- and
    //setter-functions slows down the program harshly.
    //
    //Arithmetic operators also don't refer to each other, which might seem redundant, but this also improves calculation
    //speed roughly by a factor 2.
public:
    dtype xx, xy, xz;
    dtype yx, yy, yz;
    dtype zx, zy, zz;

    //constructors
    CARTESIAN_MATRIX(): xx(0), xy(0), xz(0), yx(0), yy(0), yz(0), zx(0), zy(0), zz(0){}
    CARTESIAN_MATRIX(const dtype c): xx(c), xy(c), xz(c), yx(c), yy(c), yz(c), zx(c), zy(c), zz(c){}
    CARTESIAN_MATRIX(const CARTESIAN_COORDINATE<dtype>& col);
    CARTESIAN_MATRIX(const CARTESIAN_COORDINATE<dtype>& col1, const CARTESIAN_COORDINATE<dtype>& col2, const CARTESIAN_COORDINATE<dtype>& col3);
    CARTESIAN_MATRIX(const CARTESIAN_COORDINATE<dtype>& r1, const CARTESIAN_COORDINATE<dtype>& r2);
    CARTESIAN_MATRIX(const CARTESIAN_MATRIX& other);

    //functions
    dtype determinant() const;
    CARTESIAN_COORDINATE<dtype> diag() const;
    CARTESIAN_MATRIX& transposeInPlace();
    CARTESIAN_MATRIX transpose() const;
    CARTESIAN_MATRIX dot(const CARTESIAN_MATRIX& rhs);
    CARTESIAN_COORDINATE<dtype> dot(const CARTESIAN_COORDINATE<dtype>& rhs);
    CARTESIAN_MATRIX<double> real() const;
    CARTESIAN_MATRIX<double> imag() const;
    CARTESIAN_MATRIX& real(const CARTESIAN_MATRIX<double>& r);
    CARTESIAN_MATRIX& imag(const CARTESIAN_MATRIX<double>& i);

    //index operators
    dtype  operator()(unsigned int row, unsigned int col) const;
    dtype& operator()(unsigned int row, unsigned int col);
    //read-only
    CARTESIAN_COORDINATE<dtype> operator[](unsigned int row) const;
    CARTESIAN_COORDINATE<dtype> row(unsigned int i) const;
    CARTESIAN_COORDINATE<dtype> col(unsigned int i) const;

    //assignment operators
    CARTESIAN_MATRIX& operator=(const CARTESIAN_MATRIX& other);
    CARTESIAN_MATRIX& operator=(const dtype& c);

    CARTESIAN_MATRIX& operator+=(const CARTESIAN_MATRIX& other);
    CARTESIAN_MATRIX& operator+=(const dtype& c);

    CARTESIAN_MATRIX& operator-=(const CARTESIAN_MATRIX& other);
    CARTESIAN_MATRIX& operator-=(const dtype& c);

    CARTESIAN_MATRIX& operator*=(const CARTESIAN_MATRIX& other);
    CARTESIAN_MATRIX& operator*=(const dtype& c);

    CARTESIAN_MATRIX& operator/=(const CARTESIAN_MATRIX& other);
    CARTESIAN_MATRIX& operator/=(const dtype& c);

    //conversions
    //quiet slow
    boost::array<boost::array<dtype, 3>, 3> asArray() const;
    boost::array<dtype, 9> asFlatArray() const;
    //quiet fast
    vector<vector<dtype>> asVector() const;
    vector<dtype> asFlatVector() const;

    //arithmetic operators
    friend CARTESIAN_MATRIX operator+(const CARTESIAN_MATRIX& lhs, const CARTESIAN_MATRIX& rhs){
        CARTESIAN_MATRIX result;
        result.xx = lhs.xx + rhs.xx;
        result.xy = lhs.xy + rhs.xy;
        result.xz = lhs.xz + rhs.xz;
        result.yx = lhs.yx + rhs.yx;
        result.yy = lhs.yy + rhs.yy;
        result.yz = lhs.yz + rhs.yz;
        result.zx = lhs.zx + rhs.zx;
        result.zy = lhs.zy + rhs.zy;
        result.zz = lhs.zz + rhs.zz;
        return result;
    }

    friend CARTESIAN_MATRIX operator+(const dtype& lhs, const CARTESIAN_MATRIX& rhs){
        CARTESIAN_MATRIX result;
        result.xx = lhs + rhs.xx;
        result.xy = lhs + rhs.xy;
        result.xz = lhs + rhs.xz;
        result.yx = lhs + rhs.yx;
        result.yy = lhs + rhs.yy;
        result.yz = lhs + rhs.yz;
        result.zx = lhs + rhs.zx;
        result.zy = lhs + rhs.zy;
        result.zz = lhs + rhs.zz;
        return result;
    }

    friend CARTESIAN_MATRIX operator+(const CARTESIAN_MATRIX& lhs, const dtype& rhs){
        CARTESIAN_MATRIX result;
        result.xx = lhs.xx + rhs;
        result.xy = lhs.xy + rhs;
        result.xz = lhs.xz + rhs;
        result.yx = lhs.yx + rhs;
        result.yy = lhs.yy + rhs;
        result.yz = lhs.yz + rhs;
        result.zx = lhs.zx + rhs;
        result.zy = lhs.zy + rhs;
        result.zz = lhs.zz + rhs;
        return result;
    }

    friend CARTESIAN_MATRIX operator-(const CARTESIAN_MATRIX& lhs, const CARTESIAN_MATRIX& rhs){
        CARTESIAN_MATRIX result;
        result.xx = lhs.xx - rhs.xx;
        result.xy = lhs.xy - rhs.xy;
        result.xz = lhs.xz - rhs.xz;
        result.yx = lhs.yx - rhs.yx;
        result.yy = lhs.yy - rhs.yy;
        result.yz = lhs.yz - rhs.yz;
        result.zx = lhs.zx - rhs.zx;
        result.zy = lhs.zy - rhs.zy;
        result.zz = lhs.zz - rhs.zz;
        return result;
    }

    friend CARTESIAN_MATRIX operator-(const dtype& lhs, const CARTESIAN_MATRIX& rhs){
        CARTESIAN_MATRIX result;
        result.xx = lhs - rhs.xx;
        result.xy = lhs - rhs.xy;
        result.xz = lhs - rhs.xz;
        result.yx = lhs - rhs.yx;
        result.yy = lhs - rhs.yy;
        result.yz = lhs - rhs.yz;
        result.zx = lhs - rhs.zx;
        result.zy = lhs - rhs.zy;
        result.zz = lhs - rhs.zz;
        return result;
    }

    friend CARTESIAN_MATRIX operator-(const CARTESIAN_MATRIX& lhs, const dtype& rhs){
        CARTESIAN_MATRIX result;
        result.xx = lhs.xx - rhs;
        result.xy = lhs.xy - rhs;
        result.xz = lhs.xz - rhs;
        result.yx = lhs.yx - rhs;
        result.yy = lhs.yy - rhs;
        result.yz = lhs.yz - rhs;
        result.zx = lhs.zx - rhs;
        result.zy = lhs.zy - rhs;
        result.zz = lhs.zz - rhs;
        return result;
    }

    friend CARTESIAN_MATRIX operator*(const CARTESIAN_MATRIX& lhs, const CARTESIAN_MATRIX& rhs){
        CARTESIAN_MATRIX result;
        result.xx = lhs.xx * rhs.xx;
        result.xy = lhs.xy * rhs.xy;
        result.xz = lhs.xz * rhs.xz;
        result.yx = lhs.yx * rhs.yx;
        result.yy = lhs.yy * rhs.yy;
        result.yz = lhs.yz * rhs.yz;
        result.zx = lhs.zx * rhs.zx;
        result.zy = lhs.zy * rhs.zy;
        result.zz = lhs.zz * rhs.zz;
        return result;
    }

    friend CARTESIAN_MATRIX operator*(const dtype& lhs, const CARTESIAN_MATRIX& rhs){
        CARTESIAN_MATRIX result;
        result.xx = lhs * rhs.xx;
        result.xy = lhs * rhs.xy;
        result.xz = lhs * rhs.xz;
        result.yx = lhs * rhs.yx;
        result.yy = lhs * rhs.yy;
        result.yz = lhs * rhs.yz;
        result.zx = lhs * rhs.zx;
        result.zy = lhs * rhs.zy;
        result.zz = lhs * rhs.zz;
        return result;
    }

    friend CARTESIAN_MATRIX operator*(const CARTESIAN_MATRIX& lhs, const dtype& rhs){
        CARTESIAN_MATRIX result;
        result.xx = lhs.xx * rhs;
        result.xy = lhs.xy * rhs;
        result.xz = lhs.xz * rhs;
        result.yx = lhs.yx * rhs;
        result.yy = lhs.yy * rhs;
        result.yz = lhs.yz * rhs;
        result.zx = lhs.zx * rhs;
        result.zy = lhs.zy * rhs;
        result.zz = lhs.zz * rhs;
        return result;
    }

    friend CARTESIAN_MATRIX operator/(const CARTESIAN_MATRIX& lhs, const CARTESIAN_MATRIX& rhs){
        CARTESIAN_MATRIX result;
        result.xx = lhs.xx / rhs.xx;
        result.xy = lhs.xy / rhs.xy;
        result.xz = lhs.xz / rhs.xz;
        result.yx = lhs.yx / rhs.yx;
        result.yy = lhs.yy / rhs.yy;
        result.yz = lhs.yz / rhs.yz;
        result.zx = lhs.zx / rhs.zx;
        result.zy = lhs.zy / rhs.zy;
        result.zz = lhs.zz / rhs.zz;
        return result;
    }

    friend CARTESIAN_MATRIX operator/(const dtype& lhs, const CARTESIAN_MATRIX& rhs){
        CARTESIAN_MATRIX result;
        result.xx = lhs / rhs.xx;
        result.xy = lhs / rhs.xy;
        result.xz = lhs / rhs.xz;
        result.yx = lhs / rhs.yx;
        result.yy = lhs / rhs.yy;
        result.yz = lhs / rhs.yz;
        result.zx = lhs / rhs.zx;
        result.zy = lhs / rhs.zy;
        result.zz = lhs / rhs.zz;
        return result;
    }

    friend CARTESIAN_MATRIX operator/(const CARTESIAN_MATRIX& lhs, const dtype& rhs){
        CARTESIAN_MATRIX result;
        result.xx = lhs.xx / rhs;
        result.xy = lhs.xy / rhs;
        result.xz = lhs.xz / rhs;
        result.yx = lhs.yx / rhs;
        result.yy = lhs.yy / rhs;
        result.yz = lhs.yz / rhs;
        result.zx = lhs.zx / rhs;
        result.zy = lhs.zy / rhs;
        result.zz = lhs.zz / rhs;
        return result;
    }

    //logical operators
    friend bool operator==(const CARTESIAN_MATRIX& lhs, const CARTESIAN_MATRIX& rhs){
        if(lhs.xx==rhs.xx && lhs.xy==rhs.xy && lhs.xz==rhs.xz &&
           lhs.yx==rhs.yx && lhs.yy==rhs.yy && lhs.yz==rhs.yz &&
           lhs.zx==rhs.zx && lhs.zy==rhs.zy && lhs.zz==rhs.zz){
            return true;
        }
        else{
            return false;
        }
    }

    friend bool operator!=(const CARTESIAN_MATRIX& lhs, const CARTESIAN_MATRIX& rhs){
        if(lhs.xx!=rhs.xx && lhs.xy!=rhs.xy && lhs.xz!=rhs.xz &&
           lhs.yx!=rhs.yx && lhs.yy!=rhs.yy && lhs.yz!=rhs.yz &&
           lhs.zx!=rhs.zx && lhs.zy!=rhs.zy && lhs.zz!=rhs.zz){
            return true;
        }
        else{
            return false;
        }
    }

    //stream handling
    friend ostream& operator<<(ostream& os, const CARTESIAN_MATRIX& A){
        os << "[";
        os << A[0] << ",\n ";
        os << A[1] << ",\n ";
        os << A[2];
        os << "]";
        return os;
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename dtype>
CARTESIAN_MATRIX<dtype>::CARTESIAN_MATRIX(const CARTESIAN_COORDINATE<dtype>& col){
    xx = xy = xz = col.x;
    yx = yy = yz = col.y;
    zx = zy = zz = col.z;
}

template <typename dtype>
CARTESIAN_MATRIX<dtype>::CARTESIAN_MATRIX(const CARTESIAN_COORDINATE<dtype>& col1, const CARTESIAN_COORDINATE<dtype>& col2, const CARTESIAN_COORDINATE<dtype>& col3){
    xx = col1.x; xy = col2.x; xz = col3.x;
    yx = col1.y; yy = col2.y; yz = col3.y;
    zx = col1.z; zy = col2.z; zz = col3.z;
}

template <typename dtype>
CARTESIAN_MATRIX<dtype>::CARTESIAN_MATRIX(const CARTESIAN_COORDINATE<dtype>& r1, const CARTESIAN_COORDINATE<dtype>& r2){
    xx = r1.x * r2.x; xy = r1.x * r2.y; xz = r1.x * r2.z;
    yx = r1.y * r2.x; yy = r1.y * r2.y; yz = r1.y * r2.z;
    zx = r1.z * r2.x; zy = r1.z * r2.y; zz = r1.z * r2.z;
}

template <class dtype>
CARTESIAN_MATRIX<dtype>::CARTESIAN_MATRIX(const CARTESIAN_MATRIX& other){
    this->xx = other.xx;
    this->xy = other.xy;
    this->xz = other.xz;
    this->yx = other.yx;
    this->yy = other.yy;
    this->yz = other.yz;
    this->zx = other.zx;
    this->zy = other.zy;
    this->zz = other.zz;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename dtype>
dtype CARTESIAN_MATRIX<dtype>::determinant() const{
    return xx * yy * zz + xy * yz * zx + xz * yx * zy - xz * yy * zx - xy * yx * zz - xx * yz * zy;
}

template <typename dtype>
CARTESIAN_COORDINATE<dtype> CARTESIAN_MATRIX<dtype>::diag() const{
    return CARTESIAN_COORDINATE<dtype>(xx, yy, zz);;
}

template <typename dtype>
CARTESIAN_MATRIX<dtype>& CARTESIAN_MATRIX<dtype>::transposeInPlace(){
    dtype tmp;
    tmp = xy; xy = yx; yx = tmp;
    tmp = xz; xz = zx; zx = tmp;
    tmp = yz; yz = zy; zy = tmp;
    return *this;
}

template <typename dtype>
CARTESIAN_MATRIX<dtype> CARTESIAN_MATRIX<dtype>::transpose() const{
    CARTESIAN_MATRIX result;
    result.xx = xx;
    result.xy = yx;
    result.xz = zx;
    result.yx = xy;
    result.yy = yy;
    result.yz = zy;
    result.zx = xz;
    result.zy = yz;
    result.zz = zz;
    return result;
}

template <typename dtype>
CARTESIAN_MATRIX<dtype> CARTESIAN_MATRIX<dtype>::dot(const CARTESIAN_MATRIX& rhs){
    CARTESIAN_MATRIX result;
    result.xx = xx * rhs.xx + xy * rhs.yx + xz * rhs.zx;
    result.xy = xx * rhs.xy + xy * rhs.yy + xz * rhs.zy;
    result.xz = xx * rhs.xz + xy * rhs.yz + xz * rhs.zz;
    result.yx = yx * rhs.xx + yy * rhs.yx + yz * rhs.zx;
    result.yy = yx * rhs.xy + yy * rhs.yy + yz * rhs.zy;
    result.yz = yx * rhs.xz + yy * rhs.yz + yz * rhs.zz;
    result.zx = zx * rhs.xx + zy * rhs.yx + zz * rhs.zx;
    result.zy = zx * rhs.xy + zy * rhs.yy + zz * rhs.zy;
    result.zz = zx * rhs.xz + zy * rhs.yz + zz * rhs.zz;
    return result;
}

template <typename dtype>
CARTESIAN_COORDINATE<dtype> CARTESIAN_MATRIX<dtype>::dot(const CARTESIAN_COORDINATE<dtype>& rhs){
    CARTESIAN_COORDINATE<dtype> result;
    result.x = xx * rhs.x + xy * rhs.y + xz * rhs.z;
    result.y = yx * rhs.x + yy * rhs.y + yz * rhs.z;
    result.z = zx * rhs.x + zy * rhs.y + zz * rhs.z;
    return result;
}

template <typename dtype>
CARTESIAN_MATRIX<double> CARTESIAN_MATRIX<dtype>::real() const{
    throw runtime_error(string("real() is not implemented for the following datatype/class: ") + typeid(xx).name());
}

template <typename dtype>
CARTESIAN_MATRIX<double> CARTESIAN_MATRIX<dtype>::imag() const{
    throw runtime_error(string("imag() is not implemented for the following datatype/class: ") + typeid(xx).name());
}

template<typename dtype>
CARTESIAN_MATRIX<dtype>& CARTESIAN_MATRIX<dtype>::real(const CARTESIAN_MATRIX<double>& r){
    throw runtime_error(string("real() is not implemented for the following datatype/class: ") + typeid(xx).name());
}

template<typename dtype>
CARTESIAN_MATRIX<dtype>& CARTESIAN_MATRIX<dtype>::imag(const CARTESIAN_MATRIX<double>& i){
    throw runtime_error(string("imag() is not implemented for the following datatype/class: ") + typeid(xx).name());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename dtype>
dtype CARTESIAN_MATRIX<dtype>::operator()(unsigned int row, unsigned int col) const{
    switch(row){
        case 0:
            switch(col){
                case 0:
                    return xx;
                case 1:
                    return xy;
                case 2:
                    return xz;
                default:
                    throw std::out_of_range("col out of range.");
            }
        case 1:
            switch(col){
                case 0:
                    return yx;
                case 1:
                    return yy;
                case 2:
                    return yz;
                default:
                    throw std::out_of_range("col out of range.");
            }
        case 2:
            switch(col){
                case 0:
                    return zx;
                case 1:
                    return zy;
                case 2:
                    return zz;
                default:
                    throw std::out_of_range("col out of range.");
            }
        default:
            throw std::out_of_range("row out of range.");
    }
}

template <typename dtype>
dtype& CARTESIAN_MATRIX<dtype>::operator()(unsigned int row, unsigned int col){
    switch(row){
        case 0:
            switch(col){
                case 0:
                    return xx;
                case 1:
                    return xy;
                case 2:
                    return xz;
                default:
                    throw std::out_of_range("col() out of range.");
            }
        case 1:
            switch(col){
                case 0:
                    return yx;
                case 1:
                    return yy;
                case 2:
                    return yz;
                default:
                    throw std::out_of_range("col() out of range.");
            }
        case 2:
            switch(col){
                case 0:
                    return zx;
                case 1:
                    return zy;
                case 2:
                    return zz;
                default:
                    throw std::out_of_range("col() out of range.");
            }
        default:
            throw std::out_of_range("row() out of range.");
    }
}

template <typename dtype>
CARTESIAN_COORDINATE<dtype> CARTESIAN_MATRIX<dtype>::operator[](unsigned int row) const{
    switch(row){
        case 0:
            return CARTESIAN_COORDINATE<dtype>(xx, xy, xz);
        case 1:
            return CARTESIAN_COORDINATE<dtype>(yx, yy, yz);
        case 2:
            return CARTESIAN_COORDINATE<dtype>(zx, zy, zz);
        default:
            throw std::out_of_range("CARTESIAN_MATRIX<dtype>[] out of range.");
    }
}

template <typename dtype>
CARTESIAN_COORDINATE<dtype> CARTESIAN_MATRIX<dtype>::row(unsigned int i) const{
    switch(i){
        case 0:
            return CARTESIAN_COORDINATE<dtype>(xx, xy, xz);
        case 1:
            return CARTESIAN_COORDINATE<dtype>(yx, yy, yz);
        case 2:
            return CARTESIAN_COORDINATE<dtype>(zx, zy, zz);
        default:
            throw std::out_of_range("row() out of range.");
    }
}

template <typename dtype>
CARTESIAN_COORDINATE<dtype> CARTESIAN_MATRIX<dtype>::col(unsigned int i) const{
    switch(i){
        case 0:
            return CARTESIAN_COORDINATE<dtype>(xx, yx, zx);
        case 1:
            return CARTESIAN_COORDINATE<dtype>(xy, yy, zy);
        case 2:
            return CARTESIAN_COORDINATE<dtype>(xz, yz, zz);
        default:
            throw std::out_of_range("col() out of range.");
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename dtype>
CARTESIAN_MATRIX<dtype>& CARTESIAN_MATRIX<dtype>::operator=(const CARTESIAN_MATRIX& other){
    this->xx = other.xx;
    this->xy = other.xy;
    this->xz = other.xz;
    this->yx = other.yx;
    this->yy = other.yy;
    this->yz = other.yz;
    this->zx = other.zx;
    this->zy = other.zy;
    this->zz = other.zz;
    return *this;
}

template <typename dtype>
CARTESIAN_MATRIX<dtype>& CARTESIAN_MATRIX<dtype>::operator=(const dtype& c){
    this->xx = c;
    this->xy = c;
    this->xz = c;
    this->yx = c;
    this->yy = c;
    this->yz = c;
    this->zx = c;
    this->zy = c;
    this->zz = c;
    return *this;
}

template <typename dtype>
CARTESIAN_MATRIX<dtype>& CARTESIAN_MATRIX<dtype>::operator+=(const CARTESIAN_MATRIX& other){
    this->xx += other.xx;
    this->xy += other.xy;
    this->xz += other.xz;
    this->yx += other.yx;
    this->yy += other.yy;
    this->yz += other.yz;
    this->zx += other.zx;
    this->zy += other.zy;
    this->zz += other.zz;
    return *this;
}

template <typename dtype>
CARTESIAN_MATRIX<dtype>& CARTESIAN_MATRIX<dtype>::operator+=(const dtype& c){
    this->xx += c;
    this->xy += c;
    this->xz += c;
    this->yx += c;
    this->yy += c;
    this->yz += c;
    this->zx += c;
    this->zy += c;
    this->zz += c;
    return *this;
}

template <typename dtype>
CARTESIAN_MATRIX<dtype>& CARTESIAN_MATRIX<dtype>::operator-=(const CARTESIAN_MATRIX& other){
    this->xx -= other.xx;
    this->xy -= other.xy;
    this->xz -= other.xz;
    this->yx -= other.yx;
    this->yy -= other.yy;
    this->yz -= other.yz;
    this->zx -= other.zx;
    this->zy -= other.zy;
    this->zz -= other.zz;
    return *this;
}

template <typename dtype>
CARTESIAN_MATRIX<dtype>& CARTESIAN_MATRIX<dtype>::operator-=(const dtype& c){
    this->xx -= c;
    this->xy -= c;
    this->xz -= c;
    this->yx -= c;
    this->yy -= c;
    this->yz -= c;
    this->zx -= c;
    this->zy -= c;
    this->zz -= c;
    return *this;
}

template <typename dtype>
CARTESIAN_MATRIX<dtype>& CARTESIAN_MATRIX<dtype>::operator*=(const CARTESIAN_MATRIX& other){
    this->xx *= other.xx;
    this->xy *= other.xy;
    this->xz *= other.xz;
    this->yx *= other.yx;
    this->yy *= other.yy;
    this->yz *= other.yz;
    this->zx *= other.zx;
    this->zy *= other.zy;
    this->zz *= other.zz;
    return *this;
}

template <typename dtype>
CARTESIAN_MATRIX<dtype>& CARTESIAN_MATRIX<dtype>::operator*=(const dtype& c){
    this->xx *= c;
    this->xy *= c;
    this->xz *= c;
    this->yx *= c;
    this->yy *= c;
    this->yz *= c;
    this->zx *= c;
    this->zy *= c;
    this->zz *= c;
    return *this;
}

template <typename dtype>
CARTESIAN_MATRIX<dtype>& CARTESIAN_MATRIX<dtype>::operator/=(const CARTESIAN_MATRIX& other){
    this->xx /= other.xx;
    this->xy /= other.xy;
    this->xz /= other.xz;
    this->yx /= other.yx;
    this->yy /= other.yy;
    this->yz /= other.yz;
    this->zx /= other.zx;
    this->zy /= other.zy;
    this->zz /= other.zz;
    return *this;
}

template <typename dtype>
CARTESIAN_MATRIX<dtype>& CARTESIAN_MATRIX<dtype>::operator/=(const dtype& c){
    this->xx /= c;
    this->xy /= c;
    this->xz /= c;
    this->yx /= c;
    this->yy /= c;
    this->yz /= c;
    this->zx /= c;
    this->zy /= c;
    this->zz /= c;
    return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename dtype>
boost::array<boost::array<dtype, 3>, 3> CARTESIAN_MATRIX<dtype>::asArray() const{
    boost::array<boost::array<dtype, 3>, 3> v;
    v[0][0] = xx;
    v[0][1] = xy;
    v[0][2] = xz;
    v[1][0] = yx;
    v[1][1] = yy;
    v[1][2] = yz;
    v[2][0] = zx;
    v[2][1] = zy;
    v[2][2] = zz;
    return v;
}

template <typename dtype>
boost::array<dtype, 9> CARTESIAN_MATRIX<dtype>::asFlatArray() const{
    boost::array<dtype, 9> v;
    v[0] = xx;
    v[1] = xy;
    v[2] = xz;
    v[3] = yx;
    v[4] = yy;
    v[5] = yz;
    v[6] = zx;
    v[7] = zy;
    v[8] = zz;
    return v;
}

template <typename dtype>
vector<vector<dtype>> CARTESIAN_MATRIX<dtype>::asVector() const{
    vector<vector<dtype>> v(3);
    v[0] = (*this)[0].asVector();
    v[1] = (*this)[1].asVector();
    v[2] = (*this)[2].asVector();
    return v;
}

template <typename dtype>
vector<dtype> CARTESIAN_MATRIX<dtype>::asFlatVector() const{
    vector<dtype> v(9);
    v[0] = xx;
    v[1] = xy;
    v[2] = xz;
    v[3] = yx;
    v[4] = yy;
    v[5] = yz;
    v[6] = zx;
    v[7] = zy;
    v[8] = zz;
    return v;
}

#endif //SHEAREDSLITPOREBD_CARTESIAN_MATRIX_H
