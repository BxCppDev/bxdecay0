============================================================================
BxDecay0 - C++ port of the legacy Decay0 FORTRAN library
============================================================================

:authors: François Mauger, Volodymyr Tretyak
:date: 2023-08-29
:copyright: Copyright (C) 2017-2023 the BxCppDev group

.. image:: resources/images/logo/bxdecay0_logo_su.png
   :width: 20%

	       
The **BxDecay0** C++  library provides a set of  classes and functions
for the random generation of  simulated nuclear decays. It consists in
a C++ port of the original Decay0 Fortran program (also known as GENBB
in  some other  context) written  and maintained  by Volodymyr  Tretyak
(KINR_).  Decay0 was created to  address the Monte Carlo generation of
nuclear decays  in the context  of double  beta decay and  dark matter
experimental research.

BxDecay0 aims to  be used by any C++ simulation  program that needs to
generate  the kinematics  of primary  particles emitted  from specific
nuclear  decays  (example:  input  for a  Geant4_  based  Monte  Carlo
simulation  program).  It  can be  easily interfaced  with the  HepMC_
event/particle model or any other client application.

From version  1.0.7, BxDecay0  provides an optional  extension library
which    implements   an    interface    for    Geant4   (through    a
``PrimaryGeneratorAction`` class and  its associated *messenger*). See
the relevant section below.

.. contents::

.. raw:: pdf

   PageBreak


History
=======

The first version of the Decay0  program was written in the early 90's
by Volodymyr   Tretyak  and   collaborators,  using  the   Fortran  77
programming language and  the CERNLIB library. It  has been maintained
and improved up to now (2020).

From 1992  to 2010, the Decay0/GENBB  code was embedded in  the GEANT3
based  simulation software  of the  NEMO2 and  then NEMO3  double beta
decay experiments.

From 2005 to 2011, the NEMO3 collaboration has initiated a R&D program
to   design   a  new   generation   double   beta  decay   experiment:
SuperNEMO_. The  choice was made  to use  C++ as the  main programming
language.  In this context, François  Mauger has created a C++ version
of GENBB. The first version was  a C++ wrapper of the original Fortran
code, using binding mechanism based on plain static C structures.

Later,  a pure  C++ version  was  released without  any dependency  on
Fortran  and  CERNLIB.   This  code  was integrated  in  2011  as  the
``genbb_help`` module of the Bayeux_ C++ library (version < 4).

This release of the BxDecay0 C++  library is extracted from the Bayeux
``genbb_help`` module with some changes from the 2017-03-01 release of
the Decay0 program  by Volodymyr Tretyak.  It has then  been updated to
the 2018-12-05 and 2020-04-20 releases.

BxDecay0 is  a standalone library  with very few  dependencies (mostly
the  GSL_ library  for numerical  integration and  a few  special math
functions).   External random  engines can  be used  through a  simple
wrapping functor interface, particularly the  ones provided by the C++
standard ``random`` library can be  used by default.  However the user
is free to provide its own uniform deviates random generator (based on
GSL_, ROOT_ or whatever).

**Versions:**

- Prerelease 1.0.0  : mixed port  from Decay0 2017-03-01  and embedded
  decay0 C++ code in Bayeux 3 based on Decay0 2013.
- First release 1.0.0 : updated from Decay0 2018-12-05
- First production release 1.0.1 : updated build system
- Release 1.0.2 :

  - updated from Decay0 2020-04-20,
  - add optional support for 2nubb gA  processes for a few isotopes of
    interest  (as  a  pure  C++  implementation  with  required  large
    external               datasets             from               the
    https://gitlab.in2p3.fr/francois.mauger/bxdecay0data project which
    is automatically loaded).

- Release 1.0.3 :

  - fix kinematics issue in DBD gA process

- Release 1.0.4 :

  - fix  usage  of  the   optional  ``BXDECAY0_RESOURCE_DIR``  env  in
    ``bxdecay0-config`` script
  - support    the    optional    ``BXDECAY0_PREFIX_DIR``    env    in
    ``bxdecay0-config``  script  and  ``resource.cc.in``  (very  basic
    manual support for package relocation)

- Release 1.0.5 :

  - make BxDecay0 relocatable
  - fix missing/odd references for some *background* decays
  - add Rn222 decay generator

- Release 1.0.6:

  - add support for clang-format and clang-tidy
  - add a  few background isotopes,  namely Po210, Po218,  Th230, U234
    and U238, as simplified alpha emitters

- Release 1.0.7:

  - move some resource files
  - DBD gA  processes are  not optional  anymore but  associated phase
    space    data   files    are    only    installed   through    the
    BXDECAY0_INSTALL_DBD_GA_DATA option (default: OFF)
  - add support for  the BXDECAY0_DBD_GA_DATA_DIR environment variable
    to locate the DBD gA phase space data files
  - add the ``bxdecay0-run`` program to generate BxDecay0 decay events
    and store the output in some ASCII files
  - add  the  ``bxdecay0::event_reader``  class (compatible  with  the
    output files generated by the ``bxdecay0-run`` program)
  - add the BxDecay0 Geant4 extension library
 
- Release 1.0.8:

  - The Y90  decay generator  now reproduces as  well as  possible the
    positron energy  spectrum from the internal  pair production using
    an approximated shape  using a truncated polynomial  of degree two
    (see Dryák  P.  Jaroslav Š.,  *Measurement of the  branching ratio
    related  to  the  internal  pair  production  of  Y-90.*,  Applied
    Radiation  and Isotopes  156  (2020): 108942).   Thanks to  Daniel
    Bonifacio (IRD/CNEN, Rio de  Janeiro, Brazil) for stimulating this
    improvement.
 
- Release 1.0.9:

  - The BxDecay0 Geant4 extension library can be specified as
    a requested component from the find_package command. Example:

    .. code::
       
       find_package(BxDecay0 1.0.9 REQUIRED COMPONENTS Geant4 CONFIG)
    ..
  
- Release 1.0.10:

  - The ``bxdecay0::decay0_generator`` now  supports a mechanism which
    automates *post-generation event operations* (PGO).
  - Only  one  *post-generation  event  op* is  provided  for  now:  the
    *Momentum Direction  Lock* (MDL) algorithm  which allows to  apply a
    bias on the emission direction of some particle(s) in each generated
    event.       Specific     documentation      is     provided      in
    ``documentation/PostGenEventOps/MDL/``.
    The MDL PGO proposes also the possibility to use a simple rectangular
    cut on the emission cone aperture.
  - The    Geant4   extension
    (primary generation  action and messenger classes)  is also modified
    to enable the use of the MDL mechanism.
  - The    Geant4   extension provides an interface to use an arbitrary
    vertex generator engine to be coupled with the BxDecay0 primary generator
    action.
  - The generated companion file now uses extension ``.d0c`` to reflect the fact
    it contains informations about the configuration of the generator. It also
    lists the *post-generation event operations* used by the generator with their
    configuration parameters. This file must be considered as a helper *log file*,
    and not a *configuration file*.
    Users are responsible of the configuration of their usage of BxDecay0
    through their own simulation framework and associated configuration system.
  
