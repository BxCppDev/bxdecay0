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
#include <bxdecay0/Gd146.h>

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

  void Gd146(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_)
  {
    double t;
    double tdlev;
    double p;
    double pdecay;
    double tclev;
    double thlev;
    double thnuc;
    // Scheme of 146Gd decay ("Table of Isotopes", 7th ed., 1978).
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 10.03.1996.
    thnuc  = 4.173e6;
    tdnuc_ = tcnuc_ - thnuc / std::log(2.) * std::log(prng_());
    tclev  = 0.;
    pdecay = 100. * prng_();
    if (pdecay <= 0.3)
      goto label_806;
    if (pdecay <= 0.8)
      goto label_743;
    if (pdecay <= 77.2)
      goto label_385;
    goto label_230;
  label_806:
    decay0_gamma(prng_, event_, 0.049, 0., 0., t);
    ////label_80600  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 36.)
      goto label_80601;
    goto label_80602;
  label_80601:
    decay0_nucltransK(prng_, event_, 0.576, 0.049, 1.8e-2, 0., tclev, thlev, tdlev);
    goto label_23000;
  label_80602:
    decay0_nucltransK(prng_, event_, 0.421, 0.049, 4.5e-2, 0., tclev, thlev, tdlev);
    goto label_38500;
  label_743:
    decay0_gamma(prng_, event_, 0.049, 0., 0., t);
    ////label_74300  :
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 0.743, 0.049, 1.0e-2, 0., tclev, thlev, tdlev);
    return;
  label_385:
    p = 100. * prng_();
    if (p <= 99.91)
      decay0_gamma(prng_, event_, 0.049, 0., 0., t);
    if (p > 99.91)
      decay0_beta(prng_, event_, 0.343, -63., 0., 0., t);
  label_38500:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 0.4)
      goto label_38501;
    goto label_38502;
  label_38501:
    decay0_nucltransK(prng_, event_, 0.269, 0.049, 8.0e-2, 0., tclev, thlev, tdlev);
    goto label_11500;
  label_38502:
    decay0_nucltransK(prng_, event_, 0.155, 0.049, 6.5e-1, 0., tclev, thlev, tdlev);
    goto label_23000;
  label_230:
    decay0_gamma(prng_, event_, 0.049, 0., 0., t);
  label_23000:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 0.2)
      goto label_23001;
    goto label_23002;
  label_23001:
    decay0_nucltransK(prng_, event_, 0.230, 0.049, 1.4e-1, 0., tclev, thlev, tdlev);
    return;
  label_23002:
    decay0_nucltransK(prng_, event_, 0.115, 0.049, 1.5e-0, 0., tclev, thlev, tdlev);
    goto label_11500;
  label_11500:
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 0.115, 0.049, 1.5e-0, 0., tclev, thlev, tdlev);
    return;
  }
  // end of Gd146.f

} // end of namespace bxdecay0
