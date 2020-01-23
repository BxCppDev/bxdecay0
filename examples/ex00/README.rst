================================
BxDecay0 example ex00
================================

:author: François Mauger
:date: 2017-10-31
:copyright: Copyright (C) 2017 the BxCppDev group

.. contents::

Introduction
============

This    example   ``ex00.cxx``    illustrates   the    use   of    the
``bxdecay0::decay0_generator``  class to  generate random  double beta
decay events for various isotopes and decay modes.

The program stores the generated events  in an output ASCII file using
a very simple format.  The parsing of  this file is let as an exercise
to the user.

Build
=====

#. BxDecay0   should    be   setup   on   your    system,   i.e.   the
   ``bxdecay0-config`` utility script should be in your path.
#. Cd in the BxDecay0's ``ex00`` source directory:
#. Configure and build ``ex00`` from a dedicated build directory:

   .. code:: bash

      $ mkdir _build.d/   # Make a temporary build directory
      $ cd _build.d/
      $ cmake -DBxDecay0_DIR=$(bxdecay0-config --cmakedir) ..
      $ make
   ..

Run
===

#. Run the executable ``ex00``:

   .. code:: bash

      $ ./ex00 > bxdecay_ex00.data
   ..

#. Enjoy the ``bxdecay_ex00.data`` output file!

.. The end.
