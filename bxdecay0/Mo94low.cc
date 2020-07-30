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
#include <bxdecay0/Mo94low.h>

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

  void Mo94low(i_random & prng_, event & event_, const int levelkev_)
  {
    // double t;
    double tdlev;
    double tclev;
    double thlev;
    // Subroutine describes the deexcitation process in Mo94 nucleus
    // after 2b-decay of Zr94 to ground and excited 0+ and 2+ levels
    // of Mo94 ("Table of Isotopes", 7th ed., 1978).
    // Call : call Mo94low(levelkev_)
    // Input : levelkev_ - energy of Mo94 level (integer in keV) occupied
    // initially
    // 0+(gs) - 0 keV,
    // 2+(1) - 871 keV.
    // Output: // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 30.11.1995.
    tclev = 0.;
    if (levelkev_ == 871) {
      goto label_871;
    }
    if (levelkev_ == 0) {
      goto label_10000;
    }
    goto label_20000;
  label_871:
    thlev = 2.9e-12;
    decay0_nucltransK(prng_, event_, 0.871, 0.020, 9.5e-4, 0., tclev, thlev, tdlev);
    return;
  label_10000:
    return;
  label_20000:
    // print *,'Mo94: wrong level [keV] ',levelkev_
    return;
  }
  // end of Mo94low.f

} // end of namespace bxdecay0

// end of Mo94low.cc
// Local Variables: --
// mode: c++ --
// End: --
