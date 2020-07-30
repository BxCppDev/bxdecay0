// Copyright 1995-2016 V.I. Tretyak
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
#include <bxdecay0/Th230.h>

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

  void Th230(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_)
  {
    double t;
    double tdlev;
    double palpha;
    double tclev;
    double thlev;
    double thnuc;
    // Model for scheme of Th230 decay (NDS 77, 433 (1996) and ENSDF at NNDC site
    // on 17.07.2020).
    // https://www.nndc.bnl.gov/nudat2/decaysearchdirect.jsp?nuc=230TH&unc=nds
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, XX.07.2020.
    thnuc         = 7.538E4 * 365 * 24 * 3600.; // sec (!)
    tdnuc_        = tcnuc_ - thnuc / std::log(2.) * std::log(prng_());
    tclev         = 0.;
    palpha        = 100. * prng_();
    double pgamma = 0;

    if (palpha <= 1.4E-6) {
      goto label_3829;
    } else if (palpha <= 4.8E-6) {
      goto label_3877;
    } else if (palpha <= 0.0000151) {
      goto label_4248;
    } else if (palpha <= 0.0000231) {
      goto label_4278;
    } else if (palpha <= 0.0009931) {
      goto label_4371;
    } else if (palpha <= 0.0309931) {
      goto label_4438;
    } else if (palpha <= 0.1509931) {
      goto label_4479;
    } else if (palpha <= 23.5509931) {
      goto label_4620;
    } else {
      goto label_4687;
    }

  label_3829:
    decay0_alpha(prng_, event_, 3.8294, 0., 0., t);
  label_873:
    thlev  = 0.;
    pgamma = 100 * prng_();
    if (pgamma <= 91) {
      decay0_gamma(prng_, event_, 0.5522, tclev, thlev, tdlev);
      goto label_321;
    } else {
      decay0_gamma(prng_, event_, 0.620, tclev, thlev, tdlev);
      goto label_253;
    }
    return;

  label_3877:
    decay0_alpha(prng_, event_, 3.8778, 0., 0., t);
  label_824:
    thlev = 0.;
    decay0_gamma(prng_, event_, 0.5709, tclev, thlev, tdlev);
    goto label_253;

  label_4248:
    decay0_alpha(prng_, event_, 4.2485, 0., 0., t);
  label_446:
    thlev  = 0.;
    pgamma = 100 * prng_();
    if (pgamma <= 3.3) {
      decay0_gamma(prng_, event_, 0.1248, tclev, thlev, tdlev);
      goto label_321;
    } else {
      decay0_gamma(prng_, event_, 0.2348, tclev, thlev, tdlev);
      goto label_211;
    }
    return;

  label_4278:
    decay0_alpha(prng_, event_, 4.2783, 0., 0., t);
  label_416:
    thlev = 0.;
    decay0_gamma(prng_, event_, 0.2049, tclev, thlev, tdlev);
    goto label_211;

  label_4371:
    decay0_alpha(prng_, event_, 4.3718, 0., 0., t);
  label_321:
    thlev  = 0.;
    pgamma = 100 * prng_();
    if (pgamma <= 10) {
      decay0_gamma(prng_, event_, 0.11, tclev, thlev, tdlev);
      goto label_211;
    } else {
      decay0_gamma(prng_, event_, 0.2539, tclev, thlev, tdlev);
      goto label_67;
    }
    return;

  label_4438:
    decay0_alpha(prng_, event_, 4.4384, 0., 0., t);
  label_253:
    thlev  = 0.;
    pgamma = 100 * prng_();
    if (pgamma <= 73) {
      decay0_gamma(prng_, event_, 0.18605, tclev, thlev, tdlev);
      goto label_67;
    } else {
      decay0_gamma(prng_, event_, 0.25373, tclev, thlev, tdlev);
      return;
    }

  label_4479:
    decay0_alpha(prng_, event_, 4.4798, 0., 0., t);
  label_211:
    thlev = 0.;
    decay0_gamma(prng_, event_, 0.14387, tclev, thlev, tdlev);
    goto label_67;

  label_4620:
    decay0_alpha(prng_, event_, 4.46205, 0., 0., t);
  label_67:
    thlev = 0.;
    decay0_gamma(prng_, event_, 0.06767, tclev, thlev, tdlev);
    return;

  label_4687:
    decay0_alpha(prng_, event_, 4.46870, 0., 0., t);
    return;
  }

} // end of namespace bxdecay0

// end of Th230.cc
// Local Variables: --
// mode: c++ --
// End: --
