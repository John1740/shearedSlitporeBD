#include "sheared_slitpore_system.h"

SHEARED_SLITPORE_SYSTEM::SHEARED_SLITPORE_SYSTEM(){
//    prepareSystem();
}

SHEARED_SLITPORE_SYSTEM::SHEARED_SLITPORE_SYSTEM(const ARGUMENTS& args) : CONFINED_BROWNIAN_PARTICLES(args){
    printStress = args.printStress;
    if(args.printStressFourier > 0){
        printStress = args.printStressFourier;
    }
    printEnergy = args.printEnergy;
    shearRateOffset = args.shearRate;
    shearRateAmplitude = args.amplitude;
    oscillationPeriod = args.oscillationPeriod;
    phaseOffset = args.phaseOffset;
    currentShearRate = calculateCurrentShearRate();
    
    swf = SOFT_WALL_FORCE(args.wallInteractionStrength, simBox.getDimensions().z);
    dlvo = DLVO_SOFTSPHERE_INTERACTION(args.ssInteractionStrength);
    
    prepareSystem();
}

//needs to be done after input variables have been changed
void SHEARED_SLITPORE_SYSTEM::prepareSystem(){
    shearForce = SHEAR_FORCE(currentShearRate);
    //update lengthRange and then invoke all following setup calculations again
    
    dlvo.charge1 = particle[0].charge;
    dlvo.charge2 = particle[0].charge;
    dlvo.diameter1 = particle[0].diameter;
    dlvo.diameter2 = particle[0].diameter;
    dlvo.density = getDensity();
    dlvo.lengthRange = simBox.getDimensions().x;
    dlvo.calculateInteractionParameters();    //needs to be done anew since lengthRange changed
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
    previousParticle = particle;
    this->shearForce.shearRate = calculateCurrentShearRate();

    for(int i = 0; i < particle.size(); ++i){
        randomDisplacement = getRandomDisplacement();
        shearForce = getShearForce(i);

        particle[i].position += force[i] * D0 * dt / T + randomDisplacement + shearForce * dt;

        if(particle[i].position.z > 0.5 * simBox.getDimensions().z || particle[i].position.z < -0.5 * simBox.getDimensions().z){
            cout << "particle[i].position.z = " << particle[i].position.z << endl;
        }
        particle[i].setBoxPosition(simBox);
    }
    timestep++;
}

REAL_C SHEARED_SLITPORE_SYSTEM::getShearForce(int index){
    return shearForce.forceOnParticle(particle[index]);
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
    REAL_C tmpForce = forceFromParticleOnParticle(particle[i], particle[j]);
    force[i] += tmpForce;
    force[j] -= tmpForce;

    if(printStress > 0){ //move somewhere else?
        addConfigurationalStress(tmpForce, i, j);
    }
    if(printEnergy > 0){
        double tmpEnergy = energyFromParticleOnParticle(particle[i],particle[j]);
        energy[i] += tmpEnergy;
        energy[j] += tmpEnergy;
    }
}

void SHEARED_SLITPORE_SYSTEM::addConfigurationalStress(REAL_C forceIn, int i, int j){
    REAL_C posDifference = particle[i].boxPosition - particle[j].boxPosition;
    posDifference = simBox.convertToBoxPosition(posDifference);
    REAL_M tmpStress(posDifference, forceIn);
    stressPerParticle[i] += 0.5* tmpStress;
    stressPerParticle[j] += 0.5* tmpStress;
}

void SHEARED_SLITPORE_SYSTEM::calculateExternalForce(int i){
    REAL_C tmpForce = forceOnParticleFromExternalFields(particle[i]);
    force[i] += tmpForce;

    if(printStress > 0){
        addExternalStress(tmpForce, i);
    }

    if(printEnergy > 0){
        energy[i] += energyOfParticleFromExternalFields(particle[i]);
    }
}

void SHEARED_SLITPORE_SYSTEM::addExternalStress(const REAL_C& forceIn, int i){   //const CARTESIAN_COORDINATE&
    REAL_M tmpStress(0.);

    if(particle[i].boxPosition.z >= 0){
        tmpStress.zz += forceIn.z * (particle[i].boxPosition.z - 0.5 * simBox.getDimensions().z);
    }
    else{
        tmpStress.zz += forceIn.z * (particle[i].boxPosition.z + 0.5 * simBox.getDimensions().z);
    }

    stressPerParticle[i] += tmpStress;
}

vector< REAL_M > SHEARED_SLITPORE_SYSTEM::getStressPerParticle(){
    vector<REAL_M> tmp = stressPerParticle;
    for(int i = 0; i < tmp.size(); ++i){
        tmp[i] *= -1/simBox.getVolume();
    }
    return tmp;
}

REAL_M SHEARED_SLITPORE_SYSTEM::getMeanStress() const{
    REAL_M meanStress(0.);
    for(int i = 0; i < stressPerParticle.size(); ++i){
        meanStress += stressPerParticle[i];
    }
    return -1.*meanStress/simBox.getVolume();
}

void SHEARED_SLITPORE_SYSTEM::convertPositionToBoxPosition(){
    for(int i = 0; i < particle.size(); ++i){
        particle[i].position = particle[i].boxPosition;
    }
}

vector<double> SHEARED_SLITPORE_SYSTEM::getEnergyPerParticle(){
    return energy;
}

double SHEARED_SLITPORE_SYSTEM::getCurrentShearRate(){
    return currentShearRate;
}

double SHEARED_SLITPORE_SYSTEM::calculateCurrentShearRate(){
    currentShearRate = shearRateOffset + shearRateAmplitude * cos(2 * M_PI * timestep * dt / oscillationPeriod + M_PI * phaseOffset);
    return currentShearRate;
}

