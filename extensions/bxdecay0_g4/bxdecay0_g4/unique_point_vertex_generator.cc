// Ourselves:
#include "bxdecay0_g4/unique_point_vertex_generator.hh"

// This project:
#include "bxdecay0_g4/unique_point_vertex_generator_messenger.hh"

namespace bxdecay0_g4 {

  UniquePointVertexGenerator::UniquePointVertexGenerator()
  {
    _source_position_.set(0.0, 0.0, 0.0);
    _messenger_ = new UniquePointVertexGeneratorMessenger(this);
    return;
  }
    
  UniquePointVertexGenerator::UniquePointVertexGenerator(const G4ThreeVector & source_position_)
    : UniquePointVertexGenerator()
  {
    _source_position_ = source_position_;
    return;
  }
 
  UniquePointVertexGenerator::~UniquePointVertexGenerator()
  {
    if (_messenger_) {
      delete _messenger_;
    }
    return;
  }
    
  void UniquePointVertexGenerator::ShootVertex(G4ThreeVector & vertex_)
  {
    vertex_ = _source_position_;
    return;
  }
   
  const G4ThreeVector & UniquePointVertexGenerator::GetSourcePosition() const
  {
    return _source_position_;
  }

  void UniquePointVertexGenerator::SetSourcePosition(const G4ThreeVector & pos_)
  {
    _source_position_ = pos_;
    return;
  }
 
  void UniquePointVertexGenerator::ResetSourcePosition()
  {
    _source_position_ = G4ThreeVector(0.0, 0.0, 0.0);
    return;
  }
 
} // end of namespace bxdecay0_g4 
