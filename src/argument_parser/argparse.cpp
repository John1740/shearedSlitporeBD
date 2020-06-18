#include "argparse.h"

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
            ("configuration,c", po::value<string>()->default_value(CONFIGURATION_IN), "configuration file (particle positions, simulation box)")
            ("shearRate,s", po::value<double>()->default_value(SHEAR_RATE), "(constant) shear rate offset (in units of 1/Brownian time)")
            ("amplitude,a", po::value<double>()->default_value(AMPLITUDE), "shear rate amplitude (in units of 1/Brownian time)")
            ("period,p", po::value<double>()->default_value(OSCILLATION_PERIOD), "shear rate oscillation period (in units of Brownian time)")
            ("phaseOffset,o", po::value<double>()->default_value(PHASE_OFFSET), "phase offset (in units of Pi)"
                                                                                "(0->cos, -0.5->sin, 1->-cos, 0.5->-sin)")
            ("ssInteractionStrength", po::value<double>()->default_value(SS_INTERACTION_STRENGTH), "strength of softsphere interaction")
            ("wallInteractionStrength", po::value<double>()->default_value(WALL_INTERACTION_STRENGTH), "strength of wall interaction")
            ("dt", po::value<double>()->default_value(DELTA_T), "length of timestep")
            ("temperature,T", po::value<double>()->default_value(TEMPERATURE), "temperature")
            ("D0", po::value<double>()->default_value(DIFFUSION_CONSTANT), "diffusion constant")
            ("timesteps,N", po::value<double>()->default_value(TOTAL_NUMBER_OF_TIMESTEPS), "Number of timesteps the simulations runs for")
            ("seed", po::value<unsigned int>()->default_value(0), "random number generator seed; 0 = random seed will be generated")
            ("printAll", po::value<double>()->default_value(PRINT_ALL), "print all properties every x-th timestep; "
                                                                     "x<0 -> no print-outs; "
                                                                     "ATTENTION: The calculation will be very slow! "
                                                                     "Gets overwritten by other (non-zero) print-arguments")
            ("printVelocity", po::value<double>()->default_value(PRINT_VELOCITY), "print velocities every x-th timestep; "
                                                                               "x<0 -> no print-outs")
            ("printStress", po::value<double>()->default_value(PRINT_STRESS), "print stresses every x-th timestep; "
                                                                           "x<0 -> no print-outs")
            ("stressFourier", po::value<double>()->default_value(STRESS_FOURIER), "calculate 0-th to 4-th stress Fourier component using stresses from every x-th timestep; "
                                                                           "x<0 -> no Fourier component calculation")
            ("printEnergy", po::value<double>()->default_value(PRINT_ENERGY), "print energies every x-th timestep; "
                                                                           "x<0 -> no print-outs")
            ("printAngularBond", po::value<double>()->default_value(PRINT_ANGULAR_BOND), "print the angular bond order parameter every x-th timestep; "
                                                                                      "x<0 -> no print-outs")
            ("snapshot", po::value<double>()->default_value(SNAPSHOT_INTERVAL), "Save a configuration snapshot every x-th timestep; "
                                                                        "x<0 -> no snapshots")
            ("version,v", po::bool_switch()->default_value(false), "print version number and exit")
            ("dry", po::bool_switch()->default_value(false), "do a dry run")
            ("clear", po::bool_switch()->default_value(CLEAR), "clear all existing output files (before simulation start)")
            ;
}

ARGUMENTS ARGUMENT_PARSER::parseArgs() {
    ARGUMENTS args;
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
    args.totalNumberOfTimesteps = round(variablesMap["timesteps"].as<double>());
    args.seed = variablesMap["seed"].as<unsigned int>();
    
    //doubles are allowed as input for convenience (allows 1e5 float terminology)
    int printAll = round(variablesMap["printAll"].as<double>());
    int printVelocity = round(variablesMap["printVelocity"].as<double>());
    int printStress = round(variablesMap["printStress"].as<double>());
    int stressFourier = round(variablesMap["stressFourier"].as<double>());
    int printEnergy = round(variablesMap["printEnergy"].as<double>());
    int printAngularBond = round(variablesMap["printAngularBond"].as<double>());
    int snapshotInterval = round(variablesMap["snapshot"].as<double>());
    args.printAll = printAll;
    if(args.printAll > 0){
        args.printVelocity = printAll;
        args.printStress = printAll;
        args.stressFourier = 1;
        args.printEnergy = printAll;
        args.printAngularBond = printAll;
        args.snapshotInterval = printAll;
    }
    if(printVelocity != PRINT_VELOCITY){
        args.printVelocity = printVelocity;
    }
    if(printStress != PRINT_STRESS){
        args.printStress = printStress;
    }
    if(stressFourier != STRESS_FOURIER){
        args.stressFourier = stressFourier;
    }
    if(printEnergy != PRINT_ENERGY){
        args.printEnergy = printEnergy;
    }
    if(printAngularBond != PRINT_ANGULAR_BOND){
        args.printAngularBond = printAngularBond;
    }
    if(snapshotInterval != SNAPSHOT_INTERVAL){
        args.snapshotInterval = snapshotInterval;
    }
    args.printVersion = variablesMap["version"].as<bool>();
    args.dryRun = variablesMap["dry"].as<bool>();
    args.clear = variablesMap["clear"].as<bool>();
    return args;
}
