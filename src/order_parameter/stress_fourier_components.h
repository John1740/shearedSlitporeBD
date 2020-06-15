//
// Created by mhuels on 6/15/20.
//

#ifndef SHEAREDSLITPOREBD_STRESS_FOURIER_COMPONENTS_H
#define SHEAREDSLITPOREBD_STRESS_FOURIER_COMPONENTS_H


#include "../argument_parser/arguments.h"
#include "../struct/cartesian_matrix.h"
#include "../struct/cartesian_matrix_2.h"
#include "../systems/sheared_slitpore_system.h"
#include <vector>
#include <complex>

class STRESS_FOURIER_COMPONENTS{
private:
    int numberOfTimesteps;
    vector<CARTESIAN_MATRIX> stress;
    double period;
    double dt;

public:
    STRESS_FOURIER_COMPONENTS();
    STRESS_FOURIER_COMPONENTS(const ARGUMENTS& args);
    STRESS_FOURIER_COMPONENTS(string filename);
    
    STRESS_FOURIER_COMPONENTS& setup(const ARGUMENTS& args);
    
    CARTESIAN_MATRIX_2<complex<double>> calculate(int n);
    
    STRESS_FOURIER_COMPONENTS& addTimestep(const SHEARED_SLITPORE_SYSTEM& sys);
    
    //getter
    int getNumberOfTimesteps() const;
    vector<CARTESIAN_MATRIX> getStressList() const;
    double getPeriod() const;
    double getDt() const;
    
    //setter
    STRESS_FOURIER_COMPONENTS& setNumberOfTimesteps(int numberOfTimesteps);
    STRESS_FOURIER_COMPONENTS& setStressList(vector<CARTESIAN_MATRIX> stress);
    STRESS_FOURIER_COMPONENTS& setPeriod(double period);
    STRESS_FOURIER_COMPONENTS& setDt(double dt);
    
    //file-handling
    STRESS_FOURIER_COMPONENTS& readStressFromFile(string filename);
    
    //outstream handling
    friend ostream& operator<<(ostream& os, const STRESS_FOURIER_COMPONENTS& fc);
};


#endif //SHEAREDSLITPOREBD_STRESS_FOURIER_COMPONENTS_H
