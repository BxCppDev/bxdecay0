// Ourselves:
#include "bxdecay0_g4/primary_generator_action.hh"

// Standard library:
#include <iostream>
#include <random>
#include <limits>

// BxDecay0:
#include <bxdecay0/decay0_generator.h>
#include <bxdecay0/std_random.h>
#include <bxdecay0/event.h>       
#include <bxdecay0/bb_utils.h>
#include <bxdecay0/mdl_event_op.h>

// Geant4:
#include <globals.hh>
#include <G4ParticleMomentum.hh>
#include <G4ParticleGun.hh>
#include <G4Gamma.hh>
#include <G4Electron.hh>
#include <G4Positron.hh>
#include <G4Alpha.hh>
#include <G4SystemOfUnits.hh>
#include <G4RunManager.hh>

// This project:
#include "bxdecay0_g4/primary_generator_action_messenger.hh"

namespace {

  /// Hacked particle gun with a special ResetParticleData method
  struct MyParticleGun
    : public G4ParticleGun
  {
  public:
    MyParticleGun() = default;
    MyParticleGun(G4int numberofparticles)
      : G4ParticleGun(numberofparticles) {}
    MyParticleGun(G4ParticleDefinition* particleDef, 
                  G4int numberofparticles = 1)
      : G4ParticleGun(particleDef, numberofparticles) {}
    virtual ~MyParticleGun() override = default;
    MyParticleGun(const MyParticleGun&) = delete;
    const MyParticleGun& operator=(const MyParticleGun&) = delete;
    G4bool operator==(const MyParticleGun&) const = delete;
    G4bool operator!=(const MyParticleGun&) const = delete;
    void ResetParticleData()
    {
      NumberOfParticlesToBeGenerated = 1;
      particle_definition = nullptr;
      G4ThreeVector zero;
      particle_momentum_direction = (G4ParticleMomentum)zero;
      particle_energy = 0.0;
      particle_momentum = 0.0;
      particle_position = zero;
      particle_time = 0.0;
      particle_polarization = zero;
      particle_charge = 0.0;
    }
  };
}

namespace bxdecay0_g4 {
  
  void PrimaryGeneratorAction::ConfigurationInterface::print(std::ostream & out_, const std::string & indent_) const
  {
    out_ << indent_ << "Configuration interface: \n";
    out_ << indent_ << "|-- Decay category : '" << decay_category << "'\n";
    out_ << indent_ << "|-- Nuclide : '" << nuclide << "'\n";
    out_ << indent_ << "|-- Seed : " << seed << "\n";
    if (decay_category == "dbd") {
      out_ << indent_ << "|-- DBD mode : " << dbd_mode << "\n";
      out_ << indent_ << "|-- DBD level : " << dbd_level << "\n";
      out_ << indent_ << "|-- DBD min energy (MeV) : " << dbd_min_energy_MeV << "\n";
      out_ << indent_ << "|-- DBD max energy (MeV) : " << dbd_max_energy_MeV << "\n";
    }
    out_ << indent_ << "|-- Debug : " << std::boolalpha << debug << "\n";
    out_ << indent_ << "`-- Use MDL : " << std::boolalpha << use_mdl << "\n";
    if (use_mdl) {
      out_ << indent_ << "    " << "|-- Target particle name : " << mdl_target_name << "\n";
      out_ << indent_ << "    " << "|-- Target particle rank : " << mdl_target_rank << "\n";
      out_ << indent_ << "    " << "|-- Cone longitude       : " << mdl_cone_longitude << " degrees\n";
      out_ << indent_ << "    " << "|-- Cone colatitude      : " << mdl_cone_colatitude << " degrees\n";
      out_ << indent_ << "    " << "|-- Cone aperture        : " << mdl_cone_aperture << " degrees\n";
      out_ << indent_ << "    " << "|-- Cone aperture 2      : " << mdl_cone_aperture2 << " degrees\n";
      out_ << indent_ << "    " << "`-- Error on missing target particle : " << std::boolalpha << mdl_error_on_missing_particle << "\n";
    }
    return;
  }

