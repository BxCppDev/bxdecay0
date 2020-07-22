# - Top level CMakeLists.txt for bxdecay0_ex02 example program
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(bxdecay0_ex02)

find_package(BxDecay0 1.0 REQUIRED CONFIG)
find_package(HepMC3 REQUIRED CONFIG)

add_executable(ex02 ex02.cxx)
# message(STATUS "HEPMC3_INCLUDE_DIR=${HEPMC3_INCLUDE_DIR}")
# message(STATUS "HEPMC3_LIBRARIES=${HEPMC3_LIBRARIES}")
target_include_directories(ex02 PUBLIC ${HEPMC3_INCLUDE_DIR})
target_link_libraries(ex02 BxDecay0::BxDecay0 ${HEPMC3_LIBRARIES})

