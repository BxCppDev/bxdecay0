// Copyright 2018 V.I. Tretyak
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
#include <bxdecay0/Ta180mB.h>

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

  void Ta180mB(i_random & prng_,
               event & event_,
               const double tcnuc_,
               double & tdnuc_)
  {
    // Scheme of Ta180m decay, not observed yet (5.02.2018), beta- branch 
    // (NNDC on 5.02.2018 and NDS 126(2015)151). It is supposed that
    // Ta180m (J^pi=9^-, E_exc=77.2 keV) 100% decays to the 3rd excited level 
    // of 180W (J^pi=6^+, E_exc=688.5 keV).
    // Three-figured labels correspond to energies of 180W excited
    // levels in keV.
    // Input : tcnuc - time of creation of nucleus (sec);
    // Output: tdnuc - time of decay of nucleus (sec);
    //         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
    // VIT, 5.02.2018.
    double thnuc=0.;
    double tclev;
    double thlev;
    double tdlev;
    double t;
    tdnuc_ = tcnuc_ - thnuc / std::log(2.) * std::log(prng_());
    // Beta shape is not important if Ta180m is measured
    // as an external source, so allowed shape is used 
    decay0_beta(prng_, event_, 0.092, 74., 0., 0., t);
    tclev=0.;
  label_688:
    thlev=0.;
    decay0_nucltransK(prng_, event_, 0.351, 0.070, 5.4e-2, 0., tclev, thlev, tdlev);
    goto label_338;
  label_338:
    thlev=0.;
    decay0_nucltransK(prng_, event_, 0.234, 0.070, 0.184, 0., tclev, thlev, tdlev);
    goto label_104;
  label_104:
    thlev=1.28e-9;
    decay0_nucltransK(prng_, event_, 0.104, 0.070, 3.40, 0., tclev, thlev, tdlev);
    return;
  }
  
} // end of namespace bxdecay0

// end of Ta180mB.cc
// Local Variables: --
// mode: c++ --
// End: --
