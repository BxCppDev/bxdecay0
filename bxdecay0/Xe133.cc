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
#include <bxdecay0/Xe133.h>

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

  void Xe133(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_)
  {
    double t;
    double tdlev;
    double p;
    double pbeta;
    double tclev;
    double thlev;
    double thnuc;
    // Scheme of Xe133 decay ("Table of Isotopes", 8th ed., 1996).
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 18.08.1997. Updated 5.12.2003 in accordance with NDS 75(1995)491.
    thnuc  = 452995.2;
    tdnuc_ = tcnuc_ - thnuc / std::log(2.) * std::log(prng_());
    tclev  = 0.;
    pbeta  = 100. * prng_();
    if (pbeta <= 0.008)
      goto label_384;
    if (pbeta <= 0.818)
      goto label_161;
    goto label_81;
  label_384:
    decay0_beta(prng_, event_, 0.044, 55., 0., 0., t);
    ////    label_38400  :
    thlev = 21.e-12;
    p     = 100. * prng_();
    if (p <= 32.313)
      goto label_38401;
    if (p <= 98.259)
      goto label_38402;
    goto label_38403;
  label_38401:
    decay0_nucltransK(prng_, event_, 0.384, 0.036, 2.0e-2, 0., tclev, thlev, tdlev);
    return;
  label_38402:
    decay0_nucltransK(prng_, event_, 0.303, 0.036, 4.4e-2, 0., tclev, thlev, tdlev);
    goto label_81000;
  label_38403:
    decay0_nucltransK(prng_, event_, 0.223, 0.036, 9.8e-2, 0., tclev, thlev, tdlev);
    goto label_16100;
  label_161:
    decay0_beta(prng_, event_, 0.267, 55., 0., 0., t);
  label_16100:
    thlev = 172.e-12;
    p     = 100. * prng_();
    if (p <= 10.287)
      goto label_16101;
    goto label_16102;
  label_16101:
    decay0_nucltransK(prng_, event_, 0.161, 0.036, 3.0e-1, 0., tclev, thlev, tdlev);
    return;
  label_16102:
    decay0_nucltransK(prng_, event_, 0.080, 0.036, 1.8e+0, 0., tclev, thlev, tdlev);
    goto label_81000;
  label_81:
    decay0_beta(prng_, event_, 0.346, 55., 0., 0., t);
  label_81000:
    thlev = 6.28e-9;
    decay0_nucltransK(prng_, event_, 0.081, 0.036, 1.7e+0, 0., tclev, thlev, tdlev);
    return;
  }
  // end of Xe133.f

} // end of namespace bxdecay0

// end of Xe133.cc
// Local Variables: --
// mode: c++ --
// End: --
