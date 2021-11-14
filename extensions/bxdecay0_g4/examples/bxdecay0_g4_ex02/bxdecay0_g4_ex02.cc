//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file bxdecay0_g4_ex02.cc
/// \brief Main program of the bxdecay0_g4_ex02 example

// Geant4:
#include "G4Types.hh"
#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif
#include "G4UImanager.hh"
#include "Randomize.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

// This project:
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"
#include "SteppingVerbose.hh"

int main(int argc, char** argv)
{
  // Detect interactive mode (if no arguments) and define UI session
  G4UIExecutive* ui = 0;
  if (argc == 1) ui = new G4UIExecutive(argc, argv);

  // Choose the Random engine
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);

  // Construct the default run manager
#ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
  runManager->SetNumberOfThreads(std::min(4, G4Threading::G4GetNumberOfCores()));
#else
  // My Verbose output class
  G4VSteppingVerbose::SetInstance(new SteppingVerbose);
  G4RunManager* runManager = new G4RunManager;
#endif

  // Set mandatory initialization classes
  DetectorConstruction * detector = new DetectorConstruction;
  std::clog << "[log] main: detector=" << detector << "\n"; 

  runManager->SetUserInitialization(detector);
  runManager->SetUserInitialization(new PhysicsList);

  ActionInitialization::Config actionInitConfig;
  actionInitConfig.UseLoader = true;
  actionInitConfig.UseRecorder = false;
  actionInitConfig.VertexFilename = "vertexes-xyz.data";
  runManager->SetUserInitialization(new ActionInitialization(detector, actionInitConfig));

  // Initialize G4 kernel
  runManager->Initialize();

  // Initialize visualization
  G4VisManager* visManager = nullptr;

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if (ui) {
    // Interactive mode
    visManager = new G4VisExecutive;
    visManager->Initialize();
    UImanager->ApplyCommand("/control/execute vis.mac");
    ui->SessionStart();
    delete ui;
  } else {
    // Batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command + fileName);
  }

  // Job termination
  delete visManager;
  delete runManager;
  return 0;
}

