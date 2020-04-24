// Copyright 2013-2017 F. Mauger
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
// decay0_generator.cc

// Ourselves:
#include <bxdecay0/decay0_generator.h>

// Standard library:
#include <stdexcept>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

// This project:
#include <bxdecay0/event.h>
#include <bxdecay0/bb.h>
#include <bxdecay0/genbbsub.h>
#include <bxdecay0/version.h>
#include <bxdecay0/dbd_gA.h>

namespace bxdecay0 {

  /// \brief PIMPL type
  struct decay0_generator::pimpl_type {
    pimpl_type() = default;
    ~pimpl_type() {
      if (dbd_ga_process.is_initialized()) {
        dbd_ga_process.reset();
      }
    }
    // Attributes:
    size_t event_count = 0; //!< Current event count
    bbpars bb_params;       //!< Decay0 parameters
    bool   use_dbd_ga = false; //!< Flag to use the DBD gA generator
    dbd_gA dbd_ga_process;  //!< DBD gA generator    
  };
  
  void decay0_generator::pimpl_deleter_type::operator()(decay0_generator::pimpl_type * ptr_) const
  {
    delete ptr_;
    return;
  }

  // static
  const int decay0_generator::DBD_LEVEL_INVALID;

  // static
  std::string decay0_generator::decay_category_to_label(const decay_category_type cat_)
  {
    switch(cat_) {
    case DECAY_CATEGORY_DBD : return std::string("dbd");
    case DECAY_CATEGORY_BACKGROUND : return std::string("background");
    default: return std::string("");
    }
  }

  void decay0_generator::_set_defaults_()
  {
    _decay_category_ = DECAY_CATEGORY_UNDEFINED;
    _decay_isotope_ = "";
    _decay_version_ = "";
    _decay_dbd_level_ = DBD_LEVEL_INVALID;
    _decay_dbd_mode_ = DBDMODE_UNDEF;
    _energy_min_ = std::numeric_limits<double>::quiet_NaN();
    _energy_max_ = std::numeric_limits<double>::quiet_NaN();
    return;
  }

  decay0_generator::decay0_generator()
  {
    _initialized_ = false;
    _debug_       = false;
    _set_defaults_();
    _pimpl_.reset(new pimpl_type);
    return;
  }

  decay0_generator::~decay0_generator()
  {
    if (_initialized_) {
      reset();
    }
    _pimpl_.reset();
    return;
  }

  void decay0_generator::set_debug(const bool flag_)
  {
    _debug_ = flag_;
    return;
  }

  bool decay0_generator::is_debug() const
  {
    return _debug_;
  }

  void decay0_generator::smart_dump(std::ostream & out_,
                                    const std::string & title_,
                                    const std::string & indent_) const
  {
    if (!title_.empty()) {
      out_ << indent_ << title_ << std::endl;
    }
    static const std::string tag = "|-- ";
    static const std::string last_tag = "`-- ";
    static const std::string skip_tag = "|   ";
    static const std::string last_skip_tag = "    ";
    out_ << indent_ << tag
         << "Decay category   : '" << decay_category_to_label(_decay_category_) << "'" << std::endl;
    out_ << indent_ << tag
         << "Decay isotope    : '" << _decay_isotope_ << "'" << std::endl;
    out_ << indent_ << tag
         << "Decay version    : '" << _decay_version_ << "'" << std::endl;
    if (is_dbd()) {
      out_ << indent_ << tag
           << "Decay DBD level  : " << _decay_dbd_level_ << std::endl;
      out_ << indent_ << tag
           << "Decay DBD mode   : " << _decay_dbd_mode_ << std::endl;
      if (!std::isnan(_energy_min_)) {
        out_ << indent_ << tag
             << "Energy min       : " << _energy_min_ << " MeV" << std::endl;
      }
      if (!std::isnan(_energy_max_)) {
        out_ << indent_ << tag
             << "Energy max       : " << _energy_max_ << " MeV" << std::endl;
      }
    }
    out_ << indent_ << tag
         << "Event count      : " << _pimpl_->event_count << std::endl;

    out_ << indent_ << last_tag
         << "Initialized      : " << std::boolalpha << _initialized_ << std::endl;
    if (_initialized_ && is_dbd()) {
      out_ << indent_ << last_skip_tag << last_tag
           << "DBD working data : " << std::endl;
      std::ostringstream indent_pars_oss;
      indent_pars_oss << indent_ << last_skip_tag << last_skip_tag;
      _pimpl_->bb_params.dump(out_, indent_pars_oss.str());
    }
    return;
  }

