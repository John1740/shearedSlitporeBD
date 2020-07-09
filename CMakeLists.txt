cmake_minimum_required(VERSION 3.14)
project (shearedSlitporeBD VERSION 0.3)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#Linking Boost library
find_package(Boost COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
#link_libraries(${Boost_LIBARIES})
message("Boost_FOUND is ${Boost_FOUND}")
message("Boost_INCLUDE_DIRS is ${Boost_INCLUDE_DIRS}")
message("Boost_LIBRARY_DIRS is ${Boost_LIBRARY_DIRS}")
message("Boost_LIBRARIES is ${Boost_LIBRARIES}")
message("Boost_VERSION is ${Boost_VERSION}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
# Get the current working branch
execute_process(
        COMMAND git rev-parse --abbrev-ref HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_BRANCH
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Get the latest abbreviated commit hash of the working branch
execute_process(
        COMMAND git rev-parse HEAD #git rev-parse HEAD/git log -1 --format=%h
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_COMMIT_HASH
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Get the git version
execute_process(
        COMMAND git --version
        COMMAND sed "s/git version //"  #remove the text infront of it
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_VERSION
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Copy version.h template file and replace GIT_BRANCH and GIT_COMMIT_HASH with their values
configure_file(
        ${CMAKE_SOURCE_DIR}/src/templates/version.h.template
        ${CMAKE_BINARY_DIR}/generated/version.h
)

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
        src/struct/configuration.cpp src/struct/configuration.h
        src/struct/periodic_coordinate.cpp src/struct/periodic_coordinate.h

        src/systems/sheared_slitpore_system.cpp
        src/systems/confined_brownian_particles.cpp

        src/printer/printer.cpp

        src/tools/analysis.cpp src/tools/analysis.h

        src/argument_parser/argparse.cpp src/argument_parser/argparse.h
        src/argument_parser/arguments.cpp src/argument_parser/arguments.h

        src/defaults.h

        src/tools/clock.cpp src/tools/clock.h

        src/tools/my_vector.h

        src/templates/version.h.template
        src/tools/format.cpp src/tools/format.h
        src/printer/stress.cpp src/printer/stress.h
        src/printer/velocity.cpp src/printer/velocity.h
        src/struct/layers.cpp src/struct/layers.h
        src/order_parameter/intra_layer_pair_correlation_function.cpp src/order_parameter/intra_layer_pair_correlation_function.h src/order_parameter/angular_bond_parameter.cpp src/order_parameter/angular_bond_parameter.h src/printer/angular_bond.cpp src/printer/angular_bond.h src/order_parameter/relaxation_modulus.cpp src/order_parameter/relaxation_modulus.h src/order_parameter/stress_fourier_components.cpp src/order_parameter/stress_fourier_components.h src/struct/complex_cartesian_matrix.cpp src/struct/complex_cartesian_matrix.h src/struct/cartesian_coordinate.cpp src/struct/cartesian_coordinate.h)

#build a library first if you want to have multiple executable files!
add_executable(writePairCorrelation
        scripts/writePairCorrelation.cpp
        src/boxmueller.cpp
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
        src/struct/configuration.cpp src/struct/configuration.h
        src/struct/periodic_coordinate.cpp src/struct/periodic_coordinate.h

        src/systems/sheared_slitpore_system.cpp
        src/systems/confined_brownian_particles.cpp

        src/printer/printer.cpp

        src/tools/analysis.cpp src/tools/analysis.h

        src/argument_parser/argparse.cpp src/argument_parser/argparse.h
        src/argument_parser/arguments.cpp src/argument_parser/arguments.h

        src/defaults.h

        src/tools/clock.cpp src/tools/clock.h

        src/tools/my_vector.h

        src/templates/version.h.template
        src/tools/format.cpp src/tools/format.h
        src/printer/stress.cpp src/printer/stress.h
        src/printer/velocity.cpp src/printer/velocity.h
        src/struct/layers.cpp src/struct/layers.h
        src/order_parameter/intra_layer_pair_correlation_function.cpp src/order_parameter/intra_layer_pair_correlation_function.h
        )

target_link_libraries(shearedSlitporeBD ${Boost_LIBRARIES} stdc++fs)    # stdc++fs for filesystem support
target_link_libraries(writePairCorrelation ${Boost_LIBRARIES} stdc++fs)

# Enables finding the version number in the code (#include "version.h")
include_directories(${CMAKE_BINARY_DIR}/generated)