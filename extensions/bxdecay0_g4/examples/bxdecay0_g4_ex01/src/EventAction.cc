/// \file EventAction.cc
/// \brief Implementation of the EventAction class

// Ourselves:
#include "EventAction.hh"

// Standard library:
#include <iomanip>

// Geant4:
#include "G4Event.hh"
#include "G4RunManager.hh"

// This project:
#include "HistoManager.hh"
#include "Run.hh"

EventAction::EventAction()
  : G4UserEventAction()
{
  // Set default print level 
  G4RunManager::GetRunManager()->SetPrintProgress(500);
  return;
}


EventAction::~EventAction()
{
  return;
}


void EventAction::BeginOfEventAction(const G4Event*)
{
  
  return;
}


void EventAction::EndOfEventAction(const G4Event* evt)
{
  G4int evtID = evt->GetEventID(); 
  G4int printProgress = G4RunManager::GetRunManager()->GetPrintProgress();
  // Printing survey:
  if (evtID % printProgress == 0) {
    G4cout << "End of event #" << evtID << "." << G4endl << G4endl;
  }
  // Run * run 
  //   = static_cast<Run*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
  // run->EvisEvent(fEvisTot);
  return;
}



