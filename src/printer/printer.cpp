#include <iostream>
#include "printer.h"

PRINTER::PRINTER(){
}

PRINTER::PRINTER(fs::path filename){
    setFilename(filename);
}

PRINTER::~PRINTER(){
    closeFile();
}

void PRINTER::openFile(){
    file.open(filename.c_str(), ios::app);  //app=append
}

bool PRINTER::fileIsEmpty(bool ignoreComments){
    bool fileIsEmpty = true;
    file.close();
    ifstream tmpFile;
    tmpFile.open(filename.c_str());
    string line;
    //go to first line that doesn't contain '#' nor pure whitespace
    while(tmpFile){
        getline(tmpFile, line);
        //ignore empty lines
        if(line.empty()){
            continue;
        }
        //ignore lines with comments/header-lines
        else if(ignoreComments && line[0] == comment){
            continue;
        }
        //ignore lines with only whitespaces (' ' or '\t')
        else if(line.find_first_not_of(" \t") == string::npos){
            continue;
        }
        else{
            fileIsEmpty = false;
            break;
        }
    }
    tmpFile.close();
    openFile();
    return fileIsEmpty;
}

void PRINTER::closeFile(){
    file.close();
    if(fs::exists(filename) && fileIsEmpty()){
        fs::remove(filename);
    }
}

void PRINTER::reset(){
    closeFile();
    fs::remove(filename);
    openFile();
}

//should only be used if the filename wasn't set during constructing
//otherwise, use a new instance of PRINTER instead
void PRINTER::setFilename(fs::path filename){
    closeFile();
    this->filename = filename;
    openFile();
}

fs::path PRINTER::getFilename() const{
    return filename;
}

void PRINTER::setComment(char comment){
    this->comment = comment;
}

char PRINTER::getComment() const{
    return comment;
}

ostream& operator<<(ostream& os, const PRINTER& printer){
    os << "PRINTER(";
    os << printer.getFilename();
    os << ", '" << printer.getComment() << "'";
    if(printer.file.is_open()){
        os << ", 'open'";
    }
    else{
        os << ", 'closed'";
    }
    os << ")";
    return os;
}

std::ifstream::pos_type filesize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}