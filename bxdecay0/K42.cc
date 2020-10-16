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
#include <bxdecay0/K42.h>

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

  void K42(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_)
  {
    double t;
    double tdlev;
    double p;
    double pbeta;
    double tclev;
    double thlev;
    double thnuc;
    // Scheme of K42 decay (B.Singh et al., NDS 92(2001)1
    // with additional information from ToI-1978 and ToI-1998).
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 31.03.2006
    thnuc  = 44496.;
    tdnuc_ = tcnuc_ - thnuc / std::log(2.) * std::log(prng_());
    tclev  = 0.;
    pbeta  = 100. * prng_();
    if (pbeta <= 0.07) {
      goto label_3446;
    }
    if (pbeta <= 0.12) {
      goto label_2424;
    }
    if (pbeta <= 0.46) {
      goto label_1837;
    }
    if (pbeta <= 18.10) {
      goto label_1525;
    }
    goto label_10000;
  label_3446:
    decay0_beta(prng_, event_, 0.080, 20., 0., 0., t);
    ////    label_34460  :
    thlev = 250.e-15; // ToI-1998
    p     = 100. * prng_();
    if (p <= 63.66) {
      goto label_34461;
    }
    if (p <= 94.88) {
      goto label_34462;
    }
    goto label_34463;
  label_34461:
    decay0_nucltransK(prng_, event_, 1.921, 0.004, 1.2e-5, 5.8e-4, tclev, thlev, tdlev);
    goto label_15250;
  label_34462:
    decay0_nucltransK(prng_, event_, 1.021, 0.004, 3.9e-5, 0., tclev, thlev, tdlev);
    goto label_24240;
  label_34463:
    decay0_nucltransK(prng_, event_, 0.692, 0.004, 8.7e-5, 0., tclev, thlev, tdlev);
    goto label_27530;
  label_27530:
    thlev = 3.0e-12; // ToI-1998
    ////    label_27531  :
    decay0_nucltransK(prng_, event_, 1.228, 0.004, 5.6e-5, 1.4e-5, tclev, thlev, tdlev);
    goto label_15250;
  label_2424:
    decay0_beta(prng_, event_, 1.101, 20., 0., 0., t);
  label_24240:
    thlev = 140.e-15; // ToI-1998
    p     = 100. * prng_();
    if (p <= 27.78) {
      goto label_24241;
    }
    goto label_24242;
  label_24241:
    decay0_nucltransK(prng_, event_, 2.424, 0.004, 1.5e-5, 5.2e-4, tclev, thlev, tdlev);
    return;
  label_24242:
    decay0_nucltransK(prng_, event_, 0.900, 0.004, 8.3e-5, 0., tclev, thlev, tdlev);
    goto label_15250;
    // change to the 1st forbidden unique
  label_1837:
    decay0_beta_1fu(prng_, event_, 1.688, 20., 0., 0., t, 0., 0., 0., 0.);
    ////    label_18370  :
    thlev = 0.33e-9;
    p     = 100. * prng_();
    if (p <= 2.1) {
      goto label_18371; // ToI-1978
    }
    goto label_18372;
  label_18371:
    p = 100. * prng_();
    if (p <= 90.) {
      ;
      decay0_pair(prng_, event_, 0.815, tclev, thlev, tdlev);
    } else {
      ;
      decay0_electron(prng_, event_, 1.833, tclev, thlev, tdlev);
      decay0_gamma(prng_, event_, 0.004, 0., 0., tdlev);
    };
    return;
  label_18372:
    decay0_nucltransK(prng_, event_, 0.313, 0.004, 3.4e-3, 0., tclev, thlev, tdlev);
    goto label_15250;
    // change to forbidden spectrum with std::experimental corrections from
    // H.Daniel, RMP 49(1968)659
  label_1525:
    decay0_beta1(prng_, event_, 2.000, 20., 0., 0., t, 0.81, 0.15, -0.02, 0.);
  label_15250:
    thlev = 0.82e-12; // ToI-1998
    decay0_nucltransK(prng_, event_, 1.525, 0.004, 3.6e-5, 9.8e-5, tclev, thlev, tdlev);
    return;
    // 1st forbidden unique with std::experimental corrections from
    // H.Daniel et al., PRB 136(1964)1240 and RMP 40(1968)659
  label_10000:
    decay0_beta_1fu(prng_, event_, 3.525, 20., 0., 0., t, 0., -0.01, 0., 0.);
    return;
  }
  // end of K42.f

} // end of namespace bxdecay0

// end of K42.cc
// Local Variables: --
// mode: c++ --
// End: --
