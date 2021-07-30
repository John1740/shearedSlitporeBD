//
// Created by mhuelsberg on 30.07.21.
//

#include "restarts.h"
#include "defaults.h"
#include "boost/format.hpp"
namespace b = boost;

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
        cout << b::format(" (%.0f%% done)") % (100 * progress) << endl;
    }
    if(skip >= numberOfTimesteps){
        cout << "The timestep in " << filename << " is already too advanced (" << skip << "/" << numberOfTimesteps << "). Exiting..." << endl;
        exit(0);
    }
    return skip;
}

long restartSimulation(CONFINED_BROWNIAN_PARTICLES& sys, long numberOfTimesteps, bool verbose){
    //read configuration.out and exit if simulation is already finished
    long timestepIn = sys.getTimestep();
    if(fs::exists(CONFIGURATION_OUT)){
        restartFromConfiguration(CONFIGURATION_OUT, sys, numberOfTimesteps, verbose);
    }
    long timestepOut = sys.getTimestep();

    //read configuration.restart and exit if simulation is already finished
    if(fs::exists(CONFIGURATION_RESTART)){
        restartFromConfiguration(CONFIGURATION_RESTART, sys, numberOfTimesteps, verbose);
    }
    long timestepRestart = sys.getTimestep();

    //choose the latest version between configuration.out/configuration.restart
    if(timestepRestart < timestepOut){  //use the newer one
        restartFromConfiguration(CONFIGURATION_OUT, sys, numberOfTimesteps, verbose);
    }
    long finishedTimesteps = sys.getTimestep() - timestepIn;
    return finishedTimesteps;
}