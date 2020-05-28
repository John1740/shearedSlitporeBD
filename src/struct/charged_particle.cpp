#include "charged_particle.h"

CHARGED_PARTICLE::CHARGED_PARTICLE(): PARTICLE(){
    charge = 1;
}

CHARGED_PARTICLE::CHARGED_PARTICLE(const CARTESIAN_COORDINATE& positionIN): PARTICLE(positionIN){
    charge = 1;
}

CHARGED_PARTICLE::CHARGED_PARTICLE(const CHARGED_PARTICLE& other): PARTICLE(other){
    charge = other.charge;
}

