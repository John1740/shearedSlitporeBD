//
// Created by mhuels on 4/7/20.
//

#ifndef SHEAREDSLITPOREBD_ARGPARSE_H
#define SHEAREDSLITPOREBD_ARGPARSE_H

#include <iostream>
#include "boost/program_options.hpp"
#include "arguments.h"

namespace po = boost::program_options;
using namespace std;

class ARGUMENT_PARSER{
private:
    po::options_description description{"Brownian Dynamics Simulation with oscillatory (cos) shear protocol\n"
                                        "Options:"};
    po::variables_map variablesMap;
    void addOptions();

public:
    ARGUMENT_PARSER(int argc, const char* argv[]);

    ARGUMENTS parseArgs();
};

#endif //SHEAREDSLITPOREBD_ARGPARSE_H
