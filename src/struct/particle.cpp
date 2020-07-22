#include "particle.h"

PARTICLE::PARTICLE(){
    position = REAL_C(0.);
    boxPosition = REAL_C(0.);
    diameter = 1;
    species = 0;
    index = 0;
}

PARTICLE::PARTICLE(const REAL_C &positionIN){
    position = positionIN;
    boxPosition = REAL_C(0.);
    diameter = 1;
    species = 0;
    index = 0;
}

PARTICLE::PARTICLE(const PARTICLE &other){
    position = other.position;
    boxPosition = other.boxPosition;
    diameter = other.diameter;
    species = other.species;
    index = other.index;
}

REAL_C PARTICLE::getPosition() const{
    return REAL_C(position.x, position.y, position.z);
}

double PARTICLE::distanceTo(PARTICLE &other){
    REAL_C difference;
    difference = position - other.position; //change to boxPosition?
    return difference.abs();
}

double PARTICLE::distanceTo(REAL_C &positionIN){
    REAL_C difference;
    difference = position - positionIN;  //change to boxPosition?
    return difference.abs();
}

//needs the simulation box information
double PARTICLE::boxDistanceTo(PARTICLE &other, BOX_GEOMETRY& boxGeom){
    REAL_C difference;
    difference = boxPosition - other.boxPosition;
    difference = boxGeom.convertToBoxPosition(difference);
    return difference.abs();
}

double PARTICLE::boxDistanceTo(REAL_C &positionIN, BOX_GEOMETRY& boxGeom){
    REAL_C difference;
    difference = boxPosition - positionIN;
    difference = boxGeom.convertToBoxPosition(difference);
    return difference.abs();
}

void PARTICLE::setBoxPosition(BOX_GEOMETRY &boxGeom){
    boxPosition = boxGeom.convertToBoxPosition(position);
}

double PARTICLE::getVolume(){
    return diameter * diameter * diameter * M_PI / 6.;  //4pi/3 r^3 = 4pi/3 d^3/8 = pi/6
}