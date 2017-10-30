================================
BxDecay0 example ex03
================================

:author: François Mauger
:date: 2017-10-30
:copyright: Copyright (C) 2017 the BxCppDev group

.. contents::

Introduction
============

This    example   ``ex03.cxx``    illustrates   the    use   of    the
``bxdecay0::genbbsub`` function to generate random Co-60 decay events.

As in ``ex01``,  the program stores the generated events  in an output
ASCII file  using a very simple  format.  The parsing of  this file is
let as an exercise to the user.

Build
=====

#. BxDecay0 should be setup on your system, i.e. the ``bxdecay0-query`` utility script
   should be in your path.
#. Cd in the BxDecay0's ``ex03`` source directory:
#. Configure and build ``ex03`` from a dedicated build directory:

   .. code:: bash

      $ mkdir _build.d/   # Make a temporary build directory
      $ cd _build.d/
      $ cmake \
	     -DCMAKE_INSTALL_PREFIX=$(pwd)/../_install.d \
	     -DBxDecay0_DIR=$(bxdecay0-query --cmakedir) \
	     ..
      $ make
      $ make install
      $ cd ..
      $ rm -fr _build.d/  # Remove the temporary build directory


Run
===

#. Run the executable ``ex03``:

   .. code:: bash

      $ _install.d/bin/ex03


#. Enjoy the ``gendecay0.data`` output file!



..
   The end.
