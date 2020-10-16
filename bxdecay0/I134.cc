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
#include <bxdecay0/I134.h>

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

  void I134(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_)
  {
    double t;
    double tdlev;
    double p;
    double pbeta;
    double tclev;
    double thlev;
    double thnuc;
    // Scheme of I134 decay in accordance with Yu.V.Sergeenkov,
    // NDS 71(1994)557.
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 8.10.2002.
    thnuc  = 3168.;
    tdnuc_ = tcnuc_ - thnuc / std::log(2.) * std::log(prng_());
    tclev  = 0.;
    pbeta  = 100. * prng_();
    if (pbeta <= 0.368) {
      goto label_3492;
    }
    if (pbeta <= 0.435) {
      goto label_3477;
    }
    if (pbeta <= 2.216) {
      goto label_3375;
    }
    if (pbeta <= 3.300) {
      goto label_3360;
    }
    if (pbeta <= 3.509) {
      goto label_3314;
    }
    if (pbeta <= 3.567) {
      goto label_3300;
    }
    if (pbeta <= 3.786) {
      goto label_3256;
    }
    if (pbeta <= 5.129) {
      goto label_3084;
    }
    if (pbeta <= 35.372) {
      goto label_2867;
    }
    if (pbeta <= 35.889) {
      goto label_2773;
    }
    if (pbeta <= 42.754) {
      goto label_2654;
    }
    if (pbeta <= 58.871) {
      goto label_2588;
    }
    if (pbeta <= 62.950) {
      goto label_2548;
    }
    if (pbeta <= 69.516) {
      goto label_2408;
    }
    if (pbeta <= 80.460) {
      goto label_2353;
    }
    if (pbeta <= 82.689) {
      goto label_2302;
    }
    if (pbeta <= 84.281) {
      goto label_2272;
    }
    if (pbeta <= 87.564) {
      goto label_1920;
    }
    goto label_1731;
  label_3492:
    decay0_beta(prng_, event_, 0.678, 54., 0., 0., t);
    ////    label_34920  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 5.17) {
      goto label_34921; // 5.17%
    }
    goto label_34922;   // 94.83%
  label_34921:
    decay0_nucltransK(prng_, event_, 2.646, 0.035, 1.5e-4, 5.2e-4, tclev, thlev, tdlev);
    goto label_84700;
  label_34922:
    decay0_nucltransK(prng_, event_, 1.190, 0.035, 2.0e-3, 0.2e-4, tclev, thlev, tdlev);
    goto label_23020;
  label_3477:
    decay0_beta(prng_, event_, 0.693, 54., 0., 0., t);
    ////    label_34770  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 18.77) {
      goto label_34771; // 18.77%
    }
    goto label_34772;   // 81.23%
  label_34771:
    decay0_nucltransK(prng_, event_, 2.630, 0.035, 1.5e-4, 5.1e-4, tclev, thlev, tdlev);
    goto label_84700;
  label_34772:
    decay0_nucltransK(prng_, event_, 0.162, 0.035, 2.5e-1, 0., tclev, thlev, tdlev);
    goto label_33140;
  label_3375:
    decay0_beta(prng_, event_, 0.795, 54., 0., 0., t);
    ////    label_33750  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 21.79) {
      goto label_33751;
    }
    if (p <= 33.52) {
      goto label_33752;
    }
    if (p <= 78.21) {
      goto label_33753;
    }
    goto label_33754;
  label_33751:
    decay0_nucltransK(prng_, event_, 1.644, 0.035, 1.5e-3, 1.2e-4, tclev, thlev, tdlev);
    goto label_17310;
  label_33752:
    decay0_nucltransK(prng_, event_, 1.239, 0.035, 1.7e-3, 0.4e-4, tclev, thlev, tdlev);
    goto label_21370;
  label_33753:
    decay0_nucltransK(prng_, event_, 1.103, 0.035, 2.1e-3, 0.1e-4, tclev, thlev, tdlev);
    goto label_22720;
  label_33754:
    decay0_nucltransK(prng_, event_, 0.967, 0.035, 2.5e-3, 0., tclev, thlev, tdlev);
    goto label_24080;
  label_3360:
    decay0_beta(prng_, event_, 0.810, 54., 0., 0., t);
    ////    label_33600  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 6.16) {
      goto label_33601;
    }
    if (p <= 23.64) {
      goto label_33602;
    }
    goto label_33603;
  label_33601:
    decay0_nucltransK(prng_, event_, 2.513, 0.035, 2.0e-4, 4.6e-4, tclev, thlev, tdlev);
    goto label_84700;
  label_33602:
    decay0_nucltransK(prng_, event_, 1.629, 0.035, 9.0e-4, 1.1e-4, tclev, thlev, tdlev);
    goto label_17310;
  label_33603:
    decay0_nucltransK(prng_, event_, 0.707, 0.035, 5.0e-3, 0., tclev, thlev, tdlev);
    goto label_26540;
  label_3314:
    decay0_beta(prng_, event_, 0.856, 54., 0., 0., t);
  label_33140:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 63.81) {
      goto label_33141;
    }
    goto label_33142;
  label_33141:
    decay0_nucltransK(prng_, event_, 2.467, 0.035, 2.0e-4, 4.5e-4, tclev, thlev, tdlev);
    goto label_84700;
  label_33142:
    decay0_nucltransK(prng_, event_, 1.395, 0.035, 1.2e-3, 0.7e-4, tclev, thlev, tdlev);
    goto label_19200;
  label_3300:
    decay0_beta(prng_, event_, 0.870, 54., 0., 0., t);
    ////    label_33000  :
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 2.453, 0.035, 2.0e-4, 4.4e-4, tclev, thlev, tdlev);
    goto label_84700;
  label_3256:
    decay0_beta(prng_, event_, 0.914, 54., 0., 0., t);
    ////    label_32560  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 35.78) {
      goto label_32561;
    }
    goto label_32562;
  label_32561:
    decay0_nucltransK(prng_, event_, 2.409, 0.035, 2.1e-4, 4.1e-4, tclev, thlev, tdlev);
    goto label_84700;
  label_32562:
    decay0_nucltransK(prng_, event_, 1.336, 0.035, 1.2e-3, 0.6e-4, tclev, thlev, tdlev);
    goto label_19200;
  label_3084:
    decay0_beta(prng_, event_, 1.086, 54., 0., 0., t);
    ////    label_30840  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 3.95) {
      goto label_30841;
    }
    if (p <= 59.80) {
      goto label_30842;
    }
    if (p <= 90.32) {
      goto label_30843;
    }
    goto label_30844;
  label_30841:
    decay0_nucltransK(prng_, event_, 2.237, 0.035, 3.0e-4, 3.2e-4, tclev, thlev, tdlev);
    goto label_84700;
  label_30842:
    decay0_nucltransK(prng_, event_, 1.470, 0.035, 1.0e-3, 0.9e-4, tclev, thlev, tdlev);
    goto label_16140;
  label_30843:
    decay0_nucltransK(prng_, event_, 1.353, 0.035, 1.2e-3, 0.6e-4, tclev, thlev, tdlev);
    goto label_17310;
  label_30844:
    decay0_nucltransK(prng_, event_, 1.164, 0.035, 1.6e-3, 0.2e-4, tclev, thlev, tdlev);
    goto label_19200;
  label_2867:
    decay0_beta(prng_, event_, 1.303, 54., 0., 0., t);
    ////    label_28670  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 0.62) {
      goto label_28671;
    }
    if (p <= 30.54) {
      goto label_28672;
    }
    if (p <= 43.73) {
      goto label_28673;
    }
    if (p <= 49.75) {
      goto label_28674;
    }
    if (p <= 86.25) {
      goto label_28675;
    }
    if (p <= 93.65) {
      goto label_28676;
    }
    if (p <= 97.99) {
      goto label_28677;
    }
    if (p <= 99.50) {
      goto label_28678;
    }
    goto label_28679;
  label_28671:
    decay0_nucltransK(prng_, event_, 2.021, 0.035, 3.0e-4, 2.3e-4, tclev, thlev, tdlev);
    goto label_84700;
  label_28672:
    decay0_nucltransK(prng_, event_, 1.136, 0.035, 1.6e-3, 0.3e-4, tclev, thlev, tdlev);
    goto label_17310;
  label_28673:
    decay0_nucltransK(prng_, event_, 0.948, 0.035, 2.4e-3, 0., tclev, thlev, tdlev);
    goto label_19200;
  label_28674:
    decay0_nucltransK(prng_, event_, 0.731, 0.035, 3.4e-3, 0., tclev, thlev, tdlev);
    goto label_21370;
  label_28675:
    decay0_nucltransK(prng_, event_, 0.595, 0.035, 7.2e-3, 0., tclev, thlev, tdlev);
    goto label_22720;
  label_28676:
    decay0_nucltransK(prng_, event_, 0.514, 0.035, 8.0e-3, 0., tclev, thlev, tdlev);
    goto label_23530;
  label_28677:
    decay0_nucltransK(prng_, event_, 0.459, 0.035, 1.1e-2, 0., tclev, thlev, tdlev);
    goto label_24080;
  label_28678:
    decay0_nucltransK(prng_, event_, 0.320, 0.035, 3.7e-2, 0., tclev, thlev, tdlev);
    goto label_25480;
  label_28679:
    decay0_nucltransK(prng_, event_, 0.279, 0.035, 5.2e-2, 0., tclev, thlev, tdlev);
    goto label_25880;
  label_2773:
    decay0_beta(prng_, event_, 1.397, 54., 0., 0., t);
    ////    label_27730  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 34.62) {
      goto label_27731;
    }
    goto label_27732;
  label_27731:
    decay0_nucltransK(prng_, event_, 1.926, 0.035, 4.0e-4, 2.0e-4, tclev, thlev, tdlev);
    goto label_84700;
  label_27732:
    decay0_nucltransK(prng_, event_, 1.159, 0.035, 7.0e-4, 0.3e-4, tclev, thlev, tdlev);
    goto label_16140;
  label_2654:
    decay0_beta(prng_, event_, 1.516, 54., 0., 0., t);
  label_26540:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 71.82) {
      goto label_26541;
    }
    if (p <= 98.18) {
      goto label_26542;
    }
    goto label_26543;
  label_26541:
    decay0_nucltransK(prng_, event_, 1.807, 0.035, 6.0e-4, 1.7e-4, tclev, thlev, tdlev);
    goto label_84700;
  label_26542:
    decay0_nucltransK(prng_, event_, 1.040, 0.035, 2.0e-3, 0., tclev, thlev, tdlev);
    goto label_16140;
  label_26543:
    decay0_nucltransK(prng_, event_, 0.922, 0.035, 2.1e-3, 0., tclev, thlev, tdlev);
    goto label_17310;
  label_2588:
    decay0_beta(prng_, event_, 1.582, 54., 0., 0., t);
  label_25880:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 15.66) {
      goto label_25881;
    }
    if (p <= 44.90) {
      goto label_25882;
    }
    if (p <= 85.87) {
      goto label_25883;
    }
    goto label_25884;
  label_25881:
    decay0_nucltransK(prng_, event_, 1.741, 0.035, 6.0e-4, 0.8e-4, tclev, thlev, tdlev);
    goto label_84700;
  label_25882:
    decay0_nucltransK(prng_, event_, 0.975, 0.035, 1.7e-3, 0., tclev, thlev, tdlev);
    goto label_16140;
  label_25883:
    decay0_nucltransK(prng_, event_, 0.857, 0.035, 2.9e-3, 0., tclev, thlev, tdlev);
    goto label_17310;
  label_25884:
    decay0_nucltransK(prng_, event_, 0.235, 0.035, 8.5e-2, 0., tclev, thlev, tdlev);
    goto label_23530;
  label_2548:
    decay0_beta(prng_, event_, 1.622, 54., 0., 0., t);
  label_25480:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 13.78) {
      goto label_25481;
    }
    if (p <= 63.11) {
      goto label_25482;
    }
    if (p <= 75.78) {
      goto label_25483;
    }
    goto label_25484;
  label_25481:
    decay0_nucltransK(prng_, event_, 0.816, 0.035, 4.0e-3, 0., tclev, thlev, tdlev);
    goto label_17310;
  label_25482:
    decay0_nucltransK(prng_, event_, 0.628, 0.035, 4.9e-3, 0., tclev, thlev, tdlev);
    goto label_19200;
  label_25483:
    decay0_nucltransK(prng_, event_, 0.411, 0.035, 2.0e-2, 0., tclev, thlev, tdlev);
    goto label_21370;
  label_25484:
    decay0_nucltransK(prng_, event_, 0.139, 0.035, 4.5e-1, 0., tclev, thlev, tdlev);
    goto label_24080;
  label_2408:
    decay0_beta(prng_, event_, 1.762, 54., 0., 0., t);
  label_24080:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 84.57) {
      goto label_24081;
    }
    goto label_24082;
  label_24081:
    decay0_nucltransK(prng_, event_, 0.677, 0.035, 5.3e-3, 0., tclev, thlev, tdlev);
    goto label_17310;
  label_24082:
    decay0_nucltransK(prng_, event_, 0.489, 0.035, 9.6e-3, 0., tclev, thlev, tdlev);
    goto label_19200;
  label_2353:
    decay0_beta(prng_, event_, 1.817, 54., 0., 0., t);
  label_23530:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 4.42) {
      goto label_23531;
    }
    if (p <= 73.01) {
      goto label_23532;
    }
    goto label_23533;
  label_23531:
    decay0_nucltransK(prng_, event_, 0.739, 0.035, 3.3e-3, 0., tclev, thlev, tdlev);
    goto label_16140;
  label_23532:
    decay0_nucltransK(prng_, event_, 0.622, 0.035, 6.1e-3, 0., tclev, thlev, tdlev);
    goto label_17310;
  label_23533:
    decay0_nucltransK(prng_, event_, 0.433, 0.035, 1.6e-2, 0., tclev, thlev, tdlev);
    goto label_19200;
  label_2302:
    decay0_beta(prng_, event_, 1.868, 54., 0., 0., t);
  label_23020:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 88.08) {
      goto label_23021;
    }
    goto label_23022;
  label_23021:
    decay0_nucltransK(prng_, event_, 1.455, 0.035, 1.1e-3, 0.8e-4, tclev, thlev, tdlev);
    goto label_84700;
  label_23022:
    decay0_nucltransK(prng_, event_, 0.571, 0.035, 9.0e-3, 0., tclev, thlev, tdlev);
    goto label_17310;
  label_2272:
    decay0_beta(prng_, event_, 1.898, 54., 0., 0., t);
  label_22720:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 57.01) {
      goto label_22721;
    }
    goto label_22722;
  label_22721:
    decay0_nucltransK(prng_, event_, 0.541, 0.035, 7.7e-3, 0., tclev, thlev, tdlev);
    goto label_17310;
  label_22722:
    decay0_nucltransK(prng_, event_, 0.135, 0.035, 3.5e-1, 0., tclev, thlev, tdlev);
    goto label_21370;
  label_21370:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 96.64) {
      goto label_21371;
    }
    goto label_21372;
  label_21371:
    decay0_nucltransK(prng_, event_, 0.405, 0.035, 1.8e-2, 0., tclev, thlev, tdlev);
    goto label_17310;
  label_21372:
    decay0_nucltransK(prng_, event_, 0.217, 0.035, 1.2e-1, 0., tclev, thlev, tdlev);
    goto label_19200;
  label_1920:
    decay0_beta(prng_, event_, 2.250, 54., 0., 0., t);
  label_19200:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 94.36) {
      goto label_19201;
    }
    goto label_19202;
  label_19201:
    decay0_nucltransK(prng_, event_, 1.073, 0.035, 1.9e-3, 0.1e-4, tclev, thlev, tdlev);
    goto label_84700;
  label_19202:
    decay0_nucltransK(prng_, event_, 0.188, 0.035, 1.7e-1, 0., tclev, thlev, tdlev);
    goto label_17310;
  label_1731:
    decay0_beta(prng_, event_, 2.439, 54., 0., 0., t);
  label_17310:
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 0.884, 0.035, 2.2e-3, 0., tclev, thlev, tdlev);
    goto label_84700;
  label_16140:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 50.83) {
      goto label_16141;
    }
    goto label_16142;
  label_16141:
    decay0_nucltransK(prng_, event_, 1.614, 0.035, 3.0e-4, 0.5e-4, tclev, thlev, tdlev);
    return;
  label_16142:
    decay0_nucltransK(prng_, event_, 0.767, 0.035, 3.2e-3, 0., tclev, thlev, tdlev);
    goto label_84700;
  label_84700:
    thlev = 1.9e-12;
    decay0_nucltransK(prng_, event_, 0.847, 0.035, 2.4e-3, 0., tclev, thlev, tdlev);
    return;
  }
  // end of I134.f

} // end of namespace bxdecay0

// end of I134.cc
// Local Variables: --
// mode: c++ --
// End: --
