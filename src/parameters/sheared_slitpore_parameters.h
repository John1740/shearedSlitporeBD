#ifndef SHEARED_SLITPORE_PARAMETERS_H
#define SHEARED_SLITPORE_PARAMETERS_H

#include "../global.h"

struct SHEARED_SLITPORE_PARAMETERS
{
public:
    SHEARED_SLITPORE_PARAMETERS();

    void print();

    double shearRate;

    double dWall;
    double density;
    int numberOfParticles;

    int charge;
    double diameter;
    double ssInteractionStrength;
    double wallInteractionStrength;

    string sysIdentifierString;
    
    void setAsBiLayerWithShearRate ( double shearRateIn );
    void setAsTriLayerWithShearRate ( double shearRateIn );
};

#endif // SHEARED_SLITPORE_PARAMETERS_H
