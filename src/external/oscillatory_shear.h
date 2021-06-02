//
// Created by mhuelsberg on 02.06.21.
//
#ifndef SHEAREDSLITPOREBD_OSCILLATORY_SHEAR_H
#define SHEAREDSLITPOREBD_OSCILLATORY_SHEAR_H

#include "../interfaces/shear_protocol.h"
#include "../defaults.h"
#include <cmath>

class OSCILLATORY_SHEAR: public SHEAR_PROTOCOL{
public:
    double shearRateOffset = SHEAR_RATE;
    double shearRateAmplitude = AMPLITUDE;
    double oscillationPeriod = OSCILLATION_PERIOD;
    double phaseOffset = PHASE_OFFSET;

    OSCILLATORY_SHEAR();
    OSCILLATORY_SHEAR(double shearRate);
    OSCILLATORY_SHEAR(double shearRateOffset, double shearRateAmplitude, double oscillationPeriod, double phaseOffset);

    ////////////////////////////////////////// Calculators ///////////////////////////////////////////
    [[nodiscard]] double calculateShearStrain(double t) const override;
    [[nodiscard]] double calculateShearRate(double t) const override;
};

#endif //SHEAREDSLITPOREBD_OSCILLATORY_SHEAR_H
