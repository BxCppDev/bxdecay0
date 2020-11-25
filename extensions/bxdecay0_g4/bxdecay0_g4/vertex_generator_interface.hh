#ifndef BXDECAY0G4_VERTEX_GENERATOR_INTERFACE_HH
#define BXDECAY0G4_VERTEX_GENERATOR_INTERFACE_HH

// Geant4
#include <G4ThreeVector.hh>

namespace bxdecay0_g4 {

  /// \brief Vertex generator interface:
  struct VertexGeneratorInterface
  {
    
    VertexGeneratorInterface() = default;

    virtual ~VertexGeneratorInterface() = default;

    /// Check if the generator can provide at least one more vertex
    virtual bool HasNextVertex() const = 0;

    /// Randomize/set one more vertex
    virtual void ShootVertex(G4ThreeVector & vertex_) = 0;
    
  };

  /// \brief Non random vertex generator using an unique point-like source:
  class UniquePointVertexGenerator
    : public VertexGeneratorInterface
  {
  public:
    
    UniquePointVertexGenerator();
    
    UniquePointVertexGenerator(const G4ThreeVector & source_position_);
 
    ~UniquePointVertexGenerator() override;
 
    bool HasNextVertex() const override;
    
    void ShootVertex(G4ThreeVector & vertex_) override;
   
  private:
    
    G4ThreeVector _source_position_;

  };
  
} // end of namespace bxdecay0_g4 

#endif // BXDECAY0G4_PRIMARY_GENERATOR_ACTION_HH
