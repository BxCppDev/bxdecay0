/** \file bxdecay0/event.h
 *  \brief Generated event
 *
 * Copyright 2017 François Mauger <mauger@lpccaen.in2p3.fr>
 * Copyright 2017 Normandie Université
 *
 * This file is part of BxDecay0.
 *
 * BxDecay0 is free software: you  can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free  Software Foundation, either  version 3 of the  License, or
 * (at your option) any later version.
 *
 * BxDecay0 is distributed  in the hope that it will  be useful, but
 * WITHOUT  ANY   WARRANTY;  without  even  the   implied  warranty  of
 * MERCHANTABILITY or  FITNESS FOR A  PARTICULAR PURPOSE.  See  the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with BxDecay0.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BXDECAY0_EVENT_H
#define BXDECAY0_EVENT_H

// Standard library:
#include <vector>

// This project:
#include <bxdecay0/particle.h>
#include <bxdecay0/i_random.h>

namespace bxdecay0 {

  /// \brief Description of a generated event as an ordered list of particles
  ///
  /// An event has several atrributes:
  ///
  /// - generator : an optional generator string which may identifies the event generator responsible
  ///               of the creation of the current event,
  /// - time: an optional decay time reference which can be set externally by some activiy model
  ///         (default value: unset==NaN)
  /// - particles : a list of generated particles, ordered in time.
  ///
  /// Each particle has the following attributes:
  ///
  /// - code : the particle identifier code (using GEANT3 particle code for alpha, electron, positron,
  ///          gamma, neutron or proton),
  /// - time : the time elapsed from the previous particle or the event time reference for the first
  ///          particle (expressed in second),
  /// - momentum: an array of 3 double precision reals representing the coordinates (px, py, pz)
  ///             of the particle's momentum (expressed in MeV/c)
  ///
  class event
  {
  public:

    /// Default constructor
    event();

    /// Check if the generator is set
    bool has_generator() const;

    /// Set the generator of the event
    void set_generator(const std::string & generator_);

    /// Return the generator of the event
    const std::string & get_generator() const;

    /// Check if the reference time is set
    bool has_time() const;

    /// Set the reference time of the event (time unit: second)
    void set_time(const double time_);

    /// Return the reference time of the event (time unit: second)
    double get_time() const;

    /// Add a particle in the list of particles (append)
    void add_particle(const particle & p_);

    /// Return the ordered list of particles
    const std::vector<particle> & get_particles() const;

    /// Return a mutable reference to the last particle
    /// This method is provided only for internal usage.
    particle & grab_last_particle();

    /// Check the validity of the event
    bool is_valid() const;

    /// Shift the time of the particles by a delay (unit: second), starting from a given rank
    void shift_particles_time(double delta_time_, const int from_ = 0);

    /// Reset the event
    void reset();

    /// Print the event
    void print(std::ostream & out_ = std::clog,
               const std::string & title_ = "",
               const std::string & indent_ = "") const;

    enum store_flags {
      STORE_EVENT_DECO = (particle::STORE_LAST_FLAG << 1), ///< Flag to store some decoration comments
      STORE_EVENT_TIME = (STORE_EVENT_DECO << 1), ///< Flag to store the time of the event
      STORE_LAST_FLAG  = STORE_EVENT_TIME ///< Last supported flag
    };

    // Store the event in ASCII format
    void store(std::ostream & out_, const uint32_t flags_ = 0) const;

  private:

    std::string           _generator_; ///< Name of the generator
    double                _time_;      ///< Reference time (in second)
    std::vector<particle> _particles_; ///< List of particles (ordered in time)

  };

  /// \brief Generation of isotropical emission of particle in the range of energies and angles.
  // Input : np          - GEANT particle identification code
  //         E1,E2       - range of kinetic energy of particle (MeV);
  //         teta1,teta2 - range of teta angle (radians);
  //         phi1,phi2   - range of phi  angle (radians);
  //         tclev       - time of creation of level from which particle will be
  //                       emitted (sec);
  //         thlev       - level halflife (sec).
  // Output: tdlev       - time of decay of level (sec);
  // VIT, 15.10.1995.
  void randomize_particle(i_random & prng_, event & event_,
                          const particle_code np_, double e1_, double e2_,
                          double teta1_, double teta2_,
                          double phi1_, double phi2_,
                          double tclev_, double thlev_, double & tdlev_);

  void decay0_particle(i_random & prng_, event & event_,
                       const particle_code np_, double e1_, double e2_,
                       double teta1_, double teta2_,
                       double phi1_, double phi2_,
                       double tclev_, double thlev_, double & tdlev_);

} // end of namespace bxdecay0

#endif // BXDECAY0_EVENT_H

// Local Variables: --
// mode: c++ --
// End: --
