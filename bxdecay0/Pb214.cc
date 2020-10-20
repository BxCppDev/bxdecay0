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
#include <bxdecay0/Pb214.h>

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

  void Pb214(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_)
  {
    double t;
    double tdlev;
    double p;
    double pbeta;
    double tclev;
    double thlev;
    double thnuc;
    // Scheme of 214Pb decay ("Table of Isotopes", 7th ed., 1978).
    // Three-figured labels correspond to energies of 214Bi
    // excited levels in keV.
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 11.08.1992, 22.10.1995.
    // VIT, 4.01.2007: updated to NDS 76(1995)127, and conversion from K, L, M shells
    // is introduced.
    thnuc  = 1608.;
    tdnuc_ = tcnuc_ - thnuc / std::log(2.) * std::log(prng_());
    tclev  = 0.;
    pbeta  = 100. * prng_();
    if (pbeta <= 0.034) {
      goto label_888; // 0.034%
    }
    if (pbeta <= 2.766) {
      goto label_839; // 2.732%
    }
    if (pbeta <= 2.787) {
      goto label_797; // 0.021%
    }
    if (pbeta <= 3.951) {
      goto label_534; // 1.164%
    }
    if (pbeta <= 52.172) {
      goto label_352; // 48.221%
    }
    if (pbeta <= 93.787) {
      goto label_295; // 41.615%
    }
    goto label_10000; // 6.213%
  label_888:
    decay0_beta(prng_, event_, 0.135, 83., 0., 0., t);
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 0.511, 0.091, 6.0e-2, 0., tclev, thlev, tdlev);
    goto label_37700;
  label_839:
    decay0_beta(prng_, event_, 0.184, 83., 0., 0., t);
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 21.3) {
      goto label_83901; // 21.3%
    }
    if (p <= 60.1) {
      goto label_83902; // 38.8%
    }
    if (p <= 72.9) {
      goto label_83903; // 12.8%
    }
    if (p <= 75.4) {
      goto label_83904; // 2.5%
    }
    if (p <= 90.8) {
      goto label_83905; // 15.4%
    }
    if (p <= 98.8) {
      goto label_83906; // 8.0%
    }
    goto label_83907;   // 1.2%
  label_83901:
    decay0_nucltransKLM(prng_, event_, 0.839, 0.091, 2.99e-3, 0.016, 4.7e-4, 0.004, 1.5e-4, 0., tclev, thlev, tdlev);
    return;
  label_83902:
    decay0_nucltransKLM(prng_, event_, 0.786, 0.091, 3.38e-3, 0.016, 5.3e-4, 0.004, 1.7e-4, 0., tclev, thlev, tdlev);
    goto label_53000;
  label_83903:
    decay0_nucltransKLM(prng_, event_, 0.580, 0.091, 6.06e-3, 0.016, 9.7e-4, 0.004, 3.2e-4, 0., tclev, thlev, tdlev);
    goto label_25900;
  label_83904:
    decay0_nucltransKLM(prng_, event_, 0.544, 0.091, 6.90e-3, 0.016, 1.11e-3, 0.004, 3.7e-4, 0., tclev, thlev, tdlev);
    goto label_29500;
  label_83905:
    decay0_nucltransKLM(prng_, event_, 0.487, 0.091, 8.65e-3, 0.016, 1.41e-3, 0.004, 4.4e-4, 0., tclev, thlev, tdlev);
    goto label_35200;
  label_83906:
    decay0_nucltransKLM(prng_, event_, 0.462, 0.091, 9.64e-3, 0.016, 1.58e-3, 0.004, 4.8e-4, 0., tclev, thlev, tdlev);
    goto label_37700;
  label_83907:
    decay0_nucltransKLM(prng_, event_, 0.305, 0.091, 2.40e-2, 0.016, 4.1e-3, 0.004, 1.3e-3, 0., tclev, thlev, tdlev);
    goto label_53400;
  label_797:
    decay0_beta(prng_, event_, 0.226, 83., 0., 0., t);
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 0.538, 0.091, 8.5e-3, 0., tclev, thlev, tdlev);
    goto label_25900;
  label_534:
    decay0_beta(prng_, event_, 0.489, 83., 0., 0., t);
  label_53400:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 16.3) {
      goto label_53401; // 16.3%
    }
    if (p <= 46.0) {
      goto label_53402; // 29.7%
    }
    goto label_53403;   // 54.0%
  label_53401:
    decay0_nucltransKL(prng_, event_, 0.534, 0.091, 5.0e-2, 0.016, 1.0e-2, 0., tclev, thlev, tdlev);
    return;
  label_53402:
    decay0_nucltransKLM(prng_, event_, 0.480, 0.091, 1.22e-1, 0.016, 1.9e-2, 0.004, 6.0e-3, 0., tclev, thlev, tdlev);
    goto label_53000;
  label_53403:
    decay0_nucltransKLM(prng_, event_, 0.275, 0.091, 2.9e-1, 0.016, 7.3e-2, 0.004, 2.4e-2, 0., tclev, thlev, tdlev);
    goto label_25900;
  label_37700:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 26.2) {
      goto label_37701; // 26.2%
    }
    goto label_37702;   // 73.8%
  label_37701:
    decay0_nucltransK(prng_, event_, 0.324, 0.091, 2.1e-1, 0., tclev, thlev, tdlev);
    goto label_53000;
  label_37702:
    decay0_nucltransK(prng_, event_, 0.314, 0.091, 2.3e-1, 0., tclev, thlev, tdlev);
    goto label_63000;
  label_352:
    decay0_beta(prng_, event_, 0.671, 83., 0., 0., t);
  label_35200:
    thlev = 0.;
    decay0_nucltransKLM(prng_, event_, 0.352, 0.091, 2.55e-1, 0.016, 4.41e-2, 0.004, 1.38e-2, 0., tclev, thlev, tdlev);
    return;
  label_295:
    decay0_beta(prng_, event_, 0.728, 83., 0., 0., t);
  label_29500:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 67.10) {
      goto label_29501; // 67.1%
    }
    goto label_29502;   // 32.9%
  label_29501:
    decay0_nucltransKLM(prng_, event_, 0.295, 0.091, 3.8e-1, 0.016, 6.9e-2, 0.004, 2.2e-2, 0., tclev, thlev, tdlev);
    return;
  label_29502:
    decay0_nucltransKLM(prng_, event_, 0.242, 0.091, 7.13e-1, 0.016, 1.23e-1, 0.004, 3.88e-2, 0., tclev, thlev, tdlev);
    goto label_53000;
  label_25900:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 81.4) {
      goto label_25901; // 81.4%
    }
    if (p <= 83.8) {
      goto label_25902; // 2.4%
    }
    goto label_25903;   // 16.2%
  label_25901:
    decay0_nucltransKLM(prng_, event_, 0.259, 0.091, 5.92e-1, 0.016, 1.03e-1, 0.004, 3.2e-2, 0., tclev, thlev, tdlev);
    return;
  label_25902:
    decay0_nucltransKLM(prng_, event_, 0.206, 0.091, 1.12e+0, 0.016, 1.95e-1, 0.004, 6.1e-2, 0., tclev, thlev, tdlev);
    goto label_53000;
  label_25903:
    decay0_nucltransKLM(prng_, event_, 0.196, 0.091, 1.28e+0, 0.016, 2.23e-1, 0.004, 7.0e-2, 0., tclev, thlev, tdlev);
    goto label_63000;
  label_63000:
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 0.063, 0.016, 1.0e+1, 0., tclev, thlev, tdlev);
    return;
  label_53000:
    thlev = 0.;
    decay0_nucltransKL(prng_, event_, 0.053, 0.016, 9.69e+0, 0.004, 3.05e+0, 0., tclev, thlev, tdlev);
    return;
  label_10000:
    decay0_beta(prng_, event_, 1.023, 83., 0., 0., t);
    return;
  }
  // end of Pb214.f

} // end of namespace bxdecay0

// end of Pb214.cc
// Local Variables: --
// mode: c++ --
// End: --
