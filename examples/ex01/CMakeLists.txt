# - Top level CMakeLists.txt for bxdecay0_ex01 example program
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(bxdecay0_ex01)

find_package(BxDecay0 1.0 REQUIRED CONFIG)
add_executable (ex01 ex01.cxx)
target_link_libraries(ex01 BxDecay0)
