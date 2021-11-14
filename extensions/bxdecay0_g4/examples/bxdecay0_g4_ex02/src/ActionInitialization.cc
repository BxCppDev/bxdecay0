/// \file ActionInitialization.cc
/// \brief Implementation of the ActionInitialization class

// Standard library
#include <string>

#include "ActionInitialization.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "TrackingAction.hh"
#include "SteppingVerbose.hh"

// BxDecay0 geant4 Plugin:
#include "bxdecay0_g4/primary_generator_action.hh"
#include "bxdecay0_g4/unique_point_vertex_generator.hh"

namespace {
  /// Wrapper class to workaround memory management in Geant4
  struct NoMemoryLeakVertexGenerator : public bxdecay0_g4::VertexGeneratorInterface
  {
    NoMemoryLeakVertexGenerator(std::shared_ptr<bxdecay0_g4::VertexGeneratorInterface> vg_)
      : _vg_(vg_) {}
    ~NoMemoryLeakVertexGenerator() override = default;
    bool HasNextVertex() const override { return _vg_->HasNextVertex(); }
    void ShootVertex(G4ThreeVector & vertex_) override { _vg_->ShootVertex(vertex_); } 
    std::shared_ptr<bxdecay0_g4::VertexGeneratorInterface> _vg_;
  };
}

ActionInitialization::ActionInitialization(const DetectorConstruction * detector_,
                                           const Config & config_)
 : G4VUserActionInitialization()
 , fDetector(detector_)
 , fConfig(config_)
{
  std::clog << "[log] ActionInitialization::ActionInitialization: fDetector @" << fDetector << "\n"; 
  std::clog << "[log] ActionInitialization::ActionInitialization: UseLoader = " << std::boolalpha << fConfig.UseLoader << "\n"; 
  std::clog << "[log] ActionInitialization::ActionInitialization: UseRecorder = " << std::boolalpha << fConfig.UseRecorder << "\n"; 
  std::clog << "[log] ActionInitialization::ActionInitialization: VertexFilename = '" << fConfig.VertexFilename << "'\n"; 
}


ActionInitialization::~ActionInitialization()
{
  if (fLoaderVG.get()) {
    fLoaderVG.reset();
  }
  if (fRecorderVG.get()) {
    fRecorderVG.reset();
  }
  if (fBoxBulkVG.get()) {
    fBoxBulkVG.reset();
  }
}


void ActionInitialization::BuildForMaster() const
{
  RunAction* runAction = new RunAction(0);
  SetUserAction(runAction);
  return;
}


void ActionInitialization::Build() const
{
  NoMemoryLeakVertexGenerator * currentVertexGenerator = nullptr;
  ActionInitialization * mutableThis = const_cast<ActionInitialization*>(this);
  if (fConfig.UseLoader) {
    // Instantiate a vertex generator which loads the vertex coordinates from a file:
    mutableThis->fLoaderVG.reset(new VertexPoolLoader(fConfig.VertexFilename));
    currentVertexGenerator = new NoMemoryLeakVertexGenerator(mutableThis->fLoaderVG);
  } else { 
    // Instantiate a vertex generator from the source volume:
    mutableThis->fBoxBulkVG.reset(new BoxBulkVertexGenerator);
    std::clog << "[log] ActionInitialization::Build: Source solid @" << fDetector->GetSourceSolid() << "!\n"; 
    mutableThis->fBoxBulkVG->SetBoxLogicalVolume(fDetector->GetSourceLogicalVolume());
    mutableThis->fBoxBulkVG->SetBoxTranslation(fDetector->GetSourceTranslation());
    mutableThis->fBoxBulkVG->SetBoxRotation(fDetector->GetSourceRotation());
    mutableThis->fBoxBulkVG->SetTolerance(1.0 * CLHEP::mm);
    mutableThis->fBoxBulkVG->SetRandomSeed(314159);
    mutableThis->fBoxBulkVG->SetNoDaughters(true);
    if (fConfig.UseRecorder) {
      // Wrap the vertex generator to store the vertex coordinates in a file:
      mutableThis->fRecorderVG.reset(new VertexGeneratorRecorder(mutableThis->fBoxBulkVG, fConfig.VertexFilename));
      currentVertexGenerator = new NoMemoryLeakVertexGenerator(mutableThis->fRecorderVG);
    } else {
      currentVertexGenerator = new NoMemoryLeakVertexGenerator(mutableThis->fBoxBulkVG);
    }
  }
 
  // Instantiate the BxDecay0/Geant4 PGA (with its own internal messenger):
  bxdecay0_g4::PrimaryGeneratorAction * primary = new bxdecay0_g4::PrimaryGeneratorAction;
  primary->SetVertexGenerator(currentVertexGenerator); // Install the vertex generator in the PGA
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

