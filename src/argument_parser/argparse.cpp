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
            ("configuration,c", po::value<string>()->default_value(CONFIGURATION_IN), "configuration file (particle positions)")
            ("shearRate,s", po::value<double>()->default_value(SHEAR_RATE), "(constant) shear rate offset")
            ("amplitude,a", po::value<double>()->default_value(SHEAR_RATE), "shear rate amplitude")
            ("period,p", po::value<double>()->default_value(OSCILLATION_PERIOD), "shear rate oscillation period (in units of Brownian time)")
            ("ssInteractionStrength", po::value<double>()->default_value(SS_INTERACTION_STRENGTH), "strength of softsphere interaction")
            ("wallInteractionStrength", po::value<double>()->default_value(WALL_INTERACTION_STRENGTH), "strength of wall interaction")
            ("dt", po::value<double>()->default_value(DELTA_T), "length of timestep")
            ("temperature,t", po::value<double>()->default_value(TEMPERATURE), "temperature")
            ("D0", po::value<double>()->default_value(DIFFUSION_CONSTANT), "diffusion constant")
            ("timesteps,N", po::value<int>()->default_value(TOTAL_NUMBER_OF_TIMESTEPS), "Number of timesteps the simulations runs for")
            ("seed", po::value<unsigned int>()->default_value(0), "random number generator seed; 0 = random seed will be generated")
            ("printAll", po::value<int>()->default_value(PRINT_ALL), "print all properties every x-th timestep; "
                                                                     "x<0 -> no print-outs; "
                                                                     "ATTENTION: The calculation will be very slow! "
                                                                     "Gets overwritten by other (non-zero) print-arguments")
            ("printVelocity", po::value<int>()->default_value(PRINT_VELOCITY), "print velocities every x-th timestep; "
                                                                               "x<0 -> no print-outs")
            ("printStress", po::value<int>()->default_value(PRINT_STRESS), "print stresses every x-th timestep; "
                                                                           "x<0 -> no print-outs")
            ("printEnergy", po::value<int>()->default_value(PRINT_ENERGY), "print energies every x-th timestep; "
                                                                           "x<0 -> no print-outs")
            ("printAngularBond", po::value<int>()->default_value(PRINT_ANGULAR_BOND), "print the angular bond order parameter every x-th timestep; "
                                                                                      "x<0 -> no print-outs")
            ("snapshot", po::value<int>()->default_value(PRINT_ENERGY), "Save a configuration snapshot every x-th timestep; "
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
    args.ssInteractionStrength = variablesMap["ssInteractionStrength"].as<double>();
    args.wallInteractionStrength = variablesMap["wallInteractionStrength"].as<double>();
    args.dt = variablesMap["dt"].as<double>();
    args.temperature = variablesMap["temperature"].as<double>();
    args.D0 = variablesMap["D0"].as<double>();
    args.totalNumberOfTimesteps = variablesMap["timesteps"].as<int>();
    args.seed = variablesMap["seed"].as<unsigned int>();
    args.printAll = variablesMap["printAll"].as<int>();
    if(args.printAll > 0){
        args.printVelocity = args.printAll;
        args.printStress = args.printAll;
        args.printEnergy = args.printAll;
        args.printAngularBond = args.printAll;
        args.snapshotInterval = args.printAll;
    }
    if(variablesMap["printVelocity"].as<int>() != PRINT_VELOCITY){
        args.printVelocity = variablesMap["printVelocity"].as<int>();
    }
    if(variablesMap["printStress"].as<int>() != PRINT_STRESS){
        args.printStress = variablesMap["printStress"].as<int>();
    }
    if(variablesMap["printEnergy"].as<int>() != PRINT_ENERGY){
        args.printEnergy = variablesMap["printEnergy"].as<int>();
    }
    if(variablesMap["printAngularBond"].as<int>() != PRINT_ANGULAR_BOND){
        args.printAngularBond = variablesMap["printAngularBond"].as<int>();
    }
    if(variablesMap["snapshot"].as<int>() != SNAPSHOT_INTERVAL){
        args.snapshotInterval = variablesMap["snapshot"].as<int>();
    }
    args.printVersion = variablesMap["version"].as<bool>();
    args.dryRun = variablesMap["dry"].as<bool>();
    args.clear = variablesMap["clear"].as<bool>();
    return args;
}
