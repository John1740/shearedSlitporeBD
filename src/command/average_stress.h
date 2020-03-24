#ifndef AVERAGE_STRESS_H
#define AVERAGE_STRESS_H

#include "../interfaces/command.h"
#include "../systems/sheared_slitpore_system.h"

#include "../struct/cartesian_matrix.h"

class AVERAGE_STRESS:public COMMAND<SHEARED_SLITPORE_SYSTEM>
{
   CARTESIAN_MATRIX stress;
   int count;

public:
   AVERAGE_STRESS();
   void reset();

   void doForSystem ( SHEARED_SLITPORE_SYSTEM& sysIn );

   CARTESIAN_MATRIX getStress();
};

#endif // AVERAGE_STRESS_H
