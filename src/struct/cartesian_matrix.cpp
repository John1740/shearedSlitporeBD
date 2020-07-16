#include "cartesian_matrix.h"

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
            cout << "CARTESIAN_MATRIX[" << i << "] out of range." << endl;
            exit(1);
    }
    return CARTESIAN_COORDINATE(x, y, z);
}

double CARTESIAN_MATRIX::getDeterminant(){
    return xx * yy * zz + xy * yz * zx + xz * yx * zy - xz * yy * zx - xy * yx * zz - xx * yz * zy;
}

CARTESIAN_MATRIX& CARTESIAN_MATRIX::operator=(const CARTESIAN_MATRIX& cCoordIN){
    this->xx = cCoordIN.xx;
    this->xy = cCoordIN.xy;
    this->xz = cCoordIN.xz;
    this->yx = cCoordIN.yx;
    this->yy = cCoordIN.yy;
    this->yz = cCoordIN.yz;
    this->zx = cCoordIN.zx;
    this->zy = cCoordIN.zy;
    this->zz = cCoordIN.zz;
    return *this;
}

CARTESIAN_MATRIX& CARTESIAN_MATRIX::operator=(const double& doubleIN){
    this->xx = doubleIN;
    this->xy = doubleIN;
    this->xz = doubleIN;
    this->yx = doubleIN;
    this->yy = doubleIN;
    this->yz = doubleIN;
    this->zx = doubleIN;
    this->zy = doubleIN;
    this->zz = doubleIN;
    return *this;
}

CARTESIAN_MATRIX &CARTESIAN_MATRIX::operator+= (const CARTESIAN_MATRIX& cCoordIN){
    this->xx += cCoordIN.xx;
    this->xy += cCoordIN.xy;
    this->xz += cCoordIN.xz;
    this->yx += cCoordIN.yx;
    this->yy += cCoordIN.yy;
    this->yz += cCoordIN.yz;
    this->zx += cCoordIN.zx;
    this->zy += cCoordIN.zy;
    this->zz += cCoordIN.zz;
    return *this;
}

CARTESIAN_MATRIX& CARTESIAN_MATRIX::operator+=(const double& doubleIN){
    this->xx += doubleIN;
    this->xy += doubleIN;
    this->xz += doubleIN;
    this->yx += doubleIN;
    this->yy += doubleIN;
    this->yz += doubleIN;
    this->zx += doubleIN;
    this->zy += doubleIN;
    this->zz += doubleIN;
    return *this;
}

CARTESIAN_MATRIX &CARTESIAN_MATRIX::operator-= (const CARTESIAN_MATRIX &cCoordIN){
    this->xx -= cCoordIN.xx;
    this->xy -= cCoordIN.xy;
    this->xz -= cCoordIN.xz;
    this->yx -= cCoordIN.yx;
    this->yy -= cCoordIN.yy;
    this->yz -= cCoordIN.yz;
    this->zx -= cCoordIN.zx;
    this->zy -= cCoordIN.zy;
    this->zz -= cCoordIN.zz;
    return *this;
}

CARTESIAN_MATRIX &CARTESIAN_MATRIX::operator*= (const CARTESIAN_MATRIX &cCoordIN){
    this->xx *= cCoordIN.xx;
    this->xy *= cCoordIN.xy;
    this->xz *= cCoordIN.xz;
    this->yx *= cCoordIN.yx;
    this->yy *= cCoordIN.yy;
    this->yz *= cCoordIN.yz;
    this->zx *= cCoordIN.zx;
    this->zy *= cCoordIN.zy;
    this->zz *= cCoordIN.zz;
    return *this;
}

CARTESIAN_MATRIX &CARTESIAN_MATRIX::operator/= (const CARTESIAN_MATRIX &cCoordIN){
    this->xx /= cCoordIN.xx;
    this->xy /= cCoordIN.xy;
    this->xz /= cCoordIN.xz;
    this->yx /= cCoordIN.yx;
    this->yy /= cCoordIN.yy;
    this->yz /= cCoordIN.yz;
    this->zx /= cCoordIN.zx;
    this->zy /= cCoordIN.zy;
    this->zz /= cCoordIN.zz;
    return *this;
}
