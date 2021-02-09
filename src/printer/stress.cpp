//
// Created by mhuels on 4/20/20.
//

#include "stress.h"
#include "boost/format.hpp"

using namespace boost;

STRESS_PRINTER::STRESS_PRINTER(SHEARED_SLITPORE_SYSTEM* sysIn): PRINTER(STRESSES_OUT){
    sys = sysIn;
    printHeader();
}

STRESS_PRINTER::STRESS_PRINTER(SHEARED_SLITPORE_SYSTEM* sysIn, fs::path filename): PRINTER(filename){
    sys = sysIn;
    printHeader();
}

STRESS_PRINTER::~STRESS_PRINTER(){
}

void STRESS_PRINTER::printHeader(){
    char comment = getComment();
    *this << comment << "i: timestep (dt = " << sys->getTimeStepSize() << " tB)" << endl;
    *this << comment << "dy/dt: shear rate [1/tB]" << endl;
    *this << comment << "ij: average stress tensor component (i,j=x,y,z) [kT/d^3]" << endl;
    *this << comment;
    *this << format(format_lh) % "i";
    *this << format(format_fh) % "dy/dt";
    *this << format(format_fh) % "xx";
    *this << format(format_fh) % "yy";
    *this << format(format_fh) % "zz";
    *this << format(format_fh) % "yz";
    *this << format(format_fh) % "xz";
    *this << format(format_fh) % "xy";
    *this << "\n";
}

void STRESS_PRINTER::printLine(){
    *this << format(format_l) % (sys->getTimestep() - 1); //equationOfMotion already incremented timestep by 1
    meanStress = sys->getMeanStress();
    *this << format(format_f) % sys->getCurrentShearRate();
    *this << format(format_f) % meanStress.xx;
    *this << format(format_f) % meanStress.yy;
    *this << format(format_f) % meanStress.zz;
    *this << format(format_f) % meanStress.yz;
    *this << format(format_f) % meanStress.xz;
    *this << format(format_f) % meanStress.xy;
    *this << "\n";
}