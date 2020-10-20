/** \file bxdecay0/particle.h
 *  \brief Generated particle
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

#ifndef BXDECAY0_PARTICLE_H
#define BXDECAY0_PARTICLE_H

// Standard library:
#include <iostream>
#include <string>

// This project:
#include <bxdecay0/particle_utils.h>

namespace bxdecay0 {

  /// \brief Description of a particle with emission informations (time+kinematics)
  class particle
  {
  public:
    /// Default constructor
    particle();

    /// Check if code is valid
    bool has_code() const;

    /// Set the particle code
    void set_code(const particle_code code_);

    /// Return the particle code
    particle_code get_code() const;

    /// Check if particle is an alpha
    bool is_alpha() const;

    /// Check if particle is a positron
    bool is_positron() const;

    /// Check if particle is an electron
    bool is_electron() const;

    /// Check if particle is a neutron
    bool is_neutron() const;

    /// Check if particle is a proton
    bool is_proton() const;

    /// Check if particle is a gamma
    bool is_gamma() const;

    /// Check if time is valid
    bool has_time() const;

    /// Set the delay time with respect to the previous particle (unit: second)
    void set_time(const double time_);

    /// Shift the delay time with a delay (unit: second)
    void shift_time(const double delay_);

    /// Return the delay time with respect to the previous particle (unit: second)
    double get_time() const;

    /// Set the X coordinate of the momentum (unit: MeV/c or MeV with c=1)
    void set_px(const double px_);

    /// Return the X coordinate of the momentum (unit: MeV/c or MeV with c=1)
    double get_px() const;

    /// Set the Y coordinate of the momentum (unit: MeV/c or MeV with c=1)
    void set_py(const double py_);

    /// Return the Y coordinate of the momentum (unit: MeV/c or MeV with c=1)
    double get_py() const;

    /// Set the Z coordinate of the momentum (unit: MeV/c or MeV with c=1)
    void set_pz(const double pz_);

    /// Return the Z coordinate of the momentum (unit: MeV/c or MeV with c=1)
    double get_pz() const;

    /// Check if momentum is valid
    bool has_momentum() const;

    /// Set the coordinates of the momentum (unit: MeV/c)
    void set_momentum(const double px_, const double py_, const double pz_);

    /// Return the magnitude of the momentum (unit: MeV/c or MeV with c=1)
    double get_p() const;

    /// Check the validity of the particle
    bool is_valid() const;

    /// Reset the particle attributes
    void reset();

    /// Print the particle
    void print(std::ostream & out_         = std::clog,
               const std::string & title_  = "",
               const std::string & indent_ = "") const;

    enum store_flags
    {
      STORE_PARTICLE_NAME = 0x1,                ///< Flag to store the name of the particle
      STORE_LAST_FLAG     = STORE_PARTICLE_NAME ///< Last supported flag
    };

    // Store the particle in ASCII format
    void store(std::ostream & out_, const uint32_t flags_ = 0) const;

  private:
    particle_code _code_; ///< Particle code
    double _time_;        ///< Particle generation delay time after the previous particle in the event (unit: second)
    double _momentum_[3]; ///< Particle momentum (unit: MeV/c)
  };

} // end of namespace bxdecay0

#endif // BXDECAY0_PARTICLE_H

// Local Variables: --
// mode: c++ --
// End: --
