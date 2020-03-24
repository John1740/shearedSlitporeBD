#ifndef PARTICLE_H
#define PARTICLE_H
#include "../global.h"
#include "cartesian_coordinate.h"
#include "../interfaces/box_geometry.h"


class PARTICLE
{
public:
   CARTESIAN_COORDINATE position;
   CARTESIAN_COORDINATE boxPosition;

   double diameter;
   int species;

   PARTICLE();
   PARTICLE ( const CARTESIAN_COORDINATE& positionIN );
   PARTICLE ( const PARTICLE& other );

   double distanceTo ( PARTICLE& other );
   double distanceTo ( CARTESIAN_COORDINATE& positionIN );

   double boxDistanceTo ( PARTICLE& other );
   double boxDistanceTo ( CARTESIAN_COORDINATE& positionIN );

   void setBoxPosition ( BOX_GEOMETRY& boxGeom );

   double getVolume();

};

#endif // PARTICLE_H
