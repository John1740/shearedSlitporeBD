#ifndef DLVO_INTERACTION_H
#define DLVO_INTERACTION_H

#include "../interfaces/force_template_interfaces.h"
#include "lennard_jones_interaction.h"
#include "../struct/charged_particle.h"
#include "../interfaces/box_geometry.h"
#include "../argument_parser/arguments.h"

class DLVO_SOFTSPHERE_INTERACTION: public TWO_BODY_CONSERVATIVE_FORCE<CHARGED_PARTICLE>{

    void setParametersForAllChargeCompositions();
    void setKappa();

public:
    double distance = 1.;
    CARTESIAN_COORDINATE posDifference;

    double energyCutOffThreshold;
    double forceCutOffThreshold;

    double rcDelta = 1. / 4000.;

    double kappa;
    int charge = CHARGE;
    double diameter = DIAMETER;
    double rho = DENSITY;
    double cutOffRadius, shift1, shift2, shift3, interactionStrength;

    double ssInteractionStrength = SS_INTERACTION_STRENGTH;

    DLVO_SOFTSPHERE_INTERACTION();
    DLVO_SOFTSPHERE_INTERACTION(const ARGUMENTS& args);

    void setInteractionParameters();
    void calculateCutOffThreshold();

    CARTESIAN_COORDINATE forceOnParticleFromParticle(CHARGED_PARTICLE& particle1, CHARGED_PARTICLE& particle2, BOX_GEOMETRY& simBox);
    double energyOnParticleFromParticle(CHARGED_PARTICLE& particle1, CHARGED_PARTICLE& particle2, BOX_GEOMETRY& simBox);

//FAST:
    bool isInRangeSetDistanceAndId(CHARGED_PARTICLE& particle1, CHARGED_PARTICLE& particle2, BOX_GEOMETRY& simBox);
    CARTESIAN_COORDINATE fastForce();

    double getInteractionStrength(int Z1, double diameter1, int Z2, double diameter2);

//   Determine the cut-off radius after which (repulsive) particle-particle interactions are truncated.
//   For particles with distance r > r_cutoff, their interaction energy/force is approximated: E(r) = F(r) = 0
    double getCutOffRadius();
    double getMaxCutOffRadius();

    double forceOnParticlePerDirection(double r);
    double energyOnParticles(double r);

    void setRcDelta(double length);
};

#endif // DLVO_INTERACTION_H
