//
// Created by mhuels on 5/5/20.
//

#ifndef SHEAREDSLITPOREBD_PERIODIC_COORDINATE_H
#define SHEAREDSLITPOREBD_PERIODIC_COORDINATE_H

#include "cartesian_c.h"
#include "../interfaces/box_geometry.h"
#include <vector>

class PERIODIC_COORDINATE: public REAL_C{
private:
    //CARTESIAN_COORDINATE needs to only have position (private), not boxPosition
    //boxPosition will be overriden here onto position instead by overriding getPosition() and setPosition()
    vector<bool> periodicBoundaryConditions;   //periodic boundary condition
    const BOX_GEOMETRY* simBox;   //store the box geometry in a pointer (content of pointer should be const)

public:
    PERIODIC_COORDINATE();

    //getter
    vector<double> getPosition() const;    //0=x, 1=y, 2=z
    BOX_GEOMETRY* getSimBox() const;
    vector<bool> getPeriodicBoundaryConditions() const;

    //setter
    void setPosition(const REAL_C& other);
    void setPosition(const PERIODIC_COORDINATE& other);
    void setPosition(double x, double y, double z);
    void setSimBox(BOX_GEOMETRY* simBoxIn);
    void setPeriodicBoundaryConditions(bool x, bool y, bool z);
};

#endif //SHEAREDSLITPOREBD_PERIODIC_COORDINATE_H
