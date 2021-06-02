#include "sheared_slitpore_system.h"
#include <boost/format.hpp>

namespace bo = boost;

SHEARED_SLITPORE_SYSTEM::SHEARED_SLITPORE_SYSTEM(){
    currentShearRate = calculateCurrentShearRate();
    prepareSystem();
}

SHEARED_SLITPORE_SYSTEM::SHEARED_SLITPORE_SYSTEM(const ARGUMENTS& args): CONFINED_BROWNIAN_PARTICLES(args){
    printStress = args.printStress;
    if(args.printStressFourier > 0){
        printStress = args.printStressFourier;
    }
    printEnergy = args.printEnergy;
    OSCILLATORY_SHEAR shearProtocol(args.shearRate, args.amplitude, args.oscillationPeriod, args.phaseOffset);
    shearForce = SHEAR_FORCE(shearProtocol);
//    currentShearRate = calculateCurrentShearRate();

    swf = SOFT_WALL_FORCE(args.wallInteractionStrength, simBox.getDimensions().z);
    dlvo = DLVO_SOFTSPHERE_INTERACTION(particles[0].diameter, args.ssInteractionStrength,
                                       args.yInteractionStrength, args.kappa);

    prepareSystem();
}

//needs to be done after input variables have been changed
void SHEARED_SLITPORE_SYSTEM::prepareSystem(){
    shearForce = SHEAR_FORCE(currentShearRate);
    //update lengthRange and then invoke all following setup calculations again
    dlvo.lengthRange = simBox.getDimensions().x;
    dlvo.setup();    //needs to be done anew since lengthRange changed
    reset();
}

double SHEARED_SLITPORE_SYSTEM::getInteractionLengthScale(){
    return dlvo.cutOffRadius;
}

//reset forces, stresses and energy
void SHEARED_SLITPORE_SYSTEM::reset(){
    force.assign(numberOfParticles, REAL_C(0.));

    if(printStress > 0){
        stressPerParticle.assign(numberOfParticles, REAL_M(0.));
    }

    if(printEnergy > 0){
        energy.assign(numberOfParticles, 0.);
    }
}

void SHEARED_SLITPORE_SYSTEM::equationOfMotion(){
    // Force calculation
    calculateForce();

    REAL_C randomDisplacement;
    REAL_C shearForce;
    previousParticles = particles;
    this->shearForce.shearRate = calculateCurrentShearRate();

    for(int i = 0; i < particles.size(); ++i){
        randomDisplacement = getRandomDisplacement();
        shearForce = getShearForce(i);

        particles[i].position += force[i] * D0 * dt / T + randomDisplacement + shearForce * dt;

        if(particles[i].position.z > 0.5 * simBox.getDimensions().z ||
           particles[i].position.z < -0.5 * simBox.getDimensions().z){
            cout << "particle[i].position.z = " << particles[i].position.z << endl;
        }
        particles[i].setBoxPosition(simBox);
    }
    timestep++;
}

REAL_C SHEARED_SLITPORE_SYSTEM::getShearForce(int index){
    return shearForce.forceOnParticle(particles[index]);
}

REAL_C SHEARED_SLITPORE_SYSTEM::forceFromParticleOnParticle(CHARGED_PARTICLE& particle1, CHARGED_PARTICLE& particle2){
    return dlvo.forceOnParticleFromParticle(particle1, particle2, simBox);
}

REAL_C SHEARED_SLITPORE_SYSTEM::forceOnParticleFromExternalFields(CHARGED_PARTICLE& particle){
    return swf.forceOnParticle(particle);
}

double SHEARED_SLITPORE_SYSTEM::energyFromParticleOnParticle(CHARGED_PARTICLE& particle1, CHARGED_PARTICLE& particle2){
    return dlvo.energyOnParticleFromParticle(particle1, particle2, simBox);
}

double SHEARED_SLITPORE_SYSTEM::energyOfParticleFromExternalFields(CHARGED_PARTICLE& particle){
    return swf.energyOnParticle(particle);
}