  bool PrimaryGeneratorAction::ConfigurationInterface::is_valid_base() const
  {
    if (decay_category != "background" and decay_category != "dbd") {
      return false;
    }
    if (nuclide.empty()) {
      return false;
    }
    if (seed < 1) {
      return false;
    }
    if (decay_category == "dbd") {
      if (dbd_mode < 1) { // valid DBD modes/mechanisms start from 1):
        return false;
      }
      // Fix issue #22 (valid daughter levels start from 0):
      if (dbd_level < 0) { 
        return false;
      }
    }
    return true;
  }

  bool PrimaryGeneratorAction::ConfigurationInterface::is_valid_mdl() const
  {
    if (use_mdl) {
      if (mdl_target_name.empty()) return false;
      if (mdl_target_rank < -1) return false;
    }
    return true;
  }

  bool PrimaryGeneratorAction::ConfigurationInterface::is_valid() const
  {
    return is_valid_base() and is_valid_mdl();
  }
  
  void PrimaryGeneratorAction::ConfigurationInterface::reset_base()
  {
    decay_category = "";
    nuclide = "";
    seed = 1;
    dbd_mode = 0;
    dbd_level = 0;
    dbd_min_energy_MeV = -1.0;
    dbd_max_energy_MeV = -1.0;
    debug = false;
    return;
  }
   
  void PrimaryGeneratorAction::ConfigurationInterface::reset_mdl()
  {
    use_mdl = false;
    mdl_target_name = "";
    mdl_target_rank = -1;
    mdl_cone_longitude  = 0.0;
    mdl_cone_colatitude = 0.0;
    mdl_cone_aperture   = 0.0;
    mdl_cone_aperture2  = -1.0; // Unused cone aperture rectangular cut
    mdl_error_on_missing_particle = false;
    return;
  }
   
  void PrimaryGeneratorAction::ConfigurationInterface::reset() 
  {
    reset_base();
    reset_mdl();
    return;
  }
 
  // Private configuration structure for the unexposed BxDecay0 library:
  struct Configuration
  {
    /// Category of the decay
    bxdecay0::decay0_generator::decay_category_type decay_category = bxdecay0::decay0_generator::DECAY_CATEGORY_UNDEFINED;
    /// Name of the decaying isotope
    std::string   nuclide;      
    /// Seed for the pseudo-random number generator
    unsigned int  seed = 314159; 
    /// Daughter's energy level (default: ground state)
    int           dbd_level = 0;  
    /// Double beta decay mode (only for DBD mode)
    bxdecay0::dbd_mode_type dbd_mode = bxdecay0::DBDMODE_UNDEF; 
    /// Minimum sum energy in MeV (only for some DBD isotopes and modes)
    double dbd_min_energy_MeV = std::numeric_limits<double>::quiet_NaN();
    /// Maximum sum energy in MeV (only for some DBD isotopes and modes)
    double dbd_max_energy_MeV = std::numeric_limits<double>::quiet_NaN();
    bool   debug = false; ///< Debug flag
    
  };

  // Private configuration structure for the MDL event op of the unexposed BxDecay0 library:
  struct MdlEventOpConfiguration
  {
    bool   use_mdl = false; // Do not use MDL
    bxdecay0::particle_code code = bxdecay0::INVALID_PARTICLE; // All types of particles
    int    rank = -1; // All ranks
    double cone_phi = 0.0; // Z-axis
    double cone_theta = 0.0; // Z-axis
    double cone_aperture = 0.0; // Zero aperture
    double cone_aperture2 = std::numeric_limits<double>::quiet_NaN(); // No aperture rectangular cut 
    bool   error_on_missing_particle = false; // Pass if not applicable

  };

  // PIMPL-ized embedded private BxDecay0 driver and associated resources
  struct PrimaryGeneratorAction::pimpl_type
  {
    pimpl_type(PrimaryGeneratorAction * action);
    
    ~pimpl_type();

    bxdecay0::decay0_generator & get_decay0();

    void destroy_decay0();
    
    void destroy_generator();
    
    void destroy_prng();

    void destroy();

    std::default_random_engine & get_generator();

    bxdecay0::std_random & get_prng();

