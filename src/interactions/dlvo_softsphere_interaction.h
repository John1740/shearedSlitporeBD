#ifndef DLVO_INTERACTION_H
#define DLVO_INTERACTION_H

#include "../interfaces/force_template_interfaces.h"
#include "lennard_jones_interaction.h"
#include "../struct/charged_particle.h"
#include "../interfaces/box_geometry.h"
#include "../argument_parser/arguments.h"

class DLVO_SOFTSPHERE_INTERACTION: public TWO_BODY_CONSERVATIVE_FORCE<CHARGED_PARTICLE>{
private:
    void calculateKappa();
    void calculateInteractionStrength();
    void calculateCutOffThresholds();

    //Determine the cut-off radius after which (repulsive) particle-particle interactions are truncated.
    //For particles with distance r > r_cutoff, their interaction energy/force is approximated: E(r) = F(r) = 0
    void calculateCutOffRadius();

public:
    DLVO_SOFTSPHERE_INTERACTION();
    DLVO_SOFTSPHERE_INTERACTION(const ARGUMENTS& args);

    double lengthRange = 10;    //needed for cutOff calculation, default questionable

    int charge1 = CHARGE;
    int charge2 = charge1;
    double diameter1 = DIAMETER;
    double diameter2 = diameter1;
    double density = DENSITY;

    double ssInteractionStrength = SS_INTERACTION_STRENGTH;

    //might need to make these private and create getters/setters
    double kappa;
    double interactionStrength;
    double energyCutOffThreshold;
    double forceCutOffThreshold;
    double cutOffRadius, shift1, shift2, shift3;

    double distance;
    REAL_C posDifference;

    void calculateInteractionParameters();

    ////////////////////////////////////////// Calculators ///////////////////////////////////////////

    REAL_C forceOnParticleFromParticle(CHARGED_PARTICLE& particle1, CHARGED_PARTICLE& particle2, BOX_GEOMETRY& simBox);
    double energyOnParticleFromParticle(CHARGED_PARTICLE& particle1, CHARGED_PARTICLE& particle2, BOX_GEOMETRY& simBox);

    double forceOnParticlePerDirection(double r);
    double energyOnParticles(double r);
};

#endif // DLVO_INTERACTION_H
