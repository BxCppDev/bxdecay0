/// \file TrackingAction.hh
/// \brief Definition of the TrackingAction class

#ifndef TrackingAction_hh
#define TrackingAction_hh 1

// Geant4:
#include "G4UserTrackingAction.hh"
#include "globals.hh"

class EventAction;
class TrackingMessenger;

class TrackingAction
  : public G4UserTrackingAction
{

public:  

  TrackingAction(EventAction*);

  ~TrackingAction() override;

  void PreUserTrackingAction(const G4Track*) override;

  void PostUserTrackingAction(const G4Track*) override;
    
private:
  
  EventAction * fEvent = nullptr;
  G4double fCharge = 0.0;
  G4double fMass = 0.0;
  
};

#endif // TrackingAction_hh
