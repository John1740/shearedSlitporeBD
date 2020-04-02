#include "generate_square_layers.h"

GENERATE_SQUARE_LAYERS::GENERATE_SQUARE_LAYERS(){
   numberOfLayers = 2;
   numberOfRows = 23;
   numberOfAdditionalRows = 0;
   
   SPECIES_TOOGLE = false;
   
}

void GENERATE_SQUARE_LAYERS::setNumberOfLayersRowsAdditionalRows(int numberOfLayersIn, int numberOfRowsIn, int numberOfAdditionalRowsIn ){
   numberOfLayers = numberOfLayersIn;
   numberOfRows = numberOfRowsIn;
   numberOfAdditionalRows = numberOfAdditionalRowsIn;
}

void GENERATE_SQUARE_LAYERS::doForSystem(CONFINED_BROWNIAN_PARTICLES &sysIn ){
   simBox = sysIn.getSimulationBox();

   setLatticePeriodicity();
   particleList.clear();

   for(int i = 0; i < numberOfLayers - 1; ++i )
      addLayer(i );

   addIncommensurableLayer(numberOfLayers - 1 );

   sysIn.setParticleList(particleList );
}

void GENERATE_SQUARE_LAYERS::setLatticePeriodicity(){
   zMin = -0.2 * simBox.getDimensions().z;
   dx = simBox.getDimensions().x / numberOfRows;

   dy = simBox.getDimensions().y / numberOfRows;
   dz = (0.4 * simBox.getDimensions().z ) / (numberOfLayers - 1 ); //?

   dxAdd = simBox.getDimensions().x / (numberOfRows + numberOfAdditionalRows );
   dyAdd = dxAdd;
}


void GENERATE_SQUARE_LAYERS::addLayer(int layerIndex ){
   for(int j = 0; j < numberOfRows; ++j ) //j=index in y-direction{
      for(int k = 0; k < numberOfRows; ++k ) //k=index in x-direction{
         CHARGED_PARTICLE newParticle;
         newParticle.position = CARTESIAN_COORDINATE(dx * k + layerIndex * dx / 2, //displaced by dx/2 from lower layer
                                dy * j + layerIndex * dy / 2, //displaced by dy/2 from lower layer
                                zMin + layerIndex * dz );
         newParticle.species = 0;
         particleList.push_back(newParticle );
      }
   }
}

void GENERATE_SQUARE_LAYERS::addIncommensurableLayer(int layerIndex ){
   for(int j = 0; j < numberOfRows + numberOfAdditionalRows; ++j ){
      for(int k = 0; k < numberOfRows + numberOfAdditionalRows; ++k ){
         CHARGED_PARTICLE newParticle;
         newParticle.position = CARTESIAN_COORDINATE(dxAdd * k + layerIndex * dxAdd / 2,
                                dyAdd * j + layerIndex * dyAdd / 2,
                                zMin + layerIndex * dz );
	 if(SPECIES_TOOGLE)
	    newParticle.species = 1;
	 else
	    newParticle.species = 0;
         particleList.push_back(newParticle );
      }
   }
}



