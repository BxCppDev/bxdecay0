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
#include <bxdecay0/Mo96low.h>

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

  void Mo96low(i_random & prng_, event & event_, const int levelkev_)
  {
    // double t;
    double tdlev;
    double p;
    double tclev;
    double thlev;
    // Subroutine describes the deexcitation process in Mo96 nucleus
    // after 2b- decay of Zr96 and 2b+/eb+/2e decay of Ru96 to ground and
    // excited 0+ and 2+ levels c of Mo96 ("Table of Isotopes", 7th ed., 1978).
    // VIT, 20.05.2009: four levels (2096, 2426, 2623 and 2700 keV) are added
    // and information is updated in accordance with NNDC site on 19.05.2009 and
    // NDS 109(2008)2501.
    // Call : call Mo96low(levelkev_)
    // Input : levelkev_ - energy of Mo96 level (integer in keV) occupied
    // initially
    // 0+(gs) - 0 keV,
    // 2+(1) - 778 keV,
    // 0+(1) - 1148 keV,
    // 2+(2) - 1498 keV,
    // 2+(3) - 1626 keV,
    // 2+(4) - 2096 keV,
    // 2+(5) - 2426 keV,
    // 0+(2) - 2623 keV,
    // 2+(6) - 2700 keV,
    // 2+(7) - 2713 keV (in fact spin and parity of this level
    // are unknown).
    // Output: // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 28.06.1993, 22.10.1995, 20.05.2009.
    tclev = 0.;
    if (levelkev_ == 2713) {
      goto label_2713;
    }
    if (levelkev_ == 2700) {
      goto label_2700;
    }
    if (levelkev_ == 2623) {
      goto label_2623;
    }
    if (levelkev_ == 2426) {
      goto label_2426;
    }
    if (levelkev_ == 2096) {
      goto label_2096;
    }
    if (levelkev_ == 1626) {
      goto label_1626;
    }
    if (levelkev_ == 1498) {
      goto label_1498;
    }
    if (levelkev_ == 1148) {
      goto label_1148;
    }
    if (levelkev_ == 778) {
      goto label_778;
    }
    if (levelkev_ == 0) {
      goto label_10000;
    }
    goto label_20000;
  label_2713:
    thlev = 0.;
    // 2+ to 6+ E4 transition is supposed
    ///    label_27131  :
    decay0_nucltransK(prng_, event_, 0.272, 0.020, 5.9e-1, 0., tclev, thlev, tdlev);
    goto label_2441;
  label_2700:
    thlev = 0.103e-12;
    p     = 100. * prng_();
    if (p <= 3.04) {
      goto label_27001;
    }
    if (p <= 12.12) {
      goto label_27002;
    }
    if (p <= 53.40) {
      goto label_27003;
    }
    if (p <= 86.67) {
      goto label_27004;
    }
    goto label_27005;
  label_27001:
    decay0_nucltransK(prng_, event_, 0.160, 0.020, 6.9e-2, 0., tclev, thlev, tdlev);
    goto label_2540;
  label_27002:
    decay0_nucltransK(prng_, event_, 1.074, 0.020, 6.7e-4, 0., tclev, thlev, tdlev);
    goto label_1626;
  label_27003:
    decay0_nucltransK(prng_, event_, 1.202, 0.020, 5.5e-4, 0., tclev, thlev, tdlev);
    goto label_1498;
  label_27004:
    decay0_nucltransK(prng_, event_, 1.922, 0.020, 2.1e-4, 2.5e-4, tclev, thlev, tdlev);
    goto label_778;
  label_27005:
    decay0_nucltransK(prng_, event_, 2.701, 0.020, 1.1e-4, 6.4e-4, tclev, thlev, tdlev);
    return;
  label_2623:
    thlev = 0.6e-12;
    ////    label_26231  :
    decay0_nucltransK(prng_, event_, 1.844, 0.020, 2.2e-4, 2.3e-4, tclev, thlev, tdlev);
    goto label_778;
  label_2540:
    thlev = 0.069e-12;
    p     = 100. * prng_();
    if (p <= 8.17) {
      goto label_25401;
    }
    if (p <= 28.31) {
      goto label_25402;
    }
    goto label_25403;
  label_25401:
    decay0_nucltransK(prng_, event_, 0.915, 0.020, 9.7e-4, 0., tclev, thlev, tdlev);
    goto label_1626;
  label_25402:
    decay0_nucltransK(prng_, event_, 1.043, 0.020, 7.3e-4, 0., tclev, thlev, tdlev);
    goto label_1498;
  label_25403:
    decay0_nucltransK(prng_, event_, 1.762, 0.020, 2.5e-4, 1.7e-4, tclev, thlev, tdlev);
    goto label_778;
  label_2441:
    thlev = 0.208e-12;
    ////    label_24411  :
    decay0_nucltransK(prng_, event_, 0.813, 0.020, 1.3e-3, 0., tclev, thlev, tdlev);
    goto label_1628;
  label_2426:
    thlev = 0.19e-12;
    p     = 100. * prng_();
    if (p <= 2.50) {
      goto label_24261;
    }
    if (p <= 38.16) {
      goto label_24262;
    }
    if (p <= 42.07) {
      goto label_24263;
    }
    if (p <= 95.22) {
      goto label_24264;
    }
    goto label_24265;
  label_24261:
    decay0_nucltransK(prng_, event_, 0.448, 0.020, 6.4e-3, 0., tclev, thlev, tdlev);
    goto label_1978;
  label_24262:
    decay0_nucltransK(prng_, event_, 0.800, 0.020, 1.3e-3, 0., tclev, thlev, tdlev);
    goto label_1626;
  label_24263:
    decay0_nucltransK(prng_, event_, 0.928, 0.020, 9.2e-4, 0., tclev, thlev, tdlev);
    goto label_1498;
  label_24264:
    decay0_nucltransK(prng_, event_, 1.648, 0.020, 2.9e-4, 1.2e-4, tclev, thlev, tdlev);
    goto label_778;
  label_24265:
    decay0_nucltransK(prng_, event_, 2.426, 0.020, 1.4e-4, 5.1e-4, tclev, thlev, tdlev);
    return;
  label_2096:
    thlev = 0.097e-12;
    p     = 100. * prng_();
    if (p <= 3.06) {
      goto label_20961;
    }
    if (p <= 98.55) {
      goto label_20962;
    }
    goto label_20963;
  label_20961:
    decay0_nucltransK(prng_, event_, 0.948, 0.020, 8.7e-4, 0., tclev, thlev, tdlev);
    goto label_1148;
  label_20962:
    decay0_nucltransK(prng_, event_, 1.317, 0.020, 4.4e-4, 2.5e-5, tclev, thlev, tdlev);
    goto label_778;
  label_20963:
    decay0_nucltransK(prng_, event_, 2.096, 0.020, 1.8e-4, 3.5e-4, tclev, thlev, tdlev);
    return;
  label_1978:
    thlev = 2.29e-12;
    p     = 100. * prng_();
    if (p <= 0.18) {
      goto label_19781;
    }
    if (p <= 5.96) {
      goto label_19782;
    }
    if (p <= 9.27) {
      goto label_19783;
    }
    if (p <= 30.34) {
      goto label_19784;
    }
    goto label_19785;
  label_19781:
    decay0_nucltransK(prng_, event_, 0.109, 0.020, 2.0e-1, 0., tclev, thlev, tdlev);
    goto label_1870;
  label_19782:
    decay0_nucltransK(prng_, event_, 0.350, 0.020, 1.2e-2, 0., tclev, thlev, tdlev);
    goto label_1628;
  label_19783:
    decay0_nucltransK(prng_, event_, 0.353, 0.020, 1.2e-2, 0., tclev, thlev, tdlev);
    goto label_1626;
  label_19784:
    decay0_nucltransK(prng_, event_, 0.481, 0.020, 4.3e-3, 0., tclev, thlev, tdlev);
    goto label_1498;
  label_19785:
    decay0_nucltransK(prng_, event_, 1.200, 0.020, 5.4e-4, 6.1e-6, tclev, thlev, tdlev);
    goto label_778;
  label_1870:
    thlev = 6.4e-12;
    p     = 100. * prng_();
    if (p <= 7.52) {
      goto label_18701;
    }
    if (p <= 12.22) {
      goto label_18702;
    }
    goto label_18703;
  label_18701:
    decay0_nucltransK(prng_, event_, 0.241, 0.020, 2.4e-2, 0., tclev, thlev, tdlev);
    goto label_1628;
  label_18702:
    decay0_nucltransK(prng_, event_, 0.372, 0.020, 1.2e-2, 0., tclev, thlev, tdlev);
    goto label_1498;
  label_18703:
    decay0_nucltransK(prng_, event_, 1.091, 0.020, 6.4e-4, 0., tclev, thlev, tdlev);
    goto label_778;
  label_1628:
    thlev = 1.2e-12;
    ////    label_16281  :
    decay0_nucltransK(prng_, event_, 0.850, 0.020, 1.1e-3, 0., tclev, thlev, tdlev);
    goto label_778;
  label_1626:
    thlev = 1.4e-12;
    p     = 100. * prng_();
    if (p <= 8.47) {
      goto label_16261;
    }
    if (p <= 98.58) {
      goto label_16262;
    }
    goto label_16263;
  label_16261:
    decay0_nucltransK(prng_, event_, 1.626, 0.020, 2.8e-4, 1.3e-4, tclev, thlev, tdlev);
    return;
  label_16262:
    decay0_nucltransK(prng_, event_, 0.848, 0.020, 1.2e-3, 0., tclev, thlev, tdlev);
    goto label_778;
  label_16263:
    decay0_nucltransK(prng_, event_, 0.128, 0.020, 1.3e-1, 0., tclev, thlev, tdlev);
    goto label_1498;
  label_1498:
    thlev = 0.78e-12;
    p     = 100. * prng_();
    if (p <= 29.73) {
      goto label_14981;
    }
    goto label_14982;
  label_14981:
    decay0_nucltransK(prng_, event_, 1.498, 0.020, 3.3e-4, 8.3e-5, tclev, thlev, tdlev);
    return;
  label_14982:
    decay0_nucltransK(prng_, event_, 0.720, 0.020, 1.7e-3, 0., tclev, thlev, tdlev);
    goto label_778;
  label_1148:
    thlev = 61.e-12;
    ////    label_11481  :
    decay0_nucltransK(prng_, event_, 0.370, 0.020, 1.2e-2, 0., tclev, thlev, tdlev);
    goto label_778;
  label_778:
    thlev = 3.67e-12;
    decay0_nucltransK(prng_, event_, 0.778, 0.020, 1.4e-3, 0., tclev, thlev, tdlev);
    return;
  label_10000:
    return;
  label_20000:
    // print *,'Mo96: wrong level [keV] ',levelkev_
    return;
  }
  // end of Mo96low.f

} // end of namespace bxdecay0

// end of Mo96low.cc
// Local Variables: --
// mode: c++ --
// End: --
