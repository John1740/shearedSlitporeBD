#ifndef SHEARED_SLITPORE_SYSTEM_H
#define SHEARED_SLITPORE_SYSTEM_H

#include "../systems/confined_brownian_particles.h"

#include "../interactions/dlvo_softsphere_interaction.h"
#include "../external/soft_wall_force.h"
#include "../external/shear_force.h"
#include "../external/oscillatory_shear.h"

#include "../argument_parser/argparse.h"

#include "../defaults.h"

class SHEARED_SLITPORE_SYSTEM: public CONFINED_BROWNIAN_PARTICLES{

    friend class SYSTEM_ENERGY;
private:

protected:
    DLVO_SOFTSPHERE_INTERACTION dlvo;
    SOFT_WALL_FORCE swf;
    SHEAR_FORCE<OSCILLATORY_SHEAR> sf;

//    vector<REAL_C> randomForces, shearFlowForces;
    vector<double> energy;
    vector<REAL_M> stressPerParticle;



    double currentShearRate;

    virtual double getInteractionLengthScale();

    virtual void reset();

    virtual void equationOfMotion();
    virtual void equationOfMotionRK();
    virtual void equationOfMotionCBD();
    virtual void calculateInteractionForce(int i, int j);
    virtual void calculateExternalForce(int i);

    virtual void addConfigurationalStress(REAL_C forceIn, int i, int j);
    virtual void addExternalStress(const REAL_C& forceIn, int i);

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

    //file/stream-handling
    virtual void print(ostream& os) const override;
};

#endif // SHEARED_SLITPORE_SYSTEM_H

