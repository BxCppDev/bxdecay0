// Copyright 2017 F. Mauger
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
#include <bxdecay0/particle_utils.h>

// Standard library:
#include <limits>

namespace bxdecay0 {

  std::string geant3_particle_name(const particle_code code_)
  {
    switch(code_) {
    case GAMMA: return std::string("gamma");
    case POSITRON: return std::string("positron");
    case ELECTRON: return std::string("electron");
    case NEUTRON: return std::string("neutron");
    case PROTON: return std::string("proton");
    case ALPHA: return std::string("alpha");
    default: return std::string();
    }
  }

  double particle_mass_MeV(const particle_code code_)
  {
    switch(code_) {
    case GAMMA    : return 0.;
    case POSITRON : return 0.51099906;
    case ELECTRON : return 0.51099906;
    case NEUTRON  : return 939.56563;
    case PROTON   : return 938.27231;
    case ALPHA    : return 3727.417;
    default       : return std::numeric_limits<double>::quiet_NaN();
    }
  }

  double electron_mass_MeV()
  {
    return particle_mass_MeV(ELECTRON);
  }

  double decay0_emass()
  {
    return electron_mass_MeV();
  }

} // end of namespace bxdecay0
