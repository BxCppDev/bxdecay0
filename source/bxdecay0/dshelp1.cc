// Ourselves:
#include <bxdecay0/dshelp1.h>

// Standard library:
#include <cmath>
#include <sstream>

// This project:
#include <bxdecay0/event.h>
#include <bxdecay0/bb.h>
#include <bxdecay0/dshelp2.h>
#include <bxdecay0/dgmlt2.h>

namespace bxdecay0 {

  void decay0_dshelp1(const int m_,
                      const double * du1_,
                      double * df1_,
                      double * d_el_,
                      void * params_)
  {
    const bbpars * pars = static_cast<const bbpars *>(params_);
    const double & dens = pars->dens;
    const double & denf = pars->denf;
    for (int i = 0; i < m_; i++) {
      d_el_[0] = du1_[i];
      double d = std::max(0., dens - d_el_[0]);
      df1_[i] = decay0_dgmlt2(decay0_dshelp2, d, denf - d_el_[0],
                              16, 8 , d_el_, params_);
    }
    return;
  }

} // end of namespace bxdecay0
