/// \file Run.hh
/// \brief Definition of the Run class

#ifndef Run_hh
#define Run_hh 1

// Standard library:
#include <map>

// Geant4:
#include "G4Run.hh"
#include "G4VProcess.hh"
#include "globals.hh"

class G4ParticleDefinition;

class Run
  : public G4Run
{
public:
  
  Run();

  ~Run() override;

public:

  void ParticleCount(G4String name, G4double Ekin);
  void SetPrimary(G4ParticleDefinition * particle, G4double energy);
  void EndOfRun(); 
  void Merge(const G4Run *) override;

private:    

  struct ParticleData
  {
    ParticleData()
      : fCount(0)
      , fEmean(0.)
      , fEmin(0.)
      , fEmax(0.)
    {
      return;
    }
    
    ParticleData(G4int count, G4double ekin, G4double emin, G4double emax)
      : fCount(count)
      , fEmean(ekin)
      , fEmin(emin)
      , fEmax(emax)
    {
      return;
    }
    
    G4int     fCount;
    G4double  fEmean;
    G4double  fEmin;
    G4double  fEmax;
  
  };
     
private:
  
  G4ParticleDefinition * fParticle = nullptr;
  G4double  fEkin;           
  std::map<G4String,ParticleData>  fParticleDataMap;    
  G4int    fDecayCount;
  G4double fEkinTot[3];

};

#endif // Run_hh

