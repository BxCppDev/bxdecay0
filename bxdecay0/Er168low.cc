// Copyright 2018 V.I. Tretyak
// Copyright 2020 F. Mauger
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
#include <bxdecay0/Er168low.h>

// Standard library:
#include <cmath>
#include <sstream>
#include <stdexcept>

// This project:
#include <bxdecay0/PbAtShell.h>
#include <bxdecay0/alpha.h>
#include <bxdecay0/beta.h>
#include <bxdecay0/beta1.h>
#include <bxdecay0/beta2.h>
#include <bxdecay0/beta_1fu.h>
#include <bxdecay0/electron.h>
#include <bxdecay0/event.h>
#include <bxdecay0/gamma.h>
#include <bxdecay0/i_random.h>
#include <bxdecay0/nucltransK.h>
#include <bxdecay0/nucltransKL.h>
#include <bxdecay0/nucltransKLM.h>
#include <bxdecay0/nucltransKLM_Pb.h>
#include <bxdecay0/pair.h>
#include <bxdecay0/particle.h>
#include <bxdecay0/positron.h>

namespace bxdecay0 {

  void Er168low(i_random & prng_, event & event_, const int levelkev_)
  {
    // double t;
    // Subroutine describes the deexcitation process in Er168 nucleus
    // after 2b-decay of Yb168 to ground and excited 0+ and 2+ levels
    // of Er168 (ENSDF on 26.10.2018 and NDS 111(2010)1807).
    // Call  : call Er168low(levelkeV)
    // Input : levelkeV - energy of Er168 level (integer in keV) occupied
    //                    initially; following levels can be occupied:
    //                    0+(gs) -    0 keV,
    //                    2+(1)  -   80 keV,
    //                    2+(2)  -  821 keV,
    //                    0+(1)  - 1217 keV,
    //                    2+(3)  - 1276 keV.
    // Output: common/genevent/tevst, npfull, npgeant(100), pmoment(3, 100), ptime(100).
    // VIT, 11.11.2018.
    double tdlev;
    double p;
    double tclev;
    double thlev;
    tclev = 0.;
    if (levelkev_ == 1276)
      goto label_1276;
    if (levelkev_ == 1217)
      goto label_1217;
    if (levelkev_ == 821)
      goto label_821;
    if (levelkev_ == 80)
      goto label_80;
    if (levelkev_ == 0)
      goto label_10000;
    goto label_20000;
  label_1276:
    thlev = 2.0e-12;
    p     = 100. * prng_();
    if (p <= 1.71)
      goto label_12761;
    if (p <= 2.92)
      goto label_12762;
    if (p <= 5.34)
      goto label_12763;
    if (p <= 50.20)
      goto label_12764;
    if (p <= 75.77)
      goto label_12765;
    goto label_12766;
  label_12761:
    decay0_nucltransK(prng_, event_, 0.059, 0.057, 24.4, 0., tclev, thlev, tdlev);
    goto label_1217;
  label_12762:
    decay0_nucltransK(prng_, event_, 0.380, 0.057, 7.1e-2, 0., tclev, thlev, tdlev);
    goto label_896;
  label_12763:
    decay0_nucltransK(prng_, event_, 0.455, 0.057, 4.5e-2, 0., tclev, thlev, tdlev);
    goto label_821;
  label_12764:
    decay0_nucltransK(prng_, event_, 1.012, 0.057, 3.3e-3, 0., tclev, thlev, tdlev);
    goto label_264;
  label_12765:
    decay0_nucltransK(prng_, event_, 1.197, 0.057, 4.0e-3, 5.8e-6, tclev, thlev, tdlev);
    goto label_80;
  label_12766:
    decay0_nucltransK(prng_, event_, 1.276, 0.057, 2.1e-3, 1.5e-5, tclev, thlev, tdlev);
    return;
  label_1217:
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 1.137, 0.057, 2.6e-3, 1.0e-6, tclev, thlev, tdlev);
    goto label_80;
  label_896:
    thlev = 3.2e-12;
    p     = 100. * prng_();
    if (p <= 0.32)
      goto label_8961;
    if (p <= 15.60)
      goto label_8962;
    goto label_8963;
  label_8961:
    decay0_nucltransK(prng_, event_, 0.075, 0.057, 8.35, 0., tclev, thlev, tdlev);
    goto label_821;
  label_8962:
    decay0_nucltransK(prng_, event_, 0.632, 0.057, 9.7e-3, 0., tclev, thlev, tdlev);
    goto label_264;
  label_8963:
    decay0_nucltransK(prng_, event_, 0.816, 0.057, 5.2e-3, 0., tclev, thlev, tdlev);
    goto label_80;
  label_821:
    thlev = 2.8e-12;
    p     = 100. * prng_();
    if (p <= 0.89)
      goto label_8211;
    if (p <= 52.08)
      goto label_8212;
    goto label_8213;
  label_8211:
    decay0_nucltransK(prng_, event_, 0.557, 0.057, 1.3e-2, 0., tclev, thlev, tdlev);
    goto label_264;
  label_8212:
    decay0_nucltransK(prng_, event_, 0.741, 0.057, 6.4e-3, 0., tclev, thlev, tdlev);
    goto label_80;
  label_8213:
    decay0_nucltransK(prng_, event_, 0.821, 0.057, 5.1e-3, 0., tclev, thlev, tdlev);
    return;
  label_264:
    thlev = 114.e-12;
    decay0_nucltransK(prng_, event_, 0.184, 0.057, 0.33, 0., tclev, thlev, tdlev);
    goto label_80;
  label_80:
    thlev = 1.853e-9;
    decay0_nucltransK(prng_, event_, 0.080, 0.057, 7.04, 0., tclev, thlev, tdlev);
    return;
  label_10000:
    return;
  label_20000:
    // print *, 'Er168: wrong level [keV] ', levelkev
    return;
  }

} // end of namespace bxdecay0

// end of Er168low.cc
// Local Variables: --
// mode: c++ --
// End: --
