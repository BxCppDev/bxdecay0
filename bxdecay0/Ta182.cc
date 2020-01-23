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
#include <bxdecay0/Ta182.h>

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

  void Ta182(i_random & prng_,
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
    // Scheme of 182Ta decay ("Table of Isotopes", 7th ed., 1978).
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 6.03.1996.
    thnuc=9.936e6;
    tdnuc_=tcnuc_-thnuc/std::log(2.)*std::log(prng_());
    tclev=0.;
    pbeta=100.*prng_();
    if (pbeta <= 28.586) goto label_1553;
    if (pbeta <= 28.716) goto label_1510;
    if (pbeta <= 31.416) goto label_1488;
    if (pbeta <= 32.076) goto label_1443;
    if (pbeta <= 52.066) goto label_1374;
    if (pbeta <= 54.366) goto label_1331;
    if (pbeta <= 94.346) goto label_1289;
    if (pbeta <= 94.846) goto label_1257;
    if (pbeta <= 99.846) goto label_1221;
    if (pbeta <= 99.942) goto label_329;
    goto label_100;
  label_1553  :
    decay0_beta(prng_, event_, 0.258,74.,0.,0.,t);
    ////    label_15530  :
    thlev=1.23e-9;
    p=100.*prng_();
    if (p <=  0.25) goto label_15531;
    if (p <=  1.45) goto label_15532;
    if (p <= 22.47) goto label_15533;
    if (p <= 65.50) goto label_15534;
    if (p <= 83.50) goto label_15535;
    if (p <= 84.00) goto label_15536;
    goto label_15537;
  label_15531  :
    decay0_nucltransK(prng_, event_, 1.453,0.070,4.5e-3,0.1e-4,tclev,thlev,tdlev);
    goto label_10000;
  label_15532  :
    decay0_nucltransK(prng_, event_, 1.223,0.070,2.5e-3,0.1e-4,tclev,thlev,tdlev);
    goto label_32900;
  label_15533  :
    decay0_nucltransK(prng_, event_, 0.264,0.070,1.4e-1,0.,tclev,thlev,tdlev);
    goto label_12890;
  label_15534  :
    decay0_nucltransK(prng_, event_, 0.222,0.070,5.0e-2,0.,tclev,thlev,tdlev);
    goto label_13310;
  label_15535  :
    decay0_nucltransK(prng_, event_, 0.179,0.070,7.5e-1,0.,tclev,thlev,tdlev);
    goto label_13740;
  label_15536  :
    decay0_nucltransK(prng_, event_, 0.110,0.070,3.0e-1,0.,tclev,thlev,tdlev);
    goto label_14430;
  label_15537  :
    decay0_nucltransK(prng_, event_, 0.066,0.012,3.0e-0,0.,tclev,thlev,tdlev);
    goto label_14880;
  label_1510  :
    decay0_beta(prng_, event_, 0.301,74.,0.,0.,t);
    ////    label_15100  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 34.) goto label_15101;
    goto label_15102;
  label_15101  :
    decay0_nucltransK(prng_, event_, 1.410,0.070,2.4e-3,0.1e-4,tclev,thlev,tdlev);
    goto label_10000;
  label_15102  :
    decay0_nucltransK(prng_, event_, 1.181,0.070,1.4e-3,0.1e-4,tclev,thlev,tdlev);
    goto label_32900;
  label_1488  :
    decay0_beta(prng_, event_, 0.323,74.,0.,0.,t);
  label_14880  :
    thlev=0.;
    p=100.*prng_();
    if (p <=  1.1) goto label_14881;
    if (p <=  6.1) goto label_14882;
    if (p <= 29.3) goto label_14883;
    if (p <= 70.8) goto label_14884;
    goto label_14885;
  label_14881  :
    decay0_nucltransK(prng_, event_, 1.387,0.070,5.0e-3,0.5e-5,tclev,thlev,tdlev);
    goto label_10000;
  label_14882  :
    decay0_nucltransK(prng_, event_, 1.158,0.070,1.5e-3,0.5e-5,tclev,thlev,tdlev);
    goto label_32900;
  label_14883  :
    decay0_nucltransK(prng_, event_, 0.198,0.070,3.2e-1,0.,tclev,thlev,tdlev);
    goto label_12890;
  label_14884  :
    decay0_nucltransK(prng_, event_, 0.156,0.070,1.2e-1,0.,tclev,thlev,tdlev);
    goto label_13310;
  label_14885  :
    decay0_nucltransK(prng_, event_, 0.114,0.070,3.8e-0,0.,tclev,thlev,tdlev);
    goto label_13740;
  label_1443  :
    decay0_beta(prng_, event_, 0.368,74.,0.,0.,t);
  label_14430  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 40.) goto label_14431;
    goto label_14432;
  label_14431  :
    decay0_nucltransK(prng_, event_, 1.343,0.070,2.8e-3,0.1e-4,tclev,thlev,tdlev);
    goto label_10000;
  label_14432  :
    decay0_nucltransK(prng_, event_, 1.113,0.070,6.0e-3,0.,tclev,thlev,tdlev);
    goto label_32900;
  label_1374  :
    decay0_beta(prng_, event_, 0.437,74.,0.,0.,t);
  label_13740  :
    thlev=0.08e-9;
    p=100.*prng_();
    if (p <=  2.0) goto label_13741;
    if (p <=  7.7) goto label_13742;
    if (p <=  9.8) goto label_13743;
    if (p <= 71.3) goto label_13744;
    if (p <= 75.1) goto label_13745;
    if (p <= 97.9) goto label_13746;
    goto label_13747;
  label_13741  :
    decay0_nucltransK(prng_, event_, 1.374,0.070,5.5e-3,0.5e-5,tclev,thlev,tdlev);
    return;
  label_13742  :
    decay0_nucltransK(prng_, event_, 1.274,0.070,3.0e-3,0.1e-4,tclev,thlev,tdlev);
    goto label_10000;
  label_13743  :
    decay0_nucltransK(prng_, event_, 1.044,0.070,6.6e-3,0.,tclev,thlev,tdlev);
    goto label_32900;
  label_13744  :
    decay0_nucltransK(prng_, event_, 0.152,0.070,1.2e-1,0.,tclev,thlev,tdlev);
    goto label_12210;
  label_13745  :
    decay0_nucltransK(prng_, event_, 0.116,0.070,2.6e-1,0.,tclev,thlev,tdlev);
    goto label_12570;
  label_13746  :
    decay0_nucltransK(prng_, event_, 0.085,0.070,8.5e-0,0.,tclev,thlev,tdlev);
    goto label_12890;
  label_13747  :
    decay0_nucltransK(prng_, event_, 0.043,0.012,7.0e-1,0.,tclev,thlev,tdlev);
    goto label_13310;
  label_1331  :
    decay0_beta(prng_, event_, 0.480,74.,0.,0.,t);
  label_13310  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 85.) goto label_13311;
    goto label_13312;
  label_13311  :
    decay0_nucltransK(prng_, event_, 1.231,0.070,3.0e-3,0.1e-4,tclev,thlev,tdlev);
    goto label_10000;
  label_13312  :
    decay0_nucltransK(prng_, event_, 1.002,0.070,4.7e-3,0.,tclev,thlev,tdlev);
    goto label_32900;
  label_1289  :
    decay0_beta(prng_, event_, 0.522,74.,0.,0.,t);
  label_12890  :
    thlev=1.12e-9;
    p=100.*prng_();
    if (p <=  2.35) goto label_12891;
    if (p <= 29.75) goto label_12892;
    if (p <= 30.34) goto label_12893;
    if (p <= 99.00) goto label_12894;
    goto label_12895;
  label_12891  :
    decay0_nucltransK(prng_, event_, 1.289,0.070,1.3e-2,0.3e-4,tclev,thlev,tdlev);
    return;
  label_12892  :
    decay0_nucltransK(prng_, event_, 1.189,0.070,5.3e-3,0.1e-4,tclev,thlev,tdlev);
    goto label_10000;
  label_12893  :
    decay0_nucltransK(prng_, event_, 0.960,0.070,1.3e-2,0.,tclev,thlev,tdlev);
    goto label_32900;
  label_12894  :
    decay0_nucltransK(prng_, event_, 0.068,0.012,2.0e-1,0.,tclev,thlev,tdlev);
    goto label_12210;
  label_12895  :
    decay0_nucltransK(prng_, event_, 0.032,0.012,1.6e-0,0.,tclev,thlev,tdlev);
    goto label_12570;
  label_1257  :
    decay0_beta(prng_, event_, 0.554,74.,0.,0.,t);
  label_12570  :
    thlev=1.7e-12;
    p=100.*prng_();
    if (p <= 54.5) goto label_12571;
    if (p <= 77.8) goto label_12572;
    goto label_12573;
  label_12571  :
    decay0_nucltransK(prng_, event_, 1.257,0.070,3.0e-3,0.1e-4,tclev,thlev,tdlev);
    return;
  label_12572  :
    decay0_nucltransK(prng_, event_, 1.157,0.070,5.3e-3,0.,tclev,thlev,tdlev);
    goto label_10000;
  label_12573  :
    decay0_nucltransK(prng_, event_, 0.928,0.070,5.5e-3,0.,tclev,thlev,tdlev);
    goto label_32900;
  label_1221  :
    decay0_beta(prng_, event_, 0.590,74.,0.,0.,t);
  label_12210  :
    thlev=0.37e-12;
    p=100.*prng_();
    if (p <= 44.00) goto label_12211;
    if (p <= 99.92) goto label_12212;
    goto label_12213;
  label_12211  :
    decay0_nucltransK(prng_, event_, 1.221,0.070,3.0e-3,0.1e-4,tclev,thlev,tdlev);
    return;
  label_12212  :
    decay0_nucltransK(prng_, event_, 1.121,0.070,3.5e-3,0.1e-5,tclev,thlev,tdlev);
    goto label_10000;
  label_12213  :
    decay0_nucltransK(prng_, event_, 0.892,0.070,6.0e-3,0.,tclev,thlev,tdlev);
    goto label_32900;
  label_329  :
    decay0_beta(prng_, event_, 1.482,74.,0.,0.,t);
  label_32900  :
    thlev=64.e-12;
    decay0_nucltransK(prng_, event_, 0.229,0.070,2.4e-1,0.,tclev,thlev,tdlev);
    goto label_10000;
  label_100  :
    decay0_beta(prng_, event_, 1.711,74.,0.,0.,t);
  label_10000  :
    thlev=1.38e-9;
    decay0_nucltransK(prng_, event_, 0.100,0.012,4.0e-0,0.,tclev,thlev,tdlev);
    return;
  }
  // end of Ta182.f




} // end of namespace bxdecay0

// end of Ta182.cc
// Local Variables: --
// mode: c++ --
// End: --
