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
project(BxDecay0 VERSION 1.0.5)
# - Version of the original fortran Decay0
set(BxDecay0_DECAY0_VERSION "2020-04-20")
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
# message(STATUS "**** CMAKE_INSTALL_FULL_LIBDIR       = '${CMAKE_INSTALL_FULL_LIBDIR}'")
# message(STATUS "**** CMAKE_INSTALL_FULL_DATAROOTDIR  = '${CMAKE_INSTALL_FULL_DATAROOTDIR}'")

set(BxDecay0_RESOURCE_DIR "${BxDecay0_TAG}/resources")
# message(STATUS "**** BxDecay0_RESOURCE_DIR           = '${BxDecay0_RESOURCE_DIR}'")

file(RELATIVE_PATH BxDecay0_LIBDIR_TO_RESOURCEDIR
  "${CMAKE_INSTALL_FULL_LIBDIR}"
  "${CMAKE_INSTALL_FULL_DATAROOTDIR}/${BxDecay0_RESOURCE_DIR}")
file(RELATIVE_PATH BxDecay0_LIBDIR_TO_PREFIX
  "${CMAKE_INSTALL_FULL_LIBDIR}"
  "${CMAKE_INSTALL_PREFIX}")
# message(STATUS "**** BxDecay0_LIBDIR_TO_RESOURCEDIR = '${BxDecay0_LIBDIR_TO_RESOURCEDIR}'")
# message(STATUS "**** BxDecay0_LIBDIR_TO_PREFIX       = '${BxDecay0_LIBDIR_TO_PREFIX}'")

# Option:
option(BxDecay0_WITH_DBD_GA "Build BxDecay0 with DBD gA process support" OFF)
set(BXDECAY0_WITH_DBD_GA 0)
if (BxDecay0_WITH_DBD_GA)
  set(BXDECAY0_WITH_DBD_GA 1)
endif()

# - Dependencies
find_package(GSL 2.4 REQUIRED)

# - Publish headers
configure_file(bxdecay0/version.h.in
  ${PROJECT_BINARY_DIR}/bxdecay0/version.h @ONLY)
configure_file(bxdecay0/config.h.in
  ${PROJECT_BINARY_DIR}/bxdecay0/config.h  @ONLY)

string(RANDOM LENGTH 18 MANGLE_BINRELOC_MAIN)
set(MANGLE_BINRELOC "BXDECAY0MB${MANGLE_BINRELOC_MAIN}")
configure_file(bxdecay0/BinReloc.h.in ${PROJECT_BINARY_DIR}/bxdecay0/BinReloc.h @ONLY)
configure_file(bxdecay0/relocatable_lib.cc.in ${PROJECT_BINARY_DIR}/bxdecay0/relocatable_lib.cc @ONLY)

