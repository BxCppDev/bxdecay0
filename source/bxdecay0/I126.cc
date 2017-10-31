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
#include <bxdecay0/I126.h>

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

  void I126(i_random & prng_,
            event & event_,
            const double tcnuc_,
            double & tdnuc_)
  {
    double t;
    double tdlev;
    double p;
    double pbeta;
    double pdecay;
    double pec;
    double tclev;
    double thlev;
    double thnuc;
    // Model for scheme of I126 decay (J.Katakura et al., Nucl. Data Sheets
    // 97(2002)765).
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 25.11.2003.
    thnuc=1.1172e6;
    tdnuc_=tcnuc_-thnuc/std::log(2.)*std::log(prng_());
    tclev=0.;
    pdecay=100.*prng_();
    if (pdecay <= 47.300) goto label_1;  // 47.300% beta- to 126Xe
    if (pdecay <= 98.992) goto label_2;  // 51.692% EC to 126Te
    goto label_3;  // 1.008% beta+ to 126Te
    // beta-
  label_1  :
    pbeta=100.*prng_();
    if (pbeta <=  7.65) goto label_880;  // 7.65%
    if (pbeta <= 78.22) goto label_389;  // 70.57%
    decay0_beta(prng_, event_, 1.258,54.,0.,0.,t)  ;// 21.78%
    return;
  label_880  :
    decay0_beta(prng_, event_, 0.378,54.,0.,0.,t);
    //// label_88000  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 20.51) goto label_88001;
    goto label_88002;
  label_88001  :
    decay0_nucltransK(prng_, event_, 0.880,0.035,2.2e-3,0.,tclev,thlev,tdlev);
    return;
  label_88002  :
    decay0_nucltransK(prng_, event_, 0.491,0.035,9.5e-3,0.,tclev,thlev,tdlev);
    goto label_38900;
  label_389  :
    decay0_beta(prng_, event_, 0.869,54.,0.,0.,t);
  label_38900  :
    thlev=41.3e-12;
    p=100.*prng_();
    decay0_nucltransK(prng_, event_, 0.389,0.035,1.9e-2,0.,tclev,thlev,tdlev);
    return;
    // EC
  label_2  :
    decay0_gamma(prng_, event_, 0.032,0.,0.,t);
    pec=100.*prng_();
    if (pec <=  0.014) goto label_2045;  // 0.014%
    if (pec <=  0.015) goto label_1873;  // 0.001%
    if (pec <=  8.630) goto label_1420;  // 8.615%
    if (pec <= 63.800) goto label_666;  // 55.170%
    return  ;// 36.200%
  label_2045  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 66.00) goto label_20451;
    goto label_20452;
  label_20451  :
    decay0_nucltransK(prng_, event_, 2.045,0.032,3.0e-4,2.3e-4,tclev,thlev,tdlev);
    return;
  label_20452  :
    decay0_nucltransK(prng_, event_, 1.379,0.032,1.2e-3,0.7e-4,tclev,thlev,tdlev);
    goto label_66600;
  label_1873  :
    thlev=0.;
    decay0_nucltransK(prng_, event_, 1.207,0.032,1.1e-3,0.1e-4,tclev,thlev,tdlev);
    goto label_66600;
  label_1420  :
    thlev=0.;
    p=100.*prng_();
    if (p <=  6.83) goto label_14201;
    goto label_14202;
  label_14201  :
    decay0_nucltransK(prng_, event_, 1.420,0.032,7.0e-4,0.2e-4,tclev,thlev,tdlev);
    return;
  label_14202  :
    decay0_nucltransK(prng_, event_, 0.754,0.032,2.8e-3,0.,tclev,thlev,tdlev);
    goto label_66600;
  label_666  :
    //continue;
  label_66600  :
    thlev=0.;
    decay0_nucltransK(prng_, event_, 0.666,0.032,3.8e-3,0.,tclev,thlev,tdlev);
    return;
    // beta+
  label_3  :
    pbeta=100.*prng_();
    if (pbeta <= 19.64) goto label_1666;  // 19.64%
    decay0_beta(prng_, event_, 1.133,-52.,0.,0.,t)  ;// 80.36%
    return;
  label_1666  :
    decay0_beta(prng_, event_, 0.467,-52.,0.,0.,t);
    thlev=0.;
    decay0_nucltransK(prng_, event_, 0.666,0.032,3.8e-3,0.,tclev,thlev,tdlev);
    return;
  }
  // end of I126.f




} // end of namespace bxdecay0

// end of I126.cc
// Local Variables: --
// mode: c++ --
// End: --
