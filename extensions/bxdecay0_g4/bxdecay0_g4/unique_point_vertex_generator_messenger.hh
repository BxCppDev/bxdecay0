#ifndef BXDECAY0G4_UNIQUE_POINT_VERTEX_GENERATOR_MESSENGER_HH
#define BXDECAY0G4_UNIQUE_POINT_VERTEX_GENERATOR_MESSENGER_HH

// Standard library:
#include <memory>

// Geant4
#include <G4UImessenger.hh>
//#include <globals.hh>

class G4UIcmdWithABool;
class G4UIcommand;

// This project:
#include <bxdecay0_g4/unique_point_vertex_generator.hh>

namespace bxdecay0_g4 {

  /// \brief BxDecay0 Geant4 unique point vertex generator messenger
  class UniquePointVertexGeneratorMessenger
    : public G4UImessenger
  {
  public:
   
    UniquePointVertexGeneratorMessenger(UniquePointVertexGenerator * );

    ~UniquePointVertexGeneratorMessenger() override;

    G4String GetCurrentValue (G4UIcommand * command_) override;
    
    void SetNewValue(G4UIcommand *, G4String) override;
    
  private:

    UniquePointVertexGenerator * _upvg_ = nullptr;    
    G4UIdirectory *              _upvg_directory_ = nullptr;
    G4UIcommand *                _upvg_vertex_cmd_ = nullptr;

  };
  
} // end of namespace bxdecay0_g4 

#endif // BXDECAY0G4_UNIQUE_POINT_VERTEX_GENERATOR_MESSENGER_HH
