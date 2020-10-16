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
#include <bxdecay0/Na22.h>

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

  void Na22(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_)
  {
    double t;
    double tdlev;
    double pdecay;
    double tclev;
    double thlev;
    double thnuc;
    // Scheme of Na22 decay ("Table of Isotopes", 7th ed., 1978).
    // Accuracy in description of: decay branches - 0.001%,
    // : deexcitation process - 0.001%.
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 26.07.1993, 22.10.1995.
    // VIT, 12.11.2006 (updated to NDS 106(2005)1 and change to beta spectra with
    // std::experimental corrections).
    // VIT, 26.08.2007 (corrected beta shapes).
    thnuc  = 8.2132717e+7;
    tdnuc_ = tcnuc_ - thnuc / std::log(2.) * std::log(prng_());
    tclev  = 0.;
    pdecay = 100. * prng_();
    if (pdecay <= 99.944) {
      goto label_1275;
    }
    goto label_10000;
  label_1275:
    thlev = 3.63e-12;
    if (pdecay <= 9.618) {
      decay0_gamma(prng_, event_, 0.001, 0., 0., t);
    }
    // if (pdecay > 9.618) decay0_beta(prng_, event_, 0.545,-10.,0.,0.,t)
    // std::experimental correction to the shape of the beta spectrum from:
    // H.Daniel, RMP 40(1968)659 and H.Wenninger et al., NPA 109(1968)561
    if (pdecay > 9.618) {
      decay0_beta1(prng_, event_, 0.545, -10., 0., 0., t, 1.e-3, 0., 0., 0.);
    }
    decay0_nucltransK(prng_, event_, 1.275, 0.001, 6.8e-6, 2.1e-5, tclev, thlev, tdlev);
    return;
    // change to 2nd unique shape in accordance with H.Daniel, RMP 40(1968)659
  label_10000:
    decay0_beta2(prng_, event_, 1.820, -10., 0., 0., t, 2, 3.333333, 1., 0., 0.);
    return;
  }
  // end of Na22.f

} // end of namespace bxdecay0

// end of Na22.cc
// Local Variables: --
// mode: c++ --
// End: --
