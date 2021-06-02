//
// Created by mhuelsberg on 02.06.21.
//

#ifndef SHEAREDSLITPOREBD_SHEAR_PROTOCOL_H
#define SHEAREDSLITPOREBD_SHEAR_PROTOCOL_H

class SHEAR_PROTOCOL{
public:
    virtual double calculateShearStrain(double t) = 0;
    virtual double calculateShearRate(double t) = 0;
};

#endif //SHEAREDSLITPOREBD_SHEAR_PROTOCOL_H
