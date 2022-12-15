#include <iostream>
#include "boost/program_options.hpp"
#include "../src/command/generate_hexagonal_layers.h"
#include "../src/command/generate_square_layers.h"
#include "../src/command/generate_random_layers.h"
#include <time.h>
#include <stdlib.h>
#include "../src/systems/sheared_slitpore_system.h"
#include <math.h>
#include "../src/printer/printer.h"
#include "../src/printer/angular_bond.h"
#include "../src/order_parameter/particle_angular_bond.h"
#include "../src/order_parameter/intra_layer_pair_correlation_function.h"
#include "../src/order_parameter/intra_layer_pair_correlation_function.cpp"
#include <csignal>


using namespace std;
namespace po = boost::program_options;
volatile int exit_code = 0;

void signalHandler(int signum){
    cout << endl << "Interrupt signal (" << signum << ") received." << endl;
    exit_code = signum;
}



int main(int argc, const char* argv[]){
    //signals that should shut down the simulation (controlledly)
    signal(SIGINT, signalHandler);  //keyboard interrupt (Ctrl+C in terminal)
    signal(SIGTERM, signalHandler); //terminate (used by pbspro for example)
    signal(SIGUSR1, signalHandler); //user-defined signal (job suspension on math cluster)
    signal(SIGUSR2, signalHandler); //user-defined signal (notification before SIGKILL on math cluster)
    signal(SIGKILL, signalHandler); //kill (this error cannot be caught usually)

    po::options_description description{"Options"};
    po::variables_map vm;
    description.add_options()
            ("help,h", "Help screen")
            ("filename,o", po::value<string>()->default_value("MCsimulation.out"), "output configuration filename")
            ("dry,n", po::bool_switch()->default_value(false), "dry run")
            ("dWall", po::value<double>()->default_value(D_WALL),
             "distance between walls (in units of particle diameter)")
            ("density", po::value<double>()->default_value(DENSITY), "particle density (in 1/diameter^3)")
            ("N,N", po::value<int>()->default_value(NUMBER_OF_PARTICLES), "number of particles")
            ("steps", po::value<int>()->default_value(10000), "number of MC Steps")
            ("charge", po::value<double>()->default_value(CHARGE), "charge of particles")
            ("diameter", po::value<double>()->default_value(DIAMETER), "diameter of particles")
            ("species", po::value<int>()->default_value(0), "species number of particles")
            ("structure", po::value<string>()->default_value("square"),
             "set to square, hexagonal or random to change initial configuration")
            ("printObservables", po::value<int>()->default_value(0), "set to n>0 to print Observables every nth step")
            ("dStep", po::value<double>()->default_value(0.1), "set maximum step distance in diameters")
            ("accRateSteps", po::value<int>()->default_value(0), "number of steps acceptance rate is printed");
    po::positional_options_description pos;
    pos.add("filename", 1);
    po::store(po::command_line_parser(argc, argv).options(description).positional(pos).run(), vm);
    po::notify(vm);
    if(vm.count("help")){
        cout << description << endl;
        exit(0);
    }
    std::ofstream acceptanceRate("acceptanceRate.out");
    std::ofstream systemEnergyFile("systemEnergy.out");

    string filename = vm["filename"].as<string>();
    int printO = vm["printObservables"].as<int>();

    // Class to calculate Particle Positions at given parameters

    int steps = vm["steps"].as<int>();
    int acceptanceRateSteps =  vm["accRateSteps"].as<int>();
    double ds = vm["dStep"].as<double>();
    int minRandomABStep=100000;
    std::string structure= vm["structure"].as<string>();


    SHEARED_SLITPORE_SYSTEM sys;

    if(structure == "random"){
        GENERATE_RANDOM_LAYERS gen(vm["N"].as<int>(), vm["dWall"].as<double>(), vm["density"].as<double>());
        gen.setParticleProperties(vm["charge"].as<double>(), vm["diameter"].as<double>(), vm["species"].as<int>());
        sys=gen.generate();
    }

    if(structure == "square"){
        GENERATE_SQUARE_LAYERS gen(vm["N"].as<int>(), vm["dWall"].as<double>(), vm["density"].as<double>());
        gen.setParticleProperties(vm["charge"].as<double>(), vm["diameter"].as<double>(), vm["species"].as<int>());
        sys=gen.generate();
    }

    if(structure == "hexagonal"){
        GENERATE_HEXAGONAL_LAYERS gen(vm["N"].as<int>(), vm["dWall"].as<double>(), vm["density"].as<double>());
        gen.setParticleProperties(vm["charge"].as<double>(), vm["diameter"].as<double>(), vm["species"].as<int>());
        sys=gen.generate();
    }

    sys.setSWF(WALL_INTERACTION_STRENGTH,sys.getDimentionsOfSymbox().z);
    sys.setDLVO(SS_INTERACTION_STRENGTH,Y_INTERACTION_STRENGTH,KAPPA);
    ANGULAR_BOND_PRINTER angularBond(&sys);
    sys.printEnergy=1;
    double systemEnergy=sys.getSystemEnergy();


    double energy1;
    double energy2;

    double xDisplacement;
    double yDisplacement;
    double zDisplacement;
    double zDim = sys.getDimentionsOfSymbox().z;
    int r;
    double p;
    double randomNumber;
    int acceptedCounter = 0;
    int rejectedCounter = 0;

    srand(time(NULL));

    int numberOfParticles = sys.getNumberOfParticles();
    for(int i = 0; i < steps; ++i){
        if(exit_code != 0){
            break;
        }
        sys.setTimestep(i);
        r = rand() % numberOfParticles;
        energy1 = sys.getEnergyForParticle(r);
        xDisplacement = (double)rand() / (double)RAND_MAX * 2 * ds - ds;
        yDisplacement = (double)rand() / (double)RAND_MAX * 2 * ds - ds;
        zDisplacement = (double)rand() / (double)RAND_MAX * 2 * ds - ds;
        REAL_C pos = sys.getParticlePosition(r);

        if(abs(pos.z + zDisplacement) > zDim * 0.5){
            continue;
        }

        sys.shiftParticle(r, xDisplacement, yDisplacement, zDisplacement);
        energy2 = sys.getEnergyForParticle(r);


        if(energy2 > energy1){
            p = exp(-(energy2 - energy1));
            randomNumber = ((double)rand() / (RAND_MAX));
            if(randomNumber > p){
                sys.shiftParticle(r, -xDisplacement, -yDisplacement, -zDisplacement);
                rejectedCounter++;
            }
            else{
                acceptedCounter++;
                systemEnergy+=energy2 - energy1;
            }
        }
        else{
            acceptedCounter++;
            systemEnergy+=energy2 - energy1;
        }

        if(i == minRandomABStep && structure == "random"){
            systemEnergy = sys.getSystemEnergy();
        }

        if(printO > 0 && i % printO == 0 ){

            sys.writeConfigurationToFile("snapshots.out", false, false);


            if(i >= minRandomABStep || structure != "random"){
                angularBond.printLine();
                systemEnergyFile << i << ": " << systemEnergy << endl;
            }

            if(acceptanceRateSteps > 0 && i > 0 && i % acceptanceRateSteps == 0){

                acceptanceRate << "acceptence rate over last " << acceptanceRateSteps << "steps: "
                               << double(acceptedCounter) / double(rejectedCounter + acceptedCounter) << endl;
            }
        }
    }

    sys.writeConfigurationToFile(filename, true, false);
    systemEnergyFile << "final"<< ": " << systemEnergy << endl;
    systemEnergy=sys.getSystemEnergy();
    systemEnergyFile << "debug"<< ": " << systemEnergy << endl;
    if(steps>=minRandomABStep|| structure!="random"){
        angularBond.printLine();
    }

}