#include "dlvo_softsphere_interaction.h"

DLVO_SOFTSPHERE_INTERACTION::DLVO_SOFTSPHERE_INTERACTION()
{
   ssInteractionStrength = 1.;
   distance = 1.;
   posDifference = CARTESIAN_COORDINATE();

   rcDelta = 10. / 4000.;

   cutOffRadius.clear();
   shift1.clear();
   shift2.clear();
   shift3.clear();
   interactionStrength.clear();
   diameter.clear();
   charge.clear();
   rho.clear();

   calculateCutOffThreshold();
}

void DLVO_SOFTSPHERE_INTERACTION::calculateCutOffThreshold()
{
   LENNARD_JONES_INTERACTION lji;
   energyCutOffThreshold = abs( lji.energyOnParticles( 3. ) );
   forceCutOffThreshold = abs( lji.forceOnParticlePerDirection( 3. ) / 3. );

}

CARTESIAN_COORDINATE DLVO_SOFTSPHERE_INTERACTION::forceOnParticleFromParticle( CHARGED_PARTICLE &particle1, CHARGED_PARTICLE &particle2, BOX_GEOMETRY& simBox )
{
   id = particle1.species + particle2.species;
   posDifference = particle1.boxPosition - particle2.boxPosition;
   posDifference = simBox.convertToBoxPosition( posDifference );
   distance = posDifference.getAbs();

   if( distance <= cutOffRadius[id] )
   {
      posDifference *= ( forceOnParticlePerDirection( distance, id ) - shift1[id] ) / distance;
      return posDifference;
   }
   else
   {
      CARTESIAN_COORDINATE nullCC( 0. );
      return nullCC;
   }

}

bool DLVO_SOFTSPHERE_INTERACTION::isInRangeSetDistanceAndId( CHARGED_PARTICLE &particle1, CHARGED_PARTICLE &particle2, BOX_GEOMETRY& simBox )
{
   bool isInRange = false;

   id = particle1.species + particle2.species;
   posDifference = particle1.boxPosition - particle2.boxPosition;
   posDifference = simBox.convertToBoxPosition( posDifference );
   distance = posDifference.getAbs();

   if( distance <= cutOffRadius[id] )
   {
      isInRange = true;
   }

   return isInRange;
}

CARTESIAN_COORDINATE DLVO_SOFTSPHERE_INTERACTION::fastForce()
{
   return posDifference * ( forceOnParticlePerDirection( distance, id ) - shift1[id] ) / distance;
}


double DLVO_SOFTSPHERE_INTERACTION::energyOnParticleFromParticle( CHARGED_PARTICLE &particle1, CHARGED_PARTICLE &particle2, BOX_GEOMETRY& simBox )
{
   id = particle1.species + particle2.species;
   posDifference = particle1.boxPosition - particle2.boxPosition;
   distance = simBox.convertToBoxPosition( posDifference ).getAbs();

   if( distance <= cutOffRadius[id] )
   {
      return energyOnParticles( distance, id ) + distance * shift1[id] - ( shift2[id] + shift3[id] );
   }
   else
   {
      return 0.;
   }
}

void DLVO_SOFTSPHERE_INTERACTION::setInteractionParameters( std::vector< int > chargeIn, std::vector< double > diameterIn, std::vector< double > rhoIn )
{
   if( chargeIn.size() > 2 || diameterIn.size() > 2 || rhoIn.size() > 2 )
       cout << "chargeIn.size(): " << chargeIn.size() << "\t" << "diameterIn.size(): " << diameterIn.size() << "\t" << "rhoIn.size(): " << rhoIn.size() << endl;
   
   charge = chargeIn;
   diameter = diameterIn;
   rho = rhoIn;

   setKappa();
   setParametersForAllChargeCompositions();
}

void DLVO_SOFTSPHERE_INTERACTION::setKappa()
{
   double chargeConcentration = 0.;

   for( int i = 0; i < charge.size(); ++i )
   {
      chargeConcentration += charge[i] * rho[i];
   }

   kappa = pow( 0.07308561551392402 + 0.34524730769230782857 * chargeConcentration, 0.5 );
}

void DLVO_SOFTSPHERE_INTERACTION::setParametersForAllChargeCompositions()
{
   interactionStrength.clear();
   cutOffRadius.clear();
   diameterSpecies.clear();
   shift1.clear();
   shift2.clear();
   shift3.clear();

   for( int i = 0; i < charge.size(); ++i )
   {
      for( int j = i; j < charge.size(); ++j )
      {
         interactionStrength.push_back( getInteractionStrength( charge[i], diameter[i], charge[j], diameter[j] ) );
         diameterSpecies.push_back( 0.5 * ( diameter[i] + diameter[j] ) );
         int currentID = i + j;
         cutOffRadius.push_back( getCutOffRadius( currentID ) );
         shift1.push_back( forceOnParticlePerDirection( cutOffRadius[currentID], currentID ) );
         shift2.push_back( energyOnParticles( cutOffRadius[currentID], currentID ) );
         shift3.push_back( shift1[currentID]*cutOffRadius[currentID] );
      }
   }
}

double DLVO_SOFTSPHERE_INTERACTION::getInteractionStrength( int Z1, double diameter1, int Z2, double diameter2 )
{
   double alpha = 0.16575255001233970612;
   double Wp1 = Z1 * alpha * exp( 0.5 * kappa * diameter1 ) / ( 1 + 0.5 * kappa * diameter1 );
   double Wp2 = Z2 * alpha * exp( 0.5 * kappa * diameter2 ) / ( 1 + 0.5 * kappa * diameter2 );

   return Wp1 * Wp2;
}

double DLVO_SOFTSPHERE_INTERACTION::getCutOffRadius( int index )
{
   LENNARD_JONES_INTERACTION lji;
   lji.diameter = diameterSpecies[index];
   energyCutOffThreshold = abs( lji.energyOnParticles( 3. ) );
   forceCutOffThreshold = abs( lji.forceOnParticlePerDirection( 3. ) / 3. );


   double rc;

   for( int i = 0; i < 4000; ++i )
   {
      if( abs( energyOnParticles( i * rcDelta, index ) ) < energyCutOffThreshold && abs( forceOnParticlePerDirection( i * rcDelta, index ) / ( i * rcDelta ) ) < forceCutOffThreshold )
      {
         rc = i * rcDelta;
         break;
      }
   }
   
   return rc;
}

double DLVO_SOFTSPHERE_INTERACTION::energyOnParticles( double r, int index )
{
   return interactionStrength[index] * exp( -kappa * r ) / ( r ) + 4 * ssInteractionStrength * pow( diameterSpecies[index] / r, 12 ) ;
}

double DLVO_SOFTSPHERE_INTERACTION::forceOnParticlePerDirection( double r, int index )
{
   return ( interactionStrength[index] * exp( -kappa * r ) * ( kappa / r + 1. / ( r * r ) ) + 48 * ssInteractionStrength *  pow( diameterSpecies[index] / r, 13 ) / diameterSpecies[index] );
}

double DLVO_SOFTSPHERE_INTERACTION::getMaxCutOffRadius()
{
   double maxRC = 0.;

   for( int i = 0; i < cutOffRadius.size(); ++i )
   {
      if( cutOffRadius[i] > maxRC )
      {
         maxRC = cutOffRadius[i];
      }
   }

   return maxRC;
}

void DLVO_SOFTSPHERE_INTERACTION::setRcDelta( double length )
{
   rcDelta = length / 4000.;
}

