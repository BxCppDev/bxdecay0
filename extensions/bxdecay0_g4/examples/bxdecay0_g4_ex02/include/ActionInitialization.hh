/// \file ActionInitialization.hh
/// \brief Definition of the ActionInitialization class

#ifndef ActionInitialization_hh
#define ActionInitialization_hh 1

#include "G4VUserActionInitialization.hh"
#include "DetectorConstruction.hh"

class G4VSteppingVerbose;

// BxDecay0 geant4 Plugin:
#include "BoxBulkVertexGenerator.hh"
#include "VertexGeneratorRecorder.hh"
#include "VertexPoolLoader.hh"

/// Action initialization class.
class ActionInitialization
  : public G4VUserActionInitialization
{
public:

  /// \brief Configuration parameters of the ActionInitialization class
  struct Config
  {
    bool UseLoader = false; ///< Flag to load vertexes from a file with name VertexFilename
    bool UseRecorder = false; ///< Flag to store generated vertexes in a file with name VertexFilename
    std::string VertexFilename; ///< Name of the ASCII vertex file
  };

  ActionInitialization(const DetectorConstruction * detector_,
                       const Config & config_);

  ~ActionInitialization() override;
  
  void BuildForMaster() const override;
  
  void Build() const override;
  
  G4VSteppingVerbose* InitializeSteppingVerbose() const override;

  const DetectorConstruction * GetDetector() const { return fDetector; }

private:

  // Configuration
  const DetectorConstruction * fDetector = nullptr; ///< Geometry setup
  Config fConfig; ///< Configuration parameters
  
  // Internal working stuff
  std::shared_ptr<BoxBulkVertexGenerator>  fBoxBulkVG;
  std::shared_ptr<VertexGeneratorRecorder> fRecorderVG;
  std::shared_ptr<VertexPoolLoader>        fLoaderVG;
  
};

#endif // ActionInitialization_hh 

    
