#ifndef SLIT_PORE_BOX_H
#define SLIT_PORE_BOX_H

#include "../interfaces/box_geometry.h"

struct SLIT_PORE_BOX: public BOX_GEOMETRY {

    SLIT_PORE_BOX();
    SLIT_PORE_BOX( CARTESIAN_COORDINATE dimensionsIn );
    SLIT_PORE_BOX ( double lengthIN, double dWallIN );
    
    void setDimensions( CARTESIAN_COORDINATE dimensionsIn );

    void setDwall ( double dWallIn );
    void setLengthAndDWall ( double lengthIN, double dWallIN );
    void setVolumeAndDWall ( double volumeIN, double dWallIN );

    CARTESIAN_COORDINATE convertToBoxPosition ( CARTESIAN_COORDINATE& positionIN );

    double getVolume();
    CARTESIAN_COORDINATE getDimensions();
    
private:
    CARTESIAN_COORDINATE dimensions;
    double volume;
    void setVolume();

};

#endif // SLIT_PORE_BOX_H
