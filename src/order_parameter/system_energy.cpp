//
// Created by
//

#include "system_energy.h"

namespace b = boost;

SYSTEM_ENERGY::SYSTEM_ENERGY(){
}

SYSTEM_ENERGY::SYSTEM_ENERGY(SHEARED_SLITPORE_SYSTEM& sys){
    setup(sys);
}

SYSTEM_ENERGY&
SYSTEM_ENERGY::setup(SHEARED_SLITPORE_SYSTEM& sys){
    // sets up parameters needed for calculation
    int len = sys.energy.size();
    potentialEnergy=0;
    for(int i = 0; i < len; i++){
        potentialEnergy+=sys.energy[i];
    }
    return *this;
}

SYSTEM_ENERGY& SYSTEM_ENERGY::print(string filename, bool overwrite, string header){

    PRINTER printer(filename);
    if(overwrite){
        printer.reset();
    }
    if(header.size() > 0){
        printer << string(3, printer.getComment()) << header << endl;
    }
    printer << *this;
    return *this;
}

ostream& operator<<(ostream& os, const SYSTEM_ENERGY& sysEnergy){
    os << "# Potential Energy: " <<endl;
    os << sysEnergy.potentialEnergy<<endl;

    return os;

} 
