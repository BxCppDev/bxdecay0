/// \file bxdecay0/decay0.h
/* Author(s):     Francois Mauger <mauger@lpccaen.in2p3.fr>
 * Creation date: 2013-05-04
 * Last modified: 2017-10-31
 *
 * License:
 * Copyright 2013-2017 F. Mauger
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 * Description:
 *
 *   C++ decay0 event generator.
 *
 */

#ifndef BXDECAY0_DECAY0_H
#define BXDECAY0_DECAY0_H

// Standard library:
#include <iostream>
#include <memory>

// This project:
#include <bxdecay0/i_decay_generator.h>
#include <bxdecay0/i_random.h>
#include <bxdecay0/event.h>
#include <bxdecay0/bb.h>
#include <bxdecay0/bb_utils.h>

/// Nested namespace of the bxdecay0 library
namespace bxdecay0 {

  class bbpars;

  /// \brief Decay0/GENBB generator
  class decay0_generator
    : public i_decay_generator
  {
  public:

    /// \brief Category of decay
    enum decay_category_type {
      DECAY_CATEGORY_UNDEFINED  = 0, //!< Undefined decay
      DECAY_CATEGORY_DBD        = 1, //!< Double beta decay
      DECAY_CATEGORY_BACKGROUND = 2  //!< Radioactive background decay
    };

    /// Return a label associated to a category of decay
    static std::string decay_category_to_label(const decay_category_type);

    /// Invalid daughter nuclide level
    static const int DBD_LEVEL_INVALID = -1;

    /// Default constructor
    decay0_generator();

    /// Destructor
    ~decay0_generator();

    /// Smart print
    void smart_dump(std::ostream& out = std::clog,
                    const std::string& title  = "",
                    const std::string& indent = "") const;

    /// Check initialization status
    bool is_initialized() const;

    /// Initialize
    void initialize(i_random & prng_);

    /// Reset
    void reset();

    /// Set debug flag
    void set_debug(const bool);

    /// Check if debug flag is set
    bool is_debug() const;

    /// Check if decay category is set
    bool has_decay_category() const;

    /// Set the decay category
    void set_decay_category(const decay_category_type);

    /// Return the decay category
    decay_category_type get_decay_category() const;

    /// Check if DBD decay category
    bool is_dbd() const;

    /// Check if background decay category
    bool is_background() const;

    /// Check if decay isotope is set
    bool has_decay_isotope() const;

    /// Set the decaying isotope
    void set_decay_isotope(const std::string &);

    /// Return the decaying isotope
    const std::string & get_decay_isotope() const;

    /// Check if decay version is set
    bool has_decay_version() const;

    /// Set the decay version
    void set_decay_version(const std::string &);

    /// Check if decay dbd mode is set
    bool has_decay_dbd_mode() const;

    /// Set the DBD mode
    void set_decay_dbd_mode(const modebb_type);

    /// Return the DBD mode
    modebb_type get_decay_dbd_mode() const;

    /// Check if decay dbd level is set
    bool has_decay_dbd_level() const;

    /// Set the DBD level of the daughter nucleus
    void set_decay_dbd_level(const int);

    /// Return the DBD level of the daughter nucleus
    int get_decay_dbd_level() const;

    /// Check if decay dbd esum range is set
    bool has_decay_dbd_esum_range() const;

    /// Set the DBD energy sum range (is available for the chosen mode)
    void set_decay_dbd_esum_range(const double min_, const double max_);

    /// Return the DBD energy sum range lower bound
    double get_decay_dbd_esum_range_lower() const;

    /// Return the DBD energy sum range upper bound
    double get_decay_dbd_esum_range_upper() const;

    /// Check if a next event is available
    virtual bool has_next() const;

    /// Shoot a decay event
    virtual void shoot(i_random & prng_, event & event_);

    /// Return the current number of generated events
    size_t get_event_count() const;

    /// Return the ratio of events in the current energy range
    double get_to_all_events() const;

    /// Return a non mutable set of parameters
    const bxdecay0::bbpars & get_bb_params() const;

  private:

    /// Return a mutable set of parameters
    bxdecay0::bbpars & _grab_bb_params_();

    void _set_defaults_();

    void _init_(i_random & prng_);

    void _reset_();

  private:

    // Management:
    bool   _initialized_ = false; //!< Initialization flag
    bool   _debug_       = false; //!< Debug flag

    // Configuration:
    decay_category_type  _decay_category_; //!< Category of the decay
    std::string _decay_isotope_;           //!< Decaying isotope
    std::string _decay_version_;           //!< Decay version
    int         _decay_dbd_level_;         //!< DBD level of the daughter nucleus
    modebb_type _decay_dbd_mode_;          //!< DBD mode
    double      _energy_min_;              //!< Minimum energy sum
    double      _energy_max_;              //!< Maximum energy sum

    // Working internal data:
    size_t _event_count_; //!< Current event count
    std::unique_ptr<bxdecay0::bbpars> _bb_params_; //!< Decay parameters

  };

} // end of namespace bxdecay0

#endif // BXDECAY0_DECAY0_H

// Local Variables: --
// mode: c++ --
// End: --
