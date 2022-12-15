cmake_minimum_required(VERSION 3.14)
project(shearedSlitporeBD VERSION 1.1)
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

#find_package(PkgConfig)
#pkg_check_modules(HDF5PP REQUIRED HDF5pp)
#include_directories(${HDF5PP_INCLUDE_DIRS})

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

add_executable(
        shearedSlitporeBD
        src/main.cpp

        src/rng/boxmueller.cpp
        src/rng/mersenne.cpp
        src/global.cpp

        src/interactions/dlvo_softsphere_interaction.cpp
        src/interactions/lennard_jones_interaction.cpp

        src/external/shear_force.cpp
        src/external/soft_wall_force.cpp

        src/command/average_stress.cpp
        src/command/calculate_forces.cpp
        src/command/generate_square_layers.cpp
        src/command/generate_hexagonal_layers.cpp

        src/struct/cartesian_c.h
        src/struct/cartesian_coordinate.cpp
        src/struct/cartesian_coordinate.h
        src/struct/periodic_coordinate.cpp
        src/struct/periodic_coordinate.h
        src/struct/cartesian_m.h
        src/struct/cartesian_matrix.cpp
        src/struct/cartesian_matrix.h

        src/struct/particle.cpp
        src/struct/charged_particle.cpp
        src/struct/slit_pore_box.cpp
        src/struct/configuration.cpp
        src/struct/configuration.h
        src/struct/layers.cpp
        src/struct/layers.h

        src/systems/sheared_slitpore_system.cpp
        src/systems/confined_brownian_particles.cpp

        src/printer/printer.cpp
        src/printer/stress.cpp
        src/printer/stress.h
        src/printer/layer_velocity.cpp
        src/printer/layer_velocity.h
        src/printer/angular_bond.cpp
        src/printer/angular_bond.h

        src/argument_parser/argparse.cpp
        src/argument_parser/argparse.h
        src/argument_parser/arguments.cpp
        src/argument_parser/arguments.h

        src/defaults.h
        src/templates/version.h.template

        src/tools/clock.cpp src/tools/clock.h
        src/tools/my_vector.h
        src/tools/format.cpp src/tools/format.h
        src/tools/analysis.cpp src/tools/analysis.h

        src/order_parameter/z_density_distribution.cpp
        src/order_parameter/z_density_distribution.h
        src/order_parameter/intra_layer_pair_correlation_function.cpp
        src/order_parameter/intra_layer_pair_correlation_function.h
        src/order_parameter/angular_bond_parameter.cpp
        src/order_parameter/angular_bond_parameter.h
        src/order_parameter/relaxation_modulus.cpp
        src/order_parameter/relaxation_modulus.h
        src/order_parameter/stress_fourier_components.cpp
        src/order_parameter/stress_fourier_components.h
        src/order_parameter/system_energy.cpp
        src/order_parameter/system_energy.h
        src/order_parameter/particle_angular_bond.cpp
        src/order_parameter/particle_angular_bond.h

        src/argument_parser/print_intervals.cpp
        src/argument_parser/print_intervals.h
        src/printer/layer_position.cpp
        src/printer/layer_position.h
        src/interfaces/shear_protocol.h
        src/external/oscillatory_shear.cpp
        src/external/oscillatory_shear.h
        src/restarts.cpp src/restarts.h src/cpuinfo.cpp src/cpuinfo.h src/tools/string.cpp src/tools/string.h)

#build a library first if you want to have multiple executable files!
add_executable(
        writePairCorrelation
        scripts/writePairCorrelation.cpp

        src/rng/boxmueller.cpp
        src/rng/mersenne.cpp
        src/global.cpp

        src/command/calculate_forces.cpp


        src/struct/cartesian_c.h
        src/struct/cartesian_coordinate.cpp
        src/struct/cartesian_coordinate.h

        src/struct/particle.cpp
        src/struct/charged_particle.cpp
        src/struct/slit_pore_box.cpp
        src/struct/layers.cpp
        src/struct/layers.h

        src/systems/confined_brownian_particles.cpp

        src/printer/printer.cpp

        src/tools/clock.cpp
        src/tools/clock.h

        src/order_parameter/intra_layer_pair_correlation_function.cpp
        src/order_parameter/intra_layer_pair_correlation_function.h
        
        src/order_parameter/z_density_distribution.cpp
        src/order_parameter/z_density_distribution.h
)

add_executable(
        interactionParameters
        scripts/interactionParameters.cpp

        src/interactions/dlvo_softsphere_interaction.cpp
        src/interactions/dlvo_softsphere_interaction.h

        src/interactions/lennard_jones_interaction.cpp
        src/interactions/lennard_jones_interaction.h
)

add_executable(
        writePotential
        scripts/writePotential.cpp

        src/interactions/dlvo_softsphere_interaction.cpp
        src/interactions/dlvo_softsphere_interaction.h

        src/interactions/lennard_jones_interaction.cpp
        src/interactions/lennard_jones_interaction.h
)

add_executable(
        generateSquareLayers
        scripts/generateSquareLayers.cpp

        #generateHexagonalLayers
        #scripts/generateHexagonalLayers.cpp

        src/rng/boxmueller.cpp
        src/rng/mersenne.cpp
        src/global.cpp

        src/command/calculate_forces.cpp
        src/command/generate_square_layers.cpp

        src/struct/cartesian_c.h
        src/struct/cartesian_coordinate.cpp
        src/struct/cartesian_coordinate.h

        src/struct/particle.cpp
        src/struct/charged_particle.cpp
        src/struct/slit_pore_box.cpp
        src/struct/layers.cpp
        src/struct/layers.h

        src/systems/confined_brownian_particles.cpp
        src/systems/sheared_slitpore_system.cpp

        src/interactions/dlvo_softsphere_interaction.cpp
        src/interactions/lennard_jones_interaction.cpp

        src/external/shear_force.cpp
        src/external/soft_wall_force.cpp

        src/argument_parser/print_intervals.cpp
        src/argument_parser/print_intervals.h
        src/printer/layer_position.cpp
        src/printer/layer_position.h
        src/interfaces/shear_protocol.h
        src/external/oscillatory_shear.cpp
        src/external/oscillatory_shear.h

        src/printer/printer.cpp
)

