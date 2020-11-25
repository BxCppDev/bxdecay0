=================================
BxDecay0 Geant4 extension library
=================================

:authors: François Mauger
:date: 2020-11-25
:copyright: Copyright (C) 2020 the BxCppDev group

The  **BxDecay0  geant4  extension library**  provides  a  programming
interface for  use within the  Geant4 Simulation Toolkit,  including a
*primary generator action* class and its associated messenger.

The ``bxdecay0_g4_ex01`` example is provided  to illustrate the use of
the BxDecay0 Geant4 generator Driver.

The BxDecay0 Geant4 extension library  is built together with the core
BxDecay0  library  if   the  ``BXDECAY0_WITH_GEANT4_EXTENSION``  CMake
option is set at configuration step of BxDecay0.

Available classes
=================

* ``bxdecay0_g4::PrimaryGeneratorAction``   :  This   is  the   Geant4
  compatible  primary   generator  action  which  embeds   a  BxDecay0
  generator  (using  the PIMPL  idiom)  and  provides a  configuration
  interface usable through a dedicated messenger.
* ``bxdecay0_g4::PrimaryGeneratorActionMessenger``   :  This   is  the
  Geant4       messenger      class       associated      to       the
  ``bxdecay0_g4::PrimaryGeneratorAction`` class.
* ``bxdecay0_g4::VertexGeneratorInterface``  :  This  is  an  abstract
  class  (interface) from  which concrete  *vertex generator*  classes
  must be inherited for vertex sampling in Geant4.
* ``bxdecay0_g4::UniquePointVertexGenerator``  :  This is  a  concrete
  *vertex        generator*         class        inherited        from
  *``bxdecay0_g4::VertexGeneratorInterface``*.
    

Example
=======

* ``bxdecay0_g4_ex01`` : Simple Geant4 simulation setup which uses the
  BxDecay0 Geant4 extension library  to generate primary particles and
  build associated energy histograms.






