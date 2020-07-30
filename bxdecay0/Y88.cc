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
#include <bxdecay0/Y88.h>

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

  void Y88(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_)
  {
    double t;
    double tdlev;
    double p;
    double pdecay;
    double pec;
    double tclev;
    double thlev;
    double thnuc;
    // Scheme of Y88 decay ("Table of Isotopes", 7th ed., 1978).
    // Accuracy in description of: decay branches - 0.001%,
    // : deexcitation process - 0.001%.
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 20.07.1993, 22.10.1995.
    // VIT, 12.11.2006 (update to NDS 105(2005)419 and change of beta+ spectrum
    // shape)
    thnuc  = 9.2124864e+6;
    tdnuc_ = tcnuc_ - thnuc / std::log(2.) * std::log(prng_());
    tclev  = 0.;
    pdecay = 100. * prng_();
    if (pdecay <= 99.79) {
      goto label_1;
    }
    goto label_2;
    // EC to Sr88
  label_1:
    decay0_gamma(prng_, event_, 0.016, 0., 0., t);
    pec = pdecay;
    if (pec <= 0.065) {
      goto label_35850;
    }
    if (pec <= 0.093) {
      goto label_32190;
    }
    if (pec <= 94.490) {
      goto label_27340;
    }
    goto label_18360;
    // b+ to Sr88
    // change to the approximation to the 1st forbidden unique shape
  label_2:
    decay0_beta2(prng_, event_, 0.765, -38., 0., 0., t, 1, 1., 0., 0., 0.);
    goto label_18360;
  label_35850:
    thlev = 0.14e-9;
    decay0_nucltransK(prng_, event_, 0.851, 0.016, 8.5e-4, 0., tclev, thlev, tdlev);
    goto label_27340;
  label_32190:
    thlev = 0.13e-12;
    p     = 100. * prng_();
    if (p <= 25.) {
      goto label_32191;
    }
    goto label_32192;
  label_32191:
    decay0_nucltransK(prng_, event_, 3.219, 0.016, 6.0e-5, 8.7e-4, tclev, thlev, tdlev);
    return;
  label_32192:
    decay0_nucltransK(prng_, event_, 1.382, 0.016, 2.6e-4, 4.8e-5, tclev, thlev, tdlev);
    goto label_18360;
  label_27340:
    thlev = 0.78e-12;
    p     = 100. * prng_();
    if (p <= 0.75) {
      goto label_27341;
    }
    goto label_27342;
  label_27341:
    decay0_nucltransK(prng_, event_, 2.734, 0.016, 1.2e-4, 3.3e-4, tclev, thlev, tdlev);
    return;
  label_27342:
    decay0_nucltransK(prng_, event_, 0.898, 0.016, 3.1e-4, 0., tclev, thlev, tdlev);
    goto label_18360;
  label_18360:
    thlev = 0.148e-12;
    decay0_nucltransK(prng_, event_, 1.836, 0.016, 1.4e-4, 2.3e-4, tclev, thlev, tdlev);
    return;
  }
  // end of Y88.f

} // end of namespace bxdecay0

// end of Y88.cc
// Local Variables: --
// mode: c++ --
// End: --
