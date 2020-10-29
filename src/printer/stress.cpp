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
    *this << format("%5s\t") % "i";
    *this << format(format_h.c_str()) % "dy/dt";
    *this << format(format_h.c_str()) % "xx";
    *this << format(format_h.c_str()) % "yy";
    *this << format(format_h.c_str()) % "zz";
    *this << format(format_h.c_str()) % "yz";
    *this << format(format_h.c_str()) % "xz";
    *this << format(format_h.c_str()) % "xy";
    *this << "\n";
}

void STRESS_PRINTER::printLine(){
    *this << format("%6ld\t") % (sys->getTimestep() - 1); //equationOfMotion already incremented timestep by 1
    meanStress = sys->getMeanStress();
    *this << format(format_l.c_str()) % sys->getCurrentShearRate();
    *this << format(format_l.c_str()) % meanStress.xx;
    *this << format(format_l.c_str()) % meanStress.yy;
    *this << format(format_l.c_str()) % meanStress.zz;
    *this << format(format_l.c_str()) % meanStress.yz;
    *this << format(format_l.c_str()) % meanStress.xz;
    *this << format(format_l.c_str()) % meanStress.xy;
    *this << "\n";
}