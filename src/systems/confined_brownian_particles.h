#ifndef BROWNIAN_CHARGED_PARTICLES_H
#define BROWNIAN_CHARGED_PARTICLES_H

#include "../global.h"
#include <fstream>

#include "../boxmueller.h"
#include "../interfaces/system_interface.h"

#include "../struct/cartesian_coordinate.h"
#include "../struct/cartesian_matrix.h"
#include "../struct/particle.h"
#include "../struct/slit_pore_box.h"

#include "../command/calculate_forces.h"

#include "../tools/printer.h"

class CONFINED_BROWNIAN_PARTICLES: public SYSTEM_INTERFACE
{

    friend class CALCULATE_FORCES;
    friend class GENERATE_SQUARE_LAYERS;

private:

protected:    
    CALCULATE_FORCES calculateForces;

    vector<CHARGED_PARTICLE> particle;
    vector<CARTESIAN_COORDINATE> force;
    SLIT_PORE_BOX simBox;
    double dt;
    double D0,T;

    string configurationDir;
    
//     Internal File-Handling
    virtual void readFromString ( string str );
    virtual void printParticlesOfSystem ( string str );
    virtual void printInitilization();
    
//     Allow Children to modify simulation box
    SLIT_PORE_BOX* simulationBox();

//     Solve Equation of Motion
    virtual void equationOfMotion();
    virtual void calculateForce();
    virtual void reset();
    virtual void calculateInteractionForce ( int i, int j );
    virtual void calculateExternalForce ( int i );
    virtual CARTESIAN_COORDINATE getRandomForce();
    
//     Non-Public Set-Functions
    virtual void setParticleList( vector<CHARGED_PARTICLE> particleListIn );
    virtual void setPositionInBox();


public:
    CONFINED_BROWNIAN_PARTICLES();
    virtual void simulateForSteps ( int maxSteps );

//     Two-Body and External Forces
    virtual CARTESIAN_COORDINATE forceFromParticleOnParticle ( CHARGED_PARTICLE& particle1, CHARGED_PARTICLE& particle2 );
    virtual CARTESIAN_COORDINATE forceOnParticleFromExternalFields ( CHARGED_PARTICLE& particle );
    virtual double energyFromParticleOnParticle ( CHARGED_PARTICLE& particle1, CHARGED_PARTICLE& particle2 );
    virtual double energyOfParticleFromExternalFields ( CHARGED_PARTICLE& particle );

//     Set-Functions
    virtual void setTimeStepSize( double timeStepSizeIn );
    
//     Get-Functions
    virtual int getNumberOfParticles();
    virtual double getTimeStepSize();
    virtual double getInteractionLengthScale();
    virtual vector<CARTESIAN_COORDINATE> getPositionList();
    virtual vector<CHARGED_PARTICLE> getParticleList();
    virtual SLIT_PORE_BOX getSimulationBox();
    
//     File-Handling
    virtual void read ();
    virtual void read ( string str );
    virtual void printSystem();
    virtual void printSystem ( string str );
    
    virtual string app_identifier ( string str );

};

#endif // BROWNIAN_PARTICLES_H
