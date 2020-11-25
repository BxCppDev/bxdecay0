/// \file DetectorConstruction.hh
/// \brief Definition of the DetectorConstruction class

#ifndef DetectorConstruction_hh
#define DetectorConstruction_hh 1

// Geant4:
#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"


class DetectorConstruction
  : public G4VUserDetectorConstruction
{
public:
  
  DetectorConstruction();

  ~DetectorConstruction() override;

  G4VPhysicalVolume* Construct() override;
                        
  G4double GetWorldSize() { return fWorldSize; } 

private:
  
  G4double fWorldSize;
};


#endif // DetectorConstruction_hh