  bool decay0_generator::is_initialized() const
  {
    return _initialized_;
  }

  void decay0_generator::initialize(i_random & prng_)
  {
    if (is_debug()) std::cerr << "[debug] decay0_generator::initialize: Entering..." << std::endl;
    if (is_initialized()) {
      throw std::logic_error("bxdecay0::decay0_generator::initialize: Decay0 generator is already initialized!");
    }

    if (_decay_category_ == DECAY_CATEGORY_UNDEFINED) {
      throw std::logic_error("bxdecay0::decay0_generator::initialize: Decay0 generator type is not defined!");
    }

    if (_decay_isotope_.empty()) {
      throw std::logic_error("bxdecay0::decay0_generator::initialize: DBD isotope is not defined!");
    }

    if (_decay_category_ == DECAY_CATEGORY_DBD) {
      const std::map<dbd_mode_type,dbd_record> & dbd_modes_dict = dbd_modes();
      if (is_debug()) {
        for (const auto & md : dbd_modes_dict) {
          std::cerr << "[debug] " << "decay0_generator::initialize: "
                    << "DBD modes : " << md.first << " : " << md.second.description << std::endl;
        }
      }
      if (dbd_modes_dict.count(_decay_dbd_mode_) == 0) {
        throw std::logic_error("bxdecay0::decay0_generator::initialize: Invalid DBD mode!");
      }
      if (_decay_dbd_level_ == DBD_LEVEL_INVALID) {
        throw std::logic_error("bxdecay0::decay0_generator::initialize: DBD daughter level is not defined!");
      }

      if (!std::isnan(_energy_max_)) {
        if (_energy_min_ >= _energy_max_) {
          throw std::logic_error("bxdecay0::decay0_generator::initialize: Invalid energy range !");
        }
      }
    }
    _init_(prng_);

    _initialized_ = true;
    if (is_debug()) std::cerr << "[debug] decay0_generator::initialize: Exiting." << std::endl;
    return;
  }

  void decay0_generator::reset()
  {
    if (is_debug()) std::cerr << "[debug] decay0_generator::reset: Entering..." << std::endl;
    if (! _initialized_) {
      return;
    }
    _initialized_ = false;
    _reset_();
    if (is_debug()) std::cerr << "[debug] decay0_generator::reset: Exiting." << std::endl;
    return;
  }

  const bxdecay0::bbpars & decay0_generator::get_bb_params() const
  {
    decay0_generator * mutable_this = const_cast<decay0_generator*>(this);
    return const_cast<bxdecay0::bbpars&>(mutable_this->_grab_bb_params_());
  }

  bxdecay0::bbpars & decay0_generator::_grab_bb_params_()
  {
    return _pimpl_->bb_params;
  }

  bool decay0_generator::has_decay_category() const
  {
    return _decay_category_ != DECAY_CATEGORY_UNDEFINED;
  }

  void decay0_generator::set_decay_category(const decay_category_type category_)
  {
    _decay_category_ = category_;
    return;
  }

  decay0_generator::decay_category_type decay0_generator::get_decay_category() const
  {
    return _decay_category_;
  }

  bool decay0_generator::is_dbd() const
  {
    return _decay_category_ == DECAY_CATEGORY_DBD;
  }

  bool decay0_generator::is_background() const
  {
    return _decay_category_ == DECAY_CATEGORY_BACKGROUND;
  }

  bool decay0_generator::has_decay_isotope() const
  {
    return !_decay_isotope_.empty();
  }

  void decay0_generator::set_decay_isotope(const std::string & i_)
  {
    _decay_isotope_ = i_;
    return;
  }

  const std::string & decay0_generator::get_decay_isotope() const
  {
    return _decay_isotope_;
  }

  bool decay0_generator::has_decay_version() const
  {
    return !_decay_version_.empty();
  }

  void decay0_generator::set_decay_version(const std::string & ver_)
  {
    _decay_version_ = ver_;
    return;
  }

  bool decay0_generator::has_decay_dbd_level() const
  {
    return _decay_dbd_level_ != DBD_LEVEL_INVALID;
  }

  void decay0_generator::set_decay_dbd_level(const int level_)
  {
    _decay_dbd_level_ = level_;
    return;
  }

  int decay0_generator::get_decay_dbd_level() const
  {
    return _decay_dbd_level_;
  }

  bool decay0_generator::has_decay_dbd_mode() const
  {
    return _decay_dbd_mode_ != DBDMODE_UNDEF;
  }

