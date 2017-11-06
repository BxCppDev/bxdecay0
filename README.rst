============================================================================
bxdecay0 - C++ port of the legacy Decay0/GENBB FORTRAN library
============================================================================

:authors: François Mauger
:date: 2017-11-06
:copyright: Copyright (C) 2017 the BxCppDev group

The *BxDecay0* C++ library provides a set of classes and functions for
the random  generation of simulated  nuclear decays. It consists  in a
C++  port of  the original  Decay0/GENBB Fortran  program written  and
maintained by  Vladimir Tretyak (KINR_).  Decay0/GENBB  was created to
address the Monte Carlo generation of nuclear decays in the context of
double beta decay and dark matter experimental research.

BxDecay0 aims to  be used by any C++ simulation  program that needs to
generate  the kinematics  of primary  particles emitted  from specific
nuclear  decays  (example:  input  for  a  Geant4_  based  Monte-Carlo
simulation  program).   It  can  be  easily   interfaced  with  HepMC_
event/particle model.

.. contents::

.. raw:: pdf

   PageBreak


History
=======

The first version of the Decay0/GENBB program was written in the early
90's  by Vladimir  Tretyak  and collaborators,  using  the Fortran  77
programming language and  the CERNLIB library. It  has been maintained
and improved up to now (2017).

From 1992  to 2010, the  GENBB code was  embedded in the  GEANT3 based
simulation  software of  the NEMO2  and then  NEMO3 double  beta decay
experiments.

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
``genbb_help`` module with  some changes from the last  release of the
Decay0/GENBB  program.   It is  a  standalone  library with  very  few
dependencies (mostly the GSL_ library  for numerical integration and a
few  special math  functions).  External  random engines  can be  used
through a simple wrapping interface, particularly the ones provided by
the C++ standard library can be  used by default.  However the user is
free to  provide its own  uniform deviates random generator  (based on
GSL_, ROOT_ or whatever).

.. _SuperNEMO: http://supernemo.org/

Design
======

Plumbing
--------

The core of the BxDecay0 code  does not follow a fully object-oriented
approach.   In order  to ensure  the easy  synchronization of  its low
level code  with the original  Decay0/GENBB code, BxDecay0  mimics the
layout of  the Fortran  code (including massive  usage of  *GOTOs*!).
BxDecay0 thus provides a large collection of plain generator functions
for  about 100  radioactive nuclei  split in  two categories:
*double beta* decays and *background/calibration* decays.  When a Decay0/GENBB
fix or  improvement is published in  the original Fortran code  by its
author (V.Tretyak),  it is thus  rather easy to adequately  change the
C++ code in the relevant section in BxDecay0.

Porcelain
---------

Hopefully, BxDecay0 gets rid of the original *common block* based data
model  in  Decay0/GENBB  which  has strong  limitations  in  terms  of
usability  in a  modern  OOP context  (static  data structures).   The
BxDecay0  API   introduces  its  own   OOP  data  model   through  the
``bxdecay0::event``  and   ``bxdecay0::particle``  classes   (see  the
``ex01`` example).   It is thus easy  to use such classes  through any
C++  client program  and/or to  interface with  some high  level event
generator library (i.e. HepMC).  See the ``ex02`` example.

More, BxDecay0 provides the ``bxdecay0::decay0_generator`` class which
wraps low-level GENBB functions with a simple OOP interface.

.. raw:: pdf

   PageBreak

Installing BxDecay0
===================

Preparation of your system
--------------------------

BxDecay0 is developped  on a Ubuntu Linux (16.04 LTS)  and should work
on any Unix/BSD  flavor with a recent C++ compiler  with c++11 support
(i.e. GNU g++ >= 4.9).

Requirements for Ubuntu 16.04 LTS
---------------------------------

The following lines give some hints  to prepare your system before the
installation  of BxDecay0.  Some  instructions may  vary  on your  own
system.

#. Install GNU C++ compiler:

   .. code:: sh

      $ sudo apt-get install g++-5

#. Install CMake:

   .. code:: sh

      $ sudo apt-get install cmake

#. Install the GNU scientific library (development package):

   .. code:: sh

      $ sudo apt-get install libgsl-dev
      $ gsl-config --version
      2.1


