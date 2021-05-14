#ifndef BXDECAY0G4_UNIQUE_POINT_VERTEX_GENERATOR_HH
#define BXDECAY0G4_UNIQUE_POINT_VERTEX_GENERATOR_HH

// Geant4
#include <G4ThreeVector.hh>

// This project:
#include "bxdecay0_g4/vertex_generator_interface.hh"

namespace bxdecay0_g4 {

  class UniquePointVertexGeneratorMessenger;

  /// \brief Non random vertex generator using an unique point-like source:
  class UniquePointVertexGenerator
    : public VertexGeneratorInterface
  {
  public:
    
    UniquePointVertexGenerator();
    
    UniquePointVertexGenerator(const G4ThreeVector & source_position_);
 
    ~UniquePointVertexGenerator() override;
    
    const G4ThreeVector & GetSourcePosition() const;

    void SetSourcePosition(const G4ThreeVector &);
 
    void ResetSourcePosition();

    // From the VertexGeneratorInterface abstract class:
    void ShootVertex(G4ThreeVector & vertex_) override;
   
  private:
    
    G4ThreeVector _source_position_;
    UniquePointVertexGeneratorMessenger * _messenger_ = nullptr;
    
  };
  
} // end of namespace bxdecay0_g4 

#endif // BXDECAY0G4_UNIQUE_POINT_VERTEX_GENERATOR_HH
