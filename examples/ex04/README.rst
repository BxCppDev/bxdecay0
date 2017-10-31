================================
BxDecay0 example ex04
================================

:author: François Mauger
:date: 2017-10-30
:copyright: Copyright (C) 2017 the BxCppDev group

.. contents::

Introduction
============

This    example   ``ex04.cxx``    illustrates   the    use   of    the
``bxdecay0::genbbsub`` function  to generate random double  beta decay
events for various isotopes and decay modes.

The  ``bxdecay0::genbbsub``  function  is  the low  level  engine  for
generating decay  events from  BxDecay0. Its usage  is for  mainly for
experts. Normal users  should favor the ``bxdecay0::decay0_generator``
class   which    wraps   in    a   OOP    approach   the    magic   of
``bxdecay0::genbbsub`` (see example ``ex01``, ``ex02`` and ``ex03``).

Build
=====

#. BxDecay0 should be setup on your system, i.e. the ``bxdecay0-query`` utility script
   should be in your path.
#. Cd in the BxDecay0's ``ex04`` source directory:
#. Configure and build ``ex04`` from a dedicated build directory:

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

#. Run the executable ``ex04``:

   .. code:: bash

      $ _install.d/bin/ex04


..
   The end.
