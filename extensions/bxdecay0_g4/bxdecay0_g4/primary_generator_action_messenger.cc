// Ourselves:
#include "bxdecay0_g4/primary_generator_action_messenger.hh"

// Standard library:
#include <string>
#include <sstream>

// BxDecay0:
#include <bxdecay0/decay0_generator.h>
#include <bxdecay0/bb_utils.h>

// Geant4:
#include <G4Tokenizer.hh>
#include <G4UIcommand.hh>

namespace bxdecay0_g4 {

  PrimaryGeneratorActionMessenger::PrimaryGeneratorActionMessenger(PrimaryGeneratorAction * pga_)
    : G4UImessenger()
  {
    _pga_ = pga_;

    // Directory /bxdecay0/
    _pga_directory_ = new G4UIdirectory("/bxdecay0/");
    _pga_directory_->SetGuidance(" BxDecay0 commands.");

    // Directory /bxdecay0/generator/
    _pga_gtor_directory_ = new G4UIdirectory("/bxdecay0/generator/");
    _pga_gtor_directory_->SetGuidance(" BxDecay0 generator commands.");

    {
      // Command /particle/generator/verbosity
      _pga_gtor_log_cmd_ = new G4UIcommand("/bxdecay0/generator/verbosity", this);
      _pga_gtor_log_cmd_->SetGuidance("Set the BxDecay0 event generator verbosity");
      _pga_gtor_log_cmd_->SetGuidance("[usage] /bxdecay0/generator/verbosity LEVEL");
      _pga_gtor_log_cmd_->SetGuidance("  LEVEL: (int) The verbosity level (0:mute, 1:info, 2:debug, 3:trace");

      {
        // Verbosity parameter: 
        G4UIparameter * levelParam = new G4UIparameter("level", 'i', false);
        levelParam->SetGuidance("verbosity level of the BxDecay0 primary event generator driver ");
        levelParam->SetParameterRange("level>=0");
        _pga_gtor_log_cmd_->SetParameter(levelParam);
      }

    }
    
    {
      // Command /particle/generator/background
      _pga_gtor_bkgd_cmd_ = new G4UIcommand("/bxdecay0/generator/background", this);
      _pga_gtor_bkgd_cmd_->SetGuidance("Set the BxDecay0 event generator parameters for background decays");
      _pga_gtor_bkgd_cmd_->SetGuidance("[usage] /bxdecay0/generator/background NUCLIDE SEED [DEBUG]");
      _pga_gtor_bkgd_cmd_->SetGuidance("  NUCLIDE: (string) Decaying nuclide");
      _pga_gtor_bkgd_cmd_->SetGuidance("  SEED: (int) Random numbers generator's seed");
      _pga_gtor_bkgd_cmd_->SetGuidance("  DEBUG: (bool) Debug flag");

      {
        // Nuclide parameter: 
        G4UIparameter * nuclideParam = new G4UIparameter("nuclide", 's', false);
        nuclideParam->SetGuidance("the BxDecay0 decaying nuclide");
        _pga_gtor_bkgd_cmd_->SetParameter(nuclideParam);
      }

      {
        // Seed parameter: 
        G4UIparameter * seedParam = new G4UIparameter("seed", 'i', false);
        seedParam->SetGuidance("seed for the BxDecay0 pseudo-random number generator");
        seedParam->SetParameterRange("seed>=0");
        _pga_gtor_bkgd_cmd_->SetParameter(seedParam);
      }
      
      {
        // Debug parameter: 
        G4UIparameter * debugParam = new G4UIparameter("debug", 'b', true);
        debugParam->SetGuidance("debug flag");
        debugParam->SetDefaultValue("false");
        _pga_gtor_bkgd_cmd_->SetParameter(debugParam);
      }
 
    }

    {
      // Command /particle/generator/dbd
      _pga_gtor_dbd_cmd_ = new G4UIcommand("/bxdecay0/generator/dbd", this);
      _pga_gtor_dbd_cmd_->SetGuidance("Set the BxDecay0 event generator parameters for DBD decays");
      _pga_gtor_dbd_cmd_->SetGuidance("[usage] /bxdecay0/generator/dbd NUCLIDE SEED DBD_MODE DBD_LEVEL [DEBUG]");
      _pga_gtor_dbd_cmd_->SetGuidance("  NUCLIDE: (string) Decaying nuclide");
      _pga_gtor_dbd_cmd_->SetGuidance("  SEED: (int) Random numbers generator's seed");
      _pga_gtor_dbd_cmd_->SetGuidance("  DBD_MODE: (int) Double beta decay mode");
      _pga_gtor_dbd_cmd_->SetGuidance("  DBD_LEVEL: (int) Double beta decay daughter level");
      _pga_gtor_dbd_cmd_->SetGuidance("  DEBUG: (bool) Debug flag");

      {
        // Nuclide parameter: 
        G4UIparameter * nuclideParam = new G4UIparameter("nuclide", 's', false);
        nuclideParam->SetGuidance("the BxDecay0 decaying nuclide");
        _pga_gtor_dbd_cmd_->SetParameter(nuclideParam);
      }

      {
        // Seed parameter: 
        G4UIparameter * seedParam = new G4UIparameter("seed", 'i', false);
        seedParam->SetGuidance("seed for the BxDecay0 pseudo-random number generator");
        seedParam->SetParameterRange("seed>=0");
        _pga_gtor_dbd_cmd_->SetParameter(seedParam);
      }

      {
        // DBD mode parameter: 
        G4UIparameter * dbdModeParam = new G4UIparameter("dbd_mode", 'i', false);
        std::ostringstream ssguidance;
        ssguidance << "the BxDecay0 double beta decay mode (supported values: ["
                   << bxdecay0::DBDMODE_MIN << ',' << bxdecay0::DBDMODE_MAX << "])";
        dbdModeParam->SetGuidance(ssguidance.str().c_str());
        // dbdModeParam->SetDefaultValue(bxdecay0::DBDMODE_MIN);
        std::ostringstream ssrange;
        ssrange << "dbd_mode>=" << bxdecay0::DBDMODE_MIN;
        dbdModeParam->SetParameterRange(ssrange.str().c_str());
        _pga_gtor_dbd_cmd_->SetParameter(dbdModeParam);
      }

      {
        // Level parameter: 
        G4UIparameter * levelParam = new G4UIparameter("dbd_level", 'i', false);
        levelParam->SetGuidance("the DBD daughter nuclide level (supported values: >=0, default value: 0 = ground state)");
        // levelParam->SetDefaultValue(0);
        levelParam->SetParameterRange("dbd_level>=0");
        _pga_gtor_dbd_cmd_->SetParameter(levelParam);
      }
       
      {
        // Debug parameter: 
        G4UIparameter * debugParam = new G4UIparameter("debug", 'b', true);
        debugParam->SetGuidance("debug flag");
        debugParam->SetDefaultValue("false");
        _pga_gtor_dbd_cmd_->SetParameter(debugParam);
      }
 
    }

    {
      // Command /particle/generator/dbdranged
      _pga_gtor_dbdr_cmd_ = new G4UIcommand("/bxdecay0/generator/dbdranged", this);
      _pga_gtor_dbdr_cmd_->SetGuidance("Set the BxDecay0 event generator parameters for DBD decays");
      _pga_gtor_dbdr_cmd_->SetGuidance("[usage] /bxdecay0/generator/dbd NUCLIDE SEED DBD_MODE DBD_LEVEL DBD_MIN_ENERGY DBD_MAX_ENERGY[DEBUG]");
      _pga_gtor_dbdr_cmd_->SetGuidance("  NUCLIDE: (string) Decaying nuclide");
      _pga_gtor_dbdr_cmd_->SetGuidance("  SEED: (int) Random numbers generator's seed");
      _pga_gtor_dbdr_cmd_->SetGuidance("  DBD_MODE: (int) Double beta decay mode");
      _pga_gtor_dbdr_cmd_->SetGuidance("  DBD_LEVEL: (int) Double beta decay daughter level");
      _pga_gtor_dbdr_cmd_->SetGuidance("  DBD_MIN_ENERGY: (double) Double beta decay minimal sum energy (MeV)");
      _pga_gtor_dbdr_cmd_->SetGuidance("  DBD_MAX_ENERGY: (double) Double beta decay maximal sum energy (MeV)");
      _pga_gtor_dbdr_cmd_->SetGuidance("  DEBUG: (bool) Debug flag");

      {
        // Nuclide parameter: 
        G4UIparameter * nuclideParam = new G4UIparameter("nuclide", 's', false);
        nuclideParam->SetGuidance("the BxDecay0 decaying nuclide");
        _pga_gtor_dbdr_cmd_->SetParameter(nuclideParam);
      }

      {
        // Seed parameter: 
        G4UIparameter * seedParam = new G4UIparameter("seed", 'i', false);
        seedParam->SetGuidance("seed for the BxDecay0 pseudo-random number generator");
        seedParam->SetParameterRange("seed>=0");
        _pga_gtor_dbdr_cmd_->SetParameter(seedParam);
      }

      {
        // DBD mode parameter: 
        G4UIparameter * dbdModeParam = new G4UIparameter("dbd_mode", 'i', false);
        std::ostringstream ssguidance;
        ssguidance << "the BxDecay0 double beta decay mode (supported values: ["
                   << bxdecay0::DBDMODE_MIN << ',' << bxdecay0::DBDMODE_MAX << "])";
        dbdModeParam->SetGuidance(ssguidance.str().c_str());
        // dbdModeParam->SetDefaultValue(bxdecay0::DBDMODE_MIN);
        std::ostringstream ssrange;
        ssrange << "dbd_mode>=" << bxdecay0::DBDMODE_MIN;
        dbdModeParam->SetParameterRange(ssrange.str().c_str());
        _pga_gtor_dbdr_cmd_->SetParameter(dbdModeParam);
      }

      {
        // Level parameter: 
        G4UIparameter * levelParam = new G4UIparameter("dbd_level", 'i', false);
        levelParam->SetGuidance("the DBD daughter nuclide level (supported values: >=0, default value: 0 = ground state)");
        // levelParam->SetDefaultValue(0);
        levelParam->SetParameterRange("dbd_level>=0");
        _pga_gtor_dbdr_cmd_->SetParameter(levelParam);
      }

      {
        // DBD min sum energy parameter: 
        G4UIparameter * dbdMinSumEnergyParam = new G4UIparameter("dbd_min_energy", 'd', false);
        dbdMinSumEnergyParam->SetGuidance("the BxDecay0 double beta decay minimum sum energy (>0.0, in MeV)");
        dbdMinSumEnergyParam->SetParameterRange("dbd_min_energy==-1.0 || dbd_min_energy>=0.0");
        _pga_gtor_dbdr_cmd_->SetParameter(dbdMinSumEnergyParam);
      }

      {
        // DBD max sum energy parameter: 
        G4UIparameter * dbdMaxSumEnergyParam = new G4UIparameter("dbd_max_energy", 'd', true);
        dbdMaxSumEnergyParam->SetGuidance("the BxDecay0 double beta decay maximum sum energy (>0.0, in MeV)");
        dbdMaxSumEnergyParam->SetDefaultValue(-1.0);
        dbdMaxSumEnergyParam->SetParameterRange("dbd_max_energy==-1.0 || dbd_max_energy>0.0");
        _pga_gtor_dbdr_cmd_->SetParameter(dbdMaxSumEnergyParam);
      }
          
      {
        // Debug parameter: 
        G4UIparameter * debugParam = new G4UIparameter("debug", 'b', true);
        debugParam->SetGuidance("debug flag");
        debugParam->SetDefaultValue("false");
        _pga_gtor_dbdr_cmd_->SetParameter(debugParam);
      }
 
    }
  
    _pga_gtor_log_cmd_->AvailableForStates(G4State_PreInit, G4State_Idle);
    _pga_gtor_bkgd_cmd_->AvailableForStates(G4State_PreInit, G4State_Idle);
    _pga_gtor_dbd_cmd_->AvailableForStates(G4State_PreInit, G4State_Idle);
    _pga_gtor_dbdr_cmd_->AvailableForStates(G4State_PreInit, G4State_Idle);
    
    return;
  }

