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
#include <bxdecay0/Hf182.h>

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

  void Hf182(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_)
  {
    double t;
    double tdlev;
    double p;
    double tclev;
    double thlev;
    double thnuc;
    // Scheme of 182Hf decay ("Table of Isotopes", 7th ed., 1978).
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 5.03.1996.
    thnuc  = 2.84011e14;
    tdnuc_ = tcnuc_ - thnuc / std::log(2.) * std::log(prng_());
    tclev  = 0.;
    goto label_270;
  label_270:
    decay0_beta(prng_, event_, 0.160, 73., 0., 0., t);
    thlev = 1.2e-9;
    p     = 100. * prng_();
    if (p <= 91.77)
      goto label_27001;
    if (p <= 92.00)
      goto label_27002;
    goto label_27003;
  label_27001:
    decay0_nucltransK(prng_, event_, 0.270, 0.067, 3.1e-1, 0., tclev, thlev, tdlev);
    return;
  label_27002:
    decay0_nucltransK(prng_, event_, 0.173, 0.067, 9.5e-2, 0., tclev, thlev, tdlev);
    goto label_98000;
  label_27003:
    decay0_nucltransK(prng_, event_, 0.156, 0.067, 1.5e-1, 0., tclev, thlev, tdlev);
    goto label_11400;
  label_11400:
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 0.114, 0.067, 4.5e-0, 0., tclev, thlev, tdlev);
    return;
  label_98000:
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 0.098, 0.067, 5.0e-0, 0., tclev, thlev, tdlev);
    return;
  }
  // end of Hf182.f

} // end of namespace bxdecay0

// end of Hf182.cc
// Local Variables: --
// mode: c++ --
// End: --
