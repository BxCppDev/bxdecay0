/// \file EventAction.hh
/// \brief Definition of the EventAction class

#ifndef EventAction_hh
#define EventAction_hh 1

// Geant4:
#include "G4UserEventAction.hh"
#include "globals.hh"

class EventAction
  : public G4UserEventAction
{
public:
  
  EventAction();

  ~EventAction() override;

public:

  void BeginOfEventAction(const G4Event*) override;

  void EndOfEventAction(const G4Event*) override;
  
};

#endif // EventAction_hh

    