  PrimaryGeneratorActionMessenger::~PrimaryGeneratorActionMessenger()
  {
    delete _pga_gtor_dbdr_cmd_;
    delete _pga_gtor_dbd_cmd_;
    delete _pga_gtor_bkgd_cmd_;
    delete _pga_gtor_log_cmd_;
    delete _pga_gtor_directory_;
    delete _pga_directory_;
    return;
  }

  G4String PrimaryGeneratorActionMessenger::GetCurrentValue(G4UIcommand * command_)
  {
    std::cerr << "[trace] bxdecay0_g4::PrimaryGeneratorActionMessenger::GetCurrentValue: Entering...\n";
    G4String curValue;
    if (command_ == _pga_gtor_log_cmd_) {
      std::ostringstream sCurValue;
      sCurValue << _pga_->GetVerbosity();
      curValue = sCurValue.str();
    }
    if (command_ == _pga_gtor_bkgd_cmd_) {
      PrimaryGeneratorAction::ConfigurationInterface configInt = _pga_->GetConfiguration();
      std::ostringstream sCurValue;
      sCurValue << configInt.nuclide << ' ';
      sCurValue << configInt.seed << ' ';
      sCurValue << configInt.debug;
      curValue = sCurValue.str();
    }
    if (command_ == _pga_gtor_dbd_cmd_) {
      PrimaryGeneratorAction::ConfigurationInterface configInt = _pga_->GetConfiguration();
      std::ostringstream sCurValue;
      sCurValue << configInt.nuclide << ' ';
      sCurValue << configInt.seed << ' ';
      sCurValue << configInt.dbd_mode << ' ';
      sCurValue << configInt.dbd_level << ' ';
      sCurValue << -1.0 << ' ';
      sCurValue << -1.0 << ' ';
      sCurValue << configInt.debug;
      curValue = sCurValue.str();
    }
    if (command_ == _pga_gtor_dbdr_cmd_) {
      PrimaryGeneratorAction::ConfigurationInterface configInt = _pga_->GetConfiguration();
      std::ostringstream sCurValue;
      sCurValue << "dbd" << ' ';
      sCurValue << configInt.nuclide << ' ';
      sCurValue << configInt.seed << ' ';
      sCurValue << configInt.dbd_mode << ' ';
      sCurValue << configInt.dbd_level << ' ';
      sCurValue << configInt.dbd_min_energy_MeV << ' ';
      sCurValue << configInt.dbd_max_energy_MeV << ' ';
      sCurValue << configInt.debug;
      curValue = sCurValue.str();
    }
    std::cerr << "[log] bxdecay0_g4::PrimaryGeneratorActionMessenger::GetCurrentValue: curValue='" << curValue << "'\n";
    return curValue;
  }
    
