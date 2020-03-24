#include "parse_arguments.h"

PARSE_ARGUMENTS::PARSE_ARGUMENTS()
{

}

vector< double > PARSE_ARGUMENTS::getArgumentList ( int argc, char* argv[] )
{
    arg.clear();
    arg.resize(argc-1);
    for( int i = 0; i < arg.size(); ++i ){
	if( i+1 < argc ){
	    double argIn = convertToDouble( argv[i+1] );
	    arg[i] = argIn;
	}
    }

    return arg;
}

double PARSE_ARGUMENTS::convertToDouble ( string strIn )
{
    double argDouble = strtod( strIn.c_str(), NULL );

    if( !inputIsValid( strIn, argDouble ) ){
	printf ("Parse arguments: input '%s != %s' output! (Expecting a double in standard notation!)\n", strIn.c_str(), app_number("",argDouble).c_str() );
	argDouble = 0./0.;
    }
    
    return argDouble;
}

bool PARSE_ARGUMENTS::inputIsValid ( string strIn, double argIn )
{
    bool isValid = true;
    string test = app_number("",argIn);
	if( test != strIn ){
	    isValid = false;
    }
    return isValid;
}

void PARSE_ARGUMENTS::checkForInvalidArguments ( vector< double >& argumentsIn )
{
    for( int i = 0; i < argumentsIn.size(); ++i ){
	if( argumentsIn[i] != argumentsIn[i] ){
	    cout << "Invalid argument, exit!" << endl;
	    exit(1);
	}
    }
}

void PARSE_ARGUMENTS::printArgumentList ( vector< double >& argumentsIn )
{
    cout << "Argument list: " << endl;
    for( int i = 0; i < argumentsIn.size(); ++i ){
	cout << "arguments[" << i << "] = " << argumentsIn[i] << endl;
    }
}
