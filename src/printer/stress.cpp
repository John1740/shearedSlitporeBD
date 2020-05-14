//
// Created by mhuels on 4/20/20.
//

#include "stress.h"
#include "boost/format.hpp"
using namespace boost;

STRESS_PRINTER::STRESS_PRINTER(SHEARED_SLITPORE_SYSTEM* sysIn){
    sys = sysIn;
    printer.setFilename("stresses.out");
    printer.removeFile();
    printHeader();
}

STRESS_PRINTER::STRESS_PRINTER(SHEARED_SLITPORE_SYSTEM* sysIn, fs::path filename){
    sys = sysIn;
    printer.setFilename(filename);
    printer.removeFile();
    printHeader();
}

STRESS_PRINTER::~STRESS_PRINTER(){

}

void STRESS_PRINTER::printHeader(){
    printer.print(format("#%5s\t") % "i");
    printer.print(format(format_h.c_str()) % "shearRate");
    printer.print(format(format_h.c_str()) % "xx");
    printer.print(format(format_h.c_str()) % "yy");
    printer.print(format(format_h.c_str()) % "zz");
    printer.print(format(format_h.c_str()) % "yz");
    printer.print(format(format_h.c_str()) % "xz");
    printer.print(format(format_h.c_str()) % "xy");
    printer.printLine("");
}

void STRESS_PRINTER::printLine(){
    printer.print(format("%6ld\t") % (sys->getTimestep() - 1)); //equationOfMotion already incremented timestep by 1
    meanStress = sys->getMeanStress();
    printer.print(format(format_l.c_str()) % sys->getCurrentShearRate());
    printer.print(format(format_l.c_str()) % meanStress.xx);
    printer.print(format(format_l.c_str()) % meanStress.yy);
    printer.print(format(format_l.c_str()) % meanStress.zz);
    printer.print(format(format_l.c_str()) % meanStress.yz);
    printer.print(format(format_l.c_str()) % meanStress.xz);
    printer.print(format(format_l.c_str()) % meanStress.xy);
    printer.printLine("");
}