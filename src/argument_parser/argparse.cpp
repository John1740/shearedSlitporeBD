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

void ARGUMENT_PARSER::addOptions() {
    description.add_options()
            ("help,h", "Help screen")
            ("configuration,c", po::value<string>()->default_value(CONFIGURATION_IN), "configuration file (particle positions)")
            ("shearRate,s", po::value<double>()->default_value(SHEAR_RATE), "(constant) shear rate offset")
            ("amplitude,a", po::value<double>()->default_value(SHEAR_RATE), "shear rate amplitude")
            ("period,p", po::value<double>()->default_value(OSCILLATION_PERIOD), "shear rate oscillation period (in units of Brownian time)")
            ("dWall", po::value<double>()->default_value(D_WALL), "distance between walls (z-direction)")
            ("density,d", po::value<double>()->default_value(DENSITY), "density")
            ("numberOfParticles,n", po::value<int>()->default_value(NUMBER_OF_PARTICLES), "number of particles")
            ("charge,Z", po::value<int>()->default_value(CHARGE), "total charge")
            ("diameter", po::value<double>()->default_value(DIAMETER), "diameter of particles")
            ("ssInteractionStrength", po::value<double>()->default_value(SS_INTERACTION_STRENGTH), "strength of softsphere interaction")
            ("wallInteractionStrength", po::value<double>()->default_value(WALL_INTERACTION_STRENGTH), "strength of wall interaction")
            ("dt", po::value<double>()->default_value(DELTA_T), "length of timestep")
            ("temperature,t", po::value<double>()->default_value(TEMPERATURE), "temperature")
            ("D0", po::value<double>()->default_value(DIFFUSION_CONSTANT), "diffusion constant")
            ("timesteps,N", po::value<int>()->default_value(TOTAL_NUMBER_OF_TIMESTEPS), "Number of timesteps the simulations runs for")
            ("seed", po::value<unsigned int>()->default_value(0), "random number generator seed; 0 = random seed will be generated")
            ("printVelocity", po::value<int>()->default_value(PRINT_VELOCITY), "print out velocities every x-th timestep; 0 = no print-outs")
            ("printStress", po::value<int>()->default_value(PRINT_STRESS), "print out stresses every x-th timestep; 0 = no print-outs")
            ("printEnergy", po::value<int>()->default_value(PRINT_ENERGY), "print out energies every x-th timestep; 0 = no print-outs")
            ("snapshot", po::value<int>()->default_value(PRINT_ENERGY), "Save a configuration snapshot every x-th timestep; 0 = no snapshots")
            ("version,v", po::bool_switch()->default_value(false), "print version number and exit")
            ("dry", po::bool_switch()->default_value(false), "do a dry run")
            ;
}

ARGUMENTS ARGUMENT_PARSER::parseArgs() {
    ARGUMENTS args;
    args.configurationIn = variablesMap["configuration"].as<string>();
    args.shearRate = variablesMap["shearRate"].as<double>();
    args.amplitude = variablesMap["amplitude"].as<double>();
    args.oscillationPeriod = variablesMap["period"].as<double>();
    args.dWall = variablesMap["dWall"].as<double>();
    args.density = variablesMap["density"].as<double>();
    args.numberOfParticles = variablesMap["numberOfParticles"].as<int>();
    args.charge = variablesMap["charge"].as<int>();
    args.diameter = variablesMap["diameter"].as<double>();
    args.ssInteractionStrength = variablesMap["ssInteractionStrength"].as<double>();
    args.wallInteractionStrength = variablesMap["wallInteractionStrength"].as<double>();
    args.dt = variablesMap["dt"].as<double>();
    args.temperature = variablesMap["temperature"].as<double>();
    args.D0 = variablesMap["D0"].as<double>();
    args.totalNumberOfTimesteps = variablesMap["timesteps"].as<int>();
    args.seed = variablesMap["seed"].as<unsigned int>();
    args.printVelocity = variablesMap["printVelocity"].as<int>();
    args.printStress = variablesMap["printStress"].as<int>();
    args.printEnergy = variablesMap["printEnergy"].as<int>();
    args.snapshotInterval = variablesMap["snapshot"].as<int>();
    args.printVersion = variablesMap["version"].as<bool>();
    args.dryRun = variablesMap["dry"].as<bool>();
    return args;
}
