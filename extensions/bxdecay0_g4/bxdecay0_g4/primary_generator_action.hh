#ifndef BXDECAY0G4_PRIMARY_GENERATOR_ACTION_HH
#define BXDECAY0G4_PRIMARY_GENERATOR_ACTION_HH

// Standard library:
#include <memory>
#include <iostream>
#include <string>

// Geant4
#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4ParticleGun.hh>
//#include <globals.hh>

class G4Event;
class G4ParticleGun;

// This project:
#include <bxdecay0_g4/vertex_generator_interface.hh>

namespace bxdecay0_g4 {

  class PrimaryGeneratorActionMessenger;
  
  /// \brief Primary generator action with an (privately) embedded BxDecay0 generator driver
  class PrimaryGeneratorAction
    : public G4VUserPrimaryGeneratorAction
  {
  public:

    /// \brief BxDecay0 generator configuration interface for Geant4 (used also by the associated messenger class)
    ///
    /// @see PrimaryGeneratorAction::SetConfiguration
    struct ConfigurationInterface
    {
      void print(std::ostream & out_, const std::string & indent_ = "") const;
      void reset_base();
      void reset_mdl();
      void reset();
      bool is_valid_base() const;
      bool is_valid_mdl() const;
      bool is_valid() const;
      
      G4String  decay_category; ///< Category of the decay (mandatory)
      G4String  nuclide;        ///< Name of the decaying isotope (mandatory)
      G4int     seed = 1;       ///< Seed for the pseudo-random number generator (mandatory)
      G4int     dbd_mode = 0;   ///< Double beta decay mode (mandatory only for "dbd" category)
      G4int     dbd_level = 0;  ///< Daughter's energy level for DBD decay (only for "dbd" category, default to 0)
      /// Minimum sum xenergy in MeV (optional for "dbd" category and some specific emitter nuclides and DBD modes)
      G4double  dbd_min_energy_MeV = -1.0;
      /// Maximum sum energy in MeV (optional for "dbd" category and some specific emitter nuclides and DBD modes)
      G4double  dbd_max_energy_MeV = -1.0;
      G4bool    debug = false;  ///< Debug flag (optional)

      // MDL support:
      G4bool    use_mdl = false;
      G4String  mdl_target_name = "";
      G4int     mdl_target_rank = -1;
      G4int     mdl_cone_longitude  = 0.0; // degree
      G4int     mdl_cone_colatitude = 0.0; // degree
      G4int     mdl_cone_aperture   = 0.0; // degree
      G4bool    mdl_error_on_missing_particle = false;
      
    };
    
    PrimaryGeneratorAction(int verbosity_ = 0);    

    /// Construction with a specific configuration object
    ///
    /// @see SetConfiguration
    PrimaryGeneratorAction(const ConfigurationInterface &, int verbosity_ = 0);    

    ~PrimaryGeneratorAction() override;

    const ConfigurationInterface & GetConfiguration() const;

    ConfigurationInterface & GrabConfiguration();

    /// Set the configuration changed flag
    void SetConfigHasChanged(bool);

    /// Check if the configuration has changed
    bool ConfigHasChanged() const;
    
    /// Set the configuration of the embedded BxDecay0 driver
    void SetConfiguration(const ConfigurationInterface &);

    /// Apply the currently set configuration
    ///
    /// This will trigger the re-instantiation of any existing BxDecay0 generator instance
    /// and its configuration. This includes also any change in the seed of the embedded
    /// pseudo-random number generator as the BxDecay0 driver uses its own random engine,
    /// independantly of the random engine used within Geant4.
    void ApplyConfiguration();

    /// Destroy the current configuration if applied
    void DestroyConfiguration();

    /// Main primaries generation method
    void GeneratePrimaries(G4Event *) override;

    G4ParticleGun * GetParticleGun();
    
    bool HasVertexGenerator() const;

    void SetVerbosity(int level);

    int GetVerbosity() const;

    bool IsInfo() const;
 
    bool IsDebug() const;

    bool IsTrace() const;

    void Dump(std::ostream &) const;
    
    /// Set the reference to an external vertex generator provided by the user.
    ///
    /// The vertex generator object must inherit the `bxdecay0_g4::VertexGeneratorInterface` abstract class.
    void SetVertexGenerator(VertexGeneratorInterface & vertex_generator_);
    
    VertexGeneratorInterface & GetVertexGenerator();
   
    const VertexGeneratorInterface & GetVertexGeneratorConst() const;
    
  private:

    G4ParticleGun * _particle_gun_ = nullptr; ///< The Geant4 particle gun
    VertexGeneratorInterface * _vertex_generator_ = nullptr; ///< Reference to an external vertex generator
    PrimaryGeneratorActionMessenger * _messenger_ = nullptr; ///< Messenger
    ConfigurationInterface _config_; ///< Current configuration
    bool _config_has_changed_ = false; ///< Config change flag
    int _verbosity_ = 0; ///< Verbosity level (0=mute, 1=info, 2=debug, 3=trace)
    
    // PIMPL support (nothing of the BxDecay0 library is publicly exposed here):
    struct pimpl_type;
    std::unique_ptr<pimpl_type> _pimpl_; ///< Embedded private BxDecay0 driver and associated resources
    
  };
  
} // end of namespace bxdecay0_g4 

#endif // BXDECAY0G4_PRIMARY_GENERATOR_ACTION_HH