set(BxDecay0_HEADERS
  ${PROJECT_BINARY_DIR}/bxdecay0/version.h
  ${PROJECT_BINARY_DIR}/bxdecay0/config.h
  bxdecay0/resource.h
  bxdecay0/common.h
  bxdecay0/divdif.h
  bxdecay0/dgmlt1.h
  bxdecay0/dgmlt2.h
  bxdecay0/dshelp1.h
  bxdecay0/dshelp2.h
  bxdecay0/gauss.h
  bxdecay0/tsimpr.h
  bxdecay0/particle_utils.h
  bxdecay0/particle.h
  bxdecay0/i_random.h
  bxdecay0/i_decay_generator.h
  bxdecay0/std_random.h
  bxdecay0/event.h
  bxdecay0/positron.h
  bxdecay0/electron.h
  bxdecay0/gamma.h
  bxdecay0/alpha.h
  bxdecay0/gfang.h
  bxdecay0/gdrot.h
  bxdecay0/tgold.h
  bxdecay0/plog69.h
  bxdecay0/compton1.h
  bxdecay0/compton.h
  bxdecay0/moller1.h
  bxdecay0/moller.h
  bxdecay0/pair.h
  bxdecay0/pairext1.h
  bxdecay0/pairext.h
  bxdecay0/beta2.h
  bxdecay0/beta1.h
  bxdecay0/beta.h
  bxdecay0/beta_1fu.h
  bxdecay0/fermi.h
  bxdecay0/funbeta.h
  bxdecay0/funbeta_1fu.h
  bxdecay0/funbeta1.h
  bxdecay0/funbeta2.h
  bxdecay0/fe1_mods.h
  bxdecay0/fe2_mods.h
  bxdecay0/fe12_mods.h
  bxdecay0/nucltransK.h
  bxdecay0/nucltransKL.h
  bxdecay0/nucltransKLM.h
  bxdecay0/nucltransKLM_Pb.h
  bxdecay0/bb.h
  bxdecay0/bb_utils.h
  bxdecay0/decay0_generator.h
  bxdecay0/utils.h
  bxdecay0/genbbsub.h
  # Isotopes:
  bxdecay0/PbAtShell.h
  bxdecay0/Ac228.h
  bxdecay0/Am241.h
  bxdecay0/Ar39.h
  bxdecay0/Ar42.h
  bxdecay0/As79.h
  bxdecay0/At214.h
  bxdecay0/At214low.h
  bxdecay0/Ba136low.h
  bxdecay0/Ba138low.h
  bxdecay0/Bi207.h
  bxdecay0/Bi208.h
  bxdecay0/Bi210.h
  bxdecay0/Bi212.h
  bxdecay0/Bi214.h
  bxdecay0/C14.h
  bxdecay0/Ca48.h
  bxdecay0/Cd112low.h
  bxdecay0/Cd113.h
  bxdecay0/Co60.h
  bxdecay0/Cs136.h
  bxdecay0/Cs137.h
  bxdecay0/Eu147.h
  bxdecay0/Eu152.h
  bxdecay0/Eu154.h
  bxdecay0/Fe58low.h
  bxdecay0/Gd146.h
  bxdecay0/Gd156low.h
  bxdecay0/Gd158low.h
  bxdecay0/Ge70low.h
  bxdecay0/Ge74low.h
  bxdecay0/Hf180low.h
  bxdecay0/Hf182.h
  bxdecay0/Hg198low.h
  bxdecay0/I126.h
  bxdecay0/I133.h
  bxdecay0/I134.h
  bxdecay0/I135.h
  bxdecay0/K40.h
  bxdecay0/K42.h
  bxdecay0/Kr81.h
  bxdecay0/Kr82low.h
  bxdecay0/Kr84low.h
  bxdecay0/Kr85.h
  bxdecay0/Mn54.h
  bxdecay0/Mo94low.h
  bxdecay0/Mo96low.h
  bxdecay0/Na22.h
  bxdecay0/Nb96.h
  bxdecay0/Nd142low.h
  bxdecay0/Ni64low.h
  bxdecay0/Os186low.h
  bxdecay0/Os190low.h
  bxdecay0/P32.h
  bxdecay0/Pa231.h
  bxdecay0/Pa234m.h
  bxdecay0/Pb210.h
  bxdecay0/Pb211.h
  bxdecay0/Pb212.h
  bxdecay0/Pb214.h
  bxdecay0/Pd104low.h
  bxdecay0/Pd106low.h
  bxdecay0/Pd108low.h
  bxdecay0/Po212.h
  bxdecay0/Po214.h
  bxdecay0/Po214low.h
  bxdecay0/Ra222.h
  bxdecay0/Ra222low.h
  bxdecay0/Ra226.h
  bxdecay0/Ra228.h
  bxdecay0/Rb87.h
  bxdecay0/Rh106.h
  bxdecay0/Rn218.h
  bxdecay0/Rn218low.h
  bxdecay0/Rn222.h # Added from 2020-07-17
  bxdecay0/Ru100low.h
  bxdecay0/Sb125.h
  bxdecay0/Sb126.h
  bxdecay0/Sb133.h
  bxdecay0/Sc48.h
  bxdecay0/Se76low.h
  bxdecay0/Sm148low.h
  bxdecay0/Sm150low.h
  bxdecay0/Sn114low.h
  bxdecay0/Sn116low.h
  bxdecay0/Sn120low.h
  bxdecay0/Sr90.h
  bxdecay0/Ta182.h
  bxdecay0/Te122low.h
  bxdecay0/Te124low.h
  bxdecay0/Te133.h
  bxdecay0/Te133m.h
  bxdecay0/Te134.h
  bxdecay0/Th234.h
  bxdecay0/Ti48low.h
  bxdecay0/Tl207.h
  bxdecay0/Tl208.h
  bxdecay0/Xe128low.h
  bxdecay0/Xe129m.h
  bxdecay0/Xe130low.h
  bxdecay0/Xe131m.h
  bxdecay0/Xe133.h
  bxdecay0/Xe135.h
  bxdecay0/Y88.h
  bxdecay0/Y90.h
  bxdecay0/Zn65.h
  bxdecay0/Zr92low.h
  bxdecay0/Zr96.h
  bxdecay0/Dy162low.h # Added from 2018-12-05
  bxdecay0/Dy164low.h # Added from 2018-12-05
  bxdecay0/Er168low.h # Added from 2018-12-05
  bxdecay0/Gd154low.h # Added from 2018-12-05
  bxdecay0/Hf176low.h # Added from 2018-12-05
  bxdecay0/Nd144low.h # Added from 2018-12-05
  bxdecay0/Ta180mB.h  # Added from 2018-12-05
  bxdecay0/Ta180mEC.h # Added from 2018-12-05
  bxdecay0/Yb170low.h # Added from 2018-12-05
  # Main wrapper class
  bxdecay0/decay0_generator.h
  )

