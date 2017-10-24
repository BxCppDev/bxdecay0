// Ourselves:
#include <bxdecay0/C14.h>

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

  // C14.f 
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

  void C14(i_random & prng_,
	   event & event_,
	   const double tcnuc_,
	   double & tdnuc_)
  {
    double t;
    //double tdlev;
    double thnuc;
    // Scheme of C14 beta decay, NPA 523(1991)1 and ToI'1998.
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 5.11.2006.
    thnuc=1.798734e11;
    tdnuc_=tcnuc_-thnuc/std::log(2.)*std::log(prng_());
    // std::experimental corrections to the allowed beta shape from
    // F.E.Wietfeldt et al., PRC 52(1995)1028
    // cf(e)=(1+c1/w+c2*w+c3*w**2+c4*w**3), w=e/emass+1
    decay0_beta1(prng_, event_, 0.156,7.,0.,0.,t,0.,0.19418,0.,0.);
    return;
  }
  // end of C14.f




} // end of namespace bxdecay0 

// end of C14.cc
// Local Variables: --
// mode: c++ --
// End: --
