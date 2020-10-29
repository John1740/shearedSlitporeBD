#include "average_stress.h"

AVERAGE_STRESS::AVERAGE_STRESS(){
    reset();
}

void AVERAGE_STRESS::reset(){
    stress = REAL_M(0.);
    count = 0;
}

void AVERAGE_STRESS::doForSystem(SHEARED_SLITPORE_SYSTEM& sysIn){
    stress += sysIn.getMeanStress();
    ++count;
}

REAL_M AVERAGE_STRESS::getStress(){
    return stress / count;
}
