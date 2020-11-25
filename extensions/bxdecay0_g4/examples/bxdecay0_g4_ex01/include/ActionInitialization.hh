/// \file ActionInitialization.hh
/// \brief Definition of the ActionInitialization class

#ifndef ActionInitialization_hh
#define ActionInitialization_hh 1

#include "G4VUserActionInitialization.hh"

class G4VSteppingVerbose;

/// Action initialization class.
///

class ActionInitialization
  : public G4VUserActionInitialization
{
public:

  ActionInitialization();

  ~ActionInitialization() override;
  
  void BuildForMaster() const override;
  
  void Build() const override;
  
  G4VSteppingVerbose* InitializeSteppingVerbose() const override;
  
};

#endif // ActionInitialization_hh 

    
