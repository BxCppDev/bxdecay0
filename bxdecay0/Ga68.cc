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
#include <bxdecay0/Ga68.h>

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

  void Ga68(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_)
  {
    double t;
    double tdlev;
    double p;
    double pbeta;
    double tclev;
    double thlev;
    double thnuc;
    // Scheme of Ga68 decay (National Nuclear Data Center (NNDC), Brookhaven National Laboratory).
    // levels in keV.
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 7.05.1998
    thnuc  = 4.0626e3;
    tdnuc_ = tcnuc_ - thnuc / std::log(2.) * std::log(prng_());
    tclev  = 0.;
    pbeta  = 100. * prng_();
    
    // Three possible β⁺ decay modes
    if (pbeta <= 0.000285) {
      decay0_beta(prng_, event_, 1.8991, -30, 0., 0., t);
      goto label_1656;
    }
    if (pbeta <= 1.190) {
      decay0_beta(prng_, event_, 0.8217, -30, 0., 0., t);
      goto label_1077;
    }
    if (pbeta <= 88.9103) {
      decay0_beta(prng_, event_, 0.2432, -30, 0., 0., t);
      goto label_10000;
    }
    // Six electron-capture processes
    if (pbeta <= 88.9207) {
      decay0_gamma(prng_, event_, 0.01, 0., 0., t);
      goto label_2822;
    }
    if (pbeta <= 89.0167) {
      decay0_gamma(prng_, event_, 0.01, 0., 0., t);
      goto label_2339;
    }
    if (pbeta <= 89.2507) {
      decay0_gamma(prng_, event_, 0.01, 0., 0., t);
      goto label_1883;
    }
    if (pbeta <= 89.2842) {
      decay0_gamma(prng_, event_, 0.01, 0., 0., t);
      goto label_1656;
    }
    if (pbeta <= 91.0842) {
      decay0_gamma(prng_, event_, 0.01, 0., 0., t);
      goto label_1077;
    }
    goto label_10000;

    label_2822:
      thlev = 0.0;
      p  = 100. * prng_();
      if (p <= 2.5) {
        decay0_nucltransK(prng_, event_, 0.4834, 0.0097, 1.5e-3, 0.0, tclev, thlev, tdlev);
        goto label_2339;
      }
      if (p <= 4.2) {
        decay0_nucltransK(prng_, event_, 0.9387, 0.0097, 4.0, 0.0, tclev, thlev, tdlev);
        goto label_1883;
      }
      if (p <= 4.4) {
        decay0_nucltransK(prng_, event_, 1.166, 0.0097, 8.4e-1, 0.0, tclev, thlev, tdlev);
        goto label_1656;}
      if (p <= 8.8) {
        decay0_nucltransK(prng_, event_, 2.822, 0.0097, 3.0e-5, 0.0, tclev, thlev, tdlev);
        goto label_10000;
      }
      decay0_nucltransK(prng_, event_, 1.744, 0.0097, 3.5e-5, 0.0, tclev, thlev, tdlev);
      goto label_1077;
      

    label_2339:
      thlev = 0.24e-12;
      p  = 100. * prng_();
      if (p <= 0.32) {
        decay0_nucltransK(prng_, event_, 0.6826, 0.0097, 1.3e-1, 0.0, tclev, thlev, tdlev);
        goto label_1656;
      }
      if (p <= 0.988) {
        decay0_nucltransK(prng_, event_, 1.261, 0.0097, 7.7e-5, 0.0, tclev, thlev, tdlev);
        goto label_1077;
        }
      decay0_nucltransK(prng_, event_, 2.338, 0.0097, 4.7e-5, 0.0, tclev, thlev, tdlev);
      goto label_10000;
    label_1883:
      thlev = 1.6e-12;
      p  = 100. * prng_();
      if (p <= 0.0005) {
        decay0_nucltransK(prng_, event_, 0.2273, 0.0097, 2.7e-2, 0.0, tclev, thlev, tdlev);
        goto label_1656;
        }
      if (p <= 39.5) {
        decay0_nucltransK(prng_, event_, 0.8058, 0.0097, 5.1e-7, 0.0, tclev, thlev, tdlev);
        goto label_1077;
        }
      decay0_nucltransK(prng_, event_, 1.883, 0.0097, 6.9e-5, 0.0, tclev, thlev, tdlev);
      goto label_10000;
    label_1656:
      thlev = 70e-12;
      decay0_nucltransK(prng_, event_, 0.5785, 0.0097, 6.6e-6, 0.0, tclev, thlev, tdlev);
      goto label_1077;
    label_1077:
      thlev = 1.57e-12;
      decay0_nucltransK(prng_, event_, 1.077, 0.0097, 9.3e-10, 0.0, tclev, thlev, tdlev);
      goto label_10000;
    label_10000:
      return;
  
}
  // end of Ga68.f

} // end of namespace bxdecay0

// end of Ga68.cc
// Local Variables: --
// mode: c++ --
// End: --
