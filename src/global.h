/*
 * global.h
 *
 *  Created on: Jul 10, 2012
 *  Author: Tarlan Vezirov
 */
#ifndef global_h
#define global_h

#include <sstream>
#include <vector>
#include <sys/stat.h>

#include <unistd.h>
#include "randomc.h"

#include <iostream>
using namespace std;

extern int read_toggle;

extern string home;


extern vector<double> arguments;

//////////////////////////////////////////////////////////////////////////////////////
//*******************SMALL-FUNCTIONS******************////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

extern string app_home ( string );

template<typename T>
string app_number ( string str, T number )
{
   stringstream output;
   output << str << number;
   return output.str();
};

inline bool fileExists(const std::string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}

#endif
