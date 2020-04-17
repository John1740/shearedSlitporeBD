#include "sheared_slitpore_system.h"

SHEARED_SLITPORE_SYSTEM::SHEARED_SLITPORE_SYSTEM(){
    configurationDir = "config/";

    prepareSystem();
}

SHEARED_SLITPORE_SYSTEM::SHEARED_SLITPORE_SYSTEM(const ARGUMENTS& args) : CONFINED_BROWNIAN_PARTICLES(args){
    configurationDir = "config/"; //deprecated
    configurationIn = args.configurationIn;

    density = args.density;
    dWall = args.dWall;

    printStress = args.printStress;
    printEnergy = args.printEnergy;

    shearForce = SHEAR_FORCE(args.shearRate);
    swf = SOFT_WALL_FORCE(args);
    dlvo = DLVO_SOFTSPHERE_INTERACTION(args);

    prepareSystem();
}

//needs to be done after input variables have been changed
void SHEARED_SLITPORE_SYSTEM::prepareSystem(){
    particle.resize(numberOfParticles);
    simBox = SLIT_PORE_BOX(numberOfParticles / density, dWall);

    //update lengthRange and then invoke all following setup calculations again
    dlvo.lengthRange = simBox.getDimensions().x;
    dlvo.calculateInteractionParameters();    //needs to be done anew since lengthRange changed

    readConfiguration(configurationIn); //reads (or creates) particle positions

    reset();
}

double SHEARED_SLITPORE_SYSTEM::getInteractionLengthScale(){
    return dlvo.cutOffRadius;
}

//reset forces, stresses and energy
void SHEARED_SLITPORE_SYSTEM::reset(){
    force.assign(numberOfParticles, CARTESIAN_COORDINATE(0.));

    if(printStress){
        stressPerParticle.assign(numberOfParticles, CARTESIAN_MATRIX(0.));
    }

    if(printEnergy){
        energy.assign(numberOfParticles, 0.);
    }
}

void SHEARED_SLITPORE_SYSTEM::readConfigurationFromString(string str){
    ifstream f;
    f.open(str.c_str());

    vector<CHARGED_PARTICLE> particleIn;
    particleIn.clear();

    double c1, c2, c3, c4, c5, c6;
    CHARGED_PARTICLE newParticle;

    while(f >> c1 >> c2 >> c3 >> c4 >> c5 >> c6){
        switch(read_toggle){
        case 0:
            newParticle.position = CARTESIAN_COORDINATE(c4, c5, c6);
            break;

        case 1:
            newParticle.position = CARTESIAN_COORDINATE(c1, c2, c3);
            break;
        }
        particleIn.push_back(newParticle);
    }

    if(particleIn.size() <= 0){
        cout << configurationIn << " is either empty or does not exist!" << endl;
        setInitialConfigurationForLayersWithSides(numberOfParticles);
        printConfigurationToFile(configurationIn);
        cout << "Set initial configuration and printed to: " << configurationIn << endl;
    }
    else{
        if(particleIn.size() != numberOfParticles){
            cout << "Read in configuration number of particles deviates from expected number: ";
            cout << particleIn.size() << " != " << numberOfParticles << endl;
        }
        setParticleList(particleIn);
    }

}

void SHEARED_SLITPORE_SYSTEM::setInitialConfigurationForLayersWithSides(int numberOfParticlesIn){
    int numberOfLayers = round(simBox.getDimensions().z);
    int numberOfSides = sqrt(numberOfParticlesIn / numberOfLayers);

    cout << "Set particle positions to " << numberOfLayers << " quadratic layers with " << numberOfSides << " sides!" << endl;

    GENERATE_SQUARE_LAYERS initialConfiguration;
    initialConfiguration.setNumberOfLayersRowsAdditionalRows(numberOfLayers, numberOfSides, 0);
    initialConfiguration.doForSystem(*this);
}

void SHEARED_SLITPORE_SYSTEM::equationOfMotion(){
    // Force calculation
    calculateForce();

    CARTESIAN_COORDINATE randomDisplacement;
    CARTESIAN_COORDINATE shearForce;

    for(int i = 0; i < particle.size(); ++i){
        randomDisplacement = getRandomDisplacement();
        shearForce = getShearForce(i);

        particle[i].position += force[i] * D0 * dt / T + randomDisplacement + shearForce * dt;

        if(particle[i].position.z > 0.5 * simBox.getDimensions().z || particle[i].position.z < -0.5 * simBox.getDimensions().z){
            cout << "particle[i].position.z = " << particle[i].position.z << endl;
        }
        particle[i].setBoxPosition(simBox);
    }
}

CARTESIAN_COORDINATE SHEARED_SLITPORE_SYSTEM::getShearForce(int index){
    return shearForce.forceOnParticle(particle[index]);
}

string SHEARED_SLITPORE_SYSTEM::app_identifier(string str){
    stringstream output;
    output << str;

    output << "_shear_" << shearForce.shearRate;
    output << app_incomplete_identifier(str);

    return output.str();
}

string SHEARED_SLITPORE_SYSTEM::app_incomplete_identifier(string str){
    stringstream output;
    output << str;

    output << "__Dwall_" << simBox.getDimensions().z;
    output << "_L_" << simBox.getDimensions().x;
    output << "_rho_" << density;
    output << "_N_" << numberOfParticles;
    output << "_Wforce_" << "-0";
    output << "_Zp_" << dlvo.charge1;

    return output.str();
}

