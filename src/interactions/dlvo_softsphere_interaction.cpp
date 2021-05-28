#include "dlvo_softsphere_interaction.h"

DLVO_SOFTSPHERE_INTERACTION::DLVO_SOFTSPHERE_INTERACTION(){
    calculateInteractionParameters();
}

//not needed?
DLVO_SOFTSPHERE_INTERACTION::DLVO_SOFTSPHERE_INTERACTION(double ssInteractionStrength){
    this->ssInteractionStrength = ssInteractionStrength;
    calculateInteractionParameters();
}

void DLVO_SOFTSPHERE_INTERACTION::calculateInteractionParameters(){
    calculateKappa();
    calculateInteractionStrength();
    calculateCutOffRadius();
    //unclear names!
    shift1 = forceOnParticlePerDirection(cutOffRadius);
    shift2 = energyOnParticles(cutOffRadius);
    shift3 = shift1 * cutOffRadius;
}

void DLVO_SOFTSPHERE_INTERACTION::calculateKappa(){
    double meanCharge = (charge1 + charge2) / 2;
    double chargeConcentration = meanCharge * density;  //unit: d^-3
    //e0 = 1.602e-19 C
    //I = 1e-5 mol l^-1 = 1e-2 mol m^-3
    //NA = 6.022e23 mol^-1
    //eps = 78.5
    //eps0 = 8.854e-12 C^2 J^-1 m^-1
    //d = 26e-9 m, m = 3.846e7 d
    //T = 298 K, kT = 4.115e-21 J, J = 2.430e20 kT
    //x1 = 2 * e0^2 * I * NA / eps / eps0 / kT
    double x1 = 0.07308561551392402;
    //x2 = e0^2 / eps / eps0 / kT
    double x2 = 0.34524730769230782857;
    kappa = pow(x1 + x2 * chargeConcentration, 0.5);    //unit: d^-1
}

void DLVO_SOFTSPHERE_INTERACTION::calculateInteractionStrength(){
    //alpha^2 = e0^2 / 4 / pi / eps / eps0
    //e0 = 1.602e-19 C
    //eps = 78.5
    //eps0 = 8.854e-12 C^2 J^-1 m^-1
    //d = 26e-9 m, m = 3.846e7 d
    //T = 298 K, kT = 4.115e-21 J, J = 2.430e20 kT
    double alpha = 0.16575255001233970612;  //unit: kT^1/2 d^1/2
    double diameter = (diameter1 + diameter2) / 2;
    //TODO: should every diameter be the mean diameter?
    double Wp1 = charge1 * alpha * exp(0.5 * kappa * diameter1) / (1 + 0.5 * kappa * diameter1);
    double Wp2 = charge2 * alpha * exp(0.5 * kappa * diameter2) / (1 + 0.5 * kappa * diameter2);
    interactionStrength = Wp1 * Wp2 / diameter;
}

void DLVO_SOFTSPHERE_INTERACTION::calculateCutOffRadius(){
    calculateCutOffThresholds();

    double tmpCutOffRadius;
    double currentRadius, currentEnergy, currentForce;
    int numberOfSteps = 4000;
    double rcDelta = lengthRange / numberOfSteps;

    for(int i = 0; i < numberOfSteps; ++i){
        currentRadius = i * rcDelta;
        currentEnergy = energyOnParticles(currentRadius);
        currentForce = forceOnParticlePerDirection(currentRadius);
//        currentForce = forceOnParticlePerDirection(currentRadius) / (currentRadius);
        //forceCutOffThreshold would make sure that cutoffRadius is taken on the right side of the minimum of
        //the Lennard-Jones potential
        //however, this potential is purely repulsive and the energy is always > 0
        if(abs(currentEnergy) < energyCutOffThreshold && abs(currentForce) < forceCutOffThreshold){
            tmpCutOffRadius = currentRadius;
            break;
        }
    }
    cutOffRadius = tmpCutOffRadius;
}

void DLVO_SOFTSPHERE_INTERACTION::calculateCutOffThresholds(){
    LENNARD_JONES_INTERACTION lji;
    lji.diameter = diameter1;
    energyCutOffThreshold = abs(lji.energyOnParticles(3.));
    forceCutOffThreshold = abs(lji.forceOnParticlePerDirection(3.));
//    forceCutOffThreshold = abs(lji.forceOnParticlePerDirection(3.) / 3.);
}

double
DLVO_SOFTSPHERE_INTERACTION::energyOnParticleFromParticle(CHARGED_PARTICLE& particle1, CHARGED_PARTICLE& particle2,
                                                          BOX_GEOMETRY& simBox){
    posDifference = particle1.boxPosition - particle2.boxPosition;
    distance = simBox.convertToBoxPosition(posDifference).abs();

    if(distance <= cutOffRadius){
        return energyOnParticles(distance) + distance * shift1 - (shift2 + shift3);
//        return energyOnParticles(distance) - distance * shift1 - shift2 + shift3; //should be correct
    }
    else{
        return 0.;
    }
}

REAL_C
DLVO_SOFTSPHERE_INTERACTION::forceOnParticleFromParticle(CHARGED_PARTICLE& particle1, CHARGED_PARTICLE& particle2,
                                                         BOX_GEOMETRY& simBox){
    REAL_C forceOnParticleFromParticle;
    posDifference = particle1.boxPosition - particle2.boxPosition;
    posDifference = simBox.convertToBoxPosition(posDifference);
    distance = posDifference.abs();

    if(distance <= cutOffRadius){
        forceOnParticleFromParticle = (forceOnParticlePerDirection(distance) - shift1) * posDifference / distance;
    }
    return forceOnParticleFromParticle;
}

double DLVO_SOFTSPHERE_INTERACTION::energyOnParticles(double r){
    double diameter = (diameter1 + diameter2) / 2;
    double yukawaEnergy = interactionStrength * diameter * exp(-kappa * r) / r;
    double softSphereEnergy = 4 * ssInteractionStrength * pow(diameter / r, 12);
    double energyOnParticles = yukawaEnergy + softSphereEnergy;
    return energyOnParticles;
}

double DLVO_SOFTSPHERE_INTERACTION::forceOnParticlePerDirection(double r){
    double diameter = (diameter1 + diameter2) / 2;
    double yukawaForceAbs = interactionStrength * diameter * exp(-kappa * r) * (1. / (r * r) + kappa / r);
    double softSphereForceAbs = 48 * ssInteractionStrength * pow(diameter / r, 13) / diameter;
    double forceOnParticlePerDirection = yukawaForceAbs + softSphereForceAbs;
    return forceOnParticlePerDirection;
}
