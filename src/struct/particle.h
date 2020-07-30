#ifndef PARTICLE_H
#define PARTICLE_H
#include "../global.h"
#include "cartesian_c.h"
#include "../interfaces/box_geometry.h"

class PARTICLE{
public:
    REAL_C position;
    REAL_C boxPosition;

    int index;
    double diameter;
    int species;

    PARTICLE();
    PARTICLE(const REAL_C& positionIN);
    PARTICLE(const PARTICLE& other);

    REAL_C getPosition() const;

    double distanceTo(PARTICLE& other);
    double distanceTo(REAL_C& positionIN);

    double boxDistanceTo(PARTICLE& other, BOX_GEOMETRY& boxGeom);
    double boxDistanceTo(REAL_C& positionIN, BOX_GEOMETRY& boxGeom);

    void setBoxPosition(BOX_GEOMETRY& boxGeom);

    double getVolume();

};

#endif // PARTICLE_H
