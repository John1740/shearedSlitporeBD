#include "sheared_slitpore_system.h"
#include <boost/format.hpp>

namespace bo = boost;

SHEARED_SLITPORE_SYSTEM::SHEARED_SLITPORE_SYSTEM(){
    prepareSystem();
}

SHEARED_SLITPORE_SYSTEM::SHEARED_SLITPORE_SYSTEM(const ARGUMENTS& args): CONFINED_BROWNIAN_PARTICLES(args){
    printStress = args.printStress;
    if(args.printStressFourier > 0){
        printStress = args.printStressFourier;
    }
    printEnergy = args.printEnergy;
    OSCILLATORY_SHEAR shearProtocol(args.shearRate, args.amplitude, args.oscillationPeriod, args.phaseOffset);
    sf = SHEAR_FORCE<OSCILLATORY_SHEAR>(shearProtocol);
    sf.mu = args.mu;

    swf = SOFT_WALL_FORCE(args.wallInteractionStrength, simBox.getDimensions().z);
    dlvo = DLVO_SOFTSPHERE_INTERACTION(particles[0].diameter, args.ssInteractionStrength,
                                       args.yInteractionStrength, args.kappa);

    prepareSystem();
}

SHEARED_SLITPORE_SYSTEM::~SHEARED_SLITPORE_SYSTEM(){
    prepareSystem();
}

//needs to be done after input variables have been changed
void SHEARED_SLITPORE_SYSTEM::prepareSystem(){
    force1.assign(numberOfParticles, REAL_C(0.)); // Temporary vector to store the force at the initial pos
    randomDisplacement.assign(numberOfParticles, REAL_C(0.)); // Vector to Store current randomDisplacement
    shearforce1.assign(numberOfParticles, REAL_C(0.)); //Vector to store shear force for CBD step
    shearforce2.assign(numberOfParticles, REAL_C(0.)); //Vector to store shear force for SRK step
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
    force.assign(numberOfParticles, REAL_C(0.));  // Vector to Store current force for each particle


    if(printStress > 0){
        stressPerParticle.assign(numberOfParticles, REAL_M(0.));
    }

    if(printEnergy > 0){
        energyParticleParticle.assign(numberOfParticles, 0.);
        energyExternal.assign(numberOfParticles, 0.);
        energy.assign(numberOfParticles, 0.);
    }
}
void SHEARED_SLITPORE_SYSTEM::equationOfMotion(){
    equationOfMotionCBD();
}

void SHEARED_SLITPORE_SYSTEM::equationOfMotionRK(){
    // Calculates new positions via a 2. Order statistical Runge Kutta(SRK) Methode by calculating
    // the force and temporarily positions via the conventional BD Methode and then calculate forces on the temporary
    // positions to finally calculate the final positions with the average of the forces.


    equationOfMotionCBD();// Calculate force and  temporary positions via conventional BD Methode
    force1=force;

    calculateForce();   // Calculate force at temporary positions

    currentShearRate = sf.shearProtocol.calculateShearRate(timestep * dt);
    for(int i = 0; i < particles.size(); ++i){
        shearforce2[i] = sf.forceOnParticle(particles[i], timestep * dt);    // Get shear force
    }

    timestep--;         // Go back to initial time step
    particles=previousParticles;    // Go back to initial position

    for(int i = 0; i < particles.size(); ++i){

        // Calculate final position via SRK
        particles[i].position += mu / 2 * (force[i] + shearforce2[i] + force1[i] + shearforce1[i]) * dt + randomDisplacement[i];
        if(particles[i].position.z > 0.5 * simBox.getDimensions().z ||
           particles[i].position.z < -0.5 * simBox.getDimensions().z){
            cout << "particle[i].position.z = " << particles[i].position.z << endl;
        }
        particles[i].setBoxPosition(simBox);    // Convert new Positions to Position in Simulation Box
    }
    timestep++;


}

