/// \file PhysicsList.cc
/// \brief Implementation of the PhysicsList class

// Ourselves:
#include "PhysicsList.hh"

// Geant4:
#include "G4UnitsTable.hh"
#include "G4ParticleTypes.hh"
#include "G4IonConstructor.hh"
#include "G4PhysicsListHelper.hh"
#include "G4Radioactivation.hh"
#include "G4SystemOfUnits.hh"
#include "G4NuclideTable.hh"
#include "G4LossTableManager.hh"
#include "G4UAtomicDeexcitation.hh"
#include "G4NuclearLevelData.hh"
#include "G4DeexPrecoParameters.hh"
#include "G4NuclideTable.hh"


PhysicsList::PhysicsList()
  : G4VUserPhysicsList()
{
  // Add new units for radioActive decays:
  const G4double minute = 60 * second;
  const G4double hour   = 60 * minute;
  const G4double day    = 24 * hour;
  const G4double year   = 365 * day;
  new G4UnitDefinition("minute", "min", "Time", minute);
  new G4UnitDefinition("hour",   "h",   "Time", hour);
  new G4UnitDefinition("day",    "d",   "Time", day);
  new G4UnitDefinition("year",   "y",   "Time", year);

  // Mandatory for G4NuclideTable:
  G4NuclideTable::GetInstance()->SetThresholdOfHalfLife(0.1 * picosecond);
  G4NuclideTable::GetInstance()->SetLevelTolerance(1.0 * eV);

  // Read new PhotonEvaporation data set:
  G4DeexPrecoParameters* deex = 
    G4NuclearLevelData::GetInstance()->GetParameters();
  deex->SetCorrelatedGamma(false);
  deex->SetStoreAllLevels(true);
  deex->SetMaxLifeTime(G4NuclideTable::GetInstance()->GetThresholdOfHalfLife()
                / std::log(2.));
  return;
}


PhysicsList::~PhysicsList()
{
  return;
}


void PhysicsList::ConstructParticle()
{
  G4Geantino::GeantinoDefinition();
  G4Gamma::GammaDefinition();
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();
  G4Alpha::AlphaDefinition();
  return;
}


void PhysicsList::ConstructProcess()
{
  AddTransportation();
  return;
}


void PhysicsList::SetCuts()
{
  SetCutsWithDefault();
  return;
}

