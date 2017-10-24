/// \file bxdecay0/decay0.h
/* Author(s):     Francois Mauger <mauger@lpccaen.in2p3.fr>
 * Creation date: 2013-05-04
 * Last modified: 2017-06-11
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

/// Nested namespace of the bxdecay0 library
namespace bxdecay0 {

  class bbpars;

  /// \brief Decay0/GENBB generator
  class decay0_generator
    : public i_decay_generator
  {
  public:

    /// \brief Type of decay
    enum decay_type {
      DECAY_TYPE_UNDEFINED  = 0, //!< Undefined decay type
      DECAY_TYPE_DBD        = 1, //!< Double beta decay
      DECAY_TYPE_BACKGROUND = 2  //!< Radioactive background decay
    };

    /// Invalid decay mode
    static const int DBD_MODE_INVALID  = -1;
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
    void initialize();

    /// Reset
    void reset();

    /// Return a mutable set of parameters
    bxdecay0::bbpars & bb_params();

    /// Set the decay type
    void set_decay_type(const decay_type);

    /// Set the decaying isotope
    void set_decay_isotope(const std::string &);

    /// Set the decay version
    void set_decay_version(const int);

    /// Set the DBD level of the daughter nucleus
    void set_decay_dbd_level(const int);

    /// Set the DBD mode
    void set_decay_dbd_mode(const int);

    /// Set the DBD energy range (is available for the chosen mode)
    void set_decay_dbd_energy_range(const double min_, const double max_);

    /// Check if a next event is available
    virtual bool has_next() const;

    /// Shoot a decay event
    virtual void shoot(i_random & prng_, event & event_);

    /// Return the current number of generated events
    size_t get_event_count() const;

    /// Return the ratio of events in the current energy range
    double get_to_all_events() const;

  private:

    void _init_();

    void _reset_();

  private:

    // Management:
    bool   _initialized_ = false; //!< Initialization flag
    bool   _debug_       = false; //!< Debug flag

    // Configuration:
    int    _decay_type_;         //!< Type of the decay
    std::string _decay_isotope_; //!< Decaying isotope
    int    _decay_version_;      //!< Decay version
    int    _decay_dbd_level_;    //!< DBD level of the daughter nucleus
    int    _decay_dbd_mode_;     //!< DBD mode
    double _energy_min_;         //!< Minimum energy sum
    double _energy_max_;         //!< Maximum energy sum

    // Working internal data:
    size_t _event_count_; //!< Current event count
    std::unique_ptr<bxdecay0::bbpars> _bb_params_; //!< Decay parameters

  };

} // end of namespace bxdecay0

#endif // BXDECAY0_DECAY0_H

// Local Variables: --
// mode: c++ --
// End: --
