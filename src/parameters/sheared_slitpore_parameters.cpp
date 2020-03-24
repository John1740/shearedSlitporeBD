#include "sheared_slitpore_parameters.h"


SHEARED_SLITPORE_PARAMETERS::SHEARED_SLITPORE_PARAMETERS()
{
    shearRate = 0.;

    dWall = 3.2;
    density = 0.85;
    numberOfParticles = 1587;

    charge = 35;
    diameter = 1.;
    ssInteractionStrength = 1.;
    wallInteractionStrength = 1.;
}

void SHEARED_SLITPORE_PARAMETERS::print()
{
    cout << "sysId: " + sysIdentifierString << endl;
    cout << "dWall = " << dWall << "\t\t" << "density = " << density << "\t\t" << "numberOfParticles = " << numberOfParticles << endl;
    cout << "charge = " << charge << "\t\t" << "diameter = " << diameter << endl;
    cout << "ssIS = " << ssInteractionStrength << "\t\t" << "wallIS = " << wallInteractionStrength << endl;
    cout << endl;

}

void SHEARED_SLITPORE_PARAMETERS::setAsBiLayerWithShearRate ( double shearRateIn )
{
    numberOfParticles = 1058;

    shearRate = shearRateIn;
    dWall = 2.2;
    density = 0.85;

    charge = 35;

    diameter = 1.;

    ssInteractionStrength = 1.;
    wallInteractionStrength = 1.;

    sysIdentifierString = "2layer";
}

void SHEARED_SLITPORE_PARAMETERS::setAsTriLayerWithShearRate ( double shearRateIn )
{
    numberOfParticles = 1587;

    shearRate = shearRateIn;
    dWall = 3.2;
    density = 0.85;

    charge = 35;

    diameter = 1.;

    ssInteractionStrength = 1.;
    wallInteractionStrength = 1.;

    sysIdentifierString = "3layer";    
}

