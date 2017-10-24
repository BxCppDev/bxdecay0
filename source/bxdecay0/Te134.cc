// Ourselves:
#include <bxdecay0/Te134.h>

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

  // Te134.f
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

  void Te134(i_random & prng_,
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
    // Model for scheme of Te134 decay (Yu.V.Sergeenkov, Nucl. Data Sheets
    // 71(1994)557).
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 7.10.2002.
    thnuc=2508.;
    tdnuc_=tcnuc_-thnuc/std::log(2.)*std::log(prng_());
    tclev=0.;
    pbeta=100.*prng_();
    if (pbeta <= 14.) goto label_1106;  // 14%
    if (pbeta <= 58.) goto label_923;  // 44%
    goto label_847;  // 42%
  label_1106  :
    decay0_beta(prng_, event_, 0.454,53.,0.,0.,t);
    ////    label_11060  :
    thlev=0.;
    p=100.*prng_();
    if (p <=  3.33) goto label_11061;  // 3.33%
    if (p <= 14.45) goto label_11062;  // 11.12%
    if (p <= 17.78) goto label_11063;  // 3.33%
    if (p <= 91.15) goto label_11064;  // 73.37%
    if (p <= 94.70) goto label_11065;  // 3.55%
    goto label_11066;  // 5.30%
  label_11061  :
    decay0_nucltransK(prng_, event_, 1.027,0.033,1.5e-3,0.,tclev,thlev,tdlev);
    goto label_79000;
  label_11062  :
    decay0_nucltransK(prng_, event_, 0.926,0.033,2.5e-3,0.,tclev,thlev,tdlev);
    goto label_18100;
  label_11063  :
    decay0_nucltransK(prng_, event_, 0.896,0.033,3.0e-3,0.,tclev,thlev,tdlev);
    goto label_21000;
  label_11064  :
    decay0_nucltransK(prng_, event_, 0.461,0.033,1.5e-2,0.,tclev,thlev,tdlev);
    goto label_64500;
  label_11065  :
    decay0_nucltransK(prng_, event_, 0.260,0.033,6.0e-2,0.,tclev,thlev,tdlev);
    goto label_84700;
  label_11066  :
    decay0_nucltransK(prng_, event_, 0.183,0.033,1.8e-1,0.,tclev,thlev,tdlev);
    goto label_92300;
  label_923  :
    decay0_beta(prng_, event_, 0.637,53.,0.,0.,t);
  label_92300  :
    thlev=0.;
    p=100.*prng_();
    if (p <=  2.71) goto label_92301;  // 2.71%
    if (p <= 37.31) goto label_92302;  // 34.60%
    if (p <= 47.94) goto label_92303;  // 10.63%
    if (p <= 98.37) goto label_92304;  // 50.43%
    goto label_92305;  // 1.63%
  label_92301  :
    decay0_nucltransK(prng_, event_, 0.844,0.033,2.5e-3,0.,tclev,thlev,tdlev);
    goto label_79000;
  label_92302  :
    decay0_nucltransK(prng_, event_, 0.743,0.033,4.5e-3,0.,tclev,thlev,tdlev);
    goto label_18100;
  label_92303  :
    decay0_nucltransK(prng_, event_, 0.713,0.033,5.0e-3,0.,tclev,thlev,tdlev);
    goto label_21000;
  label_92304  :
    decay0_nucltransK(prng_, event_, 0.278,0.033,4.9e-2,0.,tclev,thlev,tdlev);
    goto label_64500;
  label_92305  :
    decay0_nucltransK(prng_, event_, 0.077,0.033,1.61,0.,tclev,thlev,tdlev);
    goto label_84700;
  label_847  :
    decay0_beta(prng_, event_, 0.713,53.,0.,0.,t);
  label_84700  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 69.71) goto label_84701;  // 69.71%
    if (p <= 72.49) goto label_84702;  // 2.78%
    if (p <= 76.45) goto label_84703;  // 3.96%
    goto label_84704;  // 23.55%
  label_84701  :
    decay0_nucltransK(prng_, event_, 0.767,0.033,3.3e-3,0.,tclev,thlev,tdlev);
    goto label_79000;
  label_84702  :
    decay0_nucltransK(prng_, event_, 0.666,0.033,6.0e-3,0.,tclev,thlev,tdlev);
    goto label_18100;
  label_84703  :
    decay0_nucltransK(prng_, event_, 0.636,0.033,7.0e-3,0.,tclev,thlev,tdlev);
    goto label_21000;
  label_84704  :
    decay0_nucltransK(prng_, event_, 0.201,0.033,1.3e-1,0.,tclev,thlev,tdlev);
    goto label_64500;
  label_64500  :
    thlev=0.;
    p=100.*prng_();
    if (p <=  2.03) goto label_64501;  // 2.03%
    if (p <= 45.01) goto label_64502;  // 42.98%
    if (p <= 55.87) goto label_64503;  // 10.86%
    goto label_64504;  // 44.13%
  label_64501  :
    decay0_nucltransK(prng_, event_, 0.645,0.033,5.0e-3,0.,tclev,thlev,tdlev);
    return;
  label_64502  :
    decay0_nucltransK(prng_, event_, 0.566,0.033,9.0e-3,0.,tclev,thlev,tdlev);
    goto label_79000;
  label_64503  :
    decay0_nucltransK(prng_, event_, 0.465,0.033,1.5e-2,0.,tclev,thlev,tdlev);
    goto label_18100;
  label_64504  :
    decay0_nucltransK(prng_, event_, 0.435,0.033,1.4e-2,0.,tclev,thlev,tdlev);
    goto label_21000;
  label_21000  :
    thlev=0.15e-9;
    p=100.*prng_();
    if (p <= 98.94) goto label_21001;  // 98.94%
    goto label_21002;  // 1.06%
  label_21001  :
    decay0_nucltransK(prng_, event_, 0.210,0.033,1.1e-1,0.,tclev,thlev,tdlev);
    return;
  label_21002  :
    decay0_nucltransK(prng_, event_, 0.131,0.033,5.2e-1,0.,tclev,thlev,tdlev);
    goto label_79000;
  label_18100  :
    thlev=0.1e-9;
    p=100.*prng_();
    if (p <= 95.83) goto label_18101;  // 95.83%
    if (p <= 96.45) goto label_18102;  // 0.62%
    goto label_18103;  // 3.55%
  label_18101  :
    decay0_nucltransK(prng_, event_, 0.181,0.033,1.8e-1,0.,tclev,thlev,tdlev);
    return;
  label_18102  :
    decay0_nucltransK(prng_, event_, 0.137,0.033,5.8e-1,0.,tclev,thlev,tdlev);
    goto label_44000;
  label_18103  :
    decay0_nucltransK(prng_, event_, 0.101,0.033,1.2,0.,tclev,thlev,tdlev);
    goto label_79000;
  label_79000  :
    thlev=1.62e-9;
    decay0_nucltransK(prng_, event_, 0.079,0.033,1.50,0.,tclev,thlev,tdlev);
    return;
  label_44000  :
    thlev=0.;
    decay0_nucltransK(prng_, event_, 0.044,0.033,7.97,0.,tclev,thlev,tdlev);
    return;
  }
  // end of Te134.f




} // end of namespace bxdecay0

// end of Te134.cc
// Local Variables: --
// mode: c++ --
// End: --
