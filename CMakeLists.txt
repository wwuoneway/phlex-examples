cmake_minimum_required(VERSION 3.31)
project(my_phlex_example VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "14.1")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "15")
      add_compile_options(-Wno-stringop-overflow)
    endif()
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "16")
      add_compile_options(-Wno-array-bounds)
    endif()
  endif()
endif()

find_package(Boost REQUIRED json)
find_package(TBB REQUIRED)
find_package(spdlog REQUIRED)
find_package(phlex REQUIRED)
find_package(ROOT REQUIRED COMPONENTS Physics EG Core RIO Tree TreePlayer)

# Register data product with ROOT so TTreeReader can read it
set(FORM_DATA_PROD_LIB_NAME "form_test_data_products")
find_package(ROOT REQUIRED COMPONENTS Physics EG Core RIO Tree TreePlayer)

include_directories(${ROOT_INCLUDE_DIRS})

REFLEX_GENERATE_DICTIONARY(${FORM_DATA_PROD_LIB_NAME} dict.h SELECTION classes_def.xml)

add_library(${FORM_DATA_PROD_LIB_NAME} SHARED ${FORM_DATA_PROD_LIB_NAME}.cxx MCParticle.cxx MCTrajectory.cxx track.cpp gaus_hit_finder/copied_from_larsoft_minor_edits/Wire.cxx gaus_hit_finder/copied_from_larsoft_minor_edits/Hit.cxx)
target_link_libraries(${FORM_DATA_PROD_LIB_NAME} ROOT::Physics ROOT::EG)

add_compile_options(-Wall -Wpedantic -Werror)
add_subdirectory(gaus_hit_finder)

# Proxies for framework-agnostic experiment libraries
# N.B. The specified library type should be SHARED.
add_library(my_add SHARED my_add.cpp)
add_library(my_geometry SHARED my_geometry.cpp)

add_library(print_mcparticles SHARED print_mcparticles.cpp)
target_link_libraries(print_mcparticles PRIVATE ${FORM_DATA_PROD_LIB_NAME} ROOT::Core ROOT::Physics ROOT::EG ROOT::RIO)

add_library(track_cheater SHARED track_cheater.cpp)
target_link_options(track_cheater PRIVATE "LINKER:--no-as-needed")
target_link_libraries(track_cheater PRIVATE ${FORM_DATA_PROD_LIB_NAME} ROOT::Core ROOT::Physics ROOT::EG ROOT::RIO)

add_library(track_cheater_per_tpc SHARED track_cheater_per_tpc.cpp)
target_link_options(track_cheater_per_tpc PRIVATE "LINKER:--no-as-needed")
target_link_libraries(track_cheater_per_tpc PRIVATE ${FORM_DATA_PROD_LIB_NAME} ROOT::Core ROOT::Physics ROOT::EG ROOT::RIO)

# Register providers for data products
add_library(numbers_source MODULE numbers_source.cpp)
target_link_libraries(numbers_source PRIVATE phlex::module)

add_library(geometry_source MODULE geometry_source.cpp)
target_link_libraries(geometry_source PRIVATE phlex::module my_geometry)

add_library(mcparticle_source MODULE mcparticle_source.cpp)
target_link_libraries(mcparticle_source PRIVATE phlex::module ROOT::Core ROOT::Tree ROOT::TreePlayer ROOT::Physics ROOT::EG ROOT::RIO)

add_library(wire_source MODULE wire_source.cpp)
target_link_libraries(wire_source PRIVATE phlex::module ROOT::Core ROOT::Tree ROOT::TreePlayer ROOT::Physics ROOT::EG ROOT::RIO ${FORM_DATA_PROD_LIB_NAME})

# Register experiment libraries with Phlex
#add_library(module MODULE module.cpp)
#target_link_libraries(module PRIVATE phlex::module my_add)

add_library(mcparticles_module MODULE mcparticles_module.cpp)
target_link_libraries(mcparticles_module PRIVATE phlex::module print_mcparticles)

add_library(track_cheater_module MODULE track_cheater_module.cpp)
target_link_libraries(track_cheater_module PRIVATE phlex::module track_cheater ${FORM_DATA_PROD_LIB_NAME})

#TODO: unfold registration seems to be broken because of a missing argument when it delegates to glue<>.
#add_library(track_cheater_per_tpc_module MODULE track_cheater_per_tpc_module.cpp)
#target_link_libraries(track_cheater_per_tpc_module PRIVATE phlex::module track_cheater_per_tpc ${FORM_DATA_PROD_LIB_NAME})

add_library(add_and_verify MODULE add_and_verify.cpp)
target_link_libraries(add_and_verify PRIVATE phlex::module my_add my_geometry)

# Enable asserts for add_and_verify
# N.B. This should not be done for production code, but it is useful for testing and development.
target_compile_options(add_and_verify PRIVATE -UNDEBUG)
