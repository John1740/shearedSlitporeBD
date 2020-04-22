//
// Created by mhuels on 4/20/20.
//

#include "stress.h"

STRESS::STRESS(){
    pFile = fopen(filename.c_str(), "w");
}

STRESS::STRESS(string filename){
    this->filename = filename;
    pFile = fopen(filename.c_str(), "w");
}

STRESS::STRESS(string filename, string format_l){
    this->filename = filename;
    this->format_l = format_l;
    pFile = fopen(filename.c_str(), "w");
}

STRESS::STRESS(string filename, string format_l, string format_h){
    this->filename = filename;
    this->format_l = format_l;
    this->format_h = format_h;
    pFile = fopen(filename.c_str(), "w");
//    cout << "Writing stresses to " << filename << endl;
}

STRESS::~STRESS(){
    fclose(pFile);
}

void STRESS::printHeader(){
    fprintf(pFile, "#%5s\t", "i");
    fprintf(pFile, format_h.c_str(), "xx");
    fprintf(pFile, format_h.c_str(), "xy");
    fprintf(pFile, format_h.c_str(), "xz");
    fprintf(pFile, format_h.c_str(), "yy");
    fprintf(pFile, format_h.c_str(), "yz");
    fprintf(pFile, format_h.c_str(), "zz");
    fprintf(pFile, "\n");
}

void STRESS::printLine(SHEARED_SLITPORE_SYSTEM& sys, int timeStep){
    fprintf(pFile, "%6d\t", timeStep);
    fprintf(pFile, format_l.c_str(), sys.getMeanStress().xx);
    fprintf(pFile, format_l.c_str(), sys.getMeanStress().xy);
    fprintf(pFile, format_l.c_str(), sys.getMeanStress().xz);
    fprintf(pFile, format_l.c_str(), sys.getMeanStress().yy);
    fprintf(pFile, format_l.c_str(), sys.getMeanStress().yz);
    fprintf(pFile, format_l.c_str(), sys.getMeanStress().zz);
    fprintf(pFile, "\n");
}
