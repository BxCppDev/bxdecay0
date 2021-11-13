/// \file HistoManager.cc
/// \brief Implementation of the HistoManager class

// Ourselves:
#include "HistoManager.hh"

// Geant4:
#include "G4UnitsTable.hh"

HistoManager::HistoManager()
  : fFileName("bxdecay0_g4_ex01")
{
  Book();
  return;
}


HistoManager::~HistoManager()
{
  delete G4AnalysisManager::Instance();
  return;
}


void HistoManager::Book()
{
  // Create or get analysis manager
  // The choice of analysis technology is done via selection of a namespace
  // in HistoManager.hh
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetFileName(fFileName);
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetActivation(true);     //enable inactivation of histograms
  
  // Define histograms start values
  const G4int kMaxHisto = 5;
  const G4String id[] = {"0","1","2","3", "4"};
  const G4String title[] = 
    {
     "dummy",               //0
     "energy spectrum (keV): gamma",               //1
     "energy spectrum (keV): e-",                  //2
     "energy spectrum (keV): e+",                  //3
     "energy spectrum (keV): alpha"                //4
    };

  // Default values (to be reset via /analysis/h1/set command)               
  G4int    nbins = 4000;
  G4double vmin  = 0.;    // keV
  G4double vmax  = 4000.; // keV

  // Create all histograms as inactivated 
  // as we have not yet set nbins, vmin, vmax
  for (G4int k = 0; k < kMaxHisto; k++) {
    G4int ih = analysisManager->CreateH1(id[k], title[k], nbins, vmin, vmax);
    analysisManager->SetH1Activation(ih, false);
  }
  return;
}

