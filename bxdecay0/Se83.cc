// Copyright 1995+3516 V.I. Tretyak
// Copyright 2011+3517 F. Mauger
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
#include <bxdecay0/Se83.h>

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

  void Se83(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_)
  {
    double t;
    double tdlev;
    double p;
    double pbeta;
    double tclev;
    double thlev;
    double thnuc;
    // Scheme of Se83 decay (National Nuclear Data Center (NNDC), Brookhaven National Laboratory).
    // levels in keV.
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 7.05.1998
    thnuc  = 70.1;
    tdnuc_ = tcnuc_ - thnuc / std::log(2.) * std::log(prng_());
    tclev  = 0.;
    pbeta  = 100. * prng_();
    
    // 11 possible β⁺ decay modes
    if (pbeta <= 0.095) {
      decay0_beta(prng_, event_, 0.811, +35, 0., 0., t);
      goto label_3091;
    }
    if (pbeta <= 0.095+0.21) {
      decay0_beta(prng_, event_, 1.092, +35, 0., 0., t);
      goto label_2810;
    }
    if (pbeta <= 0.095+0.21+18.6) {
      decay0_beta(prng_, event_, 1.850, +35, 0., 0., t);
      goto label_2052;
    }
    if (pbeta <= 0.095+0.21+18.6+2.07) {
      decay0_beta(prng_, event_, 1.986, +35, 0., 0., t);
      goto label_1916;
    }
    if (pbeta <= 0.095+0.21+18.6+2.07+2.63) {
      decay0_beta(prng_, event_, 2.242, +35, 0., 0., t);
      goto label_1660;
    }
    if (pbeta <= 0.095+0.21+18.6+2.07+2.63+0.36) {
      decay0_beta(prng_, event_, 2.848, +35, 0., 0., t);
      goto label_1054;
    }
    if (pbeta <= 0.095+0.21+18.6+2.07+2.63+0.36+33.2) {
      decay0_beta(prng_, event_, 2.871, +35, 0., 0., t);
      goto label_1031;
    }
    if (pbeta <= 0.095+0.21+18.6+2.07+2.63+0.36+33.2+12.8) {
      decay0_beta(prng_, event_, 2.914, +35, 0., 0., t);
      goto label_988;
    }
    if (pbeta <= 0.095+0.21+18.6+2.07+2.63+0.36+33.2+12.8+0.14) {
      decay0_beta(prng_, event_, 3.035, +35, 0., 0., t);
      goto label_867;
    }
    if (pbeta <= 0.095+0.21+18.6+2.07+2.63+0.36+33.2+12.8+0.14+0.1) {
      decay0_beta(prng_, event_, 3.103, +35, 0., 0., t);
      goto label_799;
    }
    decay0_beta(prng_, event_, 3.902, +35, 0., 0., t);
    goto label_10000;

    label_3091:
      thlev = 0.0;
      p  = 100. * prng_();
      if (p <= 55.0) {
        decay0_nucltransK(prng_, event_, 2.7347, 0.01347, 0.0, 0.0, tclev, thlev, tdlev);
        goto label_357;
      }
      decay0_nucltransK(prng_, event_, 3.0913, 0.01347, 0.0, 0.0, tclev, thlev, tdlev);
      goto label_10000;
      

    label_2810:
      thlev = 0.0;
      p  = 100. * prng_();
      if (p <= 68.8) {
        decay0_nucltransK(prng_, event_, 1.779, 0.01347, 0.0, 0.0, tclev, thlev, tdlev);
        goto label_1031;
      }
      if (p <= 62.6) {
        decay0_nucltransK(prng_, event_, 2.4532, 0.01347, 0.0, 0.0, tclev, thlev, tdlev);
        goto label_357;
      }
      decay0_nucltransK(prng_, event_, 2.8099, 0.01347, 0.0, 0.0, tclev, thlev, tdlev);
      goto label_10000;

    label_2052:
      thlev = 0.0;
          p  = 100. * prng_();
      if (p <= 0.64) {
        decay0_nucltransK(prng_, event_, 0.3915, 0.01347, 0.0, 0.0, tclev, thlev, tdlev);
        goto label_1660;
      }
      if (p <= 7.1) {
        decay0_nucltransK(prng_, event_, 0.9976, 0.01347, 0.0, 0.0, tclev, thlev, tdlev);
        goto label_1054;
      }
      p  = 100. * prng_();
      if (p <= 18.5) {
        decay0_nucltransK(prng_, event_, 1.0208, 0.01347, 0.0, 0.0, tclev, thlev, tdlev);
        goto label_1031;
      }
      if (p <= 37.3) {
        decay0_nucltransK(prng_, event_, 1.1163, 0.01347, 0.0, 0.0, tclev, thlev, tdlev);
        goto label_988;
      }
      p  = 100. * prng_();
      if (p <= 41.5) {
        decay0_nucltransK(prng_, event_, 1.6947, 0.01347, 0.0, 0.0, tclev, thlev, tdlev);
        goto label_357;
      }
      decay0_nucltransK(prng_, event_, 2.0515, 0.01347, 0.0, 0.0, tclev, thlev, tdlev);
      goto label_10000;

    label_1916:
      thlev = 0.0;
      if (p <= 9.7) {
        decay0_nucltransK(prng_, event_, 0.8845, 0.01347, 0.0, 0.0, tclev, thlev, tdlev);
        goto label_1031;
      }
      p  = 100. * prng_();
      if (p <= 42.5) {
        decay0_nucltransK(prng_, event_, 1.1163, 0.01347, 0.0, 0.0, tclev, thlev, tdlev);
        goto label_799;
      }
      decay0_nucltransK(prng_, event_, 1.5589, 0.01347, 0.0, 0.0, tclev, thlev, tdlev);
      goto label_357;

    label_1660:
      thlev = 0.0;
      if (p <= 30.9) {
        decay0_nucltransK(prng_, event_, 1.3033, 0.01347, 0.0, 0.0, tclev, thlev, tdlev);
        goto label_799;
      }
      decay0_nucltransK(prng_, event_, 1.6601, 0.01347, 0.0, 0.0, tclev, thlev, tdlev);
      goto label_10000;

    label_1054:
      thlev = 0.0;
      decay0_nucltransK(prng_, event_, 1.0538, 0.01347, 0.0, 0.0, tclev, thlev, tdlev);
      goto label_10000;

    label_1031:
      thlev = 0.0;
      if (p <= 0.88) {
        decay0_nucltransK(prng_, event_, 0.2315, 0.01347, 0.0, 0.0, tclev, thlev, tdlev);
        goto label_799;
      }
      p  = 100. * prng_();
      if (p <= 42.3) {
        decay0_nucltransK(prng_, event_, 0.674, 0.01347, 0.0, 0.0, tclev, thlev, tdlev);
        goto label_357;
      }
      decay0_nucltransK(prng_, event_, 1.0306, 0.01347, 0.0, 0.0, tclev, thlev, tdlev);
      goto label_10000;

    label_988:
      thlev = 0.0;
      if (p <= 1.08) {
        decay0_nucltransK(prng_, event_, 0.1889, 0.01347, 0.0, 0.0, tclev, thlev, tdlev);
        goto label_799;
      }
      p  = 100. * prng_();
      if (p <= 3.85) {
        decay0_nucltransK(prng_, event_, 0.6312, 0.01347, 0.0, 0.0, tclev, thlev, tdlev);
        goto label_357;
      }
      decay0_nucltransK(prng_, event_, 0.9881, 0.01347, 0.0, 0.0, tclev, thlev, tdlev);
      goto label_10000;

    label_867:
      thlev = 0.0;
      decay0_nucltransK(prng_, event_, 0.5101, 0.01347, 0.00165, 0.0, tclev, thlev, tdlev);
      goto label_357;

    label_799:
      thlev = 0.0;
      if (p <= 4.91) {
        decay0_nucltransK(prng_, event_, 0.4424, 0.01347, 0.0, 0.0, tclev, thlev, tdlev);
        goto label_357;
      }
      decay0_nucltransK(prng_, event_, 0.7991, 0.01347, 0.0, 0.0, tclev, thlev, tdlev);
      goto label_10000;

    label_357:
      thlev = 0.0;
      decay0_nucltransK(prng_, event_, 0.3567, 0.01347, 0.00382, 0.0, tclev, thlev, tdlev);
      goto label_10000;

    label_10000:
      return;
  
}
  // end of Se83.f

} // end of namespace bxdecay0

// end of Se83.cc
// Local Variables: --
// mode: c++ --
// End: --
