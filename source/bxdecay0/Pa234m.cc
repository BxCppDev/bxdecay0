// Ourselves:
#include <bxdecay0/Pa234m.h>

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

  // Pa234m.f
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

  void Pa234m(i_random & prng_,
              event & event_,
              const double tcnuc_,
              double & tdnuc_)
  {
    double t;
    double tdlev;
    double p;
    double pbeta;
    double pdecay;
    double tclev;
    double thlev = 0.0;
    double thnuc;
    // Model (not the exact) scheme of Pa234m decay ("Table of Isotopes",
    // 7th ed., 1978):
    // decays of Pa234m to excited levels of U234 with energies
    // greater than 1.045 MeV are not considered (p=0.20%).
    // Three- and four-figured labels correspond to energies of
    // U234 excited levels in keV.
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 18.08.1992, 22.10.1995
    // VIT, 3.11.2006 (update to NDS 71(1994)181 - however, levels with E_exc>1.045
    // MeV are still not considered
    // to the 1st forbidden with std::exp. corr.).
    thnuc=70.2;
    tdnuc_=tcnuc_-thnuc/std::log(2.)*std::log(prng_());
    tclev=0.;
    pdecay=100.*prng_();
    // IT to Pa234
    if (pdecay <= 0.16) {;
      decay0_nucltransK(prng_, event_, 0.074,0.021,1.1e+1,0.,tclev,thlev,tdlev);
      return;
    };
    // beta decay to U234
    pbeta=100.*prng_();
    if (pbeta <= 1.008) goto label_1045;  // 1.008%
    if (pbeta <= 1.012) goto label_989;  // 0.004%
    if (pbeta <= 1.022) goto label_852;  // 0.010%
    if (pbeta <= 1.712) goto label_810;  // 0.690%
    if (pbeta <= 1.744) goto label_786;  // 0.032%
    goto label_10000;  // 98.256%
  label_1045  :
    decay0_beta(prng_, event_, 1.224,92.,0.,0.,t);
    ////    label_10450  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 83.7) goto label_10451;  // 83.7%
    if (p <= 91.3) goto label_10452;  // 7.6%
    if (p <= 99.9) goto label_10453;  // 8.6%
    goto label_10454;  // 0.1%
  label_10451  :
    decay0_nucltransK(prng_, event_, 1.001,0.116,1.1e-2,0.,tclev,thlev,tdlev);
    goto label_43000;
  label_10452  :
    decay0_nucltransK(prng_, event_, 0.258,0.116,5.5e-2,0.,tclev,thlev,tdlev);
    goto label_78600;
  label_10453  :
    decay0_electron(prng_, event_, 0.120,tclev,thlev,tdlev)  ;// only ec
    decay0_gamma(prng_, event_, 0.116,0.,0.,tdlev);
    goto label_81000;
  label_10454  :
    decay0_nucltransK(prng_, event_, 0.193,0.116,8.8e-1,0.,tclev,thlev,tdlev);
    goto label_85200;
  label_989  :
    decay0_beta(prng_, event_, 1.280,92.,0.,0.,t);
    //// label_98900  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 44.8) goto label_98901;  // 44.8%
    if (p <= 56.1) goto label_98902;  // 11.3%
    if (p <= 92.3) goto label_98903;  // 36.2%
    goto label_98904;  // 7.7%
  label_98901  :
    decay0_nucltransK(prng_, event_, 0.946,0.116,4.1e-3,0.,tclev,thlev,tdlev);
    goto label_43000;
  label_98902  :
    decay0_nucltransK(prng_, event_, 0.203,0.116,1.5e0,0.,tclev,thlev,tdlev);
    goto label_78600;
  label_98903  :
    decay0_nucltransK(prng_, event_, 0.140,0.116,5.5e0,0.,tclev,thlev,tdlev);
    goto label_84900;
  label_98904  :
    decay0_nucltransK(prng_, event_, 0.063,0.022,4.3e-1,0.,tclev,thlev,tdlev);
    goto label_92700;
  label_92700  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 40.4) goto label_92701;  // 40.4%
    if (p <= 98.7) goto label_92702;  // 58.3%
    goto label_92703;  // 1.3%
  label_92701  :
    decay0_nucltransK(prng_, event_, 0.927,0.116,1.3e-2,0.,tclev,thlev,tdlev);
    return;
  label_92702  :
    decay0_nucltransK(prng_, event_, 0.883,0.116,1.4e-2,0.,tclev,thlev,tdlev);
    goto label_43000;
  label_92703  :
    decay0_nucltransK(prng_, event_, 0.783,0.116,1.8e-2,0.,tclev,thlev,tdlev);
    goto label_14300;
  label_852  :
    decay0_beta(prng_, event_, 1.417,92.,0.,0.,t);
  label_85200  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 18.6) goto label_85201;  // 18.6%
    if (p <= 64.6) goto label_85202;  // 46.0%
    goto label_85203;  // 35.4%
  label_85201  :
    decay0_nucltransK(prng_, event_, 0.852,0.116,1.5e-2,0.,tclev,thlev,tdlev);
    return;
  label_85202  :
    decay0_nucltransK(prng_, event_, 0.808,0.116,4.2e0,0.,tclev,thlev,tdlev);
    goto label_43000;
  label_85203  :
    decay0_nucltransK(prng_, event_, 0.042,0.022,1.0e+1,0.,tclev,thlev,tdlev);
    goto label_81000;
  label_84900  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 51.8) goto label_84901;  // 51.8%
    goto label_84902;  // 48.2%
  label_84901  :
    decay0_nucltransK(prng_, event_, 0.806,0.116,5.5e-3,0.,tclev,thlev,tdlev);
    goto label_43000;
  label_84902  :
    decay0_nucltransK(prng_, event_, 0.706,0.116,7.0e-3,0.,tclev,thlev,tdlev);
    goto label_14300;
  label_810  :
    decay0_beta(prng_, event_, 1.459,92.,0.,0.,t);
  label_81000  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 63.0) goto label_81001;  // 63%
    goto label_81002;  // 37%
  label_81001  :
    decay0_electron(prng_, event_, 0.694,tclev,thlev,tdlev)  ;// only ec
    decay0_gamma(prng_, event_, 0.116,0.,0.,tdlev);
    return;
  label_81002  :
    decay0_nucltransK(prng_, event_, 0.766,0.116,1.9e-2,0.,tclev,thlev,tdlev);
    goto label_43000;
  label_786  :
    decay0_beta(prng_, event_, 1.483,92.,0.,0.,t);
  label_78600  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 37.6) goto label_78601;  // 37.6%
    goto label_78602;  // 62.4%
  label_78601  :
    decay0_nucltransK(prng_, event_, 0.786,0.116,5.8e-3,0.,tclev,thlev,tdlev);
    return;
  label_78602  :
    decay0_nucltransK(prng_, event_, 0.743,0.116,6.4e-3,0.,tclev,thlev,tdlev);
    goto label_43000;
  label_14300  :
    thlev=0.;
    decay0_nucltransK(prng_, event_, 0.100,0.022,1.4e+1,0.,tclev,thlev,tdlev);
    goto label_43000;
  label_43000  :
    thlev=0.25e-9;
    decay0_nucltransK(prng_, event_, 0.043,0.022,7.2e+2,0.,tclev,thlev,tdlev);
    return;
    // change to 1st forbidden shape with std::experimental shape factor from
    // A.G.Carles et al., NIMA 369(1996)431
    // cf(e)=(1+c1/w+c2*w+c3*w**2+c4*w**3), w=e/emass+1.
  label_10000  :
    decay0_beta1(prng_, event_, 2.269,92.,0.,0.,t,0.,-0.09,0.,0.);
    return;
  }
  // end of Pa234m.f




} // end of namespace bxdecay0

// end of Pa234m.cc
// Local Variables: --
// mode: c++ --
// End: --
