#include "printer.h"

// string exec(char* cmd) {
//     FILE* pipe = popen(cmd, "r");
//     if (!pipe) return "ERROR";
//     char buffer[128];
//     std::string result = "";
//     while(!feof(pipe)) {
//       if(fgets(buffer, 128, pipe) != NULL)
//          result += buffer;
//     }
//     pclose(pipe);
//     return result;
// }

PRINTER::PRINTER()
{
   setFileExtension("txt");
   setDirectoryPathAndOutputFile( "", "" );
}

PRINTER::PRINTER( string outputFileIn )
{
   setFileExtension("txt");
   setDirectoryPathAndOutputFile( "", outputFileIn );
}

PRINTER::PRINTER( string directoryPathIn, string outputFileIn )
{
   setFileExtension("txt");
   setDirectoryPathAndOutputFile( directoryPathIn, outputFileIn );
}

PRINTER::~PRINTER()
{
   file.close();
}

void PRINTER::setFileExtension ( string fileExtensionIn )
{
    remove( filePath.c_str() );
    fileExtension = fileExtensionIn;
    closeFile();
    getFilePath();
    openFile();
}

bool PRINTER::fileIsEmpty()
{
    file.seekp(0, ios::end); // put the "cursor" at the end of the file
    double length = file.tellp();
    if( length == 0 )
	return true;
    else
	return false;
}

void PRINTER::setDirectoryPathAndOutputFile( string directoryPathIn, string outputFileIn )
{
   directoryPath = directoryPathIn;
   outputFile = outputFileIn;
   getFilePath();

   openFile();
}

void PRINTER::getFilePath()
{
   filePath = app_home( "" ) + directoryPath + "/" + outputFile + "." + fileExtension;
}

void PRINTER::openFile()
{
   file.close();
   string cmd = "mkdir -p " + app_home( directoryPath );
   system( cmd.c_str() );

   file.open( filePath.c_str(), ios::app );
}

void PRINTER::removeFile()
{
   file.close();
   remove( filePath.c_str() );
   openFile();
}



void PRINTER::setDescription( string column0, string column1, string column2, string column3, string column4, string column5, string column6, string column7, string column8, string column9 )
{
   file << column0
        << "\t" << column1
        << "\t" << column2
        << "\t" << column3
        << "\t" << column4
        << "\t" << column5
        << "\t" << column6
        << "\t" << column7
        << "\t" << column8
        << "\t" << column9
        << endl;
}

void PRINTER::closeFile()
{
   file.close();
}






