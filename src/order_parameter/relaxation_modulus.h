//
// Created by mhuels on 6/12/20.
//

#ifndef SHEAREDSLITPOREBD_RELAXATION_MODULUS_H
#define SHEAREDSLITPOREBD_RELAXATION_MODULUS_H

#include <vector>
#include "../systems/sheared_slitpore_system.h"

using namespace std;

class RELAXATION_MODULUS{
private:
    vector<long> timestep;
    vector<double> G;   //needs to be a matrix? or is it the same G for each ij?
    vector<double> shearRate;
    vector<double> stress;
//    int numberOfTimesteps;
    double dt;
public:
    RELAXATION_MODULUS();
    RELAXATION_MODULUS(SHEARED_SLITPORE_SYSTEM& sys);
    
    RELAXATION_MODULUS& reset();
    
    RELAXATION_MODULUS& calculateNext(SHEARED_SLITPORE_SYSTEM& sys);
    
    //getter
    vector<double> getShearRates() const;
    vector<double> getG() const;
    vector<long> getTimesteps() const;
    vector<double> getStress() const;
    double getDt() const;
    
    //setter
    RELAXATION_MODULUS& setDt(double dt);
    
    //printer
    friend ostream& operator<<(ostream& os, const RELAXATION_MODULUS& relaxationModulus);
};


#endif //SHEAREDSLITPOREBD_RELAXATION_MODULUS_H
