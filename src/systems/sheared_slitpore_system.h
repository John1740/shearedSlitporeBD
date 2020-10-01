#ifndef SHEARED_SLITPORE_SYSTEM_H
#define SHEARED_SLITPORE_SYSTEM_H

#include "../systems/confined_brownian_particles.h"

#include "../interactions/dlvo_softsphere_interaction.h"
#include "../external/soft_wall_force.h"
#include "../external/shear_force.h"

#include "../argument_parser/argparse.h"

#include "../defaults.h"

class SHEARED_SLITPORE_SYSTEM: public CONFINED_BROWNIAN_PARTICLES{
private:

protected:
    DLVO_SOFTSPHERE_INTERACTION dlvo;
    SOFT_WALL_FORCE swf;
    SHEAR_FORCE shearForce;

    vector<REAL_C> randomForces, shearFlowForces;
    vector<double> energy;
    vector<REAL_M> stressPerParticle;

    double shearRateOffset = SHEAR_RATE;
    double shearRateAmplitude = AMPLITUDE;
    double oscillationPeriod = OSCILLATION_PERIOD;
    double phaseOffset = PHASE_OFFSET;
    double currentShearRate;

    virtual double getInteractionLengthScale();

    virtual void reset();

    virtual REAL_C getShearForce(int index);

    virtual void equationOfMotion();
    virtual void calculateInteractionForce(int i, int j);
    virtual void calculateExternalForce(int i);

//    virtual void setParticleList(vector<CHARGED_PARTICLE> particleListIn);

    virtual void addConfigurationalStress(REAL_C forceIn, int i, int j);
    virtual void addExternalStress(const REAL_C& forceIn, int i);

    double calculateCurrentShearRate();

public:
    SHEARED_SLITPORE_SYSTEM();
    SHEARED_SLITPORE_SYSTEM(const ARGUMENTS& args);

    int printStress = PRINT_STRESS;
    int printEnergy = PRINT_ENERGY;

    virtual void prepareSystem();

    virtual REAL_C forceFromParticleOnParticle(CHARGED_PARTICLE& particle1, CHARGED_PARTICLE& particle2);
    virtual REAL_C forceOnParticleFromExternalFields(CHARGED_PARTICLE& particle);
    virtual double energyFromParticleOnParticle(CHARGED_PARTICLE& particle1, CHARGED_PARTICLE& particle2);
    virtual double energyOfParticleFromExternalFields(CHARGED_PARTICLE& particle);

    virtual void convertPositionToBoxPosition();

    //setter functions

    //getter functions
    virtual vector<REAL_M> getStressPerParticle();
    virtual REAL_M getMeanStress() const;
    double getCurrentShearRate();

    vector<double> getEnergyPerParticle();
};

#endif // SHEARED_SLITPORE_SYSTEM_H

