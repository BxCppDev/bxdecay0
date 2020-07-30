// Copyright 2018 V.I. Tretyak
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
#include <bxdecay0/Nd144low.h>

// Standar library:
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

  void Nd144low(i_random & prng_, event & event_, const int levelkev_)
  {
    // Subroutine describes the deexcitation process in Nd144 nucleus
    // after eb+/2e decay of Sm144 to the ground and excited 2+ levels
    // of Nd144 (ENSDF on 30.11.2018 and NDS 93(2001)599).
    // Call  : call Nd144low(levelkeV)
    // Input : levelkeV - energy of Nd144low level (integer in keV) occupied
    //                    initially; following levels can be occupied:
    //                    0+(gs) -    0 keV,
    //                    2+(1)  -  697 keV,
    //                    2+(2)  - 1561 keV.
    // Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
    // VIT, 3.12.2018.
    double tclev = 0.;
    double thlev;
    double tdlev;
    double p;
    if (levelkev_ == 1561)
      goto label_1561;
    if (levelkev_ == 697)
      goto label_697;
    if (levelkev_ == 0)
      goto label_10000;
    goto label_20000;
  label_1561:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 91.36)
      goto label_15611;
    goto label_15612;
  label_15611:
    decay0_nucltransK(prng_, event_, 0.864, 0.044, 4.1e-3, 0., tclev, thlev, tdlev);
    goto label_697;
  label_15612:
    decay0_nucltransK(prng_, event_, 1.561, 0.044, 1.0e-3, 9.8e-5, tclev, thlev, tdlev);
    return;
  label_697:
    thlev = 2.97e-12;
    decay0_nucltransK(prng_, event_, 0.697, 0.044, 5.1e-3, 0., tclev, thlev, tdlev);
    return;
  label_10000:
    return;
  label_20000:
    // print *,'Nd144: wrong level [keV] ',levelkev_
    return;
  }

} // end of namespace bxdecay0

// end of Nd144low.cc
// Local Variables: --
// mode: c++ --
// End: --
