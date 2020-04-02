#include "slit_pore_box.h"

SLIT_PORE_BOX::SLIT_PORE_BOX()
{
   setLengthAndDWall(1., 1. );
   setVolume();
}

SLIT_PORE_BOX::SLIT_PORE_BOX(CARTESIAN_COORDINATE dimensionsIn )
{
    setDimensions(dimensionsIn);
}

void SLIT_PORE_BOX::setDimensions(CARTESIAN_COORDINATE dimensionsIn )
{
    dimensions = dimensionsIn;
    setVolume();
}

SLIT_PORE_BOX::SLIT_PORE_BOX(double lengthIN, double dWallIN )
{
   setLengthAndDWall(lengthIN, dWallIN );
   setVolume();
}

void SLIT_PORE_BOX::setDwall(double dWallIn )
{
    dimensions.z = dWallIn;
}


void SLIT_PORE_BOX::setLengthAndDWall(double lengthIN, double dWallIN )
{
   dimensions.x = lengthIN;
   dimensions.y = dimensions.x;
   setDwall(dWallIN );
   setVolume();
}

void SLIT_PORE_BOX::setVolumeAndDWall(double volumeIN, double dWallIN )
{
   volume = volumeIN;
   setDwall(dWallIN );
   dimensions.x = sqrt(volume / dimensions.z ); //A = V/Z, X=Y=sqrt(A)
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

//Converts coordinates x and y into the scope [-L/2,+L/2] (periodic boundary conditions),
//where L is the dimension dx or dy respectively.
CARTESIAN_COORDINATE SLIT_PORE_BOX::convertToBoxPosition(CARTESIAN_COORDINATE &positionIN )
{
    CARTESIAN_COORDINATE boxPosition;
    //x  = X*L + r (x=positionIN.x, X to be integer, L=dimension.x, r to be remainder ([0,L])
    //x' = x - round( x / L ) * L  (x'=boxPosition.x)
    //x' = r - round( r / L ) * L  (r/L is element [0,1] and so either rounded to 0 or 1)
    //x' = r   , if r <  L/2       (rounded half away from zero)
    //   = r-L , if r >= L/2
    boxPosition.x = positionIN.x - round(positionIN.x / dimensions.x ) * dimensions.x;
    boxPosition.y = positionIN.y - round(positionIN.y / dimensions.y ) * dimensions.y;
    boxPosition.z = positionIN.z;

    return boxPosition;
}


