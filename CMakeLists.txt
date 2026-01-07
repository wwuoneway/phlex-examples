cmake_minimum_required(VERSION 3.31)
project(my_phlex_example VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost REQUIRED json)
find_package(TBB REQUIRED)
find_package(spdlog REQUIRED)
find_package(phlex REQUIRED)
find_package(ROOT REQUIRED COMPONENTS Physics EG Core RIO Tree TreePlayer)

# Register data product with ROOT so TTreeReader can read it
set(FORM_DATA_PROD_LIB_NAME "form_test_data_products")
find_package(ROOT REQUIRED COMPONENTS Physics EG Core RIO Tree TreePlayer)
#add_library(${FORM_DATA_PROD_LIB_NAME} SHARED MCParticle.cxx MCTrajectory.cxx) #REFLEX_GENERATE_DICTIONARY doesn't work trivially without making a shared library
#target_link_libraries(${FORM_DATA_PROD_LIB_NAME} ROOT::Physics ROOT::EG)

include_directories(${ROOT_INCLUDE_DIRS})

REFLEX_GENERATE_DICTIONARY(${FORM_DATA_PROD_LIB_NAME} dict.h SELECTION classes_def.xml) #OPTIONS "-Werror")

add_library(${FORM_DATA_PROD_LIB_NAME} SHARED ${FORM_DATA_PROD_LIB_NAME}.cxx MCParticle.cxx MCTrajectory.cxx) #REFLEX_GENERATE_DICTIONARY doesn't work trivially without making a shared library
target_link_libraries(${FORM_DATA_PROD_LIB_NAME} ROOT::Physics ROOT::EG)

# Proxies for framework-agnostic experiment libraries
# N.B. The specified library type should be SHARED.
add_library(my_add SHARED my_add.cpp)

add_library(print_mcparticles SHARED print_mcparticles.cpp)
target_link_libraries(print_mcparticles PRIVATE ${FORM_DATA_PROD_LIB_NAME} ROOT::Core ROOT::Physics ROOT::EG ROOT::RIO)

# Register providers for data products
add_library(ij_source MODULE ij_source.cpp)
target_link_libraries(ij_source PRIVATE phlex::module)

add_library(mcparticle_source MODULE mcparticle_source.cpp)
target_link_libraries(mcparticle_source PRIVATE phlex::module ROOT::Core ROOT::Tree ROOT::TreePlayer ROOT::Physics ROOT::EG ROOT::RIO)

# Register experiment libraries with Phlex
add_library(module MODULE module.cpp)
target_link_libraries(module PRIVATE phlex::module my_add)

add_library(mcparticles_module MODULE mcparticles_module.cpp)
target_link_libraries(mcparticles_module PRIVATE phlex::module print_mcparticles) # ${FORM_DATA_PROD_LIB_NAME} ROOT::Core ROOT::Physics ROOT::EG ROOT::RIO)
