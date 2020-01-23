# - Top level CMakeLists.txt for BxDecay0 C++ library
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

cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(BxDecay0 VERSION 1.0.0)
# - Version of the original fortran Decay0
set(BxDecay0_DECAY0_VERSION "2018-12-05")
set(BxDecay0_TAG "BxDecay0-${BxDecay0_VERSION}")

# - Standard Modules
# For "BUILD_TESTING" option
include(CTest)

# Install directories
include(GNUInstallDirs)

# Require relative paths to support relocation
foreach(_dir BINDIR LIBDIR INCLUDEDIR DATAROOTDIR)
  if(IS_ABSOLUTE "${CMAKE_INSTALL_${_dir}}")
    message(FATAL_ERROR "Absolute path for CMAKE_INSTALL_${_dir} not allowed")
  endif()
endforeach()

# Add a path for CMake config files
set(CMAKE_INSTALL_CMAKEDIR      ${CMAKE_INSTALL_LIBDIR}/cmake)
set(CMAKE_INSTALL_FULL_CMAKEDIR ${CMAKE_INSTALL_FULL_LIBDIR}/cmake)

# - Dependencies
find_package(GSL 2.4 REQUIRED)

# - Publish headers
configure_file(source/bxdecay0/version.h.in
  ${PROJECT_BINARY_DIR}/source/bxdecay0/version.h @ONLY)
configure_file(source/bxdecay0/config.h.in
  ${PROJECT_BINARY_DIR}/source/bxdecay0/config.h  @ONLY)

