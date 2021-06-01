//
// Created by mhuels on 6/1/21.
//

#include <iostream>
#include "boost/program_options.hpp"
#include "../src/interactions/dlvo_softsphere_interaction.h"
#include <boost/format.hpp>

using namespace std;
namespace po = boost::program_options;
namespace bo = boost;

int main(int argc, const char* argv[]){
    po::options_description options{"A quick script that prints the DLVO interaction potential and forces in their raw "
                                    "and shifted form"};
    po::options_description primary{"Primary options"};
    po::variables_map vm;
    primary.add_options()
            ("help,h", "Help screen")
            ("diameter,d", po::value<double>()->default_value(DIAMETER),
                    "macroion diameter [d]")
            ("kappa", po::value<double>()->default_value(KAPPA),
                    "inverse Debye screening length of the Yukawa potential [d]")
            ("yInteractionStrength", po::value<double>()->default_value(Y_INTERACTION_STRENGTH),
                    "strength of screened-Coulomb Yukawa potential [kT]")
            ("ssInteractionStrength", po::value<double>()->default_value(SS_INTERACTION_STRENGTH),
             "strength of softsphere interaction [kT]")
            ;
    po::options_description secondary{"Secondary options"};
    secondary.add_options()
            ("rMax", po::value<double>()->default_value(10.),
                    "maximal radius [d]")
            ("numberOfPoints", po::value<int>()->default_value(1000),
                    "maximal radius [d]")
            ;
    options.add(primary).add(secondary);
    po::store(parse_command_line(argc, argv, options), vm);
    po::notify(vm);
    if(vm.count("help")){
        cout << options << endl;
        exit(0);
    }

    DLVO_SOFTSPHERE_INTERACTION dlvo(vm["diameter"].as<double>(),
                                     vm["ssInteractionStrength"].as<double>(),
                                     vm["yInteractionStrength"].as<double>(),
                                     vm["kappa"].as<double>());

    int numberOfPoints = vm["numberOfPoints"].as<int>();
    double rcDelta = vm["rMax"].as<double>() / numberOfPoints;
    double r, E, F, E_shifted, F_shifted;
    string format_f = "% .8e\t";   //float format
    string format_fh = "%15s\t";   //float header format
    char comment = '#';
    cout << comment << "r: radius [d]" << endl;
    cout << comment << "V: potential energy [kT]" << endl;
    cout << comment << "V_sh: shifted potential energy [kT]" << endl;
    cout << comment << "F: radial force [kT d-1]" << endl;
    cout << comment << "F_sh: shifted radial force [kT d-1]" << endl;
    cout << comment;
    cout << bo::format("%14s\t") % "r";
    cout << bo::format(format_fh) % "V";
    cout << bo::format(format_fh) % "V_sh";
    cout << bo::format(format_fh) % "F";
    cout << bo::format(format_fh) % "F_sh";
    cout << endl;
    for(int i = 0; i < numberOfPoints; ++i){
        r = i * rcDelta;
        E = dlvo.energy(r);
        F = dlvo.forceAbs(r);
        E_shifted = dlvo.energyShifted(r);
        F_shifted = dlvo.forceAbsShifted(r);
        cout << bo::format(format_f) % r;
        cout << bo::format(format_f) % E;
        cout << bo::format(format_f) % E_shifted;
        cout << bo::format(format_f) % F;
        cout << bo::format(format_f) % F_shifted;
        cout << endl;
    }
    return 0;
}
