#ifndef BOX_GEOMETRY_H
#define BOX_GEOMETRY_H

#include "../struct/cartesian_coordinate.h"
#include <vector>
using namespace std;

class BOX_GEOMETRY{
public:

    virtual CARTESIAN_COORDINATE convertToBoxPosition(CARTESIAN_COORDINATE& positionIN) = 0;
//    virtual void setVolume() = 0;
    virtual double getVolume() const = 0;
    virtual CARTESIAN_COORDINATE getDimensions() const = 0;

};

#endif // BOX_GEOMETRY_H
