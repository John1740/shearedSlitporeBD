//
// Created by mhuelsberg on 02.06.21.
//

#include "oscillatory_shear.h"

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
