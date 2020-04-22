#ifndef PRINTER_H
#define PRINTER_H

#include <stdarg.h>
#include <fstream>
#include <string>
//#include <filesystem>
using namespace std;

class PRINTER{
    string directoryPath, fileStem, fileExtension;
    string absolutePath, relativePath;
    ofstream file;

    void openFile();
    void removeFile();
    void closeFile();

    void getWorkingDirectory();

public:
    PRINTER();
    PRINTER(string relativePathIn);
//    PRINTER(string directoryPathIn, string outputFileIn);
    ~PRINTER();

    // setters
//    void setOutputFile(string outputFileIn);
//    void setDirectoryPath(string directoryPathIn);
//    void setFileExtension(string fileExtensionIn);
//    void setFilePath(string filePathIn);

    // getters
//    string getOutputFile() const;
//    string getDirectoryPath() const;
//    string getFileExtension() const;
//    string getAbsolutePath() const;

    bool fileIsEmpty();

//    void setDescription (
//        string column0 = "",
//        string column1 = "",
//        string column2 = "",
//        string column3 = "",
//        string column4 = "",
//        string column5 = "",
//        string column6 = "",
//        string column7 = "",
//        string column8 = "",
//        string column9 = ""
//    );

    template<typename T>
    void printLine (T t){
        file << t << endl;
    }

    template<typename T, typename... Args>
    void printLine (T t, Args... args){
        file << t << "\t";
        printLine (args...);
    }
};

#endif // PRINTER_H
