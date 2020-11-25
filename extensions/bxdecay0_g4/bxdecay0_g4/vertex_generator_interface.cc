// Ourselves
#include "bxdecay0_g4/vertex_generator_interface.hh"

namespace bxdecay0_g4 {

  UniquePointVertexGenerator::UniquePointVertexGenerator()
  {
    _source_position_.set(0.0, 0.0, 0.0);
    return;
  }
    
  UniquePointVertexGenerator::UniquePointVertexGenerator(const G4ThreeVector & source_position_)
  {
    _source_position_ = source_position_;
    return;
  }
 
  UniquePointVertexGenerator::~UniquePointVertexGenerator()
  {
    return;
  }
 
  bool UniquePointVertexGenerator::HasNextVertex() const
  {
    return true;
  }
   
  void UniquePointVertexGenerator::ShootVertex(G4ThreeVector & vertex_)
  {
    vertex_ = _source_position_;
    return;
  }
  
} // end of namespace bxdecay0_g4 
