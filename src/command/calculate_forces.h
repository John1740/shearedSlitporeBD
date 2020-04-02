#ifndef CALCULATE_FORCES_H
#define CALCULATE_FORCES_H

#include "../interfaces/system_interface.h"

class CALCULATE_FORCES
{

   int numberOfBoxes;
   int gridSize;
   int boxIndex;
   vector<int> neighborMap;
   vector<int> firstParticleIndexInBox, nextParticleIndexInBoxOfParticleIndex;

   vector<CARTESIAN_COORDINATE> boxPositions;
   BOX_GEOMETRY* simBox;    //should be initialized in constructor

   unsigned int getBoxIndexFromGridIndices(int i, int j );
   int getBoxIndexForParticleIndex(int particleIndex );
   int getGridIndexXForParticleIndex(int particleIndex );
   int getGridIndexYForParticleIndex(int particleIndex );

   void initializeContainer();
   void initializeParticleIndexLists(SYSTEM_INTERFACE& sysIn );
   void calculateForce(SYSTEM_INTERFACE& sysIn );
    
public:
    CALCULATE_FORCES();
    
    void doForSystem(SYSTEM_INTERFACE& sysIn );
};

#endif // CALCULATE_FORCES_H
