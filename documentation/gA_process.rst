============================================================
DBD generator and the g4 processes
============================================================

:authors: F.Mauger (LPC Caen), M. Hoballah (LAL Orsay), L.Simard (LAL Orsay)
:date: 2020-02-13

Introduction
=============
       
Support for the gA mechanism in double beta decayis provided through
a dedicated generator in BxDecay0.

This generator is not ported/extracted from the legacy Decay0 program, but
provided as a specific extension of BxDecay0 and implemented in pure C++ code
without Fortran-based counterpart in Decay0.

TODO:

This generator can be integrated in the ``bxdecay0::decay0_generator`` class' interface.
So far only a small set of nuclides is supported (see below).

- The ``bxdecay0::dbd_mode_type`` (see ``bxdecay/bb_utils.h`` header)
  must be extended with new supported values:

  - ``DBDMODE_2NUBB_GA_G0`` : g0 process
  - ``DBDMODE_2NUBB_GA_G2``  : g2 process
  - ``DBDMODE_2NUBB_GA_G22`` : g22 process
  - ``DBDMODE_2NUBB_GA_G4`` : g4 process
	  
- The ``bxdecay0::decay0_generator::_init_``, ``bxdecay0::decay0_generator::_reset_``
  and ``bxdecay0::decay0_generator::shoot`` methods
  must be upgraded to support the ``bxdecay0::dbd_gA`` generator for the new DBD modes above.
  
Supported DBD emitter nuclides
==============================

Set through a string parameter:

- ``Ca48``
- ``Se82``
- ``Mo100``
- ``Cd116``
- ``Nd150``


Supported *gA* processes
==========================

Set through a enumerated parameter:

- ``g0`` : g0 process
- ``g2`` : g2 process
- ``g22`` : g22 process
- ``g4`` : g4 process

.. raw:: pdf
	 
   PageBreak
..
  

Class ``bxdecay0::dbd_gA``
===========================

Source code
--------------

* ``bxdecay0/dbd_gA.h`` : header
* ``bxdecay0/dbd_gA.cc`` : implementation

   TODO:

   - Implement the ``bxdecay0::dbd_gA::shoot_cos_theta`` method;
   - Implement the ``bxdecay0::dbd_gA::export_to_event`` static method.
  
Resource data files
-------------------


The generator is provided with resource data files which
contain the tabulated 2-dimension joint p.d.f.'s for the sampling of
kinetic energies of both emitted electrons for all supported nuclides and processes.

* From the BxDecay0's package source directory,
  the base directory is : ``resources/data/dbd_gA/``
* The files are installed automatically from the BxDecay0 installation prefix
  in the following subdirectory: ``share/BxDecay0-1.0.1/resources/data/dbd_gA/``.
  The generator is designed to automatically find and parse the proper resource file
  to be loaded in association to a given supported nuclide and gA process.
* The structure of this directory should be:

  ::
     
     resources/data/dbd_gA/
     |-- Ca48
     |   |-- g0
     |   |   `-- tab_pdf.data
     |   |-- g2
     |   |   `-- tab_pdf.data
     |   |-- g22
     |   |   `-- tab_pdf.data
     |   `-- g4
     |       `-- tab_pdf.data
     |-- Mo100
     |   |-- g0
     |   |   `-- tab_pdf.data
     |   |-- g2
     |   |   `-- tab_pdf.data
     |   |-- g22
     |   |   `-- tab_pdf.data
     |   `-- g4
     |       `-- tab_pdf.data
     .
     .  (more nuclides)
     .
     `-- Test
         `-- g0
             `-- tab_pdf.data
	     
  ..

  with each nuclide having 4 tabulated p.d.f.
  files associated to each supported *g process*.
* The format supported by ``tab_pdf.data`` files is illustrated
  by the ``resources/data/dbd_gA/Test/g0/tab_pdf.data`` mock file.

  Typically, this looks like:

  ::

     3.034                 # Qbb end point in MeV
     linear 1000 0.0 3.034 # E1 regular sampling model (MeV) 
     linear 1000 0.0 3.034 # E2 regular sampling model (MeV)
     # 2D-tabulated joint probability P(E1,E2) in arbitrary units (1000x1000 values)
     P_0,0   P_0,1   P_0,2   P_0,3   . . .  P_0,999
     P_1,0   P_1,1   P_1,2   P_1,3   . . .  P_1,999
       .       .       .       .             .
       .       .       .       .             .
       .       .       .       .             .
     P_999,0 P_999,1 P_999,2 P_999,3 . . .  P_999,999
     
  ..

  This format must be considered as preliminary.
  There are ways to optimize it in the future.
  At least it is a good starting point.
     
* TODO:

  - Optimize the format:

    - Consider to remove redundancies in the header:
    - Consider not to store *zeroes* in the tabulated p.d.f..
      The probability is obviously 0 for each node with E1+E2 > Qbb in the grid.
      We could thus save  ~50 % of storage.

    ::

     3.034 # Qbb end point in MeV
     1000  # E1 & E2 regular sampling model (MeV) 
     P_0,0   P_0,1    . . .   P_0,998  P_0,999
     P_1,0   P_1,1    . . .   P_1,998
      .        .             .
      .        .      .        
      .        .           
     P_998,0 P_998,1  
     P_999,0 
     
 
  - Consider to distribute gzip-ed ``tab_pdf.data``.

The class
---------

* Any instance of the ``bxdecay0::dbd_gA`` class must be initialized
  after being passed some configuration parameters:

  - the nuclide (see the list above);
  - the g-process (see the list above);
  - the shooting method (only the *Von Neumann rejection method* is supported for now).

* The ``bxdecay0::dbd_gA::initialize`` method triggers the
  loading of the proper resource  file and the building of internal tabulated
  p.d.f..
* The ``bxdecay0::dbd_gA::shoot_e1_e2`` fires the kinetic energies of
  both emitted electrons, depending on the selected nuclide and process.
* The ``bxdecay0::dbd_gA::shoot_cos_theta`` fires the cosine of the angle
  between the emitted electrons, depending on their energies.

  **Remark:** This method is implemented with a default flat angular distribution
  and must be updated with a relatistic p.d.f..
  
* Once ``e1``, ``e2`` and ``cos12`` have been randomized, the
  ``bxdecay0::dbd_gA::export_to_event`` static method should be used to
  fill a ``bxdecay0::event`` object:

  **Remark:** This method is not implemented yet.
  
* The ``bxdecay0::dbd_gA::reset`` method terminates the generator.
  

  

Example
---------

BxDecay0's example ``ex05`` illustrates the use of the ``bxdecay0::dbd_gA`` generator.

TODO: Implement a realistic case with a supported nuclide.

  


  
Mail from Laurent (2020-01-24)
==============================

CCIN2P3: /pbs/home/s/simard/public/ga.tgz

Les fichiers de quenching pour les isotopes Ca48, Se82, Mo100, Cd116, Nd150
et les processus G0, G2, G22, G4.

Dans chaque sous répertoire ga/"isotope"/"process"/ ,
il y a un fichier nEqNull.dat qui contient pour chaque ligne
respectivement l'énergie du 1er électron E1, l'énergie du 2e
électron (en MeV) E2 et la probabilité conjointe P(E1, E2).

Dans le sous-répertoire ga/082Se/0-N0, le programme ReadGa.C
crée le fichier ascii appelé cumulative_prob qui contient l'énergie
du 1er électron E1, l'énergie du 2e électron (en MeV) E2 et la
probabilité cumulée P(E1, E2).

Fichiers P(E1, E2) fournis par Ratislav Dvornicki.
