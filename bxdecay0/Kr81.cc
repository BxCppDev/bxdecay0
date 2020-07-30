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
#include <bxdecay0/Kr81.h>

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

  void Kr81(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_)
  {
    double t;
    double tdlev;
    double pdecay;
    double pklm;
    double tclev;
    double thlev;
    double thnuc;
    // Scheme of Kr81 decay (NDS 79(1996)447 and ENSDF at NNDC site on 9.12.2007).
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 9.12.2007.
    thnuc  = 7.226493e12;
    tdnuc_ = tcnuc_ - thnuc / std::log(2.) * std::log(prng_());
    tclev  = 0.;
    pdecay = 100. * prng_();
    if (pdecay <= 0.30) {
      goto label_276;
    }
    goto label_10000;
  label_276:
    decay0_gamma(prng_, event_, 0.013, 0., 0., t); // capture from only K shell is supposed
    thlev = 9.7e-12;
    decay0_nucltransKLM(prng_, event_, 0.276, 0.013, 7.3e-3, 0.002, 7.8e-4, 0.000, 2.6e-4, 0., tclev, thlev, tdlev);
    return;
  label_10000:
    pklm = 100. * prng_();
    if (pklm <= 84.73) {
      decay0_gamma(prng_, event_, 0.013, 0., 0., t);
    }
    if (pklm > 84.73 && pklm <= 97.44) {
      decay0_gamma(prng_, event_, 0.002, 0., 0., t);
    }
    if (pklm > 97.44) {
      decay0_gamma(prng_, event_, 0.000, 0., 0., t);
    }
    return;
  }
  // end of Kr81.f

} // end of namespace bxdecay0

// end of Kr81.cc
// Local Variables: --
// mode: c++ --
// End: --
