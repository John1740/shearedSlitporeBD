//
// Created by mhuels on 4/20/20.
//

#include "stress.h"
#include "boost/format.hpp"
using namespace boost;

STRESS_PRINTER::STRESS_PRINTER(SHEARED_SLITPORE_SYSTEM* sysIn){
    sys = sysIn;
    printer.setFilename("stresses.out");
//    printer.reset();
    printHeader();
}

STRESS_PRINTER::STRESS_PRINTER(SHEARED_SLITPORE_SYSTEM* sysIn, fs::path filename){
    sys = sysIn;
    printer.setFilename(filename);
//    printer.reset();
    printHeader();
}

STRESS_PRINTER::~STRESS_PRINTER(){

}

void STRESS_PRINTER::printHeader(){
    printer << printer.getComment();
    printer << format("%5s\t") % "i";
    printer << format(format_h.c_str()) % "shearRate";
    printer << format(format_h.c_str()) % "xx";
    printer << format(format_h.c_str()) % "yy";
    printer << format(format_h.c_str()) % "zz";
    printer << format(format_h.c_str()) % "yz";
    printer << format(format_h.c_str()) % "xz";
    printer << format(format_h.c_str()) % "xy";
    printer << "\n";
}

void STRESS_PRINTER::printLine(){
    printer << format("%6ld\t") % (sys->getTimestep() - 1); //equationOfMotion already incremented timestep by 1
    meanStress = sys->getMeanStress();
    printer << format(format_l.c_str()) % sys->getCurrentShearRate();
    printer << format(format_l.c_str()) % meanStress.xx;
    printer << format(format_l.c_str()) % meanStress.yy;
    printer << format(format_l.c_str()) % meanStress.zz;
    printer << format(format_l.c_str()) % meanStress.yz;
    printer << format(format_l.c_str()) % meanStress.xz;
    printer << format(format_l.c_str()) % meanStress.xy;
    printer << "\n";
}