#include "dlvo_softsphere_interaction.h"

DLVO_SOFTSPHERE_INTERACTION::DLVO_SOFTSPHERE_INTERACTION(){
    calculateInteractionParameters();
}

//not needed?
DLVO_SOFTSPHERE_INTERACTION::DLVO_SOFTSPHERE_INTERACTION(const ARGUMENTS &args) {
    ssInteractionStrength = args.ssInteractionStrength;

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

void DLVO_SOFTSPHERE_INTERACTION::calculateCutOffThresholds(){
    LENNARD_JONES_INTERACTION lji;
    lji.diameter = diameter1;
    energyCutOffThreshold = abs(lji.energyOnParticles(3.));
    forceCutOffThreshold = abs(lji.forceOnParticlePerDirection(3.) / 3.);
}

CARTESIAN_COORDINATE DLVO_SOFTSPHERE_INTERACTION::forceOnParticleFromParticle(CHARGED_PARTICLE &particle1, CHARGED_PARTICLE &particle2, BOX_GEOMETRY& simBox){
    CARTESIAN_COORDINATE forceOnParticleFromParticle;
    posDifference = particle1.boxPosition - particle2.boxPosition;
    posDifference = simBox.convertToBoxPosition(posDifference);
    distance = posDifference.getAbs();

    if(distance <= cutOffRadius){
        forceOnParticleFromParticle = (forceOnParticlePerDirection(distance) - shift1) * posDifference / distance;
    }
    return forceOnParticleFromParticle;
}

double DLVO_SOFTSPHERE_INTERACTION::energyOnParticleFromParticle(CHARGED_PARTICLE &particle1, CHARGED_PARTICLE &particle2, BOX_GEOMETRY& simBox){
    posDifference = particle1.boxPosition - particle2.boxPosition;
    distance = simBox.convertToBoxPosition(posDifference).getAbs();

    if(distance <= cutOffRadius){
        return energyOnParticles(distance) + distance * shift1 - (shift2 + shift3);
    }
    else{
        return 0.;
    }
}

void DLVO_SOFTSPHERE_INTERACTION::calculateKappa(){
    double meanCharge = (charge1 + charge2) / 2;
    double chargeConcentration = meanCharge * density;
    //write down parameters somewhere!
    kappa = pow(0.07308561551392402 + 0.34524730769230782857 * chargeConcentration, 0.5);
}

void DLVO_SOFTSPHERE_INTERACTION::calculateInteractionStrength(){
    double alpha = 0.16575255001233970612;
    double Wp1 = charge1 * alpha * exp(0.5 * kappa * diameter1) / (1 + 0.5 * kappa * diameter1);
    double Wp2 = charge2 * alpha * exp(0.5 * kappa * diameter2) / (1 + 0.5 * kappa * diameter2);
    interactionStrength = Wp1 * Wp2; //why squared? how is alpha defined?
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
        currentForce = forceOnParticlePerDirection(i * rcDelta) / (i * rcDelta);
        if(abs(currentEnergy) < energyCutOffThreshold && abs(currentForce) < forceCutOffThreshold){
            tmpCutOffRadius = i * rcDelta;
            break;
        }
    }
    cutOffRadius = tmpCutOffRadius;
}

double DLVO_SOFTSPHERE_INTERACTION::energyOnParticles(double r){
    double yukawaEnergy = interactionStrength * exp(-kappa * r) / r;
    double softSphereEnergy = 4 * ssInteractionStrength * pow(diameter1 / r, 12);
    double energyOnParticles = yukawaEnergy + softSphereEnergy;
    return energyOnParticles;
}

double DLVO_SOFTSPHERE_INTERACTION::forceOnParticlePerDirection(double r){
    double yukawaForceAbs = interactionStrength * exp(-kappa * r) * (1. / (r * r) + kappa / r);
    double softSphereForceAbs = 48 * ssInteractionStrength * pow(diameter1 / r, 13) / diameter1;
    double forceOnParticlePerDirection = yukawaForceAbs + softSphereForceAbs;
    return forceOnParticlePerDirection;
}
