#include "sheared_slitpore_system.h"

SHEARED_SLITPORE_SYSTEM::SHEARED_SLITPORE_SYSTEM(){
    dt = 1e-5;
    T=1.;
    STRESS = false;
    ENERGY = false;
}

SHEARED_SLITPORE_SYSTEM::SHEARED_SLITPORE_SYSTEM(SHEARED_SLITPORE_PARAMETERS& sPin){
    dt = 1e-5;
    T=1.;
    STRESS = false;
    ENERGY = false;
    setSystemParameters(sPin);
    printInitilization();
}

void SHEARED_SLITPORE_SYSTEM::setSystemParameters(SHEARED_SLITPORE_PARAMETERS& sPin){
    setShearRate(sPin.shearRate);

    density = sPin.density;
    simBox.setDwall(sPin.dWall);
    setNumberOfParticles(sPin.numberOfParticles); //also sets volume, dimensions X and Y (Z is set by dWall)

    charge = sPin.charge;
    diameter = sPin.diameter;
    setSoftWallInteraction(sPin.wallInteractionStrength);

    sysIdentifierString = sPin.sysIdentifierString;

    configurationDir = "config/";
    read();

    setDlvoSSInteraction(sPin.ssInteractionStrength);

    reset();
}

void SHEARED_SLITPORE_SYSTEM::setShearRate(double shearRateIn){
    shearForce.setShearRate(shearRateIn);
    shearForce.setDirection(CARTESIAN_COORDINATE(1.,0.,0.));
}

void SHEARED_SLITPORE_SYSTEM::setSoftWallInteraction(double softWallStrengthIn){
    swf.setInteractionParameters(simBox.getDimensions().z, softWallStrengthIn);
}

void SHEARED_SLITPORE_SYSTEM::setDlvoSSInteraction(double ssInteractionStrengthIn){
    dlvo.setRcDelta(simBox.getDimensions().x);
    dlvo.ssInteractionStrength = ssInteractionStrengthIn;

    vector<int> charges(1,charge);
    vector<double> diameters(1,diameter);
    vector<double> densities(1, density);

    dlvo.setInteractionParameters(charges, diameters, densities);
}

double SHEARED_SLITPORE_SYSTEM::getInteractionLengthScale(){
    return dlvo.getMaxCutOffRadius();
}

//reset forces, stresses and energy
void SHEARED_SLITPORE_SYSTEM::reset(){
    force.assign(getNumberOfParticles(), CARTESIAN_COORDINATE(0.));

    if(STRESS){
        stressPerParticle.assign(getNumberOfParticles(), CARTESIAN_MATRIX(0.));
    }
    
    if(ENERGY) {
        energy.assign(getNumberOfParticles(), 0.);
    }
}

void SHEARED_SLITPORE_SYSTEM::setNumberOfParticles(int numberOfParticlesIn){
    particle.resize(numberOfParticlesIn);
    simBox.setVolumeAndDWall(numberOfParticlesIn / density, simBox.getDimensions().z);
}

