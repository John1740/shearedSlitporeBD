#include "particle.h"

PARTICLE::PARTICLE()
{
   position = CARTESIAN_COORDINATE ( 0. );
   boxPosition = CARTESIAN_COORDINATE ( 0. );
   diameter = 1.;
}

PARTICLE::PARTICLE( const CARTESIAN_COORDINATE &positionIN )
{
   position = positionIN;
   boxPosition = CARTESIAN_COORDINATE ( 0. );
}

PARTICLE::PARTICLE( const PARTICLE &other )
{
   position = other.position;
   boxPosition = other.boxPosition;
}

double PARTICLE::distanceTo( PARTICLE &other )
{
    CARTESIAN_COORDINATE difference;
   difference = position - other.position;
   return difference.getAbs();
}

double PARTICLE::distanceTo( CARTESIAN_COORDINATE &positionIN )
{
    CARTESIAN_COORDINATE difference;
   difference = position - positionIN;
   return difference.getAbs();
}

double PARTICLE::boxDistanceTo( PARTICLE &other )
{
    CARTESIAN_COORDINATE difference;
   difference = boxPosition - other.boxPosition;
   return difference.getAbs();
}

double PARTICLE::boxDistanceTo( CARTESIAN_COORDINATE &positionIN )
{
    CARTESIAN_COORDINATE difference;
   difference = boxPosition - positionIN;
   return difference.getAbs();
}


void PARTICLE::setBoxPosition( BOX_GEOMETRY &boxGeom )
{
   boxPosition = boxGeom.convertToBoxPosition( position );
}

double PARTICLE::getVolume()
{
   return diameter * diameter * diameter / 6.;
}

