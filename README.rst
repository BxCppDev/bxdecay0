============================================================================
BxDecay0 - C++ port of the legacy Decay0 FORTRAN library
============================================================================

:authors: François Mauger, Vladimir Tretyak, Emma Mauger
:date: 2020-07-06
:copyright: Copyright (C) 2017-2020 the BxCppDev group

The **BxDecay0** C++ library provides a set of classes and functions for
the random  generation of simulated  nuclear decays. It consists  in a
C++ port of  the original Decay0 Fortran program (also  known as GENBB
in  some other  context) written  and maintained  by Vladimir  Tretyak
(KINR_).  Decay0 was created to  address the Monte Carlo generation of
nuclear decays  in the context  of double  beta decay and  dark matter
experimental research.

BxDecay0 aims to  be used by any C++ simulation  program that needs to
generate  the kinematics  of primary  particles emitted  from specific
nuclear  decays  (example:  input  for a  Geant4_  based  Monte  Carlo
simulation  program).  It  can be  easily interfaced  with the  HepMC_
event/particle model or any other client application.

.. contents::

.. raw:: pdf

   PageBreak


History
=======

The first version of the Decay0  program was written in the early 90's
by  Vladimir   Tretyak  and   collaborators,  using  the   Fortran  77
programming language and  the CERNLIB library. It  has been maintained
and improved up to now (2020).

From 1992  to 2010, the Decay0/GENBB  code was embedded in  the GEANT3
based  simulation software  of the  NEMO2 and  then NEMO3  double beta
decay experiments.

From 2005 to 2011, the NEMO3 collaboration has initiated a R&D program
to   design   a  new   generation   double   beta  decay   experiment:
SuperNEMO_. The  choice was  made to  use C++  as the  main programming
language.  In this context, François  Mauger has created a C++ version
of GENBB. The first version was  a C++ wrapper of the original Fortran
code,  using binding  mechanism based  on plain  static C  structures.

Later,  a pure  C++ version  was  released without  any dependency  on
Fortran  and  CERNLIB.   This  code  was integrated  in  2011  as  the
``genbb_help`` module of the Bayeux_ C++ library (version < 4).

This release of the BxDecay0 C++  library is extracted from the Bayeux
``genbb_help`` module with some changes from the 2017-03-01 release of
the Decay0 program  by Vladimir Tretyak.  It has then  been updated to
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
  - add optional support for 2nubb gA processes for a few isotopes of interest
    (as a pure C++ implementation with required large external dataset from the
    https://gitlab.in2p3.fr/francois.mauger/bxdecay0data project which is
    automatically loaded).
    
- Release 1.0.3 :

  - fix kinematics issue in DBD gA process

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
model in Decay0 which has strong  limitations in terms of usability in
a  modern OOP  context  (static data  structures).   The BxDecay0  API
introduces its own OOP data  model through the ``bxdecay0::event`` and
``bxdecay0::particle`` classes (see the ``ex01`` example).  It is thus
easy to  use such  classes through  any C++  client program  and/or to
interface with some  high level event generator  library (i.e. HepMC3).
See the ``ex02`` example.

More, BxDecay0 provides the ``bxdecay0::decay0_generator`` class which
wraps low-level functions with a simple OOP interface.

Finally, it is also possible to use the low level C++ functions ported
from  the original  Fortran code.  However it  is not  recommended and
should be reserved to experts and developpers of the library.

.. raw:: pdf

   PageBreak

Installing BxDecay0
===================

Preparation of your system
--------------------------

BxDecay0 is developped  on a Ubuntu Linux (18.04/20.04 LTS)  and should work
on any Unix/BSD  flavor with a recent C++ compiler  with c++11 support
(i.e. GNU g++ >= 4.9) including macOS.

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


Download BxDecay0 source code from the GitHub repository
--------------------------------------------------------

Clone the Git development repository on your filesystem:

.. code:: sh

   $ cd /tmp
   $ git clone https://github.com/BxCppDev/bxdecay0.git bxdecay0.git
   $ cd bxdecay0.git 
..

Or download the archive associated to a released version :

.. code:: sh

   $ cd /tmp
   $ wget https://github.com/BxCppDev/bxdecay0/archive/1.0.3.tar.gz
   $ tar xvzf bxdecay0-1.0.3.tar.gz
   $ cd bxdecay0-1.0.3
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

   $ cmake -DCMAKE_INSTALL_PREFIX=${HOME}/sw/bxdecay0 /tmp/bxdecay0-1.0.3
..


Configuration options:
~~~~~~~~~~~~~~~~~~~~~~

