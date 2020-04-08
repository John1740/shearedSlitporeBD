#include "dlvo_softsphere_interaction.h"

DLVO_SOFTSPHERE_INTERACTION::DLVO_SOFTSPHERE_INTERACTION(){
    calculateCutOffThreshold();
    setInteractionParameters();
}

DLVO_SOFTSPHERE_INTERACTION::DLVO_SOFTSPHERE_INTERACTION(const ARGUMENTS &args) {
    ssInteractionStrength = args.ssInteractionStrength;
    charge = args.charge;
    diameter = args.diameter;
    rho = args.density;

    calculateCutOffThreshold();
    setInteractionParameters();
}

void DLVO_SOFTSPHERE_INTERACTION::setInteractionParameters(){
    setKappa();
    setParametersForAllChargeCompositions();
}

void DLVO_SOFTSPHERE_INTERACTION::calculateCutOffThreshold(){
    LENNARD_JONES_INTERACTION lji;
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

bool DLVO_SOFTSPHERE_INTERACTION::isInRangeSetDistanceAndId(CHARGED_PARTICLE &particle1, CHARGED_PARTICLE &particle2, BOX_GEOMETRY& simBox){
    bool isInRange = false;

    posDifference = particle1.boxPosition - particle2.boxPosition;
    posDifference = simBox.convertToBoxPosition(posDifference);
    distance = posDifference.getAbs();

    if(distance <= cutOffRadius){
        isInRange = true;
    }

    return isInRange;
}

CARTESIAN_COORDINATE DLVO_SOFTSPHERE_INTERACTION::fastForce(){
    return posDifference * (forceOnParticlePerDirection(distance) - shift1) / distance;
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

void DLVO_SOFTSPHERE_INTERACTION::setKappa(){
    double chargeConcentration = charge * rho;

    //write down parameters somewhere!
    kappa = pow(0.07308561551392402 + 0.34524730769230782857 * chargeConcentration, 0.5);
}

void DLVO_SOFTSPHERE_INTERACTION::setParametersForAllChargeCompositions(){
    interactionStrength = getInteractionStrength(charge, diameter, charge, diameter);
    cutOffRadius = getCutOffRadius();
    //unclear names!
    shift1 = forceOnParticlePerDirection(cutOffRadius);
    shift2 = energyOnParticles(cutOffRadius);
    shift3 = shift1 * cutOffRadius;
}

double DLVO_SOFTSPHERE_INTERACTION::getInteractionStrength(int Z1, double diameter1, int Z2, double diameter2){
    double alpha = 0.16575255001233970612;
    double Wp1 = Z1 * alpha * exp(0.5 * kappa * diameter1) / (1 + 0.5 * kappa * diameter1);
    double Wp2 = Z2 * alpha * exp(0.5 * kappa * diameter2) / (1 + 0.5 * kappa * diameter2);

    return Wp1 * Wp2; //why squared? how is alpha defined?
}

double DLVO_SOFTSPHERE_INTERACTION::getCutOffRadius(){
    LENNARD_JONES_INTERACTION lji;
    lji.diameter = diameter;
    energyCutOffThreshold = abs(lji.energyOnParticles(3.));
    forceCutOffThreshold = abs(lji.forceOnParticlePerDirection(3.) / 3.);

    double cutOffRadius;
    double currentRadius, currentEnergy, currentForce;

    for(int i = 0; i < 4000; ++i){
        currentRadius = i * rcDelta;
        currentEnergy = energyOnParticles(currentRadius);
        currentForce = forceOnParticlePerDirection(i * rcDelta) / (i * rcDelta);
        if(abs(currentEnergy) < energyCutOffThreshold && abs(currentForce) < forceCutOffThreshold){
            cutOffRadius = i * rcDelta;
            break;
        }
    }
    return cutOffRadius;
}

double DLVO_SOFTSPHERE_INTERACTION::energyOnParticles(double r){
    double yukawaEnergy = interactionStrength * exp(-kappa * r) / r;
    double softSphereEnergy = 4 * ssInteractionStrength * pow(diameter / r, 12);
    double energyOnParticles = yukawaEnergy + softSphereEnergy;
    return energyOnParticles;
}

double DLVO_SOFTSPHERE_INTERACTION::forceOnParticlePerDirection(double r){
    double yukawaForceAbs = interactionStrength * exp(-kappa * r) * (1. / (r * r) + kappa / r);
    double softSphereForceAbs = 48 * ssInteractionStrength * pow(diameter / r, 13) / diameter;
    double forceOnParticlePerDirection = yukawaForceAbs + softSphereForceAbs;
    return forceOnParticlePerDirection;
}

//probably obsolete
double DLVO_SOFTSPHERE_INTERACTION::getMaxCutOffRadius(){
    //NEEDED: check if cutoff radii have been calculated yet
    double maxRC = 0.;

    if(cutOffRadius > maxRC){
        maxRC = cutOffRadius;
    }
    return maxRC;
}

void DLVO_SOFTSPHERE_INTERACTION::setRcDelta(double length){
    rcDelta = length / 4000.;
}



