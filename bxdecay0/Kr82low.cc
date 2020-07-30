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
#include <bxdecay0/Kr82low.h>

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

  void Kr82low(i_random & prng_, event & event_, const int levelkev_)
  {
    double tdlev;
    double p;
    double tclev;
    double thlev;
    // Subroutine describes the deexcitation process in Kr82 nucleus
    // after 2b-decay of Se82 to ground and excited 0+ and 2+ levels
    // of Kr82 ("Table of Isotopes", 7th ed., 1978).
    // Call : call Kr82low(levelkev_)
    // Input : levelkev_ - energy of Kr82 level (integer in keV) occupied
    // initially
    // 0+(gs) - 0 keV,
    // 2+(1)  -  777 keV,
    // 2+(2)  - 1475 keV,
    // 0+(1)  - 1488 keV,
    // 2+(3)  - 1957 keV,
    // 0+(2)  - 2172 keV,
    // 0+(3)  - 2450 keV,
    // 2+(4)  - 2480 keV,
    // 2+(5)  - 2656 keV,
    // 2+(6)  - 2945 keV.    // 2+(1) - 776 keV,
    // 2+(2)  - 1475 keV.
    // Output: // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 28.06.1993, 22.10.1995, 28.04.2020 in accordance with NDS 157(2019)260.
    tclev = 0.;
    if (levelkev_ == 2945)
      goto label_2945;
    if (levelkev_ == 2656)
      goto label_2656;
    if (levelkev_ == 2480)
      goto label_2480;
    if (levelkev_ == 2450)
      goto label_2450;
    if (levelkev_ == 2172)
      goto label_2172;
    if (levelkev_ == 1957)
      goto label_1957;
    if (levelkev_ == 1488)
      goto label_1488;
    if (levelkev_ == 1475)
      goto label_1475;
    if (levelkev_ == 777)
      goto label_777;
    if (levelkev_ == 0)
      goto label_10000;
    goto label_20000;
  label_2945:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 0.90)
      goto label_29451;
    if (p <= 1.70)
      goto label_29452;
    if (p <= 2.66)
      goto label_29453;
    if (p <= 7.62)
      goto label_29454;
    if (p <= 88.87)
      goto label_29455;
    goto label_29456;
  label_29451:
    decay0_nucltransK(prng_, event_, 0.397, 0.014, 1.7e-3, 0., tclev, thlev, tdlev);
    goto label_2547;
  label_29452:
    decay0_nucltransK(prng_, event_, 0.850, 0.014, 6.5e-4, 0., tclev, thlev, tdlev);
    goto label_2094;
  label_29453:
    decay0_nucltransK(prng_, event_, 0.988, 0.014, 4.8e-4, 0., tclev, thlev, tdlev);
    goto label_1957;
  label_29454:
    decay0_nucltransK(prng_, event_, 1.470, 0.014, 2.1e-4, 5.9e-5, tclev, thlev, tdlev);
    goto label_1475;
  label_29455:
    decay0_nucltransK(prng_, event_, 2.168, 0.014, 1.0e-4, 3.4e-4, tclev, thlev, tdlev);
    goto label_777;
  label_29456:
    decay0_nucltransK(prng_, event_, 2.945, 0.014, 6.0e-5, 7.5e-4, tclev, thlev, tdlev);
    return;
  label_2656:
    thlev = 0.03e-12;
    p     = 100. * prng_();
    if (p <= 4.16)
      goto label_26561;
    if (p <= 10.06)
      goto label_26562;
    if (p <= 19.05)
      goto label_26563;
    if (p <= 86.12)
      goto label_26564;
    goto label_26565;
  label_26561:
    decay0_nucltransK(prng_, event_, 0.699, 0.014, 1.0e-3, 0., tclev, thlev, tdlev);
    goto label_1957;
  label_26562:
    decay0_nucltransK(prng_, event_, 1.168, 0.014, 3.5e-4, 4.4e-6, tclev, thlev, tdlev);
    goto label_1488;
  label_26563:
    decay0_nucltransK(prng_, event_, 1.181, 0.014, 3.3e-4, 4.3e-6, tclev, thlev, tdlev);
    goto label_1475;
  label_26564:
    decay0_nucltransK(prng_, event_, 1.880, 0.014, 1.4e-4, 2.1e-4, tclev, thlev, tdlev);
    goto label_777;
  label_26565:
    decay0_nucltransK(prng_, event_, 2.656, 0.014, 6.0e-5, 7.6e-4, tclev, thlev, tdlev);
    return;
  label_2547:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 96.15)
      goto label_25471;
    goto label_25472;
  label_25471:
    decay0_nucltransK(prng_, event_, 1.073, 0.014, 1.9e-4, 0., tclev, thlev, tdlev);
    goto label_1475;
  label_25472:
    decay0_nucltransK(prng_, event_, 1.771, 0.014, 7.9e-5, 4.6e-4, tclev, thlev, tdlev);
    goto label_777;
  label_2480:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 9.09)
      goto label_24801;
    if (p <= 9.82)
      goto label_24802;
    if (p <= 11.86)
      goto label_24803;
    if (p <= 64.74)
      goto label_24804;
    goto label_24805;
  label_24801:
    decay0_nucltransK(prng_, event_, 0.523, 0.014, 1.9e-3, 0., tclev, thlev, tdlev);
    goto label_1957;
  label_24802:
    decay0_nucltransK(prng_, event_, 0.659, 0.014, 1.4e-3, 0., tclev, thlev, tdlev);
    goto label_1821;
  label_24803:
    decay0_nucltransK(prng_, event_, 0.992, 0.014, 5.0e-4, 0., tclev, thlev, tdlev);
    goto label_1488;
  label_24804:
    decay0_nucltransK(prng_, event_, 1.704, 0.014, 1.6e-4, 1.4e-4, tclev, thlev, tdlev);
    goto label_777;
  label_24805:
    decay0_nucltransK(prng_, event_, 2.480, 0.014, 8.0e-5, 5.4e-4, tclev, thlev, tdlev);
    return;
  label_2450:
    thlev = 0.17e-12;
    p     = 100. * prng_();
    if (p <= 55.25)
      goto label_24501;
    goto label_24502;
  label_24501:
    decay0_nucltransK(prng_, event_, 0.975, 0.014, 5.3e-4, 0., tclev, thlev, tdlev);
    goto label_1475;
  label_24502:
    decay0_nucltransK(prng_, event_, 1.674, 0.014, 1.6e-4, 1.6e-4, tclev, thlev, tdlev);
    goto label_777;
  label_2172:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 4.40)
      goto label_21721;
    if (p <= 99.99)
      goto label_21722;
    goto label_21723;
  label_21721:
    decay0_nucltransK(prng_, event_, 0.697, 0.014, 1.2e-3, 0., tclev, thlev, tdlev);
    goto label_1475;
  label_21722:
    decay0_nucltransK(prng_, event_, 1.395, 0.014, 2.4e-4, 5.0e-5, tclev, thlev, tdlev);
    goto label_777;
  label_21723:
    p = 100. * prng_();
    if (p <= 68.42) {
      decay0_pair(prng_, event_, 1.150, tclev, thlev, tdlev);
    } else {
      decay0_electron(prng_, event_, 2.158, tclev, thlev, tdlev);
      decay0_gamma(prng_, event_, 0.014, 0., 0., tdlev);
    }
    return;
  label_2094:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 0.13)
      goto label_20941;
    if (p <= 1.25)
      goto label_20942;
    if (p <= 62.36)
      goto label_20943;
    goto label_20944;
  label_20941:
    decay0_nucltransK(prng_, event_, 0.137, 0.014, 5.5e-2, 0., tclev, thlev, tdlev);
    goto label_1957;
  label_20942:
    decay0_nucltransK(prng_, event_, 0.273, 0.014, 1.0e-2, 0., tclev, thlev, tdlev);
    goto label_1821;
  label_20943:
    decay0_nucltransK(prng_, event_, 0.619, 0.014, 1.6e-3, 0., tclev, thlev, tdlev);
    goto label_1475;
  label_20944:
    decay0_nucltransK(prng_, event_, 1.317, 0.014, 3.0e-4, 2.4e-5, tclev, thlev, tdlev);
    goto label_777;
  label_1957:
    thlev = 1.1e-12;
    p     = 100. * prng_();
    if (p <= 69.74)
      goto label_19571;
    goto label_19572;
  label_19571:
    decay0_nucltransK(prng_, event_, 1.180, 0.014, 3.3e-4, 4.3e-6, tclev, thlev, tdlev);
    goto label_777;
  label_19572:
    decay0_nucltransK(prng_, event_, 1.957, 0.014, 1.2e-4, 2.9e-4, tclev, thlev, tdlev);
    return;
  label_1821:
    thlev = 0.67e-12;
    decay0_nucltransK(prng_, event_, 1.044, 0.014, 4.5e-4, 0., tclev, thlev, tdlev);
    goto label_777;
  label_1488:
    thlev = 10.e-12;
    p     = 100. * prng_();
    if (p <= 99.99)
      goto label_14881;
    goto label_14882;
  label_14881:
    decay0_nucltransK(prng_, event_, 0.711, 0.014, 1.2e-3, 0., tclev, thlev, tdlev);
    goto label_777;
  label_14882:
    p = 100. * prng_();
    if (p <= 14.31) {
      decay0_pair(prng_, event_, 0.466, tclev, thlev, tdlev);
    } else {
      decay0_electron(prng_, event_, 1.474, tclev, thlev, tdlev);
      decay0_gamma(prng_, event_, 0.014, 0., 0., tdlev);
    }
    return;
  label_1475:
    thlev = 12.e-12;
    p     = 100. * prng_();
    if (p <= 63.41)
      goto label_14751;
    goto label_14752;
  label_14751:
    decay0_nucltransK(prng_, event_, 0.698, 0.014, 1.2e-3, 0., tclev, thlev, tdlev);
    goto label_777;
  label_14752:
    decay0_nucltransK(prng_, event_, 1.475, 0.014, 2.1e-4, 7.6e-5, tclev, thlev, tdlev);
    return;
  label_777:
    thlev = 4.45e-12;
    decay0_nucltransK(prng_, event_, 0.777, 0.014, 9.2e-4, 0., tclev, thlev, tdlev);
    return;
  label_10000:
    return;
  label_20000:
    return;
  }
  // end of Kr82low.f

} // end of namespace bxdecay0

// end of Kr82low.cc
// Local Variables: --
// mode: c++ --
// End: --
