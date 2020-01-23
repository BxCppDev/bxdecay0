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
#include <bxdecay0/Pb211.h>

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

  void Pb211(i_random & prng_,
             event & event_,
             const double tcnuc_,
             double & tdnuc_)
  {
    double t;
    double tdlev;
    double p;
    double pbeta;
    double tclev;
    double thlev = 0.0;
    double thnuc;
    // Scheme of Pb211 decay ("Table of Isotopes", 7th ed., 1978).
    // Three- and four-figured labels correspond to energies of Bi211
    // excited levels in keV.
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 14.08.1992, 22.10.1995
    // VIT, 31.10.2006 (updated to NDS 103(2004)183).
    // Main beta decays are 1st forbidden (dJ^(dPi)=0^-,1^-)
    // is supposen.
    thnuc=2166.;
    tdnuc_=tcnuc_-thnuc/std::log(2.)*std::log(prng_());
    tclev=0.;
    pbeta=100.*prng_();
    if (pbeta <= 0.0186) goto label_1271;  // 0.0186%
    if (pbeta <= 0.0199) goto label_1234;  // 0.0013%
    if (pbeta <= 0.0369) goto label_1196;  // 0.0170%
    if (pbeta <= 0.8660) goto label_1109;  // 0.8291%
    if (pbeta <= 0.8706) goto label_1104;  // 0.0046%
    if (pbeta <= 0.9265) goto label_1081;  // 0.0559%
    if (pbeta <= 0.9485) goto label_951;  // 0.0220%
    if (pbeta <= 7.2616) goto label_832;  // 6.3131%
    if (pbeta <= 8.7999) goto label_405;  // 1.5383%
    goto label_10000;  // 91.2001%
  label_1271  :
    decay0_beta(prng_, event_, 0.096,83.,0.,0.,t);
    ////    label_12710  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 36.76) goto label_12711;  // 36.76%
    if (p <= 68.65) goto label_12712;  // 31.89%
    goto label_12713;  // 31.35%
  label_12711  :
    decay0_nucltransK(prng_, event_, 1.271,0.091,1.0e-2,0.2e-4,tclev,thlev,tdlev);
    return;
  label_12712  :
    decay0_nucltransK(prng_, event_, 0.866,0.091,2.8e-2,0.,tclev,thlev,tdlev);
    goto label_40500;
  label_12713  :
    decay0_nucltransK(prng_, event_, 0.504,0.091,1.1e-1,0.,tclev,thlev,tdlev);
    goto label_76700;
  label_1234  :
    decay0_beta(prng_, event_, 0.133,83.,0.,0.,t);
    decay0_nucltransK(prng_, event_, 1.234,0.091,1.1e-2,0.1e-4,tclev,thlev,tdlev);
    return;
  label_1196  :
    decay0_beta(prng_, event_, 0.171,83.,0.,0.,t);
    ////label_11960  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 62.96) goto label_11961;  // 62.96%
    goto label_11962;  // 37.04%
  label_11961  :
    decay0_nucltransK(prng_, event_, 1.196,0.091,1.2e-2,0.1e-4,tclev,thlev,tdlev);
    return;
  label_11962  :
    decay0_nucltransK(prng_, event_, 0.430,0.091,1.8e-1,0.,tclev,thlev,tdlev);
    goto label_76700;
  label_1109  :
    decay0_beta(prng_, event_, 0.258,83.,0.,0.,t);
    ////    label_11090  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 13.9) goto label_11091;  // 13.9%
    if (p <= 72.8) goto label_11092;  // 58.9%
    if (p <= 77.0) goto label_11093;  // 4.2%
    goto label_11094;  // 23.0%
  label_11091  :
    decay0_nucltransK(prng_, event_, 1.109,0.091,1.5e-2,0.4e-6,tclev,thlev,tdlev);
    return;
  label_11092  :
    decay0_nucltransK(prng_, event_, 0.705,0.091,5.0e-2,0.,tclev,thlev,tdlev);
    goto label_40500;
  label_11093  :
    decay0_nucltransK(prng_, event_, 0.343,0.091,3.2e-1,0.,tclev,thlev,tdlev);
    goto label_76700;
  label_11094  :
    decay0_nucltransK(prng_, event_, 0.095,0.016,9.6e+0,0.,tclev,thlev,tdlev);
    goto label_10140;
  label_1104  :
    decay0_beta(prng_, event_, 0.263,83.,0.,0.,t);
    ////    label_11040  :
    decay0_nucltransK(prng_, event_, 1.104,0.091,1.5e-2,0.3e-6,tclev,thlev,tdlev);
    return;
  label_1081  :
    decay0_beta(prng_, event_, 0.286,83.,0.,0.,t);
    ////    label_10810  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 21.8) goto label_10811;  // 21.8%
    if (p <= 44.9) goto label_10812;  // 23.1%
    goto label_10813;  // 55.1%
  label_10811  :
    decay0_nucltransK(prng_, event_, 1.081,0.091,1.6e-2,0.1e-4,tclev,thlev,tdlev);
    return;
  label_10812  :
    decay0_nucltransK(prng_, event_, 0.677,0.091,5.3e-2,0.,tclev,thlev,tdlev);
    goto label_40500;
  label_10813  :
    decay0_nucltransK(prng_, event_, 0.314,0.091,4.1e-1,0.,tclev,thlev,tdlev);
    goto label_76700;
  label_10140  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 28.7) goto label_10141;  // 28.7%
    goto label_10142;  // 71.3%
  label_10141  :
    decay0_nucltransK(prng_, event_, 1.014,0.091,1.9e-2,0.,tclev,thlev,tdlev);
    return;
  label_10142  :
    decay0_nucltransK(prng_, event_, 0.609,0.091,7.0e-2,0.,tclev,thlev,tdlev);
    goto label_40500;
  label_951  :
    decay0_beta(prng_, event_, 0.416,83.,0.,0.,t);
    ////    label_95100  :
    thlev=0.;
    decay0_nucltransK(prng_, event_, 0.951,0.091,2.2e-2,0.,tclev,thlev,tdlev);
    return;
  label_832  :
    decay0_beta(prng_, event_, 0.535,83.,0.,0.,t);
    ////    label_83200  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 57.4) goto label_83201;  // 57.4%
    if (p <= 90.3) goto label_83202;  // 32.9%
    goto label_83203;  // 9.7%
  label_83201  :
    decay0_nucltransK(prng_, event_, 0.832,0.091,2.9e-2,0.,tclev,thlev,tdlev);
    return;
  label_83202  :
    decay0_nucltransK(prng_, event_, 0.427,0.091,1.9e-1,0.,tclev,thlev,tdlev);
    goto label_40500;
  label_83203  :
    decay0_nucltransK(prng_, event_, 0.065,0.016,6.9e+0,0.,tclev,thlev,tdlev);
    goto label_76700;
  label_76700  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 57.4) goto label_76701;  // 93.7%
    goto label_76702;  // 6.3%
  label_76701  :
    decay0_nucltransK(prng_, event_, 0.767,0.091,4.0e-2,0.,tclev,thlev,tdlev);
    return;
  label_76702  :
    decay0_nucltransK(prng_, event_, 0.362,0.091,2.8e-1,0.,tclev,thlev,tdlev);
    goto label_40500;
  label_405  :
    decay0_beta(prng_, event_, 0.962,83.,0.,0.,t);
  label_40500  :
    thlev=0.317e-9;
    decay0_nucltransK(prng_, event_, 0.405,0.091,1.3e-1,0.,tclev,thlev,tdlev);
    return;
  label_10000  :
    decay0_beta(prng_, event_, 1.367,83.,0.,0.,t);
    return;
  }
  // end of Pb211.f




} // end of namespace bxdecay0

// end of Pb211.cc
// Local Variables: --
// mode: c++ --
// End: --