configure_file(bxdecay0/resource.cc.in
  ${PROJECT_BINARY_DIR}/bxdecay0/resource.cc  @ONLY)

include_directories("${PROJECT_SOURCE_DIR}/bxdecay0")
include_directories("${PROJECT_BINARY_DIR}/bxdecay0")
set(BxDecay0_SOURCES
  bxdecay0/relocatable_lib.h
  ${PROJECT_BINARY_DIR}/bxdecay0/resource.cc
  ${PROJECT_BINARY_DIR}/bxdecay0/relocatable_lib.cc 
  ${PROJECT_BINARY_DIR}/bxdecay0/BinReloc.h
  bxdecay0/BinReloc.c
  bxdecay0/divdif.cc
  bxdecay0/dgmlt1.cc
  bxdecay0/dgmlt2.cc
  bxdecay0/dshelp1.cc
  bxdecay0/dshelp2.cc
  bxdecay0/gauss.cc
  bxdecay0/tsimpr.cc
  bxdecay0/particle_utils.cc
  bxdecay0/particle.cc
  bxdecay0/std_random.cc
  bxdecay0/event.cc
  bxdecay0/positron.cc
  bxdecay0/electron.cc
  bxdecay0/gamma.cc
  bxdecay0/alpha.cc
  bxdecay0/gfang.cc
  bxdecay0/gdrot.cc
  bxdecay0/tgold.cc
  bxdecay0/plog69.cc
  bxdecay0/compton1.cc
  bxdecay0/compton.cc
  bxdecay0/moller1.cc
  bxdecay0/moller.cc
  bxdecay0/pair.cc
  bxdecay0/pairext.cc
  bxdecay0/pairext1.cc
  bxdecay0/fermi.cc
  bxdecay0/funbeta.cc
  bxdecay0/funbeta_1fu.cc
  bxdecay0/funbeta1.cc
  bxdecay0/funbeta2.cc
  bxdecay0/beta2.cc
  bxdecay0/beta1.cc
  bxdecay0/beta.cc
  bxdecay0/beta_1fu.cc
  bxdecay0/fe1_mods.cc
  bxdecay0/fe2_mods.cc
  bxdecay0/fe12_mods.cc
  bxdecay0/nucltransK.cc
  bxdecay0/nucltransKL.cc
  bxdecay0/nucltransKLM.cc
  bxdecay0/nucltransKLM_Pb.cc
  bxdecay0/bb.cc
  bxdecay0/bb_utils.cc
  bxdecay0/utils.cc
  bxdecay0/genbbsub.cc
  # Isotopes:
  bxdecay0/PbAtShell.cc
  bxdecay0/Ac228.cc
  bxdecay0/Am241.cc
  bxdecay0/Ar39.cc
  bxdecay0/Ar42.cc
  bxdecay0/As79.cc
  bxdecay0/At214.cc
  bxdecay0/At214low.cc
  bxdecay0/Ba136low.cc
  bxdecay0/Ba138low.cc
  bxdecay0/Bi207.cc
  bxdecay0/Bi208.cc
  bxdecay0/Bi210.cc
  bxdecay0/Bi212.cc
  bxdecay0/Bi214.cc
  bxdecay0/C14.cc
  bxdecay0/Ca48.cc
  bxdecay0/Cd112low.cc
  bxdecay0/Cd113.cc
  bxdecay0/Co60.cc
  bxdecay0/Cs136.cc
  bxdecay0/Cs137.cc
  bxdecay0/Eu147.cc
  bxdecay0/Eu152.cc
  bxdecay0/Eu154.cc
  bxdecay0/Fe58low.cc
  bxdecay0/Gd146.cc
  bxdecay0/Gd156low.cc
  bxdecay0/Gd158low.cc
  bxdecay0/Ge70low.cc
  bxdecay0/Ge74low.cc
  bxdecay0/Hf176low.cc
  bxdecay0/Hf180low.cc
  bxdecay0/Hf182.cc
  bxdecay0/Hg198low.cc
  bxdecay0/I126.cc
  bxdecay0/I133.cc
  bxdecay0/I134.cc
  bxdecay0/I135.cc
  bxdecay0/K40.cc
  bxdecay0/K42.cc
  bxdecay0/Kr81.cc
  bxdecay0/Kr82low.cc
  bxdecay0/Kr84low.cc
  bxdecay0/Kr85.cc
  bxdecay0/Mn54.cc
  bxdecay0/Mo94low.cc
  bxdecay0/Mo96low.cc
  bxdecay0/Na22.cc
  bxdecay0/Nb96.cc
  bxdecay0/Nd142low.cc
  bxdecay0/Ni64low.cc
  bxdecay0/Os186low.cc
  bxdecay0/Os190low.cc
  bxdecay0/P32.cc
  bxdecay0/Pa231.cc
  bxdecay0/Pa234m.cc
  bxdecay0/Pb210.cc
  bxdecay0/Pb211.cc
  bxdecay0/Pb212.cc
  bxdecay0/Pb214.cc
  bxdecay0/Pd104low.cc
  bxdecay0/Pd106low.cc
  bxdecay0/Pd108low.cc
  bxdecay0/Po212.cc
  bxdecay0/Po214.cc
  bxdecay0/Po214low.cc
  bxdecay0/Ra222.cc
  bxdecay0/Ra222low.cc
  bxdecay0/Ra226.cc
  bxdecay0/Ra228.cc
  bxdecay0/Rb87.cc
  bxdecay0/Rh106.cc
  bxdecay0/Rn218.cc
  bxdecay0/Rn218low.cc
  bxdecay0/Rn222.cc # Added from 2020-07-17
  bxdecay0/Ru100low.cc
  bxdecay0/Sb125.cc
  bxdecay0/Sb126.cc
  bxdecay0/Sb133.cc
  bxdecay0/Sc48.cc
  bxdecay0/Se76low.cc
  bxdecay0/Sm148low.cc
  bxdecay0/Sm150low.cc
  bxdecay0/Sn114low.cc
  bxdecay0/Sn116low.cc
  bxdecay0/Sn120low.cc
  bxdecay0/Sr90.cc
  bxdecay0/Ta182.cc
  bxdecay0/Te122low.cc
  bxdecay0/Te124low.cc
  bxdecay0/Te133.cc
  bxdecay0/Te133m.cc
  bxdecay0/Te134.cc
  bxdecay0/Th234.cc
  bxdecay0/Ti48low.cc
  bxdecay0/Tl207.cc
  bxdecay0/Tl208.cc
  bxdecay0/Xe128low.cc
  bxdecay0/Xe129m.cc
  bxdecay0/Xe130low.cc
  bxdecay0/Xe131m.cc
  bxdecay0/Xe133.cc
  bxdecay0/Xe135.cc
  bxdecay0/Y88.cc
  bxdecay0/Y90.cc
  bxdecay0/Zn65.cc
  bxdecay0/Zr92low.cc
  bxdecay0/Zr96.cc
  bxdecay0/Dy162low.cc # Added from 2018-12-05
  bxdecay0/Dy164low.cc # Added from 2018-12-05
  bxdecay0/Er168low.cc # Added from 2018-12-05
  bxdecay0/Gd154low.cc # Added from 2018-12-05
  bxdecay0/Hf176low.cc # Added from 2018-12-05
  bxdecay0/Nd144low.cc # Added from 2018-12-05
  bxdecay0/Ta180mB.cc  # Added from 2018-12-05
  bxdecay0/Ta180mEC.cc # Added from 2018-12-05
  bxdecay0/Yb170low.cc # Added from 2018-12-05
  bxdecay0/decay0_generator.cc
 )