Download BxDecay0 source code from the GitHub repository
--------------------------------------------------------

Clone the Git development repository on your filesystem:

.. code:: sh

   $ cd /tmp
   $ git clone https://github.com/BxCppDev/bxdecay0.git bxdecay0.git

Or download the archive associated to a released version :

.. code:: sh

   $ cd /tmp
   $ wget https://github.com/BxCppDev/bxprotobuftools/archive/1.0.0.tar.gz
   $ tar xvzf 1.0.0.tar.gz
   $ cd bxdecay0-1.0.0


Configuration
-------------

Here we use a temporary build directory and choose to install BxDecay0
in our home directory:

.. code:: sh

   $ mkdir /tmp/_build.d
   $ cd /tmp/_build.d
   $ cmake -DCMAKE_INSTALL_PREFIX=${HOME}/bxdecay0 /tmp/bxdecay0.git

or:

.. code:: sh

   $ cmake -DCMAKE_INSTALL_PREFIX=${HOME}/bxdecay0 /tmp/bxdecay0-1.0.0



Build, test and install
-----------------------

From the build directory:

.. code:: sh

   $ make -j4
   $ make test
   $ make install


Manual setup
------------

Add the following line in your shell startup script (i.e. ``~/.bashrc``):

.. code:: sh

   $ export PATH=${HOME}/bxdecay0/bin:$PATH


The ``bxdecay0-query`` script will be usable from your projects:

.. code:: sh

   $ which bxdecay0-query

Using Linuxbrew
---------------

As  an alternative  to  the manual  installation  proposed above,  the
BxCppDev   group  provides   the   ``bxdecay0``   formula_  from   the
``bxcppdev/homebrew-bxtap``  Linuxbrew  tap.  This allows  to  install
BxDecay0 from the Linuxbrew package management system.

.. _formula: https://github.com/BxCppDev/homebrew-bxtap


Utilities
---------

* The   ``bxdecay0-query``  utility   script  allows   you  to   fetch
  informations about your BxDecay0 installation.

  .. code:: sh

     $ bxdecay0-query --help
     $ bxdecay0-query --prefix
     $ bxdecay0-query --version
     $ bxdecay0-query --cmakedir


* CMake  configuration  scripts  are      provided:

  * ``BxDecay0Config.cmake``,
  * ``BxDecay0ConfigVersion.cmake``.

  The ``find_package(BxDecay0 1.0 CONFIG)`` CMake command can be given
  the  following variable  to locate  BxDecay0 on  your system  from a
  client project which uses the CMake build system:

  .. code:: sh

     $ cmake -DBxDecay0_DIR="$(bxdecay0-query --cmakedir)" ...


.. raw:: pdf

   PageBreak


Usage
======

Basic program
-------------

The following program is taken from the BxDecay0's ``ex00`` example:

.. code:: c++

   #include <iostream>
   #include <bxdecay0/std_random.h>
   #include <bxdecay0/event.h>
   #include <bxdecay0/decay0_generator.h>

   int main()
   {
     unsigned int seed = 314159;
     std::default_random_engine generator(seed);
     bxdecay0::std_random prng(generator);

     bxdecay0::decay0_generator decay0;
     decay0.set_decay_category(bxdecay0::decay0_generator::DECAY_CATEGORY_DBD);
     decay0.set_decay_isotope("Mo100");
     decay0.set_decay_dbd_level(0);
     decay0.set_decay_dbd_mode(bxdecay0::MODEBB_1);
     decay0.initialize(prng);

     std::size_t nevents = 10;
     for (std::size_t ievent = 0; ievent < nevents; ievent++) {
       bxdecay0::event gendecay;
       decay0.shoot(prng, gendecay);
       gendecay.store(std::cout);
     }

     decay0.reset();
     return 0;
   }


List of examples
----------------

* ``ex00`` : Minimal program for  the generation of Mo100 neutrinoless
  double beta decay events with plain ASCII output,
* ``ex01`` : Generation of Mo100 two neutrino double beta decay events
  with plain ASCII output,
* ``ex02`` : Generation of Mo100 two neutrino double beta decay events
  with HepMC3 formatted ASCII output,
