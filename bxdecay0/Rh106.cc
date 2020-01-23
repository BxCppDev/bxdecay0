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
#include <bxdecay0/Rh106.h>

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

  void Rh106(i_random & prng_,
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
    // Approximate scheme of 106Rh decay ("Table of Isotopes", 7th ed., 1978)
    // (beta decays to excited levels of 106Pd not higher 2.002 MeV,
    // 99.32% of decay).
    // Three-figured labels correspond to energies of 106Pd excited levels
    // in keV.
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 17.12.1995.
    thnuc=29.80;
    tdnuc_=tcnuc_-thnuc/std::log(2.)*std::log(prng_());
    tclev=0.;
    pbeta=100.*prng_();
    if (pbeta <=  0.45) goto label_2002;
    if (pbeta <=  0.52) goto label_1707;
    if (pbeta <=  2.32) goto label_1562;
    if (pbeta <= 12.32) goto label_1134;
    if (pbeta <= 19.32) goto label_512;
    goto label_10000;
  label_2002  :
    decay0_beta(prng_, event_, 1.539,46.,0.,0.,t);
    ////    label_20020  :
    thlev=0.;
    p=100.*prng_();
    if (p <=  0.4) goto label_20021;
    if (p <= 98.6) goto label_20022;
    goto label_20023;
  label_20021  :
    decay0_nucltransK(prng_, event_, 1.490,0.024,4.0e-4,0.3e-4,tclev,thlev,tdlev);
    goto label_51200;
  label_20022  :
    decay0_nucltransK(prng_, event_, 0.874,0.024,1.3e-3,0.,tclev,thlev,tdlev);
    goto label_11280;
  label_20023  :
    decay0_nucltransK(prng_, event_, 0.440,0.024,8.5e-3,0.,tclev,thlev,tdlev);
    goto label_15620;
  label_1707  :
    decay0_beta(prng_, event_, 1.834,46.,0.,0.,t);
    ////    label_17070  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 89.0) goto label_17071;
    goto label_17072;
  label_17071  :
    decay0_nucltransK(prng_, event_, 1.195,0.024,7.5e-4,0.,tclev,thlev,tdlev);
    goto label_51200;
  label_17072  :
    decay0_nucltransK(prng_, event_, 0.578,0.024,3.7e-3,0.,tclev,thlev,tdlev);
    goto label_11280;
  label_1562  :
    decay0_beta(prng_, event_, 1.979,46.,0.,0.,t);
  label_15620  :
    thlev=0.;
    p=100.*prng_();
    if (p <=  9.1) goto label_15621;
    if (p <= 95.6) goto label_15622;
    if (p <= 96.8) goto label_15623;
    goto label_15624;
  label_15621  :
    decay0_nucltransK(prng_, event_, 1.562,0.024,3.5e-4,0.4e-4,tclev,thlev,tdlev);
    return;
  label_15622  :
    decay0_nucltransK(prng_, event_, 1.051,0.024,8.5e-4,0.,tclev,thlev,tdlev);
    goto label_51200;
  label_15623  :
    decay0_nucltransK(prng_, event_, 0.434,0.024,8.5e-3,0.,tclev,thlev,tdlev);
    goto label_11280;
  label_15624  :
    decay0_nucltransK(prng_, event_, 0.428,0.024,8.5e-3,0.,tclev,thlev,tdlev);
    goto label_11340;
  label_1134  :
    decay0_beta(prng_, event_, 2.407,46.,0.,0.,t);
  label_11340  :
    thlev=7.0e-12;
    decay0_nucltransK(prng_, event_, 0.622,0.024,3.3e-3,0.,tclev,thlev,tdlev);
    goto label_51200;
  label_11280  :
    thlev=3.2e-12;
    p=100.*prng_();
    if (p <= 34.) goto label_11281;
    goto label_11282;
  label_11281  :
    decay0_nucltransK(prng_, event_, 1.128,0.024,7.0e-4,0.,tclev,thlev,tdlev);
    return;
  label_11282  :
    decay0_nucltransK(prng_, event_, 0.616,0.024,3.0e-3,0.,tclev,thlev,tdlev);
    goto label_51200;
  label_512  :
    decay0_beta(prng_, event_, 3.029,46.,0.,0.,t);
  label_51200  :
    thlev=11.0e-12;
    decay0_nucltransK(prng_, event_, 0.512,0.024,5.5e-3,0.,tclev,thlev,tdlev);
    return;
  label_10000  :
    decay0_beta(prng_, event_, 3.541,46.,0.,0.,t);
    return;
  }
  // end of Rh106.f




} // end of namespace bxdecay0

// end of Rh106.cc
// Local Variables: --
// mode: c++ --
// End: --
