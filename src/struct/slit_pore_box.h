#ifndef SLIT_PORE_BOX_H
#define SLIT_PORE_BOX_H

#include "../interfaces/box_geometry.h"
#include "../defaults.h"

class SLIT_PORE_BOX: public BOX_GEOMETRY{
private:
    REAL_C dimensions;
    REAL_C origin;
    double volume;

    void setVolume();

public:
    //constructors
    SLIT_PORE_BOX();
    SLIT_PORE_BOX(REAL_C dimensionsIn);
    SLIT_PORE_BOX(double volume, double dWallIN);
    SLIT_PORE_BOX(double volume, double dWallIN, double Xlength , double Ylength);

    //setter functions
    void setDwall(double dWallIn);
    void setDimensions(REAL_C dimensionsIn);
    void setOrigin(REAL_C origin);

    void setLengthAndDWall(double lengthIN, double dWallIN);    //necessary?
    void setVolumeAndDWall(double volumeIN, double dWallIN);

    //getter functions
    REAL_C getDimensions() const;
    REAL_C getOrigin() const;
    double getVolume() const;

    REAL_C convertToBoxPosition(REAL_C& positionIN);

    //file/stream-handling
    friend ostream& operator<<(ostream& os, const SLIT_PORE_BOX& simBox);
    bool readFromFile(string filename, bool verbose=true);
};

#endif // SLIT_PORE_BOX_H
