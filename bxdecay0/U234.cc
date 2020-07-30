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
#include <bxdecay0/U234.h>

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

  void U234(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_)
  {
    double t;
    double tdlev;
    double palpha;
    double tclev;
    double thlev;
    double thnuc;
    // Model for scheme of U234 decay (NDS 108, 681 (2007) and ENSDF at NNDC site
    // on 17.07.2020).
    // https://www.nndc.bnl.gov/nudat2/decaysearchdirect.jsp?nuc=238U&unc=nds
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, XX.07.2020.
    thnuc         = 2.455E5 * 365 * 24 * 3600.; // sec (!)
    tdnuc_        = tcnuc_ - thnuc / std::log(2.) * std::log(prng_());
    tclev         = 0.;
    palpha        = 100. * prng_();
    double pgamma = 0;
    if (palpha <= 7E-6)
      goto label_4108;
    else if (palpha <= 3.3E-5)
      goto label_4150;
    else if (palpha <= 7.3E-5)
      goto label_4277;
    else if (palpha <= 0.2)
      goto label_4603;
    else if (palpha <= 28.62)
      goto label_4722;
    else
      goto label_4774;

  label_4108:
    decay0_alpha(prng_, event_, 4.1086, 0., 0., t);
  label_677:
    thlev = 0.;
    // Simplified model:
    // - internal electron conversion is null
    // - pair conversion is null
    // decay0_nucltransK(prng_, evnt_, 0.510, 0.093, 0., 0., tclev, thlev, tdlev);

    pgamma = 100 * prng_();
    if (pgamma <= 86) {
      decay0_gamma(prng_, event_, 0.50355, tclev, thlev, tdlev);
      goto label_174;
    } else if (pgamma <= 88) {
      decay0_gamma(prng_, event_, 0.62433, tclev, thlev, tdlev);
      goto label_53;
    } else {
      decay0_gamma(prng_, event_, 0.67753, tclev, thlev, tdlev);
      return;
    }
    return; // in the off chance you get here

  label_4150:
    decay0_alpha(prng_, event_, 4.1506, 0., 0., t);
    thlev = 0.;
    decay0_gamma(prng_, event_, 0.58165, tclev, thlev, tdlev);
    goto label_53;

  label_4277:
    decay0_alpha(prng_, event_, 4.2773, 0., 0., t);
  label_508:
    thlev  = 0.;
    pgamma = 100 * prng_();
    if (pgamma <= 40) {
      decay0_gamma(prng_, event_, 0.45492, tclev, thlev, tdlev);
      goto label_53;
    } else {
      decay0_gamma(prng_, event_, 0.50815, tclev, thlev, tdlev);
      return;
    }
    return;

  label_4603:
    decay0_alpha(prng_, event_, 4.6035, 0., 0., t);
  label_174:
    thlev = 0.;
    decay0_gamma(prng_, event_, 0.1209, tclev, thlev, tdlev);
    goto label_53;

  label_4722:
    decay0_alpha(prng_, event_, 4.7224, 0., 0., t);
  label_53:
    thlev = 0.;
    decay0_gamma(prng_, event_, 0.0532, tclev, thlev, tdlev);
    return;

  label_4774:
    decay0_alpha(prng_, event_, 4.7746, 0., 0., t);
    return;
  }

} // end of namespace bxdecay0

// end of U234.cc
// Local Variables: --
// mode: c++ --
// End: --
