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
#include <bxdecay0/I133.h>

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

  void I133(i_random & prng_,
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
    // Scheme of I133 decay in accordance with S.Rab, NDS 75(1995)491.
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 13.12.2003.
    thnuc=74880.;
    tdnuc_=tcnuc_-thnuc/std::log(2.)*std::log(prng_());
    tclev=0.;
    pbeta=100.*prng_();
    if (pbeta <=  0.42) goto label_1590;
    if (pbeta <=  1.68) goto label_1386;
    if (pbeta <=  2.08) goto label_1350;
    if (pbeta <=  5.89) goto label_1298;
    if (pbeta <=  9.10) goto label_1236;
    if (pbeta <=  9.73) goto label_1052;
    if (pbeta <= 13.94) goto label_875;
    if (pbeta <= 15.77) goto label_744;
    if (pbeta <= 98.96) goto label_530;
    goto label_233;
  label_1590  :
    decay0_beta(prng_, event_, 0.181,54.,0.,0.,t);
    ////label_15900  :
    thlev=0.;
    p=100.*prng_();
    if (p <=  0.72) goto label_15901;
    if (p <= 33.78) goto label_15902;
    if (p <= 85.06) goto label_15903;
    if (p <= 90.33) goto label_15904;
    if (p <= 98.95) goto label_15905;
    goto label_15906;
  label_15901  :
    decay0_nucltransK(prng_, event_, 1.590,0.035,1.0e-3,1.1e-4,tclev,thlev,tdlev);
    return;
  label_15902  :
    decay0_nucltransK(prng_, event_, 1.060,0.035,1.7e-3,0.,tclev,thlev,tdlev);
    goto label_53000;
  label_15903  :
    decay0_nucltransK(prng_, event_, 0.910,0.035,2.0e-2,0.,tclev,thlev,tdlev);
    goto label_68000;
  label_15904  :
    decay0_nucltransK(prng_, event_, 0.679,0.035,5.5e-3,0.,tclev,thlev,tdlev);
    goto label_91100;
  label_15905  :
    decay0_nucltransK(prng_, event_, 0.538,0.035,8.5e-3,0.,tclev,thlev,tdlev);
    goto label_10520;
  label_15906  :
    decay0_nucltransK(prng_, event_, 0.204,0.035,1.5e-1,0.,tclev,thlev,tdlev);
    goto label_13860;
  label_1386  :
    decay0_beta(prng_, event_, 0.385,54.,0.,0.,t);
  label_13860  :
    thlev=0.;
    p=100.*prng_();
    if (p <=  0.72) goto label_13861;
    goto label_13862;
  label_13861  :
    decay0_nucltransK(prng_, event_, 1.386,0.035,3.5e-3,0.,tclev,thlev,tdlev);
    return;
  label_13862  :
    decay0_nucltransK(prng_, event_, 0.856,0.035,2.6e-3,0.,tclev,thlev,tdlev);
    goto label_53000;
  label_1350  :
    decay0_beta(prng_, event_, 0.421,54.,0.,0.,t);
    ////label_13500  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 37.48) goto label_13501;
    if (p <= 40.53) goto label_13502;
    if (p <= 79.26) goto label_13503;
    if (p <= 90.00) goto label_13504;
    goto label_13505;
  label_13501  :
    decay0_nucltransK(prng_, event_, 1.350,0.035,9.9e-4,0.6e-4,tclev,thlev,tdlev);
    return;
  label_13502  :
    decay0_nucltransK(prng_, event_, 1.088,0.035,1.3e-3,0.,tclev,thlev,tdlev);
    goto label_26300;
  label_13503  :
    decay0_nucltransK(prng_, event_, 0.821,0.035,3.1e-3,0.,tclev,thlev,tdlev);
    goto label_53000;
  label_13504  :
    decay0_nucltransK(prng_, event_, 0.670,0.035,5.0e-3,0.,tclev,thlev,tdlev);
    goto label_68000;
  label_13505  :
    decay0_nucltransK(prng_, event_, 0.439,0.035,1.4e-2,0.,tclev,thlev,tdlev);
    goto label_91100;
  label_1298  :
    decay0_beta(prng_, event_, 0.473,54.,0.,0.,t);
    ////label_12980  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 62.29) goto label_12981;
    if (p <= 62.52) goto label_12982;
    if (p <= 74.71) goto label_12983;
    if (p <= 89.13) goto label_12984;
    if (p <= 97.51) goto label_12985;
    if (p <= 99.07) goto label_12986;
    goto label_12987;
  label_12981  :
    decay0_nucltransK(prng_, event_, 1.298,0.035,9.6e-4,0.5e-4,tclev,thlev,tdlev);
    return;
  label_12982  :
    decay0_nucltransK(prng_, event_, 1.036,0.035,1.5e-3,0.,tclev,thlev,tdlev);
    goto label_26300;
  label_12983  :
    decay0_nucltransK(prng_, event_, 0.768,0.035,3.5e-3,0.,tclev,thlev,tdlev);
    goto label_53000;
  label_12984  :
    decay0_nucltransK(prng_, event_, 0.618,0.035,5.9e-3,0.,tclev,thlev,tdlev);
    goto label_68000;
  label_12985  :
    decay0_nucltransK(prng_, event_, 0.423,0.035,1.5e-2,0.,tclev,thlev,tdlev);
    goto label_87500;
  label_12986  :
    decay0_nucltransK(prng_, event_, 0.387,0.035,2.0e-2,0.,tclev,thlev,tdlev);
    goto label_91100;
  label_12987  :
    decay0_nucltransK(prng_, event_, 0.246,0.035,8.0e-2,0.,tclev,thlev,tdlev);
    goto label_10520;
  label_1236  :
    decay0_beta(prng_, event_, 0.535,54.,0.,0.,t);
    ////label_12360  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 47.94) goto label_12361;
    if (p <= 95.88) goto label_12362;
    if (p <= 96.51) goto label_12363;
    goto label_12364;
  label_12361  :
    decay0_nucltransK(prng_, event_, 1.236,0.035,1.0e-3,0.1e-4,tclev,thlev,tdlev);
    return;
  label_12362  :
    decay0_nucltransK(prng_, event_, 0.707,0.035,4.3e-3,0.,tclev,thlev,tdlev);
    goto label_53000;
  label_12363  :
    decay0_nucltransK(prng_, event_, 0.556,0.035,7.0e-3,0.,tclev,thlev,tdlev);
    goto label_68000;
  label_12364  :
    decay0_nucltransK(prng_, event_, 0.361,0.035,3.0e-2,0.,tclev,thlev,tdlev);
    goto label_87500;
  label_1052  :
    decay0_beta(prng_, event_, 0.719,54.,0.,0.,t);
  label_10520  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 90.26) goto label_10521;
    if (p <= 98.37) goto label_10522;
    goto label_10523;
  label_10521  :
    decay0_nucltransK(prng_, event_, 1.052,0.035,2.0e-3,0.,tclev,thlev,tdlev);
    return;
  label_10522  :
    decay0_nucltransK(prng_, event_, 0.790,0.035,3.0e-3,0.,tclev,thlev,tdlev);
    goto label_26300;
  label_10523  :
    decay0_nucltransK(prng_, event_, 0.372,0.035,2.5e-2,0.,tclev,thlev,tdlev);
    goto label_68000;
  label_91100  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 31.08) goto label_91101;
    if (p <= 69.59) goto label_91102;
    goto label_91103;
  label_91101  :
    decay0_nucltransK(prng_, event_, 0.911,0.035,3.0e-3,0.,tclev,thlev,tdlev);
    return;
  label_91102  :
    decay0_nucltransK(prng_, event_, 0.649,0.035,6.0e-3,0.,tclev,thlev,tdlev);
    goto label_26300;
  label_91103  :
    decay0_nucltransK(prng_, event_, 0.382,0.035,2.0e-2,0.,tclev,thlev,tdlev);
    goto label_53000;
  label_875  :
    decay0_beta(prng_, event_, 0.896,54.,0.,0.,t);
  label_87500  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 97.75) goto label_87501;
    goto label_87502;
  label_87501  :
    decay0_nucltransK(prng_, event_, 0.875,0.035,2.2e-3,0.,tclev,thlev,tdlev);
    return;
  label_87502  :
    decay0_nucltransK(prng_, event_, 0.345,0.035,3.0e-2,0.,tclev,thlev,tdlev);
    goto label_53000;
  label_744  :
    decay0_beta(prng_, event_, 1.027,54.,0.,0.,t);
    ////label_74400  :
    thlev=0.;
    decay0_nucltransK(prng_, event_, 0.510,0.035,9.0e-3,0.,tclev,thlev,tdlev);
    goto label_23300;
  label_68000  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 77.66) goto label_68001;
    if (p <= 96.42) goto label_68002;
    goto label_68003;
  label_68001  :
    decay0_nucltransK(prng_, event_, 0.680,0.035,5.4e-3,0.,tclev,thlev,tdlev);
    return;
  label_68002  :
    decay0_nucltransK(prng_, event_, 0.418,0.035,1.6e-2,0.,tclev,thlev,tdlev);
    goto label_26300;
  label_68003  :
    decay0_nucltransK(prng_, event_, 0.150,0.035,3.0e-1,0.,tclev,thlev,tdlev);
    goto label_53000;
  label_530  :
    decay0_beta(prng_, event_, 1.241,54.,0.,0.,t);
  label_53000  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 99.87) goto label_53001;
    goto label_53002;
  label_53001  :
    decay0_nucltransK(prng_, event_, 0.530,0.035,8.2e-3,0.,tclev,thlev,tdlev);
    return;
  label_53002  :
    decay0_nucltransK(prng_, event_, 0.267,0.035,6.0e-2,0.,tclev,thlev,tdlev);
    goto label_26300;
  label_26300  :
    thlev=0.;
    decay0_nucltransK(prng_, event_, 0.263,0.035,5.8e-2,0.,tclev,thlev,tdlev);
    return;
  label_233  :
    decay0_beta(prng_, event_, 1.538,54.,0.,0.,t);
  label_23300  :
    thlev=189216.;
    decay0_nucltransK(prng_, event_, 0.233,0.035,8.8,0.,tclev,thlev,tdlev);
    return;
    return;
  }
  // end of I133.f




} // end of namespace bxdecay0

// end of I133.cc
// Local Variables: --
// mode: c++ --
// End: --
