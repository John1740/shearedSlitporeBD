#include "printer.h"

#include <iostream>

PRINTER::PRINTER(){
}

PRINTER::PRINTER(fs::path filename, bool reset){
//    setFilename(filename);
    this->filename = filename;
    openFile(reset);
}

PRINTER::~PRINTER(){
    closeFile();
}

void PRINTER::openFile(bool overwrite){
    if(filename.has_parent_path()){
        fs::create_directory(filename.parent_path());
    }
    if(overwrite){
        file.open(filename.c_str(), ios::trunc); //trunc=truncate
    }
    else{
        file.open(filename.c_str(), ios::app);  //app=append
    }
}

void PRINTER::closeFile(){
    file.close();
    if(fs::exists(filename) && fileIsEmpty()){
        fs::remove(filename);
        if(filename.has_parent_path()){
            if(fs::is_empty(filename.parent_path())){
                fs::remove(filename.parent_path());
            }
        }
    }
}

//file is considered empty when it contains only whitespaces (and optionally comment-lines)
bool PRINTER::fileIsEmpty(bool ignoreComments){
    bool fileIsEmpty = true;
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
    return fileIsEmpty;
}

//returns true if the file needed to be deleted
bool PRINTER::reset() {
    closeFile();
//    bool removed = fs::remove(filename);
//    openFile();
//    file.close();
    openFile(true);
    return true;
}

//should only be used if the filename wasn't set during constructing
//otherwise, use a new instance of PRINTER instead
//DEPRECATED: does not support the ios::trunc method
void PRINTER::setFilename(fs::path filename){
    closeFile();
    this->filename = filename;
    openFile();
}

fs::path PRINTER::getFilename() const{
    return filename;
}

string PRINTER::getFilenameAsString() const{
    return string(filename);
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

void PRINTER::flush(){
    file.flush();
}
