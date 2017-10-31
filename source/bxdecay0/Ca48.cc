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
#include <bxdecay0/Ca48.h>

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

  void Ca48(i_random & prng_,
            event & event_,
            double tcnuc_,
            double & tdnuc_)
  {
    double t;
    double tdlev;
    double tclev;
    double thlev;
    double thnuc;
    // Scheme of Ca48 beta decay.
    // It is supposed that decay goes to excited 5+ level of Sc48 (E_exc=131 keV)
    // with T1/2=1.1e21 y calculated in M.Aunola et al., Europhys. Lett. 46(1999)577
    // (transition to g.s. is suppressed by factor of ~1e-10
    // with E_exc=252 keV - by factor of ~1e-5).
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 07.05.1998
    thnuc=3.47e28;
    tdnuc_=tcnuc_-thnuc/std::log(2.)*std::log(prng_());
    decay0_beta(prng_, event_, 0.151,21.,0.,0.,t);
    tclev=0.;
    thlev=0.;
    decay0_nucltransK(prng_, event_, 0.131,0.004,8.1e-3,0.,tclev,thlev,tdlev);
    return;
  }
  // end of Ca48.f




} // end of namespace bxdecay0

// end of Ca48.cc
// Local Variables: --
// mode: c++ --
// End: --