  void PrimaryGeneratorActionMessenger::SetNewValue(G4UIcommand * command_, G4String new_value_)
  {
    if (_pga_->IsTrace()) std::cerr << "[trace] bxdecay0_g4::PrimaryGeneratorActionMessenger::SetNewValue: Entering...\n";
    if (_pga_->IsDebug()) std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorActionMessenger::SetNewValue: "
                                    << "new_value='" << new_value_ << "'\n";

    if (command_ == _pga_gtor_log_cmd_) {
      G4int   level = 0;             // 0
      G4Tokenizer next(new_value_);
      level = StoI(next());
      _pga_->SetVerbosity(level);  
    }
    
    if (command_ == _pga_gtor_bkgd_cmd_) {
      // Temporary parsing variables:
      G4String nuclide;               // 0
      G4int    seed = -1;             // 1
      G4bool   debug = false;         // 2
    
      G4Tokenizer next(new_value_);
      nuclide = next();
      seed = StoI(next());
      G4String sD = next();
      if (! sD.isNull()) {
        debug = G4UIcommand::ConvertToBool(sD.data());
      }
      // Default config:
      PrimaryGeneratorAction::ConfigurationInterface configInt;
      configInt.decay_category = "background";
      configInt.nuclide = nuclide;
      configInt.seed = seed;
      configInt.debug = debug;
      if (_pga_->IsDebug()) {
        std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorActionMessenger::SetNewValue: "
                  << "Command 'background' -> Action->SetConfiguration...\n";
        configInt.print(std::cerr);
      }
      _pga_->SetConfiguration(configInt);      
    }

    if (command_ == _pga_gtor_dbd_cmd_) {
      // Temporary parsing variables:
      G4String nuclide;               // 0
      G4int    seed = -1;             // 1
      G4int    dbd_mode = -1;         // 2
      G4int    dbd_level = -1;        // 3
      G4bool   debug = false;         // 4
    
      G4Tokenizer next(new_value_);
      nuclide = next();
      seed = StoI(next());
      dbd_mode = StoI(next());
      dbd_level = StoI(next());
      G4String sD = next();
      if (! sD.isNull()) {
        debug = G4UIcommand::ConvertToBool(sD.data());
      }
      // Default config:
      PrimaryGeneratorAction::ConfigurationInterface configInt;
      configInt.decay_category = "dbd";
      configInt.nuclide = nuclide;
      configInt.seed = seed;
      configInt.dbd_mode = dbd_mode;
      configInt.dbd_level = dbd_level;
      configInt.debug = debug;
      if (_pga_->IsDebug()) std::cerr << "[log] bxdecay0_g4::PrimaryGeneratorActionMessenger::SetNewValue: "
                << "Command 'dbd' -> Action->SetConfiguration...\n";
      configInt.print(std::cerr);
      _pga_->SetConfiguration(configInt);      
    }

    if (command_ == _pga_gtor_dbdr_cmd_) {
      // Temporary parsing variables:
      G4String nuclide;               // 0
      G4int    seed = -1;             // 1
      G4int    dbd_mode = -1;         // 2
      G4int    dbd_level = -1;        // 3
      G4double dbd_min_energy = -1.0; // 4
      G4double dbd_max_energy = -1.0; // 5
      G4bool   debug = false;         // 6
    
      G4Tokenizer next(new_value_);
      nuclide = next();
      seed = StoI(next());
      dbd_mode = StoI(next());
      dbd_level = StoI(next());
      dbd_min_energy = StoD(next());
      G4String sMaxEnergy = next();
      if (! sMaxEnergy.isNull()) {
        dbd_max_energy = StoD(sMaxEnergy);
        G4String sD = next();
        if (! sD.isNull()) {
          debug = G4UIcommand::ConvertToBool(sD.data());
        }
      }
      // Default config:
      PrimaryGeneratorAction::ConfigurationInterface configInt;
      configInt.decay_category = "dbd";
      configInt.nuclide = nuclide;
      configInt.seed = seed;
      configInt.dbd_mode = dbd_mode;
      configInt.dbd_level = dbd_level;
      configInt.dbd_min_energy_MeV = dbd_min_energy;
      configInt.dbd_max_energy_MeV = dbd_max_energy;
      configInt.debug = debug;
      if (_pga_->IsDebug()) std::cerr << "[log] bxdecay0_g4::PrimaryGeneratorActionMessenger::SetNewValue: "
                << "Command 'dbdrange' -> Action->SetConfiguration...\n";
      configInt.print(std::cerr);
      _pga_->SetConfiguration(configInt);      
    }

    if (_pga_->IsTrace()) std::cerr << "[trace] bxdecay0_g4::PrimaryGeneratorActionMessenger::SetNewValue: Exiting...\n";
    return;
  }

} // end of namespace bxdecay0_g4 