- Release 1.0.11:

  - Fix missing CMake policy (issue #20)
  - Fix buggy support of the quadruple beta decay mode for Zr96, Xe136 and Nd150 (issue #21)
  - Fix buggy test in Geant4 extension (issue #22)
  
- Release 1.0.12:

  - Add an advanced example about vertex generation from the G4 extension (issue #24)
  - Fix spurious printouts in Geant4 extension (issue #25)
  
- Release 1.1.0:

  - Fix G4String issue in Geant4 extension (issue #26)
  - Fix bugs concerning the manipulation of particles' generation times
    in a generated event from examples (issue #27)
  
- Release 1.1.1:

  - Minor fix for GCC 13

    
.. _SuperNEMO: http://supernemo.org/

Design
======

Plumbing
--------

The core of the BxDecay0 code  does not follow a fully object-oriented
approach.   In order  to ensure  the easy  synchronization of  its low
level code with  the original Decay0 code, BxDecay0  mimics the layout
of the Fortran  code (including massive usage  of *GOTO* statements!).
BxDecay0 provides a large collection  of plain generator functions for
about 100  radioactive nuclei split  in two categories:  *double beta*
decay  and  *background/calibration*  decay.   When a  Decay0  fix  or
improvement is  published in the  original Fortran code by  its author
(V.Tretyak), it is thus rather easy to adequately change/adapt the C++
code in the relevant section of BxDecay0.

Porcelain
---------

Hopefully, BxDecay0 gets rid of the original *common block* based data
model in Decay0 which has  strong limitations (static data structures)
in  terms of  usability in  a modern  OOP and  possibly multi-threaded
context.  The BxDecay0  API introduces its own OOP  data model through
the  ``bxdecay0::event`` and  ``bxdecay0::particle`` classes  (see the
``ex01`` example).   It is thus easy  to use such classes  through any
C++  client program  and/or to  interface with  some high  level event
generator library (i.e.  HepMC3).  See the ``ex02`` example.

More, BxDecay0 provides the ``bxdecay0::decay0_generator`` class which
wraps low-level functions with a simple OOP interface.

Finally, it is also possible to use the low level C++ functions ported
from  the original  Fortran code.  However it  is not  recommended and
should be reserved to experts and developpers of the library.


Installing BxDecay0
===================

Preparation of your system
--------------------------

BxDecay0 is developped on a  Ubuntu Linux (18.04/20.04 LTS) and should
work on  any Unix/BSD  flavor with  a recent  C++ compiler  with c++11
support (i.e. GNU g++ >= 4.9 or clang) including macOS.

Requirements for Ubuntu 20.04 LTS
---------------------------------

The following lines give some hints  to prepare your system before the
installation  of BxDecay0.   Some instructions  may vary  depending on
your own system.

#. Install GNU C++ compiler:

   .. code:: sh

      $ sudo apt-get install g++
   ..

#. Install CMake:

   .. code:: sh

      $ sudo apt-get install cmake
   ..

#. Install the GNU scientific library (development package):

   .. code:: sh

      $ sudo apt-get install libgsl-dev
      $ gsl-config --version
      2.5
   ..

#. Install git-lfs (optional but required for supporting DBD gA data):

   .. code:: sh

      $ sudo apt-get install git-lfs
      $ git lfs install
   ..

#. Install clang-tidy, clang-format (optional, useful for development/contributors)

  .. code:: sh

     $ sudo apt-get install clang-format clang-tidy

Requirements for macOS (Catalina)
---------------------------------
If you use the Homebrew package manager, then all dependencies can be obtained through
that:

#. Install either Xcode from the App Store, or the command line tools from the Terminal:

  .. code:: sh

     $ xcode-select -install
  ..

#. Install Homebrew following the instructions here: https://brew.sh

#. Install the following required packages:

  .. code:: sh

     $ brew install cmake gsl
  ..
     
#. Install git-lfs (required for DBD gA data):

   .. code:: sh

      $ brew install git-lfs
      $ git lfs install
   ..

#. Install clang-tidy, clang-format (optional, useful for development/contributors)

  .. code:: sh

     $ brew install clang-format llvm
  ..

Download BxDecay0 source code from the GitHub repository
--------------------------------------------------------

Clone the Git development repository on your filesystem:

.. code:: sh

   $ cd /tmp
   $ git clone https://github.com/BxCppDev/bxdecay0.git bxdecay0.git
   $ ls -l bxdecay0.git/
..

Or download the archive associated to a released version :

.. code:: sh

   $ cd /tmp
   $ curl -L https://github.com/BxCppDev/bxdecay0/archive/1.1.1.tar.gz -o bxdecay0-1.1.1.tar.gz
   $ tar xvzf bxdecay0-1.1.1.tar.gz
   $ ls -l bxdecay0-1.1.1/
..


Configuration
-------------

Here we use a temporary build directory and choose to install BxDecay0
in our home directory:

.. code:: sh

   $ mkdir /tmp/_build.d
   $ cd /tmp/_build.d
   $ cmake -DCMAKE_INSTALL_PREFIX=${HOME}/sw/bxdecay0 /tmp/bxdecay0.git
..

or:

.. code:: sh

   $ cmake -DCMAKE_INSTALL_PREFIX=${HOME}/sw/bxdecay0 /tmp/bxdecay0-1.1.1
..


Configuration options:
~~~~~~~~~~~~~~~~~~~~~~

* ``BXDECAY0_INSTALL_DBD_GA_DATA`` :  Install phase-space  factor data
  files  for various  supported  BxDecay0 DBD  gA processes  (default:
  ``OFF``).  The DBD gA generator requires large datasets of tabulated
  phase-space factors so if you don't  need it in your client code, it
  is better to disable this features for it implies the downloading of
  huge external resource files (~1.7 GB).

  If set to ``ON``, the DBD gA processes' data files will be installed
  in  the   ``resources/data``  directory   and  handled   like  other
  BxDecay0's  resource files.   Alternatively, the  DBD gA  processes'
  data files  can be located through  the ``BXDECAY0_DBD_GA_DATA_DIR``
  environment variable which must point  to a directory which contains
  the  expected ``data/dbd_gA/vX.Y``  directory, following  the format
  conventionaly used by the DBD gA datasets.

  Example for auto-installing DBD gA generators data files:

  .. code:: bash

     $ cmake ... -DBXDECAY0_INSTALL_DBD_GA_DATA=ON ...
  ..


* ``BXDECAY0_WITH_GEANT4_EXTENSION`` : Build  and install the BxDecay0
  Geant4 extension library (needs Geant4 version >= 10.6).

  Example for building and installing the Geant4 extension:

  .. code:: bash

     $ cmake ... -DBXDECAY0_WITH_GEANT4_EXTENSION=ON -DGeant_DIR=/path/to/geant4/installation/dir ...
  ..

  The current release  has been tested on Ubuntu 20.04  LTS with a GSL
  2.5 system installation, Geant4 10.7  and a standalone CLHEP 2.4.4.0
  setup.
  

Build, test and install
-----------------------

From the build directory:

.. code:: sh

   $ make -j4
..

If you  are developing bxdecay0,  you can optionally use  the supplied
support files for ``clang-format``  and ``clang-tidy`` to apply format
and static an analysis checks.

Integration and use  of clang-format with a range of  text editors and
IDEs is documented here: https://clang.llvm.org/docs/ClangFormat.html

Use of clang-tidy may be enabled through CMake by configuring with the
``CMAKE_CXX_CLANG_TIDY`` option:

.. code:: sh

     $ cmake ... -DCMAKE_CXX_CLANG_TIDY=/path/to/clang-tidy ...
  ..

When  building ``bxdecay0``  with  this  setting, ``clang-tidy``  will
print warnings  when code  should be fixed  to conform  with security,
readability, performance, and modern C++ requirements. The suggestions
can be applied manually, or automatically by configuring as:

.. code:: sh

     $ cmake ... -DCMAKE_CXX_CLANG_TIDY="/path/to/clang-tidy;-fix" ...
  ..

If you are  submitting changes, it is recommended that  you split your
commits into  a sequence that  implement your change, followed  by one
that applies any  suggested fixes by `clang-tidy`.  This allows easier
review and testing.

Post-build test
-----------------------

Run the tests with:

.. code:: sh

   $ make test
..

To run a specific test:


.. code:: sh

   $ ctest -I 15,15
..

You can also run the ``bxdecay0-run`` program from the build directory
before     installation.     First     you     must    declare     the
``BXDECAY0_RESOURCE_DIR`` environment variable  to locate the resource
files which are not installed yet in the proper path. Here we generate
four Cs137 decay primary events using  the MDL bias mechanism to force
the beta ray to be emitted along the X-axis.

.. code:: sh

   $ export BXDECAY0_RESOURCE_DIR=$(pwd)/../resources
   $ ./bxdecay0-run --logging "debug" -s 314159 \
        -n 4 -c background -N "Cs137+Ba137m" \
	--pgop-mdl-particle "e-" \
	--pgop-mdl-rank 0  \
	--pgop-mdl-cone-phi 0.0 \
	--pgop-mdl-cone-theta 90.0 \
	--pgop-mdl-cone-aperture 0.0 \
	"/tmp/genCs137"
   $ cat /tmp/genCs137.d0c 
   $ cat /tmp/genCs137.d0t
..

The output  file ``/tmp/genCs137.d0c``  contains the summary  of event
generation  informations.    The  output   file  ``/tmp/genCs137.d0t``
contains the list of generated events in a very simple ASCII format.



Install
-----------------------

From the build directory:

.. code:: sh

   $ make install
..

Manual setup
------------

Add the following line in your shell startup script (i.e. ``~/.bashrc``):

.. code:: sh

   $ export PATH=${HOME}/sw/bxdecay0/bin:${PATH}
..


The ``bxdecay0-config`` script will be usable from your projects:

.. code:: sh

   $ which bxdecay0-config
..

One may want to use the ``pkg-config`` utility:

.. code:: sh

   $ export PKG_CONFIG_PATH=${HOME}/sw/bxdecay0/lib/pkgconfig:${PKG_CONFIG_PATH}
   $ pkg-config --exists bxdecay0 && echo ok
   ok
..


Utility
---------

* The   ``bxdecay0-config``  utility   script  allows   you  to   fetch
  informations about your installation of the BxDecay0 library.

  .. code:: sh

     $ bxdecay0-config --help
     $ bxdecay0-config --prefix
     $ bxdecay0-config --version
     $ bxdecay0-config --cmakedir
  ..

.. raw:: pdf

   PageBreak


Usage
======

Build support
-------------

BxDecay0  comes  with  CMake  and pkg-config  support.   The  BxDecay0
installation  directory contains  dedicated scripts  usable by  client
applications.

* CMake  configuration  scripts  are provided:

  * ``BxDecay0Config.cmake``,
  * ``BxDecay0ConfigVersion.cmake``.

  The ``find_package(BxDecay0  REQUIRED 1.1.1 CONFIG)``  CMake command
  can  be given  the following  variable  to locate  BxDecay0 on  your
  system from a client project which uses the CMake build system:

  .. code:: sh

     $ cmake -DBxDecay0_DIR="$(bxdecay0-config --cmakedir)" ...
  ..

* A ``pkg-config`` script is provided:

  * ``bxdecay0.pc``.

  Usage:

  .. code:: sh

     $ pkg-config --cflags bxdecay0 
     -I/path/to/bxdecay0/install/dir/lib/pkgconfig/../../include
     $ pkg-config --libs bxdecay0 
     -L/path/to/bxdecay0/install/dir/lib/pkgconfig/../../lib \
       -lBxDecay0 -lgsl -lgslcblas -lm
  ..


Basic program
-------------

The  following  program  is  extracted from  the  BxDecay0's  ``ex00``
example. It  randomly generates  10 simulated events  corresponding to
the neutrinoless double  beta decay (DBD) process of  :sup:`100` Mo to
the ground state  of :sup:`100` Ru.  The resulting  events are printed
in the terminal in a very simple  format.  It is of course possible to
adapt   this   program   and   use    the   OOP   interface   of   the
``bxdecay0::event`` class  in order to extract  physical quantities of
interest (particles' type and momentum...).

.. code:: c++

   #include <iostream>
   #include <bxdecay0/std_random.h>       // Wrapper for the standard random PRNG
   #include <bxdecay0/event.h>            // Decay event data model
   #include <bxdecay0/decay0_generator.h> // Decay0 generator with OOP interface

   int main()
   {
     // Declare a PRNG:
     unsigned int seed = 314159;                 // Random seed
     std::default_random_engine generator(seed); // Standard PRNG
     bxdecay0::std_random prng(generator);       // PRNG wrapper

     // Declare a Decay0 generator:
     bxdecay0::decay0_generator decay0;

     // Configure the Decay0 generator:
     decay0.set_decay_category(bxdecay0::decay0_generator::DECAY_CATEGORY_DBD);
                                                     // Double-beta decay process
     decay0.set_decay_isotope("Mo100");              // Emitter nucleus
     decay0.set_decay_dbd_level(0);                  // Ground state of the daughter
                                                     // nucleus
     decay0.set_decay_dbd_mode(bxdecay0::DBDMODE_1); // Neutrinoless DBD (mass mechanism)
     // or :
     // decay0.set_decay_dbd_mode_by_label("0nubb_mn");

     // Initialize the Decay0 generator.
     // We need to pass some PRNG to pre-compute some quantities
     // from energy distributions:
     decay0.initialize(prng);

     // Shoot some decay events:
     std::size_t nevents = 10;
     for (std::size_t ievent = 0; ievent < nevents; ievent++) {
       bxdecay0::event gendecay;     // Declare an empty decay event
       decay0.shoot(prng, gendecay); // Randomize the decay event
       gendecay.store(std::cout);    // Basic ASCII output
     }

     decay0.reset(); // Terminate the generator
     return 0;
   }
..

List of examples
----------------

* ``ex00`` : Minimal program for  the generation of Mo100 neutrinoless
  double beta decay events (mass mechanism) with plain ASCII output,
* ``ex01`` : Generation of Mo100 two neutrino double beta decay events
  with plain ASCII output,
* ``ex02`` : Generation of Mo100 two neutrino double beta decay events
  with HepMC3 formatted ASCII output (requires a proper installation of the HepMC3 library),
* ``ex03`` : Generation of Co60 decay events with plain ASCII output,
* ``ex04`` : Use of the *plumbing* ``bxdecay0::genbbsub`` function (expert/developper only),
* ``ex05`` : Use of the ``bxdecay0::dbd_gA`` class (optional).

.. raw:: pdf

   PageBreak

Units
=======

BxDecay0 uses the Decay0's legacy system for physical units.

Here the *c* quantity is the speed of light in vacuum
(with *c* ~ 300 000 km/s in S.I.).

- Let *m* be the rest mass of a particle, BxDecay0 expresses this mass
  as *M  = m c^2* where  *M* is the associated  rest mass-energy.  The
  implicit  unit   for  *M*  is  megaelectronvolts   (MeV).   This  is
  equivalent to say that *M=m* using *c=1*.
- let *p*  be some component of  the momentum of a  particle, BxDecay0
  expresses this quantity as  *P = p x c* where  *P* has the dimension
  of an energy explicitly  expressed in megaelectronvolts (MeV).  This
  is equivalent to say that *P=p* using *c=1*.
- Let  *t* be  the decay  time  of a  particle (with  respect to  some
  arbitrary  time reference),  then BxDecay0  expresses *t*  in second
  (s).

Given  these rules,  it is  up to  the client  application to  operate
physical quantities of interest using its own unit system.


**Example:**

Code  snippet  using the  CLHEP_  system  of  units, for  example  for
interfacing with Geant4_

.. code:: c++

   #include <CLHEP/Units/SystemOfUnits.h>
   #include <bxdecay0/event.h>
   #include <bxdecay0/particle.h>
    ...
   {
     bxdecay0::event gendecay;
     // Fill the event object with particles...
     ...
     
     // Extract informations from the BxDecay0 event model and define some physical quantities
     // for use within CLHEP or Geant4 with the proper explicit units:
     
     double g4_decay_time = gendecay.get_particles().front().get_time() * CLHEP::second;
     std::cout << "Decay time : " <<  g4_decay_time / CLHEP::nanosecond << " ns" << std::endl;
     
     double g4_momentum = gendecay.get_particles().front().get_momentum() * CLHEP::MeV;
     std::cout << "Momentum : " << g4_momentum / CLHEP::keV << " keV" << std::endl;
     ...
   }
..


.. raw:: pdf

   PageBreak

..


The Post-Generation Event Operation mechanism (PGOp)
======================================================

The ``bxdecay0::decay0_generator``  class accepts  an ordered  list of
*Post-Generation event  operations* (PGOp) to be  automatically applied
on each generated event.

Any  PGOp is  embodied by  an instance  of a  class inherited  from the
``bxdecay0::i_event_op`` abstract class.

Only  one type  of  PGOp algorithm  is provided  for  now, namely  the
*Momentum Direction Lock*  operation (MDL), which enables  to select a
*target particle*  in an event  and force its  momentum to point  in a
given emission  cone.  See  the ``documentation/PostGenEventOps/MDL/``
directory for  more informations.  The ``test_cs137_mdl``  function in
the ``bxdecay0/testing/test_decay0_generator.cxx`` program illustrates
the use of this feature. This mechanism also proposes a few more features
to bias a generated event with respect to the emission direction of the
primary particles.




   
The ``bxdecay0-run`` program
============================

``bxdecay0-run`` is a standalone  program which generates decay events
from a  BxDecay0 driver and  stores them in  ASCII files using  a very
simple format.  The files can be  thus easily parsed by  some external
program or read by the provided ``bxdecay0::event_reader`` class.

Usage:

.. code:: bash

   $ bxdecay0-run --help
..

Example:  Generation  of 1000  Co60  decay  events from  the  BxDecay0
driver.

.. code:: bash

   $ bxdecay0-run \
       --seed 314159 --nb-events 1000 \
       --decay-category "background" --nuclide "Co60" \
       "/tmp/genCo60"
       
..

The  program saves  the generated  events in  the ``/tmp/genCo60.d0t``
ASCII file.  The extension ``.d0t``  is automatically appended  to the
``/tmp/genCo60``   file   basename.    The  ASCII   format   of   the
``/tmp/genCo60.d0t``  output file  is  based on  a  sequence of  event
records using the following multiline structure:

.. code:: bash

   EventID EventTime NuclideName
   NumberOfParticles
   ParticleId0 ParticleDecayTime0 MomentumX0 MomentumY0 MomentumZ0
   ParticleId1 ParticleDecayTime1 MomentumX1 MomentumY1 MomentumZ1
   ...
   ParticleIdN ParticleDecayTimeN MomentumXN MomentumYN MomentumZN
   <blank line>
..
 

Times are expressed in seconds and momentum in MeV (see the *Units* section).


.. end  
   
Excerpt  of the  ``/tmp/genCo60.d0t``  decay events  output file.

::
   
   0 0 Co60
   3
   3  0 0.0890847724997921 0.107233155968529 0.210656674296868
   1  3.77695634726014e-13 0.0393104551877891 -0.0730829396361298 -1.1700609266389
   1  1.55399097807134e-12 -0.0847475363407502 -0.978273612294033 0.901491871606925

   1 0 Co60
   3
   3  0 0.0687351093356929 0.378071569687282 -0.0429368022433981
   1  4.74314079126286e-13 0.0742298643154087 -1.16402137524005 -0.124391178256253
   1  8.81837403089513e-13 -0.139316386007182 -0.515867914935887 -1.22121261004364

   ...


.. end

A  ``/tmp/genCo60.d0c``  companion file  is  also  created. It  stores
configuration  informations associated  to the  BxDecay0 run,  using a
very  simple  ASCII  format  with *key=value*  pairs.   The  extension
``.d0c`` is automatically appended to the ``/tmp/genCo60`` basename.
   
Typical   contents    of   the    ``/tmp/genCo60.d0c``   configuration
informations output file:

::
 
  library-name=BxDecay0
  library-version=1.1.1
  decay-category=background
  nuclide=Co60
  seed=314159
  time-from-epoch-s=1606423151
  nb-events=10
  @status=0
  
..

The  directory which  should contain  these  files must  exist and  be
writable before you run the program.


.. raw:: pdf

   PageBreak

..
   

The BxDecay0 Geant4 extension library
=====================================

The BxDecay0 library  can be built with an  optional companion library
named ``BxDecay0_Geant4``. Of course Geant4 (>=10.6) must be installed
and setup on your system to make  it work (former version may work but
have not been tested). This extension library proposes
a *primary generator action* which wraps the BxDecay0 event generator.

Some additional features  are proposed:

- a dedicated  messenger for the Geant4 interface,
- an  interface which allows  to install  your own algorithm for vertex generation,
- support for the MDL PGOp (with messenger),  allowing  to bias  the  emission  directions
  of  generated particles (within some arbitrary emission cone).


The      option      to      activate     this      extension      is:
``BXDECAY0_WITH_GEANT4_EXTENSION``.

Example:

.. code:: shell

   $ cmake ... -DBXDECAY0_WITH_GEANT4_EXTENSION=ON -DGeant4_DIR=/path/to/geant4/installation ...
..

Under  Linux,  this  generates  the  ``libBxDecay0_Geant4.so``  shared
library which is linked to the core ``libBxDecay0.so`` shared library.
This also  installs the  ``include/bxdecay0_g4/`` header  directory in
the BxDecay0 installation path.

A specific  example is also  available to  illustrate the use  of this
interface in a Geant4 based program (``bxdecay0_g4_ex01``).


License
=======

BxDecay0 is free  and open source software. Following  the GSL library
it depends  on, it is released  under the GNU GENERAL  PUBLIC LICENSE,
version 3.  See the ``LICENSE.txt`` file.

You  must take  care of  this licensing  terms. Distributing  your own
software  linked to  BxDecay0 implies  you  also use  the GNU  GENERAL
PUBLIC LICENSE.

If it  turns you cannot  link safely your distributable  software with
the BxDecay0  library because  of some licensing  incompatibility, you
may use the standalone ``bxdecay0-run`` program to generate standalone
datafiles  which contain  simulated events  and then  operate you  own
specific internal ASCII reader software  tool to benefit of BxDecay0's
functionalities.



Authors and contributors
========================

* Volodymyr  Tretyak  (KINR_,  Kiev  Institute  for  Nuclear  Research,
  Ukraine) is the original author  and maintener of the legacy Fortran
  Decay0 package.
* François Mauger (`LPC Caen`_,  Laboratoire de Physique Corpusculaire
  de  Caen, `Université  de  Caen Normandie`_,  Caen,  France) is  the
  author  and maintener  of the  original  C++ port  of Decay0  within
  Bayeux_ and the BxDecay0 library.
* Emma Mauger (formerly `Université de Caen Normandie`_, Caen, France)
  has done a  large part of the extraction of  the standalone BxDecay0
  from the original Bayeux_ *genbb* library module.
* Ben  Morgan (Warwick  University,  Warwick,  United Kingdom):  CMake
  build system  and package  reorganization, support  for clang-format
  and clang-tidy.
* Malak Hoballah  and Laurent Simard (IJCLab,  Orsay, France) (support
  for DBD generator with gA process).
* Rastislav Dvornicky (Comenius  University, Bratislava, Slovakia) has
  calculated specific phase space factors for some DBD gA process.
* Pierre Lasorak  (University of  Sussex, Oxford, United  Kingdom) has
  added  simplified versions  of Po210,  Po218, Th230,  U234 and  U238
  alpha emitters.
* Luigi Pertoldi (T. U. München) provides the `BxDecay0's Arch Linux packaging`_.

.. _`BxDecay0's Arch Linux packaging`: https://aur.archlinux.org/packages/?O=0&K=bxdecay0 

Who uses and supports BxDecay0...
===================================

* The SuperNEMO_  experiment through its Bayeux_  and Falaise_ software
  simulation stack (2017+).
* The LArSoft_ Collaboration, which  proposes, among others, tools for
  the simulation of Liquid Argon  Time Projection Chambers for several
  neutrino experiments, has incorporated the BxDecay0 library (2020+).
* The DUPhy_  research group (Deep Underground Physics).
* remage_ project  (2021+).
  
.. image:: resources/images/supporters/logo_panel.png
   :height: 120

The above logos and web sites  are referenced with the kind permission
of their respective authors and/or scientific communities.
	    
.. _LArSoft: https://larsoft.org/
.. _DUPhy: https://gdrduphy.in2p3.fr/
.. _remage: https://github.com/gipert/remage

References
===========

* Volodymyr Tretyak, *DECAY0 event  generator for initial kinematics of
  particles in  alpha, beta  and double beta  decays*, talk_  given at
  Laboratori Nazionali del Gran Sasso, 17 March 2015 :
* O.A.Ponkratenko, V.I.Tretyak, Yu.G.Zdesenko,  Event Generator DECAY4
  *for  Simulating Double-Beta  Processes  and  Decays of  Radioactive
  Nuclei*,  Phys.   At.  Nucl.   63  (2000)   1282
  (`nucl-ex/0104018 <https://arxiv.org/pdf/nucl-ex/0104018.pdf>`_)

.. _talk: https://agenda.infn.it/materialDisplay.py?materialId=slides&confId=9358

.. raw:: pdf

   PageBreak

Appendix 1: Supported radioactive isotopes and associated details
=================================================================

List of supported  double beta decay isotopes
---------------------------------------------

From the ``dbd_isotopes.lis`` resource file:

* ``Ca40``
* ``Ca46``
* ``Ca48``
* ``Ni58``
* ``Zn64``
* ``Zn70``
* ``Ge76``
* ``Se74``
* ``Se82``
* ``Sr84``
* ``Zr94``
* ``Zr96``
* ``Mo92``
* ``Mo100``
* ``Ru96``
* ``Ru104``
* ``Cd106``
* ``Cd108``
* ``Cd114``
* ``Cd116``
* ``Sn112``
* ``Sn122``
* ``Sn124``
* ``Te120``
* ``Te128``
* ``Te130``
* ``Xe136``
* ``Ce136``
* ``Ce138``
* ``Ce142``
* ``Nd148``
* ``Nd150``
* ``Dy156``
* ``Dy158``
* ``W180``
* ``W186``
* ``Os184``
* ``Os192``
* ``Pt190``
* ``Pt198``
* ``Bi214`` (for ``Bi214+At214``)
* ``Pb214`` (for ``Pb214+Po214``)
* ``Po218`` (for ``Po218+Rn218+Po214``)
* ``Rn222`` (for ``Rn222+Ra222+Rn218+Po214``)
* ``Sm144``
* ``Sm154``
* ``Er162``
* ``Er164``
* ``Er170``
* ``Yb168``
* ``Yb176``

.. raw:: pdf

   PageBreak

List of daughter nucleus excited states in double beta decay
----------------------------------------------------------------

* ``Ca40`` ->  ``Ar40`` :

  0. 0+ (gs) {0 MeV}

* ``Ca46`` ->  ``Ti46`` :

  0. 0+ (gs) {0 MeV}
  1. 2+ (1) {0.889 MeV}

* ``Ca48`` ->  ``Ti48`` :

  0. 0+ (gs) {0 MeV}
  1. 2+ (1) {0.984 MeV}
  2. 2+ (2) {2.421 MeV}

* ``Ni58`` ->  ``Fe58`` :

  0. 0+ (gs) {0 MeV}
  1. 2+ (1) {0.811 MeV}
  2. 2+ (2) {1.675 MeV}

* ``Zn64`` ->  ``Ni64`` :

  0. 0+ (gs) {0 MeV}

* ``Zn70`` ->  ``Ge70`` :

  0. 0+ (gs) {0 MeV}

* ``Ge76`` ->  ``Se76`` :

  0. 0+ (gs) {0 MeV}
  1. 2+ (1) {0.559 MeV}
  2. 0+ (1) {1.122 MeV}
  3. 2+ (2) {1.216 MeV}

* ``Se74`` ->  ``Ge74`` :

  0. 0+ (gs) {0 MeV}
  1. 2+ (1) {0.596 MeV}
  2. 2+ (2) {1.204 MeV}

* ``Se82`` ->  ``Kr82`` : (updated from Decay0 : 2020-04-20)

  0. 0+ (gs) {0 MeV}
  1. 2+ (1)  {0.777 MeV}
  2. 2+ (2)  {1.475 MeV}
  3. 0+ (1)  {1.488 MeV}
  4. 2+ (3)  {1.957 MeV}
  5. 0+ (2)  {2.172 MeV}
  6. 0+ (3)  {2.450 MeV}
  7. 2+ (4)  {2.480 MeV}
  8. 2+ (5)  {2.656 MeV}
  9. 2+ (6)  {2.945 MeV}

* ``Sr84`` ->  ``Kr84`` :

  0. 0+ (gs) {0 MeV}
  1. 2+ (1) {0.882 MeV}

* ``Zr94`` ->  ``Mo94`` :

  0. 0+ (gs) {0 MeV}
  1. 2+ (1) {0.871 MeV}

* ``Zr96`` ->  ``Mo96`` :

  0. 0+ (gs) {0 MeV}
  1. 2+ (1) {0.778 MeV}
  2. 0+ (1) {1.148 MeV}
  3. 2+ (2) {1.498 MeV}
  4. 2+ (3) {1.626 MeV}
  5. 2+ (4) {2.096 MeV}
  6. 2+ (5) {2.426 MeV}
  7. 0+ (2) {2.623 MeV}
  8. 2+ (6) {2.700 MeV}
  9. 2+?(7) {2.713 MeV}

* ``Mo92`` ->  ``Zr92`` :

  0. 0+ (gs) {0 MeV}
  1. 2+ (1) {0.934 MeV}
  2. 0+ (1) {1.383 MeV}

* ``Mo100`` ->  ``Ru100`` :

  0. 0+ (gs) {0 MeV}
  1. 2+ (1) {0.540 MeV}
  2. 0+ (1) {1.130 MeV}
  3. 2+ (2) {1.362 MeV}
  4. 0+ (2) {1.741 MeV}

* ``Ru96`` ->  ``Mo96`` :

  0. 0+ (gs) {0 MeV}
  1. 2+ (1) {0.778 MeV}
  2. 0+ (1) {1.148 MeV}
  3. 2+ (2) {1.498 MeV}
  4. 2+ (3) {1.626 MeV}
  5. 2+ (4) {2.096 MeV}
  6. 2+ (5) {2.426 MeV}
  7. 0+ (2) {2.623 MeV}
  8. 2+ (6) {2.700 MeV}
  9. 2+?(7) {2.713 MeV}

* ``Ru104`` ->  ``Pd104`` :

  0. 0+ (gs) {0 MeV}
  1. 2+ (1) {0.556 MeV}

* ``Cd106`` ->  ``Pd106`` :

  0. 0+ (gs) {0 MeV}
  1. 2+ (1) {0.512 MeV}
  2. 2+ (2) {1.128 MeV}
  3. 0+ (1) {1.134 MeV}
  4. 2+ (3) {1.562 MeV}
  5. 0+ (2) {1.706 MeV}

* ``Cd108`` ->  ``Pd108`` :

  0. 0+ (gs) {0 MeV}

* ``Cd114`` ->  ``Sn114`` :

  0. 0+ (gs) {0 MeV}

* ``Cd116`` ->  ``Sn116`` :

  0. 0+ (gs) {0 MeV}
  1. 2+ (1) {1.294 MeV}
  2. 0+ (1) {1.757 MeV}
  3. 0+ (2) {2.027 MeV}
  4. 2+ (2) {2.112 MeV}
  5. 2+ (3) {2.225 MeV}

* ``Sn112`` ->  ``Cd112`` :

  0. 0+ (gs) {0 MeV}
  1. 2+ (1) {0.618 MeV}
  2. 0+ (1) {1.224 MeV}
  3. 2+ (2) {1.312 MeV}
  4. 0+ (2) {1.433 MeV}
  5. 2+ (3) {1.469 MeV}
  6. 0+ (3) {1.871 MeV}

* ``Sn122`` ->  ``Te122`` :

  0. 0+ (gs) {0 MeV}

* ``Sn124`` ->  ``Te124`` :

  0. 0+ (gs) {0 MeV}
  1. 2+ (1) {0.603 MeV}
  2. 2+ (2) {1.326 MeV}
  3. 0+ (1) {1.657 MeV}
  4. 0+ (2) {1.883 MeV}
  5. 2+ (3) {2.039 MeV}
  6. 2+ (4) {2.092 MeV}
  7. 0+ (3) {2.153 MeV}
  8. 2+ (5) {2.182 MeV}

* ``Te120`` ->  ``Sn120`` :

  0. 0+ (gs) {0 MeV}
  1. 2+ (1) {1.171 MeV}

* ``Te128`` ->  ``Xe128`` :

  0. 0+ (gs) {0 MeV}
  1. 2+ (1) {0.443 MeV}

* ``Te130`` ->  ``Xe130`` :

  0. 0+ (gs) {0 MeV}
  1. 2+ (1) {0.536 MeV}
  2. 2+ (2) {1.122 MeV}
  3. 0+ (1) {1.794 MeV}

* ``Xe136`` ->  ``Ba136`` :

  0. 0+ (gs) {0 MeV}
  1. 2+ (1) {0.819 MeV}
  2. 2+ (2) {1.551 MeV}
  3. 0+ (1) {1.579 MeV}
  4. 2+ (3) (2.080 MeV}
  5. 2+ (4) {2.129 MeV}
  6. 0+ (2) {2.141 MeV}
  7. 2+ (5) {2.223 MeV}
  8. 0+ (3) {2.315 MeV}
  9. 2+ (6) {2.400 MeV}

* ``Ce136`` ->  ``Ba136`` :

  0. 0+ (gs) {0 MeV}
  1. 2+ (1) {0.819 MeV}
  2. 2+ (2) {1.551 MeV}
  3. 0+ (1) {1.579 MeV}
  4. 2+ (3) (2.080 MeV}
  5. 2+ (4) {2.129 MeV}
  6. 0+ (2) {2.141 MeV}
  7. 2+ (5) {2.223 MeV}
  8. 0+ (3) {2.315 MeV}
  9. 2+ (6) {2.400 MeV}

* ``Ce138`` ->  ``Ba138`` :

  0. 0+ (gs) {0 MeV}

* ``Ce142`` ->  ``Nd142`` :

  0. 0+ (gs) {0 MeV}

* ``Nd148`` ->  ``Sm148`` :

  0. 0+ (gs) {0 MeV}
  1. 2+ (1) {0.550 MeV}
  2. 0+ (1) {1.424 MeV}
  3. 2+ (2) {1.454 MeV}
  4. 2+ (3) {1.664 MeV}
  5. 0+ (2) {1.921 MeV}

* ``Nd150`` ->  ``Sm150`` :

  0. 0+ (gs) {0 MeV}
  1. 2+ (1) {0.334 MeV}
  2. 0+ (1) {0.740 MeV}
  3. 2+ (2) {1.046 MeV}
  4. 2+ (3) {1.194 MeV}
  5. 0+ (2) {1.256 MeV}

* ``Sm144`` ->  ``Nd144`` (new : Decay0 2018-12-05) :

  0. 0+ (gs)     {0 MeV}
  1. 2+ (1)  {0.697 MeV}
  2. 2+ (2)  {1.561 MeV}

* ``Sm154`` ->  ``Gd144`` (new : Decay0 2018-12-05) :

  0. 0+ (gs)     {0 MeV}
  1. 2+ (1)  {0.123 MeV}
  2. 0+ (1)  {0.681 MeV}
  3. 2+ (2)  {0.815 MeV}
  4. 2+ (3)  {0.996 MeV}
  5. 0+ (2)  {1.182 MeV}

* ``Dy156`` ->  ``Gd156`` :

  0. 0+ (gs) {0 MeV}
  1. 2+ (1) {0.089 MeV}
  2. 0+ (1) {1.050 MeV}
  3. 2+ (2) {1.129 MeV}
  4. 2+ (3) {1.154 MeV}
  5. 0+ (2) {1.168 MeV}
  6. 2+ (4) {1.258 MeV}
  7. 0+ (3) {1.715 MeV}
  8. 2+ (5) {1.771 MeV}
  9. 2+ (6) {1.828 MeV}
  10. 0+ (4) {1.851 MeV}
  11. 2+ (7) {1.915 MeV}
  12. 1- {1.946 MeV}
  13. 0- {1.952 MeV}
  14. 0+ (5) {1.989 MeV}
  15. 2+ (8) {2.004 MeV}

* ``Dy158`` ->  ``Gd158`` :

  0. 0+ (gs) {0 MeV}
  1. 2+ (1) {0.080 MeV}
  2. 4+ (1) {0.261 MeV}

* ``Er162`` ->  ``Dy162`` (new : Decay0 2018-12-05) :

  0. 0+ (gs)     {0 MeV}
  1. 2+ (1)  {0.081 MeV}
  2. 2+ (2)  {0.888 MeV}
  3. 0+ (1)  {1.400 MeV}
  4. 2+ (3)  {1.453 MeV}
  5. 0+ (2)  {1.666 MeV}
  6. 2+ (4)  {1.728 MeV}
  7. 2+ (5)  {1.783 MeV}

* ``Er164`` ->  ``Dy164`` (new : Decay0 2018-12-05) :

  0. 0+ (gs)     {0 MeV};

* ``Er170`` ->  ``Yb170`` (new : Decay0 2018-12-05) :

   0. 0+ (gs)     {0 MeV}
   1. 2+ (1)  {0.084 MeV}

* ``Yb168`` ->  ``Er168`` (new : Decay0 2018-12-05) :

  0. 0+ (gs)     {0 MeV}
  1. 2+ (1)  {0.080 MeV}
  2. 2+ (2)  {0.821 MeV}
  3. 0+ (1)  {1.217 MeV}
  4. 2+ (3)  {1.276 MeV}

* ``Yb176`` ->  ``Hf176`` (new : Decay0 2018-12-05) :

  0. 0+ (gs)     {0 MeV}
  1. 2+ (1)  {0.088 MeV}

* ``W180`` ->  ``Hf180`` :

  0. 0+ (gs) {0 MeV}

* ``W186`` ->  ``Os186`` :

  0. 0+ (gs) {0 MeV}
  1. 2+ (1) {0.137 MeV}

* ``Os184`` ->  ``W184`` :

  0. 0+ (gs)     {0 MeV}
  1. 2+ (1)  {0.111 MeV}
  2. 2+ (2)  {0.903 MeV}
  3. 0+ (1)  {1.002 MeV}
  4. 2+ (3)  {1.121 MeV}
  5. 0+ (2)  {1.322 MeV}
  6. 2+ (4)  {1.386 MeV}
  7. 2+ (5)  {1.431 MeV}

* ``Os192`` ->  ``Pt192`` :

  0. 0+ (gs)     {0 MeV}
  1. 2+ (1)  {0.317 MeV}

* ``Pt190`` ->  ``Os190`` :

  0. 0+ (gs) {0 MeV}
  1. 2+ (1) {0.187 MeV}
  2. 2+ (2) {0.558 MeV}
  3. 0+ (1) {0.912 MeV}
  4. 2+ (3) {1.115 MeV}
  5. 0+ (2) {1.382 MeV}

* ``Pt198`` ->  ``Hg198`` :

  0. 0+ (gs) {0 MeV}
  1. 2+ (1) {0.412 MeV}

* ``Bi214`` ->  ``At214`` :

  0. 1- (gs) {0 MeV}

* ``Pb214`` ->  ``Po214`` :

  0. 0+ (gs) {0 MeV}

* ``Po218`` ->  ``Rn218`` :

  0. 0+ (gs) {0 MeV}

* ``Rn222`` ->  ``Ra222`` :

  0. 0+ (gs) {0 MeV}


.. raw:: pdf

   PageBreak

List of supported double beta decay modes
-----------------------------------------

From the ``bxdecay0::bb_utils.h`` C++ header and the ``dbd_modes.lis`` resource file:

============== ========================= ============ ============================================================
BxDecay0 mode   Identification label      Decay0 mode  Description
============== ========================= ============ ============================================================
``DBDMODE_1``  ``0nubb_mn``              1            0nubb(mn)         0+ -> 0+     {2n} with neutrino mass
``DBDMODE_2``  ``0nubb_rhc_lambda_0``    2            0nubb(rhc-lambda) 0+ -> 0+     {2n} with RHC lambda
``DBDMODE_3``  ``0nubb_rhc_lambda_02``   3            0nubb(rhc-lambda) 0+ -> 0+, 2+ {N*} with RHC lambda
``DBDMODE_4``  ``2nubb``                 4            2nubb             0+ -> 0+     {2n}
``DBDMODE_5``  ``0nubbM1``               5            0nubbM1           0+ -> 0+     {2n} (Majoron, SI=1)
``DBDMODE_6``  ``0nubbM3``               7            0nubbM3           0+ -> 0+     {2n} (Majoron, SI=3)
``DBDMODE_7``  ``0nubb_rhc_lambda_2``    9            0nubb(rhc-lambda) 0+ -> 2+     {2n} with RHC lambda
``DBDMODE_8``  ``2nubb_2``               10           2nubb             0+ -> 2+     {2n}, {N*}
``DBDMODE_9``  ``0nuKb+``                11           0nuKb+            0+ -> 0+, 2+
``DBDMODE_10`` ``2nuKb+``                12           2nuKb+            0+ -> 0+, 2+
``DBDMODE_11`` ``0nu2K``                 13           0nu2K             0+ -> 0+, 2+
``DBDMODE_12`` ``2nu2K``                 14           2nu2K             0+ -> 0+, 2+
``DBDMODE_13`` ``0nubbM7``               8            0nubbM7           0+ -> 0+     {2n} (Majoron, SI=7)
``DBDMODE_14`` ``0nubbM2``               6            0nubbM2           0+ -> 0+     (2n} (Majoron, SI=2)
``DBDMODE_15`` ``2nubb_bosonic_0``       15           2nubb             0+ -> 0+ with bosonic neutrinos
``DBDMODE_16`` ``2nubb_bosonic_2``       16           2nubb             0+ -> 2+ with bosonic neutrinos
``DBDMODE_17`` ``0nubb_rhc_eta_s``       17           0nubb(rhc-eta)    0+ -> 0+ with RHC eta simplified expression
``DBDMODE_18`` ``0nubb_rhc_eta_nmes``    18           0nubb(rhc-eta)    0+ -> 0+ with RHC eta and specific NMEs
``DBDMODE_19`` ``2nub_lv``               19           2nubb(LV)         0+ -> 0+ with Lorentz violation
``DBDMODE_20`` ``0nu4b``                 20           0nu4b             0+ -> 0+ Quadruple beta decay
``DBDMODE_21`` ``2nubb_gA_g0``           NA           2nubbg0           0+ -> 0+     {2n} (g0)
``DBDMODE_22`` ``2nubb_gA_g2``           NA           2nubbg2           0+ -> 0+     {2n} (g2)
``DBDMODE_23`` ``2nubb_gA_g22``          NA           2nubbg22          0+ -> 0+     {2n} (g22)
``DBDMODE_24`` ``2nubb_gA_g4``           NA           2nubbg4           0+ -> 0+     {2n} (g4)
============== ========================= ============ ============================================================

.. raw:: pdf

   PageBreak

**Comments on specific modes:**

* The original Decay0 code has changed the so-called *modebb* index of
  some Majoron modes  from versions above 2017 with  respect to former
  versions.  We thus use an index map to ensure backward compatibility
  and force the BxDecay0's interface stable with respect to the original
  C++ port in the Bayeux_/genbb module.
* 5, 6, 13, 14 are Majoron modes with respective spectral index SI:

  - SI=1 - old Gelmini-Roncadelli Majoron
  - SI=3 - double M, vector M, charged M
  - SI=7
  - SI=2 - bulk M of Mohapatra

* 20: quadruple beta decay, possible only for Zr96, Xe136, Nd150 (only to the daughter nucleus' ground state)
* 21, 22, 23, 24: two neutrino double beta decay, gA modes g0, g2, g22, g4 possible only for Se82, Mo100,
  Cd116, Nd150 (only to the daughter nucleus' ground state).


List of standard radioactive isotopes (background/calibration)
--------------------------------------------------------------

From the ``background_isotopes.lis`` resource file:

* ``Ac228``
* ``Am241``
* ``Ar39``
* ``Ar42``
* ``As79`` (for ``As79+Se79m``)
* ``Bi207`` (for ``Bi207+Pb207m``)
* ``Bi208``
* ``Bi210``
* ``Bi212``  (for ``Bi212+Po212``)
* ``Bi214``  (for ``Bi214+Po214``)
* ``C14``
* ``Ca48``  (for ``Ca48+Sc48``)
* ``Cd113``
* ``Co60``
* ``Cs136``
* ``Cs137``  (for ``Cs137+Ba137m``)
* ``Eu147``
* ``Eu152``
* ``Eu154``
* ``Gd146``
* ``Hf182``
* ``I126``
* ``I133``
* ``I134``
* ``I135``
* ``K40``
* ``K42``
* ``Kr81``
* ``Kr85``
* ``Mn54``
* ``Na22``
* ``P32``
* ``Pa231`` (added from Bayeux : 2013-09-06)
* ``Pa234m``
* ``Pb210``
* ``Pb211``
* ``Pb212``
* ``Pb214``
* ``Po210`` (simplified through pure alpha emission : from tag 1.0.6)
* ``Po218`` (simplified through pure alpha emission : from tag 1.0.6)
* ``Ra226`` (added from Bayeux : 2013-07-11)
* ``Ra228``
* ``Rb87``
* ``Rh106``
* ``Rn222`` (added : 2020-07-17)
* ``Sb125``
* ``Sb126``
* ``Sb133``
* ``Sr90``
* ``Ta180m-B-``
* ``Ta180m-EC``
* ``Ta182``
* ``Te133``
* ``Te133m``
* ``Te134``
* ``Th230`` (simplified through pure alpha emission : from tag 1.0.6)
* ``Th234``
* ``Tl207``
* ``Tl208``
* ``U234`` (simplified through pure alpha emission : from tag 1.0.6)
* ``U238`` (simplified through pure alpha emission : from tag 1.0.6)
* ``Xe129m``
* ``Xe131m``
* ``Xe133``
* ``Xe135``
* ``Y88``
* ``Y90`` (new realistic model for positron energy spectrum : from tag 1.0.8)
* ``Zn65``
* ``Zr96`` (for ``Zr96+Nb96``)

Additional comment
------------------

Unlike  the  original  Decay0  code, BxDecay0  does  not  support  the
generation   of   so-called   *artifical*  events   (Compton,   Moller
scattering, e+e- pair).  It should  not be difficult to implement such
generators by yourself independently of BxDecay0.

.. Links

.. _Bayeux: https://github.com/BxCppDev/Bayeux.git
.. _Falaise: https://github.com/SuperNEMO-DBD/Falaise
.. _GSL: https://www.gnu.org/software/gsl/
.. _CLHEP: http://proj-clhep.web.cern.ch/proj-clhep/
.. _ROOT: http://root.cern.ch/
.. _KINR: http://lpd.kinr.kiev.ua/
.. _`LPC Caen`: http://www.lpc-caen.in2p3.fr/
.. _`Université de Caen Normandie`: http://www.unicaen.fr/
.. _`Geant4`: http://geant4.org/
.. _`HepMC`: http://hepmc.web.cern.ch/hepmc/
