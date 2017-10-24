// Ourselves:
#include <bxdecay0/Sb125.h>

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

  // Sb125.f
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

  void Sb125(i_random & prng_,
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
    // Scheme of 125Sb decay (NDS 86(1999)955 + NNDC on 7.02.2010).
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 13.02.2010.
    thnuc=8.705115e7;
    tdnuc_=tcnuc_-thnuc/std::log(2.)*std::log(prng_());
    tclev=0.;
    pbeta=100.*prng_();
    if (pbeta <= 13.446) goto label_671;
    if (pbeta <= 13.502) goto label_653;
    if (pbeta <= 19.265) goto label_642;
    if (pbeta <= 37.180) goto label_636;
    if (pbeta <= 38.791) goto label_525;
    if (pbeta <= 79.199) goto label_463;
    if (pbeta <= 79.247) goto label_444;
    if (pbeta <= 79.268) goto label_402;
    if (pbeta <= 86.464) goto label_321;
    goto label_145;
  label_671  :
    decay0_beta(prng_, event_, 0.096,52.,0.,0.,t);
    ////    label_6710  :
    thlev=1.26e-12;
    p=100.*prng_();
    if (p <= 13.347) goto label_6711;
    if (p <= 96.921) goto label_6712;
    if (p <= 97.980) goto label_6713;
    if (p <= 99.993) goto label_6714;
    goto label_6715;
  label_6711  :
    decay0_nucltransK(prng_, event_, 0.671,0.032,3.8e-3,0.,tclev,thlev,tdlev);
    return;
  label_6712  :
    decay0_nucltransK(prng_, event_, 0.636,0.032,5.3e-3,0.,tclev,thlev,tdlev);
    goto label_3500;
  label_6713  :
    decay0_nucltransK(prng_, event_, 0.228,0.032,8.4e-2,0.,tclev,thlev,tdlev);
    goto label_4440;
  label_6714  :
    decay0_nucltransK(prng_, event_, 0.208,0.032,9.1e-2,0.,tclev,thlev,tdlev);
    goto label_4630;
  label_6715  :
    decay0_nucltransK(prng_, event_, 0.133,0.032,3.1e-1,0.,tclev,thlev,tdlev);
    goto label_5390;
  label_653  :
    decay0_beta(prng_, event_, 0.114,52.,0.,0.,t);
    ////    label_6530  :
    thlev=0.;
    p=100.*prng_();
    if (p <=  4.85) goto label_6531;
    if (p <= 14.56) goto label_6532;
    if (p <= 19.11) goto label_6533;
    goto label_6534;
  label_6531  :
    decay0_nucltransK(prng_, event_, 0.653,0.032,4.0e-3,0.,tclev,thlev,tdlev);
    return;
  label_6532  :
    decay0_nucltransK(prng_, event_, 0.617,0.032,5.6e-3,0.,tclev,thlev,tdlev);
    goto label_3500;
  label_6533  :
    decay0_nucltransK(prng_, event_, 0.332,0.032,2.8e-2,0.,tclev,thlev,tdlev);
    goto label_3210;
  label_6534  :
    decay0_nucltransK(prng_, event_, 0.209,0.032,8.9e-2,0.,tclev,thlev,tdlev);
    goto label_4440;
  label_642  :
    decay0_beta(prng_, event_, 0.125,52.,0.,0.,t);
    ////    label_6420  :
    thlev=70e-12;
    p=100.*prng_();
    if (p <= 86.63) goto label_6421;
    if (p <= 86.70) goto label_6422;
    if (p <= 93.91) goto label_6423;
    if (p <= 94.17) goto label_6424;
    if (p <= 94.86) goto label_6425;
    goto label_6426;
  label_6421  :
    decay0_nucltransK(prng_, event_, 0.607,0.032,4.9e-3,0.,tclev,thlev,tdlev);
    goto label_3500;
  label_6422  :
    decay0_nucltransK(prng_, event_, 0.497,0.032,3.2e-2,0.,tclev,thlev,tdlev);
    goto label_1450;
  label_6423  :
    decay0_nucltransK(prng_, event_, 0.321,0.032,7.9e-3,0.,tclev,thlev,tdlev);
    goto label_3210;
  label_6424  :
    decay0_nucltransK(prng_, event_, 0.199,0.032,1.5e-1,0.,tclev,thlev,tdlev);
    goto label_4440;
  label_6425  :
    decay0_nucltransK(prng_, event_, 0.179,0.032,1.8e-1,0.,tclev,thlev,tdlev);
    goto label_4630;
  label_6426  :
    decay0_nucltransK(prng_, event_, 0.117,0.032,1.3e-1,0.,tclev,thlev,tdlev);
    goto label_5250;
  label_636  :
    decay0_beta(prng_, event_, 0.131,52.,0.,0.,t);
    ////    label_6360  :
    thlev=40e-12;
    p=100.*prng_();
    if (p <= 98.716) goto label_6361;
    if (p <= 98.743) goto label_6362;
    if (p <= 98.766) goto label_6363;
    if (p <= 99.994) goto label_6364;
    goto label_6365;
  label_6361  :
    decay0_nucltransK(prng_, event_, 0.601,0.032,5.0e-3,0.,tclev,thlev,tdlev);
    goto label_3500;
  label_6362  :
    decay0_nucltransK(prng_, event_, 0.491,0.032,3.2e-2,0.,tclev,thlev,tdlev);
    goto label_1450;
  label_6363  :
    decay0_nucltransK(prng_, event_, 0.315,0.032,8.3e-3,0.,tclev,thlev,tdlev);
    goto label_3210;
  label_6364  :
    decay0_nucltransK(prng_, event_, 0.173,0.032,1.5e-1,0.,tclev,thlev,tdlev);
    goto label_4630;
  label_6365  :
    decay0_nucltransK(prng_, event_, 0.111,0.032,1.5e-1,0.,tclev,thlev,tdlev);
    goto label_5250;
  label_5390  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 26.42) goto label_5391;
    goto label_5392;
  label_5391  :
    decay0_nucltransK(prng_, event_, 0.539,0.032,7.8e-3,0.,tclev,thlev,tdlev);
    return;
  label_5392  :
    decay0_nucltransK(prng_, event_, 0.503,0.032,9.3e-3,0.,tclev,thlev,tdlev);
    goto label_3500;
  label_525  :
    decay0_beta(prng_, event_, 0.242,52.,0.,0.,t);
  label_5250  :
    thlev=160e-12;
    p=100.*prng_();
    if (p <=  0.07) goto label_5251;
    if (p <= 81.12) goto label_5252;
    if (p <= 99.89) goto label_5253;
    goto label_5254;
  label_5251  :
    decay0_nucltransK(prng_, event_, 0.490,0.032,3.3e-2,0.,tclev,thlev,tdlev);
    goto label_3500;
  label_5252  :
    decay0_nucltransK(prng_, event_, 0.380,0.032,1.8e-2,0.,tclev,thlev,tdlev);
    goto label_1450;
  label_5253  :
    decay0_nucltransK(prng_, event_, 0.204,0.032,1.3e-1,0.,tclev,thlev,tdlev);
    goto label_3210;
  label_5254  :
    decay0_nucltransK(prng_, event_, 0.062,0.032,7.4e-1,0.,tclev,thlev,tdlev);
    goto label_4630;
  label_463  :
    decay0_beta(prng_, event_, 0.304,52.,0.,0.,t);
  label_4630  :
    thlev=13.2e-12;
    p=100.*prng_();
    if (p <= 26.08) goto label_4631;
    if (p <= 99.39) goto label_4632;
    goto label_4633;
  label_4631  :
    decay0_nucltransK(prng_, event_, 0.463,0.032,1.0e-2,0.,tclev,thlev,tdlev);
    return;
  label_4632  :
    decay0_nucltransK(prng_, event_, 0.428,0.032,1.4e-2,0.,tclev,thlev,tdlev);
    goto label_3500;
  label_4633  :
    decay0_nucltransK(prng_, event_, 0.020,0.005,11.1,0.,tclev,thlev,tdlev);
    goto label_4440;
  label_444  :
    decay0_beta(prng_, event_, 0.323,52.,0.,0.,t);
  label_4440  :
    thlev=19.1e-12;
    p=100.*prng_();
    if (p <= 62.40) goto label_4441;
    goto label_4442;
  label_4441  :
    decay0_nucltransK(prng_, event_, 0.444,0.032,1.2e-2,0.,tclev,thlev,tdlev);
    return;
  label_4442  :
    decay0_nucltransK(prng_, event_, 0.408,0.032,1.5e-2,0.,tclev,thlev,tdlev);
    goto label_3500;
  label_402  :
    decay0_beta(prng_, event_, 0.365,52.,0.,0.,t);
    ////    label_4020  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 29.72) goto label_4021;
    if (p <= 67.45) goto label_4022;
    goto label_4023;
  label_4021  :
    decay0_nucltransK(prng_, event_, 0.402,0.032,1.9e-1,0.,tclev,thlev,tdlev);
    return;
  label_4022  :
    decay0_nucltransK(prng_, event_, 0.367,0.032,2.0e-2,0.,tclev,thlev,tdlev);
    goto label_3500;
  label_4023  :
    decay0_nucltransK(prng_, event_, 0.081,0.032,3.6e-1,0.,tclev,thlev,tdlev);
    goto label_3210;
  label_321  :
    decay0_beta(prng_, event_, 0.446,52.,0.,0.,t);
  label_3210  :
    thlev=0.673e-9;
    decay0_nucltransK(prng_, event_, 0.176,0.032,1.7e-1,0.,tclev,thlev,tdlev);
    goto label_1450;
  label_145  :
    decay0_beta(prng_, event_, 0.622,52.,0.,0.,t);
  label_1450  :
    thlev=4.959e6;
    decay0_nucltransK(prng_, event_, 0.109,0.032,355.,0.,tclev,thlev,tdlev);
    goto label_3500;
  label_3500  :
    thlev=1.48e-9;
    decay0_nucltransK(prng_, event_, 0.035,0.032,14.,0.,tclev,thlev,tdlev);
    return;
  }
  // end of Sb125.f




} // end of namespace bxdecay0

// end of Sb125.cc
// Local Variables: --
// mode: c++ --
// End: --
