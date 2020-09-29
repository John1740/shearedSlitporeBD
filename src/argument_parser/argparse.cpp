#include "argparse.h"

#include <iostream>
using namespace std;

ARGUMENT_PARSER::ARGUMENT_PARSER(int argc, const char* argv[]) {
    try{
        addOptions();
        //decompose command line arguments and put them into variablesMap
        po::store(parse_command_line(argc, argv, description), variablesMap);
        po::notify(variablesMap);

        if(variablesMap.count("help")){
            cout << description << endl;
            exit(0);
        }
    }
    catch(const exception& e){
        cerr << e.what() << endl;
    }
}

//could be divided into logical segments
void ARGUMENT_PARSER::addOptions() {
    description.add_options()
            ("help,h", "Help screen")
            ("settings,s", po::value<string>()->default_value(SETTINGS_IN), "settings file")
            ("configuration,c", po::value<string>()->default_value(CONFIGURATION_IN), "configuration file (particle positions, simulation box)")
            ("shearRate", po::value<double>()->default_value(SHEAR_RATE), "(constant) shear rate offset (in units of 1/Brownian time)")
            ("amplitude,a", po::value<double>()->default_value(AMPLITUDE), "shear rate amplitude (in units of 1/Brownian time)")
            ("period,p", po::value<double>()->default_value(OSCILLATION_PERIOD), "shear rate oscillation period (in units of Brownian time)")
            ("phaseOffset,o", po::value<double>()->default_value(PHASE_OFFSET), "phase offset (in units of Pi)"
                                                                                "(0->cos, -0.5->sin, 1->-cos, 0.5->-sin)")
            ("ssInteractionStrength", po::value<double>()->default_value(SS_INTERACTION_STRENGTH), "strength of softsphere interaction")
            ("wallInteractionStrength", po::value<double>()->default_value(WALL_INTERACTION_STRENGTH), "strength of wall interaction")
            ("dt", po::value<double>()->default_value(0), "length of timestep")
            ("temperature,T", po::value<double>()->default_value(TEMPERATURE), "temperature")
            ("D0", po::value<double>()->default_value(DIFFUSION_CONSTANT), "diffusion constant")
            ("numberOfTimesteps,N", po::value<double>(), "Number of timesteps the simulations runs for")
            ("duration,d", po::value<double>(), "Duration (in Brownian times) the simulations runs for.\n"
                                               "Overwrites --numberOfTimesteps/-N")
            ("numberOfPeriods", po::value<double>(), "Number of oscillation periods the simulations runs for.\n"
                                               "Overwrites --numberOfTimesteps/-N and --duration/-d")
            ("seed", po::value<unsigned int>()->default_value(0), "random number generator seed; 0 = random seed will be generated")
            ("rngCounter", po::value<unsigned long long>()->default_value(0), "initial random number generator counter; 0 = no initial increments")
            ("printAll", po::value<double>()->default_value(PRINT_ALL), "print all properties every x-th timestep; "
                                                                     "x<0 -> no print-outs; "
                                                                     "ATTENTION: The calculation will be very slow! "
                                                                     "Gets overwritten by other (non-zero) print-arguments")
            ("printVelocity", po::value<double>()->default_value(PRINT_VELOCITY), "print velocities every x-th timestep; "
                                                                               "x<0 -> no print-outs")
            ("printStress", po::value<double>()->default_value(PRINT_STRESS), "print stresses every x-th timestep; "
                                                                           "x<0 -> no print-outs")
            ("printStressFourier", po::value<double>()->default_value(PRINT_STRESS_FOURIER), "calculate 0-th to 4-th stress Fourier component using stresses from every x-th timestep; "
                                                                           "x<0 -> no Fourier component calculation")
            ("printEnergy", po::value<double>()->default_value(PRINT_ENERGY), "print energies every x-th timestep; "
                                                                           "x<0 -> no print-outs")
            ("printAngularBond", po::value<double>()->default_value(PRINT_ANGULAR_BOND), "print the angular bond order parameter every x-th timestep; "
                                                                                      "x<0 -> no print-outs")
            ("printSnapshots", po::value<double>()->default_value(PRINT_SNAPSHOTS), "Save a configuration snapshot every x-th timestep; "
                                                                        "x<0 -> no snapshots")
            ("printSnapshotsDuration", po::value<double>(), "Same as --printSnapshots but in units of total simulation time.")
            ("printSnapshotsPeriod", po::value<double>(), "Same as --printSnapshots but in units of oscillation periods.")
            ("printPairCorrelation", po::value<double>()->default_value(PRINT_PAIR_CORRELATION), "print intra-layer pair correlation function every x-th timestep; "
                                                                        "x<0 -> no print-outs")
            ("printPairCorrelationDuration", po::value<double>(), "Same as --printPairCorrelation but in units of total simulation time")
            ("printPairCorrelationPeriod", po::value<double>(), "Same as --printPairCorrelation but in units of oscillation periods.")
            ("version,v", po::bool_switch()->default_value(false), "print version number and exit")
            ("dry", po::bool_switch()->default_value(false), "do a dry run")
            ("clear", po::bool_switch()->default_value(CLEAR), "clear all existing output files (before simulation start)")
            ;
}

