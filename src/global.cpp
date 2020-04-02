/*
 *  global.cpp
 *
 *  Created on: Jul 10, 2012
 *      Author: tarlan
 */
#include"global.h"

vector<double> arguments(0);

CRandomMersenne random_event(getpid()*time(0));

int read_toggle = 0; // 0: read periodic values; 1: read absolute values

char const *pchome = getenv("HOME");
string home = pchome ? pchome: "";

string app_home(string str){
   stringstream output;

   output << "/home/mhuels/data/shearedSlitporeBD/output/";

   output << str;
   return output.str();
}

