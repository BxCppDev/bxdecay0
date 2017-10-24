// Ourselves:
#include <bxdecay0/Bi212.h>

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

  // Bi212.f
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

  void Bi212(i_random & prng_,
	     event & event_,
	     const double tcnuc_,
	     double & tdnuc_)
  {
    double t;
    double tdlev;
    double p;
    double palfa;
    double pbeta;
    double pdecay;
    double tclev;
    double thlev;
    double thnuc;
    // Scheme of Bi212 decay ("Table of Isotopes", 7th ed., 1978).
    // Two-, three- and four-figured labels correspond to energies of
    // 208Tl or 212Po excited levels in keV. Beta-alfa decays to 208Pb
    // are not considered (p=0.014%).
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 4.08.1992, 22.10.1995.
    thnuc=3636.;
    tdnuc_=tcnuc_-thnuc/std::log(2.)*std::log(prng_());
    tclev=0.;
    pdecay=prng_();
    if (pdecay <= 0.36) goto label_10000;  // 36% alfa to 208Tl
    goto label_20000;  // 64% beta to 212Po
  label_10000  :
    palfa=100.*prng_();
    if (palfa <=  1.10) goto label_493;  // 1.10%
    if (palfa <=  1.25) goto label_473;  // 0.15%
    if (palfa <=  2.92) goto label_328;  // 1.67%
    if (palfa <= 72.80) goto label_40;  // 69.88%
    goto label_10001;  // 27.20%
  label_493  :
    decay0_alpha(prng_, event_, 5.607,0.,0.,t);
    thlev=0.;
    p=100.*prng_();
    if (p <=  5.) goto label_49301;  // 5%
    if (p <= 99.) goto label_49302;  // 94%
    goto label_49303;  // 1%
  label_49301  :
    decay0_nucltransK(prng_, event_, 0.493,0.086,2.8e-2,0.,tclev,thlev,tdlev);
    return;
  label_49302  :
    decay0_nucltransK(prng_, event_, 0.453,0.086,0.18,0.,tclev,thlev,tdlev);
    goto label_40000;
  label_49303  :
    decay0_nucltransK(prng_, event_, 0.164,0.086,0.75,0.,tclev,thlev,tdlev);
    goto label_32800;
  label_473  :
    decay0_alpha(prng_, event_, 5.626,0.,0.,t);
    thlev=0.;
    p=100.*prng_();
    if (p <= 68.) goto label_47301;  // 68%
    if (p <= 87.) goto label_47302;  // 19%
    goto label_47303;  // 13%
  label_47301  :
    decay0_nucltransK(prng_, event_, 0.474,0.086,0.14,0.,tclev,thlev,tdlev);
    return;
  label_47302  :
    decay0_nucltransK(prng_, event_, 0.434,0.086,0.14,0.,tclev,thlev,tdlev);
    goto label_40000;
  label_47303  :
    decay0_nucltransK(prng_, event_, 0.145,0.086,2.8,0.,tclev,thlev,tdlev);
    goto label_32800;
  label_328  :
    decay0_alpha(prng_, event_, 5.769,0.,0.,t);
  label_32800  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 29.) goto label_32801;  // 29%
    goto label_32802;  // 71%
  label_32801  :
    decay0_nucltransK(prng_, event_, 0.328,0.086,0.33,0.,tclev,thlev,tdlev);
    return;
  label_32802  :
    decay0_nucltransK(prng_, event_, 0.288,0.086,0.53,0.,tclev,thlev,tdlev);
    goto label_40000;
  label_40  :
    decay0_alpha(prng_, event_, 6.051,0.,0.,t);
  label_40000  :
    thlev=6.e-12;
    decay0_nucltransK(prng_, event_, 0.040,0.015,22.55,0.,tclev,thlev,tdlev);
    return;
  label_10001  :
    decay0_alpha(prng_, event_, 6.090,0.,0.,t);
    return;
  label_20000  :
    pbeta=64.*prng_();
    if (pbeta <=  0.660) goto label_1806;  // 0.660%
    if (pbeta <=  0.687) goto label_1801;  // 0.027%
    if (pbeta <=  0.937) goto label_1680;  // 0.250%
    if (pbeta <=  2.837) goto label_1621;  // 1.900%
    if (pbeta <=  4.337) goto label_1513;  // 1.500%
    if (pbeta <=  8.737) goto label_727;  // 4.400%
    goto label_20001;  // 55.263%
  label_1806  :
    decay0_beta(prng_, event_, 0.440,84.,0.,0.,t);
    thlev=0.;
    p=100.*prng_();
    if (p <= 17.) goto label_18061;  // 17%
    goto label_18062;  // 83%
  label_18061  :
    decay0_nucltransK(prng_, event_, 1.806,0.093,2.6e-2,1.7e-4,tclev,thlev,tdlev);
    return;
  label_18062  :
    decay0_nucltransK(prng_, event_, 1.079,0.093,2.0e-2,0.,tclev,thlev,tdlev);
    goto label_72700;
  label_1801  :
    decay0_beta(prng_, event_, 0.445,84.,0.,0.,t);
    thlev=0.;
    p=100.*prng_();
    if (p <= 35.) goto label_18011;  // 35%
    goto label_18012;  // 65%
  label_18011  :
    decay0_electron(prng_, event_, 1.708,tclev,thlev,tdlev)  ;// only ec
    decay0_gamma(prng_, event_, 0.093,0.,0.,tdlev);
    return;
  label_18012  :
    decay0_nucltransK(prng_, event_, 1.074,0.093,7.0e-3,0.,tclev,thlev,tdlev);
    goto label_72700;
  label_1680  :
    decay0_beta(prng_, event_, 0.566,84.,0.,0.,t);
    thlev=0.;
    p=100.*prng_();
    if (p <= 28.) goto label_16801;  // 28%
    goto label_16802;  // 72%
  label_16801  :
    decay0_nucltransK(prng_, event_, 1.680,0.093,2.8e-3,1.0e-4,tclev,thlev,tdlev);
    return;
  label_16802  :
    decay0_nucltransK(prng_, event_, 0.952,0.093,4.5e-2,0.,tclev,thlev,tdlev);
    goto label_72700;
  label_1621  :
    decay0_beta(prng_, event_, 0.625,84.,0.,0.,t);
    thlev=0.;
    p=100.*prng_();
    if (p <= 80.) goto label_16211;  // 80%
    goto label_16212;  // 20%
  label_16211  :
    decay0_nucltransK(prng_, event_, 1.621,0.093,7.0e-3,1.2e-4,tclev,thlev,tdlev);
    return;
  label_16212  :
    decay0_nucltransK(prng_, event_, 0.893,0.093,4.5e-2,0.,tclev,thlev,tdlev);
    goto label_72700;
  label_1513  :
    decay0_beta(prng_, event_, 0.733,84.,0.,0.,t);
    thlev=0.;
    p=100.*prng_();
    if (p <= 22.) goto label_15131;  // 22%
    goto label_15132;  // 78%
  label_15131  :
    decay0_nucltransK(prng_, event_, 1.513,0.093,3.5e-3,0.7e-4,tclev,thlev,tdlev);
    return;
  label_15132  :
    decay0_nucltransK(prng_, event_, 0.786,0.093,4.1e-2,0.,tclev,thlev,tdlev);
    goto label_72700;
  label_727  :
    decay0_beta(prng_, event_, 1.519,84.,0.,0.,t);
  label_72700  :
    thlev=0.;
    decay0_nucltransK(prng_, event_, 0.727,0.093,1.7e-2,0.,tclev,thlev,tdlev);
    return;
  label_20001  :
    decay0_beta(prng_, event_, 2.246,84.,0.,0.,t);
    return;
  }
  // end of Bi212.f

} // end of namespace bxdecay0

// end of Bi212.cc
// Local Variables: --
// mode: c++ --
// End: --
