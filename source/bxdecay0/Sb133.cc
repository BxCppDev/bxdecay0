// Ourselves:
#include <bxdecay0/Sb133.h>

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

  // Sb133.f
  // This file was extracted from the 'decay0' program by V.I. Tretyak
  // Copyright 1995-2011 V.I. Tretyak
  // This program is free software
  // it under the terms of the GNU General Public License as published by
  // the Free Software Foundation
  // your option) any later version.
  //
  // This program is distributed in the hope that it will be useful, but
  // WITHOUT ANY WARRANTY
  // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  // General Public License for more details.
  //
  // You should have received a copy of the GNU General Public License
  // along with this program
  // Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
  //

  void Sb133(i_random & prng_,
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
    // Scheme of 133Sb decay (S.Rab, NDS 75(1995)491).
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 11.12.2003.
    thnuc=150;
    tdnuc_=tcnuc_-thnuc/std::log(2.)*std::log(prng_());
    tclev=0.;
    pbeta=100.*prng_();
    if (pbeta <= 27.84) goto label_2756;
    if (pbeta <= 53.70) goto label_2750;
    if (pbeta <= 58.28) goto label_2211;
    if (pbeta <= 58.58) goto label_2024;
    if (pbeta <= 59.58) goto label_1976;
    if (pbeta <= 68.54) goto label_1913;
    if (pbeta <= 75.31) goto label_1729;
    if (pbeta <= 76.31) goto label_1706;
    if (pbeta <= 80.19) goto label_1642;
    if (pbeta <= 83.97) goto label_1640;
    if (pbeta <= 88.15) goto label_1552;
    if (pbeta <= 88.95) goto label_1501;
    if (pbeta <= 91.14) goto label_1421;
    if (pbeta <= 94.03) goto label_1265;
    goto label_1096;
  label_2756  :
    decay0_beta(prng_, event_, 1.247,52.,0.,0.,t);
    ////    label_27560  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 45.15) goto label_27561;
    if (p <= 49.81) goto label_27562;
    if (p <= 57.90) goto label_27563;
    if (p <= 67.22) goto label_27564;
    if (p <= 87.10) goto label_27565;
    goto label_27566;
  label_27561  :
    decay0_nucltransK(prng_, event_, 2.755,0.032,1.5e-4,5.7e-4,tclev,thlev,tdlev);
    return;
  label_27562  :
    decay0_nucltransK(prng_, event_, 2.447,0.032,1.5e-4,5.2e-4,tclev,thlev,tdlev);
    goto label_30800;
  label_27563  :
    decay0_nucltransK(prng_, event_, 1.659,0.032,4.0e-4,1.3e-4,tclev,thlev,tdlev);
    goto label_10960;
  label_27564  :
    decay0_nucltransK(prng_, event_, 1.490,0.032,5.0e-4,0.9e-4,tclev,thlev,tdlev);
    goto label_12650;
  label_27565  :
    decay0_nucltransK(prng_, event_, 1.026,0.032,1.5e-3,0.,tclev,thlev,tdlev);
    goto label_17290;
  label_27566  :
    decay0_nucltransK(prng_, event_, 0.423,0.032,1.2e-2,0.,tclev,thlev,tdlev);
    goto label_23320;
  label_2750  :
    decay0_beta(prng_, event_, 1.253,52.,0.,0.,t);
    ////    label_27500  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 32.79) goto label_27501;
    if (p <= 39.00) goto label_27502;
    if (p <= 42.36) goto label_27503;
    if (p <= 49.24) goto label_27504;
    if (p <= 92.58) goto label_27505;
    goto label_27506;
  label_27501  :
    decay0_nucltransK(prng_, event_, 2.416,0.032,8.0e-5,5.0e-4,tclev,thlev,tdlev);
    goto label_33400;
  label_27502  :
    decay0_nucltransK(prng_, event_, 1.654,0.032,4.0e-4,1.3e-4,tclev,thlev,tdlev);
    goto label_10960;
  label_27503  :
    decay0_nucltransK(prng_, event_, 1.250,0.032,1.0e-3,0.4e-4,tclev,thlev,tdlev);
    goto label_15010;
  label_27504  :
    decay0_nucltransK(prng_, event_, 1.111,0.032,1.5e-3,0.1e-4,tclev,thlev,tdlev);
    goto label_16400;
  label_27505  :
    decay0_nucltransK(prng_, event_, 0.837,0.032,8.0e-4,0.,tclev,thlev,tdlev);
    goto label_19130;
  label_27506  :
    decay0_nucltransK(prng_, event_, 0.539,0.032,7.0e-3,0.,tclev,thlev,tdlev);
    goto label_22110;
  label_23320  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 65.82) goto label_23321;
    goto label_23322;
  label_23321  :
    decay0_nucltransK(prng_, event_, 1.236,0.032,1.0e-3,0.4e-4,tclev,thlev,tdlev);
    goto label_10960;
  label_23322  :
    decay0_nucltransK(prng_, event_, 0.308,0.032,2.5e-2,0.,tclev,thlev,tdlev);
    goto label_20240;
  label_2211  :
    decay0_beta(prng_, event_, 1.792,52.,0.,0.,t);
  label_22110  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 23.75) goto label_22111;
    if (p <= 97.38) goto label_22112;
    goto label_22113;
  label_22111  :
    decay0_nucltransK(prng_, event_, 1.877,0.032,3.5e-4,1.9e-4,tclev,thlev,tdlev);
    goto label_33400;
  label_22112  :
    decay0_nucltransK(prng_, event_, 1.115,0.032,1.5e-3,0.1e-4,tclev,thlev,tdlev);
    goto label_10960;
  label_22113  :
    decay0_nucltransK(prng_, event_, 0.572,0.032,5.5e-3,0.,tclev,thlev,tdlev);
    goto label_16400;
  label_2024  :
    decay0_beta(prng_, event_, 1.979,52.,0.,0.,t);
  label_20240  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 81.61) goto label_20241;
    goto label_20242;
  label_20241  :
    decay0_nucltransK(prng_, event_, 0.928,0.032,1.8e-3,0.,tclev,thlev,tdlev);
    goto label_10960;
  label_20242  :
    decay0_nucltransK(prng_, event_, 0.523,0.032,7.0e-3,0.,tclev,thlev,tdlev);
    goto label_15010;
  label_1976  :
    decay0_beta(prng_, event_, 2.027,52.,0.,0.,t);
    ////    label_19760  :
    thlev=0.;
    decay0_nucltransK(prng_, event_, 1.976,0.032,3.0e-4,3.2e-4,tclev,thlev,tdlev);
    return;
  label_1913  :
    decay0_beta(prng_, event_, 2.090,52.,0.,0.,t);
  label_19130  :
    thlev=0.;
    p=100.*prng_();
    if (p <=  7.81) goto label_19131;
    if (p <= 98.08) goto label_19132;
    goto label_19133;
  label_19131  :
    decay0_nucltransK(prng_, event_, 1.579,0.032,4.5e-4,0.4e-4,tclev,thlev,tdlev);
    goto label_33400;
  label_19132  :
    decay0_nucltransK(prng_, event_, 0.818,0.032,8.0e-4,0.,tclev,thlev,tdlev);
    goto label_10960;
  label_19133  :
    decay0_nucltransK(prng_, event_, 0.413,0.032,1.2e-2,0.,tclev,thlev,tdlev);
    goto label_15010;
  label_1729  :
    decay0_beta(prng_, event_, 2.274,52.,0.,0.,t);
  label_17290  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 68.47) goto label_17291;
    goto label_17292;
  label_17291  :
    decay0_nucltransK(prng_, event_, 1.729,0.032,4.5e-4,1.5e-4,tclev,thlev,tdlev);
    return;
  label_17292  :
    decay0_nucltransK(prng_, event_, 0.632,0.032,4.5e-3,0.,tclev,thlev,tdlev);
    goto label_10960;
  label_1706  :
    decay0_beta(prng_, event_, 2.297,52.,0.,0.,t);
    ////    label_17060  :
    thlev=0.;
    decay0_nucltransK(prng_, event_, 1.706,0.032,4.5e-4,1.5e-4,tclev,thlev,tdlev);
    return;
  label_1642  :
    decay0_beta(prng_, event_, 2.361,52.,0.,0.,t);
    ////    label_16420  :
    thlev=0.;
    decay0_nucltransK(prng_, event_, 1.642,0.032,5.0e-4,1.2e-4,tclev,thlev,tdlev);
    return;
  label_1640  :
    decay0_beta(prng_, event_, 2.363,52.,0.,0.,t);
  label_16400  :
    thlev=0.;
    decay0_nucltransK(prng_, event_, 1.305,0.032,9.0e-4,0.5e-4,tclev,thlev,tdlev);
    goto label_33400;
  label_1552  :
    decay0_beta(prng_, event_, 2.451,52.,0.,0.,t);
    ////    label_15520  :
    thlev=0.;
    decay0_nucltransK(prng_, event_, 1.552,0.032,5.0e-4,1.0e-4,tclev,thlev,tdlev);
    return;
  label_1501  :
    decay0_beta(prng_, event_, 2.502,52.,0.,0.,t);
  label_15010  :
    thlev=0.;
    decay0_nucltransK(prng_, event_, 0.404,0.032,1.3e-2,0.,tclev,thlev,tdlev);
    goto label_10960;
  label_1421  :
    decay0_beta(prng_, event_, 2.582,52.,0.,0.,t);
    ////    label_14210  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 13.44) goto label_14211;
    goto label_14212;
  label_14211  :
    decay0_nucltransK(prng_, event_, 1.421,0.032,6.5e-4,0.7e-4,tclev,thlev,tdlev);
    return;
  label_14212  :
    decay0_nucltransK(prng_, event_, 1.113,0.032,1.3e-3,0.,tclev,thlev,tdlev);
    goto label_30800;
  label_1265  :
    decay0_beta(prng_, event_, 2.738,52.,0.,0.,t);
  label_12650  :
    thlev=0.;
    decay0_nucltransK(prng_, event_, 1.265,0.032,9.0e-4,0.5e-4,tclev,thlev,tdlev);
    return;
  label_1096  :
    decay0_beta(prng_, event_, 2.907,52.,0.,0.,t);
  label_10960  :
    thlev=0.;
    decay0_nucltransK(prng_, event_, 1.096,0.032,1.1e-3,0.,tclev,thlev,tdlev);
    return;
  label_33400  :
    return  ;// creation of isomeric 133mTe with E_exc=334 keV and T1/2=55.4 m
  label_30800  :
    thlev=0.;
    decay0_nucltransK(prng_, event_, 0.308,0.032,2.5e-2,0.,tclev,thlev,tdlev);
    return  ;// creation of 133Te in g.s. (T1/2=12.5 m)
    return;
  }
  // end of Sb133.f




} // end of namespace bxdecay0

// end of Sb133.cc
// Local Variables: --
// mode: c++ --
// End: --
