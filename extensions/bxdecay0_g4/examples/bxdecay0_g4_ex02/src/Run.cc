/// \file Run.cc
/// \brief Implementation of the Run class

// Ourselves:
#include "Run.hh"

// Geant4:
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4PhysicalConstants.hh"

// BxDecay0 Geant4:
#include <bxdecay0_g4/primary_generator_action.hh>

// This project:
#include "HistoManager.hh"

Run::Run()
  : G4Run()
  , fParticle(nullptr)
  , fEkin(0.)
  , fDecayCount(0)
{
  fEkinTot[0] = 0. ;
  fEkinTot[1] = DBL_MAX;
  fEkinTot[2] = 0. ;
  return;
}


Run::~Run()
{
  return;
}


void Run::SetPrimary(G4ParticleDefinition* particle, G4double energy)
{ 
  fParticle = particle;
  fEkin = energy;
  return;
} 


void Run::ParticleCount(G4String name, G4double Ekin)
{
  std::map<G4String, ParticleData>::iterator it = fParticleDataMap.find(name);
  if (it == fParticleDataMap.end()) {
    fParticleDataMap[name] = ParticleData(1, Ekin, Ekin, Ekin);
  } else {
    ParticleData & data = it->second;
    data.fCount++;
    data.fEmean += Ekin;
    // Update min/max:
    G4double emin = data.fEmin;
    if (Ekin < emin) data.fEmin = Ekin;
    G4double emax = data.fEmax;
    if (Ekin > emax) data.fEmax = Ekin;
  }   
  return;
}

void Run::Merge(const G4Run * run)
{
  const Run * localRun = static_cast<const Run *>(run);
  fParticle = localRun->fParticle;
  fEkin     = localRun->fEkin;
  fDecayCount  += localRun->fDecayCount;
  fEkinTot[0]  += localRun->fEkinTot[0];
  G4double min = localRun->fEkinTot[1];
  G4double max = localRun->fEkinTot[2];
  if (fEkinTot[1] > min) fEkinTot[1] = min;
  if (fEkinTot[2] < max) fEkinTot[2] = max;

  // Maps
  std::map<G4String,ParticleData>::const_iterator itn;
  for (itn = localRun->fParticleDataMap.begin(); 
       itn != localRun->fParticleDataMap.end(); ++itn) {
    
    G4String name = itn->first;
    const ParticleData& localData = itn->second;   
    if ( fParticleDataMap.find(name) == fParticleDataMap.end()) {
      fParticleDataMap[name]
        = ParticleData(localData.fCount, 
                       localData.fEmean, 
                       localData.fEmin, 
                       localData.fEmax);
    } else {
      ParticleData & data = fParticleDataMap[name];   
      data.fCount += localData.fCount;
      data.fEmean += localData.fEmean;
      G4double emin = localData.fEmin;
      if (emin < data.fEmin) data.fEmin = emin;
      G4double emax = localData.fEmax;
      if (emax > data.fEmax) data.fEmax = emax;
    }   
  }
  
  G4Run::Merge(run); 
  return;
} 
    
void Run::EndOfRun() 
{
  G4int nbEvents = numberOfEvent;
  G4String partName = fParticle->GetParticleName();
 
  G4cout << "\n ======================== run summary ======================";  
  G4cout << "\n The run was " << nbEvents << " " << partName << " of "
         << G4BestUnit(fEkin,"Energy");
  G4cout << "\n ===========================================================\n";
  G4cout << G4endl;
  if (nbEvents == 0) { return; }
 
  G4int prec = 4, wid = prec + 2;
  G4int dfprec = G4cout.precision(prec);
      
  // Particle count
  G4cout << " Nb of generated particles: \n" << G4endl;
     
  std::map<G4String,ParticleData>::iterator it;               
  for (it = fParticleDataMap.begin(); it != fParticleDataMap.end(); it++) { 
    G4String name     = it->first;
    ParticleData data = it->second;
    G4int count    = data.fCount;
    G4double eMean = data.fEmean / count;
    G4double eMin  = data.fEmin;
    G4double eMax  = data.fEmax;
         
    G4cout << "  " << std::setw(15) << name << ": " << std::setw(7) << count
           << "  Emean = " << std::setw(wid) << G4BestUnit(eMean, "Energy")
           << "\t( "  << G4BestUnit(eMin, "Energy")
           << " --> " << G4BestUnit(eMax, "Energy") << ")" << G4endl;
  }
  G4cout << G4endl;
                                              
  // Remove all contents in fParticleDataMap
  fParticleDataMap.clear();

  // Restore default precision
  G4cout.precision(dfprec);
  return;
}

