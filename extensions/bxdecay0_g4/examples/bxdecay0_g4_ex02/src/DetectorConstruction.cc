/// \file DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class

// Ourselves:
#include "DetectorConstruction.hh"

// Geant4:
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"


DetectorConstruction::DetectorConstruction()
 : G4VUserDetectorConstruction()
{
  PreConstruct(); // Initialize the geometry at construction step
}


DetectorConstruction::~DetectorConstruction()
{
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  return fPhysiWorld;
}

void DetectorConstruction::PreConstruct()
{
  std::clog << "[log] DetectorConstruction::PreConstruct: Entering...\n";
  
  // World:
  fWorldSize = 1000 * CLHEP::mm;
  G4Material * matWorld = G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR"); 
  if (matWorld == nullptr) {
    std::cerr << "[error] DetectorConstruction::Construct: invalid world material!\n"; 
  }
  G4Box * solidWorld = new G4Box("World", fWorldSize/2, fWorldSize/2, fWorldSize/2);              
  G4LogicalVolume * logicWorld = new G4LogicalVolume(solidWorld,             
                                                     matWorld,                   
                                                     "World");              
  fPhysiWorld = new G4PVPlacement(nullptr,                    
                                  G4ThreeVector(),      
                                  logicWorld,             
                                  "World",                
                                  nullptr,                
                                  false,                  
                                  0);                     
 
  // Source:
  fSourceSizeX = 100 * CLHEP::mm;
  fSourceSizeY = 300 * CLHEP::mm;
  fSourceSizeZ =  50 * CLHEP::mm;
  fSourceSolid = new G4Box("Source", fSourceSizeX/2, fSourceSizeY/2, fSourceSizeZ/2);
  std::clog << "[log] DetectorConstruction::Construct: fSourceSolid=" << fSourceSolid << "\n"; 
  G4Material * matSource = G4NistManager::Instance()->FindOrBuildMaterial("G4_Al");
  if (matSource == nullptr) {
    std::cerr << "[error] DetectorConstruction::Construct: invalid source material!\n"; 
  }
  fSourceLogicalVolume = new G4LogicalVolume(fSourceSolid, matSource, "Source");

  // Build translation:
  double sourceTransX = -300.0 * CLHEP::mm;
  double sourceTransY = -150.0 * CLHEP::mm;
  double sourceTransZ =    0.0 * CLHEP::mm;
  fSourceTranslation.set(sourceTransX, sourceTransY, sourceTransZ);
  
  // Build rotation from (ZYZ) Euler angles 
  double sourceRotPhi   = 30.0 * CLHEP::degree; // Longitude [0, 2pi] (precession)
  double sourceRotTheta = 90.0 * CLHEP::degree; // Colatitude [0,pi] (nutation)
  double sourceRotDelta = 45.0 * CLHEP::degree; // Spin [0, 2pi] (intrinsic rotation) 
  CLHEP::HepRotationZ rZ1(-sourceRotPhi);
  CLHEP::HepRotationY rY2(-sourceRotTheta);
  CLHEP::HepRotationZ rZ3(-sourceRotDelta);
  fSourceRotation = rZ3 * rY2 * rZ1;
  G4VPhysicalVolume * physiSource = new G4PVPlacement(&fSourceRotation,
                                                      fSourceTranslation,
                                                      fSourceLogicalVolume,
                                                      "Source",
                                                      logicWorld,
                                                      false,
                                                      0);
  logicWorld->AddDaughter(physiSource);

  // Source hole:
  double sourceHoleSizeX = 20 * CLHEP::mm;
  double sourceHoleSizeY = 40 * CLHEP::mm;
  double sourceHoleSizeZ = fSourceSizeZ/2;
  G4Box * solidSourceHole = new G4Box("SourceHole", sourceHoleSizeX, sourceHoleSizeY, sourceHoleSizeZ);
  double sourceHoleTransX = fSourceSizeX/2 - sourceHoleSizeX - 15 * mm;
  double sourceHoleTransY = fSourceSizeY/2 - sourceHoleSizeY - 15 * mm;
  double sourceHoleTransZ = 0.0 * CLHEP::mm;
  G4LogicalVolume * logicSourceHole = new G4LogicalVolume(solidSourceHole, matWorld, "SourceHole");  
  G4VPhysicalVolume * physiSourceHole =
    new G4PVPlacement(nullptr,
                      G4ThreeVector(sourceHoleTransX, sourceHoleTransY, sourceHoleTransZ),
                      logicSourceHole,
                      "SourceHole",
                      fSourceLogicalVolume,
                      false,
                      0);
  fSourceLogicalVolume->AddDaughter(physiSourceHole);

  return;
}

