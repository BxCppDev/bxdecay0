// Ourselves:
#include <bxdecay0/Rb87.h>

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

  // Rb87.f 
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

  void Rb87(i_random & prng_,
            event & event_,
            const double tcnuc_,
            double & tdnuc_)
  {
    double t;
    //double tdlev;
    double thnuc;
    // Scheme of Rb87 decay in accordance with NDS 95(2002)543 and ENSDF
    // at NNDC site on 6.08.2007.
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 6.08.2007.
    thnuc=1.518e18;
    tdnuc_=tcnuc_-thnuc/std::log(2.)*std::log(prng_());
    // Shape of the 3-rd forbidden non-unique beta decay in accordance with
    // measurements of: A.G.Carles et al., NPA 767(2006)248.
    decay0_beta2(prng_, event_, 0.283,38.,0.,0.,t,2,27.72,90.91,0.,0.);
    return;
  }
  // end of Rb87.f




} // end of namespace bxdecay0

// end of Rb87.cc
// Local Variables: --
// mode: c++ --
// End: --
