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
#include <bxdecay0/Th234.h>

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

  void Th234(i_random & prng_,
             event & event_,
             const double tcnuc_,
             double & tdnuc_)
  {
    double t;
    double tdlev;
    double p;
    double pbeta;
    double tclev;
    double thlev;
    double thnuc;
    // Scheme of Th234 decay to Pa234m (not Pa234!) in accordance with NDS
    // 108(2007)681 and ENSDF database at NNDC site on 8.08.2007.
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 8.08.2007.
    thnuc=2.08224e6;
    tdnuc_=tcnuc_-thnuc/std::log(2.)*std::log(prng_());
    tclev=0.;
    pbeta=100.*prng_();
    if (pbeta <=  1.501) goto label_187;  // 1.501%
    if (pbeta <=  1.516) goto label_177;  // 0.015%
    if (pbeta <=  7.921) goto label_167;  // 6.405%
    if (pbeta <= 21.933) goto label_166;  // 14.012%
    goto label_74;  // 78.067%
  label_187  :
    decay0_beta(prng_, event_, 0.086,91.,0.,0.,t);
    ////    label_18700  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 17.0) goto label_18701;  // 17.0%
    if (p <= 21.7) goto label_18702;  // 4.7%
    goto label_18703;  // 78.3%
  label_18701  :
    decay0_nucltransK(prng_, event_, 0.113,0.021,2.3e-1,0.,tclev,thlev,tdlev);
    goto label_74000;
  label_18702  :
    decay0_nucltransK(prng_, event_, 0.083,0.021,2.0e-1,0.,tclev,thlev,tdlev);
    goto label_10300;
  label_18703  :
    decay0_nucltransK(prng_, event_, 0.020,0.005,2.4e2,0.,tclev,thlev,tdlev);
    goto label_16700;
  label_177  :
    decay0_beta(prng_, event_, 0.096,91.,0.,0.,t);
    ////    label_17700  :
    thlev=0.;
    decay0_nucltransK(prng_, event_, 0.103,0.021,3.8e0,0.,tclev,thlev,tdlev);
    goto label_74000;
  label_167  :
    decay0_beta(prng_, event_, 0.106,91.,0.,0.,t);
  label_16700  :
    thlev=0.55e-9;
    p=100.*prng_();
    if (p <= 32.1) goto label_16701;  // 32.1%
    goto label_16702;  // 67.9%
  label_16701  :
    decay0_nucltransK(prng_, event_, 0.093,0.021,1.5e-1,0.,tclev,thlev,tdlev);
    goto label_74000;
  label_16702  :
    decay0_nucltransK(prng_, event_, 0.063,0.021,4.1e-1,0.,tclev,thlev,tdlev);
    goto label_10300;
  label_166  :
    decay0_beta(prng_, event_, 0.106,91.,0.,0.,t);
    ////    label_16600  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 97.0) goto label_16601;  // 97.0%
    goto label_16602;  // 3.0%
  label_16601  :
    decay0_nucltransK(prng_, event_, 0.092,0.021,5.3e0,0.,tclev,thlev,tdlev);
    goto label_74000;
  label_16602  :
    decay0_nucltransK(prng_, event_, 0.062,0.021,2.5e1,0.,tclev,thlev,tdlev);
    goto label_10300;
  label_10300  :
    thlev=0.;
    decay0_nucltransK(prng_, event_, 0.029,0.021,4.4e3,0.,tclev,thlev,tdlev);
    goto label_74000;
  label_74  :
    decay0_beta(prng_, event_, 0.199,91.,0.,0.,t);
    // below is creation of Pa234m with T1/2=1.159 m which mainly beta^- decays
    // to U234 (IT to Pa234 is only 0.16%)
    // independently
  label_74000  :
    return;
  }
  // end of Th234.f




} // end of namespace bxdecay0

// end of Th234.cc
// Local Variables: --
// mode: c++ --
// End: --