CARTESIAN_COORDINATE SHEARED_SLITPORE_SYSTEM::forceFromParticleOnParticle(CHARGED_PARTICLE& particle1, CHARGED_PARTICLE& particle2){
    return dlvo.forceOnParticleFromParticle(particle1, particle2, simBox);
}

CARTESIAN_COORDINATE SHEARED_SLITPORE_SYSTEM::forceOnParticleFromExternalFields(CHARGED_PARTICLE& particle){
    return swf.forceOnParticle(particle);
}

double SHEARED_SLITPORE_SYSTEM::energyFromParticleOnParticle(CHARGED_PARTICLE& particle1, CHARGED_PARTICLE& particle2){
    return dlvo.energyOnParticleFromParticle(particle1, particle2, simBox);
}

double SHEARED_SLITPORE_SYSTEM::energyOfParticleFromExternalFields(CHARGED_PARTICLE& particle){
    return swf.energyOnParticle(particle);
}

void SHEARED_SLITPORE_SYSTEM::setParticleList(vector<CHARGED_PARTICLE> particleListIn){
    particle = particleListIn; //copy particleList
    for(int i = 0; i < numberOfParticles; ++i){ //add some more info to each particle
        particle[i].diameter = swf.diameter;
        particle[i].charge = dlvo.charge1;
    }

    setPositionInBox();

}

void SHEARED_SLITPORE_SYSTEM::calculateInteractionForce(int i, int j){
    CARTESIAN_COORDINATE tmpForce = forceFromParticleOnParticle(particle[i], particle[j]);
    force[i] += tmpForce;
    force[j] -= tmpForce;

    if(printStress){ //move somewhere else?
        addConfigurationalStress(tmpForce, i, j);
    }
    if(printEnergy){
        double tmpEnergy = energyFromParticleOnParticle(particle[i],particle[j]);
        energy[i] += tmpEnergy;
        energy[j] += tmpEnergy;
    }
}

void SHEARED_SLITPORE_SYSTEM::addConfigurationalStress(CARTESIAN_COORDINATE forceIn, int i, int j){
    CARTESIAN_COORDINATE posDifference = particle[i].boxPosition - particle[j].boxPosition;
    posDifference = simBox.convertToBoxPosition(posDifference);
    CARTESIAN_MATRIX tmpStress(posDifference, forceIn);
    stressPerParticle[i] += 0.5* tmpStress;
    stressPerParticle[j] += 0.5* tmpStress;
}

void SHEARED_SLITPORE_SYSTEM::calculateExternalForce(int i){
    CARTESIAN_COORDINATE tmpForce = forceOnParticleFromExternalFields(particle[i]);
    force[i] += tmpForce;

    if(printStress){
        addExternalStress(tmpForce, i);
    }

    if(printEnergy){
        energy[i] += energyOfParticleFromExternalFields(particle[i]);
    }
}

void SHEARED_SLITPORE_SYSTEM::addExternalStress(const CARTESIAN_COORDINATE& forceIn, int i){   //const CARTESIAN_COORDINATE&
    CARTESIAN_MATRIX tmpStress(0.);

    if(particle[i].position.z >= 0){
        tmpStress.zz += forceIn.z * (particle[i].position.z - 0.5 * simBox.getDimensions().z);
    }
    else{
        tmpStress.zz += forceIn.z * (particle[i].position.z + 0.5 * simBox.getDimensions().z);
    }

    stressPerParticle[i] += tmpStress;
}

vector< CARTESIAN_MATRIX > SHEARED_SLITPORE_SYSTEM::getStressPerParticle(){
    vector<CARTESIAN_MATRIX> tmp = stressPerParticle;
    for(int i = 0; i < tmp.size(); ++i){
        tmp[i] *= -1/simBox.getVolume();
    }
    return tmp;
}

CARTESIAN_MATRIX SHEARED_SLITPORE_SYSTEM::getMeanStress(){
    CARTESIAN_MATRIX meanStress(0.);
    for(int i = 0; i < stressPerParticle.size(); ++i){
        meanStress += stressPerParticle[i];
    }
    return -1.*meanStress/simBox.getVolume();
}

//void SHEARED_SLITPORE_SYSTEM::readEnsembleSystem(int ensembleIndex){
//    string inputString = app_home("") + "config_ensemble/ensemble_" + app_incomplete_identifier("")
//                         + "/shear_" + app_number("", shearForce.shearRate)
//                         + "/configuration" + app_identifier("") + "_ens_" + app_number("", ensembleIndex) + ".txt";
//    cout << inputString << endl;
//    readConfigurationFromString(inputString);
//}

void SHEARED_SLITPORE_SYSTEM::printSystemWithEnsembleIndex(int ensembleIndex){
    string dir = app_home("") + "config_ensemble/ensemble_" + app_incomplete_identifier("") + "/shear_"+ app_number("", shearForce.shearRate) ;
    string cmd = "mkdir -p " + dir;
    system(cmd.c_str());
    string outputString = dir + "/configuration"+ app_identifier("") + "_ens_" + app_number("",ensembleIndex) + ".txt";

    printParticlesOfSystem(outputString);
}

void SHEARED_SLITPORE_SYSTEM::convertPositionToBoxPosition(){
    for(int i = 0; i < particle.size(); ++i){
        particle[i].position = particle[i].boxPosition;
    }
}

//string SHEARED_SLITPORE_SYSTEM::getIdentifierString(){
//    return sysIdentifierString;
//}

vector<double> SHEARED_SLITPORE_SYSTEM::getEnergyPerParticle(){
    return energy;
}

