#ifndef DLVO_INTERACTION_H
#define DLVO_INTERACTION_H

#include "../interfaces/force_template_interfaces.h"
#include "lennard_jones_interaction.h"
#include "../struct/charged_particle.h"
#include "../interfaces/box_geometry.h"

class DLVO_SOFTSPHERE_INTERACTION: public TWO_BODY_CONSERVATIVE_FORCE<CHARGED_PARTICLE>
{

   void setParametersForAllChargeCompositions();
   void setKappa();

public:
   double distance;
   CARTESIAN_COORDINATE posDifference;
   int id;

   double energyCutOffThreshold;
   double forceCutOffThreshold;

   double rcDelta;

   double kappa;
   vector<int> charge;
   vector<double> diameter, rho;
   vector<double> cutOffRadius, shift1, shift2, shift3, interactionStrength, diameterSpecies;

   double ssInteractionStrength;


   DLVO_SOFTSPHERE_INTERACTION();
   void setInteractionParameters ( vector<int> chargeIn,vector<double> diameterIN , vector<double> rhoIn );
   void calculateCutOffThreshold();

   CARTESIAN_COORDINATE forceOnParticleFromParticle ( CHARGED_PARTICLE& particle1, CHARGED_PARTICLE& particle2, BOX_GEOMETRY& simBox );
   double energyOnParticleFromParticle ( CHARGED_PARTICLE& particle1, CHARGED_PARTICLE& particle2, BOX_GEOMETRY& simBox );

//FAST:
   bool isInRangeSetDistanceAndId ( CHARGED_PARTICLE& particle1, CHARGED_PARTICLE& particle2, BOX_GEOMETRY& simBox );
   CARTESIAN_COORDINATE fastForce();


   double getInteractionStrength ( int Z1, double diameter1, int Z2, double diameter2 );
   double getCutOffRadius ( int index );
   double getMaxCutOffRadius();

   double forceOnParticlePerDirection ( double r, int index );
   double energyOnParticles ( double r, int index );

   void setRcDelta ( double length );
};

#endif // DLVO_INTERACTION_H
