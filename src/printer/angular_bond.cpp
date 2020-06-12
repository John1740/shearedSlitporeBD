//
// Created by mhuels on 5/25/20.
//

#include "angular_bond.h"
#include "../order_parameter/angular_bond_parameter.h"
#include "boost/format.hpp"
using namespace boost;

ANGULAR_BOND_PRINTER::ANGULAR_BOND_PRINTER(): PRINTER(ANGULAR_BOND_OUT){
    printHeader();
}

ANGULAR_BOND_PRINTER::ANGULAR_BOND_PRINTER(fs::path filename): PRINTER(filename){
    printHeader();
}

void ANGULAR_BOND_PRINTER::printHeader(){
    char comment = getComment();
    *this << comment << "i: timestep" << endl;
    *this << comment << "y: shear rate [1/Brownian time]" << endl;
    *this << comment << "psi(n): angular bond parameter (n = integer of symmetry)" << endl;
    *this << comment;
    *this << format("%11s\t") % "i";
    *this << format(format_h.c_str()) % "y";
    *this << format(format_h.c_str()) % "psi(4)";
    *this << format(format_h.c_str()) % "psi(6)";
    *this << "\n";
}

void ANGULAR_BOND_PRINTER::printLine(SHEARED_SLITPORE_SYSTEM& sys){
    *this << format(format_li.c_str()) % sys.getTimestep();
    *this << format(format_f.c_str()) % sys.getCurrentShearRate();
    ANGULAR_BOND_PARAMETER psi(sys, 4);
    *this << format(format_f.c_str()) % psi.calculateAverageOverAllParticles();
    psi.setN(6);
    *this << format(format_f.c_str()) % psi.calculateAverageOverAllParticles();
    
    //error outputs
    vector<int> erroneousParticles = psi.getIsolatedParticles();
    if(erroneousParticles.size() > 0){
        cout << "erroneous particles in timestep " << sys.getTimestep() << ": ";
        for(int i = 0; i < erroneousParticles.size(); i++){
            cout << erroneousParticles[i] << " ";
        }
        cout << endl;
        cout << "cutoffRadius: " << format(format_f.c_str()) % psi.getNextNeighborShellRadius() << "[diameter]" << endl;
        cout << "threshold: " << format(format_f.c_str()) % psi.getPairCorrelation().calculateMeanCorrelation() << "[1/diameter]" << endl;
        cout << endl;
        sys.writeConfigurationToFile("snapshots/configuration_" + to_string(sys.getTimestep()) + ".out", true);
        psi.getPairCorrelation().print("pairCorrelations/pairCorrelation_" + to_string(sys.getTimestep()) + ".out");
    }
    psi.getPairCorrelation().print("pairCorrelation.out");
    *this << '\n';
}
