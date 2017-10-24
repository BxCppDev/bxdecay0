// Ourselves:
#include <bxdecay0/Pd106low.h>

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

  // Pd106low.f
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

  void Pd106low(i_random & prng_,
                event & event_,
                const int levelkev_)
  {
    //double t;
    double tdlev;
    double p;
    double tclev;
    double thlev;
    // Subroutine describes the deexcitation process in Pd106 nucleus
    // after 2b-decay of Cd106 to ground and excited 0+ and 2+ levels
    // of Pd106 ("Table of Isotopes", 7th ed., 1978).
    // Call : call Pd106low(levelkev_)
    // Input : levelkev_ - energy of Pd106 level (integer in keV) occupied
    // initially
    // 0+(gs) - 0 keV,
    // 2+(1) - 512 keV,
    // 2+(2) - 1128 keV,
    // 0+(1) - 1134 keV,
    // 2+(3) - 1562 keV,
    // 0+(2) - 1706 keV.
    // Output: // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 30.11.1995; 3.04.2006
    tclev=0.;
    // if (levelkev_ == 2741) goto label_2741
    if (levelkev_ == 1706) goto label_1706;
    if (levelkev_ == 1562) goto label_1562;
    if (levelkev_ == 1134) goto label_1134;
    if (levelkev_ == 1128) goto label_1128;
    if (levelkev_ ==  512) goto label_512;
    if (levelkev_ ==  0) goto label_10000;
    goto label_20000;
    ////    label_2741  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 66.2) goto label_27411;
    goto label_27412;
  label_27411  :
    decay0_nucltransK(prng_, event_, 2.741,0.024,1.4e-4,6.6e-4,tclev,thlev,tdlev);
    return;
  label_27412  :
    decay0_nucltransK(prng_, event_, 2.230,0.024,2.1e-4,3.9e-4,tclev,thlev,tdlev);
    goto label_512;
  label_1706  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 87.2) goto label_17061;
    goto label_17062;
  label_17061  :
    decay0_nucltransK(prng_, event_, 1.195,0.024,6.9e-4,6.7e-6,tclev,thlev,tdlev);
    goto label_512;
  label_17062  :
    decay0_nucltransK(prng_, event_, 0.578,0.024,4.0e-3,0.,tclev,thlev,tdlev);
    goto label_1128;
  label_1562  :
    thlev=0.;
    p=100.*prng_();
    if (p <=  9.0) goto label_15621;
    if (p <= 95.0) goto label_15622;
    if (p <= 96.1) goto label_15623;
    goto label_15624;
  label_15621  :
    decay0_nucltransK(prng_, event_, 1.562,0.024,3.9e-4,1.1e-4,tclev,thlev,tdlev);
    return;
  label_15622  :
    decay0_nucltransK(prng_, event_, 1.050,0.024,1.0e-3,0.,tclev,thlev,tdlev);
    goto label_512;
  label_15623  :
    decay0_nucltransK(prng_, event_, 0.434,0.024,7.7e-3,0.,tclev,thlev,tdlev);
    goto label_1128;
  label_15624  :
    decay0_nucltransK(prng_, event_, 0.428,0.024,9.5e-3,0.,tclev,thlev,tdlev);
    goto label_1134;
  label_1134  :
    thlev=6.8e-12;
    p=100.*prng_();
    if (p <= 5.7e-2) goto label_11341;
    goto label_11342;
  label_11341  :
    decay0_electron(prng_, event_, 1.110,tclev,thlev,tdlev)  ;// E0 transition
    decay0_gamma(prng_, event_, 0.024,0.,0.,tdlev);
    return;
  label_11342  :
    decay0_nucltransK(prng_, event_, 0.622,0.024,3.2e-3,0.,tclev,thlev,tdlev);
    goto label_512;
  label_1128  :
    thlev=3.12e-12;
    p=100.*prng_();
    if (p <= 35.0) goto label_11281;
    goto label_11282;
  label_11281  :
    decay0_nucltransK(prng_, event_, 1.128,0.024,7.7e-4,0.,tclev,thlev,tdlev);
    return;
  label_11282  :
    decay0_nucltransK(prng_, event_, 0.616,0.024,3.4e-3,0.,tclev,thlev,tdlev);
    goto label_512;
  label_512  :
    thlev=12.1e-12;
    decay0_nucltransK(prng_, event_, 0.512,0.024,5.6e-3,0.,tclev,thlev,tdlev);
    return;
  label_10000  :
    return;
  label_20000  :
    // print *,'Pd106: wrong level [keV] ',levelkev_
    return;
  }
  // end of Pd106low.f




} // end of namespace bxdecay0

// end of Pd106low.cc
// Local Variables: --
// mode: c++ --
// End: --
