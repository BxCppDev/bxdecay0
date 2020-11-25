/// \file PhysicsList.hh
/// \brief Definition of the PhysicsList class

#ifndef PhysicsList_hh
#define PhysicsList_hh 1

// Geant4:
#include "G4VUserPhysicsList.hh"
#include "globals.hh"

class PhysicsList
  : public G4VUserPhysicsList
{
public:

  PhysicsList();

  ~PhysicsList();

protected:

  // Construct particle and physics

  void ConstructParticle() override;
  void ConstructProcess() override; 
  void SetCuts() override;   
};

#endif // PhysicsList_hh



