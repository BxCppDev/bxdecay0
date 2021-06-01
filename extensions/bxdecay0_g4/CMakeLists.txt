# BxDecay0 Geant4 library

cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(BxDecay0_Geant4 VERSION 1.0.0)

# - Dependencies
set(Geant4_CONFIG_DEBUG 1)
find_package(Geant4 10.6.3 REQUIRED)
message(STATUS "Geant4_VERSION      = '${Geant4_VERSION}'")
message(STATUS "Geant4_INCLUDE_DIRS = '${Geant4_INCLUDE_DIRS}'")
message(STATUS "Geant4_DEFINITIONS  = '${Geant4_DEFINITIONS}'")
message(STATUS "Geant4_LIBRARIES    = '${Geant4_LIBRARIES}'")

add_definitions(${Geant4_DEFINITIONS})
include_directories(${Geant4_INCLUDE_DIRS})
include_directories("${CMAKE_CURRENT_BINARY_DIR}")
include_directories("${CMAKE_CURRENT_BINARY_DIR}/bxdecay0_g4")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/bxdecay0_g4")

# - Publish headers
configure_file(bxdecay0_g4/version.hh.in
  ${CMAKE_CURRENT_BINARY_DIR}/bxdecay0_g4/version.hh @ONLY)

set(BxDecay0_Geant4_HEADERS
  ${CMAKE_CURRENT_BINARY_DIR}/bxdecay0_g4/version.hh
  ${CMAKE_CURRENT_SOURCE_DIR}/bxdecay0_g4/vertex_generator_interface.hh
  ${CMAKE_CURRENT_SOURCE_DIR}/bxdecay0_g4/unique_point_vertex_generator.hh
  ${CMAKE_CURRENT_SOURCE_DIR}/bxdecay0_g4/unique_point_vertex_generator_messenger.hh
  ${CMAKE_CURRENT_SOURCE_DIR}/bxdecay0_g4/primary_generator_action.hh
  ${CMAKE_CURRENT_SOURCE_DIR}/bxdecay0_g4/primary_generator_action_messenger.hh
)

set(BxDecay0_Geant4_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/bxdecay0_g4/primary_generator_action.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/bxdecay0_g4/vertex_generator_interface.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/bxdecay0_g4/unique_point_vertex_generator.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/bxdecay0_g4/unique_point_vertex_generator_messenger.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/bxdecay0_g4/primary_generator_action_messenger.cc
)

add_library(BxDecay0_Geant4 SHARED
  ${BxDecay0_Geant4_HEADERS}
  ${BxDecay0_Geant4_SOURCES})
set_target_properties(BxDecay0_Geant4 PROPERTIES LINKER_LANGUAGE CXX) 
# Ensure clients are aware of the minimum C++ standard we were compiled with
target_compile_features(BxDecay0_Geant4 PUBLIC cxx_std_${CMAKE_CXX_STANDARD})
target_include_directories(BxDecay0_Geant4
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_link_libraries(BxDecay0_Geant4 PUBLIC ${Geant4_LIBRARIES})
# BxDecay0 may be a private dep, only seems to appear in .cc files
target_link_libraries(BxDecay0_Geant4 PRIVATE BxDecay0)
set_target_properties(BxDecay0_Geant4 PROPERTIES
  SKIP_BUILD_RPATH            FALSE
  BUILD_WITH_INSTALL_RPATH    FALSE
  INSTALL_RPATH_USE_LINK_PATH TRUE)
if(UNIX AND NOT APPLE)
  set_target_properties(BxDecay0_Geant4
    PROPERTIES INSTALL_RPATH "\$ORIGIN/../${CMAKE_INSTALL_LIBDIR}"
    )
endif()

if(APPLE)
  set_target_properties(BxDecay0_Geant4
    PROPERTIES
    LINK_FLAGS "-undefined dynamic_lookup"
    )
endif()

install(FILES ${BxDecay0_Geant4_HEADERS}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/bxdecay0_g4
  )

install(TARGETS BxDecay0_Geant4
  EXPORT BxDecay0Targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/examples
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${BxDecay0_TAG}
  )

# - end
