#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(bxdecay0_g4_ex02)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 10.6.3 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 10.6.3 REQUIRED)
endif()

find_package(BxDecay0 1.0.7 REQUIRED COMPONENTS Geant4 CONFIG)
# message(STATUS "DEBUG *** BxDecay0_FOUND=${BxDecay0_FOUND}")
# message(STATUS "DEBUG *** BxDecay0_INCLUDE_DIRS=${BxDecay0_INCLUDE_DIRS}")
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
set(sources
  ${PROJECT_SOURCE_DIR}/src/ActionInitialization.cc
  ${PROJECT_SOURCE_DIR}/src/BoxBulkVertexGenerator.cc
  ${PROJECT_SOURCE_DIR}/src/DetectorConstruction.cc
  ${PROJECT_SOURCE_DIR}/src/EventAction.cc
  ${PROJECT_SOURCE_DIR}/src/HistoManager.cc
  ${PROJECT_SOURCE_DIR}/src/PhysicsList.cc
  ${PROJECT_SOURCE_DIR}/src/RunAction.cc
  ${PROJECT_SOURCE_DIR}/src/Run.cc
  ${PROJECT_SOURCE_DIR}/src/SteppingVerbose.cc
  ${PROJECT_SOURCE_DIR}/src/TrackingAction.cc
  ${PROJECT_SOURCE_DIR}/src/VertexGeneratorRecorder.cc
  ${PROJECT_SOURCE_DIR}/src/VertexPoolLoader.cc
  )
set(headers
  ${PROJECT_SOURCE_DIR}/include/ActionInitialization.hh
  ${PROJECT_SOURCE_DIR}/include/BoxBulkVertexGenerator.hh
  ${PROJECT_SOURCE_DIR}/include/DetectorConstruction.hh
  ${PROJECT_SOURCE_DIR}/include/EventAction.hh
  ${PROJECT_SOURCE_DIR}/include/HistoManager.hh
  ${PROJECT_SOURCE_DIR}/include/PhysicsList.hh
  ${PROJECT_SOURCE_DIR}/include/RunAction.hh
  ${PROJECT_SOURCE_DIR}/include/Run.hh
  ${PROJECT_SOURCE_DIR}/include/SteppingVerbose.hh
  ${PROJECT_SOURCE_DIR}/include/TrackingAction.hh
  ${PROJECT_SOURCE_DIR}/include/VertexGeneratorRecorder.hh
  ${PROJECT_SOURCE_DIR}/include/VertexPoolLoader.hh
  )


#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(bxdecay0_g4_ex02 bxdecay0_g4_ex02.cc ${sources} ${headers})
target_link_libraries(bxdecay0_g4_ex02 ${Geant4_LIBRARIES} BxDecay0::BxDecay0_Geant4)

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build bxdecay0_g4_ex02. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(bxdecay0_g4_ex02_SCRIPTS
    Co60.mac 
    vis.mac 
    view_vertexes.gp 
  )

foreach(_script ${bxdecay0_g4_ex02_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/macros/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS bxdecay0_g4_ex02 DESTINATION bin)

# - end