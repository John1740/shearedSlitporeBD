//
// Created by mhuelsberg on 02.06.21.
//

#include "oscillatory_shear.h"
#include <boost/format.hpp>

namespace bo = boost;

OSCILLATORY_SHEAR::OSCILLATORY_SHEAR(){
}

OSCILLATORY_SHEAR::OSCILLATORY_SHEAR(double shearRate){
    this->shearRateOffset = shearRate;
}

OSCILLATORY_SHEAR::OSCILLATORY_SHEAR(double shearRateOffset, double shearRateAmplitude, double oscillationPeriod,
                                     double phaseOffset){
    this->shearRateOffset = shearRateOffset;
    this->shearRateAmplitude = shearRateAmplitude;
    this->oscillationPeriod = oscillationPeriod;
    this->phaseOffset = phaseOffset;
}

double OSCILLATORY_SHEAR::calculateShearStrain(double t) const{
    double shearStrain = shearRateOffset * t +
                         shearRateAmplitude * oscillationPeriod / (2 * M_PI) *
                         cos(2 * M_PI * t / oscillationPeriod + M_PI * phaseOffset);
    return shearStrain;
}

double OSCILLATORY_SHEAR::calculateShearRate(double t) const{
    double shearRate = shearRateOffset +
                       shearRateAmplitude * cos(2 * M_PI * t / oscillationPeriod + M_PI * phaseOffset);
    return shearRate;
}

void OSCILLATORY_SHEAR::print(ostream& os) const{
    const char* fmt = "% .8e\t";
    os << "shearRateOffset: " << bo::format(fmt) % shearRateOffset << endl;
    os << "shearRateAmplitude: " << bo::format(fmt) % shearRateAmplitude << endl;
    os << "oscillationPeriod: " << bo::format(fmt) % oscillationPeriod << endl;
    os << "phaseOffset: " << bo::format(fmt) % phaseOffset;
}

//ostream& operator<<(ostream& os, const OSCILLATORY_SHEAR& obj){
//    const char* fmt = "% .8e\t";
//    os << "shearRateOffset: " << bo::format(fmt) % obj.shearRateOffset << endl;
//    os << "shearRateAmplitude: " << bo::format(fmt) % obj.shearRateAmplitude << endl;
//    os << "oscillationPeriod: " << bo::format(fmt) % obj.oscillationPeriod << endl;
//    os << "phaseOffset: " << bo::format(fmt) % obj.phaseOffset;
//    return os;
//}