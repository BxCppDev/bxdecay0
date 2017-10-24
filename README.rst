============================================================================
bxdecay0 - C++ port of the legacy Decay0/GENBB FORTRAN library
============================================================================

The *BxDecay0* C++ library and its  associated tools consists in a set
of C++ classes and utilities for  the random generation of the nuclear
decays.   It consists  in  a  C++ port  of  the original  Decay0/GENBB
Fortran program  written by Vladimir  Tretyak (KINR_).  It aims  to be
used  by  any  C++  simulation  program that  needs  to  generate  the
kinematics of  primary particles emitted from  specific nuclear decays
(example: Geant4_ based Monte-Carlo simulation program).

.. contents::

.. raw:: pdf

   PageBreak

Preparation of your system
============================

BxDecay0 is developped  on a Ubuntu Linux (16.04 LTS)  and should work
on any Unix/BSD  flavor with a recent C++ compiler  with c++11 support
(i.e. GNU g++ >= 4.9).

Requirements for Ubuntu 16.04 LTS
---------------------------------------

#. Install GNU C++ compiler:

   .. code:: sh

      $ sudo apt-get install g++-5

#. Install CMake:

   .. code:: sh

      $ sudo apt-get install CMake

#. Install the GNU scientific library (development package):

   .. code:: sh

      $ sudo apt-get install libgsl-dev
      $ gsl-config --version
      2.1


Using Linuxbrew
--------------------------

BxCppDev group provides the ``bxtap``  formula_ to install BxDecay0 in
a Linuxbrew package management framework.

.. _formula: https://github.com/BxCppDev/homebrew-bxtap


Build and install
========================

Download BxDecay0 from the GitHub repository
---------------------------------------------

Clone the Git repository on your filesystem:

.. code:: sh

   $ cd /tmp
   $ git clone https://github.com/BxCppDev/bxdecay0.git bxdecay0.git



Configure
-------------------

Here we use a temporary build directory and choose to install BxDecay0
in our home directory:

.. code:: sh

   $ mkdir /tmp/_build.d
   $ cd /tmp/_build.d
   $ cmake -DCMAKE_INSTALL_PREFIX=${HOME}/bxdecay0 /tmp/bxdecay0.git



Build, test and install
------------------------

From the build directory:

.. code:: sh

   $ make -j4
   $ make test
   $ make install


Using BxDecay0
====================

Manual setup
------------------------

Add the following line in your shell startup script (i.e. ``~/.bashrc``):

.. code:: sh

   $ export PATH=${HOME}/bxdecay0/bin:$PATH


The ``bxdecay0-query`` script will be usable from your projects:

.. code:: sh

   $ which bxdecay0-query


Utilities
----------------------

* The  ``bxdecay0-query`` utility  allows  you  to fetch  informations
  about your BxDecay0 installation.

  .. code:: sh

     $ bxdecay0-query --help
     $ bxdecay0-query --prefix
     $ bxdecay0-query --version
     $ bxdecay0-query --cmakedir


* CMake  configuration  scripts   (i.e.  ``BxDecay0Config.cmake``  and
  ``BxDecay0ConfigVersion.cmake``) are  provided for  client software.
  The CMake ``find_package(BxDecay0 1.0 CONFIG)`` command can be given
  the following variable to successfully find BxDecay0 on your system:

  .. code:: sh

     $ cmake -DBxDecay0_DIR="$(bxdecay0-query --cmakedir)" ...






License
========================

BxDecay0 is released under the  GNU GENERAL PUBLIC LICENSE, version 3.
See the ``LICENSE.txt`` file.



Authors and contributors
========================

* Vladimir Tretyak (KINR_, Kiev Institute for Nuclear Research, Lepton
  Physics Department,  Ukraine): original author and  maintener of the
  Fortran Decay0/GENBB project,
* François Mauger (`LPC Caen`_,  Laboratoire de Physique Corpusculaire
  de   Caen,  France):   C++  port   of  Decay0/GENBB   within  Bayeux
  (https://github.com/BxCppDev/Bayeux),
* Emma Mauger  (`Normandie Université`_):  Extraction and port  of the
  standalone BxDecay0 from the Bayeux's *genbb* library module.

.. _KINR: http://lpd.kinr.kiev.ua/
.. _`LPC Caen`: http://www.lpc-caen.in2p3.fr/
.. _`Normandie Université`: http://www.unicaen.fr/
.. _`Geant4`: http://geant4.org/


References
===========

* Vladimir Tretyak,  *DECAY0 event generator for  initial kinematics of particles  in alpha,  beta and  double  beta decays*,
  talk_ given at Laboratori Nazionali del Gran Sasso, 17 March 2015  :
* O.A.Ponkratenko, V.I.Tretyak, Yu.G.Zdesenko,
  *Event Generator DECAY4 for Simulating Double-Beta Processes and Decays of Radioactive Nuclei*,
  Phys. At. Nucl. 63 (2000) 1282 (nucl-ex/0104018)

.. _talk: https://agenda.infn.it/materialDisplay.py?materialId=slides&confId=9358


Using BxDecay0
==============
