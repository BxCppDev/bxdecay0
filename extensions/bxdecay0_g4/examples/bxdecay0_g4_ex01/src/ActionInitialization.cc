/// \file ActionInitialization.cc
/// \brief Implementation of the ActionInitialization class

#include "ActionInitialization.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "TrackingAction.hh"
#include "SteppingVerbose.hh"

// BxDecay0 geant4 Plugin:
#include "bxdecay0_g4/primary_generator_action.hh"
#include "bxdecay0_g4/unique_point_vertex_generator.hh"

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

  // Instantiate a specific vertex generator (with its own internal messenger):
  G4ThreeVector pointLikeSOurce(0.0 * CLHEP::mm, 0.0 * CLHEP::mm, 0.0 * CLHEP::mm);
  bxdecay0_g4::UniquePointVertexGenerator * vertexGen =
    new bxdecay0_g4::UniquePointVertexGenerator(pointLikeSOurce);

  // Instantiate the BxDecay0/Geant4 PGA (with its own internal messenger):
  bxdecay0_g4::PrimaryGeneratorAction * primary
    = new bxdecay0_g4::PrimaryGeneratorAction;
  primary->SetVertexGenerator(vertexGen); // Install a specific vertex generator in the PGA
  SetUserAction(primary);

  // More user actions:
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

