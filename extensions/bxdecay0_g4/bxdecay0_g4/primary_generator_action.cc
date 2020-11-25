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

namespace bxdecay0_g4 {
  
  void PrimaryGeneratorAction::ConfigurationInterface::print(std::ostream & out_) const
  {
    out_ << "Configuration interface: \n";
    out_ << "|-- Decay category : '" << decay_category << "'\n";
    out_ << "|-- Nuclide : '" << nuclide << "'\n";
    out_ << "|-- Seed : " << seed << "\n";
    out_ << "|-- DBD mode : " << dbd_mode << "\n";
    out_ << "|-- DBD level : " << dbd_level << "\n";
    out_ << "|-- DBD min energy (MeV) : " << dbd_min_energy_MeV << "\n";
    out_ << "|-- DBD max energy (MeV) : " << dbd_max_energy_MeV << "\n";
    out_ << "`-- Debug : " << std::boolalpha << debug << "\n";
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
    bool          debug = false; ///< Debug flag
  };

  // PIMPL-ized embedded private BxDecay0 driver and associated resources
  struct PrimaryGeneratorAction::pimpl_type
  {
    pimpl_type(PrimaryGeneratorAction * action);
    
    ~pimpl_type();

    bxdecay0::decay0_generator & get_decay0();

    void reset_decay0();
    
    void reset_generator();

    void reset_prng();

    std::default_random_engine & get_generator();

    bxdecay0::std_random & get_prng();

    // Attributes:
    PrimaryGeneratorAction *     action = nullptr;     // Mother action
    Configuration                config;               // Configuration of the BxDecay0 driver
    std::default_random_engine * pgenerator = nullptr; // Low level random generator (depends on config for its seeding)
    bxdecay0::std_random *       pprng = nullptr;      // High level random generator (depends on pgenerator)
    bxdecay0::decay0_generator * pdecay0 = nullptr;    // BxDecay0 generator driver (depends on pprng and config)

  };

  void PrimaryGeneratorAction::pimpl_type::reset_decay0()
  {
    if (action->IsTrace()) std::cerr << "[trace] bxdecay0_g4::PrimaryGeneratorAction::pimpl_type::reset_decay0: Entering...\n";
    if (pdecay0 != nullptr) {
      if (action->IsDebug()) std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorAction::pimpl_type::reset_decay0: Destroying the BxDecay0 driver...\n";
      pdecay0->reset();
      delete pdecay0;
      pdecay0 = nullptr;
    }
    if (action->IsTrace()) std::cerr << "[trace] bxdecay0_g4::PrimaryGeneratorAction::pimpl_type::reset_decay0: Exiting...\n";
    return;
  }
  
  bxdecay0::decay0_generator & PrimaryGeneratorAction::pimpl_type::get_decay0()
  {
    if (pdecay0 == nullptr) {
      if (action->IsDebug()) std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorAction::pimpl_type::get_decay0: Instantiating an configuring a new BxDecay0 generator...\n";
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
      pdecay0->initialize(get_prng());
      if (use_specific_erange) {
        toallevents = pdecay0->get_bb_params().toallevents;
        if (action->IsInfo()) std::cerr << "[info] bxdecay0_g4::PrimaryGeneratorAction::pimpl_type::get_decay0: BxDecay0 Geant4 extension library: toallevents=" << toallevents << "\n";
      }
    }
    return *pdecay0;
  }

  void PrimaryGeneratorAction::pimpl_type::reset_prng()
  {
    if (pprng != nullptr) {
      if (pdecay0 != nullptr) reset_decay0();
      if (action->IsDebug()) std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorAction::pimpl_type::reset_generator: Destroying the high level random generator...\n";
      delete pprng;
      pprng = nullptr;
    }
    return;
  }

  void PrimaryGeneratorAction::pimpl_type::reset_generator()
  {
    if (pgenerator != nullptr) {
      if (pprng != nullptr) reset_prng();
      if (action->IsDebug()) std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorAction::pimpl_type::reset_generator: Destroying the low level random generator...\n";
      delete pgenerator;
      pgenerator = nullptr;
    }
    return;
  }
  
