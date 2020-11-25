/// \file HistoManager.hh
/// \brief Definition of the HistoManager class

#ifndef HistoManager_hh
#define HistoManager_hh 1

// Geant4:
#include "globals.hh"
#include "g4root.hh"
//#include "g4xml.hh"
//#include "g4csv.hh"

class HistoManager
{
public:
  
  HistoManager();
  
  ~HistoManager();

private:
  
  void Book();

private:
  
  G4String fFileName;
  
};

#endif // HistoManager_hh

