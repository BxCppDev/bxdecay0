================================
BxDecay0 example ex01
================================

:author: François Mauger
:date: 2020-11-20
:copyright: Copyright (C) 2017-2020 the BxCppDev group

.. contents::

Introduction
============

This    example   ``ex01.cxx``    illustrates   the    use   of    the
``bxdecay0::decay0_generator``  class to  generate random  double beta
decay events for various isotopes and decay modes.

The program stores the generated events  in an output ASCII file using
a very simple format.  The parsing of  this file is let as an exercise
to the user.

A  variant  ``ex01bis.cxx``  is  also provided.  It  uses  a  slightly
different output  format with no  *decoration* and an  arbitrary event
number per generated event.


Build
=====

#. BxDecay0   should    be   setup   on   your    system,   i.e.   the
   ``bxdecay0-config`` utility script should be in your path.
#. Cd in the BxDecay0's ``ex01`` source directory:
#. Configure and build ``ex01`` from a dedicated build directory:

   .. code:: bash

      $ mkdir _build.d/   # Make a temporary build directory
      $ cd _build.d/
      $ cmake -DBxDecay0_DIR=$(bxdecay0-config --cmakedir) ..
      $ make

Run
===

#. Run the executable ``ex01``:

   .. code:: bash

      $ ./ex01


#. Enjoy the ``bxdecay_ex01.data`` output file!

..
   The end.