    // Attributes:
    PrimaryGeneratorAction *     action = nullptr;     // Mother action
    Configuration                config;               // Configuration of the BxDecay0 driver
    MdlEventOpConfiguration      mdl_config;           // Configuration of the MDL post-generation event operation in the BxDecay0 driver
    std::default_random_engine * pgenerator = nullptr; // Low level random generator (depends on config for its seeding)
    bxdecay0::std_random *       pprng = nullptr;      // High level random generator (depends on pgenerator)
    bxdecay0::decay0_generator * pdecay0 = nullptr;    // BxDecay0 generator driver (depends on pprng and config)

  };

  void PrimaryGeneratorAction::pimpl_type::destroy()
  {
    destroy_decay0();
    destroy_prng();
    destroy_generator();
    return;
  }

  void PrimaryGeneratorAction::pimpl_type::destroy_decay0()
  {
    if (action->IsTrace()) std::cerr << "[trace] bxdecay0_g4::PrimaryGeneratorAction::pimpl_type::destroy_decay0: Entering...\n";
    if (pdecay0 != nullptr) {
      if (action->IsDebug()) std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorAction::pimpl_type::destroy_decay0: Destroying the BxDecay0 driver...\n";
      pdecay0->reset();
      delete pdecay0;
      pdecay0 = nullptr;
    }
    if (action->IsTrace()) std::cerr << "[trace] bxdecay0_g4::PrimaryGeneratorAction::pimpl_type::destroy_decay0: Exiting...\n";
    return;
  }
  
  bxdecay0::decay0_generator & PrimaryGeneratorAction::pimpl_type::get_decay0()
  {
    if (action->IsTrace()) std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorAction::pimpl_type::get_decay0: Entering...\n";
    if (action->ConfigHasChanged()) {
      if (action->IsDebug()) std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorAction::pimpl_type::get_decay0: Configuration has changed\n";
      if (action->GetConfiguration().is_valid()) {
        action->ApplyConfiguration();
        if (pdecay0 != nullptr) {
          if (action->IsDebug()) std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorAction::pimpl_type::get_decay0: Destroying the current BxDecay0 generator instance because of a new config...\n";
          destroy();
        }
      } else {
        if (action->IsTrace()) std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorAction::pimpl_type::get_decay0: Invalid configuration!\n";
        
      }
    }
    if (pdecay0 == nullptr) {
      if (action->IsDebug()) std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorAction::pimpl_type::get_decay0: Instantiating and configuring a new BxDecay0 generator...\n";
      pdecay0 = new bxdecay0::decay0_generator;
      // Configure the BxDecay0 generator:
      pdecay0->set_debug(config.debug);
      pdecay0->set_decay_category(config.decay_category);
      pdecay0->set_decay_isotope(config.nuclide);
      double toallevents = 1.0;
      bool use_specific_erange = false;
      if (config.decay_category == bxdecay0::decay0_generator::DECAY_CATEGORY_DBD) {
        pdecay0->set_decay_dbd_level(config.dbd_level);
        pdecay0->set_decay_dbd_mode(config.dbd_mode);
        if (! std::isnan(config.dbd_min_energy_MeV) or !std::isnan(config.dbd_max_energy_MeV)) {
          // limited energy range
          double emin_MeV = 0.0;
          double emax_MeV = 5000.0;
          if (! std::isnan(config.dbd_min_energy_MeV)) {
            emin_MeV = config.dbd_min_energy_MeV;
          }
          if (! std::isnan(config.dbd_max_energy_MeV)) {
            emax_MeV = config.dbd_max_energy_MeV;
          }
          pdecay0->set_decay_dbd_esum_range(emin_MeV, emax_MeV);
          use_specific_erange = true;
        }
      }
      if (mdl_config.use_mdl) {
        // Install the MDL post-generation operation in the generator
        if (action->IsDebug()) {
          std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorAction::pimpl_type::get_decay0: "
                    << "Install the MDL post-generation operation in the BxDecay0 generator...\n";
        }
        bxdecay0::event_op_ptr mdlPtr(new bxdecay0::momentum_direction_lock_event_op(pdecay0->is_debug()));
        bxdecay0::momentum_direction_lock_event_op & mdl = dynamic_cast<bxdecay0::momentum_direction_lock_event_op&>(*mdlPtr);
        if (mdl_config.cone_aperture2 >= 0.0) {
          mdl.set_with_aperture_rectangular_cut(mdl_config.code, 
                                                mdl_config.rank,               
                                                mdl_config.cone_phi,
                                                mdl_config.cone_theta,   
                                                mdl_config.cone_aperture,        
                                                mdl_config.cone_aperture2,        
                                                mdl_config.error_on_missing_particle);
        } else {
          mdl.set(mdl_config.code, 
                  mdl_config.rank,               
                  mdl_config.cone_phi,
                  mdl_config.cone_theta,   
                  mdl_config.cone_aperture,        
                  mdl_config.error_on_missing_particle);
        }
        pdecay0->add_operation(mdlPtr); 
      }
      if (action->IsDebug()) {
        pdecay0->smart_dump(std::cerr,"BxDecay0 Generator: ", "[debug] ");
      }
      pdecay0->initialize(get_prng());
      if (use_specific_erange) {
        toallevents = pdecay0->get_bb_params().toallevents;
        if (action->IsInfo()) std::cerr << "[info] bxdecay0_g4::PrimaryGeneratorAction::pimpl_type::get_decay0: BxDecay0 Geant4 extension library: toallevents=" << toallevents << "\n";
      }
    }
    return *pdecay0;
  }

