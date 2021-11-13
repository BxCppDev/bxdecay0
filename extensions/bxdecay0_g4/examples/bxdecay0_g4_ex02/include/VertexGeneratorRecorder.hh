/// \file VertexGeneratorRecorder.hh
/// \brief Wraper for vertex generator with automatic storage of generated vertexes

#ifndef VertexGeneratorRecorder_hh
#define VertexGeneratorRecorder_hh 1

// Standard library
#include <string>
#include <fstream>
#include <memory>

// BxDecay0/G4:
#include "bxdecay0_g4/vertex_generator_interface.hh"

#include "G4Box.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"

class VertexGeneratorRecorder
  : public bxdecay0_g4::VertexGeneratorInterface
{
public:

  VertexGeneratorRecorder(bxdecay0_g4::VertexGeneratorInterface * vg_,
                          const std::string & outfilename_ = "genvertexes.data");

  ~VertexGeneratorRecorder() override;
 
  /// Check if the generator can provide at least one more vertex 
  bool HasNextVertex() const override;
 
  // From the VertexGeneratorInterface abstract class:
  void ShootVertex(G4ThreeVector & vertex_) override;
    
private:

  // Configuration:
  bxdecay0_g4::VertexGeneratorInterface * fVG = nullptr; ///< Reference to vertex generator
  std::string fOutFilename;

  // Working internals:
  std::unique_ptr<std::ofstream> fFileOut;
     
};

#endif // BoxBulkVertexGenerator_hh 