void SHEARED_SLITPORE_SYSTEM::equationOfMotionCBD(){
    // Calculates new positions via a conventional BD Methode by calculating the forces with calculateForce()

    calculateForce();  // Calculate force at the initial position

    previousParticles = particles;
    currentShearRate = sf.shearProtocol.calculateShearRate(timestep * dt);

    for(int i = 0; i < particles.size(); ++i){
        randomDisplacement[i] = getRandomDisplacement();
        shearforce1[i] = sf.forceOnParticle(particles[i], timestep * dt);

        particles[i].position += mu * (force[i]+shearforce1[i]) * dt + randomDisplacement[i];

        if(particles[i].position.z > 0.5 * simBox.getDimensions().z ||
           particles[i].position.z < -0.5 * simBox.getDimensions().z){
            cout << "particle[i].position.z = " << particles[i].position.z << endl;
        }
        particles[i].setBoxPosition(simBox);
    }
    timestep++;
}

//REAL_C SHEARED_SLITPORE_SYSTEM::getShearForce(int index){
//    return shearForce.forceOnParticle(particles[index]);
//}

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
        energyParticleParticle[i]+=tmpEnergy;
        energyParticleParticle[j]+=tmpEnergy;
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
        double tmpEnergy = energyOfParticleFromExternalFields(particles[i]);
        energy[i] += tmpEnergy;
        energyExternal[i] += tmpEnergy;
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

REAL_C SHEARED_SLITPORE_SYSTEM::getParticlePosition(int i){
    return particles[i].position;
}

double SHEARED_SLITPORE_SYSTEM::getEnergyForParticle(int i){
    if(i>particles.size()-1){
        return 0;
    }
    double particleEnergy= 0;
    particleEnergy +=energyOfParticleFromExternalFields(particles[i]);
    for(int j = 0; j < numberOfParticles; ++j){
        if(i != j){
            particleEnergy += energyFromParticleOnParticle(particles[i], particles[j]);
        }
    }
    return particleEnergy;
    }


void SHEARED_SLITPORE_SYSTEM::shiftParticle(int i,double dx,double dy,double dz){
    particles[i].position.x+=dx;
    particles[i].position.y+=dy;
    particles[i].position.z+=dz;
    particles[i].setBoxPosition(simBox);
}

double SHEARED_SLITPORE_SYSTEM::getSystemEnergy(){
    calculateForce();
    double systemEnergy=0;
    for(int i = 0; i < numberOfParticles; ++i){
        systemEnergy+=energyExternal[i]+0.5*energyParticleParticle[i];
    }
    return systemEnergy;
}

double SHEARED_SLITPORE_SYSTEM::getCurrentShearRate(){
    return currentShearRate;
}

int SHEARED_SLITPORE_SYSTEM::getNumberOfParticles(){
    return numberOfParticles;
}

void SHEARED_SLITPORE_SYSTEM::setSWF(double wallInteractionStrength,double dWall){
    swf = SOFT_WALL_FORCE(wallInteractionStrength, simBox.getDimensions().z);

}

void SHEARED_SLITPORE_SYSTEM::setDLVO(double ss_interactionStrength,double yInteractionStrength,double kappa){
    dlvo = DLVO_SOFTSPHERE_INTERACTION(particles[0].diameter, ss_interactionStrength,
    yInteractionStrength, kappa);
    dlvo.lengthRange = simBox.getDimensions().x;
    dlvo.setup();    //needs to be done anew since lengthRange changed
}

void SHEARED_SLITPORE_SYSTEM::publicCalculateForce(){

    calculateForce();
}

void SHEARED_SLITPORE_SYSTEM::print(ostream& os) const{
    const char* fmt = "% .8e\t";
    CONFINED_BROWNIAN_PARTICLES::print(os);
    os << endl;
    os << "printStress: " << bo::format(fmt) % printStress << endl;
    os << "printEnergy: " << bo::format(fmt) % printEnergy << endl;
    os << endl;
    os << "DLVO_SOFTSPHERE_INTERACTION:" << endl;
    os << dlvo << endl;
    os << endl;
    os << "SOFT_WALL_INTERACTION:" << endl;
    os << swf << endl;
    os << endl;
    os << "SHEAR_FORCE:" << endl;
    os << sf;
}
