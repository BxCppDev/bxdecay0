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

/// \brief A class which wraps a vertex generator class.
///        It randomizes vertexes using the undrlying vertex generator
///        but also stores the coordinates of the vertex generator
///        in a file using a simple ASCII format.
class VertexGeneratorRecorder
  : public bxdecay0_g4::VertexGeneratorInterface
{
public:

  VertexGeneratorRecorder(std::shared_ptr<bxdecay0_g4::VertexGeneratorInterface> vg_,
                          const std::string & outfilename_ = "genvertexes.data");

  ~VertexGeneratorRecorder() override;
 
  /// Check if the generator can provide at least one more vertex 
  bool HasNextVertex() const override;
 
  // From the VertexGeneratorInterface abstract class:
  void ShootVertex(G4ThreeVector & vertex_) override;
    
private:

  // Configuration:
  std::shared_ptr<bxdecay0_g4::VertexGeneratorInterface> fVG; ///< Reference to vertex generator
  std::string fOutFilename;

  // Working internals:
  std::unique_ptr<std::ofstream> fFileOut;
     
};

#endif // VertexGeneratorRecorder_hh 

