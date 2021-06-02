//
// Created by mhuels on 4/7/20.
//

#ifndef SHEAREDSLITPOREBD_ARGPARSE_H
#define SHEAREDSLITPOREBD_ARGPARSE_H

#include "boost/program_options.hpp"
#include "arguments.h"

namespace po = boost::program_options;

class ARGUMENT_PARSER{
private:
    po::options_description options{"Brownian Dynamics Simulation with oscillatory (cos) shear protocol\n"
                                    "Options"};
    po::options_description main{"Main control parameters"};
    po::options_description secondary{"Secondary control parameters"};
    po::options_description numerical{"Numerical parameters"};
    po::options_description observables{"Observables"};
    po::variables_map variablesMap;

    void addOptions();

public:
    ARGUMENT_PARSER(int argc, const char* argv[]);

    ARGUMENTS parseArgs();
};

#endif //SHEAREDSLITPOREBD_ARGPARSE_H
