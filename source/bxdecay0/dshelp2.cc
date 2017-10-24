// Ourselves:
#include <bxdecay0/dshelp2.h>

// Standard library:
#include <cmath>
#include <sstream>

// This project:
#include <bxdecay0/event.h>
#include <bxdecay0/bb.h>
#include <bxdecay0/dshelp1.h>
#include <bxdecay0/dgmlt2.h>
#include <bxdecay0/fe12_mods.h>

namespace bxdecay0 {

  void decay0_dshelp2(const int m_,
                      const double * du2_,
                      double * df2_,
                      double * d_el_,
                      void * params_)
  {
    bbpars * pars = static_cast<bbpars *>(params_);
    const double & dens = pars->dens;
    const double & denf = pars->denf;
    const int &    mode = pars->mode;
    double & e0         = pars->e0;
    double & e1         = pars->e1;
    for (int i = 0; i < m_; i++) {
      d_el_[1] = du2_[i];
      e1 = d_el_[0];
      double e2 = d_el_[1];
      df2_[i] = 0.0;
      if (e1 > 0. && e2 > 0. && e1 + e2 < e0) {
        if (mode == MODEBB_4)  df2_[i] = decay0_fe12_mod4(e2, params_);
        if (mode == MODEBB_5)  df2_[i] = decay0_fe12_mod5(e2, params_);
        if (mode == MODEBB_6)  df2_[i] = decay0_fe12_mod6(e2, params_);
        if (mode == MODEBB_8)  df2_[i] = decay0_fe12_mod8(e2, params_);
        if (mode == MODEBB_13) df2_[i] = decay0_fe12_mod13(e2, params_);
        if (mode == MODEBB_14) df2_[i] = decay0_fe12_mod14(e2, params_);
      }
      if (d_el_[0] + d_el_[1] < dens || d_el_[0] + d_el_[1] > denf) {
        df2_[i] = 0.0;
      }
    }
    return;
  }

} // end of namespace bxdecay0
