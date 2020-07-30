/** \file bxdecay0/particle_utils.h
 *  \brief Utilities for generated particle
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

#ifndef BXDECAY0_PARTICLE_UTILS_H
#define BXDECAY0_PARTICLE_UTILS_H

// Standard library:
#include <string>

namespace bxdecay0 {

  /// \brief Supported particles code
  ///
  /// The particle codes are from the legacy Geant3 system
  enum particle_code
  {
    INVALID_PARTICLE = 0,  ///< Invalid particle code
    GAMMA            = 1,  ///< Gamma
    POSITRON         = 2,  ///< Positron
    ELECTRON         = 3,  ///< Electron
    NEUTRON          = 13, ///< Neutron
    PROTON           = 14, ///< Proton
    ALPHA            = 47  ///< Alpha
  };

  /// Return the name of the particle with given ID (MeV)
  std::string geant3_particle_name(const particle_code code_);

  /// Return the mass of the particle with given ID (MeV)
  double particle_mass_MeV(const particle_code code_);

  /// Return the mass of the electron (MeV)
  double electron_mass_MeV();

  /// Return the mass of the electron (MeV)
  double decay0_emass();

} // end of namespace bxdecay0

#endif // BXDECAY0_PARTICLE_UTILS_H