  void PrimaryGeneratorAction::pimpl_type::destroy_prng()
  {
    if (pprng != nullptr) {
      if (pdecay0 != nullptr) destroy_decay0();
      if (action->IsDebug()) std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorAction::pimpl_type::destroy_prng: Destroying the high level random generator...\n";
      delete pprng;
      pprng = nullptr;
    }
    return;
  }

  void PrimaryGeneratorAction::pimpl_type::destroy_generator()
  {
    if (pgenerator != nullptr) {
      if (pprng != nullptr) destroy_prng();
      if (action->IsDebug()) std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorAction::pimpl_type::destroy_generator: Destroying the low level random generator...\n";
      delete pgenerator;
      pgenerator = nullptr;
    }
    return;
  }
  
  std::default_random_engine & PrimaryGeneratorAction::pimpl_type::get_generator()
  {
    if (pgenerator == nullptr) {
      if (action->IsDebug()) std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorAction::pimpl_type::get_generator: Instantiating a new low level random generator with seed=" << config.seed << "...\n";
      pgenerator = new std::default_random_engine(config.seed);
    }
    return *pgenerator;
  }

  bxdecay0::std_random & PrimaryGeneratorAction::pimpl_type::get_prng()
  {
    if (pprng == nullptr) {
      if (action->IsDebug()) std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorAction::pimpl_type::get_prng: Instantiating a new high level random generator...\n";
      pprng = new bxdecay0::std_random(get_generator());
    }
    return *pprng;
  }

  PrimaryGeneratorAction::pimpl_type::pimpl_type(PrimaryGeneratorAction * action_)
  {
    action = action_;
    if (action->IsTrace()) std::cerr << "[trace] bxdecay0_g4::PrimaryGeneratorAction::pimpl_type::ctor: Construction of the BxDecay0 Geant4 Plugin PIMPL...\n";
    return;
  }

  PrimaryGeneratorAction::pimpl_type::~pimpl_type()
  {
    destroy();
    if (action->IsTrace()) std::cerr << "[trace] bxdecay0_g4::PrimaryGeneratorAction::pimpl_type::dtor: Destruction of the BxDecay0 Geant4 Plugin PIMPL.\n";
    return;
  }

  void PrimaryGeneratorAction::SetVerbosity(int level_)
  {
    _verbosity_ = level_ < 0 ? 0 : level_;
    return;
  }

  int PrimaryGeneratorAction::GetVerbosity() const
  {
    return _verbosity_;
  }
  
  bool PrimaryGeneratorAction::IsInfo() const
  {
    return _verbosity_ > 0;
  }
  
  bool PrimaryGeneratorAction::IsDebug() const
  {
    return _verbosity_ > 1;
  }
 
  bool PrimaryGeneratorAction::IsTrace() const
     {
    return _verbosity_ > 2;
  }

