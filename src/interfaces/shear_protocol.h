//
// Created by mhuelsberg on 02.06.21.
//

#ifndef SHEAREDSLITPOREBD_SHEAR_PROTOCOL_H
#define SHEAREDSLITPOREBD_SHEAR_PROTOCOL_H

#include <iostream>
using namespace std;

class SHEAR_PROTOCOL{
public:
    ////////////////////////////////////////// Calculators ///////////////////////////////////////////
    [[nodiscard]] virtual double calculateShearStrain(double t) const{
        return 0.;
    };
    [[nodiscard]] virtual double calculateShearRate(double t) const{
        return 0.;
    };

    //file/stream-handling
    virtual void print(ostream& os) const{
        os << "operator<</print not implemented for the base class SHEAR_PROTOCOL";
    };

    friend ostream& operator<<(ostream& os, const SHEAR_PROTOCOL& obj){
        obj.print(os);
        return os;
    };
};

#endif //SHEAREDSLITPOREBD_SHEAR_PROTOCOL_H
