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
#include <bxdecay0/Ti48low.h>

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

  void Ti48low(i_random & prng_, event & event_, const int levelkev_)
  {
    // double t;
    double tdlev;
    double p;
    double tclev;
    double thlev;
    // Subroutine describes the deexcitation process in Ti48 nucleus
    // after 2b-decay of Ca48 to ground and excited 0+ and 2+ levels
    // of Ti48 ("Table of Isotopes", 7th ed., 1978).
    // Call : call Ti48low(levelkev_)
    // Input : levelkev_ - energy of Ti48 level (integer in keV) occupied
    // initially
    // 0+(gs) - 0 keV,
    // 2+(1) - 984 keV,
    // 2+(2) - 2421 keV.
    // Output: // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 19.07.1993, 22.10.1995.
    tclev = 0.;
    if (levelkev_ == 2421)
      goto label_2421;
    if (levelkev_ == 984)
      goto label_984;
    if (levelkev_ == 0)
      goto label_10000;
    goto label_20000;
  label_2421:
    thlev = 24.e-15;
    p     = 100. * prng_();
    if (p <= 8.)
      goto label_24211;
    goto label_24212;
  label_24211:
    decay0_nucltransK(prng_, event_, 2.421, 0.005, 1.5e-5, 5.0e-4, tclev, thlev, tdlev);
    return;
  label_24212:
    decay0_nucltransK(prng_, event_, 1.437, 0.005, 3.1e-5, 1.8e-4, tclev, thlev, tdlev);
    goto label_984;
  label_984:
    thlev = 4.3e-12;
    decay0_nucltransK(prng_, event_, 0.984, 0.005, 1.2e-4, 0., tclev, thlev, tdlev);
    return;
  label_10000:
    return;
  label_20000:
    // print *,'Ti48: wrong level [keV] ',levelkev_
    return;
  }
  // end of Ti48low.f

} // end of namespace bxdecay0

// end of Ti48low.cc
// Local Variables: --
// mode: c++ --
// End: --
