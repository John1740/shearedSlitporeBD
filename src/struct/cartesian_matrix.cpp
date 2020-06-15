#include "cartesian_matrix.h"

double CARTESIAN_MATRIX::getDeterminant(){
    return xx * yy * zz + xy * yz * zx + xz * yx * zy - xz * yy * zx - xy * yx * zz - xx * yz * zy;
}

CARTESIAN_MATRIX &CARTESIAN_MATRIX::operator+= (const CARTESIAN_MATRIX &cCoordIN){
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
