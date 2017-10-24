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
