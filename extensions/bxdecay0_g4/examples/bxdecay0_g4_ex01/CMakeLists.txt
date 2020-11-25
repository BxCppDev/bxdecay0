#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(bxdecay0_g4_ex01)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

find_package(BxDecay0 REQUIRED 1.0.7)
include_directories(${BxDecay0_INCLUDE_DIRS}) 

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
#
include(${Geant4_USE_FILE})

#----------------------------------------------------------------------------
# Locate sources and headers for this project
#
include_directories(${PROJECT_SOURCE_DIR}/include 
                    ${Geant4_INCLUDE_DIR} 
                    ${Geant4_INCLUDE_DIR})
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(bxdecay0_g4_ex01 bxdecay0_g4_ex01.cc ${sources} ${headers})
target_link_libraries(bxdecay0_g4_ex01 ${Geant4_LIBRARIES} BxDecay0::BxDecay0_Geant4)

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build bxdecay0_g4_ex01. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(bxdecay0_g4_ex01_SCRIPTS
    Co60.mac 
    Y90.mac 
    vis.mac 
    debug.mac 
    singleDecay.mac 
  )

foreach(_script ${bxdecay0_g4_ex01_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/macros/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS bxdecay0_g4_ex01 DESTINATION bin)

# - end