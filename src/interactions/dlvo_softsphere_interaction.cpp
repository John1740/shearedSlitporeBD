#include "dlvo_softsphere_interaction.h"
#include <boost/format.hpp>

namespace bo = boost;

DLVO_SOFTSPHERE_INTERACTION::DLVO_SOFTSPHERE_INTERACTION(){
    calculateInteractionParameters();
}

DLVO_SOFTSPHERE_INTERACTION::DLVO_SOFTSPHERE_INTERACTION(double ssInteractionStrength){
    this->ssInteractionStrength = ssInteractionStrength;
    calculateInteractionParameters();
}

void DLVO_SOFTSPHERE_INTERACTION::calculateInteractionParameters(){
    calculateCutOffRadius();
    calculateShifts(cutOffRadius);

    // temporary start
//    int numberOfSteps = 4000;
//    double rcDelta = 3. / numberOfSteps;
//    double currentRadius, currentEnergy, currentForce, shiftedEnergy, shiftedForce;
//    cout << "r \t E \t F \t E_sh \t F_sh" << endl;
//    for(int i = 0; i < numberOfSteps; ++i){
//        currentRadius = i * rcDelta;
//        currentEnergy = energy(currentRadius);
//        currentForce = forceAbs(currentRadius);
//        shiftedEnergy = energyShifted(currentRadius);
//        shiftedForce = forceAbsShifted(currentRadius);
//        cout << currentRadius << "\t" << currentEnergy << "\t" << currentForce << "\t" << shiftedEnergy << "\t" << shiftedForce << endl;
//    }
    // temporary end
}

//Z: charge (unit: 1)
//rho: density (unit: d^-3)
//I: ionic strength (unit: mol l^-1)
//T: temperature (unit: K)
//d: particle diameter (unit: m)
//eps: permittivity (unit: 1)
double DLVO_SOFTSPHERE_INTERACTION::calculateKappa(int Z, double rho, double I, double T, double d, double eps){
    double rho_SI = rho / d / d / d;    //unit: m^-3
    double I_SI = I * 1e3;              //unit: mol m^-3
    //for comparison with Sascha's code
//    double x1_SI = 2 * e0 * e0 * I_SI * NA / eps / eps0 / kB / T;   //unit: m^-2
//    double x1 = x1_SI * d * d;  //unit: d^-2
//    double x1 = 0.07308561551392402;
//    double x2_SI = e0 * e0 / eps / eps0 / kB / T;   //unit: m
//    double x2 = x2_SI / d;  //unit: d
//    double x2 = 0.34524730769230782857;
//    kappa = pow(x1 + x2 * Z * rho, 0.5)
    double prefactor = e0 * e0 / (eps * eps0 * kB * T);
    double kappa_SI = pow(prefactor * (Z * rho_SI + 2 * I_SI * NA), 0.5);
    kappa = kappa_SI * d;
    return kappa;
}

//kappa: inverse Debye screening length (unit: d^-1)
//Z: charge (unit: 1)
//T: temperature (unit: K)
//d_SI: particle diameter (unit: m)
//eps: permittivity (unit: 1)
double DLVO_SOFTSPHERE_INTERACTION::calculateInteractionStrength(double kappaIn, int Z, double T, double d_SI, double eps){
    //alpha^2 = e0^2 / 4 / pi / eps / eps0
    //for comparison with Sascha's code
//    double alpha_SI = sqrt(e0 * e0 / (4 * M_PI * eps * eps0));    //unit: J^1/2 m^1/2
//    double alpha = alpha_SI / sqrt(kB * T * d_SI);    //unit: kT^1/2 d^1/2
//    double alpha = 0.16575255001233970612;
//    double diameter = (diameter1 + diameter2) / 2;
//    double Wp1 = charge1 * alpha * exp(0.5 * kappa * diameter1) / (1 + 0.5 * kappa * diameter1);
//    double Wp2 = charge2 * alpha * exp(0.5 * kappa * diameter2) / (1 + 0.5 * kappa * diameter2);
//    yInteractionStrength = Wp1 * Wp2 / diameter;
    double d = d_SI / d_SI;  //unit: d
    double prefactor = Z * e0 * Z * e0 / (4 * M_PI * eps * eps0 * d_SI);    //unit: J
    double yInteractionStrength_SI = prefactor * exp(kappaIn * d) / pow(1. + 0.5 * kappaIn * d, 2); //unit: J
    yInteractionStrength = yInteractionStrength_SI / (kB * T);   //unit: kT
    return yInteractionStrength;
}

