// Copyright 2011-2017 F. Mauger
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
#include <bxdecay0/dshelp2.h>

// Standard library:
#include <cmath>
#include <sstream>

// This project:
#include <bxdecay0/bb.h>
#include <bxdecay0/dgmlt2.h>
#include <bxdecay0/dshelp1.h>
#include <bxdecay0/event.h>
#include <bxdecay0/fe12_mods.h>

namespace bxdecay0 {

  void decay0_dshelp2(const int m_, const double * du2_, double * df2_, double * d_el_, void * params_)
  {
    bbpars * pars       = static_cast<bbpars *>(params_);
    const double & dens = pars->dens;
    const double & denf = pars->denf;
    const int & mode    = pars->mode;
    double & e0         = pars->e0;
    double & e1         = pars->e1;
    for (int i = 0; i < m_; i++) {
      d_el_[1]  = du2_[i];
      e1        = d_el_[0];
      double e2 = d_el_[1];
      df2_[i]   = 0.0;
      if (e1 > 0. && e2 > 0. && e1 + e2 < e0) {
        if (mode == LEGACY_MODEBB_4) {
          df2_[i] = decay0_fe12_mod4(e2, params_);
        }
        if (mode == LEGACY_MODEBB_5) {
          df2_[i] = decay0_fe12_mod5(e2, params_);
        }
        if (mode == LEGACY_MODEBB_6) {
          df2_[i] = decay0_fe12_mod6(e2, params_);
        }
        if (mode == LEGACY_MODEBB_13) {
          df2_[i] = decay0_fe12_mod13(e2, params_);
        }
        if (mode == LEGACY_MODEBB_14) {
          df2_[i] = decay0_fe12_mod14(e2, params_);
        }
        if (mode == LEGACY_MODEBB_8) {
          df2_[i] = decay0_fe12_mod8(e2, params_);
        }
        if (mode == LEGACY_MODEBB_15) {
          df2_[i] = decay0_fe12_mod15(e2, params_);
        }
        if (mode == LEGACY_MODEBB_16) {
          df2_[i] = decay0_fe12_mod16(e2, params_);
        }
        if (mode == LEGACY_MODEBB_19) {
          df2_[i] = decay0_fe12_mod19(e2, params_);
        }
      }
      if (d_el_[0] + d_el_[1] < dens || d_el_[0] + d_el_[1] > denf) {
        df2_[i] = 0.0;
      }
    }
    return;
  }

} // end of namespace bxdecay0
