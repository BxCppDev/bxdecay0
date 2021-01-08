# - Top level CMakeLists.txt for bxdecay0_ex00 example program
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(bxdecay0_ex00)

find_package(BxDecay0 1.0 REQUIRED CONFIG)
add_executable(ex00 ex00.cxx)
target_link_libraries(ex00 BxDecay0::BxDecay0)
