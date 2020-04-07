#ifndef SHEARED_SLITPORE_PARAMETERS_H
#define SHEARED_SLITPORE_PARAMETERS_H

#include "../global.h"
#include "../tools/argparse.h"
#include "../defaults.h"

struct SHEARED_SLITPORE_PARAMETERS{
public:
    double shearRate = SHEAR_RATE;

    double dWall = D_WALL;
    double density = DENSITY;
    int numberOfParticles = NUMBER_OF_PARTICLES;

    int charge = CHARGE;
    double diameter = DIAMETER;
    double ssInteractionStrength = SS_INTERACTION_STRENGTH;
    double wallInteractionStrength = WALL_INTERACTION_STRENGTH;

    double dt = DELTA_T;
    double temperature = TEMPERATURE;
//    string sysIdentifierString;

    SHEARED_SLITPORE_PARAMETERS();
    SHEARED_SLITPORE_PARAMETERS(const ARGUMENTS& args);

    void print();

//    void setAsBiLayerWithShearRate(double shearRateIn);
//    void setAsTriLayerWithShearRate(double shearRateIn);

    void readFromArguments(const ARGUMENTS& args);
};

#endif // SHEARED_SLITPORE_PARAMETERS_H
