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
#include "BoxBulkVertexGenerator.hh"
#include "VertexGeneratorRecorder.hh"

ActionInitialization::ActionInitialization(const DetectorConstruction * detector_)
 : G4VUserActionInitialization()
 , fDetector(detector_)
{
  std::clog << "[log] ActionInitialization::ActionInitialization: fDetector @" << fDetector << "!\n"; 
}


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

  // Instantiate a vertex generator from the source volume:
  BoxBulkVertexGenerator * vertexGen = new BoxBulkVertexGenerator;
  std::clog << "[log] ActionInitialization::Build: Source solid @" << fDetector->GetSourceSolid() << "!\n"; 
  vertexGen->SetBoxLogicalVolume(fDetector->GetSourceLogicalVolume());
  vertexGen->SetBoxTranslation(fDetector->GetSourceTranslation());
  vertexGen->SetBoxRotation(fDetector->GetSourceRotation());
  vertexGen->SetTolerance(1.0 * CLHEP::mm);
  vertexGen->SetRandomSeed(314159);
  vertexGen->SetNoDaughters(true);

  // Wrap the vertex generator to store the vertex coordinates in a separate file for checking:
  VertexGeneratorRecorder * vertexRecorder = new VertexGeneratorRecorder(vertexGen, "source_bulk_vertexes-xyz.data");
 
  // Instantiate the BxDecay0/Geant4 PGA (with its own internal messenger):
  bxdecay0_g4::PrimaryGeneratorAction * primary
    = new bxdecay0_g4::PrimaryGeneratorAction;
  primary->SetVertexGenerator(vertexRecorder); // Install a specific vertex generator in the PGA
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
  std::clog << "[log] ActionInitialization::InitializeSteppingVerbose: Entering...\n";
  return new SteppingVerbose();
}  

