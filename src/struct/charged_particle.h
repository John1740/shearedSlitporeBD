#ifndef CHARGED_PARTICLE_H
#define CHARGED_PARTICLE_H

#include "particle.h"

class CHARGED_PARTICLE: public PARTICLE{
public:
    int charge;

    CHARGED_PARTICLE();
    CHARGED_PARTICLE(const REAL_C& positionIN);
    CHARGED_PARTICLE(const CHARGED_PARTICLE& other);

    friend ostream& operator<<(ostream& os, const CHARGED_PARTICLE& particle);
};

#endif // CHARGED_PARTICLE_H
