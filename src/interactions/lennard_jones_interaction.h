#ifndef LENNARD_JONES_INTERACTION_H
#define LENNARD_JONES_INTERACTION_H

#include "../interfaces/force_template_interfaces.h"
#include "../struct/particle.h"

class LENNARD_JONES_INTERACTION: public TWO_BODY_CONSERVATIVE_FORCE<PARTICLE>{
private:

public:
    double interactionStrength;
    double diameter;

    double distance;
    REAL_C positionDifference;

    LENNARD_JONES_INTERACTION();
    LENNARD_JONES_INTERACTION(double interactionStrengthIN);

    REAL_C forceOnParticleFromParticle(PARTICLE& particle1, PARTICLE& particle2, BOX_GEOMETRY& simBox);
    double energyOnParticleFromParticle(PARTICLE& particle1, PARTICLE& particle2, BOX_GEOMETRY& simBox);

    double energyOnParticles(double distance);
    double forceOnParticlePerDirection(double distance);

    void setParametersForParticleFromParticle(PARTICLE& particle1, PARTICLE& particle2);
};

#endif // LENNARD_JONES_INTERACTION_H
