
# - List of extension

option(BXDECAY0_WITH_GEANT4_EXTENSION "Build the BxDecay0 Geant4.10 extension library" OFF)
message(STATUS "BXDECAY0_WITH_GEANT4_EXTENSION=${BXDECAY0_WITH_GEANT4_EXTENSION}")

set(BxDecay0_WITH_GEANT4_EXTENSION 0 PARENT_SCOPE)
if (BXDECAY0_WITH_GEANT4_EXTENSION)
  set(BxDecay0_WITH_GEANT4_EXTENSION 1 PARENT_SCOPE)
  message(STATUS "Build the BxDecay0 Geant4 extension library")
  add_subdirectory(bxdecay0_g4)
endif()
message(STATUS "BxDecay0_WITH_GEANT4_EXTENSION=${BxDecay0_WITH_GEANT4_EXTENSION}")
