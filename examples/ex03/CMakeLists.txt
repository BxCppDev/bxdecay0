# - Top level CMakeLists.txt for bxdecay0_ex03 example program
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(bxdecay0_ex03)

find_package(BxDecay0 1.0 REQUIRED CONFIG)
add_executable(ex03 ex03.cxx)
target_link_libraries(ex03 BxDecay0::BxDecay0)
