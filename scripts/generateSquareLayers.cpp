//
// Created by mhuels on 8/10/20.
//

#include <iostream>
#include "boost/program_options.hpp"
#include "../src/systems/confined_brownian_particles.h"
#include "../src/defaults.h"

using namespace std;
namespace po = boost::program_options;

int main(int argc, const char *argv[]){
    po::options_description description{"Options"};
    po::variables_map variablesMap;
    description.add_options()
            ("help,h", "Help screen")
            ("filename,i", po::value<string>(), "configuration file (particle positions)")
            ("dWall", po::value<double>()->default_value(D_WALL), "distance between walls (in units of particle diameter)")
            ("density", po::value<double>()->default_value(DENSITY), "particle density (in 1/diameter^3)")
            ("N", po::value<int>()->default_value(NUMBER_OF_PARTICLES), "number of particles")
            ;
    po::positional_options_description pos;
    pos.add("filename", 1);
    po::store(po::command_line_parser(argc, argv).options(description).positional(pos).run(), variablesMap);
    po::notify(variablesMap);
    if(variablesMap.count("help")){
        cout << description << endl;
        exit(0);
    }
    
    string filename = variablesMap["filename"].as<string>();
    
    CONFINED_BROWNIAN_PARTICLES sys;
    sys.setInitialConfigurationForLayersWithSides();
    sys.writeConfigurationToFile(filename, true);
    
}