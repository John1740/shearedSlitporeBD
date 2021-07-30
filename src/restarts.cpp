//
// Created by mhuelsberg on 30.07.21.
//

#include "restarts.h"

long restartFromConfiguration(string filename, CONFINED_BROWNIAN_PARTICLES& sys, long numberOfTimesteps, bool verbose){
    if(verbose){
        cout << "Invoking restart." << endl;
    }
    long originalTimestep = sys.getTimestep();
    sys.readConfigurationFromFile(filename, false);
    long timestepNow = sys.getTimestep();
    long skip = timestepNow - originalTimestep;
    float progress = double(skip) / numberOfTimesteps;
    if(verbose){
        cout << "Restarting from timestep " << timestepNow;
        cout << " (" << 100 * progress << "% done)" << endl;
    }
    if(skip >= numberOfTimesteps){
        cout << "The timestep in " << filename << " is already too advanced (" << skip << "/" << numberOfTimesteps << "). Exiting..." << endl;
        exit(0);
    }
    return skip;
}