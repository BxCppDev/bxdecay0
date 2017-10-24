// Ourselves:
#include <bxdecay0/Ra222.h>

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

  // Ra222.f
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

  void Ra222(i_random & prng_,
             event & event_,
             const double tcnuc_,
             double & tdnuc_)
  {
    double t;
    double tdlev;
    double p;
    double palpha;
    double tclev;
    double thlev;
    double thnuc;
    // Model for scheme of Ra222 decay (NDS 107(2006)1027 and ENSDF at NNDC site
    // on 9.12.2007).
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 9.12.2007.
    thnuc=36.17;
    tdnuc_=tcnuc_-thnuc/std::log(2.)*std::log(prng_());
    tclev=0.;
    palpha=100.*prng_();
    if (palpha <= 0.0042) goto label_840;
    if (palpha <= 0.0083) goto label_797;
    if (palpha <= 0.0124) goto label_653;
    if (palpha <= 3.0635) goto label_324;
    goto label_10000;
  label_840  :
    decay0_alpha(prng_, event_, 5.734,0.,0.,t);
    //// label_84000  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 66.35) goto label_84001;
    goto label_84002;
  label_84001  :
    decay0_nucltransK(prng_, event_, 0.840,0.098,2.9e-2,0.,tclev,thlev,tdlev);
    return;
  label_84002  :
    decay0_nucltransK(prng_, event_, 0.516,0.098,2.5e-2,0.,tclev,thlev,tdlev);
    goto label_32400;
  label_797  :
    decay0_alpha(prng_, event_, 5.776,0.,0.,t);
    ////    label_79700  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 96.75) goto label_79701;
    goto label_79702;
  label_79701  :
    decay0_nucltransK(prng_, event_, 0.473,0.098,1.0e-2,0.,tclev,thlev,tdlev);
    goto label_32400;
  label_79702  :
    decay0_nucltransK(prng_, event_, 0.144,0.098,1.9e-1,0.,tclev,thlev,tdlev);
    goto label_65300;
  label_653  :
    decay0_alpha(prng_, event_, 5.917,0.,0.,t);
  label_65300  :
    thlev=0.;
    decay0_nucltransK(prng_, event_, 0.329,0.098,1.1e-1,0.,tclev,thlev,tdlev);
    goto label_32400;
  label_324  :
    decay0_alpha(prng_, event_, 6.240,0.,0.,t);
  label_32400  :
    thlev=0.;
    decay0_nucltransK(prng_, event_, 0.324,0.098,1.1e-1,0.,tclev,thlev,tdlev);
    return;
  label_10000  :
    decay0_alpha(prng_, event_, 6.559,0.,0.,t);
    return;
  }
  // end of Ra222.f




} // end of namespace bxdecay0

// end of Ra222.cc
// Local Variables: --
// mode: c++ --
// End: --
