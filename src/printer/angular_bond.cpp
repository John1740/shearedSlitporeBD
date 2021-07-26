//
// Created by mhuels on 5/25/20.
//

#include "angular_bond.h"
#include "../order_parameter/angular_bond_parameter.h"

#include "boost/format.hpp"

using namespace boost;

ANGULAR_BOND_PRINTER::ANGULAR_BOND_PRINTER(SHEARED_SLITPORE_SYSTEM* sysIn): PRINTER(ANGULAR_BOND_OUT){
    sys = sysIn;
    printHeader();
}

ANGULAR_BOND_PRINTER::ANGULAR_BOND_PRINTER(SHEARED_SLITPORE_SYSTEM* sysIn, fs::path filename): PRINTER(filename){
    sys = sysIn;
    printHeader();
}

void ANGULAR_BOND_PRINTER::printHeader(){
    char comment = getComment();
    *this << comment << "i: timestep (dt = " << sys->getTimeStepSize() << " tB)" << endl;
    *this << comment << "psi(n): angular bond parameter (n = integer of symmetry)" << endl;
    *this << comment;
    *this << format(format_lh) % "i";
    *this << format(format_fh) % "psi(4)";
    *this << format(format_fh) % "psi(6)";
    *this << "\n";
}

void ANGULAR_BOND_PRINTER::printLine(){
    *this << format(format_l) % sys->getTimestep();
    ANGULAR_BOND_PARAMETER psi(*sys, 4);
    *this << format(format_f) % psi.calculateSystemAverage();
    psi.setN(6);
    *this << format(format_f) % psi.calculateSystemAverage();

    //error outputs
    vector<int> erroneousParticles = psi.getIsolatedParticles();
    if(erroneousParticles.size() > 0){
        sys->writeConfigurationToFile(ERRONEOUS + "/" + SNAPSHOTS, false, false);
        psi.getPairCorrelation().print(ERRONEOUS + "/" + PAIR_CORRELATION_OUT, false,
                                       "timestep: " + to_string(sys->getTimestep()));
    }
    *this << '\n';
}
