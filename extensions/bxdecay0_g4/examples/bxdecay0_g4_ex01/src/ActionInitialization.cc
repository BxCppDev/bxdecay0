/// \file ActionInitialization.cc
/// \brief Implementation of the ActionInitialization class

#include "ActionInitialization.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "TrackingAction.hh"
#include "SteppingVerbose.hh"

// BxDecay0 geant4 Plugin:
#include "bxdecay0_g4/primary_generator_action.hh"


ActionInitialization::ActionInitialization()
 : G4VUserActionInitialization()
{}


ActionInitialization::~ActionInitialization()
{}


void ActionInitialization::BuildForMaster() const
{
  RunAction* runAction = new RunAction(0);
  SetUserAction(runAction);
  return;
}


void ActionInitialization::Build() const
{
  bxdecay0_g4::PrimaryGeneratorAction * primary
    = new bxdecay0_g4::PrimaryGeneratorAction;
  SetUserAction(primary);
    
  RunAction* runAction = new RunAction(primary);
  SetUserAction(runAction);
  
  EventAction* eventAction = new EventAction();
  SetUserAction(eventAction);
  
  TrackingAction* trackingAction = new TrackingAction(eventAction);
  SetUserAction(trackingAction);
  return;
}  


G4VSteppingVerbose* ActionInitialization::InitializeSteppingVerbose() const
{
  std::cerr << "ActionInitialization::InitializeSteppingVerbose: Entering...\n";
  return new SteppingVerbose();
}  