set(BxDecay0_HEADERS
  ${PROJECT_BINARY_DIR}/source/bxdecay0/version.h
  ${PROJECT_BINARY_DIR}/source/bxdecay0/config.h
  source/bxdecay0/resource.h #
  source/bxdecay0/common.h #
  source/bxdecay0/divdif.h #
  source/bxdecay0/dgmlt1.h #
  source/bxdecay0/dgmlt2.h #
  source/bxdecay0/dshelp1.h #
  source/bxdecay0/dshelp2.h #
  source/bxdecay0/gauss.h #
  source/bxdecay0/tsimpr.h #
  source/bxdecay0/particle_utils.h #
  source/bxdecay0/particle.h #
  source/bxdecay0/i_random.h #
  source/bxdecay0/i_decay_generator.h #
  source/bxdecay0/std_random.h #
  source/bxdecay0/event.h #
  source/bxdecay0/positron.h #
  source/bxdecay0/electron.h #
  source/bxdecay0/gamma.h #
  source/bxdecay0/alpha.h #
  source/bxdecay0/gfang.h #
  source/bxdecay0/gdrot.h #
  source/bxdecay0/tgold.h #
  source/bxdecay0/plog69.h #
  source/bxdecay0/compton1.h #
  source/bxdecay0/compton.h #
  source/bxdecay0/moller1.h #
  source/bxdecay0/moller.h #
  source/bxdecay0/pair.h #
  source/bxdecay0/pairext1.h #
  source/bxdecay0/pairext.h #
  source/bxdecay0/beta2.h #
  source/bxdecay0/beta1.h #
  source/bxdecay0/beta.h #
  source/bxdecay0/beta_1fu.h #
  source/bxdecay0/fermi.h #
  source/bxdecay0/funbeta.h #
  source/bxdecay0/funbeta_1fu.h #
  source/bxdecay0/funbeta1.h #
  source/bxdecay0/funbeta2.h #
  source/bxdecay0/fe1_mods.h  #
  source/bxdecay0/fe2_mods.h #
  source/bxdecay0/fe12_mods.h #
  source/bxdecay0/nucltransK.h #
  source/bxdecay0/nucltransKL.h #
  source/bxdecay0/nucltransKLM.h #
  source/bxdecay0/nucltransKLM_Pb.h #
  source/bxdecay0/bb.h
  source/bxdecay0/bb_utils.h
  source/bxdecay0/decay0_generator.h
  source/bxdecay0/utils.h
  source/bxdecay0/genbbsub.h
  # Isotopes:
  source/bxdecay0/PbAtShell.h
  source/bxdecay0/Ac228.h
  source/bxdecay0/Am241.h
  source/bxdecay0/Ar39.h
  source/bxdecay0/Ar42.h
  source/bxdecay0/As79.h
  source/bxdecay0/At214.h
  source/bxdecay0/At214low.h
  source/bxdecay0/Ba136low.h
  source/bxdecay0/Ba138low.h
  source/bxdecay0/Bi207.h
  source/bxdecay0/Bi208.h
  source/bxdecay0/Bi210.h
  source/bxdecay0/Bi212.h
  source/bxdecay0/Bi214.h
  source/bxdecay0/C14.h
  source/bxdecay0/Ca48.h
  source/bxdecay0/Cd112low.h
  source/bxdecay0/Cd113.h
  source/bxdecay0/Co60.h
  source/bxdecay0/Cs136.h
  source/bxdecay0/Cs137.h
  source/bxdecay0/Eu147.h
  source/bxdecay0/Eu152.h
  source/bxdecay0/Eu154.h
  source/bxdecay0/Fe58low.h
  source/bxdecay0/Gd146.h
  source/bxdecay0/Gd156low.h
  source/bxdecay0/Gd158low.h
  source/bxdecay0/Ge70low.h
  source/bxdecay0/Ge74low.h
  source/bxdecay0/Hf180low.h
  source/bxdecay0/Hf182.h
  source/bxdecay0/Hg198low.h
  source/bxdecay0/I126.h
  source/bxdecay0/I133.h
  source/bxdecay0/I134.h
  source/bxdecay0/I135.h
  source/bxdecay0/K40.h
  source/bxdecay0/K42.h
  source/bxdecay0/Kr81.h
  source/bxdecay0/Kr82low.h
  source/bxdecay0/Kr84low.h
  source/bxdecay0/Kr85.h
  source/bxdecay0/Mn54.h
  source/bxdecay0/Mo94low.h
  source/bxdecay0/Mo96low.h
  source/bxdecay0/Na22.h
  source/bxdecay0/Nb96.h
  source/bxdecay0/Nd142low.h
  source/bxdecay0/Ni64low.h
  source/bxdecay0/Os186low.h
  source/bxdecay0/Os190low.h
  source/bxdecay0/P32.h
  source/bxdecay0/Pa231.h
  source/bxdecay0/Pa234m.h
  source/bxdecay0/Pb210.h
  source/bxdecay0/Pb211.h
  source/bxdecay0/Pb212.h
  source/bxdecay0/Pb214.h
  source/bxdecay0/Pd104low.h
  source/bxdecay0/Pd106low.h
  source/bxdecay0/Pd108low.h
  source/bxdecay0/Po212.h
  source/bxdecay0/Po214.h
  source/bxdecay0/Po214low.h
  source/bxdecay0/Ra222.h
  source/bxdecay0/Ra222low.h
  source/bxdecay0/Ra226.h
  source/bxdecay0/Ra228.h
  source/bxdecay0/Rb87.h
  source/bxdecay0/Rh106.h
  source/bxdecay0/Rn218.h
  source/bxdecay0/Rn218low.h
  source/bxdecay0/Ru100low.h
  source/bxdecay0/Sb125.h
  source/bxdecay0/Sb126.h
  source/bxdecay0/Sb133.h
  source/bxdecay0/Sc48.h
  source/bxdecay0/Se76low.h
  source/bxdecay0/Sm148low.h
  source/bxdecay0/Sm150low.h
  source/bxdecay0/Sn114low.h
  source/bxdecay0/Sn116low.h
  source/bxdecay0/Sn120low.h
  source/bxdecay0/Sr90.h
  source/bxdecay0/Ta182.h
  source/bxdecay0/Te122low.h
  source/bxdecay0/Te124low.h
  source/bxdecay0/Te133.h
  source/bxdecay0/Te133m.h
  source/bxdecay0/Te134.h
  source/bxdecay0/Th234.h
  source/bxdecay0/Ti48low.h
  source/bxdecay0/Tl207.h
  source/bxdecay0/Tl208.h
  source/bxdecay0/Xe128low.h
  source/bxdecay0/Xe129m.h
  source/bxdecay0/Xe130low.h
  source/bxdecay0/Xe131m.h
  source/bxdecay0/Xe133.h
  source/bxdecay0/Xe135.h
  source/bxdecay0/Y88.h
  source/bxdecay0/Y90.h
  source/bxdecay0/Zn65.h
  source/bxdecay0/Zr92low.h
  source/bxdecay0/Zr96.h
  source/bxdecay0/Dy162low.h # Added from 2018-12-05
  source/bxdecay0/Dy164low.h # Added from 2018-12-05
  source/bxdecay0/Er168low.h # Added from 2018-12-05
  source/bxdecay0/Gd154low.h # Added from 2018-12-05
  source/bxdecay0/Hf176low.h # Added from 2018-12-05
  source/bxdecay0/Nd144low.h # Added from 2018-12-05
  source/bxdecay0/Ta180mB.h  # Added from 2018-12-05
  source/bxdecay0/Ta180mEC.h # Added from 2018-12-05
  source/bxdecay0/Yb170low.h # Added from 2018-12-05
  source/bxdecay0/decay0_generator.h
  )

