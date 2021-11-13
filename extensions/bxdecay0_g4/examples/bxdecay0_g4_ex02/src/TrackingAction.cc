/// \file TrackingAction.cc
/// \brief Implementation of the TrackingAction class

// Ourselves:
#include "TrackingAction.hh"

// Geant4:
#include "G4Track.hh"
#include "G4ParticleTypes.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

// This project:
#include "HistoManager.hh"
#include "Run.hh"
#include "EventAction.hh"

TrackingAction::TrackingAction(EventAction* EA)
  : G4UserTrackingAction(),
    fEvent(EA)
{
  return;
}

TrackingAction::~TrackingAction()
{
  return;
}

void TrackingAction::PreUserTrackingAction(const G4Track * track)
{
  int local_verbosity = 0;
  if (local_verbosity > 2) std::cerr << "[trace] TrackingAction::PreUserTrackingAction: Entering..." << '\n';
  Run * run 
   = static_cast<Run*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());      
  G4int ID = track->GetTrackID();
  G4ParticleDefinition * particle = track->GetDefinition();
  G4String name = particle->GetParticleName();
  fCharge = particle->GetPDGCharge();
  fMass   = particle->GetPDGMass();  
  G4double Ekin = track->GetKineticEnergy();
  if (local_verbosity > 1) {
    std::cerr << "[debug] TrackingAction::PreUserTrackingAction: Track ID #" << ID << '\n';
    std::cerr << "[debug] TrackingAction::PreUserTrackingAction:   Name   = '" << name << "'" << '\n';
    std::cerr << "[debug] TrackingAction::PreUserTrackingAction:   Charge = " << fCharge << " (e)" << '\n';
    std::cerr << "[debug] TrackingAction::PreUserTrackingAction:   Mass   = " << (fMass / MeV) << " (MeV)" << '\n';
    std::cerr << "[debug] TrackingAction::PreUserTrackingAction:   Ekin   = " << (Ekin / keV) << " (keV)" << '\n';
  }
  // Count particles:
  run->ParticleCount(name, Ekin);
  // Energy spectrum:
  G4int ih = -1;
  if (particle == G4Gamma::Gamma()) ih = 1;
  else if (particle == G4Electron::Electron()) ih = 2;
  else if (particle == G4Positron::Positron()) ih = 3;
  else if (particle == G4Alpha::Alpha()) ih = 4;
  if (ih > 0) G4AnalysisManager::Instance()->FillH1(ih, Ekin);
  if (local_verbosity > 2) std::cerr << "[trace] TrackingAction::PreUserTrackingAction: Exiting..." << '\n';
  return;
}

void TrackingAction::PostUserTrackingAction(const G4Track* /* track */)
{
  return;
}

