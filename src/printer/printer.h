#ifndef PRINTER_H
#define PRINTER_H

#include <stdarg.h>
#include <fstream>
#include <string>
#include <experimental/filesystem>

using namespace std;
namespace fs = experimental::filesystem;

class PRINTER{
    fs::path filename;
    ofstream file;
    
    void openFile();
    void closeFile();

public:
    PRINTER();
    PRINTER(fs::path filename);
    ~PRINTER();
    
    // setters
    void setFilename(fs::path filename);
    
    // getters
    fs::path getFilename() const;
    
    bool fileIsEmpty();
    void removeFile();
    
    template<typename T>
    void print(T t){
        file << t;
    }
    
    template<typename T>
    void printLine(T t){
        file << t << endl;
    }
    
    template<typename T, typename... Args>
    void printLine(T t, Args... args){
        file << t << "\t";
        printLine(args...);
    }
};

#endif // PRINTER_H
