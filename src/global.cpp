/*
 *  global.cpp
 *
 *  Created on: Jul 10, 2012
 *      Author: tarlan
 */
#include "global.h"

#include <unistd.h> //getpid()
#include "randomc.h"    //CRandomMersenne
#include <sstream>  //time()

CRandomMersenne random_event(getpid()*time(0)); //using this somewhere else needs to use 'extern'

void initSeed(unsigned int seed){
    random_event.RandomInit(seed);
}