configure_file(source/bxdecay0/resource.cc.in
  ${PROJECT_BINARY_DIR}/source/bxdecay0/resource.cc  @ONLY)

set(BxDecay0_SOURCES
  ${PROJECT_BINARY_DIR}/source/bxdecay0/resource.cc
  source/bxdecay0/divdif.cc
  source/bxdecay0/dgmlt1.cc
  source/bxdecay0/dgmlt2.cc
  source/bxdecay0/dshelp1.cc
  source/bxdecay0/dshelp2.cc
  source/bxdecay0/gauss.cc
  source/bxdecay0/tsimpr.cc
  source/bxdecay0/particle_utils.cc
  source/bxdecay0/particle.cc
  source/bxdecay0/std_random.cc
  source/bxdecay0/event.cc
  source/bxdecay0/positron.cc
  source/bxdecay0/electron.cc
  source/bxdecay0/gamma.cc
  source/bxdecay0/alpha.cc
  source/bxdecay0/gfang.cc
  source/bxdecay0/gdrot.cc
  source/bxdecay0/tgold.cc
  source/bxdecay0/plog69.cc
  source/bxdecay0/compton1.cc
  source/bxdecay0/compton.cc
  source/bxdecay0/moller1.cc
  source/bxdecay0/moller.cc
  source/bxdecay0/pair.cc
  source/bxdecay0/pairext.cc
  source/bxdecay0/pairext1.cc
  source/bxdecay0/fermi.cc
  source/bxdecay0/funbeta.cc
  source/bxdecay0/funbeta_1fu.cc
  source/bxdecay0/funbeta1.cc
  source/bxdecay0/funbeta2.cc
  source/bxdecay0/beta2.cc
  source/bxdecay0/beta1.cc
  source/bxdecay0/beta.cc
  source/bxdecay0/beta_1fu.cc
  source/bxdecay0/fe1_mods.cc
  source/bxdecay0/fe2_mods.cc
  source/bxdecay0/fe12_mods.cc
  source/bxdecay0/nucltransK.cc
  source/bxdecay0/nucltransKL.cc
  source/bxdecay0/nucltransKLM.cc
  source/bxdecay0/nucltransKLM_Pb.cc
  source/bxdecay0/bb.cc
  source/bxdecay0/bb_utils.cc
  source/bxdecay0/utils.cc
  source/bxdecay0/genbbsub.cc
  # Isotopes:
  source/bxdecay0/PbAtShell.cc
  source/bxdecay0/Ac228.cc
  source/bxdecay0/Am241.cc
  source/bxdecay0/Ar39.cc
  source/bxdecay0/Ar42.cc
  source/bxdecay0/As79.cc
  source/bxdecay0/At214.cc
  source/bxdecay0/At214low.cc
  source/bxdecay0/Ba136low.cc
  source/bxdecay0/Ba138low.cc
  source/bxdecay0/Bi207.cc
  source/bxdecay0/Bi208.cc
  source/bxdecay0/Bi210.cc
  source/bxdecay0/Bi212.cc
  source/bxdecay0/Bi214.cc
  source/bxdecay0/C14.cc
  source/bxdecay0/Ca48.cc
  source/bxdecay0/Cd112low.cc
  source/bxdecay0/Cd113.cc
  source/bxdecay0/Co60.cc
  source/bxdecay0/Cs136.cc
  source/bxdecay0/Cs137.cc
  source/bxdecay0/Eu147.cc
  source/bxdecay0/Eu152.cc
  source/bxdecay0/Eu154.cc
  source/bxdecay0/Fe58low.cc
  source/bxdecay0/Gd146.cc
  source/bxdecay0/Gd156low.cc
  source/bxdecay0/Gd158low.cc
  source/bxdecay0/Ge70low.cc
  source/bxdecay0/Ge74low.cc
  source/bxdecay0/Hf176low.cc
  source/bxdecay0/Hf180low.cc
  source/bxdecay0/Hf182.cc
  source/bxdecay0/Hg198low.cc
  source/bxdecay0/I126.cc
  source/bxdecay0/I133.cc
  source/bxdecay0/I134.cc
  source/bxdecay0/I135.cc
  source/bxdecay0/K40.cc
  source/bxdecay0/K42.cc
  source/bxdecay0/Kr81.cc
  source/bxdecay0/Kr82low.cc
  source/bxdecay0/Kr84low.cc
  source/bxdecay0/Kr85.cc
  source/bxdecay0/Mn54.cc
  source/bxdecay0/Mo94low.cc
  source/bxdecay0/Mo96low.cc
  source/bxdecay0/Na22.cc
  source/bxdecay0/Nb96.cc
  source/bxdecay0/Nd142low.cc
  source/bxdecay0/Ni64low.cc
  source/bxdecay0/Os186low.cc
  source/bxdecay0/Os190low.cc
  source/bxdecay0/P32.cc
  source/bxdecay0/Pa231.cc
  source/bxdecay0/Pa234m.cc
  source/bxdecay0/Pb210.cc
  source/bxdecay0/Pb211.cc
  source/bxdecay0/Pb212.cc
  source/bxdecay0/Pb214.cc
  source/bxdecay0/Pd104low.cc
  source/bxdecay0/Pd106low.cc
  source/bxdecay0/Pd108low.cc
  source/bxdecay0/Po212.cc
  source/bxdecay0/Po214.cc
  source/bxdecay0/Po214low.cc
  source/bxdecay0/Ra222.cc
  source/bxdecay0/Ra222low.cc
  source/bxdecay0/Ra226.cc
  source/bxdecay0/Ra228.cc
  source/bxdecay0/Rb87.cc
  source/bxdecay0/Rh106.cc
  source/bxdecay0/Rn218.cc
  source/bxdecay0/Rn218low.cc
  source/bxdecay0/Ru100low.cc
  source/bxdecay0/Sb125.cc
  source/bxdecay0/Sb126.cc
  source/bxdecay0/Sb133.cc
  source/bxdecay0/Sc48.cc
  source/bxdecay0/Se76low.cc
  source/bxdecay0/Sm148low.cc
  source/bxdecay0/Sm150low.cc
  source/bxdecay0/Sn114low.cc
  source/bxdecay0/Sn116low.cc
  source/bxdecay0/Sn120low.cc
  source/bxdecay0/Sr90.cc
  source/bxdecay0/Ta182.cc
  source/bxdecay0/Te122low.cc
  source/bxdecay0/Te124low.cc
  source/bxdecay0/Te133.cc
  source/bxdecay0/Te133m.cc
  source/bxdecay0/Te134.cc
  source/bxdecay0/Th234.cc
  source/bxdecay0/Ti48low.cc
  source/bxdecay0/Tl207.cc
  source/bxdecay0/Tl208.cc
  source/bxdecay0/Xe128low.cc
  source/bxdecay0/Xe129m.cc
  source/bxdecay0/Xe130low.cc
  source/bxdecay0/Xe131m.cc
  source/bxdecay0/Xe133.cc
  source/bxdecay0/Xe135.cc
  source/bxdecay0/Y88.cc
  source/bxdecay0/Y90.cc
  source/bxdecay0/Zn65.cc
  source/bxdecay0/Zr92low.cc
  source/bxdecay0/Zr96.cc
  source/bxdecay0/Dy162low.cc # Added from 2018-12-05
  source/bxdecay0/Dy164low.cc # Added from 2018-12-05
  source/bxdecay0/Er168low.cc # Added from 2018-12-05
  source/bxdecay0/Gd154low.cc # Added from 2018-12-05
  source/bxdecay0/Hf176low.cc # Added from 2018-12-05
  source/bxdecay0/Nd144low.cc # Added from 2018-12-05
  source/bxdecay0/Ta180mB.cc  # Added from 2018-12-05
  source/bxdecay0/Ta180mEC.cc # Added from 2018-12-05
  source/bxdecay0/Yb170low.cc # Added from 2018-12-05
  source/bxdecay0/decay0_generator.cc
 )