void SHEARED_SLITPORE_SYSTEM::readFromString(string str){
    ifstream f;
    f.open(str.c_str());

    vector<CHARGED_PARTICLE> particleIn;
    particleIn.clear();

    double c1, c2, c3, c4, c5, c6;
    CHARGED_PARTICLE newParticle;

    while(f >> c1 >> c2 >> c3 >> c4 >> c5 >> c6){
        switch(read_toggle){
        case 0:
            newParticle.position = CARTESIAN_COORDINATE(c4, c5, c3);
            break;

        case 1:
            newParticle.position = CARTESIAN_COORDINATE(c1, c2, c3);
            break;
        }
        newParticle.species = c6;

        particleIn.push_back(newParticle);
    }

    if(particleIn.size() <= 0){
        setInitialConfigurationForLayersWithSides(getNumberOfParticles());
    }
    else{
        if(particleIn.size() != getNumberOfParticles()){
            cout << "Read in configuration number of particles deviates from expected number: "
                 << particleIn.size() << " != " << getNumberOfParticles() << endl;
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

    CARTESIAN_COORDINATE randomForce;
    CARTESIAN_COORDINATE shearForce;

    for(int i = 0; i < particle.size(); ++i){
        randomForce = getRandomForce();
        shearForce = getShearForce(i);

        particle[i].position += force[i] * D0 * dt / T + randomForce + shearForce;

        if(particle[i].position.z > 0.5 * simBox.getDimensions().z || particle[i].position.z < -0.5 * simBox.getDimensions().z){
            cout << "particle[i].position.z = " << particle[i].position.z << endl;

            particle[i].setBoxPosition(simBox);
        }
    }

}

CARTESIAN_COORDINATE SHEARED_SLITPORE_SYSTEM::getShearForce(int index){
    return shearForce.forceOnParticle(particle[index]) * dt;
}

string SHEARED_SLITPORE_SYSTEM::app_identifier(string str){
    stringstream output;
    output << str;

    output << "_shear_" << shearForce.getShearRate()
           << app_incomplete_identifier(str);

    return output.str();
}

string SHEARED_SLITPORE_SYSTEM::app_incomplete_identifier(string str){
    stringstream output;
    output << str;

    output << "__Dwall_" << simBox.getDimensions().z
           << "_L_" << simBox.getDimensions().x
           << "_rho_" << density
           << "_N_" << getNumberOfParticles()
           << "_Wforce_" << "-0"
           << "_Zp_" << charge;

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

void SHEARED_SLITPORE_SYSTEM::setParticleList(vector< CHARGED_PARTICLE > particleListIn){
    particle = particleListIn; //copy particleList
    for(int i = 0; i < particle.size(); ++i){ //add some more info to each particle
        particle[i].diameter = diameter;
        particle[i].charge = charge;
        particle[i].species = 0;
    }

    simBox.setVolumeAndDWall(getNumberOfParticles() / density, simBox.getDimensions().z);
    setDlvoSSInteraction(dlvo.ssInteractionStrength);
    setPositionInBox();

}

void SHEARED_SLITPORE_SYSTEM::calculateInteractionForce(int i, int j){
    CARTESIAN_COORDINATE tmpForce = forceFromParticleOnParticle(particle[i], particle[j]);
    force[i] += tmpForce;
    force[j] -= tmpForce;

    if(STRESS){
        addConfigurationalStress(tmpForce, i, j);
    }
    if(ENERGY){
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

    if(STRESS){
        addExternalStress(tmpForce, i);
    }
    
    if(ENERGY) {
        energy[i] += energyOfParticleFromExternalFields(particle[i]);
    }
}

void SHEARED_SLITPORE_SYSTEM::addExternalStress(CARTESIAN_COORDINATE forceIn, int i){
    CARTESIAN_MATRIX tmpStress(0.);

    if(particle[i].position.z >= 0){
        tmpStress.zz += forceIn.z *(particle[i].position.z - 0.5 * simBox.getDimensions().z);
    }
    else{
        tmpStress.zz += forceIn.z *(particle[i].position.z + 0.5 * simBox.getDimensions().z);
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

void SHEARED_SLITPORE_SYSTEM::readEnsembleSystem(int ensembleIndex){
    string inputString = app_home("") + "config_ensemble/ensemble_" + app_incomplete_identifier("")
                         + "/shear_" + app_number("", shearForce.getShearRate())
                         + "/configuration" + app_identifier("") + "_ens_" + app_number("", ensembleIndex) + ".txt";
    cout << inputString << endl;
    readFromString(inputString);
}

void SHEARED_SLITPORE_SYSTEM::printSystemWithEnsembleIndex(int ensembleIndex){
    string dir = app_home("") + "config_ensemble/ensemble_" + app_incomplete_identifier("") + "/shear_"+ app_number("", shearForce.getShearRate()) ;
    string cmd = "mkdir -p " + dir;
    system(cmd.c_str());
    string outputString = dir + "/configuration"+ app_identifier("") + "_ens_" + app_number("",ensembleIndex) + ".txt";
     
    printParticlesOfSystem(outputString);
}

double SHEARED_SLITPORE_SYSTEM::getShearRate(){
    return shearForce.getShearRate();
}

void SHEARED_SLITPORE_SYSTEM::convertPositionToBoxPosition(){
    for(int i = 0; i < particle.size(); ++i){
	particle[i].position = particle[i].boxPosition;
    }
}

string SHEARED_SLITPORE_SYSTEM::getIdentifierString(){
    return sysIdentifierString;
}

vector<double> SHEARED_SLITPORE_SYSTEM::getEnergyPerParticle(){
    return energy;
}

