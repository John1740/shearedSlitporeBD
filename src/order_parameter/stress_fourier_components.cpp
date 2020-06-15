//
// Created by mhuels on 6/15/20.
//

#include "stress_fourier_components.h"

STRESS_FOURIER_COMPONENTS::STRESS_FOURIER_COMPONENTS(){
}

STRESS_FOURIER_COMPONENTS::STRESS_FOURIER_COMPONENTS(const ARGUMENTS& args){
    setup(args);
}

STRESS_FOURIER_COMPONENTS::STRESS_FOURIER_COMPONENTS(string filename){
    readStressFromFile(filename);
}

STRESS_FOURIER_COMPONENTS& STRESS_FOURIER_COMPONENTS::setup(const ARGUMENTS& args){
    numberOfTimesteps = args.totalNumberOfTimesteps / args.stressFourier;
    period = args.oscillationPeriod;
    dt = args.dt;
    stress.clear();
    return *this;
}

CARTESIAN_MATRIX_2<complex<double>> STRESS_FOURIER_COMPONENTS::calculate(int n){
    CARTESIAN_MATRIX_2<complex<double>> fc; //fc==fourier component
    complex<double> I(0, 1);
    //sometimes rounds falsely
    int timestepsPerPeriod = period / dt;
    if(stress.size() < numberOfTimesteps){
        cout << "Stress trajectory is not complete yet. Caution is adviced." << endl;
    }
    //only consider full cycles (remove uncompleted last cycle if there is one)
    int N = stress.size() / timestepsPerPeriod * timestepsPerPeriod;
    if(N == 0){
        cout << "Existing data is not large enough (" << stress.size() << "<" << timestepsPerPeriod << ") to compute a Fourier component!" << endl;
        return fc;
    }
    for(int t = 0; t < N; t++){
        double phase = n * 2 * M_PI * (t * dt) / period;
        complex<double> factor = exp(I * phase);
        fc += CARTESIAN_MATRIX_2<complex<double>>(stress[t]) * factor;
    }
    fc /= N;
    return fc;
}

STRESS_FOURIER_COMPONENTS& STRESS_FOURIER_COMPONENTS::addTimestep(const SHEARED_SLITPORE_SYSTEM& sys){
    CARTESIAN_MATRIX currentStress = sys.getMeanStress();
    stress.push_back(currentStress);
    return *this;
}

int STRESS_FOURIER_COMPONENTS::getNumberOfTimesteps() const{
    return numberOfTimesteps;
}

vector<CARTESIAN_MATRIX> STRESS_FOURIER_COMPONENTS::getStressList() const{
    return stress;
}

double STRESS_FOURIER_COMPONENTS::getPeriod() const{
    return period;
}

double STRESS_FOURIER_COMPONENTS::getDt() const{
    return dt;
}

STRESS_FOURIER_COMPONENTS& STRESS_FOURIER_COMPONENTS::setNumberOfTimesteps(int numberOfTimesteps){
    this->numberOfTimesteps = numberOfTimesteps;
    return *this;
}

STRESS_FOURIER_COMPONENTS& STRESS_FOURIER_COMPONENTS::setStressList(vector<CARTESIAN_MATRIX> stress){
    this->stress = stress;
    return *this;
}

STRESS_FOURIER_COMPONENTS& STRESS_FOURIER_COMPONENTS::setPeriod(double period){
    this->period = period;
    return *this;
}

STRESS_FOURIER_COMPONENTS& STRESS_FOURIER_COMPONENTS::setDt(double dt){
    this->dt = dt;
    return *this;
}

STRESS_FOURIER_COMPONENTS& STRESS_FOURIER_COMPONENTS::readStressFromFile(string filename){
    cout << "readStressFromFile() is not yet implemented!" << endl;
    return *this;
}

ostream& operator<<(ostream& os, const STRESS_FOURIER_COMPONENTS& fc){
    int timestepsPerPeriod = fc.period / fc.dt;
    int numberOfPeriods = fc.stress.size() / timestepsPerPeriod;
    int N = numberOfPeriods * timestepsPerPeriod;
    os << "STRESS_FOURIER_COMPONENTS(numberOfPeriods: " << numberOfPeriods << ")";
    return os;
}