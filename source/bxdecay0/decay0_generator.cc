// decay0_generator.cc
/*
 * Copyright 2013-2017 F. Mauger
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public 3.0 License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public 3.0 License for more details.
 *
 * You should have received a copy of the GNU General Publi * License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

// Ourselves:
#include <bxdecay0/decay0_generator.h>

// Standard library:
#include <stdexcept>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

// This project:
#include <bxdecay0/genbb_utils.h>
#include <bxdecay0/event.h>
#include <bxdecay0/bb.h>
#include <bxdecay0/genbbsub.h>

namespace bxdecay0 {

  // static
  const int bxdecay0::DBD_MODE_INVALID;
  const int bxdecay0::DBD_LEVEL_INVALID;

  decay0_generator::decay0_generator()
  {
    _initialized_ = false;
    _debug_       = false;
    _decay_type_ = DECAY_TYPE_UNDEFINED;
    _decay_isotope_ = "";
    _decay_version_ = 0;
    _decay_dbd_level_ = DBD_LEVEL_INVALID;
    _decay_dbd_mode_ = DBD_MODE_INVALID;
    _energy_min_ = std::numeric_limits<double>::quiet_NaN();
    _energy_max_ = std::numeric_limits<double>::quiet_NaN();
    _event_count_ = 0;
    return;
  }

  decay0_generator::~decay0_generator()
  {
    if (_initialized_) {
      reset();
    }
    return;
  }

  void decay0_generator::smart_dump(std::ostream & out_,
                                    const std::string & title_,
                                    const std::string & indent_) const
  {
    static const std::string tag = "|-- ";
    static const std::string last_tag = "`-- ";
    static const std::string skip_tag = "|   ";
    static const std::string last_skip_tag = "    ";
    out_ << indent_ << tag
          << "Decay type       : " << _decay_type_ << std::endl;
    out_ << indent_ << tag
          << "Decay isotope    : '" << _decay_isotope_ << "'" << std::endl;
    out_ << indent_ << tag
          << "Decay DBD level  : " << _decay_dbd_level_ << std::endl;
    out_ << indent_ << tag
          << "Decay DBD mode   : " << _decay_dbd_mode_ << std::endl;
    if (!std::isnan(_energy_min_)) {
      out_ << indent_ << tag
           << "Energy min        : " << _energy_min_ << " MeV" << std::endl;
    }
    if (!std::isnan(_energy_max_)) {
      out_ << indent_ << tag
           << "Energy max        : " << _energy_max_ << " MeV" << std::endl;
    }
    out_ << indent_ << last_tag
         << "Event count        : " << _event_count_ << std::endl;
    return;
  }

  bool decay0_generator::is_initialized() const
  {
    return _initialized_;
  }

  void decay0_generator::initialize()
  {
    if (is_initialized()) {
      throw std::logic_error("bxdecay0::decay0_generator::initialize: Decay0 generator is already initialized!");
    }

    if (_decay_type_ == DECAY_TYPE_UNDEFINED) {
      throw std::logic_error("bxdecay0::decay0_generator::initialize: Decay0 generator type is not defined!");
    }

    if (_decay_isotope_.empty()) {
      throw std::logic_error("bxdecay0::decay0_generator::initialize: DBD isotope is not defined!");
    }

    if (_decay_type_ == DECAY_TYPE_DBD) {
      if (_decay_dbd_level_ == DBD_LEVEL_INVALID) {
        throw std::logic_error("bxdecay0::decay0_generator::initialize: DBD daughter level is not defined!");
      }
      if (_decay_dbd_mode_ == DBD_MODE_INVALID) {
        throw std::logic_error("bxdecay0::decay0_generator::initialize: DBD daughter level is not defined!");
      }

      // const std::vector<int> & dbdmwer
      //   = utils::get_dbd_modes_with_energy_range();
      // if (std::find(dbdmwer.begin(), dbdmwer.end(),_decay_dbd_mode_) != dbdmwer.end()) {

      //   if (config_.has_key("energy_max")) {
      //     emax = config_.fetch_real ("energy_max");
      //     DT_THROW_IF (emax < 0.0, std::logic_error, "Invalid maximum value !");
      //     if (! config_.has_explicit_unit("energy_max")) emax *= energy_unit;
      //     _energy_max_ = emax;
      //   }

      //   if (config_.has_key ("energy_min")) {
      //     emin = config_.fetch_real ("energy_min");
      //     DT_THROW_IF (emin < 0.0, std::logic_error, "Invalid minimum value !");
      //     if (! config_.has_explicit_unit("energy_min")) emin *= energy_unit;
      //     _energy_min_ = emin;
      //   }

      // }
    }

    if (!std::isnan(_energy_max_)) {
      if (_energy_min_ >= _energy_max_) {
        throw std::logic_error("bxdecay0::decay0_generator::initialize: Invalid energy range !");
      }
    }
    _init_();

    _initialized_ = true;
    return;
  }

  void decay0_generator::reset()
  {
    if (! _initialized_) {
      return;
    }
    _initialized_ = false;
    _reset_();
    return;
  }

  bxdecay0::bbpars & decay0_generator::bb_params()
  {
    return *_bb_params_.get();
  }

  void decay0_generator::set_decay_type(const decay_type type_)
  {
    _decay_type_ = type_;
    return;
  }

  void decay0_generator::set_decay_isotope(const std::string & i_)
  {
    _decay_isotope_ = i_;
    return;
  }

  void decay0_generator::set_decay_version(const int ver_)
  {
    _decay_version_ = ver_;
    return;
  }

  void decay0_generator::set_decay_dbd_level(const int level_)
  {
    _decay_dbd_level_ = devel_;
    return;
  }

  void decay0_generator::set_decay_dbd_mode(const int mode_)
  {
    _decay_dbd_mode_ = mode_;
    return;
  }

  void decay0_generator::set_decay_dbd_energy_range(const double emin_, const double emax_)
  {
    _energy_min_ = emin_;
    _energy_max_ = emax_;
    return;
  }

  // virtual
  bool decay0_generator::has_next() const
  {
    return true;
  }

  void decay0_generator::shoot(i_random & prng_, event & event_)
  {
    if (! is_initialized()) {
      throw std::logic_error("bxdecay0::decay0_generator::shoot: Decay0 geenerator is not initialized !");
    }
    event_.reset();

    int error = 0;
    if (_decay_type_ == DECAY_TYPE_DBD) {
      bxdecay0::genbbsub(prng_,
                         event_,
                         bxdecay0::GENBBSUB_I2BBS_DBD,
                         _decay_isotope_,
                         _decay_dbd_level_,
                         _decay_dbd_mode_,
                         bxdecay0::GENBBSUB_ISTART_GENERATE,
                         error,
                         bb_params());
      if (error != 0) {
        throw std::logic_error("bxdecay0::decay0_generator::shoot: genbbsub DBD generation failed !");
      }
    } else if (_decay_type_ == DECAY_TYPE_BACKGROUND) {
      bxdecay0::genbbsub(prng_,
                         event_,
                         bxdecay0::GENBBSUB_I2BBS_BACKGROUND,
                         _decay_isotope_,
                         -1,
                         -1,
                         bxdecay0::GENBBSUB_ISTART_GENERATE,
                         error,
                         bb_params());
      if (error != 0) {
        throw std::logic_error("bxdecay0::decay0_generator::shoot: genbbsub background generation failed !");
      }
    }
    _event_count_++;
    return;
  }

  size_t decay0_generator::get_event_count() const
  {
    return _event_count_;
  }

  double decay0_generator::get_to_all_events() const
  {
    return _bb_params_.get()->toallevents;
  }

  void decay0_generator::_reset_()
  {
    _event_count_ = 0;
    if (_bb_params_.get() != 0) {
      _bb_params_.get()->reset();
      _bb_params_.reset(0);
    }
    _decay_type_ = DECAY_TYPE_UNDEFINED;
    _decay_isotope_ = "";
    _decay_version_ = 0;
    _decay_dbd_level_ = DBD_LEVEL_INVALID;
    _decay_dbd_mode_ = DBD_MODE_INVALID;
    _energy_min_ = std::numeric_limits<double>::quiet_NaN();
    _energy_max_ = std::numeric_limits<double>::quiet_NaN();
    return;
  }

  void decay0_generator::_init_()
  {
    _bb_params_.reset(new bxdecay0::bbpars);

    bb_params().reset();
    if (_decay_type_ == DECAY_TYPE_DBD) {
      bb_params().modebb   = _decay_dbd_mode_;
      bb_params().istartbb = 0;

      const std::vector<int> & dbdmwer
        = utils::get_dbd_modes_with_energy_range ();
      if (_debug_) {
        std::clog << "[debug] " << "Decay DBD mode : " << _decay_dbd_mode_ << std::endl;
      }
      if (std::find (dbdmwer.begin (), dbdmwer.end (), _decay_dbd_mode_) != dbdmwer.end ()) {
        if (!std::isnan(_energy_min_)) {
          if (_debug_) {
            std::clog << "[debug] " << "Setting DBD energy min to "
                      << _energy_min_ << " MeV" << std::endl;
          }
          bb_params().ebb1 = (float) _energy_min_;
        }
        if (!std::isnan(_energy_max_)) {
          if (_debug_) {
            std::clog << "[debug] " << "Setting DBD energy max to "
                      << _energy_max_ << " MeV" << std::endl;
          }
          bb_params().ebb2 = (float) _energy_max_;
        }
        if (bb_params().ebb1 >= bb_params().ebb2) {
          throw std::logic_error("bxdecay0::decay0_generator::_init_: Invalid DBD energy range (Emin=" << bb_params().ebb1 << " >= Emax=" << bb_params().ebb2 << ") (MeV) !");
        }
      } else {
        if (_debug_) {
          std::cerr << "[debug] " << "Not a DBD energy range mode." << std::endl;
        }
      }
    }

    int error = 0;
    if (_decay_type_ == DECAY_TYPE_DBD) {
      event dummy_event;
      bxdecay0::genbbsub(prng_,
                       dummy_event,
                       bxdecay0::GENBBSUB_I2BBS_DBD,
                       _decay_isotope_,
                       _decay_dbd_level_,
                       _decay_dbd_mode_,
                       bxdecay0::GENBBSUB_ISTART_INIT, // initialization without event generation
                       error,
                       bb_params());
      if (error != 0) {
        throw std::logic_error("bxdecay0::decay0_generator::_init_: genbbsub DBD initialization failed !");
      }
    } else if (_decay_type_ == DECAY_TYPE_BACKGROUND) {
      event dummy_event;
      bxdecay0::genbbsub(prng_,
                       dummy_event,
                       bxdecay0::GENBBSUB_I2BBS_BACKGROUND,
                       _decay_isotope_,
                       -1,
                       -1,
                       bxdecay0::GENBBSUB_ISTART_INIT, // initialization without event generation
                       error,
                       bb_params());
      if (error != 0) {
        throw std::logic_error("bxdecay0::decay0_generator::_init_: genbbsub background initialization failed !");
      }
    }
    return;
  }

} // end of namespace bxdecay0