  void PrimaryGeneratorAction::Dump(std::ostream & out_) const
  {
    out_ << "=== bxdecay0_g4::PrimaryGeneratorAction ===\n";
    out_ << "Verbosity : " << _verbosity_ << "\n";
    out_ << "Vertex generator : " << (_vertex_generator_ ? "yes" : "no") << "\n";
    out_ << "Messenger : " << (_messenger_ ? "yes" : "no") << "\n";
    _config_.print(out_);
    out_ << "Configuration has changed : " << std::boolalpha << _config_has_changed_ << "\n";
    out_ << "PIMPL : " << (_pimpl_ ? "yes" : "no") << "\n";
    if (_pimpl_ and _pimpl_->pdecay0) {
      _pimpl_->pdecay0->smart_dump(out_, "Decay0 generator instance: ", "");
    }
    return;
  }
   
  PrimaryGeneratorAction::PrimaryGeneratorAction(int verbosity_)
    : G4VUserPrimaryGeneratorAction()
    , _particle_gun_(nullptr)
  {
    SetVerbosity(verbosity_);
    if (IsDebug()) std::cerr << "[debug] Instantiating BxDecay0 Geant4 Plugin PIMPL...\n";
    _pimpl_.reset(new pimpl_type(this));
    if (IsDebug()) std::cerr << "[debug] Instantiating Geant4 particle gun...\n";
    // _particle_gun_ = new G4ParticleGun(1);
    _particle_gun_ = new MyParticleGun(1);
    if (IsDebug()) std::cerr << "[debug] Instantiating messenger...\n";
    _messenger_ = new PrimaryGeneratorActionMessenger(this);
    return;
  }
  
  PrimaryGeneratorAction::PrimaryGeneratorAction(const ConfigurationInterface & config_inter_, int verbosity_)
    : PrimaryGeneratorAction(verbosity_)
  {
    SetConfiguration(config_inter_);
    return;
  }
 
  PrimaryGeneratorAction::~PrimaryGeneratorAction()
  {
    if (_owned_vertex_generator_ and _vertex_generator_ != nullptr) {
      if (IsDebug()) std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorAction::~PrimaryGeneratorAction: Destroying the vertex generator...\n";
     delete _vertex_generator_;
      _vertex_generator_ = nullptr;
    }
    if (_messenger_) {
      if (IsDebug()) std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorAction::~PrimaryGeneratorAction: Terminating messenger...\n";
      delete _messenger_;
    }
    if (_particle_gun_) {
      if (IsDebug()) std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorAction::~PrimaryGeneratorAction: Terminating Geant4 particle gun...\n";
      delete _particle_gun_;
    }
    if (_pimpl_) {
      if (IsDebug()) std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorAction::~PrimaryGeneratorAction: Terminating BxDecay0 Geant4 Plugin PIMPL stuff...\n";
      _pimpl_.reset();
    }
    return;
  }

  const PrimaryGeneratorAction::ConfigurationInterface & PrimaryGeneratorAction::GetConfiguration() const
  {
    return _config_;
  }

  PrimaryGeneratorAction::ConfigurationInterface & PrimaryGeneratorAction::GrabConfiguration() 
  {
    if (IsDebug()) std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorAction::GrabConfiguration: Destroy PIMPL material, if any...\n";
    // SetConfigHasChanged(true);
    return _config_;
  }

  void PrimaryGeneratorAction::SetConfigHasChanged(bool changed_)
  {
    if (IsDebug()) std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorAction::SetConfigHasChanged: changed=" << changed_ << "\n";
    _config_has_changed_ = changed_;
    return;
  }
  
  bool PrimaryGeneratorAction::ConfigHasChanged() const
  {
    return _config_has_changed_;
  }

  void PrimaryGeneratorAction::SetConfiguration(const ConfigurationInterface & config_inter_)
  {
    if (IsTrace()) std::cerr << "[trace] bxdecay0_g4::PrimaryGeneratorAction::SetConfiguration: Entering...\n";
    _config_ = config_inter_;
    SetConfigHasChanged(true);
    if (IsTrace()) std::cerr << "[trace] bxdecay0_g4::PrimaryGeneratorAction::SetConfiguration: Exiting...\n";
    return;
  }

  void PrimaryGeneratorAction::DestroyConfiguration()
  {
    if (IsTrace()) std::cerr << "[trace] bxdecay0_g4::PrimaryGeneratorAction::DestroyConfiguration: Entering...\n";
    if (IsDebug()) std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorAction::DestroyConfiguration: Entering...\n";
    _pimpl_->destroy();
    _config_.reset();
    _config_has_changed_ = false;
    if (IsDebug()) std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorAction::DestroyConfiguration: Exiting...\n";
    if (IsTrace()) std::cerr << "[trace] bxdecay0_g4::PrimaryGeneratorAction::DestroyConfiguration: Exiting...\n";
    return;
  }

