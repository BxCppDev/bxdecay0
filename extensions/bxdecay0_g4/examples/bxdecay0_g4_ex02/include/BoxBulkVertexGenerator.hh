/// \file BoxBulkVertexGenerator.hh
/// \brief Vertex generator from the volume of a 3D-box (uniform sampling)

#ifndef BoxBulkVertexGenerator_hh
#define BoxBulkVertexGenerator_hh 1

// Standard library
#include <random>

// BxDecay0/G4:
#include "bxdecay0_g4/vertex_generator_interface.hh"

#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"

class BoxBulkVertexGenerator
  : public bxdecay0_g4::VertexGeneratorInterface
{
public:

  BoxBulkVertexGenerator();

  ~BoxBulkVertexGenerator() override;
  
  const G4LogicalVolume * GetBoxLogicalVolume() const;
  
  void SetBoxLogicalVolume(const G4LogicalVolume *);
   
  const G4Box * GetBox() const;
 
  const G4ThreeVector & GetBoxTranslation() const;
  
  void SetBoxTranslation(const G4ThreeVector &);
 
  const G4RotationMatrix & GetBoxRotation() const;
 
  const G4RotationMatrix & GetBoxInverseRotation() const;
  
  void SetBoxRotation(const G4RotationMatrix &);
 
  double GetTolerance() const;
  
  void SetTolerance(double tolerance_);

  void SetRandomSeed(unsigned int seed_);

  void SetNoDaughters(bool no_daughters_);

  // From the VertexGeneratorInterface abstract class:
  void ShootVertex(G4ThreeVector & vertex_) override;
    
private:

  // Configuration:
  const G4LogicalVolume * fLogVol = nullptr; ///< Reference to the logical volume
  G4ThreeVector fBoxTranslation; ///< The box position in world coordinate frame
  G4RotationMatrix fBoxRotation; ///< The box rotation in world coordinate frame
  double fTolerance{1.0 * CLHEP::um}; ///< Geometrical tolerance (length)
  unsigned int fRandomSeed{0}; ///< Seed for the random number generator
  bool fNoDaughters = false; ///< Flag to reject vertexes generated from daughter volumes
  
  // Working internals:
  const G4Box * fBox = nullptr; ///< Reference to the box from which are generated vertexes
  G4RotationMatrix fBoxInverseRotation; ///< The inverse box rotation
  std::default_random_engine fGenerator{0}; // Private embedded random engine
  std::uniform_real_distribution<double> fUniformDeviates{0.0, 1.0}; // Uniform distribution
  unsigned int fCounter = 0.0; // Internal vertex counter
     
};

#endif // BoxBulkVertexGenerator_hh 

