#include "confined_brownian_particles.h"

CONFINED_BROWNIAN_PARTICLES::CONFINED_BROWNIAN_PARTICLES(){
}

CONFINED_BROWNIAN_PARTICLES::CONFINED_BROWNIAN_PARTICLES(const ARGUMENTS &args) {
    dt = args.dt;
    T = args.temperature;
    D0 = args.D0;
    numberOfParticles = args.numberOfParticles;
}

string CONFINED_BROWNIAN_PARTICLES::app_identifier(string str){
    stringstream output;
    output << str;

    return output.str();
}

void CONFINED_BROWNIAN_PARTICLES::simulateForSteps(int maxSteps){
    for(int i = 0; i < maxSteps; ++i){
        equationOfMotion();
    }
}

void CONFINED_BROWNIAN_PARTICLES::equationOfMotion(){
    calculateForce();
    CARTESIAN_COORDINATE randomDisplacement;

    for(int i = 0; i < particle.size(); ++i){
        randomDisplacement = getRandomDisplacement();

        particle[i].position += force[i] * D0 * dt / T + randomDisplacement;
    }
    setPositionInBox();
}

void CONFINED_BROWNIAN_PARTICLES::calculateForce(){
    reset();
    calculateForces.doForSystem(*this);
}

//reset forces
void CONFINED_BROWNIAN_PARTICLES::reset(){
    force.assign(numberOfParticles, CARTESIAN_COORDINATE(0.));
}

CARTESIAN_COORDINATE CONFINED_BROWNIAN_PARTICLES::getRandomDisplacement(){
    CARTESIAN_COORDINATE randomForce;
    randomForce.x = sqrt(2 * D0 * dt) * boxmueller(0, 1);
    randomForce.y = sqrt(2 * D0 * dt) * boxmueller(0, 1);
    randomForce.z = sqrt(2 * D0 * dt) * boxmueller(0, 1);
    return randomForce;
}

SLIT_PORE_BOX* CONFINED_BROWNIAN_PARTICLES::simulationBox(){
    return &simBox;
}

vector< CHARGED_PARTICLE > CONFINED_BROWNIAN_PARTICLES::getParticleList(){
    return particle;
}

vector< CARTESIAN_COORDINATE > CONFINED_BROWNIAN_PARTICLES::getPositionList(){
    setPositionInBox();
    vector<CARTESIAN_COORDINATE> positionList(particle.size());

    for(int i = 0; i < particle.size(); ++i){
        positionList[i] = particle[i].boxPosition;
    }

    return positionList;
}

void CONFINED_BROWNIAN_PARTICLES::setPositionInBox(){
    for(int i = 0; i < particle.size(); ++i){
        particle[i].setBoxPosition(simBox);
    }
}

double CONFINED_BROWNIAN_PARTICLES::getInteractionLengthScale(){
    return 1.;
}

void CONFINED_BROWNIAN_PARTICLES::calculateInteractionForce(int i, int j){
    CARTESIAN_COORDINATE tmpForce = forceFromParticleOnParticle(particle[i], particle[j]);
    force[i] += tmpForce;
    force[j] -= tmpForce;
}

void CONFINED_BROWNIAN_PARTICLES::calculateExternalForce(int i){
    force[i] += forceOnParticleFromExternalFields(particle[i]);
}

CARTESIAN_COORDINATE CONFINED_BROWNIAN_PARTICLES::forceFromParticleOnParticle(CHARGED_PARTICLE& particle1, CHARGED_PARTICLE& particle2){
    return CARTESIAN_COORDINATE(0.);
}

double CONFINED_BROWNIAN_PARTICLES::energyFromParticleOnParticle(CHARGED_PARTICLE& particle1, CHARGED_PARTICLE& particle2){
    return 0.;
}

CARTESIAN_COORDINATE CONFINED_BROWNIAN_PARTICLES::forceOnParticleFromExternalFields(CHARGED_PARTICLE& particle){
    return CARTESIAN_COORDINATE(0.);
}

double CONFINED_BROWNIAN_PARTICLES::energyOfParticleFromExternalFields(CHARGED_PARTICLE& particle){
    return 0.;
}

double CONFINED_BROWNIAN_PARTICLES::getTimeStepSize(){
    return dt;
}

void CONFINED_BROWNIAN_PARTICLES::writeConfigurationToFile(string filename, bool verbose){
//    PRINTER printer(configurationOut);
//    printer.removeFile();
//    for(int i = 0; i < particle.size(); ++i){
//        printer.printLine(particle[i].position.x, particle[i].position.y, particle[i].position.z, particle[i].boxPosition.x, particle[i].boxPosition.y, particle[i].boxPosition.z);
//    }
    fstream f(filename.c_str(), ofstream::out);
    char buffer[20];
    const char* fmt = "% 2.5f\t";
    for(int i = 0; i < numberOfParticles; ++i){
        sprintf(buffer, fmt, particle[i].position.x);
        f << buffer;
        sprintf(buffer, fmt, particle[i].position.y);
        f << buffer;
        sprintf(buffer, fmt, particle[i].position.z);
        f << buffer;
        sprintf(buffer, fmt, particle[i].boxPosition.x);
        f << buffer;
        sprintf(buffer, fmt, particle[i].boxPosition.y);
        f << buffer;
        sprintf(buffer, fmt, particle[i].boxPosition.z);
        f << buffer << endl;
    }
    f.close();
    if(verbose){
        cout << "Wrote configuration to " << filename << endl;
    }
}

void CONFINED_BROWNIAN_PARTICLES::readConfigurationFromFile(string str){
    cout << "CONFINED_BROWNIAN_PARTICLES::readConfigurationFromFile is empty!" << endl;
}

void CONFINED_BROWNIAN_PARTICLES::setParticleList(vector< CHARGED_PARTICLE > particleListIn){
    particle = particleListIn;
}

SLIT_PORE_BOX CONFINED_BROWNIAN_PARTICLES::getSimulationBox(){
    return simBox;
}

void CONFINED_BROWNIAN_PARTICLES::setTimeStepSize(double timeStepSizeIn){
    cout << "Set dt = " << dt << " to " << timeStepSizeIn << endl;
    dt = timeStepSizeIn;
}

