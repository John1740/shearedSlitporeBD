#include "charged_particle.h"

CHARGED_PARTICLE::CHARGED_PARTICLE(): PARTICLE(){
    charge = 1;
}

CHARGED_PARTICLE::CHARGED_PARTICLE(const REAL_C& positionIN): PARTICLE(positionIN){
    charge = 1;
}

CHARGED_PARTICLE::CHARGED_PARTICLE(const CHARGED_PARTICLE& other): PARTICLE(other){
    charge = other.charge;
}

ostream& operator<<(ostream& os, const CHARGED_PARTICLE& particle){
    os << "CHARGED_PARTICLE(";
    os << "charge: " << particle.charge << ", ";
    os << "diameter: " << particle.diameter << ", ";
    os << "species: " << particle.species << ", ";
    os << "boxPosition: " << particle.boxPosition;
    os << ")";
    return os;
}
