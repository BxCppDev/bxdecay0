// Ourselves:
#include <bxdecay0/Ge74low.h>

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

  // Ge74low.f 
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

  void Ge74low(i_random & prng_,
               event & event_,
               const int levelkev_)
  {
    //double t;
    double tdlev;
    double p;
    double tclev;
    double thlev;
    // Subroutine describes the deexcitation process in Ge74 nucleus
    // after 2b-decay of Se74 to ground and excited 0+ and 2+ levels
    // of Ge74 ("Table of Isotopes", 7th ed., 1978).
    // Call : call Ge74low(levelkev_)
    // Input : levelkev_ - energy of Ge74 level (integer in keV) occupied
    // initially
    // 0+(gs) - 0 keV,
    // 2+(1) - 596 keV,
    // 2+(2) - 1204 keV.
    // Output: // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 30.11.1995.
    tclev=0.;
    if (levelkev_ == 1204) goto label_1204;
    if (levelkev_ ==  596) goto label_596;
    if (levelkev_ ==  0) goto label_10000;
    goto label_20000;
  label_1204  :
    thlev=6.0e-12;
    p=100.*prng_();
    if (p <= 34.) goto label_12041;
    goto label_12042;
  label_12041  :
    decay0_nucltransK(prng_, event_, 1.204,0.011,1.9e-4,0.1e-4,tclev,thlev,tdlev);
    return;
  label_12042  :
    decay0_nucltransK(prng_, event_, 0.608,0.011,1.1e-3,0.,tclev,thlev,tdlev);
    goto label_596;
  label_596  :
    thlev=12.0e-12;
    decay0_nucltransK(prng_, event_, 0.596,0.011,1.1e-3,0.,tclev,thlev,tdlev);
    return;
  label_10000  :
    return;
  label_20000  :
    // print *,'Ge74: wrong level [keV] ',levelkev_
    return;
  }
  // end of Ge74low.f




} // end of namespace bxdecay0

// end of Ge74low.cc
// Local Variables: --
// mode: c++ --
// End: --
