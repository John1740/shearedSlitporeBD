//
// Created by mhuelsberg on 30.07.21.
//

#include "restarts.h"
#include "defaults.h"
#include "boost/format.hpp"
namespace b = boost;

bool restartFromConfiguration(string filename, CONFINED_BROWNIAN_PARTICLES& sys, long timestepIn, long numberOfTimesteps, bool verbose){
    if(verbose){
        cout << "Invoking restart from " << filename << endl;
    }
    bool successful = sys.readConfigurationFromFile(filename, false);
    if(!successful){
        return false;
    }
    long timestepOut = sys.getTimestep();
    long skip = timestepOut - timestepIn;
    float progress = double(skip) / numberOfTimesteps;
    if(verbose){
        cout << "Restarting from timestep " << timestepOut;
        cout << b::format(" (%.0f%% done)") % (100 * progress) << endl;
    }
    return successful;
}

bool restartSimulation(CONFINED_BROWNIAN_PARTICLES& sys, long numberOfTimesteps, bool verbose){
    bool successful = false;
    bool successfulOut = false;
    bool successfulRestart = false;
    //read configuration.out and exit if simulation is already finished
    long timestepIn = sys.getTimestep();
    if(fs::exists(CONFIGURATION_OUT)){
        successfulOut = restartFromConfiguration(CONFIGURATION_OUT, sys, timestepIn, numberOfTimesteps, verbose);
    }
    long timestepOut = sys.getTimestep();

    //read configuration.restart and exit if simulation is already finished
    if(fs::exists(CONFIGURATION_RESTART)){
        successfulRestart = restartFromConfiguration(CONFIGURATION_RESTART, sys, timestepIn, numberOfTimesteps, verbose);
    }
    if(!successfulRestart && fs::exists(CONFIGURATION_RESTART + BACKUP_EXTENSION)){
        successfulRestart = restartFromConfiguration(CONFIGURATION_RESTART + BACKUP_EXTENSION, sys, timestepIn, numberOfTimesteps, verbose);
        if(successfulRestart){
            fs::rename(CONFIGURATION_RESTART + BACKUP_EXTENSION, CONFIGURATION_RESTART);    //if configuration.restart is broken, replace it with the backup
        }
    }
    long timestepRestart = sys.getTimestep();

    //choose the latest version between configuration.out/configuration.restart
    if(timestepRestart < timestepOut){  //use the newer one
        successfulOut = restartFromConfiguration(CONFIGURATION_OUT, sys, timestepIn, numberOfTimesteps, verbose);
    }
    successful = successfulOut || successfulRestart;
    return successful;
}

void saveMilestone(CONFINED_BROWNIAN_PARTICLES& sys, bool verbose){
    if(fs::exists(CONFIGURATION_RESTART)){
        fs::rename(CONFIGURATION_RESTART, CONFIGURATION_RESTART + BACKUP_EXTENSION);
    }
    sys.writeConfigurationToFile(CONFIGURATION_RESTART, true, verbose);
}
