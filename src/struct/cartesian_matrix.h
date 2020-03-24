#ifndef CARTESIAN_MATRIX_H
#define CARTESIAN_MATRIX_H

#include "cartesian_coordinate.h"

struct CARTESIAN_MATRIX
{
   double xx,xy,xz;
   double yx,yy,yz;
   double zx,zy,zz;

   CARTESIAN_MATRIX() : xx ( 0 ), xy ( 0 ), xz ( 0 ), yx ( 0 ), yy ( 0 ), yz ( 0 ), zx ( 0 ), zy ( 0 ), zz ( 0 ) {}
   CARTESIAN_MATRIX ( double doubleIn ) : xx ( doubleIn ), xy ( doubleIn ), xz ( doubleIn ), yx ( doubleIn ), yy ( doubleIn ), yz ( doubleIn ), zx ( doubleIn ), zy ( doubleIn ), zz ( doubleIn ) {}
   CARTESIAN_MATRIX ( CARTESIAN_COORDINATE posIn ) : xx ( posIn.x ), xy ( posIn.y ), xz ( posIn.z ), yx ( posIn.x ), yy ( posIn.y ), yz ( posIn.z ), zx ( posIn.x ), zy ( posIn.y ), zz ( posIn.z ) {}
   CARTESIAN_MATRIX ( CARTESIAN_COORDINATE row1, CARTESIAN_COORDINATE row2, CARTESIAN_COORDINATE row3 ) : xx ( row1.x ), xy ( row1.y ), xz ( row1.z ), yx ( row2.x ), yy ( row2.y ), yz ( row2.z ), zx ( row3.x ), zy ( row3.y ), zz ( row3.z ) {}
   CARTESIAN_MATRIX ( CARTESIAN_COORDINATE vec1, CARTESIAN_COORDINATE vec2 ) : xx ( vec1.x*vec2.x ), xy ( vec1.x*vec2.y ), xz ( vec1.x*vec2.z ), yx ( vec1.y*vec2.x ), yy ( vec1.y*vec2.y ), yz ( vec1.y*vec2.z ), zx ( vec1.z*vec2.x ), zy ( vec1.z*vec2.y ), zz ( vec1.z*vec2.z ) {}

   double getDeterminante();

   CARTESIAN_MATRIX& operator+= ( CARTESIAN_MATRIX const& cCoordIN );
   CARTESIAN_MATRIX& operator+= ( double const& doubleIN )
   {
      return *this += CARTESIAN_MATRIX ( doubleIN );
   };

   CARTESIAN_MATRIX& operator-= ( CARTESIAN_MATRIX const& cCoordIN );
   CARTESIAN_MATRIX& operator-= ( double const& doubleIN )
   {
      return *this -= CARTESIAN_MATRIX ( doubleIN );
   };

   CARTESIAN_MATRIX& operator*= ( CARTESIAN_MATRIX const& cCoordIN );
   CARTESIAN_MATRIX& operator*= ( double const& doubleIN )
   {
      return *this *= CARTESIAN_MATRIX ( doubleIN );
   };

   CARTESIAN_MATRIX& operator/= ( CARTESIAN_MATRIX const& cCoordIN );
   CARTESIAN_MATRIX& operator/= ( double const& doubleIN )
   {
      return *this /= CARTESIAN_MATRIX ( doubleIN );
   };


   friend CARTESIAN_MATRIX operator+ ( CARTESIAN_MATRIX const& lhs, CARTESIAN_MATRIX const& rhs )
   {
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
   friend CARTESIAN_MATRIX operator+ ( double const& lhs, CARTESIAN_MATRIX const& rhs )
   {
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
   friend CARTESIAN_MATRIX operator+ ( CARTESIAN_MATRIX const& lhs, double const& rhs )
   {
      CARTESIAN_MATRIX result;
      result = rhs + lhs;
      return result;
   };


   friend CARTESIAN_MATRIX operator- ( CARTESIAN_MATRIX const& lhs, CARTESIAN_MATRIX const& rhs )
   {
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
   friend CARTESIAN_MATRIX operator- ( double const& lhs, CARTESIAN_MATRIX const& rhs )
   {
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
   friend CARTESIAN_MATRIX operator- ( CARTESIAN_MATRIX const& lhs, double const& rhs )
   {
      CARTESIAN_MATRIX result;
      result = -1*rhs + lhs;
      return result;
   };


   friend CARTESIAN_MATRIX operator* ( CARTESIAN_MATRIX const& lhs, CARTESIAN_MATRIX const& rhs )
   {
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
   friend CARTESIAN_MATRIX operator* ( double const& lhs, CARTESIAN_MATRIX const& rhs )
   {
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
   friend CARTESIAN_MATRIX operator* ( CARTESIAN_MATRIX const& lhs, double const& rhs )
   {
      CARTESIAN_MATRIX result;
      result = rhs * lhs;
      return result;
   };

   friend CARTESIAN_MATRIX operator/ ( CARTESIAN_MATRIX const& lhs, CARTESIAN_MATRIX const& rhs )
   {
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
   friend CARTESIAN_MATRIX operator/ ( double const& lhs, CARTESIAN_MATRIX const& rhs )
   {
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
   friend CARTESIAN_MATRIX operator/ ( CARTESIAN_MATRIX const& lhs, double const& rhs )
   {
      CARTESIAN_MATRIX result;
      result = lhs * ( 1./rhs );
      return result;
   };

   friend ostream& operator<< ( ostream& lhs, CARTESIAN_MATRIX const& rhs )
   {
      return lhs << rhs.xx << "\t" << rhs.xy << "\t" << rhs.xz << "\n" << rhs.yx << "\t" << rhs.yy << "\t" << rhs.yz << "\n" << rhs.zx << "\t" << rhs.zy << "\t" << rhs.zz;
   }

   friend bool operator== ( const CARTESIAN_MATRIX& lhs, const CARTESIAN_MATRIX& rhs )
   {
      if ( lhs.xx==rhs.xx && lhs.xy==rhs.xy && lhs.xz==rhs.xz && lhs.yx==rhs.yx && lhs.yy==rhs.yy && lhs.yz==rhs.yz && lhs.zx==rhs.zx && lhs.zy==rhs.zy && lhs.zz==rhs.zz )
         {
            return true;
         }
      else
         {
            return false;
         }
   };

   friend bool operator!= ( const CARTESIAN_MATRIX& lhs, const CARTESIAN_MATRIX& rhs )
   {
      return ! ( lhs == rhs );
   };


};

#endif // CARTESIAN_MATRIX_H
