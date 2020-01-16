# - Top level CMakeLists.txt for bxdecay0 C++ library

cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

# - Versioning
set(BxDecay0_VERSION_MAJOR 1)
set(BxDecay0_VERSION_MINOR 0)
set(BxDecay0_VERSION_PATCH 0)
set(BxDecay0_VERSION "${BxDecay0_VERSION_MAJOR}.${BxDecay0_VERSION_MINOR}.${BxDecay0_VERSION_PATCH}")

message("[info] BxDecay0_VERSION_MAJOR = ${BxDecay0_VERSION_MAJOR}")
message("[info] BxDecay0_VERSION_MINOR = ${BxDecay0_VERSION_MINOR}")
message("[info] BxDecay0_VERSION_PATCH = ${BxDecay0_VERSION_PATCH}")
message("[info] BxDecay0_VERSION       = '${BxDecay0_VERSION}'")

project(bxdecay0 VERSION ${BxDecay0_VERSION} LANGUAGES CXX)
message("[info] Project name           = '${PROJECT_NAME}'")
message("[info] Project version        = '${PROJECT_VERSION}'")
message("[info] Source directory       = '${CMAKE_SOURCE_DIR}'")
message("[info] Build directory        = '${CMAKE_BINARY_DIR}'")
message("[info] Install directory      = '${CMAKE_INSTALL_PREFIX}'")

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

# - Load Custom Modules
#   a dedicated FindGSL.cmake (extracted from CMake 3.5) is provided
#   because CMake 3.0 has none.
list(INSERT CMAKE_MODULE_PATH 0 ${PROJECT_SOURCE_DIR}/cmake)

# - Version of the original fortran Decay0
set(BxDecay0_DECAY0_VERSION "2018-12-05")
message("[info] Original Decay0 version = '${BxDecay0_DECAY0_VERSION}'")

#-----------------------------------------------------------------------
# - Standard UNIX Tool install paths, including relative paths for use
# by applications requiring resources
include(GNUInstallDirs)

# - Validate that certain paths are relative, otherwise relocation may fail
foreach(_dir BINDIR LIBDIR INCLUDEDIR DATAROOTDIR)
  if(IS_ABSOLUTE "${CMAKE_INSTALL_${_dir}}")
    message(FATAL_ERROR "[fatal] Absolute path for CMAKE_INSTALL_${_dir} not allowed")
  endif()
endforeach()

# Add a path for CMake config files
set(CMAKE_INSTALL_CMAKEDIR      ${CMAKE_INSTALL_LIBDIR}/cmake)
set(CMAKE_INSTALL_FULL_CMAKEDIR ${CMAKE_INSTALL_FULL_LIBDIR}/cmake)

# Resources directories based on name-version subdirs
set(BxDecay0_TAG "BxDecay0-${BxDecay0_VERSION}")
message("[info] BxDecay0 tag = '${BxDecay0_TAG}'")

file(RELATIVE_PATH BXDECAY0_BINDIR_TO_RESOURCEDIR
  "${CMAKE_INSTALL_FULL_BINDIR}"
  "${CMAKE_INSTALL_FULL_DATAROOTDIR}/${BxDecay0_TAG}"
  )
file(RELATIVE_PATH BXDECAY0_CMAKEDIR_TO_INCLUDEDIR
  "${CMAKE_INSTALL_FULL_CMAKEDIR}/${BxDecay0_TAG}"
  "${CMAKE_INSTALL_FULL_INCLUDEDIR}"
  )
message(STATUS "[info] BXDECAY0_BINDIR_TO_RESOURCEDIR  = '${BXDECAY0_BINDIR_TO_RESOURCEDIR}'")
message(STATUS "[info] BXDECAY0_CMAKEDIR_TO_INCLUDEDIR = '${BXDECAY0_CMAKEDIR_TO_INCLUDEDIR}'")

# - Dependencies
find_package(GSL 1.15 REQUIRED)
message(STATUS "[info] GSL_VERSION      = '${GSL_VERSION}'")
message(STATUS "[info] GSL_INCLUDE_DIRS = '${GSL_INCLUDE_DIRS}'")
message(STATUS "[info] GSL_LIBRARIES    = '${GSL_LIBRARIES}'")

message(STATUS "[info] Project binary directory = '${PROJECT_BINARY_DIR}'")

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

message("[info] BxDecay0_HEADERS = '${BxDecay0_HEADERS}'")
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

message("[info] BxDecay0_SOURCES = '${BxDecay0_SOURCES}'")

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
  source/bxdecay0/testing/test_bb.cxx
  source/bxdecay0/testing/test_genbbsub.cxx
  source/bxdecay0/testing/test_decay0_generator.cxx
  )

message("[info] BxDecay0_TESTS = '${BxDecay0_TESTS}'")

set(BXDECAY0_DEFINITIONS
  -std=c++11
  )

if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS ${BXDECAY0_DEFINITIONS})
endif()

include_directories(${PROJECT_SOURCE_DIR}/source)
include_directories(${PROJECT_BINARY_DIR}/source)

add_library(Bayeux_decay0 SHARED
  ${BxDecay0_HEADERS}
  ${BxDecay0_SOURCES}
  )

set(BxDecay0_OTHER_LIBS
  GSL::gsl GSL::gslcblas
  )

target_link_libraries(Bayeux_decay0 ${BxDecay0_OTHER_LIBS})

# - Set RPATH as needed
set_target_properties(Bayeux_decay0 PROPERTIES INSTALL_RPATH_USE_LINK_PATH 1)

