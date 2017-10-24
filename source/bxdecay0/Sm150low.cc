// Ourselves:
#include <bxdecay0/Sm150low.h>

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

  // Sm150low.f 
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

  void Sm150low(i_random & prng_,
                event & event_,
                const int levelkev_)
  {
    //double t;
    double tdlev;
    double p;
    double tclev;
    double thlev;
    // Subroutine describes the deexcitation process in Sm150 nucleus
    // after 2b-decay of Nd150 to ground and excited 0+ and 2+ levels
    // of Sm150 ("Table of Isotopes", 7th ed., 1978).
    // Call : call Sm150low(levelkev_)
    // Input : levelkev_ - energy of Sm150 level (integer in keV) occupied
    // initially
    // 0+(gs) - 0 keV,
    // 2+(1) - 334 keV,
    // 0+(1) - 740 keV,
    // 2+(2) - 1046 keV,
    // 2+(3) - 1194 keV,
    // 0+(2) - 1256 keV.
    // Output: // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 28.06.1993, 22.10.1995
    tclev=0.;
    if (levelkev_ == 1256) goto label_1256;
    if (levelkev_ == 1194) goto label_1194;
    if (levelkev_ == 1046) goto label_1046;
    if (levelkev_ ==  740) goto label_740;
    if (levelkev_ ==  334) goto label_334;
    if (levelkev_ ==  0) goto label_10000;
    goto label_20000;
  label_1256  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 93.) goto label_12561;
    goto label_12562;
  label_12561  :
    decay0_nucltransK(prng_, event_, 0.922,0.047,2.6e-3,0.,tclev,thlev,tdlev);
    goto label_334;
  label_12562  :
    decay0_nucltransK(prng_, event_, 0.210,0.047,1.7e-1,0.,tclev,thlev,tdlev);
    goto label_1046;
  label_1194  :
    thlev=1.3e-12;
    p=100.*prng_();
    if (p <= 55.9) goto label_11941;
    if (p <= 96.9) goto label_11942;
    if (p <= 98.7) goto label_11943;
    goto label_11944;
  label_11941  :
    decay0_nucltransK(prng_, event_, 1.194,0.047,1.6e-3,0.1e-4,tclev,thlev,tdlev);
    return;
  label_11942  :
    decay0_nucltransK(prng_, event_, 0.860,0.047,3.2e-3,0.,tclev,thlev,tdlev);
    goto label_334;
  label_11943  :
    decay0_nucltransK(prng_, event_, 0.453,0.047,1.5e-2,0.,tclev,thlev,tdlev);
    goto label_740;
  label_11944  :
    decay0_nucltransK(prng_, event_, 0.420,0.047,1.9e-2,0.,tclev,thlev,tdlev);
    goto label_773;
  label_1046  :
    thlev=0.7e-12;
    p=100.*prng_();
    if (p <=  7.0) goto label_10461;
    if (p <= 94.3) goto label_10462;
    if (p <= 97.0) goto label_10463;
    goto label_10464;
  label_10461  :
    decay0_nucltransK(prng_, event_, 1.046,0.047,2.0e-3,0.,tclev,thlev,tdlev);
    return;
  label_10462  :
    decay0_nucltransK(prng_, event_, 0.712,0.047,7.6e-3,0.,tclev,thlev,tdlev);
    goto label_334;
  label_10463  :
    decay0_nucltransK(prng_, event_, 0.306,0.047,4.9e-2,0.,tclev,thlev,tdlev);
    goto label_740;
  label_10464  :
    decay0_nucltransK(prng_, event_, 0.273,0.047,7.0e-2,0.,tclev,thlev,tdlev);
    goto label_773;
  label_773  :
    thlev=6.6e-12;
    decay0_nucltransK(prng_, event_, 0.439,0.047,1.7e-2,0.,tclev,thlev,tdlev);
    goto label_334;
  label_740  :
    thlev=20.e-12;
    p=100.*prng_();
    // the following line is corrected in accordance with ToI'1998 and Nucl.
    // Data Sheets 75(1995)827 (real page is 856)
    // VIT, 23.09.2008
    // if (p <= 92.) goto label_74001
    if (p <= 1.33) goto label_74001;
    goto label_74002;
  label_74001  :
    decay0_electron(prng_, event_, 0.740-0.047,tclev,thlev,tdlev)  ;// only ec
    decay0_gamma(prng_, event_, 0.047,0.,0.,tdlev);
    return;
  label_74002  :
    decay0_nucltransK(prng_, event_, 0.407,0.047,2.0e-2,0.,tclev,thlev,tdlev);
    goto label_334;
  label_334  :
    thlev=48.5e-12;
    decay0_nucltransK(prng_, event_, 0.334,0.047,3.7e-2,0.,tclev,thlev,tdlev);
    return;
  label_10000  :
    return;
  label_20000  :
    // print *,'Sm150: wrong level [keV] ',levelkev_
    return;
  }
  // end of Sm150low.f



} // end of namespace bxdecay0

// end of Sm150low.cc
// Local Variables: --
// mode: c++ --
// End: --