ARGUMENTS ARGUMENT_PARSER::parseArgs() {
    ARGUMENTS args;
    args.settingsIn = variablesMap["settings"].as<string>();
    args.configurationIn = variablesMap["configuration"].as<string>();
    args.shearRate = variablesMap["shearRate"].as<double>();
    args.amplitude = variablesMap["amplitude"].as<double>();
    args.oscillationPeriod = variablesMap["period"].as<double>();
    args.phaseOffset = variablesMap["phaseOffset"].as<double>();
    args.ssInteractionStrength = variablesMap["ssInteractionStrength"].as<double>();
    args.wallInteractionStrength = variablesMap["wallInteractionStrength"].as<double>();
    args.dt = variablesMap["dt"].as<double>();
    args.temperature = variablesMap["temperature"].as<double>();
    args.D0 = variablesMap["D0"].as<double>();
    if(variablesMap.count("numberOfTimesteps")){
        args.numberOfTimesteps = round(variablesMap["numberOfTimesteps"].as<double>());
    }
    else{
        args.numberOfTimesteps = 0;
    }
    if(variablesMap.count("duration")){
        args.setDuration(variablesMap["duration"].as<double>());
    }
    if(variablesMap.count("numberOfPeriods")){
        args.setNumberOfPeriods(variablesMap["numberOfPeriods"].as<double>());
    }
    args.seed = variablesMap["seed"].as<unsigned int>();
    args.rngCounter = variablesMap["rngCounter"].as<unsigned long long>();

    //doubles are allowed as input for convenience (allows 1e5 float terminology)
    args.printVelocity = round(variablesMap["printVelocity"].as<double>());
    args.printStress = round(variablesMap["printStress"].as<double>());
    args.printStressFourier = round(variablesMap["printStressFourier"].as<double>());
    args.printEnergy = round(variablesMap["printEnergy"].as<double>());
    args.printAngularBond = round(variablesMap["printAngularBond"].as<double>());
    args.printSnapshots = round(variablesMap["printSnapshots"].as<double>());
    if(variablesMap.count("printSnapshotsDuration")){
        args.setSnapshotDuration(variablesMap["printSnapshotsDuration"].as<double>());
    }
    if(variablesMap.count("printSnapshotsPeriod")){
        args.setSnapshotPeriod(variablesMap["printSnapshotsPeriod"].as<double>());
    }
    args.printPairCorrelation.interval = round(variablesMap["printPairCorrelation"].as<double>());
    if(variablesMap.count("printPairCorrelationDuration")){
        args.printPairCorrelation.setDuration(variablesMap["printPairCorrelationDuration"].as<double>());
    }
    if(variablesMap.count("printPairCorrelationPeriod")){
        args.printPairCorrelation.setPeriod(variablesMap["printPairCorrelationPeriod"].as<double>());
    }

    args.printAll = round(variablesMap["printAll"].as<double>());
    // overwrite print-statements by printAll if not further specified
    if(args.printAll > 0){
        if(args.printVelocity == PRINT_VELOCITY) args.printVelocity = args.printAll;
        if(args.printStress == PRINT_STRESS) args.printStress = args.printAll;
        if(args.printStressFourier == PRINT_STRESS_FOURIER) args.printStressFourier = 1;
        if(args.printEnergy == PRINT_ENERGY) args.printEnergy = args.printAll;
        if(args.printAngularBond == PRINT_ANGULAR_BOND) args.printAngularBond = args.printAll;
        if(args.printSnapshots == PRINT_SNAPSHOTS
            && args.getSnapshotDuration() == 0
            && args.getSnapshotPeriod() == 0) args.printSnapshots = args.printAll;
        if(args.printPairCorrelation.interval == PRINT_PAIR_CORRELATION
            && args.printPairCorrelation.getDuration() == 0
            && args.printPairCorrelation.getPeriod() == 0) args.printPairCorrelation.interval = args.printAll;
    }
    args.printVersion = variablesMap["version"].as<bool>();
    args.dry = variablesMap["dry"].as<bool>();
    args.clear = variablesMap["clear"].as<bool>();
    return args;
}
