// Ourselves:
#include <bxdecay0/Ra222low.h>

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

  // Ra222low.f
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

  void Ra222low(i_random & /* prng_ */,
                event & /* event_ */,
                const int levelkev_)
  {
    //double t;
    //double tdlev;
    //// double tclev;
    // Subroutine describes the deexcitation process in Rn218 nucleus
    // after 2b-decay of Po218 to ground and excited 0+ and 2+ levels
    // of Rn218.
    // Call : call Ra222low(levelkev_)
    // Input : levelkev_ - energy of Ra222 level (integer in keV) occupied
    // initially
    // 0+(gs) - 0 keV.
    // Output: // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 10.12.2007.
    //// tclev=0.;
    if (levelkev_ ==  0) goto label_10000;
    goto label_20000;
  label_10000  :
    return;
  label_20000  :
    // print *,'Ra222: wrong level [keV] ',levelkev_
    return;
  }
  // end of Ra222low.f




} // end of namespace bxdecay0

// end of Ra222low.cc
// Local Variables: --
// mode: c++ --
// End: --
