#include "slit_pore_box.h"

SLIT_PORE_BOX::SLIT_PORE_BOX()
{
   setLengthAndDWall( 1., 1. );
   setVolume();
}

SLIT_PORE_BOX::SLIT_PORE_BOX ( CARTESIAN_COORDINATE dimensionsIn )
{
    setDimensions(dimensionsIn);
}

void SLIT_PORE_BOX::setDimensions ( CARTESIAN_COORDINATE dimensionsIn )
{
    dimensions = dimensionsIn;
    setVolume();
}

SLIT_PORE_BOX::SLIT_PORE_BOX( double lengthIN, double dWallIN )
{
   setLengthAndDWall( lengthIN, dWallIN );
   setVolume();
}

void SLIT_PORE_BOX::setDwall( double dWallIn )
{
    dimensions.z = dWallIn;
}


void SLIT_PORE_BOX::setLengthAndDWall( double lengthIN, double dWallIN )
{
   dimensions.x = lengthIN;
   dimensions.y = dimensions.x;
   setDwall( dWallIN );
   setVolume();
}

void SLIT_PORE_BOX::setVolumeAndDWall( double volumeIN, double dWallIN )
{
   volume = volumeIN;
   setDwall( dWallIN );
   dimensions.x = sqrt( volume / dimensions.z ); //A = V/Z, X=Y=sqrt(A)
   dimensions.y = dimensions.x;
}



double SLIT_PORE_BOX::getVolume()
{
   return volume;
}

void SLIT_PORE_BOX::setVolume()
{
    volume = dimensions.x * dimensions.y * dimensions.z;
}

CARTESIAN_COORDINATE SLIT_PORE_BOX::getDimensions()
{
    return dimensions;
}


CARTESIAN_COORDINATE SLIT_PORE_BOX::convertToBoxPosition( CARTESIAN_COORDINATE &positionIN )
{
   CARTESIAN_COORDINATE boxPosition(
      positionIN.x - round( positionIN.x / dimensions.x ) * dimensions.x,
      positionIN.y - round( positionIN.y / dimensions.y ) * dimensions.y,
      positionIN.z );

   return boxPosition;
}


