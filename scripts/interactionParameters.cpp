//
// Created by mhuels on 5/31/21.
//

#include <iostream>
#include "boost/program_options.hpp"
#include "../src/interactions/dlvo_softsphere_interaction.h"

using namespace std;
namespace po = boost::program_options;

int main(int argc, const char* argv[]){
    po::options_description description{"Options"};
    po::variables_map variablesMap;
    description.add_options()
            ("help,h", "Help screen")
            ("dr", po::value<double>(), "resolution dr");
    po::store(parse_command_line(argc, argv, description), variablesMap);
    po::notify(variablesMap);
    if(variablesMap.count("help")){
        cout << description << endl;
        exit(0);
    }

    DLVO_SOFTSPHERE_INTERACTION dlvo;
    double kappa = dlvo.calculateKappa();
    dlvo.calculateInteractionStrength(kappa);
    cout << dlvo << endl;
    return 0;
}