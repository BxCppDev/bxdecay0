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
#include <bxdecay0/Cs136.h>

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

  void Cs136(i_random & prng_,
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
    // Model for scheme of Cs136 decay ("Table of Isotopes", 8th ed.,
    // 1996 and Nucl. Data Sheets 95(2002)837).
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 11.09.2002.
    thnuc=1.137024e+6;
    tdnuc_=tcnuc_-thnuc/std::log(2.)*std::log(prng_());
    tclev=0.;
    pbeta=100.*prng_();
    if (pbeta <=  2.025) goto label_2374;  // 2.025%
    if (pbeta <=  2.233) goto label_2357;  // 0.208%
    if (pbeta <= 72.009) goto label_2207;  // 69.776%
    if (pbeta <= 82.431) goto label_2140;  // 10.422%
    if (pbeta <= 87.097) goto label_2054;  // 4.666%
    goto label_1867;  // 12.903%
  label_2374  :
    decay0_beta(prng_, event_, 0.174,56.,0.,0.,t);
    ////label_23740  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 48.02) goto label_23741;  // 48.02%
    if (p <= 73.36) goto label_23742;  // 25.34%
    if (p <= 77.36) goto label_23743;  // 4.00%
    goto label_23744;  // 22.64%
  label_23741  :
    decay0_nucltransK(prng_, event_, 0.507,0.037,1.1e-2,0.,tclev,thlev,tdlev);
    goto label_18670;
  label_23742  :
    decay0_nucltransK(prng_, event_, 0.320,0.037,3.5e-2,0.,tclev,thlev,tdlev);
    goto label_20540;
  label_23743  :
    decay0_nucltransK(prng_, event_, 0.234,0.037,2.0e-2,0.,tclev,thlev,tdlev);
    goto label_21400;
  label_23744  :
    decay0_nucltransK(prng_, event_, 0.167,0.037,2.5e-1,0.,tclev,thlev,tdlev);
    goto label_22070;
  label_2357  :
    decay0_beta(prng_, event_, 0.191,56.,0.,0.,t);
    ////label_23570  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 47.12) goto label_23571;  // 47.12%
    if (p <= 85.24) goto label_23572;  // 38.12%
    goto label_23573;  // 14.76%
  label_23571  :
    decay0_nucltransK(prng_, event_, 1.538,0.037,6.0e-4,0.2e-4,tclev,thlev,tdlev);
    goto label_81900;
  label_23572  :
    decay0_nucltransK(prng_, event_, 0.490,0.037,1.2e-2,0.,tclev,thlev,tdlev);
    goto label_18670;
  label_23573  :
    decay0_nucltransK(prng_, event_, 0.303,0.037,4.5e-2,0.,tclev,thlev,tdlev);
    goto label_20540;
  label_2207  :
    decay0_beta(prng_, event_, 0.341,56.,0.,0.,t);
  label_22070  :
    thlev=3.11e-9;
    p=100.*prng_();
    if (p <= 61.84) goto label_22071;  // 61.84%
    if (p <= 76.78) goto label_22072;  // 14.94%
    if (p <= 88.48) goto label_22073;  // 11.70%
    goto label_22074;  // 11.52%
  label_22071  :
    decay0_nucltransK(prng_, event_, 0.341,0.037,3.0e-2,0.,tclev,thlev,tdlev);
    goto label_18670;
  label_22072  :
    decay0_nucltransK(prng_, event_, 0.176,0.037,5.0e-2,0.,tclev,thlev,tdlev);
    goto label_20310;
  label_22073  :
    decay0_nucltransK(prng_, event_, 0.153,0.037,4.3e-1,0.,tclev,thlev,tdlev);
    goto label_20540;
  label_22074  :
    decay0_nucltransK(prng_, event_, 0.067,0.037,6.9e-1,0.,tclev,thlev,tdlev);
    goto label_21400;
  label_2140  :
    decay0_beta(prng_, event_, 0.408,56.,0.,0.,t);
  label_21400  :
    thlev=1.6e-9;
    p=100.*prng_();
    if (p <=  0.27) goto label_21401;  // 0.27%
    if (p <= 60.13) goto label_21402;  // 59.86%
    if (p <= 62.88) goto label_21403;  // 2.75%
    goto label_21404;  // 37.12%
  label_21401  :
    decay0_nucltransK(prng_, event_, 1.321,0.037,1.7e-3,0.1e-4,tclev,thlev,tdlev);
    goto label_81900;
  label_21402  :
    decay0_nucltransK(prng_, event_, 0.273,0.037,1.6e-2,0.,tclev,thlev,tdlev);
    goto label_18670;
  label_21403  :
    decay0_nucltransK(prng_, event_, 0.109,0.037,1.47,0.,tclev,thlev,tdlev);
    goto label_20310;
  label_21404  :
    decay0_nucltransK(prng_, event_, 0.086,0.037,3.5e-1,0.,tclev,thlev,tdlev);
    goto label_20540;
  label_2054  :
    decay0_beta(prng_, event_, 0.494,56.,0.,0.,t);
  label_20540  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 97.90) goto label_20541;  // 97.90%
    goto label_20542;  // 2.10%
  label_20541  :
    decay0_nucltransK(prng_, event_, 1.235,0.037,1.0e-3,0.1e-4,tclev,thlev,tdlev);
    goto label_81900;
  label_20542  :
    decay0_nucltransK(prng_, event_, 0.187,0.037,1.9e-1,0.,tclev,thlev,tdlev);
    goto label_18670;
  label_20310  :
    thlev=0.3084;
    decay0_nucltransK(prng_, event_, 0.164,0.037,2.26,0.,tclev,thlev,tdlev);
    goto label_18670;
  label_1867  :
    decay0_beta(prng_, event_, 0.681,56.,0.,0.,t);
  label_18670  :
    thlev=0.;
    decay0_nucltransK(prng_, event_, 1.048,0.037,1.5e-3,0.,tclev,thlev,tdlev);
    goto label_81900;
  label_81900  :
    thlev=1.930e-12;
    decay0_nucltransK(prng_, event_, 0.819,0.037,2.7e-3,0.,tclev,thlev,tdlev);
    return;
  }
  // end of Cs136.f




} // end of namespace bxdecay0

// end of Cs136.cc
// Local Variables: --
// mode: c++ --
// End: --