  void PrimaryGeneratorAction::ApplyConfiguration()
  {
    if (IsTrace()) std::cerr << "[trace] bxdecay0_g4::PrimaryGeneratorAction::ApplyConfiguration: Entering...\n";
    if (not _config_.is_valid()) {
      std::cerr << "[error] bxdecay0_g4::PrimaryGeneratorAction::ApplyConfiguration: Invalid configuration!\n";
      return;
    }
    bool error = false;
    if (IsDebug()) std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorAction::pimpl_type::get_decay0: Destroying the old BxDecay0 generator because of a new config to be applied...\n";
    _pimpl_->destroy();
    {
      // Set a default configuration:
      Configuration dummyConfig;
      _pimpl_->config = dummyConfig;
      MdlEventOpConfiguration dummyMdlDummy;
      _pimpl_->mdl_config = dummyMdlDummy;
    };
    
    _pimpl_->config.debug = _config_.debug;

    if (not error) {
      if (_config_.seed <= 0) {
        std::cerr << "[error] bxdecay0_g4::PrimaryGeneratorAction::ApplyConfiguration: Invalid seed value " << _config_.seed << "!\n";
        error = true;
      } else {
        _pimpl_->config.seed = _config_.seed;
      }
    }

    if (not error) {
      if (_config_.decay_category == "dbd") {
        _pimpl_->config.decay_category = bxdecay0::decay0_generator::DECAY_CATEGORY_DBD;
      } else if (_config_.decay_category == "background") {
        _pimpl_->config.decay_category = bxdecay0::decay0_generator::DECAY_CATEGORY_BACKGROUND;
      } else {
        std::cerr << "[error] bxdecay0_g4::PrimaryGeneratorAction::ApplyConfiguration: Unsupported decay category '" << _config_.decay_category << "'!\n";
        error = true;
      }
    }

    if (not error) {
      if (_pimpl_->config.decay_category == bxdecay0::decay0_generator::DECAY_CATEGORY_DBD) {
        if (bxdecay0::dbd_isotopes().count(_config_.nuclide) == 0) {
          std::cerr << "[error] bxdecay0_g4::PrimaryGeneratorAction::ApplyConfiguration: Unsupported DBD nuclide '" << _config_.nuclide << "'!\n";
          error = true;
        } 
      } else if (_pimpl_->config.decay_category == bxdecay0::decay0_generator::DECAY_CATEGORY_DBD) {
        if (bxdecay0::background_isotopes().count(_config_.nuclide) == 0) {
          std::cerr << "[error] bxdecay0_g4::PrimaryGeneratorAction::ApplyConfiguration: Unsupported background nuclide '" << _config_.nuclide << "'!\n";
          error = true;
        } 
      }
      if (not error) {
        _pimpl_->config.nuclide = _config_.nuclide;
      }
    }

    if (not error and _pimpl_->config.decay_category == bxdecay0::decay0_generator::DECAY_CATEGORY_DBD) {
      if (_config_.dbd_mode < bxdecay0::DBDMODE_MIN or _config_.dbd_mode > bxdecay0::DBDMODE_MAX) {
        std::cerr << "[error] bxdecay0_g4::PrimaryGeneratorAction::ApplyConfiguration: Invalid DBD decay mode " << _config_.dbd_mode << "!";
        error = true;
      } else {
        _pimpl_->config.dbd_mode = static_cast<bxdecay0::dbd_mode_type>(_config_.dbd_mode);
      }
      if (not error) {
        if (_config_.dbd_level < 0) {
          std::cerr << "[error] bxdecay0_g4::PrimaryGeneratorAction::ApplyConfiguration: Invalid DBD daughter level index " << _config_.dbd_level << "!";
          error = true;
        } else {
          _pimpl_->config.dbd_level = (int) _config_.dbd_level;
        }
      }
      if (not error) {
        if (_config_.dbd_min_energy_MeV > 0.0) {
          _pimpl_->config.dbd_min_energy_MeV = (double) _config_.dbd_min_energy_MeV;
        }
        if (_config_.dbd_max_energy_MeV > 0.0) {
          _pimpl_->config.dbd_max_energy_MeV = (double) _config_.dbd_max_energy_MeV;
          if (_config_.dbd_min_energy_MeV > 0.0) {
            if (_pimpl_->config.dbd_min_energy_MeV >= _pimpl_->config.dbd_max_energy_MeV) {
              // Check bounds ordering of the energy range:
              std::cerr << "[error] bxdecay0_g4::PrimaryGeneratorAction::ApplyConfiguration: Invalid DBD energy range!";
              error = true;
            }
          }
        }
      }
    }

    if (_config_.use_mdl) {
      MdlEventOpConfiguration & mdlConfig = _pimpl_->mdl_config;
      if (not error) {
        mdlConfig.use_mdl = _config_.use_mdl;
        if (_config_.mdl_target_name == "*" or _config_.mdl_target_name == "all") {
          mdlConfig.code = bxdecay0::INVALID_PARTICLE; 
        } else if (_config_.mdl_target_name == "e-" or _config_.mdl_target_name == "electron") {
          mdlConfig.code = bxdecay0::ELECTRON;
        } else if (_config_.mdl_target_name == "e+" or _config_.mdl_target_name == "positron") {
          mdlConfig.code = bxdecay0::POSITRON;
        } else if (_config_.mdl_target_name == "g" or _config_.mdl_target_name == "gamma") {
          mdlConfig.code = bxdecay0::GAMMA;
        } else if (_config_.mdl_target_name == "n" or _config_.mdl_target_name == "neutron") {
          mdlConfig.code = bxdecay0::NEUTRON;
        } else if (_config_.mdl_target_name == "p" or _config_.mdl_target_name == "proton") {
          mdlConfig.code = bxdecay0::PROTON;
        } else if (_config_.mdl_target_name == "a" or _config_.mdl_target_name == "alpha") {
          mdlConfig.code = bxdecay0::ALPHA;
        } else {
          std::cerr << "[error] bxdecay0_g4::PrimaryGeneratorAction::ApplyConfiguration: Invalid target particle label '" << _config_.mdl_target_name << "'!";
          error = true;
        }
      }
      
      if (not error) {     
        if (_config_.mdl_target_rank < 0) {
          mdlConfig.rank = -1; 
        } else {
          mdlConfig.rank = _config_.mdl_target_rank; 
        }
      }
      
      if (not error) {
        // Convert degrees to radians:
        mdlConfig.cone_phi = _config_.mdl_cone_longitude * M_PI / 180.0;
        mdlConfig.cone_theta = _config_.mdl_cone_colatitude * M_PI / 180.0;
        mdlConfig.cone_aperture = _config_.mdl_cone_aperture * M_PI / 180.0;
        mdlConfig.cone_aperture2 = std::numeric_limits<double>::quiet_NaN();
        if (_config_.mdl_cone_aperture2 >= 0.0) {
          mdlConfig.cone_aperture2 = _config_.mdl_cone_aperture2 * M_PI / 180.0;
        }
        mdlConfig.error_on_missing_particle = _config_.mdl_error_on_missing_particle;
      }
    }
    
    if (error) {
      std::cerr << "[error] bxdecay0_g4::PrimaryGeneratorAction::ApplyConfiguration: Invalid configuration! Abort run!\n";
      G4RunManager::GetRunManager()->AbortRun();
    }
    SetConfigHasChanged(false);
    if (IsTrace()) std::cerr << "[trace] bxdecay0_g4::PrimaryGeneratorAction::ApplyConfiguration: Exiting...\n";
    return;
  }

