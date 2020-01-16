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
#include <bxdecay0/Ta180mEC.h>

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

  void Ta180mEC(i_random & prng_,
                event & event_,
                const double tcnuc_,
                double & tdnuc_)
  {
    // Scheme of Ta180m decay, not observed yet (5.02.2018), EC branch 
    // (NNDC on 5.02.2018 and NDS 126(2015)151). It is supposed that
    // Ta180m (J^pi=9^-, E_exc=77.2 keV) 100% decays to the 3rd excited level 
    // of 180Hf (J^pi=6^+, E_exc=640.8 keV).
    // Three-figured labels correspond to energies of 180Hf excited
    // levels in keV.
    // Input : tcnuc - time of creation of nucleus (sec);
    // Output: tdnuc - time of decay of nucleus (sec);
    //         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
    // VIT, 5.02.2018.
    double thnuc=0.;
    double thlev;
    double tclev;
    double tdlev;
    double t;
    tdnuc_ = tcnuc_ - thnuc / std::log(2.) * std::log(prng_());
    decay0_gamma(prng_, event_, 0.065, 0., 0., t);
    tclev=0.;
  label_641:
    thlev=10.e-12;
    decay0_nucltransK(prng_, event_, 0.332, 0.065, 5.9e-2, 0., tclev, thlev, tdlev);
    goto label_309;
  label_309:
    thlev=71.e-12;
    decay0_nucltransK(prng_, event_, 0.215, 0.065, 0.225, 0., tclev, thlev, tdlev);
    goto label_93;
  label_93:
    thlev=1.519e-9;
    decay0_nucltransK(prng_, event_, 0.093, 0.065, 4.63, 0., tclev, thlev, tdlev); 
    return;
  }
  
} // end of namespace bxdecay0

// end of Ta180mEC.cc
// Local Variables: --
// mode: c++ --
// End: --
