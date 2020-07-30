// Copyright 1995-2016 V.I. Tretyak
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
#include <bxdecay0/Te124low.h>

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

  void Te124low(i_random & prng_, event & event_, const int levelkev_)
  {
    // double t;
    double tdlev;
    double p;
    double tclev;
    double thlev;
    // Subroutine describes the deexcitation process in Te124 nucleus
    // after 2b-decay of Sn124 to ground 0+ and excited 2+ levels
    // of Te124 (NNDC site on 22.12.2008 and NDS 109(2008)1655).
    // Call : call Te124low(levelkev_)
    // Input : levelkev_ - energy of Te124 level (integer in keV) occupied
    // initially
    // 0+(gs) - 0 keV,
    // 2+(1) - 603 keV,
    // 2+(2) - 1326 keV,
    // 0+(1) - 1657 keV,
    // 0+(2) - 1883 keV,
    // 2+(3) - 2039 keV,
    // 2+(4) - 2092 keV,
    // 0+(3) - 2153 keV,
    // 2+(5) - 2182 keV.
    // Output: // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 23.12.2008.
    tclev = 0.;
    if (levelkev_ == 2182)
      goto label_2182;
    if (levelkev_ == 2153)
      goto label_2153;
    if (levelkev_ == 2092)
      goto label_2092;
    if (levelkev_ == 2039)
      goto label_2039;
    if (levelkev_ == 1883)
      goto label_1883;
    if (levelkev_ == 1657)
      goto label_1657;
    if (levelkev_ == 1326)
      goto label_1326;
    if (levelkev_ == 603)
      goto label_603;
    if (levelkev_ == 0)
      goto label_10000;
    goto label_20000;
  label_2182:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 9.53)
      goto label_21821;
    if (p <= 92.38)
      goto label_21822;
    goto label_21823;
  label_21821:
    decay0_nucltransK(prng_, event_, 2.182, 0.032, 7.0e-4, 3.9e-4, tclev, thlev, tdlev);
    return;
  label_21822:
    decay0_nucltransK(prng_, event_, 1.580, 0.032, 7.7e-4, 1.0e-4, tclev, thlev, tdlev);
    goto label_603;
  label_21823:
    decay0_nucltransK(prng_, event_, 0.857, 0.032, 2.3e-3, 0., tclev, thlev, tdlev);
    goto label_1326;
  label_2153:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 19.29)
      goto label_21531;
    goto label_21532;
  label_21531:
    decay0_nucltransK(prng_, event_, 1.550, 0.032, 6.8e-4, 1.0e-4, tclev, thlev, tdlev);
    goto label_603;
  label_21532:
    decay0_nucltransK(prng_, event_, 0.828, 0.032, 2.2e-3, 0., tclev, thlev, tdlev);
    goto label_1326;
  label_2092:
    thlev = 0.28e-12;
    p     = 100. * prng_();
    if (p <= 97.97)
      goto label_20921;
    if (p <= 98.24)
      goto label_20922;
    goto label_20923;
  label_20921:
    decay0_nucltransK(prng_, event_, 1.488, 0.032, 8.3e-4, 7.1e-5, tclev, thlev, tdlev);
    goto label_603;
  label_20922:
    decay0_nucltransK(prng_, event_, 0.844, 0.032, 2.1e-3, 0., tclev, thlev, tdlev);
    goto label_1248;
  label_20923:
    decay0_nucltransK(prng_, event_, 0.766, 0.032, 3.0e-3, 0., tclev, thlev, tdlev);
    goto label_1326;
  label_2039:
    thlev = 0.49e-12;
    p     = 100. * prng_();
    if (p <= 34.26)
      goto label_20391;
    if (p <= 94.57)
      goto label_20392;
    if (p <= 96.80)
      goto label_20393;
    if (p <= 99.04)
      goto label_20394;
    goto label_20395;
  label_20391:
    decay0_nucltransK(prng_, event_, 2.039, 0.032, 6.7e-4, 3.2e-4, tclev, thlev, tdlev);
    return;
  label_20392:
    decay0_nucltransK(prng_, event_, 1.437, 0.032, 8.7e-4, 5.5e-5, tclev, thlev, tdlev);
    goto label_603;
  label_20393:
    decay0_nucltransK(prng_, event_, 0.791, 0.032, 2.5e-3, 0., tclev, thlev, tdlev);
    goto label_1248;
  label_20394:
    decay0_nucltransK(prng_, event_, 0.714, 0.032, 4.0e-3, 0., tclev, thlev, tdlev);
    goto label_1326;
  label_20395:
    decay0_nucltransK(prng_, event_, 0.382, 0.032, 1.8e-2, 0., tclev, thlev, tdlev);
    goto label_1657;
  label_1883:
    thlev = 0.76e-12;
    p     = 100. * prng_();
    if (p <= 0.31)
      goto label_18831;
    if (p <= 99.93)
      goto label_18832;
    goto label_18833;
  label_18831:
    p = 100. * prng_();
    if (p <= 21.89) {
      ;                                                       // e0.exe
      decay0_pair(prng_, event_, 0.861, tclev, thlev, tdlev); // conversion to pair
    } else {
      ;
      decay0_electron(prng_, event_, 1.851, tclev, thlev, tdlev); // conversion to electron
      decay0_gamma(prng_, event_, 0.032, 0., 0., tdlev);
    };
    return;
  label_18832:
    decay0_nucltransK(prng_, event_, 0.557, 0.032, 6.0e-3, 0., tclev, thlev, tdlev);
    goto label_1326;
  label_18833:
    decay0_electron(prng_, event_, 0.194, tclev, thlev, tdlev); // E0 conversion to electron
    decay0_gamma(prng_, event_, 0.032, 0., 0., tdlev);
    goto label_1657;
  label_1657:
    thlev = 0.55 - 12;
    p     = 100. * prng_();
    if (p <= 0.02)
      goto label_16571;
    goto label_16572;
  label_16571:
    p = 100. * prng_();
    if (p <= 10.68) {
      ;                                                       // e0.exe
      decay0_pair(prng_, event_, 0.636, tclev, thlev, tdlev); // conversion to pair
    } else {
      ;
      decay0_electron(prng_, event_, 1.626, tclev, thlev, tdlev); // conversion to electron
      decay0_gamma(prng_, event_, 0.032, 0., 0., tdlev);
    };
    return;
  label_16572:
    decay0_nucltransK(prng_, event_, 1.055, 0.032, 1.3e-3, 0., tclev, thlev, tdlev);
    goto label_603;
  label_1326:
    thlev = 1.04e-12;
    p     = 100. * prng_();
    if (p <= 13.84)
      goto label_13261;
    goto label_13262;
  label_13261:
    decay0_nucltransK(prng_, event_, 1.326, 0.032, 8.3e-4, 2.8e-5, tclev, thlev, tdlev);
    return;
  label_13262:
    decay0_nucltransK(prng_, event_, 0.723, 0.032, 3.1e-3, 0., tclev, thlev, tdlev);
    goto label_603;
  label_1248:
    thlev = 1.4e-12;
    decay0_nucltransK(prng_, event_, 0.646, 0.032, 4.1e-3, 0., tclev, thlev, tdlev);
    goto label_603;
  label_603:
    thlev = 6.2e-12;
    decay0_nucltransK(prng_, event_, 0.603, 0.032, 4.9e-3, 0., tclev, thlev, tdlev);
    return;
  label_10000:
    return;
  label_20000:
    // print *,'Te124: wrong level [keV] ',levelkev_
    return;
  }
  // end of Te124low.f

} // end of namespace bxdecay0

// end of Te124low.cc
// Local Variables: --
// mode: c++ --
// End: --
