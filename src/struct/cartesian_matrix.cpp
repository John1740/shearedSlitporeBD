#include "cartesian_matrix.h"
#include <stdexcept>

CARTESIAN_MATRIX::CARTESIAN_MATRIX(const CARTESIAN_COORDINATE& col){
    xx = xy = xz = col.x;
    yx = yy = yz = col.y;
    zx = zy = zz = col.z;
}

CARTESIAN_MATRIX::CARTESIAN_MATRIX(const CARTESIAN_COORDINATE& col1, const CARTESIAN_COORDINATE& col2, const CARTESIAN_COORDINATE& col3){
    xx = col1.x; xy = col2.x; xz = col3.x;
    yx = col1.y; yy = col2.y; yz = col3.y;
    zx = col1.z; zy = col2.z; zz = col3.z;
}

CARTESIAN_MATRIX::CARTESIAN_MATRIX(const CARTESIAN_COORDINATE& r1, const CARTESIAN_COORDINATE& r2){
    xx = r1.x * r2.x; xy = r1.x * r2.y; xz = r1.x * r2.z;
    yx = r1.y * r2.x; yy = r1.y * r2.y; yz = r1.y * r2.z;
    zx = r1.z * r2.x; zy = r1.z * r2.y; zz = r1.z * r2.z;
}

CARTESIAN_MATRIX::CARTESIAN_MATRIX(const CARTESIAN_MATRIX& other){
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

//read-only
CARTESIAN_COORDINATE CARTESIAN_MATRIX::operator[](unsigned int i) const{
    double x, y, z;
    switch(i){
        case 0:
            x = xx; y = xy; z = xz;
            break;
        case 1:
            x = yx; y = yy; z = yz;
            break;
        case 2:
            x = zx; y = zy; z = zz;
            break;
        default:
            throw std::out_of_range("CARTESIAN_MATRIX[] out of range.");
    }
    return CARTESIAN_COORDINATE(x, y, z);
}

double CARTESIAN_MATRIX::getDeterminant(){
    return xx * yy * zz + xy * yz * zx + xz * yx * zy - xz * yy * zx - xy * yx * zz - xx * yz * zy;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CARTESIAN_MATRIX& CARTESIAN_MATRIX::operator=(const CARTESIAN_MATRIX& other){
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

CARTESIAN_MATRIX& CARTESIAN_MATRIX::operator=(const double& c){
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

CARTESIAN_MATRIX& CARTESIAN_MATRIX::operator+=(const CARTESIAN_MATRIX& other){
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

CARTESIAN_MATRIX& CARTESIAN_MATRIX::operator+=(const double& c){
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

CARTESIAN_MATRIX& CARTESIAN_MATRIX::operator-=(const CARTESIAN_MATRIX& other){
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

CARTESIAN_MATRIX& CARTESIAN_MATRIX::operator-=(const double& c){
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

CARTESIAN_MATRIX& CARTESIAN_MATRIX::operator*=(const CARTESIAN_MATRIX& other){
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

CARTESIAN_MATRIX& CARTESIAN_MATRIX::operator*=(const double& c){
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

CARTESIAN_MATRIX& CARTESIAN_MATRIX::operator/=(const CARTESIAN_MATRIX& other){
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

CARTESIAN_MATRIX& CARTESIAN_MATRIX::operator/=(const double& c){
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

CARTESIAN_MATRIX operator+(const CARTESIAN_MATRIX& lhs, const CARTESIAN_MATRIX& rhs){
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

CARTESIAN_MATRIX operator+(const double& lhs, const CARTESIAN_MATRIX& rhs){
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

CARTESIAN_MATRIX operator+(const CARTESIAN_MATRIX& lhs, const double& rhs){
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

CARTESIAN_MATRIX operator-(const CARTESIAN_MATRIX& lhs, const CARTESIAN_MATRIX& rhs){
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

CARTESIAN_MATRIX operator-(const double& lhs, const CARTESIAN_MATRIX& rhs){
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

CARTESIAN_MATRIX operator-(const CARTESIAN_MATRIX& lhs, const double& rhs){
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

CARTESIAN_MATRIX operator*(const CARTESIAN_MATRIX& lhs, const CARTESIAN_MATRIX& rhs){
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

CARTESIAN_MATRIX operator*(const double& lhs, const CARTESIAN_MATRIX& rhs){
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

CARTESIAN_MATRIX operator*(const CARTESIAN_MATRIX& lhs, const double& rhs){
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

CARTESIAN_MATRIX operator/(const CARTESIAN_MATRIX& lhs, const CARTESIAN_MATRIX& rhs){
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

CARTESIAN_MATRIX operator/(const double& lhs, const CARTESIAN_MATRIX& rhs){
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

CARTESIAN_MATRIX operator/(const CARTESIAN_MATRIX& lhs, const double& rhs){
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool operator==(const CARTESIAN_MATRIX& lhs, const CARTESIAN_MATRIX& rhs){
    if(lhs.xx==rhs.xx && lhs.xy==rhs.xy && lhs.xz==rhs.xz &&
       lhs.yx==rhs.yx && lhs.yy==rhs.yy && lhs.yz==rhs.yz &&
       lhs.zx==rhs.zx && lhs.zy==rhs.zy && lhs.zz==rhs.zz){
        return true;
    }
    else{
        return false;
    }
}

bool operator!=(const CARTESIAN_MATRIX& lhs, const CARTESIAN_MATRIX& rhs){
    if(lhs.xx!=rhs.xx && lhs.xy!=rhs.xy && lhs.xz!=rhs.xz &&
       lhs.yx!=rhs.yx && lhs.yy!=rhs.yy && lhs.yz!=rhs.yz &&
       lhs.zx!=rhs.zx && lhs.zy!=rhs.zy && lhs.zz!=rhs.zz){
        return true;
    }
    else{
        return false;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ostream& operator<<(ostream& os, const CARTESIAN_MATRIX& A){
    os << "[";
    os << A[0] << ",\n ";
    os << A[1] << ",\n ";
    os << A[2];
    os << "]";
    return os;
}