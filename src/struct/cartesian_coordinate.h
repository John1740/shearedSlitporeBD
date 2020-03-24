#ifndef CARTESIAN_COORDINATE_H
#define CARTESIAN_COORDINATE_H

#include <iostream>
#include <math.h>
using namespace std;

struct CARTESIAN_COORDINATE
{

   double x,y,z;

   CARTESIAN_COORDINATE() : x ( 0. ), y ( 0. ), z ( 0. ) {}
   CARTESIAN_COORDINATE ( double doubleIN ) : x ( doubleIN ), y ( doubleIN ), z ( doubleIN ) {}
   CARTESIAN_COORDINATE ( double xIN, double yIN, double zIN ) : x ( xIN ),y ( yIN ),z ( zIN ) {}
   CARTESIAN_COORDINATE ( const CARTESIAN_COORDINATE& cCoordIN ) : x ( cCoordIN.x ),y ( cCoordIN.y ),z ( cCoordIN.z ) {}

   double getAbs();

   CARTESIAN_COORDINATE& operator+= ( CARTESIAN_COORDINATE const& cCoordIN );
   CARTESIAN_COORDINATE& operator+= ( double const& doubleIN )
   {
      return *this += CARTESIAN_COORDINATE ( doubleIN );
   };

   CARTESIAN_COORDINATE& operator-= ( CARTESIAN_COORDINATE const& cCoordIN );
   CARTESIAN_COORDINATE& operator-= ( double const& doubleIN )
   {
      return *this -= CARTESIAN_COORDINATE ( doubleIN );
   };

   CARTESIAN_COORDINATE& operator*= ( CARTESIAN_COORDINATE const& cCoordIN );
   CARTESIAN_COORDINATE& operator*= ( double const& doubleIN )
   {
      return *this *= CARTESIAN_COORDINATE ( doubleIN );
   };

   CARTESIAN_COORDINATE& operator/= ( CARTESIAN_COORDINATE const& cCoordIN );
   CARTESIAN_COORDINATE& operator/= ( double const& doubleIN )
   {
      return *this /= CARTESIAN_COORDINATE ( doubleIN );
   };


   friend CARTESIAN_COORDINATE operator+ ( CARTESIAN_COORDINATE const& lhs, CARTESIAN_COORDINATE const& rhs )
   {
      CARTESIAN_COORDINATE result ( lhs.x+rhs.x,lhs.y+rhs.y, lhs.z+rhs.z );
      return result;
   };
   friend CARTESIAN_COORDINATE operator+ ( double const& lhs, CARTESIAN_COORDINATE const& rhs )
   {
      CARTESIAN_COORDINATE result ( lhs+rhs.x,lhs+rhs.y, lhs+rhs.z );
      return result;
   };
   friend CARTESIAN_COORDINATE operator+ ( CARTESIAN_COORDINATE const& lhs, double const& rhs )
   {
      CARTESIAN_COORDINATE result ( lhs.x+rhs,lhs.y+rhs, lhs.z+rhs );
      return result;
   };


   friend CARTESIAN_COORDINATE operator- ( CARTESIAN_COORDINATE const& lhs, CARTESIAN_COORDINATE const& rhs )
   {
      CARTESIAN_COORDINATE result ( lhs.x-rhs.x,lhs.y-rhs.y, lhs.z-rhs.z );
      return result;
   };
   friend CARTESIAN_COORDINATE operator- ( double const& lhs, CARTESIAN_COORDINATE const& rhs )
   {
      CARTESIAN_COORDINATE result ( lhs-rhs.x,lhs-rhs.y, lhs-rhs.z );
      return result;
   };
   friend CARTESIAN_COORDINATE operator- ( CARTESIAN_COORDINATE const& lhs, double const& rhs )
   {
      CARTESIAN_COORDINATE result ( lhs.x-rhs,lhs.y-rhs, lhs.z-rhs );
      return result;
   };

   friend CARTESIAN_COORDINATE operator* ( CARTESIAN_COORDINATE const& lhs, CARTESIAN_COORDINATE const& rhs )
   {
      CARTESIAN_COORDINATE result ( lhs.x*rhs.x,lhs.y*rhs.y, lhs.z*rhs.z );
      return result;
   };
   friend CARTESIAN_COORDINATE operator* ( double const& lhs, CARTESIAN_COORDINATE const& rhs )
   {
      CARTESIAN_COORDINATE result ( lhs*rhs.x,lhs*rhs.y, lhs*rhs.z );
      return result;
   };
   friend CARTESIAN_COORDINATE operator* ( CARTESIAN_COORDINATE const& lhs, double const& rhs )
   {
      CARTESIAN_COORDINATE result ( lhs.x*rhs,lhs.y*rhs, lhs.z*rhs );
      return result;
   };

   friend CARTESIAN_COORDINATE operator/ ( CARTESIAN_COORDINATE const& lhs, CARTESIAN_COORDINATE const& rhs )
   {
      CARTESIAN_COORDINATE result ( lhs.x/rhs.x,lhs.y/rhs.y, lhs.z/rhs.z );
      return result;
   };
   friend CARTESIAN_COORDINATE operator/ ( double const& lhs, CARTESIAN_COORDINATE const& rhs )
   {
      CARTESIAN_COORDINATE result ( lhs/rhs.x,lhs/rhs.y, lhs/rhs.z );
      return result;
   };
   friend CARTESIAN_COORDINATE operator/ ( CARTESIAN_COORDINATE const& lhs, double const& rhs )
   {
      CARTESIAN_COORDINATE result ( lhs.x/rhs,lhs.y/rhs, lhs.z/rhs );
      return result;
   };

   friend ostream& operator<< ( ostream& lhs, CARTESIAN_COORDINATE const& rhs )
   {
      return lhs << rhs.x << "\t" << rhs.y << "\t" << rhs.z;
   }

   friend bool operator== ( const CARTESIAN_COORDINATE& lhs, const CARTESIAN_COORDINATE& rhs )
   {
      if ( lhs.x==rhs.x && lhs.y==rhs.y && lhs.z==rhs.z )
         {
            return true;
         }
      else
         {
            return false;
         }
   };

   friend bool operator!= ( const CARTESIAN_COORDINATE& lhs, const CARTESIAN_COORDINATE& rhs )
   {
      return ! ( lhs == rhs );
   };

};

#endif // CARTESIAN_COORDINATE_H
