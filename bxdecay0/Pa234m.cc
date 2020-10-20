// Copyright 1995-2016 V.I. Tretyak
// Copyright 2011-2017 F. Mauger
//
// This program is free software: you  can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free  Software Foundation, either  version 3 of the  License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

// Ourselves:
#include <bxdecay0/Pa234m.h>

// Standard library:
#include <cmath>
#include <sstream>
#include <stdexcept>

// This project:
#include <bxdecay0/PbAtShell.h>
#include <bxdecay0/alpha.h>
#include <bxdecay0/beta.h>
#include <bxdecay0/beta1.h>
#include <bxdecay0/beta2.h>
#include <bxdecay0/beta_1fu.h>
#include <bxdecay0/electron.h>
#include <bxdecay0/event.h>
#include <bxdecay0/gamma.h>
#include <bxdecay0/i_random.h>
#include <bxdecay0/nucltransK.h>
#include <bxdecay0/nucltransKL.h>
#include <bxdecay0/nucltransKLM.h>
#include <bxdecay0/nucltransKLM_Pb.h>
#include <bxdecay0/pair.h>
#include <bxdecay0/particle.h>
#include <bxdecay0/positron.h>

namespace bxdecay0 {

  void Pa234m(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_)
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
    // VIT, 1.03.2017 - update to NDS 108(2007)681; levels with E_exc>1.045
    // MeV are still not considered.
    thnuc  = 69.54;
    tdnuc_ = tcnuc_ - thnuc / std::log(2.) * std::log(prng_());
    tclev  = 0.;
    pdecay = 100. * prng_();
    // IT to Pa234
    if (pdecay <= 0.16) {
      ;
      decay0_nucltransK(prng_, event_, 0.074, 0.021, 1.1e+1, 0., tclev, thlev, tdlev);
      return;
    };
    // beta decay to U234
    pbeta = 100. * prng_();
    if (pbeta <= 1.006) {
      goto label_1045; // 1.006%
    }
    if (pbeta <= 1.015) {
      goto label_989; // 0.009%
    }
    if (pbeta <= 1.967) {
      goto label_810; // 0.952%
    }
    if (pbeta <= 2.026) {
      goto label_786; // 0.059%
    }
    goto label_10000; // 97.974%
  label_1045:
    decay0_beta(prng_, event_, 1.224, 92., 0., 0., t);
    ////    label_10450  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 83.766) {
      goto label_10451; // 83.766%
    }
    if (p <= 91.281) {
      goto label_10452; // 7.515%
    }
    if (p <= 99.897) {
      goto label_10453; // 8.616%
    }
    goto label_10454;   // 0.103%
  label_10451:
    decay0_nucltransK(prng_, event_, 1.001, 0.116, 1.1e-2, 0., tclev, thlev, tdlev);
    goto label_43000;
  label_10452:
    decay0_nucltransK(prng_, event_, 0.258, 0.116, 5.5e-2, 0., tclev, thlev, tdlev);
    goto label_78600;
  label_10453:
    decay0_electron(prng_, event_, 0.119, tclev, thlev, tdlev); // only ec
    decay0_gamma(prng_, event_, 0.116, 0., 0., tdlev);
    goto label_81000;
  label_10454:
    decay0_nucltransK(prng_, event_, 0.193, 0.116, 8.5e-1, 0., tclev, thlev, tdlev);
    goto label_85200;
  label_989:
    decay0_beta(prng_, event_, 1.280, 92., 0., 0., t);
    //// label_98900  :
    thlev = 0.76e-9;
    p     = 100. * prng_();
    if (p <= 42.437) {
      goto label_98901; // 42.437%
    }
    if (p <= 59.244) {
      goto label_98902; // 16.807%
    }
    if (p <= 92.857) {
      goto label_98903; // 33.613%
    }
    goto label_98904;   // 7.143%
  label_98901:
    decay0_nucltransK(prng_, event_, 0.946, 0.116, 4.1e-3, 0., tclev, thlev, tdlev);
    goto label_43000;
  label_98902:
    decay0_nucltransK(prng_, event_, 0.203, 0.116, 1.4e0, 0., tclev, thlev, tdlev);
    goto label_78600;
  label_98903:
    decay0_nucltransK(prng_, event_, 0.140, 0.116, 5.3e0, 0., tclev, thlev, tdlev);
    goto label_84900;
  label_98904:
    decay0_nucltransK(prng_, event_, 0.063, 0.022, 4.3e-1, 0., tclev, thlev, tdlev);
    goto label_92700;
  label_92700:
    thlev = 1.38e-12;
    p     = 100. * prng_();
    if (p <= 25.714) {
      goto label_92701; // 25.714%
    }
    if (p <= 99.1847) {
      goto label_92702; // 73.470%
    }
    goto label_92703;   // 0.816%
  label_92701:
    decay0_nucltransK(prng_, event_, 0.927, 0.116, 1.3e-2, 0., tclev, thlev, tdlev);
    return;
  label_92702:
    decay0_nucltransK(prng_, event_, 0.883, 0.116, 1.4e-2, 0., tclev, thlev, tdlev);
    goto label_43000;
  label_92703:
    decay0_nucltransK(prng_, event_, 0.783, 0.116, 1.8e-2, 0., tclev, thlev, tdlev);
    goto label_14300;
  // label_852  :
  //   decay0_beta(prng_, event_, 1.417,92.,0.,0.,t);
  label_85200:
    thlev = 1.74e-12;
    p     = 100. * prng_();
    if (p <= 15.556) {
      goto label_85201; // 15.556%
    }
    if (p <= 63.368) {
      goto label_85202; // 47.812%
    }
    if (p <= 68.223) {
      goto label_85203; // 4.855%
    }
    goto label_85204;   // 31.777%
  label_85201:
    decay0_nucltransK(prng_, event_, 0.852, 0.116, 1.5e-2, 0., tclev, thlev, tdlev);
    return;
  label_85202:
    decay0_nucltransK(prng_, event_, 0.808, 0.116, 4.2e0, 0., tclev, thlev, tdlev);
    goto label_43000;
  label_85203:
    decay0_nucltransK(prng_, event_, 0.708, 0.116, 2.2e-2, 0., tclev, thlev, tdlev);
    goto label_14300;
  label_85204:
    decay0_nucltransK(prng_, event_, 0.042, 0.022, 8.6e+2, 0., tclev, thlev, tdlev);
    goto label_81000;
  label_84900:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 51.304) {
      goto label_84901; // 51.304%
    }
    goto label_84902;   // 48.696%
  label_84901:
    decay0_nucltransK(prng_, event_, 0.806, 0.116, 5.5e-3, 0., tclev, thlev, tdlev);
    goto label_43000;
  label_84902:
    decay0_nucltransK(prng_, event_, 0.706, 0.116, 7.0e-3, 0., tclev, thlev, tdlev);
    goto label_14300;
  label_810:
    decay0_beta(prng_, event_, 1.459, 92., 0., 0., t);
  label_81000:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 72.606) {
      goto label_81001; // 72.606%
    }
    goto label_81002;   // 27.394%
  label_81001:
    decay0_electron(prng_, event_, 0.694, tclev, thlev, tdlev); // only ec
    decay0_gamma(prng_, event_, 0.116, 0., 0., tdlev);
    return;
  label_81002:
    decay0_nucltransK(prng_, event_, 0.766, 0.116, 1.9e-2, 0., tclev, thlev, tdlev);
    goto label_43000;
  label_786:
    decay0_beta(prng_, event_, 1.483, 92., 0., 0., t);
  label_78600:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 33.786) {
      goto label_78601; // 33.786%
    }
    goto label_78602;   // 66.214%
  label_78601:
    decay0_nucltransK(prng_, event_, 0.786, 0.116, 5.7e-3, 0., tclev, thlev, tdlev);
    return;
  label_78602:
    decay0_nucltransK(prng_, event_, 0.743, 0.116, 6.4e-3, 0., tclev, thlev, tdlev);
    goto label_43000;
  label_14300:
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 0.100, 0.022, 1.3e+1, 0., tclev, thlev, tdlev);
    goto label_43000;
  label_43000:
    thlev = 0.252e-9;
    decay0_nucltransK(prng_, event_, 0.043, 0.022, 7.1e+2, 0., tclev, thlev, tdlev);
    return;
    // change to 1st forbidden shape with std::experimental shape factor from
    // A.G.Carles et al., NIMA 369(1996)431
    // cf(e)=(1+c1/w+c2*w+c3*w**2+c4*w**3), w=e/emass+1.
  label_10000:
    decay0_beta1(prng_, event_, 2.269, 92., 0., 0., t, 0., -0.09, 0., 0.);
    return;
  }
  // end of Pa234m.f

} // end of namespace bxdecay0

// end of Pa234m.cc
// Local Variables: --
// mode: c++ --
// End: --