# - Use BinReloc
set_target_properties(Bayeux_decay0 PROPERTIES COMPILE_DEFINITIONS ENABLE_BINRELOC)

install( FILES
  ${BxDecay0_HEADERS}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}/bxdecay0
  PERMISSIONS OWNER_READ OWNER_WRITE
  GROUP_READ
  WORLD_READ
  )

install( FILES
  ${PROJECT_BINARY_DIR}/libBayeux_decay0${CMAKE_SHARED_LIBRARY_SUFFIX}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}
  PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
  GROUP_READ GROUP_EXECUTE
  WORLD_READ WORLD_EXECUTE
  )

configure_file(source/utilities/bxdecay0-query.in
  ${PROJECT_BINARY_DIR}/source/utilities/bxdecay0-query
  @ONLY)

install( FILES
  ${PROJECT_BINARY_DIR}/source/utilities/bxdecay0-query
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}
  PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
  GROUP_READ GROUP_EXECUTE
  WORLD_READ WORLD_EXECUTE
  )

# configure_file(cmake/bxdecay0.pc.in
#   ${PROJECT_BINARY_DIR}/cmake/bxdecay0.pc
#   @ONLY)

# install( FILES
#   ${PROJECT_BINARY_DIR}/cmake/bxdecay0.pc
#   DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/pkgconfig/
#   PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
#   GROUP_READ GROUP_EXECUTE
#   WORLD_READ WORLD_EXECUTE
#   )

install( DIRECTORY
  ${PROJECT_SOURCE_DIR}/examples
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}/${BxDecay0_TAG}
  FILE_PERMISSIONS OWNER_READ
  GROUP_READ
  WORLD_READ
  DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
  GROUP_READ GROUP_EXECUTE
  WORLD_READ WORLD_EXECUTE
  )

install( DIRECTORY
  ${PROJECT_SOURCE_DIR}/resources/data
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}/${BxDecay0_TAG}/resources/
  FILE_PERMISSIONS OWNER_READ
  GROUP_READ
  WORLD_READ
  DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
  GROUP_READ GROUP_EXECUTE
  WORLD_READ WORLD_EXECUTE
  )

install( FILES
  ${PROJECT_SOURCE_DIR}/LICENSE.txt
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}/${BxDecay0_TAG}
  PERMISSIONS OWNER_READ OWNER_WRITE
  GROUP_READ
  WORLD_READ
)

option(BXDECAY0_ENABLE_TESTING "Build unit testing system for BxDecay0" ON)
if(BXDECAY0_ENABLE_TESTING)
  enable_testing()
endif()

if(BXDECAY0_ENABLE_TESTING)
  foreach(_testsource ${BxDecay0_TESTS})
    set(_bxdecay0_TEST_ENVIRONMENT
      "BXDECAY0_RESOURCE_DIR=${PROJECT_SOURCE_DIR}/resources"
      )
    get_filename_component(_testname "${_testsource}" NAME_WE)
    set(_testname "bxdecay0-${_testname}")
    add_executable(${_testname} ${_testsource}
      # source/bxdecay0/testing/test.h
      # source/bxdecay0/testing/test.cc
      )
    target_link_libraries(${_testname} Bayeux_decay0 ${BxDecay0_OTHER_LIBS})
    # - On Apple, ensure dynamic_lookup of undefined symbols
    if(APPLE)
      set_target_properties(${_testname} PROPERTIES LINK_FLAGS "-undefined dynamic_lookup")
    endif()
    add_test(NAME ${_testname} COMMAND ${_testname})
    set_property(TEST ${_testname}
      APPEND PROPERTY ENVIRONMENT ${_bxdecay0_TEST_ENVIRONMENT}
      )
    # - For now, dump them into the testing output directory
    set_target_properties(${_testname}
      PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bxdecay0_tests
      ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bxdecay0_tests
      )
  endforeach()
endif()

#-----------------------------------------------------------------------
# Install targets and resources
#
install(TARGETS Bayeux_decay0
  EXPORT  BxDecay0Targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )

#-----------------------------------------------------------------------
# Configure/Install support files
# Done here so that external package variables are visible
#
# - Targets
export(TARGETS Bayeux_decay0
  FILE ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_CMAKEDIR}/${BxDecay0_TAG}/BxDecay0Targets.cmake
  )
install(EXPORT BxDecay0Targets
  DESTINATION ${CMAKE_INSTALL_CMAKEDIR}/${BxDecay0_TAG}
  )

# - Versioning (build and install trees)
configure_file(${PROJECT_SOURCE_DIR}/cmake/BxDecay0ConfigVersion.cmake.in
  ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_CMAKEDIR}/${BxDecay0_TAG}/BxDecay0ConfigVersion.cmake
  @ONLY
  )

# - Config (build and install trees *at present*)
configure_file(${PROJECT_SOURCE_DIR}/cmake/BxDecay0Config.cmake.in
  ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_CMAKEDIR}/${BxDecay0_TAG}/BxDecay0Config.cmake
  @ONLY
  )

install(FILES
  ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_CMAKEDIR}/${BxDecay0_TAG}/BxDecay0ConfigVersion.cmake
  ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_CMAKEDIR}/${BxDecay0_TAG}/BxDecay0Config.cmake
  DESTINATION ${CMAKE_INSTALL_CMAKEDIR}/${BxDecay0_TAG}
  )

# - end of CMakeLists.txt
