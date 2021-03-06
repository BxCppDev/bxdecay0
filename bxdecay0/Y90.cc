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
#include <bxdecay0/Y90.h>

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

  void Y90(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_)
  {
    double t;
    double tdlev;
    double p;
    double pbeta;
    double tclev;
    double thlev;
    double thnuc;
    // Scheme of Y90 decay ("Table of Isotopes", 7th ed., 1978).
    // Accuracy in description of: decay branches - 0.001%,
    // : deexcitation process - 0.001%.
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // Slight update to NDS 82(1997)379.
    // VIT, 9.08.1993, 22.10.1995, 26.10.2006
    thnuc  = 230400.;
    tdnuc_ = tcnuc_ - thnuc / std::log(2.) * std::log(prng_());
    tclev  = 0.;
    pbeta  = 100. * prng_();
    if (pbeta <= 0.0115) {
      goto label_1761;
    }
    goto label_10000;
  label_1761:
    decay0_beta_1fu(prng_, event_, 0.519, 40., 0., 0., t, 0., 0., 0., 0.);
    ////    label_17610  :
    thlev = 61.3e-9;
    p     = 100. * prng_();
    // to reproduce 31.86e-6 branching ratio for e+e- pair,
    // R.G.Selwyn et al., Appl. Rad. Isot. 65(2007)318
    if (p <= 27.7) {
      goto label_17611;
    }
    goto label_17612;
  label_17611:
    decay0_pair(prng_, event_, 0.739, tclev, thlev, tdlev);
    return;
  label_17612:
    decay0_electron(prng_, event_, 1.743, tclev, thlev, tdlev);
    decay0_gamma(prng_, event_, 0.018, 0., 0., tdlev);
    return;
    // Change from the allowed shape to the 1st forbidden unique with empirical
    // correction from: H.H.Hansen, Appl. Rad. Isot. 34(1983)1241
  label_10000:
    decay0_beta_1fu(prng_, event_, 2.280, 40., 0., 0., t, 0., -0.0078, 0., 0.);
    return;
  }
  // end of Y90.f

} // end of namespace bxdecay0

// end of Y90.cc
// Local Variables: --
// mode: c++ --
// End: --
