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
#include <bxdecay0/Eu147.h>

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

  void Eu147(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_)
  {
    double t;
    double tdlev;
    double p;
    double pdecay;
    double tclev;
    double thlev;
    double thnuc;
    // Scheme of 147Eu decay ("Table of Isotopes", 7th ed., 1978).
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 10.03.1996.
    thnuc  = 1.9008e6;
    tdnuc_ = tcnuc_ - thnuc / std::log(2.) * std::log(prng_());
    tclev  = 0.;
    pdecay = 100. * prng_();
    if (pdecay <= 0.002) {
      ;
      decay0_alpha(prng_, event_, 2.908, 0., 0., t);
      return;
    };
    if (pdecay <= 0.202) {
      goto label_1646;
    }
    if (pdecay <= 0.502) {
      goto label_1549;
    }
    if (pdecay <= 0.552) {
      goto label_1471;
    }
    if (pdecay <= 1.552) {
      goto label_1453;
    }
    if (pdecay <= 2.052) {
      goto label_1318;
    }
    if (pdecay <= 2.252) {
      goto label_1304;
    }
    if (pdecay <= 11.352) {
      goto label_1077;
    }
    if (pdecay <= 11.582) {
      goto label_1063;
    }
    if (pdecay <= 17.102) {
      goto label_1054;
    }
    if (pdecay <= 17.182) {
      goto label_1007;
    }
    if (pdecay <= 35.382) {
      goto label_799;
    }
    if (pdecay <= 57.592) {
      goto label_197;
    }
    if (pdecay <= 76.792) {
      goto label_121;
    }
    goto label_10000;
  label_1646:
    decay0_gamma(prng_, event_, 0.049, 0., 0., t);
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 1.449, 0.047, 5.0e-4, 0.8e-4, tclev, thlev, tdlev);
    goto label_19700;
  label_1549:
    decay0_gamma(prng_, event_, 0.049, 0., 0., t);
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 31.) {
      goto label_15491;
    }
    goto label_15492;
  label_15491:
    decay0_nucltransK(prng_, event_, 1.427, 0.047, 5.0e-4, 0.7e-4, tclev, thlev, tdlev);
    goto label_12100;
  label_15492:
    decay0_nucltransK(prng_, event_, 0.750, 0.047, 1.8e-3, 0., tclev, thlev, tdlev);
    goto label_79900;
  label_1471:
    decay0_gamma(prng_, event_, 0.049, 0., 0., t);
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 1.350, 0.047, 5.5e-4, 0.6e-4, tclev, thlev, tdlev);
    goto label_12100;
  label_1453:
    decay0_gamma(prng_, event_, 0.049, 0., 0., t);
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 24.) {
      goto label_14531;
    }
    goto label_14532;
  label_14531:
    decay0_nucltransK(prng_, event_, 1.332, 0.047, 5.5e-4, 0.5e-4, tclev, thlev, tdlev);
    goto label_12100;
  label_14532:
    decay0_nucltransK(prng_, event_, 1.256, 0.047, 6.0e-4, 0.4e-4, tclev, thlev, tdlev);
    goto label_19700;
  label_1318:
    decay0_gamma(prng_, event_, 0.049, 0., 0., t);
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 22.8) {
      goto label_13181;
    }
    if (p <= 68.3) {
      goto label_13182;
    }
    goto label_13183;
  label_13181:
    decay0_nucltransK(prng_, event_, 1.318, 0.047, 5.5e-4, 0.5e-4, tclev, thlev, tdlev);
    return;
  label_13182:
    decay0_nucltransK(prng_, event_, 1.197, 0.047, 6.5e-4, 0.3e-4, tclev, thlev, tdlev);
    goto label_12100;
  label_13183:
    decay0_nucltransK(prng_, event_, 1.120, 0.047, 7.5e-4, 0.2e-4, tclev, thlev, tdlev);
    goto label_19700;
  label_1304:
    decay0_gamma(prng_, event_, 0.049, 0., 0., t);
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 15.) {
      goto label_13041;
    }
    goto label_13042;
  label_13041:
    decay0_nucltransK(prng_, event_, 1.107, 0.047, 7.5e-4, 0.1e-4, tclev, thlev, tdlev);
    goto label_19700;
  label_13042:
    decay0_nucltransK(prng_, event_, 0.505, 0.047, 4.0e-3, 0., tclev, thlev, tdlev);
    goto label_79900;
  label_1077:
    decay0_gamma(prng_, event_, 0.049, 0., 0., t);
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 62.5) {
      goto label_10771;
    }
    if (p <= 98.5) {
      goto label_10772;
    }
    goto label_10773;
  label_10771:
    decay0_nucltransK(prng_, event_, 1.077, 0.047, 4.3e-3, 0.1e-4, tclev, thlev, tdlev);
    return;
  label_10772:
    decay0_nucltransK(prng_, event_, 0.956, 0.047, 5.5e-3, 0., tclev, thlev, tdlev);
    goto label_12100;
  label_10773:
    decay0_nucltransK(prng_, event_, 0.880, 0.047, 9.5e-3, 0., tclev, thlev, tdlev);
    goto label_19700;
  label_1063:
    decay0_gamma(prng_, event_, 0.049, 0., 0., t);
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 40.) {
      goto label_10631;
    }
    goto label_10632;
  label_10631:
    decay0_nucltransK(prng_, event_, 1.063, 0.047, 1.1e-3, 0.1e-4, tclev, thlev, tdlev);
    return;
  label_10632:
    decay0_nucltransK(prng_, event_, 0.942, 0.047, 1.3e-3, 0., tclev, thlev, tdlev);
    goto label_12100;
  label_1054:
    decay0_gamma(prng_, event_, 0.049, 0., 0., t);
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 57.) {
      goto label_10541;
    }
    goto label_10542;
  label_10541:
    decay0_nucltransK(prng_, event_, 0.933, 0.047, 1.3e-3, 0., tclev, thlev, tdlev);
    goto label_12100;
  label_10542:
    decay0_nucltransK(prng_, event_, 0.857, 0.047, 1.6e-3, 0., tclev, thlev, tdlev);
    goto label_19700;
  label_1007:
    decay0_gamma(prng_, event_, 0.049, 0., 0., t);
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 45.) {
      goto label_10071;
    }
    goto label_10072;
  label_10071:
    decay0_nucltransK(prng_, event_, 0.886, 0.047, 1.5e-3, 0., tclev, thlev, tdlev);
    goto label_12100;
  label_10072:
    decay0_nucltransK(prng_, event_, 0.809, 0.047, 9.0e-3, 0., tclev, thlev, tdlev);
    goto label_19700;
  label_799:
    decay0_gamma(prng_, event_, 0.049, 0., 0., t);
  label_79900:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 24.2) {
      goto label_79901;
    }
    if (p <= 71.7) {
      goto label_79902;
    }
    goto label_79903;
  label_79901:
    decay0_nucltransK(prng_, event_, 0.799, 0.047, 4.5e-3, 0., tclev, thlev, tdlev);
    return;
  label_79902:
    decay0_nucltransK(prng_, event_, 0.678, 0.047, 1.4e-2, 0., tclev, thlev, tdlev);
    goto label_12100;
  label_79903:
    decay0_nucltransK(prng_, event_, 0.601, 0.047, 1.8e-2, 0., tclev, thlev, tdlev);
    goto label_19700;
  label_197:
    p = 100. * prng_();
    if (p <= 99.4) {
      decay0_gamma(prng_, event_, 0.049, 0., 0., t);
    }
    if (p > 99.4) {
      decay0_beta(prng_, event_, 0.511, -62., 0., 0., t);
    }
  label_19700:
    thlev = 1.3e-9;
    p     = 100. * prng_();
    if (p <= 97.2) {
      goto label_19701;
    }
    goto label_19702;
  label_19701:
    decay0_nucltransK(prng_, event_, 0.197, 0.047, 2.2e-1, 0., tclev, thlev, tdlev);
    return;
  label_19702:
    decay0_nucltransK(prng_, event_, 0.076, 0.047, 3.5e-0, 0., tclev, thlev, tdlev);
    goto label_12100;
  label_121:
    p = 100. * prng_();
    if (p <= 99.5) {
      decay0_gamma(prng_, event_, 0.049, 0., 0., t);
    }
    if (p > 99.5) {
      decay0_beta(prng_, event_, 0.587, -62., 0., 0., t);
    }
  label_12100:
    thlev = 0.77e-9;
    decay0_nucltransK(prng_, event_, 0.121, 0.047, 1.1e-0, 0., tclev, thlev, tdlev);
    return;
  label_10000:
    p = 100. * prng_();
    if (p <= 99.3) {
      decay0_gamma(prng_, event_, 0.049, 0., 0., t);
    }
    if (p > 99.3) {
      decay0_beta(prng_, event_, 0.708, -62., 0., 0., t);
    }
    return;
  }
  // end of Eu147.f

} // end of namespace bxdecay0

// end of Eu147.cc
// Local Variables: --
// mode: c++ --
// End: --
