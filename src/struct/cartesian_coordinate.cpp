#include "cartesian_coordinate.h"

double CARTESIAN_COORDINATE::getAbs()
{
   return sqrt( x * x + y * y + z * z );
}



CARTESIAN_COORDINATE &CARTESIAN_COORDINATE::operator+= ( CARTESIAN_COORDINATE const &cCoordIN )
{
   this->x += cCoordIN.x;
   this->y += cCoordIN.y;
   this->z += cCoordIN.z;
   return *this;
}

CARTESIAN_COORDINATE &CARTESIAN_COORDINATE::operator-= ( CARTESIAN_COORDINATE const &cCoordIN )
{
   this->x -= cCoordIN.x;
   this->y -= cCoordIN.y;
   this->z -= cCoordIN.z;
   return *this;
}

CARTESIAN_COORDINATE &CARTESIAN_COORDINATE::operator*= ( CARTESIAN_COORDINATE const &cCoordIN )
{
   this->x *= cCoordIN.x;
   this->y *= cCoordIN.y;
   this->z *= cCoordIN.z;
   return *this;
}

CARTESIAN_COORDINATE &CARTESIAN_COORDINATE::operator/= ( CARTESIAN_COORDINATE const &cCoordIN )
{
   this->x /= cCoordIN.x;
   this->y /= cCoordIN.y;
   this->z /= cCoordIN.z;
   return *this;
}

