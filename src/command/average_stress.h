#ifndef AVERAGE_STRESS_H
#define AVERAGE_STRESS_H

#include "../interfaces/command.h"
#include "../systems/sheared_slitpore_system.h"
#include "../struct/cartesian_m.h"

class AVERAGE_STRESS: public COMMAND<SHEARED_SLITPORE_SYSTEM>{
private:
    REAL_M stress;
    int count;

public:
    AVERAGE_STRESS();
    void reset();

    void doForSystem(SHEARED_SLITPORE_SYSTEM& sysIn);

    REAL_M getStress();
};

#endif // AVERAGE_STRESS_H
