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

  void Kr82low(i_random & prng_,
               event & event_,
               const int levelkev_)
  {
    //double t;
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
    // 2+(1) - 776 keV,
    // 2+(2) - 1475 keV.
    // Output: // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 28.06.1993, 22.10.1995.
    tclev=0.;
    if (levelkev_ == 1475) goto label_1475;
    if (levelkev_ ==  776) goto label_776;
    if (levelkev_ ==  0) goto label_10000;
    goto label_20000;
  label_1475  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 36.7) goto label_14751;
    goto label_14752;
  label_14751  :
    decay0_nucltransK(prng_, event_, 1.475,0.014,2.0e-4,0.5e-4,tclev,thlev,tdlev);
    return;
  label_14752  :
    decay0_nucltransK(prng_, event_, 0.698,0.014,1.3e-3,0.,tclev,thlev,tdlev);
    goto label_776;
  label_776  :
    thlev=5.e-12;
    decay0_nucltransK(prng_, event_, 0.776,0.014,9.3e-4,0.,tclev,thlev,tdlev);
    return;
  label_10000  :
    return;
  label_20000  :
    // print *,'Kr82: wrong level [keV] ',levelkev_
    return;
  }
  // end of Kr82low.f




} // end of namespace bxdecay0

// end of Kr82low.cc
// Local Variables: --
// mode: c++ --
// End: --
