#ifndef BOX_GEOMETRY_H
#define BOX_GEOMETRY_H

#include "../struct/cartesian_c.h"

class BOX_GEOMETRY{
public:

    virtual REAL_C convertToBoxPosition(REAL_C& positionIN) = 0;
//    virtual void setVolume() = 0;
    virtual double getVolume() const = 0;
    virtual REAL_C getDimensions() const = 0;

};

#endif // BOX_GEOMETRY_H
