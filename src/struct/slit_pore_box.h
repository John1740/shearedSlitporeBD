#ifndef SLIT_PORE_BOX_H
#define SLIT_PORE_BOX_H

#include "../interfaces/box_geometry.h"
#include "../defaults.h"

class SLIT_PORE_BOX: public BOX_GEOMETRY{
private:
    CARTESIAN_COORDINATE dimensions;
    CARTESIAN_COORDINATE origin;
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
    void setOrigin(CARTESIAN_COORDINATE origin);
    
    void setLengthAndDWall(double lengthIN, double dWallIN);    //necessary?
    void setVolumeAndDWall(double volumeIN, double dWallIN);

    //getter functions
    CARTESIAN_COORDINATE getDimensions() const;
    CARTESIAN_COORDINATE getOrigin() const;
    double getVolume() const;

    CARTESIAN_COORDINATE convertToBoxPosition(CARTESIAN_COORDINATE& positionIN);
    
    //file handling
    friend ostream& operator<<(ostream& os, const SLIT_PORE_BOX& simBox);
};

#endif // SLIT_PORE_BOX_H
