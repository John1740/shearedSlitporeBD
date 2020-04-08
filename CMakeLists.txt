cmake_minimum_required(VERSION 2.6) 
project (shearedSlitporeBD)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -lboost_program_options")

FIND_PACKAGE(Boost COMPONENTS program_options REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

add_executable(shearedSlitporeBD
 
        src/boxmueller.cpp
        src/main.cpp
        src/mersenne.cpp
        src/global.cpp

        src/interactions/dlvo_softsphere_interaction.cpp
        src/interactions/lennard_jones_interaction.cpp

        src/external/shear_force.cpp
        src/external/soft_wall_force.cpp

        src/command/average_stress.cpp
        src/command/calculate_forces.cpp
        src/command/generate_square_layers.cpp

        src/struct/charged_particle.cpp
        src/struct/particle.cpp
        src/struct/slit_pore_box.cpp
        src/struct/cartesian_coordinate.cpp
        src/struct/cartesian_matrix.cpp

        src/systems/sheared_slitpore_system.cpp
        src/systems/confined_brownian_particles.cpp

        src/tools/printer.cpp

        src/helpers/analysis.cpp src/helpers/analysis.h

        src/argument_parser/argparse.cpp src/argument_parser/argparse.h src/defaults.h src/argument_parser/arguments.cpp src/argument_parser/arguments.h)

TARGET_LINK_LIBRARIES(shearedSlitporeBD ${Boost_LIBRARIES})