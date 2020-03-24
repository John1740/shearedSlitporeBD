#include "average_stress.h"

AVERAGE_STRESS::AVERAGE_STRESS()
{
   reset();
}

void AVERAGE_STRESS::reset()
{
   stress = CARTESIAN_MATRIX( 0. );
   count = 0;
}

void AVERAGE_STRESS::doForSystem( SHEARED_SLITPORE_SYSTEM &sysIn )
{
   stress += sysIn.getMeanStress();
   ++count;
}

CARTESIAN_MATRIX AVERAGE_STRESS::getStress()
{
   return stress / count;
}



