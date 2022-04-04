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
generating  decay  events  from  BxDecay0. Its  usage  is  mainly  for
experts.  Normal users  should use  the ``bxdecay0::decay0_generator``
class   which    wraps   in    a   OOP    approach   the   *magic*  of
``bxdecay0::genbbsub``  inherited from  the Decay0  Fortran code  (see
example ``ex01``, ``ex02`` and ``ex03``).

Build
=====

#. BxDecay0   should    be   setup   on   your    system,   i.e.   the
   ``bxdecay0-config`` utility script should be in your path.
#. Cd in the BxDecay0's ``ex04`` source directory:
#. Configure and build ``ex04`` from a dedicated build directory:

   .. code:: bash

      $ mkdir _build.d/   # Make a temporary build directory
      $ cd _build.d/
      $ cmake -DBxDecay0_DIR=$(bxdecay0-config --cmakedir) ..
      $ make

Run
===

#. Run the executable ``ex04``:

   .. code:: bash

      $ ./ex04


..
   The end.
