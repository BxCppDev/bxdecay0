/// \file SteppingVerbose.hh
/// \brief Definition of the SteppingVerbose class

#ifndef SteppingVerbose_hh
#define SteppingVerbose_hh 1

// Geant4:
#include "G4SteppingVerbose.hh"

class SteppingVerbose
  : public G4SteppingVerbose
{

public:   

  SteppingVerbose();

  ~SteppingVerbose() override;
 
  void TrackingStarted() override;

  void StepInfo() override;
  
};

#endif // SteppingVerbose_hh
