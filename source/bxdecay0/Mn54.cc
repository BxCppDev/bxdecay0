// Ourselves:
#include <bxdecay0/Mn54.h>

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

  // Mn54.f 
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

  void Mn54(i_random & prng_,
            event & event_,
            const double tcnuc_,
            double & tdnuc_)
  {
    double t;
    double tdlev;
    double tclev;
    double thlev;
    double thnuc;
    // Scheme of Mn54 decay ("Table of Isotopes", 8th ed., 1996 + NDS 50(1987)255).
    // Accuracy in description of: decay branches - 0.001%,
    // : deexcitation process - 0.001%.
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 16.04.1998.
    // VIT, 1.04.2007, updated to NDS 107(2006)1393.
    thnuc=2.696717E+07;
    tdnuc_=tcnuc_-thnuc/std::log(2.)*std::log(prng_());
    tclev=0.;
    // 100% EC to Cr54
    decay0_gamma(prng_, event_, 0.006,0.,0.,t);
    thlev=7.9e-12;
    decay0_nucltransK(prng_, event_, 0.835,0.006,2.4e-4,0.,tclev,thlev,tdlev);
    return;
  }
  // end of Mn54.f




} // end of namespace bxdecay0

// end of Mn54.cc
// Local Variables: --
// mode: c++ --
// End: --
