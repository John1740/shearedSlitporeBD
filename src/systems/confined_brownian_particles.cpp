#include "confined_brownian_particles.h"

#include "../struct/layers.h"
#include "../rng/boxmueller.h"

#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>

namespace bo = boost;

CONFINED_BROWNIAN_PARTICLES::CONFINED_BROWNIAN_PARTICLES(){
}

CONFINED_BROWNIAN_PARTICLES::CONFINED_BROWNIAN_PARTICLES(const ARGUMENTS& args){
    configurationIn = args.configurationIn;

    bool successful = readConfigurationFromFile(configurationIn, true); //reads (or creates) simBox and particle positions
    if(!successful){
        cout << "Reading " << configurationIn << " failed!" << endl;
        exit(0);
    }
    dt = args.dt;
    kT = args.kT;
    mu = args.mu;
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
    previousParticles = particles;

    for(int i = 0; i < particles.size(); ++i){
        randomDisplacement = getRandomDisplacement();

        particles[i].position += mu * force[i] * dt + randomDisplacement;
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
    randomForce.x = sqrt(2 * mu * kT * dt) * boxmueller(0, 1);
    randomForce.y = sqrt(2 * mu * kT * dt) * boxmueller(0, 1);
    randomForce.z = sqrt(2 * mu * kT * dt) * boxmueller(0, 1);
    return randomForce;
}

SLIT_PORE_BOX* CONFINED_BROWNIAN_PARTICLES::simulationBox(){
    return &simBox;
}

vector<CHARGED_PARTICLE> CONFINED_BROWNIAN_PARTICLES::getParticleList(){
    return particles;
}

vector<CHARGED_PARTICLE> CONFINED_BROWNIAN_PARTICLES::getPreviousParticleList(){
    return previousParticles;
}

vector<REAL_C> CONFINED_BROWNIAN_PARTICLES::getPositionList(){
    setPositionInBox();
    vector<REAL_C> positionList(particles.size());

    for(int i = 0; i < particles.size(); ++i){
        positionList[i] = particles[i].boxPosition;
    }

    return positionList;
}

void CONFINED_BROWNIAN_PARTICLES::setPositionInBox(){
    for(int i = 0; i < particles.size(); ++i){
        particles[i].setBoxPosition(simBox);
    }
}

double CONFINED_BROWNIAN_PARTICLES::getInteractionLengthScale(){
    return 1.;
}

void CONFINED_BROWNIAN_PARTICLES::calculateInteractionForce(int i, int j){
    REAL_C tmpForce = forceFromParticleOnParticle(particles[i], particles[j]);
    force[i] += tmpForce;
    force[j] -= tmpForce;
}

void CONFINED_BROWNIAN_PARTICLES::calculateExternalForce(int i){
    force[i] += forceOnParticleFromExternalFields(particles[i]);
}

REAL_C
CONFINED_BROWNIAN_PARTICLES::forceFromParticleOnParticle(CHARGED_PARTICLE& particle1, CHARGED_PARTICLE& particle2){
    return REAL_C(0.);
}

double
CONFINED_BROWNIAN_PARTICLES::energyFromParticleOnParticle(CHARGED_PARTICLE& particle1, CHARGED_PARTICLE& particle2){
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

void CONFINED_BROWNIAN_PARTICLES::writeConfigurationToFile(string filename, bool overwrite, bool verbose){
    PRINTER printer(filename, overwrite);
//    if(overwrite){
//        printer.reset();
//    }
//    const char* fmt = "% .17e\t";
//    const char* fmt = "% .8e\t";

    //header
    printer << bo::format("ITEM: TIMESTEP\n%ld\n") % timestep;

    //box geometry
    printer << simBox;

    //particle positions
    printer << bo::format("ITEM: NUMBER OF ATOMS\n%d\n") % numberOfParticles;
    printer << "ITEM: ATOMS index x y z diameter charge species\n";
    for(int i = 0; i < numberOfParticles; ++i){
        printer << bo::format("%4d\t") % particles[i].index;
        printer << bo::format(printer.format_f) % particles[i].position.x;
        printer << bo::format(printer.format_f) % particles[i].position.y;
        printer << bo::format(printer.format_f) % particles[i].position.z;
        printer << bo::format("%2.3f\t") % particles[i].diameter;
        printer << bo::format("%3.2f\t") % particles[i].charge;
        printer << bo::format("%2d\t") % particles[i].species;
        printer << '\n';    //this leads to an empty last line
    }
    if(verbose){
        cout << "Wrote configuration to " << filename << endl;
    }
}

bool CONFINED_BROWNIAN_PARTICLES::readConfigurationFromFile(string filename, bool verbose){
    //this also checks if file exists
    SLIT_PORE_BOX simBox;
    bool successful = simBox.readFromFile(filename);
    if(!successful){
        return false;
    }

    ifstream f;
    f.open(filename.c_str());
    string line;

    //reset metadata (and throw error if essential data is missing in file)
    long timestep = 0;
    int numberOfParticles = 0;

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
        if(verbose){
            cout << "numberOfParticles within " + filename + " not valid. Please set accordingly with:" << endl;
            cout << "ITEM: NUMBER OF ATOMS\n<numberOfParticles>" << endl;
        }
        return false;
    }

    //read particle information
    SLIT_PORE_BOX simBoxOld = this->simBox;
    this->simBox = simBox;  //readParticleFromFile needs this->simBox information
    successful = readParticlesFromFile(filename, numberOfParticles, true, verbose);

    //only make permanent changes if everything was read successfully
    if(successful){
        this->timestep = timestep;
        this->numberOfParticles = numberOfParticles;
    }
    else{
        this->simBox = simBoxOld;
    }

    if(successful && verbose){
        cout << "Read " << filename << " successfully!" << endl;
    }
    return successful;
}

//needs simBox to be set
bool CONFINED_BROWNIAN_PARTICLES::readParticlesFromFile(string filename, int numberOfParticles, bool addMissingInfo, bool verbose){
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
                    pIndex = i;
                    continue;
                }
                else if(linesplit[i].compare("x") == 0){
                    pX = i;
                    continue;
                }
                else if(linesplit[i].compare("y") == 0){
                    pY = i;
                    continue;
                }
                else if(linesplit[i].compare("z") == 0){
                    pZ = i;
                    continue;
                }
                else if(linesplit[i].compare("diameter") == 0){
                    pDiameter = i;
                    continue;
                }
                else if(linesplit[i].compare("charge") == 0){
                    pCharge = i;
                    continue;
                }
                else if(linesplit[i].compare("species") == 0){
                    pSpecies = i;
                    continue;
                }
                else{
                    cout << "Can't recognize the label " << linesplit[i] << " in the configuration file " << filename << endl;
                }
            }
            if(pX == -1 || pY == -1 || pZ == -1){
                cout << "Missing a x-, y- or z-position column in" << filename << ". Please use the following header:" << endl;
                cout << keyword << "index x y z diameter charge species" << endl;
                return false;
            }

            //read particle positions
            vector<double> c(numberOfColumns);   //container
            int counter = 0;
            while(!f.eof()){    //enters the loop one time too often because of trailing last line
                for(int i = 0; i < numberOfColumns; i++){
                    f >> c[i];
                }
                if(f.eof()){    //abort if end of file is reached
                    break;
                }
                // it might be better to read the file line by line (easier to catch an empty line)
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
                        cout << "Missing a particle diameter column in " << filename << ". Please provide one via:" << endl;
                        cout << keyword << "index x y z diameter charge species" << endl;
                        return false;
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
                        cout << "Missing a particle charge column in " << filename << ". Please provide one via:" << endl;
                        cout << keyword << "index x y z diameter charge species" << endl;
                        return false;
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
        if(verbose){
            cout << "Number of particles deviates from expected number: ";
            cout << particleIn.size() << " != " << numberOfParticles << endl;
        }
        return false;
    }
    setParticleList(particleIn);
    return true;
}

