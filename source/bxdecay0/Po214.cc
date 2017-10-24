// Ourselves:
#include <bxdecay0/Po214.h>

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

  // Po214.f
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

  void Po214(i_random & prng_,
             event & event_,
             const double tcnuc_,
             double & tdnuc_)
  {
    double t;
    double tdlev;
    double palpha;
    double thnuc;
    double tclev(0.0);
    double thlev(0.0);
    // Scheme of Po214 decay (Nucl. Data Sheets 55(1988)665).
    // Alpha decay to excited level 1097.7 keV of Pb210 is neglected (6e-5%).
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 14.07.1995, 22.10.1995.
    // VIT, 11.05.2005, updated to NDS 99(2003)649.
    thnuc=164.3e-6;
    tdnuc_=tcnuc_-thnuc/std::log(2.)*std::log(prng_());
    palpha=100.*prng_();
    if (palpha <= 0.0104) goto label_800;  // 0.0104%
    goto label_10000;  // 99.9896%
  label_800  :
    decay0_alpha(prng_, event_, 6.902,0.,0.,t);
    decay0_nucltransK(prng_, event_, 0.800,0.088,1.1e-2,0.,tclev,thlev,tdlev);
    return;
  label_10000  :
    decay0_alpha(prng_, event_, 7.687,0.,0.,t);
    return;
  }
  // end of Po214.f




} // end of namespace bxdecay0

// end of Po214.cc
// Local Variables: --
// mode: c++ --
// End: --
