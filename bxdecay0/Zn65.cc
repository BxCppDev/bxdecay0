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
#include <bxdecay0/Zn65.h>

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

  void Zn65(i_random & prng_,
            event & event_,
            const double tcnuc_,
            double & tdnuc_)
  {
    double t;
    double tdlev;
    double p;
    double pbec;
    double tclev;
    double thlev;
    double thnuc;
    // Scheme of Zn65 decay (NDS 69(1993)209 and NNDC online corrections on 28.03.2007).
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 28.03.2007.
    thnuc=2.1086784E+07;
    tdnuc_=tcnuc_-thnuc/std::log(2.)*std::log(prng_());
    tclev=0.;
    pbec=100.*prng_();
    if (pbec <= 1.42) goto label_1;
    goto label_2;
    // beta+ decay to g.s. of 65-Cu
  label_1  :
    decay0_pair(prng_, event_, 0.329,0.,0.,tdlev);
    return;
    // X ray after EC to 65-Cu
  label_2  :
    decay0_gamma(prng_, event_, 0.009,0.,0.,t);
    if (pbec <= 52.03) goto label_11160;
    goto label_10000;
  label_11160  :
    thlev=0.285e-12;
    p=100.*prng_();
    if (p <= 99.994) goto label_11161;
    goto label_11162;
  label_11161  :
    decay0_nucltransK(prng_, event_, 1.116,0.009,1.9e-4,1.0e-6,tclev,thlev,tdlev);
    return;
  label_11162  :
    decay0_nucltransK(prng_, event_, 0.345,0.009,6.8e-3,0.,tclev,thlev,tdlev);
    goto label_77100;
  label_77100  :
    thlev=99.e-15;
    decay0_nucltransK(prng_, event_, 0.771,0.009,3.8e-4,0.,tclev,thlev,tdlev);
  label_10000  :
    return;
  }
  // end of Zn65.f




} // end of namespace bxdecay0

// end of Zn65.cc
// Local Variables: --
// mode: c++ --
// End: --