# For now, use CMAKE_CXX_STANDARD to apply flag.
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 11)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(BxDecay0 SHARED ${BxDecay0_HEADERS} ${BxDecay0_SOURCES})
target_compile_definitions(BxDecay0 PRIVATE ENABLE_BINRELOC)
target_include_directories(BxDecay0 PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/source>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
# GSL may be a private dep, only seems to appear in .cc files
target_link_libraries(BxDecay0 PUBLIC GSL::gsl)
set_target_properties(BxDecay0 PROPERTIES INSTALL_RPATH_USE_LINK_PATH 1)

install(FILES ${BxDecay0_HEADERS}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/bxdecay0
  )

install(TARGETS BxDecay0
  EXPORT BxDecay0Targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )


install(DIRECTORY ${PROJECT_SOURCE_DIR}/examples
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${BxDecay0_TAG}
  )

install(DIRECTORY ${PROJECT_SOURCE_DIR}/resources/data
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${BxDecay0_TAG}/resources/
  )

install(FILES ${PROJECT_SOURCE_DIR}/LICENSE.txt
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${BxDecay0_TAG}
  )

if(BUILD_TESTING)
  set(BxDecay0_TESTS
    source/bxdecay0/testing/test_resource.cxx
    source/bxdecay0/testing/test_decay0.cxx
    source/bxdecay0/testing/test_tsimpr.cxx
    source/bxdecay0/testing/test_particle.cxx
    source/bxdecay0/testing/test_std_random.cxx
    source/bxdecay0/testing/test_event.cxx
    source/bxdecay0/testing/test_positron.cxx
    source/bxdecay0/testing/test_electron.cxx
    source/bxdecay0/testing/test_gamma.cxx
    source/bxdecay0/testing/test_alpha.cxx
    source/bxdecay0/testing/test_pair.cxx
    source/bxdecay0/testing/test_fermi.cxx
    source/bxdecay0/testing/test_bb_utils.cxx
    source/bxdecay0/testing/test_bb.cxx
    source/bxdecay0/testing/test_genbbsub.cxx
    source/bxdecay0/testing/test_decay0_generator.cxx
    )

  set(_bxdecay0_TEST_ENVIRONMENT "BXDECAY0_RESOURCE_DIR=${PROJECT_SOURCE_DIR}/resources")
  
  foreach(_testsource ${BxDecay0_TESTS})
   get_filename_component(_testname "${_testsource}" NAME_WE)
    set(_testname "bxdecay0-${_testname}")
    add_executable(${_testname} ${_testsource})
    target_link_libraries(${_testname} BxDecay0)
    add_test(NAME ${_testname} COMMAND ${_testname})
    set_property(TEST ${_testname}
      APPEND PROPERTY ENVIRONMENT ${_bxdecay0_TEST_ENVIRONMENT}
      )
  endforeach()
endif()

#-----------------------------------------------------------------------
# Configure/Install support files
# bxdecay0-config program
configure_file(source/utilities/bxdecay0-query.in
  ${PROJECT_BINARY_DIR}/bxdecay0-query
  @ONLY)

install(FILES
  ${PROJECT_BINARY_DIR}/bxdecay0-query
  DESTINATION ${CMAKE_INSTALL_BINDIR}
  )

# - PkgConfig
configure_file(cmake/bxdecay0.pc.in
  "${PROJECT_BINARY_DIR}/cmake/bxdecay0.pc"
  @ONLY)

install(FILES "${PROJECT_BINARY_DIR}/cmake/bxdecay0.pc"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig/
  )

# - CMake
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
   "${PROJECT_BINARY_DIR}/BxDecay0ConfigVersion.cmake"
   VERSION ${BxDecay0_VERSION}
   COMPATIBILITY SameMajorVersion
   )

