/// \file RunAction.hh
/// \brief Definition of the RunAction class

#ifndef RunAction_hh
#define RunAction_hh 1

// Geant4
#include "G4UserRunAction.hh"
#include "globals.hh"

class Run;
class HistoManager;

namespace bxdecay0_g4 {
  class PrimaryGeneratorAction;
}

class RunAction
  : public G4UserRunAction
{
public:
  
  RunAction(bxdecay0_g4::PrimaryGeneratorAction *);

  ~RunAction() override;

  G4Run * GenerateRun() override;   

  void BeginOfRunAction(const G4Run *) override;

  void EndOfRunAction(const G4Run *) override;
    
private:

  bxdecay0_g4::PrimaryGeneratorAction * fPrimary = nullptr;
  Run *                    fRun = nullptr;
  HistoManager *           fHistoManager = nullptr;    

};

#endif // RunAction_hh

