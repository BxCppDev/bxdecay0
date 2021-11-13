/// \file BoxBulkVertexGenerator.cc
/// \brief Implementation of the BoxBulkVertexGenerator class

#include "BoxBulkVertexGenerator.hh"

BoxBulkVertexGenerator::BoxBulkVertexGenerator()
{
  fBoxInverseRotation = fBoxRotation.inverse();
}

BoxBulkVertexGenerator::~BoxBulkVertexGenerator()
{
  std::clog << "[log] BoxBulkVertexGenerator::DTOR: counter=" << fCounter << " generated vertexes\n";
}
 
const G4LogicalVolume * BoxBulkVertexGenerator::GetBoxLogicalVolume() const
{
  return fLogVol;
}
  
void BoxBulkVertexGenerator::SetBoxLogicalVolume(const G4LogicalVolume * logvol_)
{
  G4VSolid * solid = logvol_->GetSolid();
  G4Box * box = dynamic_cast<G4Box *>(solid);
  if (box == nullptr) {
    throw std::logic_error("Logical volume '" + logvol_->GetName() + "' has no box solid!"); 
  }
  fLogVol = logvol_;
  fBox = box;
  std::clog << "[log] BoxBulkVertexGenerator::SetBoxLogicalVolume: box=" << fBox << "\n";
}

const G4Box * BoxBulkVertexGenerator::GetBox() const
{
  return fBox;
}

const G4ThreeVector & BoxBulkVertexGenerator::GetBoxTranslation() const
{
  return fBoxTranslation;
}

void BoxBulkVertexGenerator::SetBoxTranslation(const G4ThreeVector & translation_)
{
  fBoxTranslation = translation_;
  std::clog << "[log] BoxBulkVertexGenerator::SetBoxTranslation: translation=" << (fBoxTranslation / CLHEP::mm) << " mm\n";
}

const G4RotationMatrix & BoxBulkVertexGenerator::GetBoxRotation() const
{
  return fBoxRotation;
}

const G4RotationMatrix & BoxBulkVertexGenerator::GetBoxInverseRotation() const
{
  return fBoxInverseRotation;
}
  
void BoxBulkVertexGenerator::SetBoxRotation(const G4RotationMatrix & rotation_)
{
  fBoxRotation = rotation_;
  fBoxInverseRotation = fBoxRotation.inverse();
  std::clog << "[log] BoxBulkVertexGenerator::SetBoxRotation: rotation=" << fBoxRotation << "\n";
}

double BoxBulkVertexGenerator::GetTolerance() const
{
  return fTolerance;
}
  
void BoxBulkVertexGenerator::SetTolerance(double tolerance_)
{
  if (tolerance_ <= 0.0) {
    throw std::range_error("BoxBulkVertexGenerator::SetTolerance: invalid tolerance!");
  }
  fTolerance = tolerance_;  
  std::clog << "[log] BoxBulkVertexGenerator::SetBoxRotation: tolerance=" << fTolerance / CLHEP::mm << " mm\n";
}

void BoxBulkVertexGenerator::SetRandomSeed(unsigned int seed_)
{
  fRandomSeed = seed_;
  fGenerator = std::default_random_engine(fRandomSeed);
  std::clog << "[log] BoxBulkVertexGenerator::SetRandomSeed: seed=" << fRandomSeed << " after " << fCounter << " generated vertexes\n";
}

void BoxBulkVertexGenerator::SetNoDaughters(bool no_daughters_)
{
  fNoDaughters = no_daughters_;
}
 
void BoxBulkVertexGenerator::ShootVertex(G4ThreeVector & vertex_)
{
  double hx = fBox->GetXHalfLength() - fTolerance;
  double hy = fBox->GetYHalfLength() - fTolerance;
  double hz = fBox->GetZHalfLength() - fTolerance;
  double x, y, z;
  G4ThreeVector localVertex;
  while (true) {
    x = hx * (-1.0 + 2.0 * fUniformDeviates(fGenerator));
    y = hy * (-1.0 + 2.0 * fUniformDeviates(fGenerator));
    z = hz * (-1.0 + 2.0 * fUniformDeviates(fGenerator));
    localVertex.set(x, y, z);
    bool reject = false;
    if (fNoDaughters) {
      for (unsigned int i = 0; i < fLogVol->GetNoDaughters(); i++) {
        const G4VPhysicalVolume * daughterPhys = fLogVol->GetDaughter(i);
        // std::cerr << "[debug] daughterPhys  = " << daughterPhys << "\n";
        const G4ThreeVector & daughterTrans = daughterPhys->GetTranslation();
        // std::cerr << "[debug] daughterTrans  = " << daughterTrans << "\n";
        const G4RotationMatrix * daughterRotation = daughterPhys->GetRotation();
        // std::cerr << "[debug] daughterRotation  = " << daughterRotation << "\n";
        const G4VSolid * daughterSolid = daughterPhys->GetLogicalVolume()->GetSolid();
        G4ThreeVector daughterVertex;
        if (daughterRotation != nullptr) {
          daughterVertex = (*daughterRotation)(localVertex - daughterTrans);
        } else {
          daughterVertex = localVertex - daughterTrans;
        }
        // std::cerr << "[debug] daughterSolid  = " << daughterSolid << "\n";
        // std::cerr << "[debug] daughterVertex = " << daughterVertex << "\n";
        if (daughterSolid->Inside(daughterVertex) == kInside) {
          reject = true;
          break;
        }
      }
    }
    if (not reject) break;
  }
  vertex_ = fBoxInverseRotation(localVertex) + fBoxTranslation;
  fCounter++;
}
