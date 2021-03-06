// Copyright 2020 F. Mauger
//
// This program is free software: you  can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free  Software Foundation, either  version 3 of the  License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

// Ourselves:
#include "bxdecay0_driver.hpp"

// Standard library:
#include <random>
#include <stdexcept>
#include <ctime>

// This project:
#include <bxdecay0/std_random.h>
#include <bxdecay0/event.h>       
#include <bxdecay0/version.h>      

namespace bxdecay0 {

  // static
  std::string driver::logging_to_string(const logging_type & log_)
  {
    if (log_ == LOGGING_MUTE) return "mute";
    if (log_ == LOGGING_VERBOSE) return "verbose";
    if (log_ == LOGGING_DEBUG) return "debug";
    return "";
  }
    
  // static
  driver::logging_type driver::logging_from_string(const std::string & token_)
  {
    if (token_ == logging_to_string(LOGGING_MUTE)) return LOGGING_MUTE;
    if (token_ == logging_to_string(LOGGING_VERBOSE)) return LOGGING_VERBOSE;
    if (token_ == logging_to_string(LOGGING_DEBUG)) return LOGGING_DEBUG;
    return LOGGING_UNDEFINED;
  }
 
  driver::driver(const config_type & config_)
  {
    // Sanity checks:
    if (config_.decay_category == decay0_generator:: DECAY_CATEGORY_UNDEFINED) {
      throw std::logic_error("bxdecay0::driver::ctor: Undefined decay category!");
    }
    if (config_.nuclide.empty()) {
      throw std::logic_error("bxdecay0::driver::ctor: Empty nuclide!");
    }
    if (config_.decay_category == decay0_generator:: DECAY_CATEGORY_BACKGROUND) {
      if (!background_isotopes().count(config_.nuclide)) {
        throw std::logic_error("bxdecay0::driver::ctor: Usupported background isotope '" + config_.nuclide + "'!");
      }
    } else if (config_.decay_category == decay0_generator:: DECAY_CATEGORY_DBD) {
      if (!dbd_isotopes().count(config_.nuclide)) {
        throw std::logic_error("bxdecay0::driver::ctor: Usupported DBD isotope '" + config_.nuclide + "'!");
      }
      if (config_.dbd_mode == DBDMODE_UNDEF) {
        throw std::logic_error("bxdecay0::driver::ctor: Undefined DBD mode!");
      }
      if (!std::isnan(config_.energy_min_MeV) or !std::isnan(config_.energy_max_MeV)) {
        if (!dbd_supports_esum_range(config_.dbd_mode)) {
          throw std::logic_error("bxdecay0::driver::ctor: DBD mode '"
                                 + dbd_mode_label(config_.dbd_mode) + "' does no support energy range!");
        }
      }
    }
    if (!std::isnan(config_.activity_Bq)) {
      if (config_.activity_Bq <= 0.0) {
        throw std::logic_error("bxdecay0::driver::ctor: Invalid activity value!");
      }
    }
    if (config_.basename.empty()) {
      throw std::logic_error("bxdecay0::driver::ctor: Empty basename!");
    }
    _config_ = config_;
    return;
  }

