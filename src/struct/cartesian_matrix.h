#ifndef CARTESIAN_MATRIX_H
#define CARTESIAN_MATRIX_H

#include "cartesian_coordinate.h"

class CARTESIAN_MATRIX{
public:
    double xx, xy, xz;
    double yx, yy, yz;
    double zx, zy, zz;

    //constructors
    CARTESIAN_MATRIX(): xx(0), xy(0), xz(0), yx(0), yy(0), yz(0), zx(0), zy(0), zz(0){}
//    CARTESIAN_MATRIX();
    CARTESIAN_MATRIX(const double c): xx(c), xy(c), xz(c), yx(c), yy(c), yz(c), zx(c), zy(c), zz(c){}
//    CARTESIAN_MATRIX(double c);
//    CARTESIAN_MATRIX(CARTESIAN_COORDINATE r): xx(r.x), xy(r.y), xz(r.z), yx(r.x), yy(r.y), yz(r.z), zx(r.x), zy(r.y), zz(r.z){}
    CARTESIAN_MATRIX(const CARTESIAN_COORDINATE& col);
//    CARTESIAN_MATRIX(CARTESIAN_COORDINATE col1, CARTESIAN_COORDINATE col2, CARTESIAN_COORDINATE col3): xx(col1.x), xy(col2.x), xz(col3.x), yx(col1.y), yy(col2.y), yz(col3.y), zx(col1.z), zy(col2.z), zz(col3.z){}
    CARTESIAN_MATRIX(const CARTESIAN_COORDINATE& col1, const CARTESIAN_COORDINATE& col2, const CARTESIAN_COORDINATE& col3);
//    CARTESIAN_MATRIX(CARTESIAN_COORDINATE r1, CARTESIAN_COORDINATE r2): xx(r1.x * r2.x), xy(r1.x * r2.y), xz(r1.x * r2.z), yx(r1.y * r2.x), yy(r1.y * r2.y), yz(r1.y * r2.z), zx(r1.z * r2.x), zy(r1.z * r2.y), zz(r1.z * r2.z){}
    CARTESIAN_MATRIX(const CARTESIAN_COORDINATE& r1, const CARTESIAN_COORDINATE& r2);

    double getDeterminant();
//    CARTESIAN_MATRIX& invert();
//    CARTESIAN_MATRIX invert() const;

//    CARTESIAN_MATRIX productWith(const CARTESIAN_MATRIX& rhs);
    CARTESIAN_COORDINATE operator[](int i) const;
//    CARTESIAN_COORDINATE& operator[](int i);

    CARTESIAN_MATRIX& operator+= (CARTESIAN_MATRIX const& cCoordIN);
    CARTESIAN_MATRIX& operator+= (double const& doubleIN){
        return *this += CARTESIAN_MATRIX(doubleIN);
    };

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

    friend ostream& operator<< (ostream& lhs, CARTESIAN_MATRIX const& rhs){
        return lhs << rhs.xx << "\t" << rhs.xy << "\t" << rhs.xz << "\n" << rhs.yx << "\t" << rhs.yy << "\t" << rhs.yz << "\n" << rhs.zx << "\t" << rhs.zy << "\t" << rhs.zz;
    }

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

};

#endif // CARTESIAN_MATRIX_H
