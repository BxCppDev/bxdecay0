// Copyright 1995-2018 V.I. Tretyak
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
#include <bxdecay0/Hf176low.h>

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
  
  void Hf176low(i_random & prng_,
                event & event_,
                const int levelkev_)
  {
    // Subroutine describes the deexcitation process in Hf176 nucleus
    // after 2b-decay of Yb176 to ground and excited 0+ and 2+ levels
    // of Hf176 (NNDC site on 09.11.2018, NDS 107(2006)791).
    // Call  : call Hf176low(levelkeV)
    // Input : levelkeV - energy of Hf176 level (integer in keV) occupied
    //                    initially; following levels can be occupied:
    //                    0+(gs) -   0 keV,
    //                    2+(1)  -  88 keV.
    // Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
    // VIT, 9.11.2018.
    double tdlev;
    double tclev;
    double thlev;
    tclev=0.;
    if (levelkev_ == 88) goto label_88;
    if (levelkev_ ==  0) goto label_10000;
    goto label_20000;
  label_88 :
    thlev=1.43e-9;
    decay0_nucltransK(prng_, event_, 0.088, 0.065, 5.86, 0., tclev, thlev, tdlev);
    return;
  label_10000:
    return;
  label_20000  :
    // print *,'Hf176: wrong level [keV] ',levelkev_
    return;
  }
  
} // end of namespace bxdecay0

// end of Gd156low.cc
// Local Variables: --
// mode: c++ --
// End: --
