# - Top level CMakeLists.txt for bxdecay0_ex05 example program
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(bxdecay0_ex05)

find_package(BxDecay0 1.0 REQUIRED CONFIG)
add_executable (ex05 ex05.cxx)
target_link_libraries(ex05 BxDecay0)
