# - Top level CMakeLists.txt for bxdecay0_ex04 example program
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(bxdecay0_ex04)

find_package(BxDecay0 1.0 REQUIRED CONFIG)

add_executable(ex04 ex04.cxx)
target_link_libraries(ex04 BxDecay0)
