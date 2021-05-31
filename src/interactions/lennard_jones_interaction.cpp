#include "lennard_jones_interaction.h"

LENNARD_JONES_INTERACTION::LENNARD_JONES_INTERACTION(){
    interactionStrength = 1.;
    diameter = 1.;
}

LENNARD_JONES_INTERACTION::LENNARD_JONES_INTERACTION(double interactionStrength){
    this->interactionStrength = interactionStrength;
    diameter = 1.;
}

LENNARD_JONES_INTERACTION::LENNARD_JONES_INTERACTION(double interactionStrength, double diameter){
    this->interactionStrength = interactionStrength;
    this-> diameter = diameter;
}

double LENNARD_JONES_INTERACTION::energy(double r){
    double energy = 4. * interactionStrength * (pow(diameter / r, 12) - pow(diameter / r, 6));
    return energy;
}

double LENNARD_JONES_INTERACTION::forceAbs(double r){
    double forceAbs = 48. * interactionStrength / diameter * (pow(diameter / r, 13) - 0.5 * pow(diameter / r, 7));
    return forceAbs;
}

double LENNARD_JONES_INTERACTION::energyOnParticleFromParticle(PARTICLE& particle1, PARTICLE& particle2, BOX_GEOMETRY& simBox){
    setParametersForParticleFromParticle(particle1, particle2, simBox);
    return energy(distance);
}

REAL_C LENNARD_JONES_INTERACTION::forceOnParticleFromParticle(PARTICLE& particle1, PARTICLE& particle2, BOX_GEOMETRY& simBox){
    setParametersForParticleFromParticle(particle1, particle2, simBox);
    REAL_C force;
    force = forceAbs(distance) * posDifference / distance;
    return force;
}

void LENNARD_JONES_INTERACTION::setParametersForParticleFromParticle(PARTICLE& particle1, PARTICLE& particle2, BOX_GEOMETRY& simBox){
    posDifference = particle1.boxPosition - particle2.boxPosition;
    posDifference = simBox.convertToBoxPosition(posDifference);
    distance = posDifference.abs();
    diameter = 0.5 * (particle1.diameter + particle2.diameter);
}

