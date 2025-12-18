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
#include <bxdecay0/Sc44.h>

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

  void Sc44(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_)
  {
    double t;
    double tdlev;
    double p;
    double pbeta;
    double tclev;
    double thlev;
    double thnuc;
    // Scheme of Sc44 decay (National Nuclear Data Center (NNDC), Brookhaven National Laboratory).
    // levels in keV.
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 7.05.1998
    thnuc  = 1.45512e+04;
    tdnuc_ = tcnuc_ - thnuc / std::log(2.) * std::log(prng_());
    tclev  = 0.;
    pbeta  = 100. * prng_();
    
    // One possible β⁺ decay mode
    if (pbeta <= 94.27) {
      decay0_beta(prng_, event_, 1.4737, -20, 0., 0., t);
      goto label_1157;
    }
    // Three electron-capture processes
    if (pbeta <= 94.2744) {
      decay0_gamma(prng_, event_, 0.04, 0., 0., t);
      goto label_3302;
    }
    if (pbeta <= 95.293) {
      decay0_gamma(prng_, event_, 0.04, 0., 0., t);
      goto label_2657;
    }
    decay0_gamma(prng_, event_, 0.04, 0., 0., t);
    goto label_1157;

    label_3302:
      thlev = 35e-15;
      p  = 100. * prng_();
      if (p <= 72.55) {
        decay0_nucltransK(prng_, event_, 2.14442, 0.00404, 0.0, 0.0, tclev, thlev, tdlev);
        goto label_1157;
      }
      decay0_nucltransK(prng_, event_, 3.30133, 0.00404, 9.3e-6, 0.0, tclev, thlev, tdlev);
      goto label_10000;
      

    label_2657:
      thlev = 30e-15;
      p  = 100. * prng_();
      if (p <= 89.0) {
        decay0_nucltransK(prng_, event_, 1.4995, 0.00404, 3.1e-5, 0.0, tclev, thlev, tdlev);
        goto label_1157;
      }
      decay0_nucltransK(prng_, event_, 2.6564, 0.00404, 1.34e-5, 0.0, tclev, thlev, tdlev);
      goto label_10000;

    label_1157:
      thlev = 2.95e-12;
      decay0_nucltransK(prng_, event_, 1.157, 0.00404, 6.0e-5, 0.0, tclev, thlev, tdlev);

    label_10000:
      return;
  
}
  // end of Sc44.f

} // end of namespace bxdecay0

// end of Sc44.cc
// Local Variables: --
// mode: c++ --
// End: --