if (BXDECAY0_WITH_DBD_GA)
  message(STATUS "Appending DBD gA classes...")
  list(APPEND BxDecay0_HEADERS bxdecay0/dbd_gA.h)
  list(APPEND BxDecay0_SOURCES bxdecay0/dbd_gA.cc)
endif()

# For now, use CMAKE_CXX_STANDARD to apply flag.
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 11)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(BxDecay0 SHARED ${BxDecay0_HEADERS} ${BxDecay0_SOURCES})
target_compile_definitions(BxDecay0 PRIVATE ENABLE_BINRELOC)
# Ensure clients are aware of the minimum C++ standard we were compiled with
target_compile_features(BxDecay0 PUBLIC cxx_std_${CMAKE_CXX_STANDARD})
target_include_directories(BxDecay0 PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
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

if (BXDECAY0_WITH_DBD_GA)
  # Load datasets for dbd_gA process:
  include(ExternalProject)

  # Must have git-lfs to properly checkout
  find_program(GIT_LFS_EXECUTABLE git-lfs DOC "Path to git-lfs executable")
  if (NOT GIT_LFS_EXECUTABLE)
    message(FATAL_ERROR "git-lfs is required to build/install gA data for bxdecay0")
  endif()

  ExternalProject_Add(bxdecay0data_dbd_gA
    GIT_REPOSITORY "https://gitlab.in2p3.fr/francois.mauger/bxdecay0data"
    GIT_TAG        "1.0.1"
    PREFIX         "${CMAKE_BINARY_DIR}/bxdecay0data_dbd_gA"
    # Trick: installing datasets in the BxDecay0 source directory:
    INSTALL_DIR "${PROJECT_SOURCE_DIR}/resources/data"
    CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
    -DBXDECAY0DATA_WITH_DBD_GA=ON
    )
endif()

install(DIRECTORY ${PROJECT_SOURCE_DIR}/resources/data
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${BxDecay0_TAG}/resources
  )

install(FILES ${PROJECT_SOURCE_DIR}/LICENSE.txt
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${BxDecay0_TAG}
  )

if(BUILD_TESTING)
  set(BxDecay0_TESTS
    bxdecay0/testing/test_utils.cxx
    bxdecay0/testing/test_resource.cxx
    bxdecay0/testing/test_decay0.cxx
    bxdecay0/testing/test_tsimpr.cxx
    bxdecay0/testing/test_particle.cxx
    bxdecay0/testing/test_std_random.cxx
    bxdecay0/testing/test_event.cxx
    bxdecay0/testing/test_positron.cxx
    bxdecay0/testing/test_electron.cxx
    bxdecay0/testing/test_gamma.cxx
    bxdecay0/testing/test_alpha.cxx
    bxdecay0/testing/test_pair.cxx
    bxdecay0/testing/test_fermi.cxx
    bxdecay0/testing/test_bb_utils.cxx
    bxdecay0/testing/test_bb.cxx
    bxdecay0/testing/test_genbbsub.cxx
    bxdecay0/testing/test_decay0_generator.cxx
    )

  if (BXDECAY0_WITH_DBD_GA)
    message(STATUS "Appending DBD gA test...")
    list(APPEND BxDecay0_TESTS bxdecay0/testing/test_dbd_gA.cxx)
  endif()

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
file(RELATIVE_PATH BxDecay0_BINDIR_TO_PREFIX "${CMAKE_INSTALL_FULL_BINDIR}" "${CMAKE_INSTALL_PREFIX}")
# message(STATUS "**** BxDecay0_BINDIR_TO_PREFIX       = '${BxDecay0_BINDIR_TO_PREFIX}'")
configure_file(bxdecay0-config.in
  ${PROJECT_BINARY_DIR}/bxdecay0-config
  @ONLY)

install(FILES
  ${PROJECT_BINARY_DIR}/bxdecay0-config
  DESTINATION ${CMAKE_INSTALL_BINDIR}
  PERMISSIONS
  OWNER_READ OWNER_EXECUTE
  GROUP_READ GROUP_EXECUTE
  WORLD_READ WORLD_EXECUTE
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
  NAMESPACE BxDecay0::
  FILE "${PROJECT_BINARY_DIR}/BxDecay0Targets.cmake"
  )
# config file...
set(BxDecay0_CONFIG_INCLUDEDIR "${PROJECT_SOURCE_DIR}")
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
  NAMESPACE BxDecay0::
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
