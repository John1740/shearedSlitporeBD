//
// Created by mhuels on 5/31/21.
//

#include <iostream>
#include "boost/program_options.hpp"
#include "../src/interactions/dlvo_softsphere_interaction.h"
#include <boost/format.hpp>

using namespace std;
namespace po = boost::program_options;
namespace bo = boost;

int main(int argc, const char* argv[]){
    po::options_description description{"Options"};
    po::variables_map vm;
    description.add_options()
            ("help,h", "Help screen")
            ("charge,Z", po::value<int>()->default_value(35), "charge of the macroion")
            ("density", po::value<double>()->default_value(0.85), "macroion density [d-3]")
            ("ionicStrength,I", po::value<double>()->default_value(1e-5), "ionic strength [mol l-1]")
            ("temperature,T", po::value<double>()->default_value(298), "temperature [K]")
            ("diameter,d", po::value<double>()->default_value(26e-9), "macroion diameter [m]")
            ("eps", po::value<double>()->default_value(78.5), "permittivity of the solvent")
            ("ssInteractionStrength", po::value<double>()->default_value(SS_INTERACTION_STRENGTH), "soft-sphere interaction strength [kT]")
            ;
    po::store(parse_command_line(argc, argv, description), vm);
    po::notify(vm);
    if(vm.count("help")){
        cout << description << endl;
        exit(0);
    }

    cout << "#Input parameters:" << endl;
    const char* fmt = "% .8f\t";
    cout << "charge: " << bo::format(fmt) % vm["charge"].as<int>() << endl;
    cout << "density: " << bo::format(fmt) % vm["density"].as<double>() << "[d-3]" << endl;
    cout << "ionicStrength: " << bo::format(fmt) % vm["ionicStrength"].as<double>() << "[mol l-1]" << endl;
    cout << "temperature: " << bo::format(fmt) % vm["temperature"].as<double>() << "[K]" << endl;
    cout << "diameter: " << bo::format(fmt) % vm["diameter"].as<double>() << "[m]" << endl;
    cout << "eps: " << bo::format(fmt) % vm["eps"].as<double>() << endl;
    cout << "ssInteractionStrength: " << bo::format(fmt) % vm["ssInteractionStrength"].as<double>() << "[kT]" << endl;
    cout << endl;

    DLVO_SOFTSPHERE_INTERACTION dlvo;
    dlvo.diameter = 1.0;
    dlvo.ssInteractionStrength = vm["ssInteractionStrength"].as<double>();
    double kappa = dlvo.calculateKappa(vm["charge"].as<int>(),
                                       vm["density"].as<double>(),
                                       vm["ionicStrength"].as<double>(),
                                       vm["temperature"].as<double>(),
                                       vm["diameter"].as<double>(),
                                       vm["eps"].as<double>());
    dlvo.calculateInteractionStrength(kappa,
                                      vm["charge"].as<int>(),
                                      vm["temperature"].as<double>(),
                                      vm["diameter"].as<double>(),
                                      vm["eps"].as<double>());
    dlvo.setup();
    cout << "#Interaction parameters:" << endl;
    cout << dlvo << endl;
    return 0;
}
