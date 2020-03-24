#include "cartesian_matrix.h"

double CARTESIAN_MATRIX::getDeterminante()
{
   return xx * yy * zz + xy * yz * zx + xz * yx * zy - xz * yy * zx - xy * yx * zz - xx * yz * zy;
}


// CARTASIAN_MATRIX CARTASIAN_MATRIX::getInverseMatrix()
// {
//     CARTASIAN_MATRIX invertedMatrix;
//     
//     invertedMatrix.xx =  yy* zz -  yz* zy;
//     invertedMatrix.xy =  xz* zy -  xy* zz;
//     invertedMatrix.xz =  xy* yz -  xz* yy;
//     invertedMatrix.yx =  yz* zx -  yx* zz;
//     invertedMatrix.yy =  xx* zz -  xz* zx;
//     invertedMatrix.yz =  xz* yx -  xx* yz;
//     invertedMatrix.zx =  yx* zy -  yy* zx;
//     invertedMatrix.zy =  xy* zx -  xx* zy;
//     invertedMatrix.zz =  xx* yy -  xy* yx;
//     
//     invertedMatrix /= getDeterminante();
//     
//     return invertedMatrix;
// }

// CARTASIAN_MATRIX CARTASIAN_MATRIX::matrixProduct( CARTASIAN_MATRIX matrix )
// {
//     CARTASIAN_MATRIX result;
//     
//     result.xx = this->xx * matrix.xx + this->xy * matrix.yx + this->xz * matrix.zx;
//     
//     return result;
// }

CARTESIAN_MATRIX &CARTESIAN_MATRIX::operator+= ( const CARTESIAN_MATRIX &cCoordIN )
{
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

CARTESIAN_MATRIX &CARTESIAN_MATRIX::operator-= ( const CARTESIAN_MATRIX &cCoordIN )
{
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

CARTESIAN_MATRIX &CARTESIAN_MATRIX::operator*= ( const CARTESIAN_MATRIX &cCoordIN )
{
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

CARTESIAN_MATRIX &CARTESIAN_MATRIX::operator/= ( const CARTESIAN_MATRIX &cCoordIN )
{
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
