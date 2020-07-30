// Copyright 1995-2016 V.I. Tretyak
// Copyright 2011-2020 F. Mauger
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

/// Ourselves:
#include <bxdecay0/Sm148low.h>

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

  // History:
  // - Updated from decay0_2018-12-05
  void Sm148low(i_random & prng_, event & event_, const int levelkev_)
  {
    // double t;
    double tdlev;
    double p;
    double tclev;
    double thlev;
    // Subroutine describes the deexcitation process in Sm148 nucleus
    // after 2b-decay of Nd148 to ground and excited 0+ and 2+ levels
    // of Sm148 ("Table of Isotopes", 7th ed., 1978).
    // Call : call Sm148low(levelkev_)
    // Input : levelkev_ - energy of Sm148 level (integer in keV) occupied
    // initially
    // 0+(gs) - 0 keV,
    // 2+(1) - 550 keV,
    // 2+(2) - 1454 keV.
    // Output: // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 30.11.1995.
    tclev = 0.;
    if (levelkev_ == 1921)
      goto label_1921;
    if (levelkev_ == 1664)
      goto label_1664;
    if (levelkev_ == 1454)
      goto label_1454;
    if (levelkev_ == 1424)
      goto label_1424;
    if (levelkev_ == 550)
      goto label_550;
    if (levelkev_ == 0)
      goto label_10000;
    goto label_20000;
  label_1921:
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 1.371, 0.047, 1.3e-3, 3.6e-5, tclev, thlev, tdlev);
    goto label_550;
  label_1664:
    thlev = 0.25e-12;
    p     = 100. * prng_();
    if (p <= 34.04)
      goto label_16641;
    goto label_16642;
  label_16641:
    decay0_nucltransK(prng_, event_, 1.664, 0.047, 1.0e-3, 1.4e-4, tclev, thlev, tdlev);
    return;
  label_16642:
    decay0_nucltransK(prng_, event_, 1.114, 0.047, 2.8e-3, 5.7e-7, tclev, thlev, tdlev);
    goto label_550;
  label_1454:
    thlev = 0.285e-12;
    p     = 100. * prng_();
    if (p <= 49.9)
      goto label_14541;
    goto label_14542;
  label_14541:
    decay0_nucltransK(prng_, event_, 1.454, 0.047, 1.2e-3, 0.6e-4, tclev, thlev, tdlev);
    return;
  label_14542:
    decay0_nucltransK(prng_, event_, 0.904, 0.047, 3.4e-3, 0., tclev, thlev, tdlev);
    goto label_550;
  label_1424:
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 0.874, 0.047, 3.3e-3, 0., tclev, thlev, tdlev);
    goto label_550;
  label_550:
    thlev = 7.72e-12;
    decay0_nucltransK(prng_, event_, 0.550, 0.047, 1.0e-2, 0., tclev, thlev, tdlev);
    return;
  label_10000:
    return;
  label_20000:
    // print *,'Sm148: wrong level [keV] ',levelkev_
    return;
  }
  // end of Sm148low.f

} // end of namespace bxdecay0

// end of Sm148low.cc
// Local Variables: --
// mode: c++ --
// End: --
