================================
BxDecay0 example ex05
================================

:author: François Mauger
:date: 2020-05-10
:copyright: Copyright (C) 2020 the BxCppDev group

.. contents::

Introduction
============

This    example   ``ex05.cxx``    illustrates   the    use   of    the
``bxdecay0::dbd_gA`` class to randomly  generate the kinematics of the
electrons  emitted  in  the  double beta  decay  process  for  various
isotopes and some special gA decay mode.

The program stores the generated kinetic energies in an output ASCII file using
a very simple format. 

Build
=====

#. BxDecay0   should    be   setup   on   your    system,   i.e.   the
   ``bxdecay0-config`` utility script should be in your path.
#. Cd in the BxDecay0's ``ex05`` source directory:
#. Configure and build ``ex05`` from a dedicated build directory:

   .. code:: bash

      $ mkdir _build.d/   # Make a temporary build directory
      $ cd _build.d/
      $ cmake -DBxDecay0_DIR=$(bxdecay0-config --cmakedir) ..
      $ make
      $ cd ..
   ..

Run
===

The example program uses the Se-82 DBD emitter nuclide (``"Se82"``) and
its  tabulated 2-dimension  c.d.f. to  represent the  distribution of
individual kinetic energies of the  emitted beta particles in ``"g0"``
mode.

#. Run the executable ``ex05``:

   .. code:: bash

      $ ./_build.d/ex05
   ..

#. Output files:

   * ``bxdecay_ex05_1.data`` : randomized (E1,E2) kinetic energies of the betas		
   * ``bxdecay_ex05_2.data`` : generated individual kinetic energies of the betas		
   * ``bxdecay_ex05_3.data`` : sum of generated individual kinetic energy of the betas
   * ``bxdecay_ex05_4.data`` : generated cosines of the angle between individual momenta of the betas

#. Sample images:
	 
   .. figure:: images/bxdecay0_ex05_2d-pdf_random.jpg
      :width: 95%

      Randomized (E1,E2) kinetic energies of the two emitted electrons
   
     
   .. figure:: images/bxdecay0_ex05_e1e2.jpg
      :width: 75%

      Histograms of generated E1 and E2 individual kinetic energies

   .. figure:: images/bxdecay0_ex05_esum.jpg
      :width: 75%
	      
      Histogram of the sum of generated kinetic energies 

   .. figure:: images/bxdecay0_ex05_cos12.jpg
      :width: 75%
	      
      Histogram of the cos(theta) 

.. The end.
