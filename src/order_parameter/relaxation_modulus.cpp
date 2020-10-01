//
// Created by mhuels on 6/12/20.
//

#include "relaxation_modulus.h"
#include <boost/format.hpp>

namespace b = boost;

RELAXATION_MODULUS::RELAXATION_MODULUS(){
    reset();
}

RELAXATION_MODULUS::RELAXATION_MODULUS(SHEARED_SLITPORE_SYSTEM& sys){
    reset();
    dt = sys.getTimeStepSize();
}

RELAXATION_MODULUS& RELAXATION_MODULUS::reset(){
    timestep.clear();
    G.clear();
    shearRate.clear();
    return *this;
}

RELAXATION_MODULUS& RELAXATION_MODULUS::calculateNext(SHEARED_SLITPORE_SYSTEM& sys){
    double GNew, stressNew;
    timestep.push_back(sys.getTimestep() - 1);
    shearRate.push_back(sys.getCurrentShearRate());
    stressNew = sys.getMeanStress().xz;
    stress.push_back(stressNew);
    if(G.size() == 0){
        GNew = sys.getMeanStress().xz / dt / shearRate[0];
    }
    else{
        //problem if shearRate[0] = 0
        GNew = stressNew / dt / shearRate[0];
        //loop
//        GNew -=
    }
    return *this;
}

vector<double> RELAXATION_MODULUS::getShearRates() const{
    return shearRate;
}

vector<double> RELAXATION_MODULUS::getG() const{
    return G;
}

vector<long> RELAXATION_MODULUS::getTimesteps() const{
    return timestep;
}

vector<double> RELAXATION_MODULUS::getStress() const{
    return stress;
}

double RELAXATION_MODULUS::getDt() const{
    return dt;
}

RELAXATION_MODULUS& RELAXATION_MODULUS::setDt(double dt){
    this->dt = dt;
    return *this;
}

ostream& operator<<(ostream& os, const RELAXATION_MODULUS& relaxationModulus){
//    os << "#r: radius [diameter]" << endl;
//    os << "#g(r): in-plane radial pair correlation function [1/diameter]" << endl;
//    os << "#" << b::format("%7s") % "r";
//    os << "\t" << b::format("%8s") % "g(r)";
//    os << "\n";

    //data
    vector<double> G = relaxationModulus.getG();
    vector<double> shearRate = relaxationModulus.getShearRates();
    vector<long> timestep = relaxationModulus.getTimesteps();
    vector<double> stress = relaxationModulus.getStress();
    for(int i = 0; i < G.size(); i++){
        os << b::format("% 2.5f") % timestep[i];
        os << "\t" << b::format("% 2.5f") % shearRate[i];
        os << "\t" << b::format("% 2.5f") % stress[i];
        os << "\t" << b::format("% 2.5f") % G[i];
        os << "\n";
    }
    return os;
}
