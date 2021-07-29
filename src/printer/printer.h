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
    char comment = '#';

    void openFile(bool overwrite=false);
    void closeFile();

public:
    PRINTER();
    PRINTER(fs::path filename, bool reset=false);
    ~PRINTER();

    // datatype formats (+ headers)
    string format_f = "% .8e\t";   //float format
    string format_fh = "%15s\t";   //float header format
    string format_l = "%12li\t";   //long (integer) format
    string format_lh = "%11s\t";   //long (integer) header format

    // setters
    void setFilename(fs::path filename);
    void setComment(char comment);

    // getters
    fs::path getFilename() const;
    string getFilenameAsString() const;
    char getComment() const;

    bool fileIsEmpty(bool ignoreComments = true);
    bool reset();

    //don't use this! better use << to write to stream
    template<typename T>
    void print(T t){
        file << t;
    }

    //don't use this! better use << to write to stream
    template<typename T>
    void printLine(T t){
        file << t << endl;
    }

    //don't use this! better use << to write to stream
    template<typename T, typename... Args>
    void printLine(T t, Args... args){
        file << t << "\t";
        printLine(args...);
    }

    template<typename T>
    ofstream& operator<<(T t){
        file << t;
        return file;
    }

    friend ostream& operator<<(ostream& os, const PRINTER& printer);
};

#endif // PRINTER_H