  G4ParticleGun * PrimaryGeneratorAction::GetParticleGun()
  {
    return _particle_gun_;
  }
   
  bool PrimaryGeneratorAction::HasVertexGenerator() const
  {
    return _vertex_generator_ != nullptr;
  }

  void PrimaryGeneratorAction::SetVertexGenerator(VertexGeneratorInterface & vertex_generator_)
  {
    if (_owned_vertex_generator_ and _vertex_generator_ != nullptr) {
      delete _vertex_generator_;
      _vertex_generator_ = nullptr;
      _owned_vertex_generator_ = false;
    }
    _vertex_generator_ = &vertex_generator_;
    _owned_vertex_generator_ = false;
    return;
  }
 
  void PrimaryGeneratorAction::SetVertexGenerator(VertexGeneratorInterface * vertex_generator_ptr_)
  {
    if (_owned_vertex_generator_ and _vertex_generator_ != nullptr) {
      delete _vertex_generator_;
      _vertex_generator_ = nullptr;
      _owned_vertex_generator_ = false;
    }
    _vertex_generator_ = vertex_generator_ptr_;
    _owned_vertex_generator_ = true;
    return;
  }
 
  VertexGeneratorInterface & PrimaryGeneratorAction::GetVertexGenerator()
  {
    return *_vertex_generator_;
  }
 
