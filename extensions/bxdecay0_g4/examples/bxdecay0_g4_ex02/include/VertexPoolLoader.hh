/// \file VertexPoolLoader.hh
/// \brief Wraper for vertex generator with automatic loading of generated vertexes stored in a file

#ifndef VertexPoolLoader_hh
#define VertexPoolLoader_hh 1

// Standard library
#include <string>
#include <fstream>
#include <memory>

// BxDecay0/G4:
#include "bxdecay0_g4/vertex_generator_interface.hh"

#include "G4Box.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"

/// \brief A class with behaves like a vertex generator but
///        practically reads vertex coordinates from a file
///        (generated by the VertexGeneratorRecorder wrapper class)
class VertexPoolLoader
  : public bxdecay0_g4::VertexGeneratorInterface
{
public:

  VertexPoolLoader(const std::string & infilename_ = "genvertexes.data");

  ~VertexPoolLoader() override;
 
  /// Check if the generator can provide at least one more vertex 
  bool HasNextVertex() const override;
 
  // From the VertexGeneratorInterface abstract class:
  void ShootVertex(G4ThreeVector & vertex_) override;
    
private:
 
  void LoadNextVertex();

  // Configuration:
  std::string fInFilename; ///< Vetex file name

  // Working internals:
  std::unique_ptr<std::ifstream> fFileIn; ///< Input file
  unsigned int fCounter = 0;
  G4ThreeVector fNextVertex; ///< Preloaded vertex 
     
};

#endif // VertexPoolLoader_hh 

