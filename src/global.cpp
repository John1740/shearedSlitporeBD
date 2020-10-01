/*
 *  global.cpp
 *
 *  Created on: Jul 10, 2012
 *      Author: tarlan
 */
#include "global.h"

#include <unistd.h> //getpid()
#include <sstream>  //time()

//global instance that can be used everywhere via the 'extern' keyword
CRandomMersenne random_event(getpid() * time(0));