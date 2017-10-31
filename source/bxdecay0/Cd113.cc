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
#include <bxdecay0/Cd113.h>

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

  void Cd113(i_random & prng_,
             event & event_,
             const double tcnuc_,
             double & tdnuc_)
  {
    double t;
    //double tdlev;
    double c1;
    double c2;
    double c3;
    double thnuc;
    // Scheme of Cd113 beta decay.
    // Half-life and coefficients in the shape correction factor are taken from:
    // F.A.Danevich et al., Phys. At. Nuclei 59(1996)1.
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 31.03.2006.
    thnuc=2.42987e23;
    tdnuc_=tcnuc_-thnuc/std::log(2.)*std::log(prng_());
    c1=1.01*7.;
    c2=1.48*7.;
    c3=0.684;
    // Q_beta=0.320 MeV, G.Audi et al., Nucl. Phys. A 729(2003)337.
    decay0_beta2(prng_, event_, 0.320,49.,0.,0.,t,3,c1,c2,c3,0.);
    return;
  }
  // end of Cd113.f




} // end of namespace bxdecay0

// end of Cd113.cc
// Local Variables: --
// mode: c++ --
// End: --