  const VertexGeneratorInterface & PrimaryGeneratorAction::GetVertexGeneratorConst() const
  {
    return *_vertex_generator_;
  }
    
  void PrimaryGeneratorAction::GeneratePrimaries(G4Event * event_)
  {
    if (IsTrace()) std::cerr << "[trace] bxdecay0_g4::PrimaryGeneratorAction::GeneratePrimaries: Entering..." << '\n';
    bxdecay0::event gendecay;
    _pimpl_->get_decay0().shoot(_pimpl_->get_prng(), gendecay);
    double event_time = 0.0 * CLHEP::second;
    // Force event reference time to be zero (even if the generator tells something else):
    // if (gendecay.has_time()) {
    //    event_time = gendecay.get_time() * CLHEP::second;
    // }
    double particle_time = 0.0;
    const auto & particles = gendecay.get_particles();
    if (IsDebug()) std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorAction::GeneratePrimaries: Nb particles=" << particles.size() << '\n';

    // Shoot the common vertex:
    G4ThreeVector vertex(0.0, 0.0, 0.0);
    if (HasVertexGenerator()) {
      if (not _vertex_generator_->HasNextVertex()) {
        G4RunManager::GetRunManager()->AbortRun();
        G4Exception("bxdecay0_g4::PrimaryGeneratorAction::GeneratePrimaries: ",
                    "InvalidArgument",
                    RunMustBeAborted,
                    "Vertex generator has no more vertex available! Abort run!");
      }
      _vertex_generator_->ShootVertex(vertex);  
    }

    // Scan the list of BxDecay0 generated particles:
    for (const auto & particle : particles) {
      // Reset gun's internals:
      dynamic_cast<MyParticleGun*>(_particle_gun_)->ResetParticleData();
      // Particle type:
      if (particle.is_electron()) {
        _particle_gun_->SetParticleDefinition(G4Electron::ElectronDefinition());
      } else if (particle.is_positron()) {
        _particle_gun_->SetParticleDefinition(G4Positron::PositronDefinition());
      } else if (particle.is_gamma()) {
        _particle_gun_->SetParticleDefinition(G4Gamma::GammaDefinition());
      } else if (particle.is_alpha()) {
        _particle_gun_->SetParticleDefinition(G4Alpha::AlphaDefinition());
      } else {
        throw std::logic_error("bxdecay9_g4::PrimaryGeneratorAction::GeneratePrimaries: Unsupported particle type!");
      }
      // Time:
      if (particle.has_time()) {
        particle_time = particle.get_time() * CLHEP::second;
      } else {
        particle_time = 0.0 * CLHEP::second;
      }
      // Shift particle time by the event reference time:
      particle_time += event_time;
      _particle_gun_->SetParticleTime(particle_time);
      // Momentum:
      G4ThreeVector momentum(particle.get_px() * CLHEP::MeV,
                             particle.get_py() * CLHEP::MeV,
                             particle.get_pz() * CLHEP::MeV);
      _particle_gun_->SetParticleMomentum(momentum);
      // Vertex:
      _particle_gun_->SetParticlePosition(vertex);
      // Push the BxDecay0 generated  particle in the stack of Geant4 primaries:
      _particle_gun_->GeneratePrimaryVertex(event_);
    }
    if (IsTrace()) std::cerr << "[trace] bxdecay0_g4::PrimaryGeneratorAction::GeneratePrimaries: Exiting..." << '\n';
    return;
  }

} // end of namespace bxdecay0_g4 
