#include "confined_brownian_particles.h"

CONFINED_BROWNIAN_PARTICLES::CONFINED_BROWNIAN_PARTICLES()
{
    configurationDir = "brownian";
    D0=1.;
    T=0.;
}

void CONFINED_BROWNIAN_PARTICLES::printInitilization()
{
    cout << "Initialized System: "
         << configurationDir + "configuration" + app_identifier ( "" ) + ".txt"
         << endl
         << endl;
}

string CONFINED_BROWNIAN_PARTICLES::app_identifier ( string str )
{
    stringstream output;
    output << str;

    return output.str();
}

void CONFINED_BROWNIAN_PARTICLES::simulateForSteps ( int maxSteps )
{
    for ( int i = 0; i < maxSteps; ++i ) {
        equationOfMotion();
    }
}

void CONFINED_BROWNIAN_PARTICLES::equationOfMotion()
{
    calculateForce();
    CARTESIAN_COORDINATE randomForce;

    for ( int i = 0; i < particle.size(); ++i ) {
        randomForce = getRandomForce();

        particle[i].position += force[i] * D0 * dt / T + randomForce;

    }
    setPositionInBox();
}

void CONFINED_BROWNIAN_PARTICLES::calculateForce()
{
    reset();
    calculateForces.doForSystem ( *this );
//     for(int i = 0; i < particle.size(); ++i){
//         for(int j = i+1; j < particle.size(); ++j){
//             calculateInteractionForce ( i, j );
//         }
//         calculateExternalForce ( i );
//     }
}

void CONFINED_BROWNIAN_PARTICLES::reset()
{
   force.assign ( getNumberOfParticles(), CARTESIAN_COORDINATE ( 0. ) );
}


int CONFINED_BROWNIAN_PARTICLES::getNumberOfParticles()
{
    return particle.size();
}

CARTESIAN_COORDINATE CONFINED_BROWNIAN_PARTICLES::getRandomForce()
{
    return CARTESIAN_COORDINATE ( sqrt ( 2 * D0 * dt ) * boxmueller ( 0, 1 ),
                                   sqrt ( 2 * D0 * dt ) * boxmueller ( 0, 1 ),
                                   sqrt ( 2 * D0 * dt ) * boxmueller ( 0, 1 ) );
}

SLIT_PORE_BOX* CONFINED_BROWNIAN_PARTICLES::simulationBox()
{
    return &simBox;
}

vector< CHARGED_PARTICLE > CONFINED_BROWNIAN_PARTICLES::getParticleList()
{
    return particle;
}

vector< CARTESIAN_COORDINATE > CONFINED_BROWNIAN_PARTICLES::getPositionList()
{
    setPositionInBox();
    vector<CARTESIAN_COORDINATE> positionList ( particle.size() );

    for ( int i = 0; i < particle.size(); ++i ) {
        positionList[i] = particle[i].boxPosition;
    }

    return positionList;
}

void CONFINED_BROWNIAN_PARTICLES::setPositionInBox()
{
    for ( int i = 0; i < particle.size(); ++i ) {
        particle[i].setBoxPosition ( simBox );
    }
}

double CONFINED_BROWNIAN_PARTICLES::getInteractionLengthScale()
{
    return 1.;
}

void CONFINED_BROWNIAN_PARTICLES::calculateInteractionForce ( int i, int j )
{
    CARTESIAN_COORDINATE tmpForce = forceFromParticleOnParticle ( particle[i], particle[j] );
    force[i] += tmpForce;
    force[j] -= tmpForce;
}

void CONFINED_BROWNIAN_PARTICLES::calculateExternalForce ( int i )
{
    force[i] += forceOnParticleFromExternalFields ( particle[i] );
}

CARTESIAN_COORDINATE CONFINED_BROWNIAN_PARTICLES::forceFromParticleOnParticle ( CHARGED_PARTICLE& particle1, CHARGED_PARTICLE& particle2 )
{
    return CARTESIAN_COORDINATE ( 0. );
}

double CONFINED_BROWNIAN_PARTICLES::energyFromParticleOnParticle ( CHARGED_PARTICLE& particle1, CHARGED_PARTICLE& particle2 )
{
    return 0.;
}

CARTESIAN_COORDINATE CONFINED_BROWNIAN_PARTICLES::forceOnParticleFromExternalFields ( CHARGED_PARTICLE& particle )
{
    return CARTESIAN_COORDINATE ( 0. );
}

double CONFINED_BROWNIAN_PARTICLES::energyOfParticleFromExternalFields ( CHARGED_PARTICLE& particle )
{
    return 0.;
}

double CONFINED_BROWNIAN_PARTICLES::getTimeStepSize()
{
    return dt;
}

void CONFINED_BROWNIAN_PARTICLES::printSystem ( string str )
{
    string outputString =  "configuration_" + str + app_identifier ( "" );
    printParticlesOfSystem ( outputString );
}

void CONFINED_BROWNIAN_PARTICLES::printSystem()
{
    string outputString =  "configuration" + app_identifier ( "" );
    printParticlesOfSystem ( outputString );
}

void CONFINED_BROWNIAN_PARTICLES::printParticlesOfSystem ( string str )
{
    PRINTER printer(configurationDir, str);
    printer.removeFile();
    for(int i = 0; i < particle.size(); ++i){
        printer.printLine( particle[i].position.x, particle[i].position.y, particle[i].position.z, particle[i].boxPosition.x, particle[i].boxPosition.y, particle[i].species );
    }
}

void CONFINED_BROWNIAN_PARTICLES::read ( string str )
{
    string inputString = configurationDir + "configuration_" + str + app_identifier( "" ) + ".txt";
    readFromString( inputString );
    printInitilization();
}

void CONFINED_BROWNIAN_PARTICLES::read()
{
   string inputString = configurationDir + "configuration" + app_identifier( "" ) + ".txt";
    readFromString( inputString );
    printInitilization();
}

void CONFINED_BROWNIAN_PARTICLES::readFromString ( string str )
{
    cout << "CONFINED_BROWNIAN_PARTICLES::readFromString is empty!" << endl;
}

void CONFINED_BROWNIAN_PARTICLES::setParticleList ( vector< CHARGED_PARTICLE > particleListIn )
{
    particle = particleListIn;
}

SLIT_PORE_BOX CONFINED_BROWNIAN_PARTICLES::getSimulationBox()
{
    return simBox;
}

void CONFINED_BROWNIAN_PARTICLES::setTimeStepSize ( double timeStepSizeIn )
{
    cout << "Set dt = " << dt << " to " << timeStepSizeIn << endl;
    dt = timeStepSizeIn;
}




