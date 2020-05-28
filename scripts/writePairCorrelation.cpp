//
// Created by mhuels on 5/20/20.
//
#include <iostream>
#include "boost/program_options.hpp"
#include "../src/systems/confined_brownian_particles.h"
#include "../src/order_parameter/pair_correlation.h"

using namespace std;
namespace po = boost::program_options;

int main(int argc, const char *argv[]){
    po::options_description description{"Options"};
    po::variables_map variablesMap;
    description.add_options()
            ("help,h", "Help screen")
            ("filename,i", po::value<string>(), "configuration file (particle positions)")
//            ("outname,o", po::value<string>()->default_value("pairCorrelation.out"), "filename of output file")
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
//    string outname = variablesMap["outname"].as<string>();
    
    cout << "#Generated from: " << filename << endl;
    
    CONFINED_BROWNIAN_PARTICLES sys;
    sys.readConfigurationFromFileOld(filename, false, false);
    PAIR_CORRELATION pairCorrelation(sys, 0.01);
    pairCorrelation.calculate();
    cout << pairCorrelation;
    return 0;
}