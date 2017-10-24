// Ourselves:
#include <bxdecay0/Xe135.h>

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

  // Xe135.f
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

  void Xe135(i_random & prng_,
             event & event_,
             const double tcnuc_,
             double & tdnuc_)
  {
    double t;
    double tdlev;
    double p;
    double pbeta;
    double tclev;
    double thlev;
    double thnuc;
    // Model of Xe135 decay (Yu.V.Sergeenkov et al., Nucl. Data Sheets
    // 84(1998)115).
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 9.10.2002.
    thnuc=32904.;
    tdnuc_=tcnuc_-thnuc/std::log(2.)*std::log(prng_());
    tclev=0.;
    pbeta=100.*prng_();
    if (pbeta <= 0.123) goto label_1062;  // 0.123%%
    if (pbeta <= 0.198) goto label_981;  // 0.075%
    if (pbeta <= 3.311) goto label_608;  // 3.113%
    if (pbeta <= 3.902) goto label_408;  // 0.591%
    goto label_250;  // 96.098%
  label_1062  :
    decay0_beta(prng_, event_, 0.089,55.,0.,0.,t);
    ////    label_10620  :
    thlev=0.;
    p=100.*prng_();
    if (p <=  3.34) goto label_10621;  // 3.34%
    if (p <= 60.40) goto label_10622;  // 57.06%
    if (p <= 97.07) goto label_10623;  // 36.67%
    goto label_10624;  // 2.93%
  label_10621  :
    decay0_nucltransK(prng_, event_, 1.062,0.036,2.0e-3,0.,tclev,thlev,tdlev);
    return;
  label_10622  :
    decay0_nucltransK(prng_, event_, 0.813,0.036,3.8e-3,0.,tclev,thlev,tdlev);
    goto label_25000;
  label_10623  :
    decay0_nucltransK(prng_, event_, 0.654,0.036,6.5e-3,0.,tclev,thlev,tdlev);
    goto label_40800;
  label_10624  :
    decay0_nucltransK(prng_, event_, 0.454,0.036,1.5e-2,0.,tclev,thlev,tdlev);
    goto label_60800;
  label_981  :
    decay0_beta(prng_, event_, 0.170,55.,0.,0.,t);
    ////    label_98100  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 73.53) goto label_98101;  // 73.53%
    if (p <= 79.95) goto label_98102;  // 6.42%
    goto label_98103;  // 20.05%
  label_98101  :
    decay0_nucltransK(prng_, event_, 0.732,0.036,5.0e-3,0.,tclev,thlev,tdlev);
    goto label_25000;
  label_98102  :
    decay0_nucltransK(prng_, event_, 0.573,0.036,9.0e-3,0.,tclev,thlev,tdlev);
    goto label_40800;
  label_98103  :
    decay0_nucltransK(prng_, event_, 0.373,0.036,2.5e-2,0.,tclev,thlev,tdlev);
    goto label_60800;
  label_608  :
    decay0_beta(prng_, event_, 0.543,55.,0.,0.,t);
  label_60800  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 92.42) goto label_60801;  // 92.42%
    if (p <= 99.62) goto label_60802;  // 7.20%
    goto label_60803;  // 0.38%
  label_60801  :
    decay0_nucltransK(prng_, event_, 0.608,0.036,7.5e-3,0.,tclev,thlev,tdlev);
    return;
  label_60802  :
    decay0_nucltransK(prng_, event_, 0.358,0.036,2.7e-2,0.,tclev,thlev,tdlev);
    goto label_25000;
  label_60803  :
    decay0_nucltransK(prng_, event_, 0.200,0.036,1.4e-1,0.,tclev,thlev,tdlev);
    goto label_40800;
  label_408  :
    decay0_beta(prng_, event_, 0.743,55.,0.,0.,t);
  label_40800  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 55.33) goto label_40801;  // 55.33%
    goto label_40802;  // 44.67%
  label_40801  :
    decay0_nucltransK(prng_, event_, 0.408,0.036,2.0e-2,0.,tclev,thlev,tdlev);
    return;
  label_40802  :
    decay0_nucltransK(prng_, event_, 0.158,0.036,2.5e-1,0.,tclev,thlev,tdlev);
    goto label_25000;
  label_250  :
    decay0_beta(prng_, event_, 0.901,55.,0.,0.,t);
  label_25000  :
    thlev=0.28e-9;
    decay0_nucltransK(prng_, event_, 0.250,0.036,7.6e-2,0.,tclev,thlev,tdlev);
    return;
  }
  // end of Xe135.f




} // end of namespace bxdecay0

// end of Xe135.cc
// Local Variables: --
// mode: c++ --
// End: --