//Determine the cut-off radius after which (repulsive) particle-particle interactions are truncated.
//For particles with distance r > rC, their interaction energy/force is approximated: E(r) = F(r) = 0
//both energy and force need to be smaller than residual energy/force of the Lennard-Jones potential at 3d
double DLVO_SOFTSPHERE_INTERACTION::calculateCutOffRadius(){
    calculateCutOffThresholds();
    double tmpCutOffRadius = lengthRange;   //maximal range in case energy/force doesn't converge
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

void DLVO_SOFTSPHERE_INTERACTION::calculateShifts(double cutOffRadiusIn){
    forceShift = forceAbs(cutOffRadiusIn);
    energyShift = energy(cutOffRadiusIn);
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

double DLVO_SOFTSPHERE_INTERACTION::energy(double r) const{
    double yukawaEnergy = yInteractionStrength * diameter * exp(-kappa * r) / r;
    double softSphereEnergy = 4 * ssInteractionStrength * pow(diameter / r, 12);
    double energy = yukawaEnergy + softSphereEnergy;
    return energy;
}

double DLVO_SOFTSPHERE_INTERACTION::forceAbs(double r) const{
    double yukawaForceAbs = yInteractionStrength * diameter * exp(-kappa * r) * (1. / (r * r) + kappa / r);
    double softSphereForceAbs = 48 * ssInteractionStrength * pow(diameter / r, 13) / diameter;
    double forceAbs = yukawaForceAbs + softSphereForceAbs;
    return forceAbs;
}

double DLVO_SOFTSPHERE_INTERACTION::energyShifted(double r) const{
    double energyShifted = 0;
    if(r <= cutOffRadius){
        //remove first and second order terms of Taylor series (around r=rC)
        //U_shifted(r) = U(r) - U(rC) - U'(rC) * (r - rC)
        //forceShift = -U'(rC)
        energyShifted = energy(r) - energyShift + forceShift * (r - cutOffRadius);
    }
    return energyShifted;
}

double DLVO_SOFTSPHERE_INTERACTION::forceAbsShifted(double r) const{
    double force = 0;
    if(r <= cutOffRadius){
        force = forceAbs(r) - forceShift;
    }
    return force;
}

ostream& operator<<(ostream& os, const DLVO_SOFTSPHERE_INTERACTION& dlvo){
    const char* fmt = "% .8f\t";
    os << "diameter: " << bo::format(fmt) % (dlvo.diameter) << "[d]" << endl;
    os << "kappa: " << bo::format(fmt) % (dlvo.kappa) << "[d-1]" << endl;
    os << "yInteractionStrength: " << bo::format(fmt) % (dlvo.yInteractionStrength) << "[kT]" << endl;
    os << "ssInteractionStrength: " << bo::format(fmt) % (dlvo.ssInteractionStrength) << "[kT]" << endl;
    os << "cutOffRadius: " << bo::format(fmt) % (dlvo.cutOffRadius) << "[d]" << endl;
    os << "energyCutOffThreshold: " << bo::format(fmt) % (dlvo.energyCutOffThreshold) << "[kT]" << endl;
    os << "forceCutOffThreshold: " << bo::format(fmt) % (dlvo.forceCutOffThreshold) << "[kT d-1]" << endl;
    return os;
}