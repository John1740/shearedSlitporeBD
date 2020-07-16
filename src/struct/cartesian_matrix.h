#ifndef CARTESIAN_MATRIX_H
#define CARTESIAN_MATRIX_H

#include "cartesian_coordinate.h"

class CARTESIAN_MATRIX{
    //This is completely hard-coded to improve performance. Another (slower) concept, that has been tried, is:
    //CARTESIAN_COORDINATE x, y, z, accessing via (*this).x.x
    //Access of single components is fast, but any operator or constructor that uses a function of CARTESIAN_COORDINATE
    //is much slower. Same goes for the fact that the members here are public. Making them private and using getter- and
    //setter-functions slows down the program harshly.
public:
    double xx, xy, xz;
    double yx, yy, yz;
    double zx, zy, zz;

    //constructors
    CARTESIAN_MATRIX(): xx(0), xy(0), xz(0), yx(0), yy(0), yz(0), zx(0), zy(0), zz(0){}
    CARTESIAN_MATRIX(const double c): xx(c), xy(c), xz(c), yx(c), yy(c), yz(c), zx(c), zy(c), zz(c){}
    CARTESIAN_MATRIX(const CARTESIAN_COORDINATE& col);
    CARTESIAN_MATRIX(const CARTESIAN_COORDINATE& col1, const CARTESIAN_COORDINATE& col2, const CARTESIAN_COORDINATE& col3);
    CARTESIAN_MATRIX(const CARTESIAN_COORDINATE& r1, const CARTESIAN_COORDINATE& r2);
    
    //functions
    double getDeterminant();
//    CARTESIAN_MATRIX& invert();
//    CARTESIAN_MATRIX invert() const;
//    CARTESIAN_COORDINATE diag() const;
//    CARTESIAN_MATRIX dot(const CARTESIAN_MATRIX& rhs);
    
    //type cast operators?
    
    //index operators
    CARTESIAN_COORDINATE operator[](unsigned int i) const;
    
    //assignment operators
    CARTESIAN_MATRIX& operator= (const CARTESIAN_MATRIX& cCoordIN);
    CARTESIAN_MATRIX& operator= (const double& doubleIN);
    
    CARTESIAN_MATRIX& operator+= (const CARTESIAN_MATRIX& cCoordIN);
    CARTESIAN_MATRIX& operator+= (const double& doubleIN);

    CARTESIAN_MATRIX& operator-= (CARTESIAN_MATRIX const& cCoordIN);
    CARTESIAN_MATRIX& operator-= (double const& doubleIN){
        return *this -= CARTESIAN_MATRIX(doubleIN);
    };

    CARTESIAN_MATRIX& operator*= (CARTESIAN_MATRIX const& cCoordIN);
    CARTESIAN_MATRIX& operator*= (double const& doubleIN){
        return *this *= CARTESIAN_MATRIX(doubleIN);
    };

    CARTESIAN_MATRIX& operator/= (CARTESIAN_MATRIX const& cCoordIN);
    CARTESIAN_MATRIX& operator/= (double const& doubleIN){
        return *this /= CARTESIAN_MATRIX(doubleIN);
    };
    
    //arithmetic operators
    friend CARTESIAN_MATRIX operator+ (CARTESIAN_MATRIX const& lhs, CARTESIAN_MATRIX const& rhs){
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
    };
    friend CARTESIAN_MATRIX operator+ (double const& lhs, CARTESIAN_MATRIX const& rhs){
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
    };
    friend CARTESIAN_MATRIX operator+ (CARTESIAN_MATRIX const& lhs, double const& rhs){
        CARTESIAN_MATRIX result;
        result = rhs + lhs;
        return result;
    };

    friend CARTESIAN_MATRIX operator- (CARTESIAN_MATRIX const& lhs, CARTESIAN_MATRIX const& rhs){
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
    };
    friend CARTESIAN_MATRIX operator- (double const& lhs, CARTESIAN_MATRIX const& rhs){
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
    };
    friend CARTESIAN_MATRIX operator- (CARTESIAN_MATRIX const& lhs, double const& rhs){
        CARTESIAN_MATRIX result;
        result = -1*rhs + lhs;
        return result;
    };

    friend CARTESIAN_MATRIX operator* (CARTESIAN_MATRIX const& lhs, CARTESIAN_MATRIX const& rhs){
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
    };
    friend CARTESIAN_MATRIX operator* (double const& lhs, CARTESIAN_MATRIX const& rhs){
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
    };
    friend CARTESIAN_MATRIX operator* (CARTESIAN_MATRIX const& lhs, double const& rhs){
        CARTESIAN_MATRIX result;
        result = rhs * lhs;
        return result;
    };

    friend CARTESIAN_MATRIX operator/ (CARTESIAN_MATRIX const& lhs, CARTESIAN_MATRIX const& rhs){
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
    };
    friend CARTESIAN_MATRIX operator/ (double const& lhs, CARTESIAN_MATRIX const& rhs){
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
    };
    friend CARTESIAN_MATRIX operator/ (CARTESIAN_MATRIX const& lhs, double const& rhs){
        CARTESIAN_MATRIX result;
        result = lhs * (1./rhs);
        return result;
    };
    
    //logical operators
    friend bool operator== (const CARTESIAN_MATRIX& lhs, const CARTESIAN_MATRIX& rhs){
        if(lhs.xx==rhs.xx && lhs.xy==rhs.xy && lhs.xz==rhs.xz && lhs.yx==rhs.yx && lhs.yy==rhs.yy && lhs.yz==rhs.yz && lhs.zx==rhs.zx && lhs.zy==rhs.zy && lhs.zz==rhs.zz){
            return true;
        }
        else{
            return false;
        }
    };

    friend bool operator!= (const CARTESIAN_MATRIX& lhs, const CARTESIAN_MATRIX& rhs){
        return ! (lhs == rhs);
    };
    
    //conversions
    vector<vector<double>> asVector() const;
    vector<double> asFlatVector() const;
    
    //stream handling
    friend ostream& operator<< (ostream& lhs, CARTESIAN_MATRIX const& rhs){
        return lhs << rhs.xx << "\t" << rhs.xy << "\t" << rhs.xz << "\n" << rhs.yx << "\t" << rhs.yy << "\t" << rhs.yz << "\n" << rhs.zx << "\t" << rhs.zy << "\t" << rhs.zz;
    }
};

#endif // CARTESIAN_MATRIX_H
