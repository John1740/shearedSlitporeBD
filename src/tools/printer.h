#ifndef PRINTER_H
#define PRINTER_H
// #include "../global.h"

#include<stdarg.h>
#include <fstream>
#include <string>
using namespace std;
#include "../global.h"

class PRINTER
{
   string outputFile, filePath,directoryPath;
   ofstream file;

   string fileExtension;

   void getFilePath();
   void openFile();

public:
   PRINTER();
   PRINTER ( string outputFileIn );
   PRINTER ( string directoryPathIn, string outputFileIn );
   ~PRINTER();
   
   void setFileExtension( string fileExtensionIn );
   
   void setDirectoryPathAndOutputFile ( string directoryPathIn, string outputFileIn );
   void removeFile();
   void closeFile();
   
   bool fileIsEmpty();

   void setDescription (
      string column0 = "",
      string column1 = "",
      string column2 = "",
      string column3 = "",
      string column4 = "",
      string column5 = "",
      string column6 = "",
      string column7 = "",
      string column8 = "",
      string column9 = ""
   );

   template<typename T>
   void printLine ( T t )
   {
      file << t << endl;
   }

   template<typename T, typename... Args>
   void printLine ( T t, Args... args )
   {
      file << t << "\t";
      printLine ( args... );
   }


};

#endif // PRINTER_H
