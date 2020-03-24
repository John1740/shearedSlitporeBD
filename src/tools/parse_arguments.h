#ifndef PARSE_ARGUMENTS_H
#define PARSE_ARGUMENTS_H

#include "../global.h"
#include <stdio.h>

class PARSE_ARGUMENTS
{
    vector<double> arg;

    double convertToDouble( string strIn );
    bool inputIsValid( string strIn, double argIn );
    
public:
    PARSE_ARGUMENTS();
    
    vector<double> getArgumentList( int argc, char* argv[] );
    void checkForInvalidArguments( vector<double>& argumentsIn );
    void printArgumentList( vector<double>& argumentsIn );
};

#endif // PARSE_ARGUMENTS_H
