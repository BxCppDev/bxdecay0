// Ourselves:
#include <bxdecay0/Rn218.h>

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

  // Rn218.f 
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

  void Rn218(i_random & prng_,
             event & event_,
             const double tcnuc_,
             double & tdnuc_)
  {
    double t;
    double tdlev;
    double palpha;
    double tclev;
    double thlev;
    double thnuc;
    // Model for scheme of Rn218 decay (NDS 76(1995)127 and ENSDF at NNDC site
    // on 9.12.2007).
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 9.12.2007.
    thnuc=35.e-3;
    tdnuc_=tcnuc_-thnuc/std::log(2.)*std::log(prng_());
    tclev=0.;
    palpha=100.*prng_();
    if (palpha <= 0.127) goto label_609;
    goto label_10000;
  label_609  :
    decay0_alpha(prng_, event_, 6.532,0.,0.,t);
    thlev=0.;
    decay0_nucltransK(prng_, event_, 0.609,0.093,2.1e-2,0.,tclev,thlev,tdlev);
    return;
  label_10000  :
    decay0_alpha(prng_, event_, 7.130,0.,0.,t);
    return;
  }
  // end of Rn218.f




} // end of namespace bxdecay0

// end of Rn218.cc
// Local Variables: --
// mode: c++ --
// End: --
