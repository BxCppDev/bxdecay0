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
#include <bxdecay0/Cd112low.h>

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

  void Cd112low(i_random & prng_, event & event_, const int levelkev_)
  {
    // double t;
    double tdlev;
    double p;
    double tclev;
    double thlev;
    // Subroutine describes the deexcitation process in Cd112 nucleus
    // after 2b-decay of Sn112 to ground 0+ and excited 2+ levels
    // of Cd112 (NNDC site on 22.12.2008 and NDS 79(1996)639).
    // Call : call Cd112low(levelkev_)
    // Input : levelkev_ - energy of Cd112 level (integer in keV) occupied
    // initially
    // 0+(gs) - 0 keV,
    // 2+(1) - 618 keV,
    // 0+(1) - 1224 keV,
    // 2+(2) - 1312 keV,
    // 0+(2) - 1433 keV,
    // 2+(3) - 1469 keV,
    // 0+(3) - 1871 keV.
    // Output: // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 23.12.2008.
    tclev = 0.;
    if (levelkev_ == 1871) {
      goto label_1871;
    }
    if (levelkev_ == 1469) {
      goto label_1469;
    }
    if (levelkev_ == 1433) {
      goto label_1433;
    }
    if (levelkev_ == 1312) {
      goto label_1312;
    }
    if (levelkev_ == 1224) {
      goto label_1224;
    }
    if (levelkev_ == 618) {
      goto label_618;
    }
    if (levelkev_ == 0) {
      goto label_10000;
    }
    goto label_20000;
  label_1871:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 86.91) {
      goto label_18711;
    }
    if (p <= 89.88) {
      goto label_18712;
    }
    goto label_18713;
  label_18711:
    decay0_nucltransK(prng_, event_, 1.253, 0.027, 7.2e-4, 1.5e-5, tclev, thlev, tdlev);
    goto label_618;
  label_18712:
    decay0_nucltransK(prng_, event_, 0.559, 0.027, 4.9e-3, 0., tclev, thlev, tdlev);
    goto label_1312;
  label_18713:
    decay0_nucltransK(prng_, event_, 0.402, 0.027, 1.3e-2, 0., tclev, thlev, tdlev);
    goto label_1469;
  label_1469:
    thlev = 2.7e-12;
    p     = 100. * prng_();
    if (p <= 36.98) {
      goto label_14691;
    }
    if (p <= 99.14) {
      goto label_14692;
    }
    goto label_14693;
  label_14691:
    decay0_nucltransK(prng_, event_, 1.469, 0.027, 5.8e-4, 7.1e-5, tclev, thlev, tdlev);
    return;
  label_14692:
    decay0_nucltransK(prng_, event_, 0.851, 0.027, 1.8e-3, 0., tclev, thlev, tdlev);
    goto label_618;
  label_14693:
    decay0_nucltransK(prng_, event_, 0.245, 0.027, 6.4e-2, 0., tclev, thlev, tdlev);
    goto label_1224;
  label_1433:
    thlev = 1.9e-9;
    p     = 100. * prng_();
    if (p <= 0.66) {
      goto label_14331;
    }
    if (p <= 39.36) {
      goto label_14332;
    }
    if (p <= 60.61) {
      goto label_14333;
    }
    goto label_14334;
  label_14331:
    p = 100. * prng_();
    if (p <= 3.8) {
      ;                                                       // e0.exe
      decay0_pair(prng_, event_, 0.411, tclev, thlev, tdlev); // conversion to pair
    } else {
      ;
      decay0_electron(prng_, event_, 1.406, tclev, thlev, tdlev); // conversion to electron
      decay0_gamma(prng_, event_, 0.027, 0., 0., tdlev);
    };
    return;
  label_14332:
    decay0_nucltransK(prng_, event_, 0.816, 0.027, 1.8e-3, 0., tclev, thlev, tdlev);
    goto label_618;
  label_14333:
    decay0_electron(prng_, event_, 0.182, tclev, thlev, tdlev); // E0 conversion to electron
    decay0_gamma(prng_, event_, 0.027, 0., 0., tdlev);
    goto label_1224;
  label_14334:
    decay0_nucltransK(prng_, event_, 0.121, 0.027, 7.6e-1, 0., tclev, thlev, tdlev);
    goto label_1312;
  label_1312:
    thlev = 2.0e-12;
    p     = 100. * prng_();
    if (p <= 26.59) {
      goto label_13121;
    }
    goto label_13122;
  label_13121:
    decay0_nucltransK(prng_, event_, 1.312, 0.027, 6.6e-4, 2.6e-5, tclev, thlev, tdlev);
    return;
  label_13122:
    decay0_nucltransK(prng_, event_, 0.695, 0.027, 2.8e-3, 0., tclev, thlev, tdlev);
    goto label_618;
  label_1224:
    thlev = 4.2e-12;
    p     = 100. * prng_();
    if (p <= 0.12) {
      goto label_12241;
    }
    goto label_12242;
  label_12241:
    p = 100. * prng_();
    if (p <= 0.4) {
      ;                                                       // e0.exe
      decay0_pair(prng_, event_, 0.202, tclev, thlev, tdlev); // conversion to pair
    } else {
      ;
      decay0_electron(prng_, event_, 1.197, tclev, thlev, tdlev); // conversion to electron
      decay0_gamma(prng_, event_, 0.027, 0., 0., tdlev);
    };
    return;
  label_12242:
    decay0_nucltransK(prng_, event_, 0.607, 0.027, 3.9e-3, 0., tclev, thlev, tdlev);
    goto label_618;
  label_618:
    thlev = 6.51e-12;
    decay0_nucltransK(prng_, event_, 0.618, 0.027, 3.7e-3, 0., tclev, thlev, tdlev);
    return;
  label_10000:
    return;
  label_20000:
    // print *,'Cd112: wrong level [keV] ',levelkev_
    return;
  }
  // end of Cd112low.f

} // end of namespace bxdecay0

// end of Cd112low.cc
// Local Variables: --
// mode: c++ --
// End: --
