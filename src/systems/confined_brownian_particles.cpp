#include "confined_brownian_particles.h"
#include "../command/generate_square_layers.h"  //can't use in header (circular dependency)

CONFINED_BROWNIAN_PARTICLES::CONFINED_BROWNIAN_PARTICLES(){
}

CONFINED_BROWNIAN_PARTICLES::CONFINED_BROWNIAN_PARTICLES(const ARGUMENTS &args) {
    configurationIn = args.configurationIn;
    numberOfParticles = args.numberOfParticles;
    density = args.density;
    dWall = args.dWall;
    
    readConfigurationFromFile(configurationIn, true); //reads (or creates) simBox and particle positions
    dt = args.dt;
    T = args.temperature;
    D0 = args.D0;
    initSeed(args.seed);
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
    timestep++;
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
    FILE* pFile = fopen(filename.c_str(), "w");
    const char* fmt = "% 2.5f\t";
    //header
    fprintf(pFile, "ITEM: TIMESTEP\n%ld\n", timestep);
    fprintf(pFile, "ITEM: NUMBER OF ATOMS\n%d\n", numberOfParticles);
    fprintf(pFile, "ITEM: BOX BOUNDS xx yy zz\n");
    fprintf(pFile, fmt, simBox.getOrigin().x - simBox.getDimensions().x / 2);
    fprintf(pFile, fmt, simBox.getOrigin().x + simBox.getDimensions().x / 2);
    fprintf(pFile, "\n");
    fprintf(pFile, fmt, simBox.getOrigin().y - simBox.getDimensions().y / 2);
    fprintf(pFile, fmt, simBox.getOrigin().y + simBox.getDimensions().y / 2);
    fprintf(pFile, "\n");
    fprintf(pFile, fmt, simBox.getOrigin().z - simBox.getDimensions().z / 2);
    fprintf(pFile, fmt, simBox.getOrigin().z + simBox.getDimensions().z / 2);
    fprintf(pFile, "\n");
    fprintf(pFile, "ITEM: ATOMS x y z\n");
    
    //particle positions
    for(int i = 0; i < numberOfParticles; ++i){
        fprintf(pFile, fmt, particle[i].boxPosition.x);
        fprintf(pFile, fmt, particle[i].boxPosition.y);
        fprintf(pFile, fmt, particle[i].boxPosition.z);
        fprintf(pFile, "\n");
    }
    fclose(pFile);
    if(verbose){
        cout << "Wrote configuration to " << filename << endl;
    }
}

void CONFINED_BROWNIAN_PARTICLES::readConfigurationFromFile(string filename, bool createIfMissing){
        //check for existance
        if(fs::exists(filename) == false){
            if(createIfMissing){
                cout << configurationIn << " does not exist!" << endl;
                setInitialConfigurationForLayersWithSides();
                writeConfigurationToFile(configurationIn, false);
                cout << "Set initial configuration and printed to: " << configurationIn << endl;
                return;
            }
            else{
                cout << configurationIn << " is missing!" << endl;
                exit(0);
            }
        }
        
        ifstream f;
        f.open(filename.c_str());
        
        vector<CHARGED_PARTICLE> particleIn;
        SLIT_PORE_BOX simBoxIn;
        particleIn.clear();
        
        double c1, c2, c3;  //containers
        CHARGED_PARTICLE newParticle;
        string line;
        
        //reset metadata (and throw error if essential data is missing in file)
        timestep = 0;
        numberOfParticles = 0;
        simBox.setDimensions(0);
        
        //read header/metadata
        while(getline(f, line)){
            if(line.find("TIMESTEP") != string::npos){
                getline(f, line);
                timestep = stol(line);
            }
            else if(line.find("NUMBER OF ATOMS") != string::npos){
                getline(f, line);
                numberOfParticles = stoi(line);
            }
            else if(line.find("BOX BOUNDS xx yy zz") != string::npos){
                CARTESIAN_COORDINATE boxDimensions;
                f >> c1 >> c2;
                boxDimensions.x = c2 - c1;
                f >> c1 >> c2;
                boxDimensions.y = c2 - c1;
                f >> c1 >> c2;
                boxDimensions.z = c2 - c1;
                simBox.setDimensions(boxDimensions);
            }
            else if(line.find("ATOMS x y z") != string::npos){
                break;
            }
        }
        
        // error messages (metadata)
        if(numberOfParticles == 0){
            cout << "numberOfParticles within " + filename + " not valid. Please set accordingly with:" << endl;
            cout << "ITEM: NUMBER OF ATOMS\n<numberOfParticles>" << endl;
            exit(0);
        }
        else if(simBox.getVolume() <= 0){
            cout << "Simulation box boundaries within " + filename + " not valid. Please set accordingly with:" << endl;
            cout << "ITEM: BOX BOUNDS xx yy zz\nxMin xMax\nyMin yMax\nzMin zMax" << endl;
            exit(0);
        }
        
        dWall = simBox.getDimensions().z;
        density = numberOfParticles / simBox.getVolume();
        
        //read particle positions
        while(f >> c1 >> c2 >> c3){
            newParticle.position = CARTESIAN_COORDINATE(c1, c2, c3);
            particleIn.push_back(newParticle);
        }
        
        cout << "Read " << filename << " successfully!" << endl;
        if(particleIn.size() != numberOfParticles){
            cout << "Number of particles deviates from expected number: ";
            cout << particleIn.size() << " != " << numberOfParticles << endl;
        }
        setParticleList(particleIn);
    }

void CONFINED_BROWNIAN_PARTICLES::setParticleList(vector<CHARGED_PARTICLE> particleListIn){
    particle = particleListIn;
    setPositionInBox();
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

void CONFINED_BROWNIAN_PARTICLES::setInitialConfigurationForLayersWithSides(){
    simBox = SLIT_PORE_BOX(numberOfParticles / density, dWall);
    int numberOfLayers = round(simBox.getDimensions().z);
    int numberOfSides = sqrt(numberOfParticles / numberOfLayers);
    
    cout << "Set particle positions to " << numberOfLayers << " quadratic layers with " << numberOfSides << " sides!" << endl;
    
    GENERATE_SQUARE_LAYERS initialConfiguration;
    initialConfiguration.setNumberOfLayersRowsAdditionalRows(numberOfLayers, numberOfSides, 0);
    initialConfiguration.doForSystem(*this);
}
