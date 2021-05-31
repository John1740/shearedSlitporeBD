#include "dlvo_softsphere_interaction.h"

DLVO_SOFTSPHERE_INTERACTION::DLVO_SOFTSPHERE_INTERACTION(){
    calculateInteractionParameters();
}

DLVO_SOFTSPHERE_INTERACTION::DLVO_SOFTSPHERE_INTERACTION(double ssInteractionStrength){
    this->ssInteractionStrength = ssInteractionStrength;
    calculateInteractionParameters();
}

void DLVO_SOFTSPHERE_INTERACTION::calculateInteractionParameters(){
    calculateKappa();
    calculateInteractionStrength();
    calculateCutOffRadius();
    calculateShifts();

    // temporary start
    int numberOfSteps = 4000;
    double rcDelta = 3. / numberOfSteps;
    double currentRadius, currentEnergy, currentForce, shiftedEnergy, shiftedForce;
    cout << "r \t E \t F \t E_sh \t F_sh" << endl;
    for(int i = 0; i < numberOfSteps; ++i){
        currentRadius = i * rcDelta;
        currentEnergy = energy(currentRadius);
        currentForce = forceAbs(currentRadius);
        shiftedEnergy = energyShifted(currentRadius);
        shiftedForce = forceAbsShifted(currentRadius);
        cout << currentRadius << "\t" << currentEnergy << "\t" << currentForce << "\t" << shiftedEnergy << "\t" << shiftedForce << endl;
    }
    // temporary end
}

double DLVO_SOFTSPHERE_INTERACTION::calculateKappa(){
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
    return kappa;
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
    YinteractionStrength = Wp1 * Wp2 / diameter;
}

//Determine the cut-off radius after which (repulsive) particle-particle interactions are truncated.
//For particles with distance r > rC, their interaction energy/force is approximated: E(r) = F(r) = 0
//both energy and force need to be smaller than residual energy/force of the Lennard-Jones potential at 3d
double DLVO_SOFTSPHERE_INTERACTION::calculateCutOffRadius(){
    calculateCutOffThresholds();
    double tmpCutOffRadius;
    double currentRadius, currentEnergy, currentForce;
    int numberOfSteps = 4000;
    double rcDelta = lengthRange / numberOfSteps;
    for(int i = 0; i < numberOfSteps; ++i){
        currentRadius = i * rcDelta;
        currentEnergy = energy(currentRadius);
        currentForce = forceAbs(currentRadius);
        //logical AND (&&) also makes sure that initial zero-crossings of the energy or force (in partly attractive
        //partly repulsive force fields don't accidentally break the loop too early
        if(abs(currentEnergy) < energyCutOffThreshold && abs(currentForce) < forceCutOffThreshold){
            tmpCutOffRadius = currentRadius;
            break;
        }
    }
    cutOffRadius = tmpCutOffRadius;
    return cutOffRadius;
}

//choose energy and force thresholds equal to those a Lennard Jones potential would have at r/d = rLJ (default = 3)
void DLVO_SOFTSPHERE_INTERACTION::calculateCutOffThresholds(double rLJ){
    LENNARD_JONES_INTERACTION lji;
    energyCutOffThreshold = abs(lji.energy(rLJ));
    forceCutOffThreshold = abs(lji.forceAbs(rLJ));
}

void DLVO_SOFTSPHERE_INTERACTION::calculateShifts(){
    forceShift = forceAbs(cutOffRadius);
    energyShift = energy(cutOffRadius);
}

double
DLVO_SOFTSPHERE_INTERACTION::energyOnParticleFromParticle(CHARGED_PARTICLE& particle1, CHARGED_PARTICLE& particle2,
                                                          BOX_GEOMETRY& simBox){
    REAL_C posDifference = particle1.boxPosition - particle2.boxPosition;
    posDifference = simBox.convertToBoxPosition(posDifference);
    double distance = posDifference.abs();
    double energyOnParticleFromParticle = energyShifted(distance);
    return energyOnParticleFromParticle;
}

REAL_C
DLVO_SOFTSPHERE_INTERACTION::forceOnParticleFromParticle(CHARGED_PARTICLE& particle1, CHARGED_PARTICLE& particle2,
                                                         BOX_GEOMETRY& simBox){
    REAL_C force; //defaults to (0,0,0)
    REAL_C posDifference = particle1.boxPosition - particle2.boxPosition;
    posDifference = simBox.convertToBoxPosition(posDifference);
    double distance = posDifference.abs();
    force = forceAbsShifted(distance) * posDifference / distance;
    return force;
}

double DLVO_SOFTSPHERE_INTERACTION::energy(double r){
    double diameter = 0.5 * (diameter1 + diameter2);
    double yukawaEnergy = YinteractionStrength * diameter * exp(-kappa * r) / r;
    double softSphereEnergy = 4 * ssInteractionStrength * pow(diameter / r, 12);
    double energy = yukawaEnergy + softSphereEnergy;
    return energy;
}

double DLVO_SOFTSPHERE_INTERACTION::forceAbs(double r){
    double diameter = (diameter1 + diameter2) / 2;
    double yukawaForceAbs = YinteractionStrength * diameter * exp(-kappa * r) * (1. / (r * r) + kappa / r);
    double softSphereForceAbs = 48 * ssInteractionStrength * pow(diameter / r, 13) / diameter;
    double forceAbs = yukawaForceAbs + softSphereForceAbs;
    return forceAbs;
}

double DLVO_SOFTSPHERE_INTERACTION::energyShifted(double r){
    double energyShifted = 0;
    if(r <= cutOffRadius){
        //remove first and second order terms of Taylor series (around r=rC)
        //U_shifted(r) = U(r) - U(rC) - U'(rC) * (r - rC)
        //forceShift = -U'(rC)
        energyShifted = energy(r) - energyShift + forceShift * (r - cutOffRadius);
    }
    return energyShifted;
}

double DLVO_SOFTSPHERE_INTERACTION::forceAbsShifted(double r){
    double force = 0;
    if(r <= cutOffRadius){
        force = forceAbs(r) - forceShift;
    }
    return force;
}
