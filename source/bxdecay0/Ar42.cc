// Ourselves:
#include <bxdecay0/Ar42.h>

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

  // Ar42.f
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

  void Ar42(i_random & prng_,
            event & event_,
            const double tcnuc_,
            double & tdnuc_)
  {
    double t;
    //double tdlev;
    double thnuc;
    // Model for Ar42 decay (Nucl. Data Sheets 92(2001)1).
    // Input : tcnuc - time of creation of nucleus (sec)
    // Output: tdnuc - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 12.09.2005
    thnuc=1.0382166e9;
    tdnuc_=tcnuc_-thnuc/std::log(2.)*std::log(prng_());
    // decay0_beta(prng_, event_, 0.599,19.,0.,0.,t)
    // change to the 1st forbidden unique shape
    decay0_beta_1fu(prng_, event_, 0.599,19.,0.,0.,t,0.,0.,0.,0.);
    return;
  }
  // end of Ar42.f

} // end of namespace bxdecay0
