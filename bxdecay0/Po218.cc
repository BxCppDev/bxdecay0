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
#include <bxdecay0/Po218.h>

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

  void Po218(i_random & prng_,
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
    // Model for scheme of Po218 decay (NDS 110, 681 (2009) and ENSDF at NNDC site
    // on 17.07.2020).
    // https://www.nndc.bnl.gov/nudat2/decaysearchdirect.jsp?nuc=218PO&unc=nds
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, XX.07.2020.
    thnuc = 3.098 * 60.; // sec
    tdnuc_ = tcnuc_-thnuc/std::log(2.)*std::log(prng_());
    tclev=0.;
    palpha=100.*prng_();
    
    if (palpha <= 0.001){
      goto label_5181;
    } else {
      goto label_6002;
    }
    
  label_5181:
    decay0_alpha(prng_, event_, 5.181,0.,0.,t);
    thlev=0.;
    // Simplified model:
    // - internal electron conversion is null
    // - pair conversion is null
    // decay0_nucltransK(prng_, event_, 0.510, 0.093, 0., 0., tclev, thlev, tdlev);
    decay0_gamma(prng_, event_, 0.835, tclev, thlev, tdlev);
    return;
  label_6002:
    decay0_alpha(prng_, event_, 6.00235,0.,0.,t);
    return;
  }

} // end of namespace bxdecay0

// end of Po218.cc
// Local Variables: --
// mode: c++ --
// End: --
