//
// Created by mhuels on 8/10/20.
//

#include <iostream>
#include "boost/program_options.hpp"
#include "../src/systems/confined_brownian_particles.h"

using namespace std;
namespace po = boost::program_options;

int main(int argc, const char *argv[]){
    po::options_description description{"Options"};
    po::variables_map variablesMap;
    description.add_options()
            ("help,h", "Help screen")
            ("filename,i", po::value<string>(), "configuration file (particle positions)")
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
    
    cout << filename << endl;
    
    CONFINED_BROWNIAN_PARTICLES sys;
    
}