  void decay0_generator::set_decay_dbd_mode_by_label(const std::string & dbd_mode_label_)
  {
    set_decay_dbd_mode(dbd_mode_from_label(dbd_mode_label_));
    return;
  }

  void decay0_generator::set_decay_dbd_mode(const dbd_mode_type mode_)
  {
    _decay_dbd_mode_ = mode_;
    return;
  }

  dbd_mode_type decay0_generator::get_decay_dbd_mode() const
  {
    return _decay_dbd_mode_;
  }

  bool decay0_generator::has_decay_dbd_esum_range() const
  {
    return (_energy_min_ == _energy_min_) && (_energy_max_ == _energy_max_);
  }

  void decay0_generator::set_decay_dbd_esum_range(const double emin_, const double emax_)
  {
    _energy_min_ = emin_;
    _energy_max_ = emax_;
    return;
  }

  double decay0_generator::get_decay_dbd_esum_range_lower() const
  {
    return _energy_min_;
  }

  double decay0_generator::get_decay_dbd_esum_range_upper() const
  {
    return _energy_max_;
  }

  // virtual
  bool decay0_generator::has_next() const
  {
    return true;
  }

  void decay0_generator::shoot(i_random & prng_, event & event_)
  {
    if (is_debug()) std::cerr << "[debug] decay0_generator::shoot: Entering..." << std::endl;
    if (! is_initialized()) {
      throw std::logic_error("bxdecay0::decay0_generator::shoot: Decay0 generator is not initialized !");
    }
    event_.reset();

    int error = 0;
    if (_decay_category_ == DECAY_CATEGORY_DBD) {
      if (_pimpl_->use_dbd_ga) {
        _pimpl_->dbd_ga_process.shoot(prng_, event_);     
      } else {
        bxdecay0::genbbsub(prng_,
                           event_,
                           bxdecay0::GENBBSUB_I2BBS_DBD,
                           _decay_isotope_,
                           _decay_dbd_level_,
                           _decay_dbd_mode_,
                           bxdecay0::GENBBSUB_ISTART_GENERATE,
                           error,
                         _grab_bb_params_());
        if (error != 0) {
          throw std::logic_error("bxdecay0::decay0_generator::shoot: genbbsub DBD generation failed !");
        }
      }
    } else if (_decay_category_ == DECAY_CATEGORY_BACKGROUND) {
      bxdecay0::genbbsub(prng_,
                         event_,
                         bxdecay0::GENBBSUB_I2BBS_BACKGROUND,
                         _decay_isotope_,
                         -1,
                         -1,
                         bxdecay0::GENBBSUB_ISTART_GENERATE,
                         error,
                         _grab_bb_params_());
      if (error != 0) {
        throw std::logic_error("bxdecay0::decay0_generator::shoot: genbbsub background generation failed !");
      }
    }
    _pimpl_->event_count++;
    if (is_debug()) std::cerr << "[debug] decay0_generator::shoot: Exiting." << std::endl;
    return;
  }

  size_t decay0_generator::get_event_count() const
  {
    return _pimpl_->event_count;
  }

  double decay0_generator::get_to_all_events() const
  {
    return _pimpl_->bb_params.toallevents;
  }

  void decay0_generator::_reset_()
  {
    _pimpl_->event_count = 0;
    _pimpl_->bb_params.reset();
    if (_pimpl_->use_dbd_ga) {
      if (_pimpl_->dbd_ga_process.is_initialized()) {
        _pimpl_->dbd_ga_process.reset();
      }
    }
    _pimpl_->use_dbd_ga = false;
    _set_defaults_();
    return;
  }

