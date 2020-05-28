#ifndef CONFINED_BROWNIAN_PARTICLES_H
#define CONFINED_BROWNIAN_PARTICLES_H

#include "../global.h"
#include <fstream>

#include "../boxmueller.h"
#include "../interfaces/system_interface.h"

#include "../struct/cartesian_coordinate.h"
#include "../struct/cartesian_matrix.h"
#include "../struct/particle.h"
#include "../struct/slit_pore_box.h"

#include "../command/calculate_forces.h"

#include "../printer/printer.h"
#include "experimental/filesystem"

#include "../defaults.h"
#include "../argument_parser/arguments.h"
#include "../struct/configuration.h"

namespace fs = experimental::filesystem;

class CONFINED_BROWNIAN_PARTICLES: public SYSTEM_INTERFACE{

    friend class CALCULATE_FORCES;
    friend class GENERATE_SQUARE_LAYERS;
    friend class PAIR_CORRELATION;

private:

protected:
    CALCULATE_FORCES calculateForces;
    
//    CONFIGURATION cfg;
    
    vector<CHARGED_PARTICLE> particle, previousParticle;
    vector<CARTESIAN_COORDINATE> force;
    SLIT_PORE_BOX simBox;
    
    string configurationIn = CONFIGURATION_IN;

    int numberOfParticles = NUMBER_OF_PARTICLES;
    
    double density = DENSITY;
    double dWall = D_WALL;

    long timestep = 0;
    double dt = DELTA_T;
    double T = TEMPERATURE;
    double D0 = DIFFUSION_CONSTANT;

    // Allow Children to modify simulation box
    SLIT_PORE_BOX* simulationBox();

    // Solve Equation of Motion
    virtual void equationOfMotion();
    virtual void calculateForce();
    virtual void reset();
    virtual void calculateInteractionForce(int i, int j);
    virtual void calculateExternalForce(int i);
    virtual CARTESIAN_COORDINATE getRandomDisplacement();

    // Non-Public Set-Functions
    virtual void setParticleList(vector<CHARGED_PARTICLE> particleListIn);
    virtual void setPositionInBox();

public:
    CONFINED_BROWNIAN_PARTICLES();
    CONFINED_BROWNIAN_PARTICLES(const ARGUMENTS& args);
    ~CONFINED_BROWNIAN_PARTICLES();

    virtual void simulateForSteps(int maxSteps);

    // Two-Body and External Forces
    virtual CARTESIAN_COORDINATE forceFromParticleOnParticle(CHARGED_PARTICLE& particle1, CHARGED_PARTICLE& particle2);
    virtual CARTESIAN_COORDINATE forceOnParticleFromExternalFields(CHARGED_PARTICLE& particle);
    virtual double energyFromParticleOnParticle(CHARGED_PARTICLE& particle1, CHARGED_PARTICLE& particle2);
    virtual double energyOfParticleFromExternalFields(CHARGED_PARTICLE& particle);

    // setter
    void setTimestep(long timestepIn);
    virtual void setTimeStepSize(double timeStepSizeIn, bool verbose=false);

    // getter
    long getTimestep() const;
    virtual double getTimeStepSize();
    virtual double getInteractionLengthScale();
    virtual vector<CARTESIAN_COORDINATE> getPositionList();
    virtual vector<CHARGED_PARTICLE> getParticleList();
    virtual vector<CHARGED_PARTICLE> getPreviousParticleList();
    virtual SLIT_PORE_BOX getSimulationBox();
    
    vector<CARTESIAN_COORDINATE> getVelocities();
    CARTESIAN_COORDINATE getMeanVelocity();
    vector<CARTESIAN_COORDINATE> getMeanLayerVelocities();

    // Initial configuration generation
//    virtual void generateInitialConfiguration();
    virtual void setInitialConfigurationForLayersWithSides();
    
    // File-Handling
    virtual void readConfigurationFromFileOld(string filename, bool createIfMissing= false, bool verbose= true);
    virtual void writeConfigurationToFileOld(string filename, bool verbose= true);
};

#endif // BROWNIAN_PARTICLES_H
