#include "printer.h"

PRINTER::PRINTER(){
}

PRINTER::PRINTER(fs::path filename){
    setFilename(filename);
    openFile();
}

PRINTER::~PRINTER(){
    closeFile();
}

bool PRINTER::fileIsEmpty(){
    return fs::is_empty(filename);
}

void PRINTER::openFile(){
    closeFile();
    file.open(filename.c_str(), ios::app);  //app=append
}

void PRINTER::removeFile(){
    closeFile();
    fs::remove(filename);
    openFile();
}

void PRINTER::closeFile(){
    file.close();
}

void PRINTER::setFilename(fs::path filename){
    closeFile();
    this->filename = filename;
    openFile();
}

fs::path PRINTER::getFilename() const{
    return filename;
}