* ``ex03`` : Generation of Co60 decay events with plain ASCII output,
* ``ex04`` : Use of the *plumbing* ``bxdecay0::genbbsub`` function (expert/developper only).

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
  the Fortran Decay0/GENBB package,
* François Mauger (`LPC Caen`_,  Laboratoire de Physique Corpusculaire
  de Caen, `Université de Caen  Normandie`_, France) is the author and
  maintener   of  the   C++  port   of  Decay0/GENBB   within  Bayeux_
  (https://github.com/BxCppDev/Bayeux) and the current BxDecay0 library,
* Emma Mauger (`Université de Caen  Normandie`_) has performed a large
  part of the extraction and port to C++ of the standalone BxDecay0 from the
  Bayeux_ *genbb* library module.

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

* ``Ca40``, ``Ca46``, ``Ca48``,
* ``Ni58``,
* ``Zn64``, ``Zn70``,
* ``Ge76``,
* ``Se74``, ``Se82``,
* ``Sr84``,
* ``Zr94``, ``Zr96``,
* ``Mo92``, ``Mo100``,
* ``Ru96``, ``Ru104``,
* ``Cd106``, ``Cd108``, ``Cd114``, ``Cd116``,
* ``Sn112``, ``Sn122``, ``Sn124``,
* ``Te120``, ``Te128``, ``Te130``,
* ``Xe136``,
* ``Ce136``, ``Ce138``, ``Ce142``,
* ``Nd148``, ``Nd150``,
* ``Dy156``, ``Dy158``,
* ``W180``, ``W186``,
* ``Os184``, ``Os192``,
* ``Pt190``, ``Pt198``,
* ``Bi214`` (for ``Bi214+At214``),
* ``Pb214`` (for ``Pb214+Po214``),
* ``Po218`` (for ``Po218+Rn218+Po214``),
* ``Rn222`` (for ``Rn222+Ra222+Rn218+Po214``),
* ``Rn226`` (for ``Rn226``).

.. raw:: pdf

   PageBreak

List of daughter nucleus excited states in double beta decay
------------------------------------------------------------

* ``Ca48-Ti48`` :

  0. 0+ (gs) {0 MeV},
  1. 2+ (1) {0.984 MeV},
  2. 2+ (2) {2.421 MeV},

* ``Ni58-Fe58`` :

  0. 0+ (gs) {0 MeV},
  1. 2+ (1) {0.811 MeV},
  2. 2+ (2) {1.675 MeV},

* ``Zn64-Ni64`` :

  0. 0+ (gs) {0 MeV},

* ``Zn70-Ge70`` :

  0. 0+ (gs) {0 MeV},

* ``Ge76-Se76`` :

  0. 0+ (gs) {0 MeV},
  1. 2+ (1) {0.559 MeV},
  2. 0+ (1) {1.122 MeV},
  3. 2+ (2) {1.216 MeV},

* ``Se74-Ge74`` :

  0. 0+ (gs) {0 MeV},
  1. 2+ (1) {0.596 MeV},
  2. 2+ (2) {1.204 MeV},

* ``Se82-Kr82`` :

  0. 0+ (gs) {0 MeV},
  1. 2+ (1) {0.776 MeV},
  2. 2+ (2) {1.475 MeV},

* ``Sr84-Kr84`` :

  0. 0+ (gs) {0 MeV},
  1. 2+ (1) {0.882 MeV},

* ``Zr94-Mo94`` :

  0. 0+ (gs) {0 MeV},
  1. 2+ (1) {0.871 MeV},

* ``Zr96-Mo96`` :

  0. 0+ (gs) {0 MeV},
  1. 2+ (1) {0.778 MeV},
  2. 0+ (1) {1.148 MeV},
  3. 2+ (2) {1.498 MeV},
  4. 2+ (3) {1.626 MeV},
  5. 2+ (4) {2.096 MeV},
  6. 2+ (5) {2.426 MeV},
  7. 0+ (2) {2.623 MeV},
  8. 2+ (6) {2.700 MeV},
  9. 2+?(7) {2.713 MeV},

* ``Mo92-Zr92`` :

  0. 0+ (gs) {0 MeV},
  1. 2+ (1) {0.934 MeV},
  2. 0+ (1) {1.383 MeV},

* ``Mo100-Ru100`` :

  0. 0+ (gs) {0 MeV},
  1. 2+ (1) {0.540 MeV},
  2. 0+ (1) {1.130 MeV},
  3. 2+ (2) {1.362 MeV},
  4. 0+ (2) {1.741 MeV},

* ``Ru96-Mo96`` :

  0. 0+ (gs) {0 MeV},
  1. 2+ (1) {0.778 MeV},
  2. 0+ (1) {1.148 MeV},
  3. 2+ (2) {1.498 MeV},
  4. 2+ (3) {1.626 MeV},
  5. 2+ (4) {2.096 MeV},
  6. 2+ (5) {2.426 MeV},
  7. 0+ (2) {2.623 MeV},
  8. 2+ (6) {2.700 MeV},
  9. 2+?(7) {2.713 MeV},

* ``Ru104-Pd104`` :

  0. 0+ (gs) {0 MeV},
  1. 2+ (1) {0.556 MeV},

* ``Cd106-Pd106`` :

  0. 0+ (gs) {0 MeV},
  1. 2+ (1) {0.512 MeV},
  2. 2+ (2) {1.128 MeV},
  3. 0+ (1) {1.134 MeV},
  4. 2+ (3) {1.562 MeV},
  5. 0+ (2) {1.706 MeV},

* ``Cd108-Pd108`` :

  0. 0+ (gs) {0 MeV},

* ``Cd114-Sn114`` :

  0. 0+ (gs) {0 MeV},

* ``Cd116-Sn116`` :

  0. 0+ (gs) {0 MeV},
  1. 2+ (1) {1.294 MeV},
  2. 0+ (1) {1.757 MeV},
  3. 0+ (2) {2.027 MeV},
  4. 2+ (2) {2.112 MeV},
  5. 2+ (3) {2.225 MeV},

* ``Sn112-Cd112`` :

  0. 0+ (gs) {0 MeV},
  1. 2+ (1) {0.618 MeV},
  2. 0+ (1) {1.224 MeV},
  3. 2+ (2) {1.312 MeV},
  4. 0+ (2) {1.433 MeV},
  5. 2+ (3) {1.469 MeV},
  6. 0+ (3) {1.871 MeV},

* ``Sn122-Te122`` :

  0. 0+ (gs) {0 MeV},

* ``Sn124-Te124`` :

  0. 0+ (gs) {0 MeV},
  1. 2+ (1) {0.603 MeV},
  2. 2+ (2) {1.326 MeV},
  3. 0+ (1) {1.657 MeV},
  4. 0+ (2) {1.883 MeV},
  5. 2+ (3) {2.039 MeV},
  6. 2+ (4) {2.092 MeV},
  7. 0+ (3) {2.153 MeV},
  8. 2+ (5) {2.182 MeV},

* ``Te120-Sn120`` :

  0. 0+ (gs) {0 MeV},
  1. 2+ (1) {1.171 MeV},

* ``Te128-Xe128`` :

  0. 0+ (gs) {0 MeV},
  1. 2+ (1) {0.443 MeV},

* ``Te130-Xe130`` :

  0. 0+ (gs) {0 MeV},
  1. 2+ (1) {0.536 MeV},
  2. 2+ (2) {1.122 MeV},
  3. 0+ (1) {1.794 MeV},

* ``Xe136-Ba136`` :

  0. 0+ (gs) {0 MeV},
  1. 2+ (1) {0.819 MeV},
  2. 2+ (2) {1.551 MeV},
  3. 0+ (1) {1.579 MeV},
  4. 2+ (3) (2.080 MeV},
  5. 2+ (4) {2.129 MeV},
  6. 0+ (2) {2.141 MeV},
  7. 2+ (5) {2.223 MeV},
  8. 0+ (3) {2.315 MeV},
  9. 2+ (6) {2.400 MeV},

* ``Ce136-Ba136`` :

  0. 0+ (gs) {0 MeV},
  1. 2+ (1) {0.819 MeV},
  2. 2+ (2) {1.551 MeV},
  3. 0+ (1) {1.579 MeV},
  4. 2+ (3) (2.080 MeV},
  5. 2+ (4) {2.129 MeV},
  6. 0+ (2) {2.141 MeV},
  7. 2+ (5) {2.223 MeV},
  8. 0+ (3) {2.315 MeV},
  9. 2+ (6) {2.400 MeV},

* ``Ce138-Ba138`` :

  0. 0+ (gs) {0 MeV},

* ``Ce142-Nd142`` :

  0. 0+ (gs) {0 MeV},

* ``Nd148-Sm148`` :

  0. 0+ (gs) {0 MeV},
  1. 2+ (1) {0.550 MeV},
  2. 2+ (2) {1.455 MeV},

* ``Nd150-Sm150`` :

  0. 0+ (gs) {0 MeV},
  1. 2+ (1) {0.334 MeV},
  2. 0+ (1) {0.740 MeV},
  3. 2+ (2) {1.046 MeV},
  4. 2+ (3) {1.194 MeV},
  5. 0+ (2) {1.256 MeV}

* ``Dy156-Gd156`` :

  0. 0+ (gs) {0 MeV},
  1. 2+ (1) {0.089 MeV},
  2. 0+ (1) {1.050 MeV},
  3. 2+ (2) {1.129 MeV},
  4. 2+ (3) {1.154 MeV},
  5. 0+ (2) {1.168 MeV},
  6. 2+ (4) {1.258 MeV},
  7. 0+ (3) {1.715 MeV},
  8. 2+ (5) {1.771 MeV},
  9. 2+ (6) {1.828 MeV},
  10. 0+ (4) {1.851 MeV},
  11. 2+ (7) {1.915 MeV},
  12. 1- {1.946 MeV},
  13. 0- {1.952 MeV},
  14. 0+ (5) {1.989 MeV},
  15. 2+ (8) {2.004 MeV},

* ``Dy158-Gd158`` :

  0. 0+ (gs) {0 MeV},
  1. 2+ (1) {0.080 MeV},
  2. 4+ (1) {0.261 MeV}

* ``W180-Hf180`` :

  0. 0+ (gs) {0 MeV}

* ``W186-Os186`` :

  0. 0+ (gs) {0 MeV},
  1. 2+ (1) {0.137 MeV}

* ``Pt190-Os190`` :

  0. 0+ (gs) {0 MeV},
  1. 2+ (1) {0.187 MeV},
  2. 2+ (2) {0.558 MeV},
  3. 0+ (1) {0.912 MeV},
  4. 2+ (3) {1.115 MeV},
  5. 0+ (2) {1.382 MeV}

* ``Pt198-Hg198`` :

  0. 0+ (gs) {0 MeV},
  1. 2+ (1) {0.412 MeV}

* ``Bi214-At214`` :

  0. 1- (gs) {0 MeV}

* ``Pb214-Po214`` :

  0. 0+ (gs) {0 MeV}

* ``Po218-Rn218`` :

  0. 0+ (gs) {0 MeV}

* ``Rn222-Ra222`` :

  0. 0+ (gs) {0 MeV}


.. raw:: pdf

   PageBreak

List of supported double beta decay modes
-----------------------------------------

1. ``bxdecay0::MODEBB_1`` : 0nubb(mn), with neutrino mass, 0+ -> 0+ {2n},
2. ``bxdecay0::MODEBB_2`` : 0nubb(rhc-lambda), with rhc-lambda,   0+ -> 0+ {2n},
3. ``bxdecay0::MODEBB_3`` : 0nubb(rhc-lambda), with rhc-lambda, 0+ -> 0+, 2+ {N*},
4. ``bxdecay0::MODEBB_4`` : 2nubb, 0+ -> 0+ {2n},
5. ``bxdecay0::MODEBB_5`` : 0nuM1bb, 0+ -> 0+ {2n}

   Majoron with spectral index SI=1 (old M of Gelmini-Roncadelli),
6. ``bxdecay0::MODEBB_6`` : 0nuM3bb, 0+ -> 0+ {2n}

   Majoron with SI=3 (vector M, double M, charged M),
7. ``bxdecay0::MODEBB_7`` : 0nubb(rhc-lambda),  with rhc-lambda, 0+ -> 2+ {2n},
8. ``bxdecay0::MODEBB_8`` : 2nubb, 0+ -> 2+ {2n}, {N*},
9. ``bxdecay0::MODEBB_9`` : 0nuKb+, 0+ -> 0+, 2+,
10. ``bxdecay0::MODEBB_10`` : 2nuKb+, 0+ -> 0+, 2+,
11. ``bxdecay0::MODEBB_11`` : 0nu2K, 0+ -> 0+, 2+,
12. ``bxdecay0::MODEBB_12`` : 2nu2K, 0+ -> 0+, 2+,
13. ``bxdecay0::MODEBB_13`` : 0nuM7bb, 0+ -> 0+ {2n}

    Majoron with SI=7,
14. ``bxdecay0::MODEBB_14`` : 0nuM2bb, 0+ -> 0+ {2n}

    Majoron with SI=2 (bulk M of Mohapatra)
15. ``bxdecay0::MODEBB_15`` : 2nubb, 0+ -> 0+ with bosonic neutrinos,
16. ``bxdecay0::MODEBB_16`` : 2nubb, 0+ -> 2+ with bosonic neutrinos,
17. ``bxdecay0::MODEBB_17`` : 0nubb(rhc-eta), with rhc-eta , 0+ -> 0+ simplified expression,
18. ``bxdecay0::MODEBB_18`` : 0nubb(rhc-eta), with rhc-eta , 0+ -> 0+ with specified NMEs.
19. ``bxdecay0::MODEBB_19`` : 2nubb with LV,  0+ -> 0+, with Lorentz violation
20. ``bxdecay0::MODEBB_20`` : 0nu4b,          0+ -> 0+, quadruple beta decay

SI: *Spectral Index* for Majoron modes.

.. raw:: pdf

   PageBreak

List of standard radioactive isotopes (background/calibration)
--------------------------------------------------------------

* ``Ac228``,
* ``Am241``,
* ``Ar39``,
* ``Ar42``,
* ``As79`` (for ``As79+Se79m``),
* ``Bi207`` (for ``Bi207+Pb207m``),
* ``Bi208``,
* ``Bi210``,
* ``Bi212``  (for ``Bi212+Po212``),
* ``Bi214``  (for ``Bi214+Po214``),
* ``Ca48``  (for ``Ca48+Sc48``),
* ``C14``,
* ``Cd113``,
* ``Co60``,
* ``Cs136``,
* ``Cs137``  (for ``Cs137+Ba137m``),
* ``Eu147``,
* ``Eu152``,
* ``Eu154``,
* ``Gd146``,
* ``Hf182``,
* ``I126``,
* ``I133``,
* ``I134``,
* ``I135``,
* ``K40``,
* ``K42``,
* ``Kr81``,
* ``Kr85``,
* ``Mn54``,
* ``Na22``,
* ``P32``,
* ``Pa231`` (added 2013-09-06),
* ``Pa234m``,
* ``Pb210``,
* ``Pb211``,
* ``Pb212``,
* ``Pb214``,
* ``Ra226`` (added 2013-07-11),
* ``Ra228``,
* ``Rb87``,
* ``Rh106``,
* ``Sb125``,
* ``Sb126``,
* ``Sb133``,
* ``Sr90``,
* ``Ta182``,
* ``Te133``,
* ``Te133m``,
* ``Te134``,
* ``Th234``,
* ``Tl207``,
* ``Tl208``,
* ``Xe129m``,
* ``Xe131m``,
* ``Xe133``,
* ``Xe135``,
* ``Y88``,
* ``Y90``,
* ``Zn95``,
* ``Zr96`` (for ``Zr96+Nb96``).


Additional comment
------------------

Unlike  the  original  Decay0/GENBB,  BxDecay0 does  not  support  the
generation   of   so-called   *artifical*  events   (Compton,   Moller
scattering, e+e- pair).  It should  not be difficult to implement such
generators by yourself.

.. Links

.. _Bayeux: https://github.com/BxCppDev/Bayeux.git
.. _GSL: https://www.gnu.org/software/gsl/
.. _ROOT: http://root.cern.ch/
.. _KINR: http://lpd.kinr.kiev.ua/
.. _`LPC Caen`: http://www.lpc-caen.in2p3.fr/
.. _`Université de Caen Normandie`: http://www.unicaen.fr/
.. _`Geant4`: http://geant4.org/
.. _`HepMC`: http://hepmc.web.cern.ch/hepmc/
