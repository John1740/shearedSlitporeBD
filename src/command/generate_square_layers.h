#ifndef GENERATE_SQUARE_LAYERS_H
#define GENERATE_SQUARE_LAYERS_H

#include "../interfaces/command.h"
#include "../systems/confined_brownian_particles.h"

class GENERATE_SQUARE_LAYERS:public COMMAND<CONFINED_BROWNIAN_PARTICLES>
{
   bool SPECIES_TOOGLE;
    
   vector<CHARGED_PARTICLE> particleList;

   int numberOfLayers;
   int numberOfRows;
   int numberOfAdditionalRows;

   SLIT_PORE_BOX simBox;
   double dx,dy,dz,dxAdd,dyAdd;
   double zMin;

   void setLatticePeriodicity();

   void addLayer ( int layerIndex );
   void addIncommensurableLayer ( int layerIndex );

public:
   GENERATE_SQUARE_LAYERS();
   void setNumberOfLayersRowsAdditionalRows ( int numberOfLayersIn, int numberOfRowsIn, int numberOfAdditionalRowsIn );

   void doForSystem ( CONFINED_BROWNIAN_PARTICLES& sysIn );
};

#endif // GENERATE_SQUARE_LAYERS_H
