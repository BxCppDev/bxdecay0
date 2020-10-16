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
#include <bxdecay0/Te133m.h>

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

  void Te133m(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_)
  {
    double t;
    double tdlev;
    double p;
    double pbeta;
    double pdecay;
    double tclev;
    double thlev = 0.0;
    double thnuc;
    // Model for scheme of Te133m decay (S.Rab, Nucl. Data Sheets
    // 75(1995)491
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 18.12.2003.
    thnuc  = 3324.;
    tdnuc_ = tcnuc_ - thnuc / std::log(2.) * std::log(prng_());
    tclev  = 0.;
    pdecay = 100. * prng_();
    // 17.5% IT to 133Te(g.s.)
    if (pdecay <= 17.5) {
      ;
      decay0_nucltransK(prng_, event_, 0.334, 0.033, 1.431, 0., tclev, thlev, tdlev);
      return;
    };
    // 82.5% beta decay to 133I
    pbeta = 100. * prng_();
    if (pbeta <= 1.77) {
      goto label_3051;
    }
    if (pbeta <= 2.70) {
      goto label_3029;
    }
    if (pbeta <= 3.03) {
      goto label_2975;
    }
    if (pbeta <= 3.16) {
      goto label_2968;
    }
    if (pbeta <= 4.25) {
      goto label_2881;
    }
    if (pbeta <= 5.22) {
      goto label_2826;
    }
    if (pbeta <= 6.02) {
      goto label_2808;
    }
    if (pbeta <= 7.59) {
      goto label_2784;
    }
    if (pbeta <= 10.97) {
      goto label_2686;
    }
    if (pbeta <= 31.35) {
      goto label_2596;
    }
    if (pbeta <= 36.78) {
      goto label_2556;
    }
    if (pbeta <= 37.87) {
      goto label_2516;
    }
    if (pbeta <= 39.00) {
      goto label_2506;
    }
    if (pbeta <= 41.05) {
      goto label_2500;
    }
    if (pbeta <= 41.77) {
      goto label_2483;
    }
    if (pbeta <= 45.63) {
      goto label_2467;
    }
    if (pbeta <= 46.96) {
      goto label_2445;
    }
    if (pbeta <= 47.36) {
      goto label_2427;
    }
    if (pbeta <= 48.10) {
      goto label_2419;
    }
    if (pbeta <= 55.22) {
      goto label_2372;
    }
    if (pbeta <= 56.31) {
      goto label_2262;
    }
    if (pbeta <= 57.64) {
      goto label_2249;
    }
    if (pbeta <= 59.21) {
      goto label_2212;
    }
    if (pbeta <= 61.14) {
      goto label_2142;
    }
    if (pbeta <= 63.07) {
      goto label_2049;
    }
    if (pbeta <= 66.21) {
      goto label_2005;
    }
    if (pbeta <= 72.72) {
      goto label_1991;
    }
    if (pbeta <= 73.32) {
      goto label_1975;
    }
    if (pbeta <= 74.41) {
      goto label_1943;
    }
    if (pbeta <= 78.03) {
      goto label_1886;
    }
    if (pbeta <= 86.59) {
      goto label_1777;
    }
    if (pbeta <= 88.28) {
      goto label_1647;
    }
    if (pbeta <= 91.06) {
      goto label_1560;
    }
    if (pbeta <= 91.66) {
      goto label_1516;
    }
    if (pbeta <= 92.87) {
      goto label_1455;
    }
    if (pbeta <= 93.96) {
      goto label_915;
    }
    if (pbeta <= 95.17) {
      goto label_913;
    }
    goto label_10000;
  label_3051:
    decay0_beta(prng_, event_, 0.203, 53., 0., 0., t);
    ////    label_30510  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 21.62) {
      goto label_30511;
    }
    if (p <= 29.05) {
      goto label_30512;
    }
    goto label_30513;
  label_30511:
    decay0_nucltransK(prng_, event_, 3.051, 0.033, 2.0e-5, 18.1e-4, tclev, thlev, tdlev);
    return;
  label_30512:
    decay0_nucltransK(prng_, event_, 1.405, 0.033, 3.5e-4, 0.3e-4, tclev, thlev, tdlev);
    goto label_16470;
  label_30513:
    decay0_nucltransK(prng_, event_, 0.535, 0.033, 8.0e-3, 0., tclev, thlev, tdlev);
    goto label_25160;
  label_3029:
    decay0_beta(prng_, event_, 0.225, 53., 0., 0., t);
    ////    label_30290  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 35.90) {
      goto label_30291;
    }
    if (p <= 78.21) {
      goto label_30292;
    }
    goto label_30293;
  label_30291:
    decay0_nucltransK(prng_, event_, 1.574, 0.033, 2.6e-4, 0.7e-4, tclev, thlev, tdlev);
    goto label_14550;
  label_30292:
    decay0_nucltransK(prng_, event_, 1.252, 0.033, 4.0e-4, 0.2e-4, tclev, thlev, tdlev);
    goto label_17770;
  label_30293:
    decay0_nucltransK(prng_, event_, 1.054, 0.033, 7.0e-4, 0., tclev, thlev, tdlev);
    goto label_19750;
  label_2975:
    decay0_beta(prng_, event_, 0.279, 53., 0., 0., t);
    ////    label_29750  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 31.25) {
      goto label_29751;
    }
    goto label_29752;
  label_29751:
    decay0_nucltransK(prng_, event_, 2.062, 0.033, 1.4e-4, 4.8e-4, tclev, thlev, tdlev);
    goto label_91300;
  label_29752:
    decay0_nucltransK(prng_, event_, 1.198, 0.033, 5.0e-4, 0.1e-4, tclev, thlev, tdlev);
    goto label_17770;
  label_2968:
    decay0_beta(prng_, event_, 0.286, 53., 0., 0., t);
    ////    label_29680  :
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 2.968, 0.033, 8.0e-5, 15.1e-4, tclev, thlev, tdlev);
    return;
  label_2881:
    decay0_beta(prng_, event_, 0.373, 53., 0., 0., t);
    ////    label_28810  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 17.89) {
      goto label_28811;
    }
    if (p <= 47.36) {
      goto label_28812;
    }
    if (p <= 76.83) {
      goto label_28813;
    }
    goto label_28814;
  label_28811:
    decay0_nucltransK(prng_, event_, 1.968, 0.033, 1.7e-4, 3.2e-4, tclev, thlev, tdlev);
    goto label_91300;
  label_28812:
    decay0_nucltransK(prng_, event_, 0.890, 0.033, 3.1e-3, 0., tclev, thlev, tdlev);
    goto label_19910;
  label_28813:
    decay0_nucltransK(prng_, event_, 0.632, 0.033, 7.0e-3, 0., tclev, thlev, tdlev);
    goto label_22490;
  label_28814:
    decay0_nucltransK(prng_, event_, 0.285, 0.033, 5.0e-2, 0., tclev, thlev, tdlev);
    goto label_25960;
  label_2826:
    decay0_beta(prng_, event_, 0.428, 53., 0., 0., t);
    ////    label_28260  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 16.10) {
      goto label_28261;
    }
    if (p <= 23.00) {
      goto label_28262;
    }
    if (p <= 55.18) {
      goto label_28263;
    }
    if (p <= 67.82) {
      goto label_28264;
    }
    goto label_28265;
  label_28261:
    decay0_nucltransK(prng_, event_, 2.826, 0.033, 9.0e-5, 13.7e-4, tclev, thlev, tdlev);
    return;
  label_28262:
    decay0_nucltransK(prng_, event_, 1.914, 0.033, 1.8e-4, 2.7e-4, tclev, thlev, tdlev);
    goto label_91300;
  label_28263:
    decay0_nucltransK(prng_, event_, 1.372, 0.033, 3.5e-4, 0.3e-4, tclev, thlev, tdlev);
    goto label_14550;
  label_28264:
    decay0_nucltransK(prng_, event_, 0.852, 0.033, 1.0e-3, 0., tclev, thlev, tdlev);
    goto label_19750;
  label_28265:
    decay0_nucltransK(prng_, event_, 0.326, 0.033, 3.6e-2, 0., tclev, thlev, tdlev);
    goto label_25000;
  label_2808:
    decay0_beta(prng_, event_, 0.446, 53., 0., 0., t);
    ////    label_28080  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 16.42) {
      goto label_28081;
    }
    if (p <= 58.21) {
      goto label_28082;
    }
    goto label_28083;
  label_28081:
    decay0_nucltransK(prng_, event_, 1.104, 0.033, 6.0e-4, 0., tclev, thlev, tdlev);
    goto label_17040;
  label_28082:
    decay0_nucltransK(prng_, event_, 0.308, 0.033, 1.0e-2, 0., tclev, thlev, tdlev);
    goto label_25000;
  label_28083:
    decay0_nucltransK(prng_, event_, 0.251, 0.033, 7.5e-2, 0., tclev, thlev, tdlev);
    goto label_25560;
  label_2784:
    decay0_beta(prng_, event_, 0.470, 53., 0., 0., t);
    ////    label_27840  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 42.97) {
      goto label_27841;
    }
    if (p <= 94.53) {
      goto label_27842;
    }
    goto label_27843;
  label_27841:
    decay0_nucltransK(prng_, event_, 1.871, 0.033, 1.8e-4, 2.2e-4, tclev, thlev, tdlev);
    goto label_91300;
  label_27842:
    decay0_nucltransK(prng_, event_, 1.008, 0.033, 7.0e-4, 0., tclev, thlev, tdlev);
    goto label_17770;
  label_27843:
    decay0_nucltransK(prng_, event_, 0.734, 0.033, 1.4e-3, 0., tclev, thlev, tdlev);
    goto label_20490;
  label_2686:
    decay0_beta(prng_, event_, 0.568, 53., 0., 0., t);
    ////    label_26860  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 23.49) {
      goto label_26861;
    }
    if (p <= 62.64) {
      goto label_26862;
    }
    if (p <= 70.47) {
      goto label_26863;
    }
    if (p <= 74.38) {
      goto label_26864;
    }
    if (p <= 88.26) {
      goto label_26865;
    }
    goto label_26866;
  label_26861:
    decay0_nucltransK(prng_, event_, 1.773, 0.033, 1.9e-4, 1.4e-4, tclev, thlev, tdlev);
    goto label_91300;
  label_26862:
    decay0_nucltransK(prng_, event_, 0.801, 0.033, 1.1e-3, 0., tclev, thlev, tdlev);
    goto label_18860;
  label_26863:
    decay0_nucltransK(prng_, event_, 0.637, 0.033, 1.7e-3, 0., tclev, thlev, tdlev);
    goto label_20490;
  label_26864:
    decay0_nucltransK(prng_, event_, 0.475, 0.033, 3.5e-3, 0., tclev, thlev, tdlev);
    goto label_22120;
  label_26865:
    decay0_nucltransK(prng_, event_, 0.314, 0.033, 1.0e-2, 0., tclev, thlev, tdlev);
    goto label_23720;
  label_26866:
    decay0_nucltransK(prng_, event_, 0.241, 0.033, 2.0e-2, 0., tclev, thlev, tdlev);
    goto label_24450;
  label_2596:
    decay0_beta(prng_, event_, 0.658, 53., 0., 0., t);
  label_25960:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 24.04) {
      goto label_25961;
    }
    if (p <= 27.23) {
      goto label_25962;
    }
    if (p <= 31.05) {
      goto label_25963;
    }
    if (p <= 37.13) {
      goto label_25964;
    }
    if (p <= 41.94) {
      goto label_25965;
    }
    if (p <= 42.92) {
      goto label_25966;
    }
    if (p <= 47.09) {
      goto label_25967;
    }
    if (p <= 61.18) {
      goto label_25968;
    }
    if (p <= 64.71) {
      goto label_25969;
    }
    if (p <= 67.61) {
      goto label_25970;
    }
    if (p <= 74.97) {
      goto label_25971;
    }
    if (p <= 75.95) {
      goto label_25972;
    }
    if (p <= 79.77) {
      goto label_25973;
    }
    if (p <= 99.02) {
      goto label_25974;
    }
    goto label_25975;
  label_25961:
    decay0_nucltransK(prng_, event_, 1.683, 0.033, 2.5e-4, 1.0e-4, tclev, thlev, tdlev);
    goto label_91300;
  label_25962:
    decay0_nucltransK(prng_, event_, 1.080, 0.033, 6.0e-4, 0., tclev, thlev, tdlev);
    goto label_15160;
  label_25963:
    decay0_nucltransK(prng_, event_, 0.949, 0.033, 8.0e-4, 0., tclev, thlev, tdlev);
    goto label_16470;
  label_25964:
    decay0_nucltransK(prng_, event_, 0.891, 0.033, 9.0e-4, 0., tclev, thlev, tdlev);
    goto label_17040;
  label_25965:
    decay0_nucltransK(prng_, event_, 0.889, 0.033, 9.0e-4, 0., tclev, thlev, tdlev);
    goto label_17070;
  label_25966:
    decay0_nucltransK(prng_, event_, 0.819, 0.033, 3.7e-3, 0., tclev, thlev, tdlev);
    goto label_17770;
  label_25967:
    decay0_nucltransK(prng_, event_, 0.710, 0.033, 1.4e-3, 0., tclev, thlev, tdlev);
    goto label_18860;
  label_25968:
    decay0_nucltransK(prng_, event_, 0.703, 0.033, 1.4e-3, 0., tclev, thlev, tdlev);
    goto label_18930;
  label_25969:
    decay0_nucltransK(prng_, event_, 0.653, 0.033, 1.7e-3, 0., tclev, thlev, tdlev);
    goto label_19430;
  label_25970:
    decay0_nucltransK(prng_, event_, 0.621, 0.033, 1.8e-3, 0., tclev, thlev, tdlev);
    goto label_19750;
  label_25971:
    decay0_nucltransK(prng_, event_, 0.605, 0.033, 7.7e-3, 0., tclev, thlev, tdlev);
    goto label_19910;
  label_25972:
    decay0_nucltransK(prng_, event_, 0.384, 0.033, 2.5e-2, 0., tclev, thlev, tdlev);
    goto label_22120;
  label_25973:
    decay0_nucltransK(prng_, event_, 0.347, 0.033, 3.0e-2, 0., tclev, thlev, tdlev);
    goto label_22490;
  label_25974:
    decay0_nucltransK(prng_, event_, 0.334, 0.033, 3.4e-2, 0., tclev, thlev, tdlev);
    goto label_22620;
  label_25975:
    decay0_nucltransK(prng_, event_, 0.224, 0.033, 1.0e-1, 0., tclev, thlev, tdlev);
    goto label_23720;
  label_2556:
    decay0_beta(prng_, event_, 0.698, 53., 0., 0., t);
  label_25560:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 6.82) {
      goto label_25561;
    }
    if (p <= 15.08) {
      goto label_25562;
    }
    if (p <= 26.44) {
      goto label_25563;
    }
    if (p <= 63.01) {
      goto label_25564;
    }
    if (p <= 65.28) {
      goto label_25565;
    }
    if (p <= 75.61) {
      goto label_25566;
    }
    if (p <= 77.06) {
      goto label_25567;
    }
    if (p <= 91.94) {
      goto label_25568;
    }
    if (p <= 96.49) {
      goto label_25569;
    }
    goto label_25570;
  label_25561:
    decay0_nucltransK(prng_, event_, 1.644, 0.033, 2.6e-4, 0.9e-4, tclev, thlev, tdlev);
    goto label_91300;
  label_25562:
    decay0_nucltransK(prng_, event_, 0.996, 0.033, 7.0e-4, 0., tclev, thlev, tdlev);
    goto label_15600;
  label_25563:
    decay0_nucltransK(prng_, event_, 0.827, 0.033, 3.7e-3, 0., tclev, thlev, tdlev);
    goto label_17290;
  label_25564:
    decay0_nucltransK(prng_, event_, 0.780, 0.033, 4.2e-3, 0., tclev, thlev, tdlev);
    goto label_17770;
  label_25565:
    decay0_nucltransK(prng_, event_, 0.663, 0.033, 6.0e-3, 0., tclev, thlev, tdlev);
    goto label_18930;
  label_25566:
    decay0_nucltransK(prng_, event_, 0.581, 0.033, 8.2e-3, 0., tclev, thlev, tdlev);
    goto label_19750;
  label_25567:
    decay0_nucltransK(prng_, event_, 0.565, 0.033, 8.3e-3, 0., tclev, thlev, tdlev);
    goto label_19910;
  label_25568:
    decay0_nucltransK(prng_, event_, 0.344, 0.033, 3.2e-2, 0., tclev, thlev, tdlev);
    goto label_22120;
  label_25569:
    decay0_nucltransK(prng_, event_, 0.295, 0.033, 4.8e-2, 0., tclev, thlev, tdlev);
    goto label_22620;
  label_25570:
    decay0_nucltransK(prng_, event_, 0.185, 0.033, 1.6e-1, 0., tclev, thlev, tdlev);
    goto label_23720;
  label_2516:
    decay0_beta(prng_, event_, 0.738, 53., 0., 0., t);
  label_25160:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 30.50) {
      goto label_25161;
    }
    if (p <= 72.00) {
      goto label_25162;
    }
    if (p <= 86.00) {
      goto label_25163;
    }
    goto label_25164;
  label_25161:
    decay0_nucltransK(prng_, event_, 0.740, 0.033, 4.8e-3, 0., tclev, thlev, tdlev);
    goto label_17770;
  label_25162:
    decay0_nucltransK(prng_, event_, 0.719, 0.033, 4.9e-3, 0., tclev, thlev, tdlev);
    goto label_17970;
  label_25163:
    decay0_nucltransK(prng_, event_, 0.623, 0.033, 6.0e-3, 0., tclev, thlev, tdlev);
    goto label_18930;
  label_25164:
    decay0_nucltransK(prng_, event_, 0.526, 0.033, 1.1e-2, 0., tclev, thlev, tdlev);
    goto label_19910;
  label_2506:
    decay0_beta(prng_, event_, 0.748, 53., 0., 0., t);
    ////    label_25060  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 64.89) {
      goto label_25061;
    }
    goto label_25062;
  label_25061:
    decay0_nucltransK(prng_, event_, 0.945, 0.033, 2.6e-3, 0., tclev, thlev, tdlev);
    goto label_15600;
  label_25062:
    decay0_nucltransK(prng_, event_, 0.244, 0.033, 7.5e-2, 0., tclev, thlev, tdlev);
    goto label_22620;
  label_2500:
    decay0_beta(prng_, event_, 0.754, 53., 0., 0., t);
  label_25000:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 62.53) {
      goto label_25001;
    }
    if (p <= 67.31) {
      goto label_25002;
    }
    if (p <= 72.09) {
      goto label_25003;
    }
    if (p <= 84.25) {
      goto label_25004;
    }
    if (p <= 91.63) {
      goto label_25005;
    }
    goto label_25006;
  label_25001:
    decay0_nucltransK(prng_, event_, 1.588, 0.033, 7.0e-4, 1.1e-4, tclev, thlev, tdlev);
    goto label_91300;
  label_25002:
    decay0_nucltransK(prng_, event_, 0.796, 0.033, 1.1e-3, 0., tclev, thlev, tdlev);
    goto label_17040;
  label_25003:
    decay0_nucltransK(prng_, event_, 0.793, 0.033, 1.1e-3, 0., tclev, thlev, tdlev);
    goto label_17070;
  label_25004:
    decay0_nucltransK(prng_, event_, 0.724, 0.033, 5.0e-3, 0., tclev, thlev, tdlev);
    goto label_17770;
  label_25005:
    decay0_nucltransK(prng_, event_, 0.607, 0.033, 2.0e-3, 0., tclev, thlev, tdlev);
    goto label_18930;
  label_25006:
    decay0_nucltransK(prng_, event_, 0.495, 0.033, 3.0e-3, 0., tclev, thlev, tdlev);
    goto label_20050;
  label_2483:
    decay0_beta(prng_, event_, 0.771, 53., 0., 0., t);
    ////    label_24830  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 11.66) {
      goto label_24831;
    }
    if (p <= 31.09) {
      goto label_24832;
    }
    goto label_24833;
  label_24831:
    decay0_nucltransK(prng_, event_, 2.483, 0.033, 2.2e-4, 4.5e-4, tclev, thlev, tdlev);
    return;
  label_24832:
    decay0_nucltransK(prng_, event_, 1.570, 0.033, 7.0e-4, 1.1e-4, tclev, thlev, tdlev);
    goto label_91300;
  label_24833:
    decay0_nucltransK(prng_, event_, 1.174, 0.033, 1.5e-3, 0.3e-4, tclev, thlev, tdlev);
    goto label_13070;
  label_2467:
    decay0_beta(prng_, event_, 0.787, 53., 0., 0., t);
    ////    label_24670  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 5.30) {
      goto label_24671;
    }
    if (p <= 27.73) {
      goto label_24672;
    }
    if (p <= 51.72) {
      goto label_24673;
    }
    goto label_24674;
  label_24671:
    decay0_nucltransK(prng_, event_, 1.552, 0.033, 7.0e-4, 1.1e-4, tclev, thlev, tdlev);
    goto label_91500;
  label_24672:
    decay0_nucltransK(prng_, event_, 0.574, 0.033, 8.5e-3, 0., tclev, thlev, tdlev);
    goto label_18930;
  label_24673:
    decay0_nucltransK(prng_, event_, 0.493, 0.033, 1.2e-2, 0., tclev, thlev, tdlev);
    goto label_19750;
  label_24674:
    decay0_nucltransK(prng_, event_, 0.462, 0.033, 1.4e-2, 0., tclev, thlev, tdlev);
    goto label_20050;
  label_2445:
    decay0_beta(prng_, event_, 0.809, 53., 0., 0., t);
  label_24450:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 75.00) {
      goto label_24451;
    }
    goto label_24452;
  label_24451:
    decay0_nucltransK(prng_, event_, 0.885, 0.033, 9.5e-4, 0., tclev, thlev, tdlev);
    goto label_15600;
  label_24452:
    decay0_nucltransK(prng_, event_, 0.629, 0.033, 7.0e-3, 0., tclev, thlev, tdlev);
    goto label_18170;
  label_2427:
    decay0_beta(prng_, event_, 0.827, 53., 0., 0., t);
    ////    label_24270  :
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 0.178, 0.033, 1.7e-1, 0., tclev, thlev, tdlev);
    goto label_22490;
  label_2419:
    decay0_beta(prng_, event_, 0.835, 53., 0., 0., t);
    ////    label_24190  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 45.91) {
      goto label_24191;
    }
    if (p <= 63.94) {
      goto label_24192;
    }
    if (p <= 81.97) {
      goto label_24193;
    }
    goto label_24194;
  label_24191:
    decay0_nucltransK(prng_, event_, 1.506, 0.033, 9.0e-4, 0.9e-4, tclev, thlev, tdlev);
    goto label_91300;
  label_24192:
    decay0_nucltransK(prng_, event_, 0.859, 0.033, 2.9e-3, 0., tclev, thlev, tdlev);
    goto label_15600;
  label_24193:
    decay0_nucltransK(prng_, event_, 0.415, 0.033, 2.0e-2, 0., tclev, thlev, tdlev);
    goto label_20050;
  label_24194:
    decay0_nucltransK(prng_, event_, 0.158, 0.033, 2.5e-1, 0., tclev, thlev, tdlev);
    goto label_22620;
  label_2372:
    decay0_beta(prng_, event_, 0.882, 53., 0., 0., t);
  label_23720:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 2.55) {
      goto label_23721;
    }
    if (p <= 4.20) {
      goto label_23722;
    }
    if (p <= 5.85) {
      goto label_23723;
    }
    if (p <= 19.06) {
      goto label_23724;
    }
    if (p <= 37.37) {
      goto label_23725;
    }
    if (p <= 39.02) {
      goto label_23726;
    }
    if (p <= 53.13) {
      goto label_23727;
    }
    if (p <= 86.29) {
      goto label_23728;
    }
    if (p <= 97.10) {
      goto label_23729;
    }
    if (p <= 98.75) {
      goto label_23730;
    }
    goto label_23731;
  label_23721:
    decay0_nucltransK(prng_, event_, 1.459, 0.033, 2.5e-4, 0.5e-4, tclev, thlev, tdlev);
    goto label_91300;
  label_23722:
    decay0_nucltransK(prng_, event_, 1.456, 0.033, 2.5e-4, 0.5e-4, tclev, thlev, tdlev);
    goto label_91500;
  label_23723:
    decay0_nucltransK(prng_, event_, 0.724, 0.033, 1.3e-2, 0., tclev, thlev, tdlev);
    goto label_16470;
  label_23724:
    decay0_nucltransK(prng_, event_, 0.642, 0.033, 5.0e-3, 0., tclev, thlev, tdlev);
    goto label_17290;
  label_23725:
    decay0_nucltransK(prng_, event_, 0.574, 0.033, 9.0e-3, 0., tclev, thlev, tdlev);
    goto label_17970;
  label_23726:
    decay0_nucltransK(prng_, event_, 0.555, 0.033, 7.0e-3, 0., tclev, thlev, tdlev);
    goto label_18170;
  label_23727:
    decay0_nucltransK(prng_, event_, 0.479, 0.033, 3.5e-3, 0., tclev, thlev, tdlev);
    goto label_18930;
  label_23728:
    decay0_nucltransK(prng_, event_, 0.429, 0.033, 4.5e-3, 0., tclev, thlev, tdlev);
    goto label_19430;
  label_23729:
    decay0_nucltransK(prng_, event_, 0.397, 0.033, 5.2e-3, 0., tclev, thlev, tdlev);
    goto label_19750;
  label_23730:
    decay0_nucltransK(prng_, event_, 0.322, 0.033, 9.0e-3, 0., tclev, thlev, tdlev);
    goto label_20490;
  label_23731:
    decay0_nucltransK(prng_, event_, 0.110, 0.033, 1.6e-1, 0., tclev, thlev, tdlev);
    goto label_22620;
  label_2262:
    decay0_beta(prng_, event_, 0.992, 53., 0., 0., t);
  label_22620:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 29.62) {
      goto label_22621;
    }
    if (p <= 47.12) {
      goto label_22622;
    }
    if (p <= 52.69) {
      goto label_22623;
    }
    if (p <= 93.44) {
      goto label_22624;
    }
    if (p <= 95.63) {
      goto label_22625;
    }
    goto label_22626;
  label_22621:
    decay0_nucltransK(prng_, event_, 1.349, 0.033, 5.0e-4, 0.3e-4, tclev, thlev, tdlev);
    goto label_91300;
  label_22622:
    decay0_nucltransK(prng_, event_, 0.532, 0.033, 1.1e-2, 0., tclev, thlev, tdlev);
    goto label_17290;
  label_22623:
    decay0_nucltransK(prng_, event_, 0.464, 0.033, 3.5e-3, 0., tclev, thlev, tdlev);
    goto label_17970;
  label_22624:
    decay0_nucltransK(prng_, event_, 0.445, 0.033, 1.6e-2, 0., tclev, thlev, tdlev);
    goto label_18170;
  label_22625:
    decay0_nucltransK(prng_, event_, 0.369, 0.033, 6.0e-3, 0., tclev, thlev, tdlev);
    goto label_18930;
  label_22626:
    decay0_nucltransK(prng_, event_, 0.319, 0.033, 4.0e-2, 0., tclev, thlev, tdlev);
    goto label_19430;
  label_2249:
    decay0_beta(prng_, event_, 1.005, 53., 0., 0., t);
  label_22490:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 34.30) {
      goto label_22491;
    }
    if (p <= 54.96) {
      goto label_22492;
    }
    if (p <= 81.82) {
      goto label_22493;
    }
    goto label_22494;
  label_22491:
    decay0_nucltransK(prng_, event_, 0.472, 0.033, 1.3e-2, 0., tclev, thlev, tdlev);
    goto label_17770;
  label_22492:
    decay0_nucltransK(prng_, event_, 0.363, 0.033, 7.0e-3, 0., tclev, thlev, tdlev);
    goto label_18860;
  label_22493:
    decay0_nucltransK(prng_, event_, 0.355, 0.033, 7.0e-3, 0., tclev, thlev, tdlev);
    goto label_18930;
  label_22494:
    decay0_nucltransK(prng_, event_, 0.258, 0.033, 6.5e-2, 0., tclev, thlev, tdlev);
    goto label_19910;
  label_2212:
    decay0_beta(prng_, event_, 1.042, 53., 0., 0., t);
  label_22120:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 7.42) {
      goto label_22121;
    }
    if (p <= 60.70) {
      goto label_22122;
    }
    if (p <= 89.52) {
      goto label_22123;
    }
    goto label_22124;
  label_22121:
    decay0_nucltransK(prng_, event_, 1.299, 0.033, 4.0e-4, 0.3e-4, tclev, thlev, tdlev);
    goto label_91300;
  label_22122:
    decay0_nucltransK(prng_, event_, 0.435, 0.033, 1.7e-2, 0., tclev, thlev, tdlev);
    goto label_17770;
  label_22123:
    decay0_nucltransK(prng_, event_, 0.413, 0.033, 1.6e-2, 0., tclev, thlev, tdlev);
    goto label_17990;
  label_22124:
    decay0_nucltransK(prng_, event_, 0.221, 0.033, 1.0e-1, 0., tclev, thlev, tdlev);
    goto label_19910;
  label_2142:
    decay0_beta(prng_, event_, 1.112, 53., 0., 0., t);
    ////    label_21420  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 12.99) {
      goto label_21421;
    }
    if (p <= 23.03) {
      goto label_21422;
    }
    if (p <= 24.98) {
      goto label_21423;
    }
    if (p <= 63.96) {
      goto label_21424;
    }
    if (p <= 72.82) {
      goto label_21425;
    }
    goto label_21426;
  label_21421:
    decay0_nucltransK(prng_, event_, 1.230, 0.033, 1.5e-3, 0.4e-4, tclev, thlev, tdlev);
    goto label_91300;
  label_21422:
    decay0_nucltransK(prng_, event_, 1.228, 0.033, 1.5e-3, 0.4e-4, tclev, thlev, tdlev);
    goto label_91500;
  label_21423:
    decay0_nucltransK(prng_, event_, 0.249, 0.033, 7.5e-2, 0., tclev, thlev, tdlev);
    goto label_18930;
  label_21424:
    decay0_nucltransK(prng_, event_, 0.151, 0.033, 1.8e-2, 0., tclev, thlev, tdlev);
    goto label_19910;
  label_21425:
    decay0_nucltransK(prng_, event_, 0.137, 0.033, 4.0e-1, 0., tclev, thlev, tdlev);
    goto label_20050;
  label_21426:
    decay0_nucltransK(prng_, event_, 0.092, 0.033, 1.3, 0., tclev, thlev, tdlev);
    goto label_20490;
  label_2049:
    decay0_beta(prng_, event_, 1.205, 53., 0., 0., t);
  label_20490:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 50.00) {
      goto label_20491;
    }
    if (p <= 61.48) {
      goto label_20492;
    }
    if (p <= 75.00) {
      goto label_20493;
    }
    if (p <= 90.98) {
      goto label_20494;
    }
    goto label_20495;
  label_20491:
    decay0_nucltransK(prng_, event_, 2.049, 0.033, 1.5e-4, 2.2e-4, tclev, thlev, tdlev);
    return;
  label_20492:
    decay0_nucltransK(prng_, event_, 1.137, 0.033, 1.7e-3, 0.3e-4, tclev, thlev, tdlev);
    goto label_91300;
  label_20493:
    decay0_nucltransK(prng_, event_, 1.135, 0.033, 1.7e-3, 0.3e-4, tclev, thlev, tdlev);
    goto label_91500;
  label_20494:
    decay0_nucltransK(prng_, event_, 0.743, 0.033, 3.5e-3, 0., tclev, thlev, tdlev);
    goto label_13070;
  label_20495:
    decay0_nucltransK(prng_, event_, 0.346, 0.033, 3.0e-2, 0., tclev, thlev, tdlev);
    goto label_17040;
  label_2005:
    decay0_beta(prng_, event_, 1.249, 53., 0., 0., t);
  label_20050:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 72.63) {
      goto label_20051;
    }
    if (p <= 72.86) {
      goto label_20052;
    }
    if (p <= 75.21) {
      goto label_20053;
    }
    if (p <= 95.30) {
      goto label_20054;
    }
    if (p <= 97.65) {
      goto label_20055;
    }
    goto label_20056;
  label_20051:
    decay0_nucltransK(prng_, event_, 2.005, 0.033, 8.0e-4, 2.3e-4, tclev, thlev, tdlev);
    return;
  label_20052:
    decay0_nucltransK(prng_, event_, 1.693, 0.033, 4.5e-4, 0.7e-4, tclev, thlev, tdlev);
    goto label_31200;
  label_20053:
    decay0_nucltransK(prng_, event_, 1.091, 0.033, 2.0e-3, 0., tclev, thlev, tdlev);
    goto label_91500;
  label_20054:
    decay0_nucltransK(prng_, event_, 0.698, 0.033, 5.5e-3, 0., tclev, thlev, tdlev);
    goto label_13070;
  label_20055:
    decay0_nucltransK(prng_, event_, 0.119, 0.033, 5.0e-1, 0., tclev, thlev, tdlev);
    goto label_18860;
  label_20056:
    decay0_nucltransK(prng_, event_, 0.112, 0.033, 5.5e-1, 0., tclev, thlev, tdlev);
    goto label_18930;
  label_1991:
    decay0_beta(prng_, event_, 1.263, 53., 0., 0., t);
  label_19910:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 1.96) {
      goto label_19911;
    }
    if (p <= 91.68) {
      goto label_19912;
    }
    if (p <= 98.47) {
      goto label_19913;
    }
    goto label_19914;
  label_19911:
    decay0_nucltransK(prng_, event_, 1.078, 0.033, 6.0e-4, 0., tclev, thlev, tdlev);
    goto label_91300;
  label_19912:
    decay0_nucltransK(prng_, event_, 0.262, 0.033, 6.5e-2, 0., tclev, thlev, tdlev);
    goto label_17290;
  label_19913:
    decay0_nucltransK(prng_, event_, 0.193, 0.033, 3.5e-2, 0., tclev, thlev, tdlev);
    goto label_17970;
  label_19914:
    decay0_nucltransK(prng_, event_, 0.098, 0.033, 2.2e-1, 0., tclev, thlev, tdlev);
    goto label_18930;
  label_1975:
    decay0_beta(prng_, event_, 1.279, 53., 0., 0., t);
  label_19750:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 1.13) {
      goto label_19751;
    }
    if (p <= 49.41) {
      goto label_19752;
    }
    if (p <= 51.15) {
      goto label_19753;
    }
    if (p <= 59.29) {
      goto label_19754;
    }
    if (p <= 62.49) {
      goto label_19755;
    }
    if (p <= 67.43) {
      goto label_19756;
    }
    if (p <= 73.83) {
      goto label_19757;
    }
    goto label_19758;
  label_19751:
    decay0_nucltransK(prng_, event_, 1.975, 0.033, 4.0e-4, 1.9e-4, tclev, thlev, tdlev);
    return;
  label_19752:
    decay0_nucltransK(prng_, event_, 1.062, 0.033, 2.0e-3, 0.1e-4, tclev, thlev, tdlev);
    goto label_91300;
  label_19753:
    decay0_nucltransK(prng_, event_, 1.060, 0.033, 2.0e-3, 0.1e-4, tclev, thlev, tdlev);
    goto label_91500;
  label_19754:
    decay0_nucltransK(prng_, event_, 0.520, 0.033, 8.0e-3, 0., tclev, thlev, tdlev);
    goto label_14550;
  label_19755:
    decay0_nucltransK(prng_, event_, 0.458, 0.033, 1.5e-2, 0., tclev, thlev, tdlev);
    goto label_15160;
  label_19756:
    decay0_nucltransK(prng_, event_, 0.198, 0.033, 3.2e-2, 0., tclev, thlev, tdlev);
    goto label_17770;
  label_19757:
    decay0_nucltransK(prng_, event_, 0.177, 0.033, 1.9e-1, 0., tclev, thlev, tdlev);
    goto label_17970;
  label_19758:
    decay0_nucltransK(prng_, event_, 0.082, 0.033, 1.8, 0., tclev, thlev, tdlev);
    goto label_18930;
  label_1943:
    decay0_beta(prng_, event_, 1.311, 53., 0., 0., t);
  label_19430:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 35.36) {
      goto label_19431;
    }
    if (p <= 97.97) {
      goto label_19432;
    }
    goto label_19433;
  label_19431:
    decay0_nucltransK(prng_, event_, 1.030, 0.033, 2.1e-3, 0., tclev, thlev, tdlev);
    goto label_91300;
  label_19432:
    decay0_nucltransK(prng_, event_, 0.213, 0.033, 2.6e-2, 0., tclev, thlev, tdlev);
    goto label_17290;
  label_19433:
    decay0_nucltransK(prng_, event_, 0.050, 0.033, 1.4e+1, 0., tclev, thlev, tdlev);
    goto label_18930;
  label_18930:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 2.13) {
      goto label_18931;
    }
    if (p <= 23.29) {
      goto label_18932;
    }
    if (p <= 92.90) {
      goto label_18933;
    }
    if (p <= 96.02) {
      goto label_18934;
    }
    goto label_18935;
  label_18931:
    decay0_nucltransK(prng_, event_, 1.893, 0.033, 4.0e-4, 1.4e-4, tclev, thlev, tdlev);
    return;
  label_18932:
    decay0_nucltransK(prng_, event_, 0.980, 0.033, 2.5e-3, 0., tclev, thlev, tdlev);
    goto label_91300;
  label_18933:
    decay0_nucltransK(prng_, event_, 0.978, 0.033, 2.5e-3, 0., tclev, thlev, tdlev);
    goto label_91500;
  label_18934:
    decay0_nucltransK(prng_, event_, 0.377, 0.033, 2.5e-2, 0., tclev, thlev, tdlev);
    goto label_15160;
  label_18935:
    decay0_nucltransK(prng_, event_, 0.116, 0.033, 1.5e-1, 0., tclev, thlev, tdlev);
    goto label_17770;
  label_1886:
    decay0_beta(prng_, event_, 1.368, 53., 0., 0., t);
  label_18860:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 18.33) {
      goto label_18861;
    }
    if (p <= 28.52) {
      goto label_18862;
    }
    if (p <= 34.63) {
      goto label_18863;
    }
    if (p <= 36.67) {
      goto label_18864;
    }
    if (p <= 40.74) {
      goto label_18865;
    }
    goto label_18866;
  label_18861:
    decay0_nucltransK(prng_, event_, 1.886, 0.033, 2.0e-4, 1.2e-4, tclev, thlev, tdlev);
    return;
  label_18862:
    decay0_nucltransK(prng_, event_, 0.973, 0.033, 2.5e-3, 0., tclev, thlev, tdlev);
    goto label_91300;
  label_18863:
    decay0_nucltransK(prng_, event_, 0.971, 0.033, 2.5e-3, 0., tclev, thlev, tdlev);
    goto label_91500;
  label_18864:
    decay0_nucltransK(prng_, event_, 0.369, 0.033, 2.6e-2, 0., tclev, thlev, tdlev);
    goto label_15160;
  label_18865:
    decay0_nucltransK(prng_, event_, 0.177, 0.033, 2.0e-1, 0., tclev, thlev, tdlev);
    goto label_17070;
  label_18866:
    decay0_nucltransK(prng_, event_, 0.088, 0.033, 1.4, 0., tclev, thlev, tdlev);
    goto label_17970;
  label_18170:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 52.17) {
      goto label_18171;
    }
    goto label_18172;
  label_18171:
    decay0_nucltransK(prng_, event_, 0.040, 0.033, 3.2e+1, 0., tclev, thlev, tdlev);
    goto label_17770;
  label_18172:
    decay0_nucltransK(prng_, event_, 0.018, 0.005, 2.0e+1, 0., tclev, thlev, tdlev);
    goto label_17990;
  label_17990:
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 0.164, 0.033, 2.5e-1, 0., tclev, thlev, tdlev);
    goto label_16340;
  label_17970:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 3.06) {
      goto label_17971;
    }
    if (p <= 19.90) {
      goto label_17972;
    }
    if (p <= 57.49) {
      goto label_17973;
    }
    if (p <= 65.99) {
      goto label_17974;
    }
    if (p <= 67.86) {
      goto label_17975;
    }
    if (p <= 75.34) {
      goto label_17976;
    }
    goto label_17977;
  label_17971:
    decay0_nucltransK(prng_, event_, 1.797, 0.033, 4.5e-4, 0.9e-4, tclev, thlev, tdlev);
    return;
  label_17972:
    decay0_nucltransK(prng_, event_, 0.885, 0.033, 3.0e-3, 0., tclev, thlev, tdlev);
    goto label_91300;
  label_17973:
    decay0_nucltransK(prng_, event_, 0.883, 0.033, 3.0e-3, 0., tclev, thlev, tdlev);
    goto label_91500;
  label_17974:
    decay0_nucltransK(prng_, event_, 0.343, 0.033, 3.0e-2, 0., tclev, thlev, tdlev);
    goto label_14550;
  label_17975:
    decay0_nucltransK(prng_, event_, 0.281, 0.033, 5.5e-2, 0., tclev, thlev, tdlev);
    goto label_15160;
  label_17976:
    decay0_nucltransK(prng_, event_, 0.151, 0.033, 3.3e-1, 0., tclev, thlev, tdlev);
    goto label_16470;
  label_17977:
    decay0_nucltransK(prng_, event_, 0.021, 0.005, 2.6, 0., tclev, thlev, tdlev);
    goto label_17770;
  label_1777:
    decay0_beta(prng_, event_, 1.477, 53., 0., 0., t);
  label_17770:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 98.61) {
      goto label_17771;
    }
    goto label_17772;
  label_17771:
    decay0_nucltransK(prng_, event_, 0.864, 0.033, 2.5e-3, 0., tclev, thlev, tdlev);
    goto label_91300;
  label_17772:
    decay0_nucltransK(prng_, event_, 0.047, 0.033, 1.7e+1, 0., tclev, thlev, tdlev);
    goto label_17290;
  label_17290:
    thlev = 170.e-9;
    p     = 100. * prng_();
    if (p <= 37.93) {
      goto label_17291;
    }
    goto label_17292;
  label_17291:
    decay0_nucltransK(prng_, event_, 0.169, 0.033, 4.7e-2, 0., tclev, thlev, tdlev);
    goto label_15600;
  label_17292:
    decay0_nucltransK(prng_, event_, 0.095, 0.033, 2.1, 0., tclev, thlev, tdlev);
    goto label_16340;
  label_17070:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 90.91) {
      goto label_17071;
    }
    goto label_17072;
  label_17071:
    decay0_nucltransK(prng_, event_, 0.795, 0.033, 4.0e-3, 0., tclev, thlev, tdlev);
    goto label_91300;
  label_17072:
    decay0_nucltransK(prng_, event_, 0.793, 0.033, 3.0e-3, 0., tclev, thlev, tdlev);
    goto label_91500;
  label_17040:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 52.17) {
      goto label_17041;
    }
    if (p <= 60.14) {
      goto label_17042;
    }
    if (p <= 68.11) {
      goto label_17043;
    }
    goto label_17044;
  label_17041:
    decay0_nucltransK(prng_, event_, 1.704, 0.033, 6.0e-4, 1.4e-4, tclev, thlev, tdlev);
    return;
  label_17042:
    decay0_nucltransK(prng_, event_, 1.392, 0.033, 8.5e-4, 0.2e-4, tclev, thlev, tdlev);
    goto label_31200;
  label_17043:
    decay0_nucltransK(prng_, event_, 0.792, 0.033, 4.0e-3, 0., tclev, thlev, tdlev);
    goto label_91300;
  label_17044:
    decay0_nucltransK(prng_, event_, 0.790, 0.033, 4.0e-3, 0., tclev, thlev, tdlev);
    goto label_91500;
  label_1647:
    decay0_beta(prng_, event_, 1.607, 53., 0., 0., t);
  label_16470:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 9.88) {
      goto label_16471;
    }
    if (p <= 72.34) {
      goto label_16472;
    }
    if (p <= 93.86) {
      goto label_16473;
    }
    goto label_16474;
  label_16471:
    decay0_nucltransK(prng_, event_, 1.646, 0.033, 5.0e-4, 0.6e-4, tclev, thlev, tdlev);
    return;
  label_16472:
    decay0_nucltransK(prng_, event_, 0.734, 0.033, 4.6e-3, 0., tclev, thlev, tdlev);
    goto label_91300;
  label_16473:
    decay0_nucltransK(prng_, event_, 0.732, 0.033, 4.6e-3, 0., tclev, thlev, tdlev);
    goto label_91500;
  label_16474:
    decay0_nucltransK(prng_, event_, 0.087, 0.033, 2.9, 0., tclev, thlev, tdlev);
    goto label_15600;
  label_16340:
    thlev = 9.;
    decay0_nucltransK(prng_, event_, 0.074, 0.033, 2.4e+1, 0., tclev, thlev, tdlev);
    goto label_15600;
  label_1560:
    decay0_beta(prng_, event_, 1.694, 53., 0., 0., t);
  label_15600:
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 0.648, 0.033, 4.6e-3, 0., tclev, thlev, tdlev);
    goto label_91300;
  label_1516:
    decay0_beta(prng_, event_, 1.738, 53., 0., 0., t);
  label_15160:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 78.54) {
      goto label_15161;
    }
    if (p <= 92.15) {
      goto label_15162;
    }
    goto label_15163;
  label_15161:
    decay0_nucltransK(prng_, event_, 1.516, 0.033, 8.0e-4, 0.9e-4, tclev, thlev, tdlev);
    return;
  label_15162:
    decay0_nucltransK(prng_, event_, 1.204, 0.033, 1.1e-3, 0.1e-4, tclev, thlev, tdlev);
    goto label_31200;
  label_15163:
    decay0_nucltransK(prng_, event_, 0.602, 0.033, 8.0e-3, 0., tclev, thlev, tdlev);
    goto label_91500;
  label_1455:
    decay0_beta(prng_, event_, 1.799, 53., 0., 0., t);
  label_14550:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 30.90) {
      goto label_14551;
    }
    if (p <= 87.98) {
      goto label_14552;
    }
    goto label_14553;
  label_14551:
    decay0_nucltransK(prng_, event_, 1.455, 0.033, 1.0e-3, 0.9e-4, tclev, thlev, tdlev);
    return;
  label_14552:
    decay0_nucltransK(prng_, event_, 1.143, 0.033, 1.8e-3, 0.3e-4, tclev, thlev, tdlev);
    goto label_31200;
  label_14553:
    decay0_nucltransK(prng_, event_, 0.540, 0.033, 1.0e-2, 0., tclev, thlev, tdlev);
    goto label_91500;
  label_13070:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 39.00) {
      goto label_13071;
    }
    if (p <= 89.00) {
      goto label_13072;
    }
    goto label_13073;
  label_13071:
    decay0_nucltransK(prng_, event_, 1.307, 0.033, 1.2e-3, 0.5e-4, tclev, thlev, tdlev);
    return;
  label_13072:
    decay0_nucltransK(prng_, event_, 0.995, 0.033, 2.5e-3, 0., tclev, thlev, tdlev);
    goto label_31200;
  label_13073:
    decay0_nucltransK(prng_, event_, 0.392, 0.033, 2.1e-2, 0., tclev, thlev, tdlev);
    goto label_91500;
  label_915:
    decay0_beta(prng_, event_, 2.339, 53., 0., 0., t);
  label_91500:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 99.84) {
      goto label_91501;
    }
    goto label_91502;
  label_91501:
    decay0_nucltransK(prng_, event_, 0.915, 0.033, 2.7e-3, 0., tclev, thlev, tdlev);
    return;
  label_91502:
    decay0_nucltransK(prng_, event_, 0.602, 0.033, 5.0e-3, 0., tclev, thlev, tdlev);
    goto label_31200;
  label_913:
    decay0_beta(prng_, event_, 2.341, 53., 0., 0., t);
  label_91300:
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 0.913, 0.033, 2.1e-3, 0., tclev, thlev, tdlev);
    return;
  label_31200:
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 0.312, 0.033, 4.0e-2, 0., tclev, thlev, tdlev);
    return;
  label_10000:
    decay0_beta(prng_, event_, 3.254, 53., 0., 0., t);
    return;
    return;
  }
  // end of Te133m.f

} // end of namespace bxdecay0

// end of Te133m.cc
// Local Variables: --
// mode: c++ --
// End: --
