
#ifndef SYSTEM_ENERGY_H
#define SYSTEM_ENERGY_H

#include "../systems/sheared_slitpore_system.h"

class SYSTEM_ENERGY{
    // Observable to calculate the particle density over z. Input particle positions via SHEARED_SLITPORE_SYSTEM
    // class and optional dz. positions are printed via << operator to "zDensity.out"
private:
double potentialEnergy;

public:
    SYSTEM_ENERGY();
    SYSTEM_ENERGY(SHEARED_SLITPORE_SYSTEM& sys);
    SYSTEM_ENERGY& setup(SHEARED_SLITPORE_SYSTEM& sys);


    SYSTEM_ENERGY& print(string filename, bool overwrite=false, string header="");
    friend ostream& operator<<(ostream& os, const  SYSTEM_ENERGY& sysEnergy);

};

#endif //SHEAREDSLITPOREBD_SYSTEM_ENERGY_H