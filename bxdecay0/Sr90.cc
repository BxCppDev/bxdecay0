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
#include <bxdecay0/Sr90.h>

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

  void Sr90(i_random & prng_,
            event & event_,
            const double tcnuc_,
            double & tdnuc_)
  {
    double t;
    //double tdlev;
    double thnuc;
    // Scheme of Sr90 decay ("Table of Isotopes", 7th ed., 1978).
    // Accuracy in description of: decay branches - 0.001%,
    // : deexcitation process - 0.001%.
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // Slight update to NDS 82(1997)379.
    // VIT, 9.08.1993, 22.10.1995, 26.10.2006.
    thnuc=0.9085184E+09;
    tdnuc_=tcnuc_-thnuc/std::log(2.)*std::log(prng_());
    // decay0_beta(prng_, event_, 0.546,39.,0.,0.,t)
    // Change from the allowed shape to the 1st forbidden unique with empirical
    // correction from: H.H.Hansen, Appl. Rad. Isot. 34(1983)1241
    decay0_beta_1fu(prng_, event_, 0.546,39.,0.,0.,t,0.,-0.032,0.,0.);
    return;
  }
  // end of Sr90.f




} // end of namespace bxdecay0

// end of Sr90.cc
// Local Variables: --
// mode: c++ --
// End: --
