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

#include "../defaults.h"
#include "../argument_parser/arguments.h"

class CONFINED_BROWNIAN_PARTICLES: public SYSTEM_INTERFACE{

    friend class CALCULATE_FORCES;
    friend class GENERATE_SQUARE_LAYERS;

private:

protected:
    CALCULATE_FORCES calculateForces;

    vector<CHARGED_PARTICLE> particle, previousParticle;
    vector<CARTESIAN_COORDINATE> force;
    SLIT_PORE_BOX simBox;

    int numberOfParticles = NUMBER_OF_PARTICLES;

    double dt = DELTA_T;
    double T = TEMPERATURE;
    double D0 = DIFFUSION_CONSTANT;

    string configurationDir = "brownian";

//     Allow Children to modify simulation box
    SLIT_PORE_BOX* simulationBox();

//     Solve Equation of Motion
    virtual void equationOfMotion();
    virtual void calculateForce();
    virtual void reset();
    virtual void calculateInteractionForce(int i, int j);
    virtual void calculateExternalForce(int i);
    virtual CARTESIAN_COORDINATE getRandomDisplacement();

//     Non-Public Set-Functions
    virtual void setParticleList(vector<CHARGED_PARTICLE> particleListIn);
    virtual void setPositionInBox();

public:
    CONFINED_BROWNIAN_PARTICLES();
    CONFINED_BROWNIAN_PARTICLES(const ARGUMENTS& args);

    virtual void simulateForSteps(int maxSteps);

//     Two-Body and External Forces
    virtual CARTESIAN_COORDINATE forceFromParticleOnParticle(CHARGED_PARTICLE& particle1, CHARGED_PARTICLE& particle2);
    virtual CARTESIAN_COORDINATE forceOnParticleFromExternalFields(CHARGED_PARTICLE& particle);
    virtual double energyFromParticleOnParticle(CHARGED_PARTICLE& particle1, CHARGED_PARTICLE& particle2);
    virtual double energyOfParticleFromExternalFields(CHARGED_PARTICLE& particle);

//     Set-Functions
    virtual void setTimeStepSize(double timeStepSizeIn);

//     Get-Functions
    virtual double getTimeStepSize();
    virtual double getInteractionLengthScale();
    virtual vector<CARTESIAN_COORDINATE> getPositionList();
    virtual vector<CHARGED_PARTICLE> getParticleList();
    virtual vector<CHARGED_PARTICLE> getPreviousParticleList();
    virtual SLIT_PORE_BOX getSimulationBox();
    vector<CARTESIAN_COORDINATE> getVelocities();
    CARTESIAN_COORDINATE getMeanVelocity();
    vector<CARTESIAN_COORDINATE> getMeanLayerVelocities();

//     File-Handling
    virtual void readConfigurationFromFile(string str);
    virtual void writeConfigurationToFile(string filename, bool verbose=true);

    virtual string app_identifier(string str);

};

#endif // BROWNIAN_PARTICLES_H
