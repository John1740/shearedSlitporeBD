#ifndef LENNARD_JONES_INTERACTION_H
#define LENNARD_JONES_INTERACTION_H

#include "../interfaces/force_template_interfaces.h"
#include "../interfaces/box_geometry.h"
#include "../struct/particle.h"

class LENNARD_JONES_INTERACTION: public TWO_BODY_CONSERVATIVE_FORCE<PARTICLE>{
private:
    double distance;
    REAL_C posDifference;

    void setParametersForParticleFromParticle(PARTICLE& particle1, PARTICLE& particle2, BOX_GEOMETRY& simBox);

public:
    double interactionStrength;
    double diameter;

    LENNARD_JONES_INTERACTION();
    LENNARD_JONES_INTERACTION(double interactionStrength);
    LENNARD_JONES_INTERACTION(double interactionStrength, double diameter);

    REAL_C forceOnParticleFromParticle(PARTICLE& particle1, PARTICLE& particle2, BOX_GEOMETRY& simBox);
    double energyOnParticleFromParticle(PARTICLE& particle1, PARTICLE& particle2, BOX_GEOMETRY& simBox);

    double energy(double r);
    double forceAbs(double r);
};

#endif // LENNARD_JONES_INTERACTION_H
