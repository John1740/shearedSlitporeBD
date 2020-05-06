//
// Created by mhuels on 4/20/20.
//

#include "stress.h"

STRESS::STRESS(){
    pFile = fopen(filename.c_str(), "w");
    printHeader();
}

STRESS::STRESS(string filename){
    this->filename = filename;
    pFile = fopen(filename.c_str(), "w");
    printHeader();
}

STRESS::STRESS(string filename, string format_l){
    this->filename = filename;
    this->format_l = format_l;
    pFile = fopen(filename.c_str(), "w");
    printHeader();
}

STRESS::STRESS(string filename, string format_l, string format_h){
    this->filename = filename;
    this->format_l = format_l;
    this->format_h = format_h;
    pFile = fopen(filename.c_str(), "w");
    printHeader();
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

void STRESS::printLine(SHEARED_SLITPORE_SYSTEM& sys){
    fprintf(pFile, "%6ld\t", sys.getTimestep() - 1); //equationOfMotion already incremented timestep by 1
    meanStress = sys.getMeanStress();
    fprintf(pFile, format_l.c_str(), meanStress.xx);
    fprintf(pFile, format_l.c_str(), meanStress.xy);
    fprintf(pFile, format_l.c_str(), meanStress.xz);
    fprintf(pFile, format_l.c_str(), meanStress.yy);
    fprintf(pFile, format_l.c_str(), meanStress.yz);
    fprintf(pFile, format_l.c_str(), meanStress.zz);
    fprintf(pFile, "\n");
}

string STRESS::getFilename() const{
    return filename;
}
