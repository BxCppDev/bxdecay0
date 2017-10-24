// Ourselves:
#include <bxdecay0/Fe58low.h>

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

  // Fe58low.f 
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

  void Fe58low(i_random & prng_,
               event & event_,
               const int levelkev_)
  {
    //double t;
    double tdlev;
    double p;
    double tclev;
    double thlev;
    // Subroutine describes the deexcitation process in Fe58 nucleus
    // after 2b-decay of Ni58 to ground and excited 0+ and 2+ levels
    // of Fe58 ("Table of Isotopes", 7th ed., 1978).
    // Call : call Fe58low(levelkev_)
    // Input : levelkev_ - energy of Fe58 level (integer in keV) occupied
    // initially
    // 0+(gs) - 0 keV,
    // 2+(1) - 811 keV,
    // 2+(2) - 1675 keV.
    // Output: // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 30.11.1995.
    tclev=0.;
    if (levelkev_ == 1675) goto label_1675;
    if (levelkev_ ==  811) goto label_811;
    if (levelkev_ ==  0) goto label_10000;
    goto label_20000;
  label_1675  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 43.) goto label_16751;
    goto label_16752;
  label_16751  :
    decay0_nucltransK(prng_, event_, 1.675,0.007,1.0e-4,0.6e-4,tclev,thlev,tdlev);
    return;
  label_16752  :
    decay0_nucltransK(prng_, event_, 0.864,0.007,3.0e-4,0.,tclev,thlev,tdlev);
    goto label_811;
  label_811  :
    thlev=9.0e-12;
    decay0_nucltransK(prng_, event_, 0.811,0.007,5.0e-4,0.,tclev,thlev,tdlev);
    return;
  label_10000  :
    return;
  label_20000  :
    // print *,'Fe58: wrong level [keV] ',levelkev_
    return;
  }
  // end of Fe58low.f




} // end of namespace bxdecay0

// end of Fe58low.cc
// Local Variables: --
// mode: c++ --
// End: --
