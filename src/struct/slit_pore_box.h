#ifndef SLIT_PORE_BOX_H
#define SLIT_PORE_BOX_H

#include "../interfaces/box_geometry.h"
#include "../defaults.h"

struct SLIT_PORE_BOX: public BOX_GEOMETRY{
private:
    CARTESIAN_COORDINATE dimensions;
    double volume;
    void setVolume();

public:
    //constructors
    SLIT_PORE_BOX();
    SLIT_PORE_BOX(CARTESIAN_COORDINATE dimensionsIn);
    SLIT_PORE_BOX(double volume, double dWallIN);

    //setter functions
    void setDwall(double dWallIn);
    void setDimensions(CARTESIAN_COORDINATE dimensionsIn);
    void setLengthAndDWall(double lengthIN, double dWallIN);
    void setVolumeAndDWall(double volumeIN, double dWallIN);

    //getter functions
    double getVolume();
    CARTESIAN_COORDINATE getDimensions();

    CARTESIAN_COORDINATE convertToBoxPosition(CARTESIAN_COORDINATE& positionIN);
};

#endif // SLIT_PORE_BOX_H