add_executable(
        generateHexagonalLayers
        scripts/generateHexagonalLayers.cpp

        src/rng/boxmueller.cpp
        src/rng/mersenne.cpp
        src/global.cpp

        src/command/calculate_forces.cpp
        src/command/generate_hexagonal_layers.cpp

        src/struct/cartesian_c.h
        src/struct/cartesian_coordinate.cpp
        src/struct/cartesian_coordinate.h

        src/struct/particle.cpp
        src/struct/charged_particle.cpp
        src/struct/slit_pore_box.cpp
        src/struct/layers.cpp
        src/struct/layers.h

        src/systems/confined_brownian_particles.cpp
        src/systems/sheared_slitpore_system.cpp

        src/interactions/dlvo_softsphere_interaction.cpp
        src/interactions/lennard_jones_interaction.cpp

        src/external/shear_force.cpp
        src/external/soft_wall_force.cpp

        src/argument_parser/print_intervals.cpp
        src/argument_parser/print_intervals.h
        src/printer/layer_position.cpp
        src/printer/layer_position.h
        src/interfaces/shear_protocol.h
        src/external/oscillatory_shear.cpp
        src/external/oscillatory_shear.h

        src/printer/printer.cpp
)


add_executable(
        generateRandomLayers
        scripts/generateRandomLayers.cpp

        src/rng/boxmueller.cpp
        src/rng/mersenne.cpp
        src/global.cpp

        src/command/calculate_forces.cpp
        src/command/generate_random_layers.cpp

        src/struct/cartesian_c.h
        src/struct/cartesian_coordinate.cpp
        src/struct/cartesian_coordinate.h

        src/struct/particle.cpp
        src/struct/charged_particle.cpp
        src/struct/slit_pore_box.cpp
        src/struct/layers.cpp
        src/struct/layers.h

        src/systems/confined_brownian_particles.cpp
        src/systems/sheared_slitpore_system.cpp

        src/interactions/dlvo_softsphere_interaction.cpp
        src/interactions/lennard_jones_interaction.cpp

        src/external/shear_force.cpp
        src/external/soft_wall_force.cpp

        src/argument_parser/print_intervals.cpp
        src/argument_parser/print_intervals.h
        src/printer/layer_position.cpp
        src/printer/layer_position.h
        src/interfaces/shear_protocol.h
        src/external/oscillatory_shear.cpp
        src/external/oscillatory_shear.h

        src/printer/printer.cpp
)



add_executable(
        monteCarlo
        scripts/moneCarlo.cpp


        src/rng/boxmueller.cpp
        src/rng/mersenne.cpp
        src/global.cpp

        src/command/calculate_forces.cpp
        src/command/generate_hexagonal_layers.cpp
        src/command/generate_square_layers.cpp
        src/command/generate_random_layers.cpp

        src/struct/cartesian_c.h
        src/struct/cartesian_coordinate.cpp
        src/struct/cartesian_coordinate.h

        src/struct/particle.cpp
        src/struct/charged_particle.cpp
        src/struct/slit_pore_box.cpp
        src/struct/layers.cpp
        src/struct/layers.h

        src/systems/confined_brownian_particles.cpp
        src/systems/sheared_slitpore_system.cpp

        src/interactions/dlvo_softsphere_interaction.cpp
        src/interactions/lennard_jones_interaction.cpp

        src/external/shear_force.cpp
        src/external/soft_wall_force.cpp

        src/argument_parser/print_intervals.cpp
        src/argument_parser/print_intervals.h
        src/printer/layer_position.cpp
        src/printer/layer_position.h
        src/interfaces/shear_protocol.h
        src/external/oscillatory_shear.cpp
        src/external/oscillatory_shear.h

        src/printer/printer.cpp
        src/printer/stress.cpp
        src/printer/stress.h
        src/printer/layer_velocity.cpp
        src/printer/layer_velocity.h
        src/printer/angular_bond.cpp
        src/printer/angular_bond.h
        src/order_parameter/angular_bond_parameter.cpp
        src/order_parameter/angular_bond_parameter.h
)

target_link_libraries(shearedSlitporeBD ${Boost_LIBRARIES} stdc++fs)    # stdc++fs for filesystem support
target_link_libraries(writePairCorrelation ${Boost_LIBRARIES} stdc++fs)
target_link_libraries(interactionParameters ${Boost_LIBRARIES} stdc++fs)
target_link_libraries(writePotential ${Boost_LIBRARIES} stdc++fs)
target_link_libraries(generateSquareLayers ${Boost_LIBRARIES} stdc++fs)
target_link_libraries(generateHexagonalLayers ${Boost_LIBRARIES} stdc++fs)
target_link_libraries(generateRandomLayers ${Boost_LIBRARIES} stdc++fs)
target_link_libraries(monteCarlo ${Boost_LIBRARIES} stdc++fs)

# Enables finding the version number in the code (#include "version.h")
include_directories(${CMAKE_BINARY_DIR}/generated)
#include_directories(/home/ckahriman/local/HDF5/hdf/HDF5-1.12.2-Linux/HDF_Group/HDF5/1.12.2/include)
