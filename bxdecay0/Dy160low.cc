// Copyright 2024 V.I. Tretyak
// Copyright 2024 F. Mauger
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
#include <bxdecay0/Dy160low.h>

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
//#include <bxdecay0/nucltransKL.h>
//#include <bxdecay0/nucltransKLM.h>
//#include <bxdecay0/nucltransKLM_Pb.h>
//#include <bxdecay0/pair.h>
#include <bxdecay0/particle.h>
// #include <bxdecay0/positron.h>

namespace bxdecay0 {

  void Dy160low(i_random & prng_, event & event_, const int levelkev_)
  {
    // Subroutine describes the deexcitation process in Dy160 nucleus
    // after 2b-decay of Gd160 to ground and excited 2+ levels
    // of Dy160 (NNDC site on 17.12.2024).
    // Call  : call Dy160low(levelkeV)
    // Input : levelkeV - energy of Dy160 level (integer in keV) occupied
    //                    initially; following levels can be occupied:
    //                    0+(gs) -    0 keV,
    //                    2+(1)  -   87 keV,
    double tdlev;
    double p;
    double tclev;
    double thlev;
    tclev = 0.;
    if (levelkev_ == 87) {
      goto label_87;
    }
    if (levelkev_ == 0) {
      goto label_10000;
    }
    goto label_20000;
  label_87:
    thlev = 2.02e-9;
    decay0_nucltransK(prng_, event_, 0.0867877, 0.054, 4.63, 0., tclev, thlev, tdlev);
    return;
  label_10000:
    return;
  label_20000:
    // print *, 'Dy160: wrong level [keV] ', levelkev
    return;
  }

} // end of namespace bxdecay0

// end of Dy162low.cc
// Local Variables: --
// mode: c++ --
// End: --
