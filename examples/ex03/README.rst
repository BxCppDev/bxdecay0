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
``bxdecay0::decay0_generator``  class to  generate random  Co-60 decay
events.

As in ``ex03``,  the program stores the generated events  in an output
ASCII file  using a very simple  format.  The parsing of  this file is
let as an exercise to the user.

Build
=====

#. BxDecay0 should be setup on your system, i.e. the ``bxdecay0-config`` utility script
   should be in your path.
#. Cd in the BxDecay0's ``ex03`` source directory:
#. Configure and build ``ex03`` from a dedicated build directory:

   .. code:: bash

      $ mkdir _build.d/   # Make a temporary build directory
      $ cd _build.d/
      $ cmake -DBxDecay0_DIR=$(bxdecay0-config --cmakedir) ..
      $ make

Run
===

#. Run the executable ``ex03``:

   .. code:: bash

      $ ./ex03


#. Enjoy the ``bxdecay_ex03.data`` output file!



..
   The end.
