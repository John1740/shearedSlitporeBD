#include "particle.h"

PARTICLE::PARTICLE(){
    position = CARTESIAN_COORDINATE(0.);
    boxPosition = CARTESIAN_COORDINATE(0.);
    diameter = 1.;
}

PARTICLE::PARTICLE(const CARTESIAN_COORDINATE &positionIN){
    position = positionIN;
    boxPosition = CARTESIAN_COORDINATE(0.);
}

PARTICLE::PARTICLE(const PARTICLE &other){
    position = other.position;
    boxPosition = other.boxPosition;
}

CARTESIAN_COORDINATE PARTICLE::getPosition() const{
    return CARTESIAN_COORDINATE(position.x, position.y, position.z);
}

double PARTICLE::distanceTo(PARTICLE &other){
    CARTESIAN_COORDINATE difference;
    difference = position - other.position; //change to boxPosition?
    return difference.getAbs();
}

double PARTICLE::distanceTo(CARTESIAN_COORDINATE &positionIN){
    CARTESIAN_COORDINATE difference;
    difference = position - positionIN;  //change to boxPosition?
    return difference.getAbs();
}

//needs the simulation box information
double PARTICLE::boxDistanceTo(PARTICLE &other){
    CARTESIAN_COORDINATE difference;
    difference = boxPosition - other.boxPosition;
    return difference.getAbs();
}

double PARTICLE::boxDistanceTo(CARTESIAN_COORDINATE &positionIN){
    CARTESIAN_COORDINATE difference;
    difference = boxPosition - positionIN;
    return difference.getAbs();
}

void PARTICLE::setBoxPosition(BOX_GEOMETRY &boxGeom){
    boxPosition = boxGeom.convertToBoxPosition(position);
}

double PARTICLE::getVolume(){
    return diameter * diameter * diameter * M_PI / 6.;  //4pi/3 r^3 = 4pi/3 d^3/8 = pi/6
}