* ``BxDecay0_WITH_DBD_GA`` : Enable support for the specific generator
  of DBD gA processes (default: ``ON``).  This generator requires large
  datasets of tabulated space-phase factors so if you don't need it in
  your  client code,  it is  better to  disable this  features for  it
  implies the downloading of external resource files (~1.7 GB).
  
  Example for disabling DBD gA generators:

  .. code:: bash

     $ cmake ... -DBxDecay0_WITH_DBD_GA=OFF ...
  ..
  

Build, test and install
-----------------------

You will need **Git with LFS support** in order to download data files specific to the DB gA processes.

From the build directory:

.. code:: sh

   $ make -j4
   $ make test
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

  The ``find_package(BxDecay0 1.0 CONFIG)`` CMake command can be given
  the  following variable  to locate  BxDecay0 on  your system  from a
  client project which uses the CMake build system:

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
the neutrinoless double beta decay (DBD) process of :sup:`100` Mo to
the ground state of :sup:`100` Ru.
The resulting events are printed in the  terminal in a very simple format.
It  is of  course  possible to  adapt  this program  and  use the  OOP
interface  of  the  ``bxdecay0::event``  class  in  order  to  extract
physical quantities of interest (particles' type and momentum...).

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
  with HepMC3 formatted ASCII output,
* ``ex03`` : Generation of Co60 decay events with plain ASCII output,
* ``ex04`` : Use of the *plumbing* ``bxdecay0::genbbsub`` function (expert/developper only).
* ``ex05`` : Use of the ``bxdecay0::dbd_gA`` class.

.. raw:: pdf

   PageBreak

License
=======

BxDecay0 is released under the  GNU GENERAL PUBLIC LICENSE, version 3.
See the ``LICENSE.txt`` file.



Authors and contributors
========================

* Vladimir Tretyak (KINR_, Kiev Institute for Nuclear Research, Lepton
  Physics Department, Ukraine) is the original author and maintener of
  the Fortran Decay0 package.
* François Mauger (`LPC Caen`_,  Laboratoire de Physique Corpusculaire
  de Caen, `Université de Caen  Normandie`_, France) is the author and
  maintener   of  the  original C++  port   of  Decay0   within  Bayeux_
  and the BxDecay0 library.
* Emma Mauger (formerly `Université de Caen Normandie`_) has done a large
  part of the extraction and port to C++ of the standalone BxDecay0 from the
  original Bayeux_ *genbb* library module.
* Ben Morgan (Warwick University): CMake build system and package reorganization.
* Malak Hoballah and Laurent Simard (LAL Orsay) (support for DBD generator with gA process).
  
  
References
===========

* Vladimir Tretyak,  *DECAY0 event generator for  initial kinematics of particles  in alpha,  beta and  double  beta decays*,
  talk_ given at Laboratori Nazionali del Gran Sasso, 17 March 2015  :
* O.A.Ponkratenko, V.I.Tretyak, Yu.G.Zdesenko,
  *Event Generator DECAY4 for Simulating Double-Beta Processes and Decays of Radioactive Nuclei*,
  Phys. At. Nucl. 63 (2000) 1282 (`nucl-ex/0104018 <https://arxiv.org/pdf/nucl-ex/0104018.pdf>`_)

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
  and force the BxDecay0 interface stable with respect to the original
  C++ port in the Bayeux_/genbb module.
* 5, 6, 13, 14 are Majoron modes with spectral index SI:
  
  - SI=1 - old Gelmini-Roncadelli Majoron
  - SI=3 - double M, vector M, charged M
  - SI=7
  - SI=2 - bulk M of Mohapatra
	       
* 20: quadruple beta decay, possible only for Zr96, Xe136, Nd150      
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
* ``Ca48``  (for ``Ca48+Sc48``)
* ``C14``
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
* ``Ra226`` (added from Bayeux : 2013-07-11)
* ``Ra228``
* ``Rb87``
* ``Rh106``
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
* ``Th234``
* ``Tl207``
* ``Tl208``
* ``Xe129m``
* ``Xe131m``
* ``Xe133``
* ``Xe135``
* ``Y88``
* ``Y90``
* ``Zn95``
* ``Zr96`` (for ``Zr96+Nb96``)

Additional comment
------------------

Unlike  the  original  Decay0  code, BxDecay0  does  not  support  the
generation   of   so-called   *artifical*  events   (Compton,   Moller
scattering, e+e- pair).  It should  not be difficult to implement such
generators by yourself independently of BxDecay0.

.. Links

.. _Bayeux: https://github.com/BxCppDev/Bayeux.git
.. _GSL: https://www.gnu.org/software/gsl/
.. _ROOT: http://root.cern.ch/
.. _KINR: http://lpd.kinr.kiev.ua/
.. _`LPC Caen`: http://www.lpc-caen.in2p3.fr/
.. _`Université de Caen Normandie`: http://www.unicaen.fr/
.. _`Geant4`: http://geant4.org/
.. _`HepMC`: http://hepmc.web.cern.ch/hepmc/