  void decay0_generator::_init_(i_random & prng_)
  {
    {
      bbpars raz;
      _pimpl_->bb_params = raz;
    }
    if (_decay_version_.empty()) {
      set_decay_version(BXDECAY0_LIB_VERSION);
    }
    _grab_bb_params_().reset();
    if (_decay_category_ == DECAY_CATEGORY_DBD) {
      if ((_decay_dbd_mode_ == DBDMODE_2NUBB_GA_G0)
          or (_decay_dbd_mode_ == DBDMODE_2NUBB_GA_G2)
          or (_decay_dbd_mode_ == DBDMODE_2NUBB_GA_G22)
          or (_decay_dbd_mode_ == DBDMODE_2NUBB_GA_G4)) {
        // Special DBD gA modes:
        _pimpl_->dbd_ga_process.set_nuclide(_decay_isotope_);
        if (_decay_dbd_mode_ == DBDMODE_2NUBB_GA_G0) {
          _pimpl_->dbd_ga_process.set_process(dbd_gA::PROCESS_G0);
        } else if (_decay_dbd_mode_ == DBDMODE_2NUBB_GA_G2) {
          _pimpl_->dbd_ga_process.set_process(dbd_gA::PROCESS_G2);
        } else if (_decay_dbd_mode_ == DBDMODE_2NUBB_GA_G22) {
          _pimpl_->dbd_ga_process.set_process(dbd_gA::PROCESS_G22);
        } else if (_decay_dbd_mode_ == DBDMODE_2NUBB_GA_G4) {
          _pimpl_->dbd_ga_process.set_process(dbd_gA::PROCESS_G4);
        }
        if (_decay_dbd_level_ != 0) {
          throw std::logic_error("bxdecay0::decay0_generator::_init_: Unsupported level of the daughter nucleus!");
        }
        _pimpl_->dbd_ga_process.set_shooting(dbd_gA::SHOOTING_INVERSE_TRANSFORM_METHOD);
        _pimpl_->use_dbd_ga = true;
      } else {
        // Set the BB mode with the proper legacy value from the Decay0 engine:
        _grab_bb_params_().modebb  = dbd_legacy_mode(_decay_dbd_mode_);
        _grab_bb_params_().istartbb = 0;

        const std::set<dbd_mode_type> & dbdmwer = dbd_modes_with_esum_range();
        if (is_debug()) {
          std::cerr << "[debug] decay0_generator::_init_: " << "Decay DBD mode : " << _decay_dbd_mode_ << std::endl;
        }
        if (dbd_supports_esum_range(_decay_dbd_mode_)) {
          if (!std::isnan(_energy_min_)) {
            if (is_debug()) {
              std::cerr << "[debug] decay0_generator::_init_: " << "Setting DBD energy min to "
                        << _energy_min_ << " MeV" << std::endl;
            }
            _grab_bb_params_().ebb1 = (float) _energy_min_;
          }
          if (!std::isnan(_energy_max_)) {
            if (is_debug()) {
              std::cerr << "[debug] decay0_generator::_init_: " << "Setting DBD energy max to "
                        << _energy_max_ << " MeV" << std::endl;
            }
            _grab_bb_params_().ebb2 = (float) _energy_max_;
          }
          if (_grab_bb_params_().ebb1 >= _grab_bb_params_().ebb2) {
            throw std::logic_error("bxdecay0::decay0_generator::_init_: Invalid DBD energy range (Emin="
                                   + std::to_string(_grab_bb_params_().ebb1)
                                   + " >= Emax=" + std::to_string(_grab_bb_params_().ebb2) + ") (MeV) !");
          }
        } else {
          if (is_debug()) {
            std::cerr << "[debug] decay0_generator::_init_: " << "Not a DBD energy range mode." << std::endl;
          }
        }
      }
    }

    int error = 0;
    if (_decay_category_ == DECAY_CATEGORY_DBD) {
      if (_pimpl_->use_dbd_ga) {
        _pimpl_->dbd_ga_process.initialize();
      } else {
        if (is_debug()) std::cerr << "[debug] decay0_generator::_init_: DBD event..." << std::endl;
        event dummy_event;
        bxdecay0::genbbsub(prng_,
                           dummy_event,
                           bxdecay0::GENBBSUB_I2BBS_DBD,
                           _decay_isotope_,
                           _decay_dbd_level_,
                           _decay_dbd_mode_,
                           bxdecay0::GENBBSUB_ISTART_INIT, // initialization without event generation
                           error,
                           _grab_bb_params_());
        if (error != 0) {
          throw std::logic_error("bxdecay0::decay0_generator::_init_: genbbsub DBD initialization failed !");
        }
      }
    } else if (_decay_category_ == DECAY_CATEGORY_BACKGROUND) {
      if (is_debug()) std::cerr << "[debug] decay0_generator::_init_: background event..." << std::endl;
      event dummy_event;
      bxdecay0::genbbsub(prng_,
                         dummy_event,
                         bxdecay0::GENBBSUB_I2BBS_BACKGROUND,
                         _decay_isotope_,
                         -1,
                         -1,
                         bxdecay0::GENBBSUB_ISTART_INIT, // initialization without event generation
                         error,
                         _grab_bb_params_());
      if (error != 0) {
        throw std::logic_error("bxdecay0::decay0_generator::_init_: genbbsub background initialization failed !");
      }
    }
    return;
  }

} // end of namespace bxdecay0
