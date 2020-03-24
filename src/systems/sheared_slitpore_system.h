#ifndef SHEARED_SLITPORE_SYSTEM_H
#define SHEARED_SLITPORE_SYSTEM_H

#include "../systems/confined_brownian_particles.h"

#include "../interactions/dlvo_softsphere_interaction.h"
#include "../external/soft_wall_force.h"
#include "../external/shear_force.h"

#include "../parameters/sheared_slitpore_parameters.h"

#include "../command/generate_square_layers.h"

class SHEARED_SLITPORE_SYSTEM : public  CONFINED_BROWNIAN_PARTICLES
{
   
    
private:
    
protected:
    DLVO_SOFTSPHERE_INTERACTION dlvo;
    SOFT_WALL_FORCE swf;
    SHEAR_FORCE shearForce;

    string sysIdentifierString;

    double density, diameter;
    int charge;
    
    vector<CARTESIAN_COORDINATE> randomForces, shearFlowForces;
    vector<double> energy;
    
    vector<CARTESIAN_MATRIX> stressPerParticle;
//     vector<double> absDistancePerParticle;
//     vector<double> absForcePerParticle;
//     vector<double> validCountsPerParticle;

    virtual void setSoftWallInteraction ( double softWallStrengthIn );
    virtual void setDlvoSSInteraction ( double ssInteractionStrengthIn );
    virtual double getInteractionLengthScale();

    virtual void reset();
    virtual void setNumberOfParticles ( int numberOfParticlesIn );

    virtual void readFromString ( string str );

    virtual CARTESIAN_COORDINATE getShearForce ( int index );

    virtual void equationOfMotion();
    virtual void calculateInteractionForce ( int i, int j );
    virtual void calculateExternalForce ( int i );
    
    virtual void setInitialConfigurationForLayersWithSides( int numberOfParticlesIn );
    virtual void setParticleList( vector<CHARGED_PARTICLE> particleListIn );
    
    virtual void addConfigurationalStress( CARTESIAN_COORDINATE forceIn, int i, int j );
    virtual void addExternalStress( CARTESIAN_COORDINATE forceIn, int i );

public:
    bool STRESS;
    bool ENERGY;
    
    SHEARED_SLITPORE_SYSTEM();
    SHEARED_SLITPORE_SYSTEM ( SHEARED_SLITPORE_PARAMETERS& sPin );
    virtual void setSystemParameters ( SHEARED_SLITPORE_PARAMETERS& sPin );
    virtual void readEnsembleSystem( int ensembleIndex );
    virtual void printSystemWithEnsembleIndex( int ensembleIndex );
    
    virtual string getIdentifierString();
    
    virtual CARTESIAN_COORDINATE forceFromParticleOnParticle ( CHARGED_PARTICLE& particle1, CHARGED_PARTICLE& particle2 );
    virtual CARTESIAN_COORDINATE forceOnParticleFromExternalFields ( CHARGED_PARTICLE& particle );
    virtual double energyFromParticleOnParticle ( CHARGED_PARTICLE& particle1, CHARGED_PARTICLE& particle2 );
    virtual double energyOfParticleFromExternalFields ( CHARGED_PARTICLE& particle );

    virtual void setShearRate ( double shearRateIn );
    virtual double getShearRate();
    
    virtual vector<CARTESIAN_MATRIX> getStressPerParticle();
    virtual CARTESIAN_MATRIX getMeanStress();
    
    vector<double> getEnergyPerParticle();

    virtual string app_identifier ( string str );
    virtual string app_incomplete_identifier ( string str );
    virtual void convertPositionToBoxPosition();

};

#endif // SHEARED_SLITPORE_SYSTEM_H