# Build tree
# targets...
export(EXPORT BxDecay0Targets
  NAMESPACE BxDecay0
  FILE "${PROJECT_BINARY_DIR}/BxDecay0Targets.cmake"
  )
# config file...
set(BxDecay0_CONFIG_INCLUDEDIR "${PROJECT_SOURCE_DIR}/source")
configure_package_config_file(cmake/BxDecay0Config.cmake.in
  "${PROJECT_BINARY_DIR}/BxDecay0Config.cmake"
  INSTALL_DESTINATION "."
  INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
  PATH_VARS BxDecay0_CONFIG_INCLUDEDIR
  NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

# Install Tree
# targets...
install(EXPORT BxDecay0Targets
  NAMESPACE 
  DESTINATION ${CMAKE_INSTALL_CMAKEDIR}/BxDecay0
  )
set(BxDecay0_CONFIG_INCLUDEDIR "${CMAKE_INSTALL_INCLUDEDIR}")
configure_package_config_file(cmake/BxDecay0Config.cmake.in
  "${PROJECT_BINARY_DIR}/cmake/BxDecay0Config.cmake"
  INSTALL_DESTINATION "${CMAKE_INSTALL_CMAKEDIR}/BxDecay0"
  PATH_VARS BxDecay0_CONFIG_INCLUDEDIR
  NO_CHECK_REQUIRED_COMPONENTS_MACRO
  )

install(FILES
  ${PROJECT_BINARY_DIR}/BxDecay0ConfigVersion.cmake
  ${PROJECT_BINARY_DIR}/cmake/BxDecay0Config.cmake
  DESTINATION ${CMAKE_INSTALL_CMAKEDIR}/BxDecay0
  )
