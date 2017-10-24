// Ourselves:
#include <bxdecay0/Cs137.h>

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

  // Cs137.f 
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

  void Cs137(i_random & prng_,
             event & event_,
             const double tcnuc_,
             double & tdnuc_)
  {
    double t;
    double tdlev;
    double pdecay;
    double tclev;
    double thlev;
    double thnuc;
    // Model for scheme of Cs137 decay (Nucl. Data Sheets 72(1994)355)
    // (really it is model for (Cs137 + Ba137m)-decay but not the model of
    // Cs137 decay alone).
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 31.08.1992, 11.07.1995, 06.11.1995
    // VIT, 30.10.2006 (update to NDS 81(1997)579 and corrections to the beta shapes).
    thnuc=0.9489110E+09;
    tdnuc_=tcnuc_-thnuc/std::log(2.)*std::log(prng_());
    tclev=0.;
    pdecay=100.*prng_();
    if (pdecay <= 94.4) goto label_1;
    goto label_2;
    // change to the 1st forbidden unique shape without std::experimental corrections
  label_1  :
    decay0_beta_1fu(prng_, event_, 0.514,56.,0.,0.,t,0.,0.,0.,0.);
    thlev=153.12;
    decay0_nucltransKL(prng_, event_, 0.662,0.037,9.0e-2,0.006,1.6e-2,0.,
		       // + tdlev,thlev,tdlev)
		       // corrected
		       tclev,thlev,tdlev);
    return;
    // change to 2nd forbidden non-unique shape with std::experimental correction factor
    // from S.T.Hsue et al., NP 86(1966)47: p_nu^2+0.004*p_el^2
    // cf(e)=(1+c1/w+c2*w+c3*w**2+c4*w**3), w=e/emass+1
    // wrong numerical coefficients
  label_2  :
    decay0_beta1(prng_, event_, 1.176,56.,0.,0.,t,0.,-0.6060315,0.0921520,0.);
    return;
  }
  // end of Cs137.f




} // end of namespace bxdecay0

// end of Cs137.cc
// Local Variables: --
// mode: c++ --
// End: --
