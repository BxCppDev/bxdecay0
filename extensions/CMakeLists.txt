
# - List of extension

option(BXDECAY0_WITH_GEANT4_EXTENSION "Build the BxDecay0 Geant4.10 extension library" OFF)

set(BxDecay0_WITH_GEANT4_EXTENSION 0)
if (BXDECAY0_WITH_GEANT4_EXTENSION)
  set(BxDecay0_WITH_GEANT4_EXTENSION 1)
  message(STATUS "Build the BxDecay0 geant4 extension library")
  add_subdirectory(bxdecay0_g4)
endif()