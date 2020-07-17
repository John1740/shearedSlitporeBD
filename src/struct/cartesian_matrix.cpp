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

double CARTESIAN_MATRIX::determinant() const{
    return xx * yy * zz + xy * yz * zx + xz * yx * zy - xz * yy * zx - xy * yx * zz - xx * yz * zy;
}

CARTESIAN_COORDINATE CARTESIAN_MATRIX::diag() const{
    return CARTESIAN_COORDINATE(xx, yy, zz);;
}

CARTESIAN_MATRIX& CARTESIAN_MATRIX::transposeInPlace(){
    double tmp;
    tmp = xy; xy = yx; yx = tmp;
    tmp = xz; xz = zx; zx = tmp;
    tmp = yz; yz = zy; zy = tmp;
    return *this;
}

CARTESIAN_MATRIX CARTESIAN_MATRIX::transpose() const{
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

CARTESIAN_MATRIX CARTESIAN_MATRIX::dot(const CARTESIAN_MATRIX& rhs){
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

//CARTESIAN_MATRIX CARTESIAN_MATRIX::dot(const CARTESIAN_MATRIX& rhs){
//    CARTESIAN_MATRIX result;
//    for(int i=0; i < 3; i++){
//        for(int j=0; j < 3; j++){
//            for(int k=0; k < 3; k++){
//                result(i, j) += (*this)(i, k) * rhs(k, j);
//            }
//        }
//    }
//    return result;
//}

CARTESIAN_COORDINATE CARTESIAN_MATRIX::dot(const CARTESIAN_COORDINATE& rhs){
    CARTESIAN_COORDINATE result;
    result.x = xx * rhs.x + xy * rhs.y + xz * rhs.z;
    result.y = yx * rhs.x + yy * rhs.y + yz * rhs.z;
    result.z = zx * rhs.x + zy * rhs.y + zz * rhs.z;
    return result;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double CARTESIAN_MATRIX::operator()(unsigned int row, unsigned int col) const{
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

double& CARTESIAN_MATRIX::operator()(unsigned int row, unsigned int col){
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

CARTESIAN_COORDINATE CARTESIAN_MATRIX::operator[](unsigned int row) const{
    switch(row){
        case 0:
            return CARTESIAN_COORDINATE(xx, xy, xz);
        case 1:
            return CARTESIAN_COORDINATE(yx, yy, yz);
        case 2:
            return CARTESIAN_COORDINATE(zx, zy, zz);
        default:
            throw std::out_of_range("CARTESIAN_MATRIX[] out of range.");
    }
}

CARTESIAN_COORDINATE CARTESIAN_MATRIX::row(unsigned int i) const{
    switch(i){
        case 0:
            return CARTESIAN_COORDINATE(xx, xy, xz);
        case 1:
            return CARTESIAN_COORDINATE(yx, yy, yz);
        case 2:
            return CARTESIAN_COORDINATE(zx, zy, zz);
        default:
            throw std::out_of_range("row() out of range.");
    }
}

CARTESIAN_COORDINATE CARTESIAN_MATRIX::col(unsigned int i) const{
    switch(i){
        case 0:
            return CARTESIAN_COORDINATE(xx, yx, zx);
        case 1:
            return CARTESIAN_COORDINATE(xy, yy, zy);
        case 2:
            return CARTESIAN_COORDINATE(xz, yz, zz);
        default:
            throw std::out_of_range("col() out of range.");
    }
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

boost::array<boost::array<double, 3>, 3> CARTESIAN_MATRIX::asArray() const{
    boost::array<boost::array<double, 3>, 3> v;
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

boost::array<double, 9> CARTESIAN_MATRIX::asFlatArray() const{
    boost::array<double, 9> v;
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

vector<vector<double>> CARTESIAN_MATRIX::asVector() const{
    vector<vector<double>> v(3);
    v[0] = (*this)[0].asVector();
    v[1] = (*this)[1].asVector();
    v[2] = (*this)[2].asVector();
    return v;
}

vector<double> CARTESIAN_MATRIX::asFlatVector() const{
    vector<double> v(9);
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ostream& operator<<(ostream& os, const CARTESIAN_MATRIX& A){
    os << "[";
    os << A[0] << ",\n ";
    os << A[1] << ",\n ";
    os << A[2];
    os << "]";
    return os;
}
