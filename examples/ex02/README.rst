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
   ``bxdecay0-query`` utility script should be in your path.
#. Cd in the BxDecay0's ``ex02`` source directory:
#. Configure  and build  ``ex02``  from a  dedicated build  directory,
   assuming HepMC3 is installed from *Linuxbrew* :

   .. code:: bash

      $ mkdir _build.d/   # Make a temporary build directory
      $ cd _build.d/
      $ cmake \
	     -DCMAKE_INSTALL_PREFIX=$(pwd)/../_install.d \
	     -DBxDecay0_DIR=$(bxdecay0-query --cmakedir) \
	     -DHepMC_DIR=$(HepMC-config --prefix)/share/HepMC/cmake \
	     ..
      $ make
      $ make install
      $ cd ..
      $ rm -fr _build.d/  # Remove the temporary build directory
   ..

Run
===

#. Run the executable ``ex02``:

   .. code:: bash

      $ _install.d/bin/ex02
   ..

#. Enjoy the ``bxdecay_ex02-hepmc3-ascii.data`` output file!


.. The end.
