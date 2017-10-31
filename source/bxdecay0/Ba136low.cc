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
#include <bxdecay0/Ba136low.h>

// Standard library:
#include <sstream>
#include <stdexcept>
#include <cmath>

// This project:
#include <bxdecay0/i_random.h>
#include <bxdecay0/event.h>
#include <bxdecay0/alpha.h>
#include <bxdecay0/gamma.h>
#include <bxdecay0/electron.h>
#include <bxdecay0/positron.h>
#include <bxdecay0/particle.h>
#include <bxdecay0/pair.h>
#include <bxdecay0/nucltransK.h>
#include <bxdecay0/nucltransKL.h>
#include <bxdecay0/nucltransKLM.h>
#include <bxdecay0/nucltransKLM_Pb.h>
#include <bxdecay0/beta.h>
#include <bxdecay0/beta1.h>
#include <bxdecay0/beta2.h>
#include <bxdecay0/beta_1fu.h>
#include <bxdecay0/PbAtShell.h>

namespace bxdecay0 {

  void Ba136low(i_random & prng_,
                event & event_,
                const int levelkev_)
  {
    //double t;
    double tdlev;
    double p;
    double tclev;
    double thlev;
    // Subroutine describes the deexcitation process in Ba136 nucleus
    // after 2b-decay of Xe136 or Ce136 to ground and excited 0+ and 2+ levels
    // of Ba136 ("Table of Isotopes", 7th ed., 1978).
    // Call : call Ba136low(levelkev_)
    // Input : levelkev_ - energy of Ba136 level (integer in keV) occupied
    // initially
    // 0+(gs) - 0 keV,
    // 2+(1) - 819 keV,
    // 2+(2) - 1551 keV,
    // 0+(1) - 1579 keV,
    // 2+(3) - 2080 keV,
    // 2+(4) - 2129 keV,
    // 0+(2) - 2141 keV,
    // 2+(5) - 2223 keV,
    // 0+(3) - 2315 keV,
    // 2+(6) - 2400 keV.
    // Output: // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 28.06.1993, 22.10.1995.
    // VIT, 10.12.2008: updated to NDS 95(2002)837
    // (E0 transitions from 2141 and 1579 keV levels are neglected)
    // levels 2080, 2129, 2141, 2223, 2315 and 2400 keV were added.
    tclev=0.;
    if (levelkev_ == 2400) goto label_2400;
    if (levelkev_ == 2315) goto label_2315;
    if (levelkev_ == 2223) goto label_2223;
    if (levelkev_ == 2141) goto label_2141;
    if (levelkev_ == 2129) goto label_2129;
    if (levelkev_ == 2080) goto label_2080;
    if (levelkev_ == 1579) goto label_1579;
    if (levelkev_ == 1551) goto label_1551;
    if (levelkev_ ==  819) goto label_819;
    if (levelkev_ ==  0) goto label_10000;
    goto label_20000;
  label_2400  :
    thlev=0.;
    decay0_nucltransK(prng_, event_, 1.581,0.037,1.0e-3,1.1e-4,tclev,thlev,tdlev);
    goto label_819;
  label_2315  :
    thlev=0.;
    decay0_nucltransK(prng_, event_, 1.497,0.037,8.7e-4,7.7e-5,tclev,thlev,tdlev);
    goto label_819;
  label_2223  :
    thlev=0.;
    p=100.*prng_();
    if (p <=  4.3) goto label_22231;
    if (p <= 51.9) goto label_22232;
    goto label_22233;
  label_22231  :
    decay0_nucltransK(prng_, event_, 2.223,0.037,7.8e-4,4.0e-4,tclev,thlev,tdlev);
    return;
  label_22232  :
    decay0_nucltransK(prng_, event_, 1.404,0.037,9.6e-4,4.8e-5,tclev,thlev,tdlev);
    goto label_819;
  label_22233  :
    decay0_nucltransK(prng_, event_, 0.672,0.037,6.5e-3,0.,tclev,thlev,tdlev);
    goto label_1551;
  label_2141  :
    thlev=0.;
    decay0_nucltransK(prng_, event_, 1.323,0.037,1.0e-3,2.6e-5,tclev,thlev,tdlev);
    goto label_819;
  label_2129  :
    thlev=0.051e-12;
    p=100.*prng_();
    if (p <= 33.3) goto label_21291;
    goto label_21292;
  label_21291  :
    decay0_nucltransK(prng_, event_, 2.129,0.037,7.7e-4,3.6e-4,tclev,thlev,tdlev);
    return;
  label_21292  :
    decay0_nucltransK(prng_, event_, 1.310,0.037,1.4e-3,2.3e-5,tclev,thlev,tdlev);
    goto label_819;
  label_2080  :
    thlev=0.6e-12;
    p=100.*prng_();
    if (p <= 35.4) goto label_20801;
    if (p <= 93.8) goto label_20802;
    goto label_20803;
  label_20801  :
    decay0_nucltransK(prng_, event_, 2.080,0.037,7.6e-4,3.3e-4,tclev,thlev,tdlev);
    return;
  label_20802  :
    decay0_nucltransK(prng_, event_, 1.262,0.037,1.3e-3,1.4e-5,tclev,thlev,tdlev);
    goto label_819;
  label_20803  :
    decay0_nucltransK(prng_, event_, 0.529,0.037,1.0e-2,0.,tclev,thlev,tdlev);
    goto label_1551;
  label_1579  :
    thlev=0.;
    decay0_nucltransK(prng_, event_, 0.761,0.037,3.4e-3,0.,tclev,thlev,tdlev);
    goto label_819;
  label_1551  :
    thlev=1.01e-12;
    p=100.*prng_();
    if (p <= 52.1) goto label_15511;
    goto label_15512;
  label_15511  :
    decay0_nucltransK(prng_, event_, 1.551,0.037,8.4e-4,9.7e-5,tclev,thlev,tdlev);
    return;
  label_15512  :
    decay0_nucltransK(prng_, event_, 0.733,0.037,4.5e-3,0.,tclev,thlev,tdlev);
    goto label_819;
  label_819  :
    thlev=1.93e-12;
    decay0_nucltransK(prng_, event_, 0.819,0.037,2.9e-3,0.,tclev,thlev,tdlev);
    return;
  label_10000  :
    return;
  label_20000  :
    // print *,'Ba136: wrong level [keV] ',levelkev_
    return;
  }
  // end of Ba136low.f




} // end of namespace bxdecay0

// end of Ba136low.cc
// Local Variables: --
// mode: c++ --
// End: --
