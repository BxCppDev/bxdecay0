/// \file DetectorConstruction.hh
/// \brief Definition of the DetectorConstruction class

#ifndef DetectorConstruction_hh
#define DetectorConstruction_hh 1

// Geant4:
#include "G4VUserDetectorConstruction.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4Box.hh"
#include "globals.hh"

// CLHEP
#include <CLHEP/Units/SystemOfUnits.h>

class DetectorConstruction
  : public G4VUserDetectorConstruction
{
public:
  
  DetectorConstruction();

  ~DetectorConstruction() override;

  G4VPhysicalVolume * Construct() override;
  G4double GetWorldSize() { return fWorldSize; }
  const G4Box * GetSourceSolid() const { return fSourceSolid; }
  const G4ThreeVector & GetSourceTranslation() const { return fSourceTranslation; }
  const G4RotationMatrix & GetSourceRotation() const { return fSourceRotation; }
  const G4LogicalVolume * GetSourceLogicalVolume() const { return fSourceLogicalVolume; }

private:

  /// Construct the detector geometry at constructor step to enable the use of  
  /// geometry informations from other user actions (see ActionInitialization::Build)
  void PreConstruct();

private:
  
  G4double fWorldSize;
  G4double fSourceSizeX;
  G4double fSourceSizeY;
  G4double fSourceSizeZ;
  G4Box * fSourceSolid = nullptr;
  G4LogicalVolume * fSourceLogicalVolume = nullptr;
  G4ThreeVector fSourceTranslation;
  G4RotationMatrix fSourceRotation;
  G4VPhysicalVolume * fPhysiWorld = nullptr;
  
};

#endif // DetectorConstruction_hh

