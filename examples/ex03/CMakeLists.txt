# - Top level CMakeLists.txt for bxdecay0_ex03 example program

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(bxdecay0_ex03)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(STATUS "${PROJECT_NAME} requires an out-of-source build.")
  message(STATUS "Please remove these files from ${CMAKE_BINARY_DIR} first:")
  message(STATUS "  CMakeCache.txt")
  message(STATUS "  CMakeFiles")
  message(STATUS "Once these files are removed, create a separate directory")
  message(STATUS "and run CMake from there, pointing it to:")
  message(STATUS "  ${CMAKE_SOURCE_DIR}")
  message(FATAL_ERROR "in-source build detected")
endif()

# -- RPATH settings --
# From: https://cmake.org/Wiki/CMake_RPATH_handling
# use, i.e. don't skip the full RPATH for the build tree
set(CMAKE_SKIP_BUILD_RPATH  FALSE)
# when building, don't use the install RPATH already
# (but later on when installing)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
# the RPATH to be used when installing, but only if it's not a system directory
list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_FULL_LIBDIR}" isSystemDir)
if("${isSystemDir}" STREQUAL "-1")
  set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_FULL_LIBDIR}")
endif()

# BxDecay0
message (STATUS "[info] Finding package BxRabbitMQ with 'manager' component...")
find_package(BxDecay0 1.0 REQUIRED CONFIG COMPONENTS manager)
message (STATUS "BxDecay0_VERSION       ='${BxDecay0_VERSION}'")
message (STATUS "BxDecay0_INCLUDE_DIRS  ='${BxDecay0_INCLUDE_DIRS}'")
message (STATUS "BxDecay0_LIBRARIES     ='${BxDecay0_LIBRARIES}'")

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

add_definitions     (${BxDecay0_DEFINITIONS})
include_directories (${PROJECT_SOURCE_DIR} ${BxDecay0_INCLUDE_DIRS})
link_libraries      (${BxDecay0_LIBRARIES})

add_executable (ex03 ex03.cxx)

install ( FILES
    ${PROJECT_BINARY_DIR}/ex03
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
    PERMISSIONS OWNER_READ OWNER_EXECUTE
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE
  )

# end of CMakeLists.txt
