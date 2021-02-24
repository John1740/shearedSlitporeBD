//
// Created by mhuels on 6/15/20.
//

#ifndef SHEAREDSLITPOREBD_STRESS_FOURIER_COMPONENTS_H
#define SHEAREDSLITPOREBD_STRESS_FOURIER_COMPONENTS_H

#include "../argument_parser/arguments.h"
#include "../struct/cartesian_m.h"
#include "../systems/sheared_slitpore_system.h"
#include <vector>
#include <complex>

class STRESS_FOURIER_COMPONENTS{
private:
    long numberOfTimesteps;
    vector<REAL_M> stress;
    double period;
    double amplitude;
    double dt;

public:
    STRESS_FOURIER_COMPONENTS();
    STRESS_FOURIER_COMPONENTS(const ARGUMENTS& args);
    STRESS_FOURIER_COMPONENTS(string filename);

    STRESS_FOURIER_COMPONENTS& setup(const ARGUMENTS& args);

    COMPLEX_M calculate(int n);
    double calculateStorageModulus();
    double calculateLossModulus();
    double calculateStorageModulusOld();
    double calculateLossModulusOld();

    STRESS_FOURIER_COMPONENTS& addTimestep(const SHEARED_SLITPORE_SYSTEM& sys);

    //getter
    int getNumberOfTimesteps() const;
    vector<REAL_M> getStressList() const;
    double getPeriod() const;
    double getDt() const;

    //setter
    STRESS_FOURIER_COMPONENTS& setNumberOfTimesteps(int numberOfTimesteps);
    STRESS_FOURIER_COMPONENTS& setStressList(vector<REAL_M> stress);
    STRESS_FOURIER_COMPONENTS& setPeriod(double period);
    STRESS_FOURIER_COMPONENTS& setDt(double dt);

    //file-handling
    STRESS_FOURIER_COMPONENTS& readStressFromFile(string filename);

    //outstream handling
    friend ostream& operator<<(ostream& os, const STRESS_FOURIER_COMPONENTS& fc);
};

#endif //SHEAREDSLITPOREBD_STRESS_FOURIER_COMPONENTS_H