//void SHEARED_SLITPORE_SYSTEM::setParticleList(vector<CHARGED_PARTICLE> particleListIn){
//    particle = particleListIn; //copy particleList
//    setPositionInBox();
//}

void SHEARED_SLITPORE_SYSTEM::calculateInteractionForce(int i, int j){
    REAL_C tmpForce = forceFromParticleOnParticle(particles[i], particles[j]);
    force[i] += tmpForce;
    force[j] -= tmpForce;

    if(printStress > 0){ //move somewhere else?
        addConfigurationalStress(tmpForce, i, j);
    }
    if(printEnergy > 0){
        double tmpEnergy = energyFromParticleOnParticle(particles[i], particles[j]);
        energy[i] += tmpEnergy;
        energy[j] += tmpEnergy;
    }
}

void SHEARED_SLITPORE_SYSTEM::addConfigurationalStress(REAL_C forceIn, int i, int j){
    REAL_C posDifference = particles[i].boxPosition - particles[j].boxPosition;
    posDifference = simBox.convertToBoxPosition(posDifference);
    REAL_M tmpStress(posDifference, forceIn);
    stressPerParticle[i] += 0.5 * tmpStress;
    stressPerParticle[j] += 0.5 * tmpStress;
}

void SHEARED_SLITPORE_SYSTEM::calculateExternalForce(int i){
    REAL_C tmpForce = forceOnParticleFromExternalFields(particles[i]);
    force[i] += tmpForce;

    if(printStress > 0){
        addExternalStress(tmpForce, i);
    }

    if(printEnergy > 0){
        energy[i] += energyOfParticleFromExternalFields(particles[i]);
    }
}

void SHEARED_SLITPORE_SYSTEM::addExternalStress(const REAL_C& forceIn, int i){   //const CARTESIAN_COORDINATE&
    REAL_M tmpStress(0.);

    if(particles[i].boxPosition.z >= 0){
        tmpStress.zz += forceIn.z * (particles[i].boxPosition.z - 0.5 * simBox.getDimensions().z);
    }
    else{
        tmpStress.zz += forceIn.z * (particles[i].boxPosition.z + 0.5 * simBox.getDimensions().z);
    }

    stressPerParticle[i] += tmpStress;
}

vector<REAL_M> SHEARED_SLITPORE_SYSTEM::getStressPerParticle(){
    vector<REAL_M> tmp = stressPerParticle;
    for(int i = 0; i < tmp.size(); ++i){
        tmp[i] *= -1 / simBox.getVolume();
    }
    return tmp;
}

REAL_M SHEARED_SLITPORE_SYSTEM::getMeanStress() const{
    REAL_M meanStress(0.);
    for(int i = 0; i < stressPerParticle.size(); ++i){
        meanStress += stressPerParticle[i];
    }
    return -1. * meanStress / simBox.getVolume();
}

void SHEARED_SLITPORE_SYSTEM::convertPositionToBoxPosition(){
    for(int i = 0; i < particles.size(); ++i){
        particles[i].position = particles[i].boxPosition;
    }
}

vector<double> SHEARED_SLITPORE_SYSTEM::getEnergyPerParticle(){
    return energy;
}

double SHEARED_SLITPORE_SYSTEM::getCurrentShearRate(){
    return currentShearRate;
}

double SHEARED_SLITPORE_SYSTEM::calculateCurrentShearRate(){
    currentShearRate = shearRateOffset +
                       shearRateAmplitude * cos(2 * M_PI * timestep * dt / oscillationPeriod + M_PI * phaseOffset);
    return currentShearRate;
}

ostream& operator<<(ostream& os, const SHEARED_SLITPORE_SYSTEM& sys){
    const char* fmt = "% .8f\t";
    os << "numberOfParticles: " << bo::format(fmt) % sys.numberOfParticles << endl;
    os << endl;
    os << "DLVO_SOFTSPHERE_INTERACTION: " << endl;
    os << sys.dlvo << endl;
    os << endl;
    os << "SOFT_WALL_INTERACTION: " << endl;
    os << sys.swf;
    //...
    return os;
}