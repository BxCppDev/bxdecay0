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
#include <bxdecay0/Yb170low.h>

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

  void Yb170low(i_random & prng_, event & event_, const int levelkev_)
  {
    // Subroutine describes the deexcitation process in Yb170 nucleus
    // after 2b-decay of Er170 to ground and excited 0+ and 2+ levels
    // of Yb170 (NNDC site on 04.02.2018, NDS 96(2002)611).
    // Call  : call Yb170low(levelkeV)
    // Input : levelkeV - energy of Yb170 level (integer in keV) occupied
    //                    initially; following levels can be occupied:
    //                    0+(gs) -   0 keV,
    //                    2+(1)  -  84 keV.
    // Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
    // VIT, 22.06.2012.
    double tdlev;
    double tclev;
    double thlev;
    tclev = 0.;
    if (levelkev_ == 84)
      goto label_84;
    if (levelkev_ == 0)
      goto label_10000;
    goto label_20000;
  label_84:
    thlev = 1.6e-9;
    decay0_nucltransK(prng_, event_, 0.084, 0.061, 6.37, 0., tclev, thlev, tdlev);
    return;
  label_10000:
    return;
  label_20000:
    // print *,'Yb170: wrong level [keV] ',levelkev_
    return;
  }

} // end of namespace bxdecay0

// end of Gd156low.cc
// Local Variables: --
// mode: c++ --
// End: --
