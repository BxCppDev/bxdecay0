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
    _pga_directory_->SetGuidance(" BxDecay0 comands.");

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
      // Command /particle/generator/dump
      _pga_gtor_dump_cmd_ = new G4UIcommand("/bxdecay0/generator/dump", this);
      _pga_gtor_dump_cmd_->SetGuidance("print the current configuration of the BxDecay0 driver");
      _pga_gtor_dump_cmd_->SetGuidance("[usage] /bxdecay0/generator/dump");
    }

    {
      // Command /particle/generator/apply
      _pga_gtor_apply_cmd_ = new G4UIcommand("/bxdecay0/generator/apply", this);
      _pga_gtor_apply_cmd_->SetGuidance("Apply the current configuration");
      _pga_gtor_apply_cmd_->SetGuidance("[usage] /bxdecay0/generator/apply");
    }
  
    {
      // Command /particle/generator/destroy
      _pga_gtor_destroy_cmd_ = new G4UIcommand("/bxdecay0/generator/destroy", this);
      _pga_gtor_destroy_cmd_->SetGuidance("Destroy the current configuration");
      _pga_gtor_destroy_cmd_->SetGuidance("[usage] /bxdecay0/generator/destroy");
    }
 
    {
      // Command /bxdecay0/generator/mdl
      _pga_gtor_mdl_cmd_ = new G4UIcommand("/bxdecay0/generator/mdl", this);
      _pga_gtor_mdl_cmd_->SetGuidance("Set the parameters of a MDL post-generation event biasing operation in the BxDecay0 event generator");
      _pga_gtor_mdl_cmd_->SetGuidance("[usage] /bxdecay0/generator/mdl [TARGET_PARTICLE] [TARGET_RANK] ");
      _pga_gtor_mdl_cmd_->SetGuidance("                                [CONE_LONGITUDE] [CONE_COLATITUDE] [CONE_APERTURE] ");
      _pga_gtor_mdl_cmd_->SetGuidance("                                [ERROR_ON_MISSING_TARGET]");
      _pga_gtor_mdl_cmd_->SetGuidance("  TARGET_PARTICLE: (string) name of the target particle");
      _pga_gtor_mdl_cmd_->SetGuidance("    Supported values: *|all, e+|positron, e-|electron, g|gamma, a|alpha, n|neutron, p|proton");
      _pga_gtor_mdl_cmd_->SetGuidance("  TARGET_RANK: (int) rank of the target particle (0, 1...)");
      _pga_gtor_mdl_cmd_->SetGuidance("  CONE_LONGITUDE: (double) Cone axis longitude (0..360 degree)");
      _pga_gtor_mdl_cmd_->SetGuidance("  CONE_COLATITUDE: (double) Cone axis colatitude (0..180 degree)");
      _pga_gtor_mdl_cmd_->SetGuidance("  CONE_APERTURE: (double) Cone angle of aperture (0..180 degree)");
      _pga_gtor_mdl_cmd_->SetGuidance("  ERROR_ON_MISSING_TARGET: (bool) Throw error on missing target particle (default: false)");

      {
        // Target particle type parameter: 
        G4UIparameter * targetParticleNameParam = new G4UIparameter("particle", 's', true);
        targetParticleNameParam->SetGuidance("the name of the target particle (optional)");
        targetParticleNameParam->SetDefaultValue("all");
        _pga_gtor_mdl_cmd_->SetParameter(targetParticleNameParam);
      }

      {
        // Target particle rank parameter: 
        G4UIparameter * targetParticleRankParam = new G4UIparameter("rank", 'i', true);
        targetParticleRankParam->SetGuidance("the rank of the target particle (optional)");
        targetParticleRankParam->SetDefaultValue("-1");
        _pga_gtor_mdl_cmd_->SetParameter(targetParticleRankParam);
      }
 
      {
        // Cone longitude: 
        G4UIparameter * coneLongitudeParam = new G4UIparameter("longitude", 'f', true);
        coneLongitudeParam->SetGuidance("longitude of the emission cone axis (degree)");
        // coneLongitudeParam->SetParameterName("longitude");
        // coneLongitudeParam->SetParameterRange("longitude >= 0.0 && longitude <= 360.0");
        coneLongitudeParam->SetDefaultValue("0.0");
        _pga_gtor_mdl_cmd_->SetParameter(coneLongitudeParam);
      }
 
       {
        // Cone colatitude: 
        G4UIparameter * coneColatitudeParam = new G4UIparameter("colatitude", 'f', true);
        coneColatitudeParam->SetGuidance("colatitude of the emission cone axis (degree)");
        // coneColatitudeParam->SetParameterName("colatitude");
        // coneColatitudeParam->SetParameterRange("colatitude >= 0.0 && colatitude <= 180.0");
        coneColatitudeParam->SetDefaultValue("0.0");
        _pga_gtor_mdl_cmd_->SetParameter(coneColatitudeParam);
      }

      {
        // Cone aperture: 
        G4UIparameter * coneApertureParam = new G4UIparameter("aperture", 'f', true);
        coneApertureParam->SetGuidance("aperture of the emission cone (degree)");
        // coneApertureParam->SetParameterName("aperture");
        // coneApertureParam->SetParameterRange("aperture >= 0.0 && aperture <= 180.0");
        coneApertureParam->SetDefaultValue("0.0");
        _pga_gtor_mdl_cmd_->SetParameter(coneApertureParam);
      }
   
      {
        // Error on missing target parameter: 
        G4UIparameter * errorOnMissingTargetParam = new G4UIparameter("error_on_missing_target", 'b', true);
        errorOnMissingTargetParam->SetGuidance("throw error on missing target particle");
        errorOnMissingTargetParam->SetDefaultValue("false");
        _pga_gtor_mdl_cmd_->SetParameter(errorOnMissingTargetParam);
      }
    
    }
  
    {
      // Command /bxdecay0/generator/mdlr
      _pga_gtor_mdlr_cmd_ = new G4UIcommand("/bxdecay0/generator/mdlr", this);
      _pga_gtor_mdlr_cmd_->SetGuidance("Set the parameters of a MDL post-generation event biasing operation in the");
      _pga_gtor_mdlr_cmd_->SetGuidance("BxDecay0 event generator (with rectangular cut on conical aperture)");
      _pga_gtor_mdlr_cmd_->SetGuidance("[usage] /bxdecay0/generator/mdle [TARGET_PARTICLE] [TARGET_RANK] ");
      _pga_gtor_mdlr_cmd_->SetGuidance("                                [CONE_LONGITUDE] [CONE_COLATITUDE] ");
      _pga_gtor_mdlr_cmd_->SetGuidance("                                [CONE_APERTURE] [CONE_APERTURE2] ");
      _pga_gtor_mdlr_cmd_->SetGuidance("                                [ERROR_ON_MISSING_TARGET]");
      _pga_gtor_mdlr_cmd_->SetGuidance("  TARGET_PARTICLE: (string) name of the target particle");
      _pga_gtor_mdlr_cmd_->SetGuidance("    Supported values: *|all, e+|positron, e-|electron, g|gamma, a|alpha, n|neutron, p|proton");
      _pga_gtor_mdlr_cmd_->SetGuidance("  TARGET_RANK: (int) rank of the target particle (0, 1...)");
      _pga_gtor_mdlr_cmd_->SetGuidance("  CONE_LONGITUDE: (double) Cone axis longitude (0..360 degree)");
      _pga_gtor_mdlr_cmd_->SetGuidance("  CONE_COLATITUDE: (double) Cone axis colatitude (0..180 degree)");
      _pga_gtor_mdlr_cmd_->SetGuidance("  CONE_APERTURE: (double) Cone angle of aperture (0..90 degree)");
      _pga_gtor_mdlr_cmd_->SetGuidance("  CONE_APERTURE2: (double) Cone angle of aperture 2 (0..90 degree)");
      _pga_gtor_mdlr_cmd_->SetGuidance("  ERROR_ON_MISSING_TARGET: (bool) Throw error on missing target particle (default: false)");

      {
        // Target particle type parameter: 
        G4UIparameter * targetParticleNameParam = new G4UIparameter("particle", 's', true);
        targetParticleNameParam->SetGuidance("the name of the target particle (optional)");
        targetParticleNameParam->SetDefaultValue("all");
        _pga_gtor_mdlr_cmd_->SetParameter(targetParticleNameParam);
      }

      {
        // Target particle rank parameter: 
        G4UIparameter * targetParticleRankParam = new G4UIparameter("rank", 'i', true);
        targetParticleRankParam->SetGuidance("the rank of the target particle (optional)");
        targetParticleRankParam->SetDefaultValue("-1");
        _pga_gtor_mdlr_cmd_->SetParameter(targetParticleRankParam);
      }
 
      {
        // Cone longitude: 
        G4UIparameter * coneLongitudeParam = new G4UIparameter("longitude", 'f', true);
        coneLongitudeParam->SetGuidance("longitude of the emission cone axis (degree)");
        // coneLongitudeParam->SetParameterName("longitude");
        // coneLongitudeParam->SetParameterRange("longitude >= 0.0 && longitude <= 360.0");
        coneLongitudeParam->SetDefaultValue("0.0");
        _pga_gtor_mdlr_cmd_->SetParameter(coneLongitudeParam);
      }
 
       {
        // Cone colatitude: 
        G4UIparameter * coneColatitudeParam = new G4UIparameter("colatitude", 'f', true);
        coneColatitudeParam->SetGuidance("colatitude of the emission cone axis (degree)");
        // coneColatitudeParam->SetParameterName("colatitude");
        // coneColatitudeParam->SetParameterRange("colatitude >= 0.0 && colatitude <= 180.0");
        coneColatitudeParam->SetDefaultValue("0.0");
        _pga_gtor_mdlr_cmd_->SetParameter(coneColatitudeParam);
      }

      {
        // Cone aperture: 
        G4UIparameter * coneApertureParam = new G4UIparameter("aperture", 'f', true);
        coneApertureParam->SetGuidance("first aperture of the emission cone (degree)");
        // coneApertureParam->SetParameterName("aperture");
        // coneApertureParam->SetParameterRange("aperture >= 0.0 && aperture <= 90.0");
        coneApertureParam->SetDefaultValue("0.0");
        _pga_gtor_mdlr_cmd_->SetParameter(coneApertureParam);
      }

      {
        // Cone aperture 2: 
        G4UIparameter * coneAperture2Param = new G4UIparameter("aperture2", 'f', true);
        coneAperture2Param->SetGuidance("second aperture of the emission cone (degree)");
        // coneAperture2Param->SetParameterName("aperture2");
        // coneAperture2Param->SetParameterRange("aperture2 >= 0.0 && aperture2 <= 90.0");
        coneAperture2Param->SetDefaultValue("0.0");
        _pga_gtor_mdlr_cmd_->SetParameter(coneAperture2Param);
      }
   
      {
        // Error on missing target parameter: 
        G4UIparameter * errorOnMissingTargetParam = new G4UIparameter("error_on_missing_target", 'b', true);
        errorOnMissingTargetParam->SetGuidance("throw error on missing target particle");
        errorOnMissingTargetParam->SetDefaultValue("false");
        _pga_gtor_mdlr_cmd_->SetParameter(errorOnMissingTargetParam);
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
        seedParam->SetParameterRange("seed>0");
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
      // Command /bxdecay0/generator/dbd
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
      // Command /bxdecay0/generator/dbdranged
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
    _pga_gtor_mdl_cmd_->AvailableForStates(G4State_PreInit, G4State_Idle);
    _pga_gtor_mdlr_cmd_->AvailableForStates(G4State_PreInit, G4State_Idle);
    _pga_gtor_apply_cmd_->AvailableForStates(G4State_PreInit, G4State_Idle);
    _pga_gtor_destroy_cmd_->AvailableForStates(G4State_PreInit, G4State_Idle);
    _pga_gtor_dump_cmd_->AvailableForStates(G4State_PreInit, G4State_Idle);
    
    return;
  }

  PrimaryGeneratorActionMessenger::~PrimaryGeneratorActionMessenger()
  {
    delete _pga_gtor_dump_cmd_;
    delete _pga_gtor_apply_cmd_;
    delete _pga_gtor_destroy_cmd_;
    delete _pga_gtor_mdl_cmd_;
    delete _pga_gtor_mdlr_cmd_;
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
    if (command_ == _pga_gtor_dump_cmd_) {
    }
    if (command_ == _pga_gtor_apply_cmd_) {
    }
    if (command_ == _pga_gtor_destroy_cmd_) {
    }
    if (command_ == _pga_gtor_mdl_cmd_) {
      PrimaryGeneratorAction::ConfigurationInterface configInt = _pga_->GetConfiguration();
      std::ostringstream sCurValue;
      sCurValue << (configInt.mdl_target_name.empty() ? "all" :  configInt.mdl_target_name) << ' ';
      sCurValue << configInt.mdl_target_rank << ' ';
      sCurValue << configInt.mdl_cone_longitude << ' ';
      sCurValue << configInt.mdl_cone_colatitude << ' ';
      sCurValue << configInt.mdl_cone_aperture << ' ';
      sCurValue << std::boolalpha << configInt.mdl_error_on_missing_particle;
      curValue = sCurValue.str();
    }
    if (command_ == _pga_gtor_mdlr_cmd_) {
      PrimaryGeneratorAction::ConfigurationInterface configInt = _pga_->GetConfiguration();
      std::ostringstream sCurValue;
      sCurValue << (configInt.mdl_target_name.empty() ? "all" :  configInt.mdl_target_name) << ' ';
      sCurValue << configInt.mdl_target_rank << ' ';
      sCurValue << configInt.mdl_cone_longitude << ' ';
      sCurValue << configInt.mdl_cone_colatitude << ' ';
      sCurValue << configInt.mdl_cone_aperture << ' ';
      sCurValue << configInt.mdl_cone_aperture2 << ' ';
      sCurValue << std::boolalpha << configInt.mdl_error_on_missing_particle;
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

    if (command_ == _pga_gtor_apply_cmd_) {
      _pga_->ApplyConfiguration();  
      if (_pga_->IsDebug()) {
        std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorActionMessenger::SetNewValue: "
                  << "Command 'apply' -> Action -> ApplyConfiguration...\n";
        const PrimaryGeneratorAction::ConfigurationInterface & configInt = _pga_->GetConfiguration();
        configInt.print(std::cerr);
      }
    }

    if (command_ == _pga_gtor_destroy_cmd_) {
      _pga_->DestroyConfiguration();  
      if (_pga_->IsDebug()) {
        std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorActionMessenger::SetNewValue: "
                  << "Command 'destroy' -> Action -> DestroyConfiguration...\n";
        const PrimaryGeneratorAction::ConfigurationInterface & configInt = _pga_->GetConfiguration();
        configInt.print(std::cerr);
      }
    }
    
    if (command_ == _pga_gtor_dump_cmd_) {
      _pga_->Dump(G4cout);  
      if (_pga_->IsDebug()) {
        std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorActionMessenger::SetNewValue: "
                  << "Command 'dump' -> Action -> Dump...\n";
      }
    }
   
    if (command_ == _pga_gtor_log_cmd_) {
      G4int   level = 0;             // 0
      G4Tokenizer next(new_value_);
      level = StoI(next());
      _pga_->SetVerbosity(level);  
      if (_pga_->IsDebug()) {
        std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorActionMessenger::SetNewValue: "
                  << "Command 'log' -> Action -> SetVerbosity...\n";
      }
    }
    
    if (command_ == _pga_gtor_mdl_cmd_) {
      // Temporary parsing variables:
      G4String particuleName  = "all"; // 0
      G4int    particuleRank  = -1;    // 1
      G4double coneLongitude  = 0.0;   // 2
      G4double coneColatitude = 0.0;   // 3
      G4double coneAperture   = 0.0;   // 4
      G4bool   errorOnMissingTarget = false; // 5
      G4Tokenizer next(new_value_);
      particuleName = next();
      G4String pR = next();
      if (pR == "all") {
        particuleRank = -1;
      } else {
        particuleRank = StoI(pR);
        if (particuleRank < -1) particuleRank = -1;
      }
      coneLongitude = StoD(next());
      coneColatitude = StoD(next());
      coneAperture = StoD(next());
      G4String sD = next();
      if (! sD.isNull()) {
        errorOnMissingTarget = G4UIcommand::ConvertToBool(sD.data());
      }
      if (_pga_->IsDebug()) {
        std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorActionMessenger::SetNewValue: "
                  << "particuleName = " << particuleName << "\n";
        std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorActionMessenger::SetNewValue: "
                  << "particuleRank = " << particuleRank << "\n";
        std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorActionMessenger::SetNewValue: "
                  << "coneLongitude = " << coneLongitude << "\n";
        std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorActionMessenger::SetNewValue: "
                  << "coneColatitude = " << coneColatitude << "\n";
        std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorActionMessenger::SetNewValue: "
                  << "coneAperture = " << coneAperture << "\n";
        std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorActionMessenger::SetNewValue: "
                  << "errorOnMissingTarget = " << errorOnMissingTarget << "\n";
      }
      // Grab config interface:
      PrimaryGeneratorAction::ConfigurationInterface & configInt = _pga_->GrabConfiguration();
      configInt.reset_mdl();
      static const std::set<G4String> targetNames
        = {"all", "*", "e+", "positron", "e-", "electron", "g", "gamma", "a", "alpha", "n", "neutron", "p", "proton"};
      bool error = false;
      if (targetNames.count(particuleName) == 0)  error = true;
      if (particuleRank < -1 and particuleRank >= 10) error = true;
      if (not error) {
        configInt.use_mdl = true;
        configInt.mdl_target_name = particuleName;
        configInt.mdl_target_rank = particuleRank;
        configInt.mdl_cone_longitude = coneLongitude;
        configInt.mdl_cone_colatitude = coneColatitude;
        configInt.mdl_cone_aperture = coneAperture;
        configInt.mdl_error_on_missing_particle = errorOnMissingTarget;
        _pga_->SetConfigHasChanged(true);
        if (_pga_->IsDebug()) {
          std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorActionMessenger::SetNewValue: "
                    << "Command 'mdl' -> Action -> update the working configuration...\n";
          configInt.print(std::cerr);
        }
      } else {
          std::cerr << "[error] bxdecay0_g4::PrimaryGeneratorActionMessenger::SetNewValue: "
                    << "Command 'mdl' : Parameter error!\n";    
      }
  
    }
    
    if (command_ == _pga_gtor_mdlr_cmd_) {
      // Temporary parsing variables:
      G4String particuleName  = "all"; // 0
      G4int    particuleRank  = -1;    // 1
      G4double coneLongitude  = 0.0;   // 2
      G4double coneColatitude = 0.0;   // 3
      G4double coneAperture   = 0.0;   // 4
      G4double coneAperture2   = 0.0;  // 5
      G4bool   errorOnMissingTarget = false; // 6
      G4Tokenizer next(new_value_);
      particuleName = next();
      G4String pR = next();
      if (pR == "all") {
        particuleRank = -1;
      } else {
        particuleRank = StoI(pR);
        if (particuleRank < -1) particuleRank = -1;
      }
      coneLongitude = StoD(next());
      coneColatitude = StoD(next());
      coneAperture = StoD(next());
      coneAperture2 = StoD(next());
      G4String sD = next();
      if (! sD.isNull()) {
        errorOnMissingTarget = G4UIcommand::ConvertToBool(sD.data());
      }
      if (_pga_->IsDebug()) {
        std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorActionMessenger::SetNewValue: "
                  << "particuleName = " << particuleName << "\n";
        std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorActionMessenger::SetNewValue: "
                  << "particuleRank = " << particuleRank << "\n";
        std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorActionMessenger::SetNewValue: "
                  << "coneLongitude = " << coneLongitude << "\n";
        std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorActionMessenger::SetNewValue: "
                  << "coneColatitude = " << coneColatitude << "\n";
        std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorActionMessenger::SetNewValue: "
                  << "coneAperture = " << coneAperture << "\n";
        std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorActionMessenger::SetNewValue: "
                  << "coneAperture2 = " << coneAperture2 << "\n";
         std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorActionMessenger::SetNewValue: "
                  << "errorOnMissingTarget = " << errorOnMissingTarget << "\n";
      }
      // Grab config interface:
      PrimaryGeneratorAction::ConfigurationInterface & configInt = _pga_->GrabConfiguration();
      configInt.reset_mdl();
      static const std::set<G4String> targetNames
        = {"all", "*", "e+", "positron", "e-", "electron", "g", "gamma", "a", "alpha", "n", "neutron", "p", "proton"};
      bool error = false;
      if (targetNames.count(particuleName) == 0)  error = true;
      if (particuleRank < -1 and particuleRank >= 10) error = true;
      if (not error) {
        configInt.use_mdl = true;
        configInt.mdl_target_name = particuleName;
        configInt.mdl_target_rank = particuleRank;
        configInt.mdl_cone_longitude = coneLongitude;
        configInt.mdl_cone_colatitude = coneColatitude;
        configInt.mdl_cone_aperture = coneAperture;
        configInt.mdl_cone_aperture2 = coneAperture2;
        configInt.mdl_error_on_missing_particle = errorOnMissingTarget;
        _pga_->SetConfigHasChanged(true);
        if (_pga_->IsDebug()) {
          std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorActionMessenger::SetNewValue: "
                    << "Command 'mdl' -> Action -> update the working configuration...\n";
          configInt.print(std::cerr);
        }
      } else {
          std::cerr << "[error] bxdecay0_g4::PrimaryGeneratorActionMessenger::SetNewValue: "
                    << "Command 'mdl' : Parameter error!\n";    
      }
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
      // Grab config interface:
      PrimaryGeneratorAction::ConfigurationInterface & configInt = _pga_->GrabConfiguration();
      bool error = false;
      if (not error) {
        configInt.reset_base();
        configInt.decay_category = "background";
        configInt.nuclide = nuclide;
        configInt.seed = seed;
        configInt.debug = debug;
        _pga_->SetConfigHasChanged(true);
        if (_pga_->IsDebug()) {
          std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorActionMessenger::SetNewValue: "
                    << "Command 'background' -> Action -> update the working configuration...\n";
          configInt.print(std::cerr);
        }
      } else {
          std::cerr << "[error] bxdecay0_g4::PrimaryGeneratorActionMessenger::SetNewValue: "
                    << "Command 'background' : Parameter error!\n";     
      }
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
      // Grab config interface:
      PrimaryGeneratorAction::ConfigurationInterface & configInt = _pga_->GrabConfiguration();
      bool error = false;
      if (not error) {
        configInt.reset_mdl();
        configInt.decay_category = "dbd";
        configInt.nuclide = nuclide;
        configInt.seed = seed;
        configInt.dbd_mode = dbd_mode;
        configInt.dbd_level = dbd_level;
        configInt.debug = debug;
        _pga_->SetConfigHasChanged(true);
        if (_pga_->IsDebug()) {
          std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorActionMessenger::SetNewValue: "
                    << "Command 'dbd' -> Action -> update the working configuration...\n";
          configInt.print(std::cerr);
        }
      } else {
        std::cerr << "[error] bxdecay0_g4::PrimaryGeneratorActionMessenger::SetNewValue: "
                  << "Command 'dbd' : Parameter error!\n";      
      }
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
      // Grab config interface:
      PrimaryGeneratorAction::ConfigurationInterface & configInt = _pga_->GrabConfiguration();
      bool error = false;
      if (not error) {
        configInt.reset_mdl();
        configInt.decay_category = "dbd";
        configInt.nuclide = nuclide;
        configInt.seed = seed;
        configInt.dbd_mode = dbd_mode;
        configInt.dbd_level = dbd_level;
        configInt.dbd_min_energy_MeV = dbd_min_energy;
        configInt.dbd_max_energy_MeV = dbd_max_energy;
        configInt.debug = debug;
        _pga_->SetConfigHasChanged(true);
        if (_pga_->IsDebug()) {
          std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorActionMessenger::SetNewValue: "
                    << "Command 'dbdranged' -> Action -> update the working configuration...\n";
          configInt.print(std::cerr);
        }
      } else {
        std::cerr << "[error] bxdecay0_g4::PrimaryGeneratorActionMessenger::SetNewValue: "
                  << "Command 'dbdranged' : Parameter error!\n";        
      }
    }

    if (_pga_->IsTrace()) std::cerr << "[trace] bxdecay0_g4::PrimaryGeneratorActionMessenger::SetNewValue: Exiting...\n";
    return;
  }

} // end of namespace bxdecay0_g4 
