// Ourselves:
#include <bxdecay0/Sn116low.h>

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

  // Sn116low.f 
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

  void Sn116low(i_random & prng_,
                event & event_,
                const int levelkev_)
  {
    //double t;
    double tdlev;
    double p;
    double tclev;
    double thlev;
    // Subroutine describes the deexcitation process in Sn116 nucleus
    // after 2b-decay of Cd116 to ground and excited 0+ and 2+ levels
    // of Sn116 ("Table of Isotopes", 7th ed., 1978).
    // Call : call Sn116low(levelkev_)
    // Input : levelkev_ - energy of Sn116 level (integer in keV) occupied
    // initially
    // 0+(gs) - 0 keV,
    // 2+(1) - 1294 keV,
    // 0+(1) - 1757 keV,
    // 0+(2) - 2027 keV,
    // 2+(2) - 2112 keV,
    // 2+(3) - 2225 keV.
    // Output: // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 28.06.1993, 22.10.1995.
    tclev=0.;
    if (levelkev_ == 2225) goto label_2225;
    if (levelkev_ == 2112) goto label_2112;
    if (levelkev_ == 2027) goto label_2027;
    if (levelkev_ == 1757) goto label_1757;
    if (levelkev_ == 1294) goto label_1294;
    if (levelkev_ ==  0) goto label_10000;
    goto label_20000;
  label_2225  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 37.) goto label_22251;
    goto label_22252;
  label_22251  :
    decay0_nucltransK(prng_, event_, 2.225,0.029,2.7e-4,3.4e-4,tclev,thlev,tdlev);
    return;
  label_22252  :
    decay0_nucltransK(prng_, event_, 0.932,0.029,1.5e-3,0.,tclev,thlev,tdlev);
    goto label_1294;
  label_2112  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 54.9) goto label_21121;
    if (p <= 96.9) goto label_21122;
    goto label_21123;
  label_21121  :
    decay0_nucltransK(prng_, event_, 2.112,0.029,3.1e-4,2.7e-4,tclev,thlev,tdlev);
    return;
  label_21122  :
    decay0_nucltransK(prng_, event_, 0.819,0.029,2.6e-3,0.,tclev,thlev,tdlev);
    goto label_1294;
  label_21123  :
    decay0_nucltransK(prng_, event_, 0.355,0.029,1.8e-2,0.,tclev,thlev,tdlev);
    goto label_1757;
  label_2027  :
    thlev=0.;
    decay0_nucltransK(prng_, event_, 0.733,0.029,2.7e-3,0.,tclev,thlev,tdlev);
    goto label_1294;
  label_1757  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 0.29) goto label_17571;
    goto label_17572;
  label_17571  :
    decay0_electron(prng_, event_, 1.757-0.029,tclev,thlev,tdlev)  ;// only ec
    decay0_gamma(prng_, event_, 0.029,0.,0.,tdlev);
    return;
  label_17572  :
    decay0_nucltransK(prng_, event_, 0.463,0.029,9.0e-3,0.,tclev,thlev,tdlev);
    goto label_1294;
  label_1294  :
    thlev=0.36e-12;
    decay0_nucltransK(prng_, event_, 1.294,0.029,7.5e-4,0.5e-4,tclev,thlev,tdlev);
    return;
  label_10000  :
    return;
  label_20000  :
    // print *,'Sn116: wrong level [keV] ',levelkev_
    return;
  }
  // end of Sn116low.f




} // end of namespace bxdecay0

// end of Sn116low.cc
// Local Variables: --
// mode: c++ --
// End: --
