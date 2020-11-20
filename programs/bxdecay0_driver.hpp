
#ifndef BXDECAY0_DRIVER_HPP
#define BXDECAY0_DRIVER_HPP

// Standard library:
#include <cstdlib>
#include <iostream>
#include <exception>
#include <string>
#include <limits>

// This project:
#include <bxdecay0/decay0_generator.h>
#include <bxdecay0/bb_utils.h>

namespace bxdecay0 {

  /// \brief BxDecay0 decay generator driver
  class driver
  {
  public:

    /// \brief Driver logging levels
    enum logging_type
      {
       LOGGING_UNDEFINED = -1,
       LOGGING_MUTE      =  0,
       LOGGING_VERBOSE   =  1,
       LOGGING_DEBUG     =  2
      };

    static std::string logging_to_string(const logging_type &);
    
    static logging_type logging_from_string(const std::string &);
    
    /// \brief Driver configuration
    struct config_type
    {
      logging_type logging   = LOGGING_MUTE;  ///< Logging level
      unsigned int seed      = 314159;        ///< Seed for the pseudo-random number generator
      std::size_t  nb_events = 1;             ///< number of generated decay events
      decay0_generator::decay_category_type decay_category = decay0_generator::DECAY_CATEGORY_UNDEFINED; ///< Category of the decay
      std::string  nuclide;                   ///< Name of the decaying isotope
      int          level     = 0;             ///< Daughter's energy level (default: ground state)
      dbd_mode_type dbd_mode = DBDMODE_UNDEF; ///< Double beta decay mode (only for DBD mode)
      double energy_min_MeV  = std::numeric_limits<double>::quiet_NaN(); ///< Minimum sum energy in MeV (only for some DBD isotopes and modes )
      double energy_max_MeV  = std::numeric_limits<double>::quiet_NaN(); ///< Maximum sum energy in MeV (only for some DBD isotopes and modes)
      double activity_Bq     = std::numeric_limits<double>::quiet_NaN(); ///< Activity in Bq (optional, for the generation of random decay times)
      std::string  basename;                  ///< Base name of the output data file
    };

    /// Construction and configuration
    driver(const config_type & config_);

    /// Generation of decays
    void run();

  private:
    
    config_type _config_; ///< Configuration    

  };
  
} // namespace bxdecay0

#endif // BXDECAY0_DRIVER_HPP

