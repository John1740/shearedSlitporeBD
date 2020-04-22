#include "printer.h"

PRINTER::PRINTER(){
//    fileStem = "";
//    directoryPath = "";
//    fileExtension = "";
    relativePath = "";
//    absolutePath = getWorkingDirectory() + relativePath;
    //should not be allowed
}

PRINTER::PRINTER(string relativePathIn){
//    fileStem = relativePathIn;
//    directoryPath = "";
//    fileExtension = "";
    relativePath = relativePathIn;
//    absolutePath = getWorkingDirectory() + relativePath;
    openFile();
}

//PRINTER::PRINTER(string directoryPathIn, string outputFileIn){
//    fileStem = outputFileIn;
//    directoryPath = directoryPathIn;
//    fileExtension = "";
//    absolutePath = getFilePath();
//    openFile();
//}

PRINTER::~PRINTER(){
    file.close();
}

//void PRINTER::setFileExtension (string fileExtensionIn){
//    remove(absolutePath.c_str());
//    fileExtension = fileExtensionIn;
//    closeFile();
////    getFilePath();
//    openFile();
//}

bool PRINTER::fileIsEmpty(){
    file.seekp(0, ios::end); // put the "cursor" at the end of the file
    double length = file.tellp();
    if(length == 0) {
        return true;
    }
    else {
        return false;
    }
}

//void PRINTER::getFilePath(){
//    absolutePath = app_home("") + directoryPath + "/" + fileStem + "." + fileExtension;
//}

void PRINTER::openFile(){
    string cmd = "mkdir -p " + directoryPath;
    system(cmd.c_str());
    file.open(absolutePath.c_str(), ios::app);
}

void PRINTER::removeFile(){
    file.close();
    remove(absolutePath.c_str());
    openFile();
}

//void PRINTER::setDescription(string column0, string column1, string column2, string column3, string column4, string column5, string column6, string column7, string column8, string column9){
//    file << column0
//        << "\t" << column1
//        << "\t" << column2
//        << "\t" << column3
//        << "\t" << column4
//        << "\t" << column5
//        << "\t" << column6
//        << "\t" << column7
//        << "\t" << column8
//        << "\t" << column9
//        << endl;
//}

void PRINTER::closeFile(){
    file.close();
}

//void PRINTER::setOutputFile(string outputFileIn) {
//    file.close();
//    fileStem = outputFileIn;
//}

//void PRINTER::setDirectoryPath(string directoryPathIn) {
//    directoryPath = directoryPathIn;
//}