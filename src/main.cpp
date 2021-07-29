#include "tools/clock.h"
#include "version.h"
#include "tools/format.h"
#include "boost/format.hpp"
#include <boost/progress.hpp>

namespace b = boost;

#include "global.h" //contains random_event definition

extern CRandomMersenne random_event;    //use global instance of random_event

#include "systems/sheared_slitpore_system.h"

//#include "printer/printer.h"
#include "printer/stress.h"
#include "printer/layer_position.h"
#include "printer/layer_velocity.h"
#include "printer/angular_bond.h"
#include "order_parameter/stress_fourier_components.h"
#include "order_parameter/intra_layer_pair_correlation_function.h"

#include <experimental/filesystem>

namespace fs = experimental::filesystem;

long restartFromConfiguration(string filename, CONFINED_BROWNIAN_PARTICLES& sys, long numberOfTimesteps, bool verbose=true){
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

int main(int argc, const char* argv[]){
    CLOCK clock;

    ARGUMENT_PARSER parser(argc, argv);
    ARGUMENTS argsParsed = parser.parseArgs();
    ARGUMENTS args;
    if(fs::exists(argsParsed.settingsIn)){
        args.readFromFile(argsParsed.settingsIn);
    }
    else{
        argsParsed.settingsIn += string(" (not existing)");
    }
    args.update(argsParsed);    //argsParsed have priority
    args.finalize();  //dt-defaulting and matching of numberOfTimesteps

    cout << surroundWithSeparator("shearedSlitporeBD") << endl << endl;

    //print version details
    cout << surroundWithSeparator("Version Details") << endl;
    cout << "Version: " << PROJECT_VERSION << endl;
    cout << "Git branch: " << GIT_BRANCH << endl;
    cout << "Git commit: " << GIT_COMMIT_HASH << endl;
    cout << "Git version: " << GIT_VERSION << endl;
    cout << surroundWithSeparator("", 60, 1, '#', false) << endl << endl;
    if(args.printVersion){
        exit(0);
    }

    cout << "Task started at " << clock.readTimePoint(0) << endl << endl;

    //generate or read seed
    if(args.seed == 0){
        args.seed = getpid() * time(0); //dunno where getpid()-definition was imported from (unistd.h)
    }

    //print parsed arguments
    cout << surroundWithSeparator("Parsed arguments/System parameters") << endl;
    cout << args << endl;

    //initialize Slitpore System
    cout << surroundWithSeparator("System Initialization") << endl;
    //initialize RNG with seed (and skip steps if asked for)
    random_event.RandomInit(args.seed);
    if(args.rngCounter != 0){
        for(unsigned long long int i = 0; i < args.rngCounter; i++){
            random_event.Random();
        }
        cout << "Called random number generator " << args.rngCounter << " times." << endl;
    }

    SHEARED_SLITPORE_SYSTEM sys(args);

    cout << sys << endl << endl;

    //clear
    bool restart = true;
    if(args.clear){
        cout << "Clearing all existing output-files!" << endl;
        if(restart){
            cout << "Restarts (--restart) are not invoked because --clear is active." << endl;
        }
        fs::remove(CONFIGURATION_OUT);
        fs::remove(SNAPSHOTS);
        fs::remove(STRESSES_OUT);
        fs::remove(LAYER_POSITIONS_OUT);
        fs::remove(LAYER_VELOCITIES_OUT);
        fs::remove(ANGULAR_BOND_OUT);
        fs::remove(PAIR_CORRELATION_OUT);
        fs::remove("configuration.restart");
        fs::remove_all(ERRONEOUS);
    }

    //check if calculation was already finished and needs to be extended
    long timestepOriginal = sys.getTimestep();
    if(fs::exists(CONFIGURATION_OUT)){
        restartFromConfiguration(CONFIGURATION_OUT, sys, args.numberOfTimesteps);
    }
    long timestepNew = sys.getTimestep();

    //restart
    if(restart && fs::exists("configuration.restart")){
        restartFromConfiguration("configuration.restart", sys, args.numberOfTimesteps);
    }
    long timestepRestart = sys.getTimestep();
    if(timestepRestart < timestepNew){  //use the newer one
        restartFromConfiguration(CONFIGURATION_OUT, sys, args.numberOfTimesteps);
    }

    if(args.dry){
        cout << "This was a dry run. To do an actual run, remove the '--dry' option!" << endl;
        exit(0);
    }

    //Simulation start
    cout << endl << surroundWithSeparator("Simulation start") << endl;

    //Skip first few steps
    //TODO: implement restarts
    if(args.skip){
        clock.addTimePoint();
        cout << "Skipping first " << args.skip << " timesteps. " << endl;
        long timestep = sys.getTimestep();
        b::progress_display progress(args.skip);
        for(int i = 0; i < args.skip; i++){
            sys.simulateForSteps(1);
            ++progress;
        }
        sys.setTimestep(timestep);
        clock.addTimePoint();
        cout << "Skipping done ... " << clock.readDuration(-2, -1, "%02d:%02d:%06.3f").c_str() << endl;
        sys.writeConfigurationToFile("configuration.in.skipped", true, true);
    }

    LAYER_POSITION_PRINTER layerPosition(&sys);
    LAYER_VELOCITY_PRINTER layerVelocity(&sys);
    STRESS_PRINTER stress(&sys);
    ANGULAR_BOND_PRINTER angularBond(&sys);
    STRESS_FOURIER_COMPONENTS fc(args);

    cout << "Starting simulation with print-outs (" << args.numberOfTimesteps << " timesteps)." << endl;
    clock.addTimePoint();
    long skip = sys.getTimestep() - timestepOriginal;
    b::progress_display progress(args.numberOfTimesteps);
    for(long i = 0; i < skip; i++){     //skip to correct progress if restart was invoked
        ++progress;
    }

    for(long i = skip; i < args.numberOfTimesteps; i++){
        // write restart configuration file every x timesteps/seconds
        if(args.numberOfTimesteps < 10 || i % (args.numberOfTimesteps / 10) == 0){
            sys.writeConfigurationToFile("configuration.restart", true, false);
        }
        if(args.printSnapshots > 0 && i % args.printSnapshots == 0){
            sys.writeConfigurationToFile("snapshots.out", false, false);
        }
        if(args.printLayerPosition > 0 && i % args.printLayerPosition == 0){
            layerPosition.printLine();
        }
        if(args.printAngularBond > 0 && i % args.printAngularBond == 0){
            angularBond.printLine();
        }
        if(args.printPairCorrelation > 0 && i % args.printPairCorrelation == 0){
            INTRA_LAYER_PAIR_CORRELATION_FUNCTION pC(sys);
            pC.calculateAverageLayerCorrelation();
            pC.print(PAIR_CORRELATION_OUT, false, "timestep: " + to_string(i));
        }
        sys.simulateForSteps(1);
        if(args.printStress > 0 && i % args.printStress == 0){
            stress.printLine();
        }
        if(args.printStressFourier > 0 && i % args.printStressFourier == 0){
            fc.addTimestep(sys);
        }
        if(args.printLayerVelocity > 0 && i > 0 && (i - 1) % args.printLayerVelocity == 0){
            layerVelocity.printLine();
        }
        ++progress;
    }
    clock.addTimePoint();
    cout << "Simulation done ... " << clock.readDuration(-2, -1, "%02d:%02d:%06.3f").c_str() << endl;
    sys.writeConfigurationToFile(CONFIGURATION_OUT, true);
    cout << "rngCounter: " << random_event.rngCounter << endl;

    //one more iteration for last velocity step (might cause minor problems if simulation is restarted without same seed and correct RNG counter)
    sys.simulateForSteps(1);
    if(args.printLayerVelocity > 0 && args.numberOfTimesteps > 0 &&
       (args.numberOfTimesteps - 1) % args.printLayerVelocity == 0){
        layerVelocity.printLine();
    }

    if(args.printStress > 0){
        cout << b::format("Printed stresses to %s") % stress.getFilename().c_str() << endl;
    }
    if(args.printLayerPosition > 0){
        cout << b::format("Printed layer positions to %s") % layerPosition.getFilename().c_str() << endl;
    }
    if(args.printLayerVelocity > 0){
        cout << b::format("Printed layer velocities to %s") % layerVelocity.getFilename().c_str() << endl;
    }
    if(args.printAngularBond > 0){
        cout << b::format("Printed angular bond parameters to %s") % angularBond.getFilename().c_str() << endl;
    }
    if(args.printPairCorrelation > 0){
        cout << b::format("Printed pair correlations to %s") % PAIR_CORRELATION_OUT << endl;
    }
    if(args.printStressFourier > 0){
        cout << endl << fc << endl;
        cout << "Storage modulus [kT/d^3]: " << fc.calculateStorageModulus() << endl;
        cout << "Loss modulus [kT/d^3]: " << fc.calculateLossModulus() << endl;
        for(int i = 0; i <= 4; i++){
            cout << "Fourier component (xz) (n= " << i << "): " << fc.calculate(i).xz << endl;
            if(i > 0){
                cout << "Fourier component (xz) (n=" << -i << "): " << fc.calculate(-i).xz << endl;
            }
        }
    }

    cout << endl << surroundWithSeparator("Simulation end") << endl;

    clock.addTimePoint();
    cout << endl << "Task finished at " << clock.readTimePoint(-1) << endl;
    cout << b::format("Task finished in %.3f seconds (%s)") % clock.getDuration(0, -1) %
            clock.readDuration(0, -1).c_str() << endl;
    cout << endl;

    return 0;
}