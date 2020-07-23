//
// Created by mhuels on 7/9/20.
//

#include "real_coordinate.h"
#include "math.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

REAL_C::REAL_C() : CARTESIAN_COORDINATE(){

}

REAL_C::REAL_C(double c): CARTESIAN_COORDINATE(c){

}

REAL_C::REAL_C(double x, double y, double z): CARTESIAN_COORDINATE(x, y, z){

}

REAL_C::REAL_C(const REAL_C& other) : CARTESIAN_COORDINATE(other){

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double REAL_C::abs() const{
    return sqrt(x * x + y * y + z * z);
}