void CONFINED_BROWNIAN_PARTICLES::setParticleList(vector<CHARGED_PARTICLE> particleListIn){
    particles = particleListIn;
    numberOfParticles = particleListIn.size();
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
        REAL_C positionDifference = particles[i].boxPosition - previousParticles[i].boxPosition;
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
        layerNumber = layers.tellLayerNumber(previousParticles[i]);
        meanLayerVelocities[layerNumber] += velocities[i];
        counter[layerNumber]++;
    }
    for(int j = 0; j < numberOfLayers; j++){
        meanLayerVelocities[j] /= counter[j];
    }
    return meanLayerVelocities;
}

vector<REAL_C> CONFINED_BROWNIAN_PARTICLES::getMeanLayerPositions(){
    LAYERS layers(simBox);
    int numberOfLayers = layers.getNumberOfLayers();
    vector<REAL_C> meanLayerPositions(numberOfLayers);
    vector<int> counter(numberOfLayers);
    int layerNumber;
    for(int i = 0; i < numberOfParticles; i++){
        layerNumber = layers.tellLayerNumber(particles[i]);
        meanLayerPositions[layerNumber] += particles[i].position;
        counter[layerNumber]++;
    }
    for(int j = 0; j < numberOfLayers; j++){
        meanLayerPositions[j] /= counter[j];
    }
    return meanLayerPositions;
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

void CONFINED_BROWNIAN_PARTICLES::print(ostream& os) const{
    const char* fmt = "% .8e\t";
    os << "configurationIn: " << bo::format(fmt) % configurationIn << endl;
    os << "numberOfParticles: " << bo::format(fmt) % numberOfParticles << endl;
    os << "timestep: " << bo::format(fmt) % timestep << endl;
    os << "dt: " << bo::format(fmt) % dt << "[tB-1]" << endl;
    os << "kT: " << bo::format(fmt) % kT << "[kT]" << endl;
    os << "mu: " << bo::format(fmt) % mu << "[d2 tB-1 kT-1]";
}