  void driver::run()
  {
    std::default_random_engine generator(_config_.seed);
    bxdecay0::std_random prng(generator);
    
    bxdecay0::decay0_generator decay0;
    decay0.set_debug(_config_.logging >= LOGGING_DEBUG);
    decay0.set_decay_category(_config_.decay_category);
    decay0.set_decay_isotope(_config_.nuclide);
    double toallevents = 1.0;
    bool use_specific_erange = false;
    if (_config_.decay_category == decay0_generator::DECAY_CATEGORY_DBD) {
      decay0.set_decay_dbd_level(_config_.level);
      decay0.set_decay_dbd_mode(_config_.dbd_mode);
      if (! std::isnan(_config_.energy_min_MeV) or !std::isnan(_config_.energy_max_MeV)) {
        // limited energy range
        double emin_MeV = 0.0;
        double emax_MeV = 5000.0;
        if (! std::isnan(_config_.energy_min_MeV)) {
          emin_MeV = _config_.energy_min_MeV;
        }
        if (! std::isnan(_config_.energy_max_MeV)) {
          emax_MeV = _config_.energy_max_MeV;
        }
        decay0.set_decay_dbd_esum_range(emin_MeV, emax_MeV);
        use_specific_erange = true;
      }
    }
    if (_config_.use_mdl) {
      bxdecay0::event_op_ptr mdlPtr(new bxdecay0::momentum_direction_lock_event_op(decay0.is_debug()));
      bxdecay0::momentum_direction_lock_event_op & mdl = dynamic_cast<bxdecay0::momentum_direction_lock_event_op&>(*mdlPtr);
      mdl.set(_config_.mdl_config);
      decay0.add_operation(mdlPtr); // Install the MDL PGOp in the generator
    }

    std::string basename = _config_.basename;
    
    // Output files for configuration informations and generated decay events:
    std::string info_filename  = basename + ".d0c";
    std::string event_filename = basename + ".d0t";
    std::ofstream fevent(event_filename.c_str());
    fevent.precision(15);
    uint32_t store_flags = bxdecay0::event::STORE_EVENT_TIME;
    std::ofstream finfo(info_filename.c_str());
    finfo.precision(15);
     
    decay0.initialize(prng);
    if (use_specific_erange) {
      toallevents = decay0.get_bb_params().toallevents;
    }
    double activity_Bq = std::numeric_limits<double>::quiet_NaN();
    if (! std::isnan(_config_.activity_Bq)) {
      activity_Bq = _config_.activity_Bq;
    }
    std::exponential_distribution<> decay_timer(activity_Bq);

    // Store config/information in the file header:
    std::time_t now_time = std::time(0);
    finfo << "library-name=BxDecay0" << std::endl;
    finfo << "library-version=" << BXDECAY0_LIB_VERSION << std::endl;
    finfo << "decay-category=" << decay0_generator::decay_category_to_label(decay0.get_decay_category()) << std::endl;
    finfo << "nuclide=" << decay0.get_decay_isotope() << std::endl;
    finfo << "seed=" << _config_.seed << std::endl;
    finfo << "time-from-epoch-s=" << now_time << std::endl;
    if (! std::isnan(activity_Bq)) {
      finfo << "activity-Bq=" << activity_Bq << std::endl;
    }
    finfo << "nb-events=" << _config_.nb_events << std::endl;
    if (_config_.decay_category == decay0_generator::DECAY_CATEGORY_DBD) {
      finfo << "dbd-daughter-level=" << decay0.get_decay_dbd_level() << std::endl;
      finfo << "dbd-mode=" << decay0.get_decay_dbd_mode() << std::endl;
      if (decay0.has_decay_dbd_esum_range()) {
        finfo << "erange-min-energy-MeV=" << decay0.get_decay_dbd_esum_range_lower() << std::endl;
        finfo << "erange-max-energy-MeV=" << decay0.get_decay_dbd_esum_range_upper() << std::endl;
        finfo << "erange-toallevents=" << toallevents << std::endl;
      }
    }
    if (decay0.get_operations().size()) {
      finfo << "pgops=";
      for (size_t iop = 0; iop < decay0.get_operations().size(); iop++) {
        std::string pgopName = decay0.get_operations()[iop]->name();
        if (_config_.use_mdl and (typeid(*decay0.get_operations()[iop]) == typeid(bxdecay0::momentum_direction_lock_event_op))) {
          pgopName = "mdl";
        }
        if (iop > 0) finfo << ", ";
        finfo << pgopName;
      }
      finfo << std::endl;
      if (_config_.use_mdl) {
        finfo << "mdl.particle_label=" << (_config_.mdl_config.particle_label.empty() ? "all" : _config_.mdl_config.particle_label) << std::endl;
        finfo << "mdl.target_particle_rank=" << _config_.mdl_config.target_particle_rank << std::endl;
        finfo << "mdl.cone_phi_degree=" << _config_.mdl_config.cone_phi_degree << std::endl;
        finfo << "mdl.cone_theta_degree=" << _config_.mdl_config.cone_theta_degree << std::endl;
        finfo << "mdl.cone_aperture_degree=" << _config_.mdl_config.cone_aperture_degree << std::endl;
      }
    }
    
    bxdecay0::event gendecay;
    // Loop on events:
    for (std::size_t ievent = 0; ievent < _config_.nb_events; ievent++) {
      decay0.shoot(prng, gendecay);
      double evtime = 0.0;
      if (! std::isnan(activity_Bq)) {
        // Randomize activity
        evtime = decay_timer(generator);
      }
      gendecay.set_time(evtime);
      if (_config_.logging >= LOGGING_DEBUG) {
        gendecay.print(std::cerr, "DBD event:", "[debug] ");
      }
      fevent << ievent << ' ';
      gendecay.store(fevent, store_flags);
      fevent << '\n';
      gendecay.reset();
      if (_config_.logging >= LOGGING_VERBOSE) {
        if ((ievent + 1) % 1000 == 0) {
          double genevfrac = (100.0 * (ievent + 1) / _config_.nb_events);
          std::clog.precision(4);
          std::clog << "[log] Number of generated decay events: " << (ievent + 1) << "/" << _config_.nb_events << " (" << genevfrac  << " %)"
                    << "\n";
        }
      }
    }
    fevent.close();
    finfo << "@status=" << "0" << std::endl;
    finfo.close();
    decay0.reset();

    if (_config_.logging >= LOGGING_VERBOSE) {
      std::clog << "[log] The following ASCII files have been generated on your system:\n";
      std::clog << "[log] - information file  : '" << info_filename << "'\n";
      std::clog << "[log] - decay events file : '" << event_filename << "'\n";
    }
   
    return;
  }

} // namespace bxdecay0
