#ifndef SHEARED_SLITPORE_SYSTEM_H
#define SHEARED_SLITPORE_SYSTEM_H

#include "../systems/confined_brownian_particles.h"

#include "../interactions/dlvo_softsphere_interaction.h"
#include "../external/soft_wall_force.h"
#include "../external/shear_force.h"

#include "../argument_parser/argparse.h"

#include "../command/generate_square_layers.h"
#include "../defaults.h"

class SHEARED_SLITPORE_SYSTEM: public CONFINED_BROWNIAN_PARTICLES{
private:

protected:
    DLVO_SOFTSPHERE_INTERACTION dlvo;
    SOFT_WALL_FORCE swf;
    SHEAR_FORCE shearForce;

    string configurationIn = CONFIGURATION_IN;
    double density = DENSITY;
    double dWall = D_WALL;

    vector<CARTESIAN_COORDINATE> randomForces, shearFlowForces;
    vector<double> energy;
    vector<CARTESIAN_MATRIX> stressPerParticle;

    virtual double getInteractionLengthScale();

    virtual void reset();

    virtual void readConfigurationFromString(string str);

    virtual CARTESIAN_COORDINATE getShearForce(int index);

    virtual void equationOfMotion();
    virtual void calculateInteractionForce(int i, int j);
    virtual void calculateExternalForce(int i);

    virtual void setInitialConfigurationForLayersWithSides(int numberOfParticlesIn);
    virtual void setParticleList(vector<CHARGED_PARTICLE> particleListIn);

    virtual void addConfigurationalStress(CARTESIAN_COORDINATE forceIn, int i, int j);
    virtual void addExternalStress(const CARTESIAN_COORDINATE& forceIn, int i);

public:
    SHEARED_SLITPORE_SYSTEM();
    SHEARED_SLITPORE_SYSTEM(const ARGUMENTS& args);

    bool printStress = PRINT_STRESS;
    bool printEnergy = PRINT_ENERGY;

    virtual void prepareSystem();
//    virtual void readEnsembleSystem(int ensembleIndex);
    virtual void printSystemWithEnsembleIndex(int ensembleIndex);

    virtual CARTESIAN_COORDINATE forceFromParticleOnParticle(CHARGED_PARTICLE& particle1, CHARGED_PARTICLE& particle2);
    virtual CARTESIAN_COORDINATE forceOnParticleFromExternalFields(CHARGED_PARTICLE& particle);
    virtual double energyFromParticleOnParticle(CHARGED_PARTICLE& particle1, CHARGED_PARTICLE& particle2);
    virtual double energyOfParticleFromExternalFields(CHARGED_PARTICLE& particle);

    virtual string app_identifier(string str);
    virtual string app_incomplete_identifier(string str);
    virtual void convertPositionToBoxPosition();

    //setter functions

    //getter functions
    virtual vector<CARTESIAN_MATRIX> getStressPerParticle();
    virtual CARTESIAN_MATRIX getMeanStress();

    vector<double> getEnergyPerParticle();
};

#endif // SHEARED_SLITPORE_SYSTEM_H

