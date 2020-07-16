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
#include <bxdecay0/Rn222.h>

// Standard library:
#include <sstream>
#include <stdexcept>
#include <cmath>

// This project:
#include <bxdecay0/i_random.h>
#include <bxdecay0/event.h>
#include <bxdecay0/alpha.h>
#include <bxdecay0/gamma.h>
#include <bxdecay0/electron.h>
#include <bxdecay0/positron.h>
#include <bxdecay0/particle.h>
#include <bxdecay0/pair.h>
#include <bxdecay0/nucltransK.h>
#include <bxdecay0/nucltransKL.h>
#include <bxdecay0/nucltransKLM.h>
#include <bxdecay0/nucltransKLM_Pb.h>
#include <bxdecay0/beta.h>
#include <bxdecay0/beta1.h>
#include <bxdecay0/beta2.h>
#include <bxdecay0/beta_1fu.h>
#include <bxdecay0/PbAtShell.h>

namespace bxdecay0 {

  void Rn222(i_random & prng_,
             event & event_,
             const double tcnuc_,
             double & tdnuc_)
  {
    double t;
    double tdlev;
    double palpha;
    double tclev;
    double thlev;
    double thnuc;
    // Model for scheme of Rn222 decay (NDS 160, 405 (2019) and ENSDF at NNDC site
    // on 17.07.2020).
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, XX.07.2020.
    thnuc = 3.8222 * 24. * 3600.; // sec
    tdnuc_ = tcnuc_-thnuc/std::log(2.)*std::log(prng_());
    tclev=0.;
    palpha=100.*prng_();
    if (palpha <= 0.078) goto label_513;
    goto label_10000;
  label_513  :
    decay0_alpha(prng_, event_, 4.986,0.,0.,t);
    thlev=0.;
    // Simplified model:
    // - internal electron conversion is null
    // - pair conversion is null
    // decay0_nucltransK(prng_, event_, 0.510, 0.093, 0., 0., tclev, thlev, tdlev);
    decay0_gamma(prng_, event_, 0.510, tclev, thlev, tdlev);
    return;
  label_10000  :
    decay0_alpha(prng_, event_, 5.48948,0.,0.,t);
    return;
  }

} // end of namespace bxdecay0

// end of Rn222.cc
// Local Variables: --
// mode: c++ --
// End: --
