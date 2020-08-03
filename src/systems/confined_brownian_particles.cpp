#include "confined_brownian_particles.h"
#include "../command/generate_square_layers.h"  //can't use in header (circular dependency)
#include "../struct/layers.h"
#include "../order_parameter/intra_layer_pair_correlation_function.h"
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
namespace bo = boost;

CONFINED_BROWNIAN_PARTICLES::CONFINED_BROWNIAN_PARTICLES(){
}

CONFINED_BROWNIAN_PARTICLES::CONFINED_BROWNIAN_PARTICLES(const ARGUMENTS &args) {
    configurationIn = args.configurationIn;
//    numberOfParticles = args.numberOfParticles;
//    density = args.density;
//    dWall = args.dWall;
    
    readConfigurationFromFile(configurationIn, true); //reads (or creates) simBox and particle positions
    dt = args.dt;
    T = args.temperature;
    D0 = args.D0;
    initSeed(args.seed);
}

CONFINED_BROWNIAN_PARTICLES::~CONFINED_BROWNIAN_PARTICLES(){

}

void CONFINED_BROWNIAN_PARTICLES::simulateForSteps(int maxSteps){
    for(int i = 0; i < maxSteps; ++i){
        equationOfMotion();
    }
}

void CONFINED_BROWNIAN_PARTICLES::equationOfMotion(){
    calculateForce();
    REAL_C randomDisplacement;
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
    force.assign(numberOfParticles, REAL_C(0.));
}

