/// \file ActionInitialization.hh
/// \brief Definition of the ActionInitialization class

#ifndef ActionInitialization_hh
#define ActionInitialization_hh 1

#include "G4VUserActionInitialization.hh"
#include "DetectorConstruction.hh"

class G4VSteppingVerbose;

/// Action initialization class.
///

class ActionInitialization
  : public G4VUserActionInitialization
{
public:

  ActionInitialization(const DetectorConstruction * detector_);

  ~ActionInitialization() override;
  
  void BuildForMaster() const override;
  
  void Build() const override;
  
  G4VSteppingVerbose* InitializeSteppingVerbose() const override;

  const DetectorConstruction * GetDetector() const { return fDetector; }

private:
  const DetectorConstruction * fDetector = nullptr;
  
};

#endif // ActionInitialization_hh 

    
