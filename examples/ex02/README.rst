================================
BxDecay0 example ex02
================================

:author: François Mauger
:date: 2017-10-30
:copyright: Copyright (C) 2017 the BxCppDev group

.. contents::


Introduction
============

This    example   ``ex02.cxx``    illustrates   the    use   of    the
``bxdecay0::decay0_generator``  class to  generate random  double beta
decay events for various isotopes and decay modes.

The program  stores the generated events  in an output file  using the
HepMC3  ASCII  format.   Thus  you  should  have  the  HepMC3  library
installed  and setup  on  your  system, for  instance  from the  Spack
package manager.

Build
=====

#. BxDecay0   should    be   setup   on   your    system,   i.e.   the
   ``bxdecay0-config`` utility script should be in your path.
#. Cd in the BxDecay0's ``ex02`` source directory:
#. Configure  and build  ``ex02``  from a  dedicated build  directory,
   assuming HepMC3 is installed from *Linuxbrew* :

   .. code:: bash

      $ mkdir _build.d/  # Make a temporary build directory
      $ cd _build.d/
      $ # Update the PATH for the spack-installed HepMC library:
      $ export PATH=$(spack find --format "{prefix}" bxdecay0)/bin:${PATH}
      $ export PATH=$(spack find --format "{prefix}" hepmc3)/bin:${PATH}
      $ cmake \
	     -DBxDecay0_DIR=$(bxdecay0-config --cmakedir) \
	     -DHepMC3_DIR=$(HepMC3-config --prefix)/share/HepMC/cmake \
	     ..
      $ make
   ..

Run
===

#. Run the executable ``ex02``:

   .. code:: bash

      $ ./ex02
   ..

#. Enjoy the ``bxdecay_ex02-hepmc3-ascii.data`` output file!


.. The end.
