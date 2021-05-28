#include "lennard_jones_interaction.h"

LENNARD_JONES_INTERACTION::LENNARD_JONES_INTERACTION(){
    interactionStrength = 1.;
    diameter = 1.;
}

LENNARD_JONES_INTERACTION::LENNARD_JONES_INTERACTION(double interactionStrengthIN){
    interactionStrength = interactionStrengthIN;
    diameter = 1.;
}

double LENNARD_JONES_INTERACTION::energyOnParticles(double distance){
    double energy = 4. * interactionStrength * (pow(diameter / distance, 12) - pow(diameter / distance, 6));
    return energy;
}

double LENNARD_JONES_INTERACTION::forceOnParticlePerDirection(double distance){
    double force = 48. * interactionStrength / diameter * (pow(diameter / distance, 13) - 0.5 * pow(diameter / distance, 7));
    return force;
}

double LENNARD_JONES_INTERACTION::energyOnParticleFromParticle(PARTICLE& particle1, PARTICLE& particle2, BOX_GEOMETRY& simBox){
    setParametersForParticleFromParticle(particle1, particle2, simBox);
    return energyOnParticles(distance);
}

REAL_C LENNARD_JONES_INTERACTION::forceOnParticleFromParticle(PARTICLE& particle1, PARTICLE& particle2, BOX_GEOMETRY& simBox){
    setParametersForParticleFromParticle(particle1, particle2, simBox);
    REAL_C force;
    force = forceOnParticlePerDirection(distance) * positionDifference / distance;
    return force;
}

void LENNARD_JONES_INTERACTION::setParametersForParticleFromParticle(PARTICLE& particle1, PARTICLE& particle2, BOX_GEOMETRY& simBox){
    positionDifference = particle1.boxPosition - particle2.boxPosition;
    positionDifference = simBox.convertToBoxPosition(positionDifference);
    distance = positionDifference.abs();
    diameter = 0.5 * (particle1.diameter + particle2.diameter);
}

