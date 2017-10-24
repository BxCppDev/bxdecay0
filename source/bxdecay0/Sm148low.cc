// Ourselves:
#include <bxdecay0/Sm148low.h>

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

  // Sm148low.f 
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

  void Sm148low(i_random & prng_,
                event & event_,
                const int levelkev_)
  {
    //double t;
    double tdlev;
    double p;
    double tclev;
    double thlev;
    // Subroutine describes the deexcitation process in Sm148 nucleus
    // after 2b-decay of Nd148 to ground and excited 0+ and 2+ levels
    // of Sm148 ("Table of Isotopes", 7th ed., 1978).
    // Call : call Sm148low(levelkev_)
    // Input : levelkev_ - energy of Sm148 level (integer in keV) occupied
    // initially
    // 0+(gs) - 0 keV,
    // 2+(1) - 550 keV,
    // 2+(2) - 1455 keV.
    // Output: // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 30.11.1995.
    tclev=0.;
    if (levelkev_ == 1455) goto label_1455;
    if (levelkev_ ==  550) goto label_550;
    if (levelkev_ ==  0) goto label_10000;
    goto label_20000;
  label_1455  :
    thlev=0.6e-12;
    p=100.*prng_();
    if (p <= 42.) goto label_14551;
    goto label_14552;
  label_14551  :
    decay0_nucltransK(prng_, event_, 1.455,0.047,1.1e-3,0.3e-4,tclev,thlev,tdlev);
    return;
  label_14552  :
    decay0_nucltransK(prng_, event_, 0.904,0.047,2.8e-3,0.,tclev,thlev,tdlev);
    goto label_550;
  label_550  :
    thlev=7.3e-12;
    decay0_nucltransK(prng_, event_, 0.550,0.047,9.0e-3,0.,tclev,thlev,tdlev);
    return;
  label_10000  :
    return;
  label_20000  :
    // print *,'Sm148: wrong level [keV] ',levelkev_
    return;
  }
  // end of Sm148low.f




} // end of namespace bxdecay0

// end of Sm148low.cc
// Local Variables: --
// mode: c++ --
// End: --
