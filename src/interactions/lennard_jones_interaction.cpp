#include "lennard_jones_interaction.h"


LENNARD_JONES_INTERACTION::LENNARD_JONES_INTERACTION()
{
   interactionStrength = 1.;
   diameter = 1.;
}

LENNARD_JONES_INTERACTION::LENNARD_JONES_INTERACTION( double interactionStrengthIN ) : interactionStrength( interactionStrengthIN )
{
   diameter = 1.;
}

double LENNARD_JONES_INTERACTION::energyOnParticleFromParticle( PARTICLE &particle1, PARTICLE &particle2, BOX_GEOMETRY& simBox )
{
   setParametersForParticleFromParticle( particle1, particle2 );

   return energyOnParticles( distance );
}

double LENNARD_JONES_INTERACTION::energyOnParticles( double distance )
{
   return 4.*interactionStrength * ( pow( diameter / distance, 12 ) - pow( diameter / distance, 6 ) );
}

CARTESIAN_COORDINATE LENNARD_JONES_INTERACTION::forceOnParticleFromParticle( PARTICLE &particle1, PARTICLE &particle2, BOX_GEOMETRY& simBox )
{
   setParametersForParticleFromParticle( particle1, particle2 );

    CARTESIAN_COORDINATE result;
   result = positionDifference * forceOnParticlePerDirection( distance ) / distance;
   return result;
}

double LENNARD_JONES_INTERACTION::forceOnParticlePerDirection( double distance )
{
   return 48.*interactionStrength * ( pow( diameter / distance, 13 ) - 0.5 * pow( diameter / distance, 7 ) );
}

void LENNARD_JONES_INTERACTION::setParametersForParticleFromParticle( PARTICLE &particle1, PARTICLE &particle2 )
{
   positionDifference = particle1.boxPosition - particle2.boxPosition;
   distance = positionDifference.getAbs();
   diameter = 0.5 * ( particle1.diameter + particle2.diameter );
}


