#include "confined_brownian_particles.h"

CONFINED_BROWNIAN_PARTICLES::CONFINED_BROWNIAN_PARTICLES(){
}

CONFINED_BROWNIAN_PARTICLES::CONFINED_BROWNIAN_PARTICLES(const ARGUMENTS &args) {
    dt = args.dt;
    T = args.temperature;
    D0 = args.D0;
    numberOfParticles = args.numberOfParticles;
    initSeed(args.seed);
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
    previousParticle = particle;

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

vector<CHARGED_PARTICLE> CONFINED_BROWNIAN_PARTICLES::getParticleList(){
    return particle;
}

vector<CHARGED_PARTICLE> CONFINED_BROWNIAN_PARTICLES::getPreviousParticleList(){
    return previousParticle;
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

//Calculate the velocities of the previous time step.
//v(t-dt) = (r(t) - r(t-dt))/dt
vector<CARTESIAN_COORDINATE> CONFINED_BROWNIAN_PARTICLES::getVelocities(){
    vector<CARTESIAN_COORDINATE> velocities;
    for(int i = 0; i < numberOfParticles; i++){
        CARTESIAN_COORDINATE positionDifference = particle[i].boxPosition - previousParticle[i].boxPosition;
        positionDifference = simBox.convertToBoxPosition(positionDifference);
        velocities.push_back(positionDifference / dt);
    }
    return velocities;
}

CARTESIAN_COORDINATE CONFINED_BROWNIAN_PARTICLES::getMeanVelocity(){
    vector<CARTESIAN_COORDINATE> velocities = getVelocities();
    CARTESIAN_COORDINATE meanVelocity;
    for(int i = 0; i < numberOfParticles; i++){
        meanVelocity += velocities[i];
    }
    meanVelocity /= numberOfParticles;
    return meanVelocity;
}

//Returns velocity average of each layer. Length of returned vector corresponds to number of layers.
vector<CARTESIAN_COORDINATE> CONFINED_BROWNIAN_PARTICLES::getMeanLayerVelocities(){
    int numberOfLayers = round(simBox.getDimensions().z);
    double zMin = - 0.2 * simBox.getDimensions().z;
    double dz = - 2 * zMin / (numberOfLayers - 1);   //dz is width of each layer
    vector<double> layerCenter;
    for(int i = 0; i < numberOfLayers; i++){
        layerCenter.push_back((zMin + i * dz));
    }
    
    vector<CARTESIAN_COORDINATE> velocities = getVelocities();
    vector<CARTESIAN_COORDINATE> meanLayerVelocities(numberOfLayers);
    vector<int> counter(numberOfLayers);
    for(int i = 0; i < numberOfParticles; i++){
        double zCurrent = previousParticle[i].boxPosition.z;
        for(int j = 0; j < numberOfLayers; j++){
            if(zCurrent >= layerCenter[j] - dz / 2 && zCurrent < layerCenter[j] + dz / 2){
                meanLayerVelocities[j] += velocities[i];
                counter[j]++;
                break;
            }
        }
        //not optimal
        if(zCurrent < layerCenter[0] - dz / 2 || zCurrent >= layerCenter[numberOfLayers - 1] + dz / 2){
            printf("Particle %d can't be assigned to any layer (z=%.2f).\n", i, zCurrent);
        }
    }
    for(int j = 0; j < numberOfLayers; j++){
        meanLayerVelocities[j] /= counter[j];
    }
    return meanLayerVelocities;
}


