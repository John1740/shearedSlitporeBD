#ifndef DLVO_INTERACTION_H
#define DLVO_INTERACTION_H

#include "../interfaces/force_template_interfaces.h"
#include "lennard_jones_interaction.h"
#include "../struct/charged_particle.h"
#include "../interfaces/box_geometry.h"
#include "../defaults.h"

class DLVO_SOFTSPHERE_INTERACTION: public TWO_BODY_CONSERVATIVE_FORCE<CHARGED_PARTICLE>{
private:
    double calculateKappa();
    void calculateInteractionStrength();
    void calculateCutOffThresholds(double rLJ = 3.);

    double calculateCutOffRadius();
    void calculateShifts();

public:
    DLVO_SOFTSPHERE_INTERACTION();
    DLVO_SOFTSPHERE_INTERACTION(double ssInteractionStrength);
    void calculateInteractionParameters();

    double lengthRange = 10;    //needed for cutOff calculation, default questionable

    int charge1 = CHARGE;
    int charge2 = charge1;
    double diameter1 = DIAMETER;
    double diameter2 = diameter1;
    double density = DENSITY;

    double ssInteractionStrength = SS_INTERACTION_STRENGTH;
    double YinteractionStrength;
    double kappa;

    //might need to make these private and create getters/setters
    double energyCutOffThreshold, forceCutOffThreshold;
    double cutOffRadius, forceShift, energyShift;

    ////////////////////////////////////////// Calculators ///////////////////////////////////////////

    double energyOnParticleFromParticle(CHARGED_PARTICLE& particle1, CHARGED_PARTICLE& particle2, BOX_GEOMETRY& simBox);
    REAL_C forceOnParticleFromParticle(CHARGED_PARTICLE& particle1, CHARGED_PARTICLE& particle2, BOX_GEOMETRY& simBox);

    double energy(double r);
    double forceAbs(double r);
    double energyShifted(double r);
    double forceAbsShifted(double r);
};

#endif // DLVO_INTERACTION_H