  std::default_random_engine & PrimaryGeneratorAction::pimpl_type::get_generator()
  {
    if (pgenerator == nullptr) {
      if (action->IsDebug()) std::cerr << "[debug] bxdecay0_g4::PrimaryGeneratorAction::pimpl_type::get_prng: Instantiating a new low level random generator with seed=" << config.seed << "...\n";
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
    reset_decay0();
    reset_prng();
    reset_generator();
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
  
  PrimaryGeneratorAction::PrimaryGeneratorAction(int verbosity_)
    : G4VUserPrimaryGeneratorAction()
    , _particle_gun_(nullptr)
  {
    SetVerbosity(verbosity_);
    if (IsDebug()) std::cerr << "[debug] Instantiating BxDecay0 Geant4 Plugin PIMPL...\n";
    _pimpl_.reset(new pimpl_type(this));
    if (IsDebug()) std::cerr << "[debug] Instantiating Geant4 particle gun...\n";
    _particle_gun_ = new G4ParticleGun(1);
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

  void PrimaryGeneratorAction::SetConfiguration(const ConfigurationInterface & config_inter_)
  {
    if (IsTrace()) std::cerr << "[trace] bxdecay0_g4::PrimaryGeneratorAction::SetConfiguration: Entering...\n";
    _config_ = config_inter_;
    bool error = false;
    _pimpl_->reset_decay0();
    _pimpl_->reset_prng();
    _pimpl_->reset_generator();
    {
      // Set a default configuration:
      Configuration dummy;
      _pimpl_->config = dummy;
    };
    
    _pimpl_->config.debug = _config_.debug;

    if (not error) {
      if (_config_.seed <= 0) {
        std::cerr << "[error] bxdecay0_g4::PrimaryGeneratorAction::SetConfiguration: Invalid seed value " << _config_.seed << "!\n";
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
        std::cerr << "[error] bxdecay0_g4::PrimaryGeneratorAction::SetConfiguration: Unsupported decay category '" << _config_.decay_category << "'!\n";
        error = true;
      }
    }

    if (not error) {
      if (_pimpl_->config.decay_category == bxdecay0::decay0_generator::DECAY_CATEGORY_DBD) {
        if (bxdecay0::dbd_isotopes().count(_config_.nuclide) == 0) {
          std::cerr << "[error] bxdecay0_g4::PrimaryGeneratorAction::SetConfiguration: Unsupported DBD nuclide '" << _config_.nuclide << "'!\n";
          error = true;
        } 
      } else if (_pimpl_->config.decay_category == bxdecay0::decay0_generator::DECAY_CATEGORY_DBD) {
        if (bxdecay0::background_isotopes().count(_config_.nuclide) == 0) {
          std::cerr << "[error] bxdecay0_g4::PrimaryGeneratorAction::SetConfiguration: Unsupported background nuclide '" << _config_.nuclide << "'!\n";
          error = true;
        } 
      }
      if (not error) {
        _pimpl_->config.nuclide = _config_.nuclide;
      }
    }

    if (not error and _pimpl_->config.decay_category == bxdecay0::decay0_generator::DECAY_CATEGORY_DBD) {
      if (_config_.dbd_mode < bxdecay0::DBDMODE_MIN or _config_.dbd_mode > bxdecay0::DBDMODE_MAX) {
        std::cerr << "[error] bxdecay0_g4::PrimaryGeneratorAction::SetConfiguration: Invalid DBD decay mode " << _config_.dbd_mode << "!";
        error = true;
      } else {
        _pimpl_->config.dbd_mode = static_cast<bxdecay0::dbd_mode_type>(_config_.dbd_mode);
      }
      if (not error) {
        if (_config_.dbd_level < 0) {
          std::cerr << "[error] bxdecay0_g4::PrimaryGeneratorAction::SetConfiguration: Invalid DBD daughter level index " << _config_.dbd_level << "!";
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
              std::cerr << "[error] bxdecay0_g4::PrimaryGeneratorAction::SetConfiguration: Invalid DBD energy range!";
              error = true;
            }
          }
        }
      }
    }
    if (error) {
      std::cerr << "[error] bxdecay0_g4::PrimaryGeneratorAction::SetConfiguration: Invalid configuration! Abort run!\n";
      G4RunManager::GetRunManager()->AbortRun();
    }
    if (IsTrace()) std::cerr << "[trace] bxdecay0_g4::PrimaryGeneratorAction::SetConfiguration: Exiting...\n";
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
    _vertex_generator_ = &vertex_generator_;
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
    gendecay.set_time(0.0);
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
        particle_time += gendecay.get_time() * CLHEP::second;
      }
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
