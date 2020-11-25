/// \file RunAction.cc
/// \brief Implementation of the RunAction class

// Standard library:
#include <iomanip>
#include <iostream>

// Geant4:
#include "G4Run.hh"
#include "G4UnitsTable.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

// BxDecay0 geant4 Plugin:
#include "bxdecay0_g4/primary_generator_action.hh"

// This project:
#include "RunAction.hh"
#include "Run.hh"
#include "HistoManager.hh"

RunAction::RunAction(bxdecay0_g4::PrimaryGeneratorAction * kin_)
  : G4UserRunAction()
  , fPrimary(kin_)
  , fRun(nullptr)
  , fHistoManager(nullptr)
{
  fHistoManager = new HistoManager();
  return;
}

RunAction::~RunAction()
{
  delete fHistoManager;
}

G4Run* RunAction::GenerateRun()
{ 
  // G4cerr << "[trace] RunAction::GenerateRun: Entering...\n";
  fRun = new Run();
  // G4cerr << "[trace] RunAction::GenerateRun: Exiting...\n";
  return fRun;
}

void RunAction::BeginOfRunAction(const G4Run*)
{ 
  // G4cerr << "[trace] RunAction::BeginOfRunAction: Entering...\n";
  // Keep run condition:
  if (fPrimary) {
    // std::cerr << "[debug] RunAction::BeginOfRunAction: Has primary \n";
    G4ParticleDefinition * particle 
      = fPrimary->GetParticleGun()->GetParticleDefinition();
    G4double energy = fPrimary->GetParticleGun()->GetParticleEnergy();
    fRun->SetPrimary(particle, energy);
  }     
      
  // Histograms:
  G4AnalysisManager * analysisManager = G4AnalysisManager::Instance();
  if (analysisManager->IsActive()) {
    G4cerr << "[info] RunAction::EndOfRunAction: Opening histograms file(s)...\n";
    analysisManager->OpenFile();
  }
  // G4cerr << "[trace] RunAction::BeginOfRunAction: Exiting...\n";
  return;
}

void RunAction::EndOfRunAction(const G4Run*)
{
  // G4cerr << "[trace] RunAction::EndOfRunAction: Entering...\n";
  if (isMaster) fRun->EndOfRun();
            
  // Save histograms:
  G4AnalysisManager * analysisManager = G4AnalysisManager::Instance();
  if (analysisManager->IsActive()) {
    G4cerr << "[info] RunAction::EndOfRunAction: Saving histograms...\n";
    analysisManager->Write();
    G4cerr << "[info] RunAction::EndOfRunAction: Closing histograms file(s)...\n";
    analysisManager->CloseFile();
  } 
  // G4cerr << "[trace] RunAction::EndOfRunAction: Exiting...\n";
  return;
}