REAL_C CONFINED_BROWNIAN_PARTICLES::getRandomDisplacement(){
    REAL_C randomForce;
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

vector< REAL_C > CONFINED_BROWNIAN_PARTICLES::getPositionList(){
    setPositionInBox();
    vector<REAL_C> positionList(particle.size());

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
    REAL_C tmpForce = forceFromParticleOnParticle(particle[i], particle[j]);
    force[i] += tmpForce;
    force[j] -= tmpForce;
}

void CONFINED_BROWNIAN_PARTICLES::calculateExternalForce(int i){
    force[i] += forceOnParticleFromExternalFields(particle[i]);
}

REAL_C CONFINED_BROWNIAN_PARTICLES::forceFromParticleOnParticle(CHARGED_PARTICLE& particle1, CHARGED_PARTICLE& particle2){
    return REAL_C(0.);
}

double CONFINED_BROWNIAN_PARTICLES::energyFromParticleOnParticle(CHARGED_PARTICLE& particle1, CHARGED_PARTICLE& particle2){
    return 0.;
}

REAL_C CONFINED_BROWNIAN_PARTICLES::forceOnParticleFromExternalFields(CHARGED_PARTICLE& particle){
    return REAL_C(0.);
}

double CONFINED_BROWNIAN_PARTICLES::energyOfParticleFromExternalFields(CHARGED_PARTICLE& particle){
    return 0.;
}

double CONFINED_BROWNIAN_PARTICLES::getTimeStepSize(){
    return dt;
}

void CONFINED_BROWNIAN_PARTICLES::writeConfigurationToFileOld(string filename, bool verbose){
//    PRINTER printer(configurationOut);
//    printer.reset();
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

void CONFINED_BROWNIAN_PARTICLES::readConfigurationFromFileOld(string filename, bool createIfMissing, bool verbose){
    //check for existance
    if(fs::exists(filename) == false){
        if(createIfMissing){
            cout << configurationIn << " does not exist!" << endl;
            setInitialConfigurationForLayersWithSides();
            writeConfigurationToFileOld(configurationIn, false);
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
            REAL_C boxDimensions;
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
    
//    dWall = simBox.getDimensions().z;
//    density = numberOfParticles / simBox.getVolume();
    
    //read particle positions
    while(f >> c1 >> c2 >> c3){
        newParticle.position = REAL_C(c1, c2, c3);
        particleIn.push_back(newParticle);
    }
    
    if(verbose){
        cout << "Read " << filename << " successfully!" << endl;
    }
    if(particleIn.size() != numberOfParticles){
        cout << "Number of particles deviates from expected number: ";
        cout << particleIn.size() << " != " << numberOfParticles << endl;
    }
    setParticleList(particleIn);
}

void CONFINED_BROWNIAN_PARTICLES::writeConfigurationToFile(string filename, bool verbose){
    PRINTER printer(filename);
    printer.reset();
    const char* fmt = "% 2.5f\t";
    
    //header
    printer << bo::format("ITEM: TIMESTEP\n%ld\n") % timestep;
    
    //box geometry
    printer << simBox;
    
    //particle positions
    printer << bo::format("ITEM: NUMBER OF ATOMS\n%d\n") % numberOfParticles;
    printer << "ITEM: ATOMS index x y z diameter charge species\n";
    for(int i = 0; i < numberOfParticles; ++i){
        printer << bo::format("%4d\t") % particle[i].index;
//        printer << bo::format("%4d\t") % i;
        printer << bo::format(fmt) % particle[i].boxPosition.x;
        printer << bo::format(fmt) % particle[i].boxPosition.y;
        printer << bo::format(fmt) % particle[i].boxPosition.z;
        printer << bo::format("%2.3f\t") % particle[i].diameter;
        printer << bo::format("%3.2f\t") % particle[i].charge;
//        printer << bo::format("%3.2f\t") % 35;
        printer << bo::format("%2d\t") % particle[i].species;
        printer << '\n';
    }
    if(verbose){
        cout << "Wrote configuration to " << filename << endl;
    }
}

void CONFINED_BROWNIAN_PARTICLES::readConfigurationFromFile(string filename, bool verbose){
    //this also checks if file exists
    simBox.readFromFile(filename);
    
    ifstream f;
    f.open(filename.c_str());
    string line;
    
    //reset metadata (and throw error if essential data is missing in file)
    timestep = 0;
    numberOfParticles = 0;
    
    //read header/metadata
    int found = 0;
    while(getline(f, line)){
        //defaults to 0 if not found
        if(line.find("TIMESTEP") != string::npos){
            getline(f, line);
            timestep = stol(line);
            found++;
        }
        else if(line.find("NUMBER OF ATOMS") != string::npos){
            getline(f, line);
            numberOfParticles = stoi(line);
            found++;
        }
        //skip looking through rest of file
        if(found >= 2){
            break;
        }
    }
    f.close();
    
    // error messages (metadata)
    if(numberOfParticles == 0){
        cout << "numberOfParticles within " + filename + " not valid. Please set accordingly with:" << endl;
        cout << "ITEM: NUMBER OF ATOMS\n<numberOfParticles>" << endl;
        exit(0);
    }
    
    //read particle information
    readParticlesFromFile(filename, true);
    
//    dWall = simBox.getDimensions().z;   //deprecated
//    density = numberOfParticles / simBox.getVolume();
    
    if(verbose){
        cout << "Read " << filename << " successfully!" << endl;
    }
}

//numberOfParticles needs to be set
CONFINED_BROWNIAN_PARTICLES& CONFINED_BROWNIAN_PARTICLES::readParticlesFromFile(string filename, bool addMissingInfo){
    vector<CHARGED_PARTICLE> particleIn;
    particleIn.clear();
    ifstream f;
    f.open(filename.c_str());
    CHARGED_PARTICLE newParticle;
    string line;
    while(getline(f, line)){
        //search for ATOMS keyword
        string keyword = "ITEM: ATOMS ";
        if(line.find(keyword) != string::npos){
            //find out number of columns
            line = line.erase(line.find(keyword), keyword.length());
            vector<string> linesplit;
            bo::split(linesplit, line, bo::is_any_of(" "));
            int numberOfColumns = linesplit.size();
            //find out column mapping
            int pIndex = -1, pX = -1, pY = -1, pZ = -1, pDiameter = -1, pCharge = -1, pSpecies = -1;
            for(int i = 0; i < numberOfColumns; i++){
                if(linesplit[i].compare("index") == 0){
                    pIndex = i; continue;
                }
                else if(linesplit[i].compare("x") == 0){
                    pX = i; continue;
                }
                else if(linesplit[i].compare("y") == 0){
                    pY = i; continue;
                }
                else if(linesplit[i].compare("z") == 0){
                    pZ = i; continue;
                }
                else if(linesplit[i].compare("diameter") == 0){
                    pDiameter = i; continue;
                }
                else if(linesplit[i].compare("charge") == 0){
                    pCharge = i; continue;
                }
                else if(linesplit[i].compare("species") == 0){
                    pSpecies = i; continue;
                }
                else{
                    cout << "Can't recognize the label " << linesplit[i] << " in the configuration file." << endl;
                }
            }
            if(pX == -1 || pY == -1 || pZ == -1){
                cout << "Missing a x-, y- or z-position column. Please use the following header:" << endl;
                cout << keyword << "index x y z diameter charge species" << endl;
                exit(0);
            }
            
            //read particle positions
            vector<double> c(numberOfColumns);   //container
            int counter = 0;
            while(counter < numberOfParticles){
                for(int i = 0; i < numberOfColumns; i++){
                    f >> c[i];
                }
                if(pIndex != -1){
                    newParticle.index = c[pIndex];
                }
                else{
                    newParticle.index = counter;
                }
                newParticle.position = REAL_C(c[pX], c[pY], c[pZ]);
                newParticle.boxPosition = newParticle.position;
                if(pDiameter != -1){
                    newParticle.diameter = c[pDiameter];
                }
                else{
                    if(addMissingInfo){
                        newParticle.diameter = 1.0;
                    }
                    else{
                        cout << "Missing a particle diameter column. Please provide one via:" << endl;
                        cout << keyword << "index x y z diameter charge species" << endl;
                        exit(0);
                    }
                }
                if(pCharge != -1){
                    newParticle.charge = c[pCharge];
                }
                else{
                    if(addMissingInfo){
                        newParticle.charge = 35;
                    }
                    else{
                        cout << "Missing a particle charge column. Please provide one via:" << endl;
                        cout << keyword << "index x y z diameter charge species" << endl;
                        exit(0);
                    }
                }
                if(pSpecies != -1){
                    newParticle.species = c[pSpecies];
                }
                else{
                    newParticle.species = 0;
                }
                particleIn.push_back(newParticle);
                counter++;
            }
            break;
        }
    }
    f.close();
    if(particleIn.size() != numberOfParticles){
        cout << "Number of particles deviates from expected number: ";
        cout << particleIn.size() << " != " << numberOfParticles << endl;
        exit(0);
    }
    setParticleList(particleIn);
    return *this;
}

void CONFINED_BROWNIAN_PARTICLES::setParticleList(vector<CHARGED_PARTICLE> particleListIn){
    particle = particleListIn;
    setPositionInBox();
}

SLIT_PORE_BOX CONFINED_BROWNIAN_PARTICLES::getSimulationBox(){
    return simBox;
}

void CONFINED_BROWNIAN_PARTICLES::setTimeStepSize(double timeStepSizeIn, bool verbose){
    if(verbose){
        cout << "Set dt = " << dt << " to " << timeStepSizeIn << endl;
    }
    dt = timeStepSizeIn;
}

//Calculate the velocities of the previous time step.
//v(t-dt) = (r(t) - r(t-dt))/dt
vector<REAL_C> CONFINED_BROWNIAN_PARTICLES::getVelocities(){
    vector<REAL_C> velocities;
    for(int i = 0; i < numberOfParticles; i++){
        REAL_C positionDifference = particle[i].boxPosition - previousParticle[i].boxPosition;
        positionDifference = simBox.convertToBoxPosition(positionDifference);
        velocities.push_back(positionDifference / dt);
    }
    return velocities;
}

REAL_C CONFINED_BROWNIAN_PARTICLES::getMeanVelocity(){
    vector<REAL_C> velocities = getVelocities();
    REAL_C meanVelocity;
    for(int i = 0; i < numberOfParticles; i++){
        meanVelocity += velocities[i];
    }
    meanVelocity /= numberOfParticles;
    return meanVelocity;
}

//Returns velocity average of each layer. Length of returned vector corresponds to number of layers.
vector<REAL_C> CONFINED_BROWNIAN_PARTICLES::getMeanLayerVelocities(){
    LAYERS layers(simBox);
    int numberOfLayers = layers.getNumberOfLayers();
    
    vector<REAL_C> velocities = getVelocities();
    vector<REAL_C> meanLayerVelocities(numberOfLayers);
    vector<int> counter(numberOfLayers);
    int layerNumber;
    for(int i = 0; i < numberOfParticles; i++){
        layerNumber = layers.tellLayerNumber(previousParticle[i]);
        meanLayerVelocities[layerNumber] += velocities[i];
        counter[layerNumber]++;
    }
    for(int j = 0; j < numberOfLayers; j++){
        meanLayerVelocities[j] /= counter[j];
    }
    return meanLayerVelocities;
}

void CONFINED_BROWNIAN_PARTICLES::setInitialConfigurationForLayersWithSides(){
    simBox = SLIT_PORE_BOX(numberOfParticles / DENSITY, D_WALL);
    int numberOfLayers = round(simBox.getDimensions().z);
    int numberOfSides = sqrt(numberOfParticles / numberOfLayers);
    
    cout << "Set particle positions to " << numberOfLayers << " quadratic layers with " << numberOfSides << " sides!" << endl;
    
    GENERATE_SQUARE_LAYERS initialConfiguration;
    initialConfiguration.setNumberOfLayersRowsAdditionalRows(numberOfLayers, numberOfSides, 0);
    initialConfiguration.doForSystem(*this);
}

void CONFINED_BROWNIAN_PARTICLES::setTimestep(long timestepIn){
    timestep = timestepIn;
}

long CONFINED_BROWNIAN_PARTICLES::getTimestep() const{
    return timestep;
}

double CONFINED_BROWNIAN_PARTICLES::getDensity() const{
    double density = numberOfParticles / simBox.getVolume();
    return density;
}
