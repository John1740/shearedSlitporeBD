//
// Created by mhuels on 8/10/20.
//

#include <iostream>
#include "boost/program_options.hpp"
#include "../src/command/generate_square_layers.h"
#include "../src/systems/confined_brownian_particles.h"
#include "../src/defaults.h"

using namespace std;
namespace po = boost::program_options;

int main(int argc, const char *argv[]){
    po::options_description description{"Options"};
    po::variables_map vm;
    description.add_options()
            ("help,h", "Help screen")
            ("filename,o", po::value<string>(), "output configuration filename")
            ("dry,n", po::bool_switch()->default_value(false), "dry run")
            ("dWall", po::value<double>()->default_value(D_WALL), "distance between walls (in units of particle diameter)")
            ("density", po::value<double>()->default_value(DENSITY), "particle density (in 1/diameter^3)")
            ("N,N", po::value<int>()->default_value(NUMBER_OF_PARTICLES), "number of particles")
            ("charge", po::value<double>()->default_value(CHARGE), "charge of particles")
            ("diameter", po::value<double>()->default_value(DIAMETER), "diameter of particles")
            ("species", po::value<int>()->default_value(0), "species number of particles")
            ;
    po::positional_options_description pos;
    pos.add("filename", 1);
    po::store(po::command_line_parser(argc, argv).options(description).positional(pos).run(), vm);
    po::notify(vm);
    if(vm.count("help")){
        cout << description << endl;
        exit(0);
    }
    
    string filename = vm["filename"].as<string>();

    GENERATE_SQUARE_LAYERS gen(vm["N"].as<int>(), vm["dWall"].as<double>(), vm["density"].as<double>());

    cout << "Generating a square-layer configuration with" << endl;
    cout << "numberOfParticles: " << vm["N"].as<int>() << " -> " << gen.getNumberOfParticles() << endl;
    cout << "density: " << vm["density"].as<double>() << " [diameters^-3]" << endl;
    cout << "dWall: " << vm["dWall"].as<double>() << " [diameters]" << endl << endl;

    gen.setParticleProperties(vm["charge"].as<double>(), vm["diameter"].as<double>(), vm["species"].as<int>());
    cout << "Simulation box:" << endl;
    cout << gen.getSimBox() << endl;
    cout << "Particle template: " << endl;
    cout << gen.getParticleTemplate() << endl << endl;
    CONFINED_BROWNIAN_PARTICLES sys = gen.generate();
    cout << gen << endl;
    if(!vm["dry"].as<bool>()){
        sys.writeConfigurationToFile(filename, true);
    }
    else{
        cout << "Dry run. Remove the -n (or --dry) option to do an actual run!" << endl;
    }
    
}