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
#include <bxdecay0/I135.h>

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

  void I135(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_)
  {
    double t;
    double tdlev;
    double p;
    double pbeta;
    double tclev;
    double thlev;
    double thnuc;
    // Scheme of I135 decay (Yu.V.Sergeenkov et al., Nucl. Data Sheets
    // 84(1998)115).
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 12.10.2002.
    thnuc  = 23652.;
    tdnuc_ = tcnuc_ - thnuc / std::log(2.) * std::log(prng_());
    tclev  = 0.;
    pbeta  = 100. * prng_();
    if (pbeta <= 0.013) {
      goto label_2478;
    }
    if (pbeta <= 0.155) {
      goto label_2475;
    }
    if (pbeta <= 0.282) {
      goto label_2466;
    }
    if (pbeta <= 0.422) {
      goto label_2447;
    }
    if (pbeta <= 1.449) {
      goto label_2409;
    }
    if (pbeta <= 2.366) {
      goto label_2372;
    }
    if (pbeta <= 3.752) {
      goto label_2357;
    }
    if (pbeta <= 8.518) {
      goto label_2255;
    }
    if (pbeta <= 15.896) {
      goto label_2233;
    }
    if (pbeta <= 15.919) {
      goto label_2152;
    }
    if (pbeta <= 15.989) {
      goto label_2112;
    }
    if (pbeta <= 17.574) {
      goto label_2093;
    }
    if (pbeta <= 18.681) {
      goto label_2046;
    }
    if (pbeta <= 26.657) {
      goto label_1968;
    }
    if (pbeta <= 26.707) {
      goto label_1927;
    }
    if (pbeta <= 27.315) {
      goto label_1894;
    }
    if (pbeta <= 36.089) {
      goto label_1791;
    }
    if (pbeta <= 57.825) {
      goto label_1678;
    }
    if (pbeta <= 65.801) {
      goto label_1565;
    }
    if (pbeta <= 73.279) {
      goto label_1458;
    }
    if (pbeta <= 96.810) {
      goto label_1260;
    }
    if (pbeta <= 98.106) {
      goto label_1132;
    }
    goto label_527;
  label_2478:
    decay0_beta(prng_, event_, 0.170, 54., 0., 0., t);
    ////    label_24780  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 9.72) {
      goto label_24781;
    }
    goto label_24782;
  label_24781:
    decay0_nucltransK(prng_, event_, 2.477, 0.035, 2.0e-4, 4.5e-4, tclev, thlev, tdlev);
    return;
  label_24782:
    decay0_nucltransK(prng_, event_, 2.189, 0.035, 3.0e-4, 3.1e-4, tclev, thlev, tdlev);
    goto label_28800;
  label_2475:
    decay0_beta(prng_, event_, 0.173, 54., 0., 0., t);
    ////label_24750  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 45.00) {
      goto label_24751;
    }
    goto label_24752;
  label_24751:
    decay0_nucltransK(prng_, event_, 1.948, 0.035, 2.4e-4, 2.1e-4, tclev, thlev, tdlev);
    goto label_52700;
  label_24752:
    decay0_nucltransK(prng_, event_, 1.344, 0.035, 4.0e-4, 0.7e-4, tclev, thlev, tdlev);
    goto label_11320;
  label_2466:
    decay0_beta(prng_, event_, 0.182, 54., 0., 0., t);
    ////label_24660  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 56.69) {
      goto label_24661;
    }
    if (p <= 81.89) {
      goto label_24662;
    }
    goto label_24663;
  label_24661:
    decay0_nucltransK(prng_, event_, 2.466, 0.035, 4.0e-4, 5.3e-4, tclev, thlev, tdlev);
    return;
  label_24662:
    decay0_nucltransK(prng_, event_, 1.335, 0.035, 1.2e-3, 0.6e-4, tclev, thlev, tdlev);
    goto label_11320;
  label_24663:
    decay0_nucltransK(prng_, event_, 0.685, 0.035, 4.0e-3, 0., tclev, thlev, tdlev);
    goto label_17810;
  label_2447:
    decay0_beta(prng_, event_, 0.201, 54., 0., 0., t);
    ////label_24470  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 46.81) {
      goto label_24471;
    }
    goto label_24472;
  label_24471:
    decay0_nucltransK(prng_, event_, 1.316, 0.035, 4.5e-4, 0.5e-4, tclev, thlev, tdlev);
    goto label_11320;
  label_24472:
    decay0_nucltransK(prng_, event_, 0.656, 0.035, 1.6e-3, 0., tclev, thlev, tdlev);
    goto label_17910;
  label_2409:
    decay0_beta(prng_, event_, 0.239, 54., 0., 0., t);
    ////    label_24090  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 93.48) {
      goto label_24091;
    }
    if (p <= 96.40) {
      goto label_24092;
    }
    goto label_24093;
  label_24091:
    decay0_nucltransK(prng_, event_, 2.409, 0.035, 3.5e-4, 4.1e-4, tclev, thlev, tdlev);
    return;
  label_24092:
    decay0_nucltransK(prng_, event_, 0.960, 0.035, 2.6e-3, 0., tclev, thlev, tdlev);
    goto label_14480;
  label_24093:
    decay0_nucltransK(prng_, event_, 0.617, 0.035, 7.0e-3, 0., tclev, thlev, tdlev);
    goto label_17910;
  label_2372:
    decay0_beta(prng_, event_, 0.276, 54., 0., 0., t);
    ////    label_23720  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 0.66) {
      goto label_23721;
    }
    goto label_23722;
  label_23721:
    decay0_nucltransK(prng_, event_, 1.845, 0.035, 2.6e-4, 1.8e-4, tclev, thlev, tdlev);
    goto label_52700;
  label_23722:
    decay0_nucltransK(prng_, event_, 1.240, 0.035, 1.4e-3, 0.5e-4, tclev, thlev, tdlev);
    goto label_11320;
  label_2357:
    decay0_beta(prng_, event_, 0.291, 54., 0., 0., t);
    ////   label_23570  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 41.91) {
      goto label_23571;
    }
    if (p <= 45.02) {
      goto label_23572;
    }
    if (p <= 51.45) {
      goto label_23573;
    }
    if (p <= 55.42) {
      goto label_23574;
    }
    if (p <= 64.74) {
      goto label_23575;
    }
    if (p <= 86.41) {
      goto label_23576;
    }
    goto label_23577;
  label_23571:
    decay0_nucltransK(prng_, event_, 1.831, 0.035, 2.6e-4, 1.6e-4, tclev, thlev, tdlev);
    goto label_52700;
  label_23572:
    decay0_nucltransK(prng_, event_, 1.226, 0.035, 1.4e-3, 0.4e-4, tclev, thlev, tdlev);
    goto label_11320;
  label_23573:
    decay0_nucltransK(prng_, event_, 1.097, 0.035, 1.4e-3, 0., tclev, thlev, tdlev);
    goto label_12600;
  label_23574:
    decay0_nucltransK(prng_, event_, 0.679, 0.035, 6.0e-3, 0., tclev, thlev, tdlev);
    goto label_16780;
  label_23575:
    decay0_nucltransK(prng_, event_, 0.576, 0.035, 8.5e-3, 0., tclev, thlev, tdlev);
    goto label_17810;
  label_23576:
    decay0_nucltransK(prng_, event_, 0.430, 0.035, 1.8e-2, 0., tclev, thlev, tdlev);
    goto label_19270;
  label_23577:
    decay0_nucltransK(prng_, event_, 0.264, 0.035, 6.5e-2, 0., tclev, thlev, tdlev);
    goto label_20930;
  label_2255:
    decay0_beta(prng_, event_, 0.393, 54., 0., 0., t);
    ////  label_22550  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 12.88) {
      goto label_22551;
    }
    if (p <= 89.34) {
      goto label_22552;
    }
    if (p <= 92.51) {
      goto label_22553;
    }
    if (p <= 93.48) {
      goto label_22554;
    }
    if (p <= 97.07) {
      goto label_22555;
    }
    if (p <= 99.79) {
      goto label_22556;
    }
    goto label_22557;
  label_22551:
    decay0_nucltransK(prng_, event_, 2.255, 0.035, 3.7e-4, 3.8e-4, tclev, thlev, tdlev);
    return;
  label_22552:
    decay0_nucltransK(prng_, event_, 1.124, 0.035, 1.7e-3, 0.2e-4, tclev, thlev, tdlev);
    goto label_11320;
  label_22553:
    decay0_nucltransK(prng_, event_, 0.995, 0.035, 1.9e-3, 0., tclev, thlev, tdlev);
    goto label_12600;
  label_22554:
    decay0_nucltransK(prng_, event_, 0.807, 0.035, 2.6e-3, 0., tclev, thlev, tdlev);
    goto label_14480;
  label_22555:
    decay0_nucltransK(prng_, event_, 0.798, 0.035, 4.0e-3, 0., tclev, thlev, tdlev);
    goto label_14580;
  label_22556:
    decay0_nucltransK(prng_, event_, 0.690, 0.035, 5.5e-3, 0., tclev, thlev, tdlev);
    goto label_15650;
  label_22557:
    decay0_nucltransK(prng_, event_, 0.163, 0.035, 2.2e-1, 0., tclev, thlev, tdlev);
    goto label_20930;
  label_2233:
    decay0_beta(prng_, event_, 0.415, 54., 0., 0., t);
    ////    label_22330  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 55.75) {
      goto label_22331;
    }
    if (p <= 77.64) {
      goto label_22332;
    }
    if (p <= 94.09) {
      goto label_22333;
    }
    if (p <= 98.39) {
      goto label_22334;
    }
    if (p <= 99.68) {
      goto label_22335;
    }
    goto label_22336;
  label_22331:
    decay0_nucltransK(prng_, event_, 1.706, 0.035, 2.8e-4, 1.0e-4, tclev, thlev, tdlev);
    goto label_52700;
  label_22332:
    decay0_nucltransK(prng_, event_, 1.102, 0.035, 1.4e-3, 0.1e-4, tclev, thlev, tdlev);
    goto label_11320;
  label_22333:
    decay0_nucltransK(prng_, event_, 0.973, 0.035, 1.8e-3, 0., tclev, thlev, tdlev);
    goto label_12600;
  label_22334:
    decay0_nucltransK(prng_, event_, 0.452, 0.035, 1.6e-2, 0., tclev, thlev, tdlev);
    goto label_17810;
  label_22335:
    decay0_nucltransK(prng_, event_, 0.306, 0.035, 4.0e-2, 0., tclev, thlev, tdlev);
    goto label_19270;
  label_22336:
    decay0_nucltransK(prng_, event_, 0.184, 0.035, 4.0e-2, 0., tclev, thlev, tdlev);
    goto label_20490;
  label_2152:
    decay0_beta(prng_, event_, 0.496, 54., 0., 0., t);
    ////    label_21520  :
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 2.152, 0.035, 2.0e-4, 2.9e-4, tclev, thlev, tdlev);
    return;
  label_2112:
    decay0_beta(prng_, event_, 0.536, 54., 0., 0., t);
    ////    label_21120  :
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 2.112, 0.035, 2.0e-4, 2.7e-4, tclev, thlev, tdlev);
    return;
  label_2093:
    decay0_beta(prng_, event_, 0.555, 54., 0., 0., t);
  label_20930:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 72.79) {
      goto label_20931;
    }
    if (p <= 81.26) {
      goto label_20932;
    }
    if (p <= 98.25) {
      goto label_20933;
    }
    goto label_20934;
  label_20931:
    decay0_nucltransK(prng_, event_, 1.566, 0.035, 2.8e-4, 0.7e-4, tclev, thlev, tdlev);
    goto label_52700;
  label_20932:
    decay0_nucltransK(prng_, event_, 0.961, 0.035, 2.6e-3, 0., tclev, thlev, tdlev);
    goto label_11320;
  label_20933:
    decay0_nucltransK(prng_, event_, 0.415, 0.035, 2.0e-2, 0., tclev, thlev, tdlev);
    goto label_16780;
  label_20934:
    decay0_nucltransK(prng_, event_, 0.166, 0.035, 2.2e-1, 0., tclev, thlev, tdlev);
    goto label_19270;
  label_20490:
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 1.522, 0.035, 9.0e-4, 0.9e-4, tclev, thlev, tdlev);
    goto label_52700;
  label_2046:
    decay0_beta(prng_, event_, 0.602, 54., 0., 0., t);
    ////    label_20460  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 79.31) {
      goto label_20461;
    }
    if (p <= 93.16) {
      goto label_20462;
    }
    if (p <= 97.90) {
      goto label_20463;
    }
    goto label_20464;
  label_20461:
    decay0_nucltransK(prng_, event_, 2.046, 0.035, 4.5e-4, 2.3e-4, tclev, thlev, tdlev);
    return;
  label_20462:
    decay0_nucltransK(prng_, event_, 0.785, 0.035, 3.6e-3, 0., tclev, thlev, tdlev);
    goto label_12600;
  label_20463:
    decay0_nucltransK(prng_, event_, 0.588, 0.035, 8.5e-3, 0., tclev, thlev, tdlev);
    goto label_14580;
  label_20464:
    decay0_nucltransK(prng_, event_, 0.255, 0.035, 6.5e-2, 0., tclev, thlev, tdlev);
    goto label_17910;
  label_1968:
    decay0_beta(prng_, event_, 0.680, 54., 0., 0., t);
    ////    label_19680  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 0.21) {
      goto label_19681;
    }
    if (p <= 84.72) {
      goto label_19682;
    }
    if (p <= 93.05) {
      goto label_19683;
    }
    if (p <= 95.98) {
      goto label_19684;
    }
    goto label_19685;
  label_19681:
    decay0_nucltransK(prng_, event_, 1.442, 0.035, 0.8e-4, 1.0e-3, tclev, thlev, tdlev);
    goto label_52700;
  label_19682:
    decay0_nucltransK(prng_, event_, 0.837, 0.035, 2.5e-3, 0., tclev, thlev, tdlev);
    goto label_11320;
  label_19683:
    decay0_nucltransK(prng_, event_, 0.708, 0.035, 5.0e-3, 0., tclev, thlev, tdlev);
    goto label_12600;
  label_19684:
    decay0_nucltransK(prng_, event_, 0.403, 0.035, 1.8e-2, 0., tclev, thlev, tdlev);
    goto label_15650;
  label_19685:
    decay0_nucltransK(prng_, event_, 0.290, 0.035, 4.6e-2, 0., tclev, thlev, tdlev);
    goto label_16780;
  label_1927:
    decay0_beta(prng_, event_, 0.721, 54., 0., 0., t);
  label_19270:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 58.50) {
      goto label_19271;
    }
    if (p <= 63.05) {
      goto label_19272;
    }
    goto label_19273;
  label_19271:
    decay0_nucltransK(prng_, event_, 1.927, 0.035, 5.0e-4, 1.4e-4, tclev, thlev, tdlev);
    return;
  label_19272:
    decay0_nucltransK(prng_, event_, 0.796, 0.035, 4.0e-3, 0., tclev, thlev, tdlev);
    goto label_11320;
  label_19273:
    decay0_nucltransK(prng_, event_, 0.362, 0.035, 2.8e-2, 0., tclev, thlev, tdlev);
    goto label_15650;
  label_1894:
    decay0_beta(prng_, event_, 0.754, 54., 0., 0., t);
    ////    label_18940  :
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 1.368, 0.035, 9.0e-4, 0.2e-4, tclev, thlev, tdlev);
    goto label_52700;
  label_1791:
    decay0_beta(prng_, event_, 0.857, 54., 0., 0., t);
  label_17910:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 86.68) {
      goto label_17911;
    }
    if (p <= 98.81) {
      goto label_17912;
    }
    if (p <= 99.17) {
      goto label_17913;
    }
    if (p <= 99.18) {
      goto label_17914;
    }
    if (p <= 99.60) {
      goto label_17915;
    }
    if (p <= 99.92) {
      goto label_17916;
    }
    goto label_17917;
  label_17911:
    decay0_nucltransK(prng_, event_, 1.791, 0.035, 6.5e-4, 1.6e-4, tclev, thlev, tdlev);
    return;
  label_17912:
    decay0_nucltransK(prng_, event_, 1.503, 0.035, 7.5e-4, 0.3e-4, tclev, thlev, tdlev);
    goto label_28800;
  label_17913:
    decay0_nucltransK(prng_, event_, 0.531, 0.035, 9.3e-3, 0., tclev, thlev, tdlev);
    goto label_12600;
  label_17914:
    decay0_nucltransK(prng_, event_, 0.343, 0.035, 3.0e-2, 0., tclev, thlev, tdlev);
    goto label_14480;
  label_17915:
    decay0_nucltransK(prng_, event_, 0.334, 0.035, 3.5e-2, 0., tclev, thlev, tdlev);
    goto label_14580;
  label_17916:
    decay0_nucltransK(prng_, event_, 0.248, 0.035, 8.0e-3, 0., tclev, thlev, tdlev);
    goto label_15440;
  label_17917:
    decay0_nucltransK(prng_, event_, 0.113, 0.035, 6.0e-1, 0., tclev, thlev, tdlev);
    goto label_16780;
  label_17810:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 1.29) {
      goto label_17811;
    }
    goto label_17812;
  label_17811:
    decay0_nucltransK(prng_, event_, 1.255, 0.035, 4.7e-4, 0.3e-4, tclev, thlev, tdlev);
    goto label_52700;
  label_17812:
    decay0_nucltransK(prng_, event_, 0.645, 0.035, 4.5e-3, 0., tclev, thlev, tdlev);
    goto label_11320;
  label_1678:
    decay0_beta(prng_, event_, 0.970, 54., 0., 0., t);
  label_16780:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 42.57) {
      goto label_16781;
    }
    if (p <= 74.58) {
      goto label_16782;
    }
    if (p <= 90.20) {
      goto label_16783;
    }
    if (p <= 91.38) {
      goto label_16784;
    }
    if (p <= 99.94) {
      goto label_16785;
    }
    goto label_16786;
  label_16781:
    decay0_nucltransK(prng_, event_, 1.678, 0.035, 5.6e-4, 0.7e-4, tclev, thlev, tdlev);
    return;
  label_16782:
    decay0_nucltransK(prng_, event_, 0.547, 0.035, 9.1e-3, 0., tclev, thlev, tdlev);
    goto label_11320;
  label_16783:
    decay0_nucltransK(prng_, event_, 0.418, 0.035, 1.6e-2, 0., tclev, thlev, tdlev);
    goto label_12600;
  label_16784:
    decay0_nucltransK(prng_, event_, 0.230, 0.035, 1.0e-1, 0., tclev, thlev, tdlev);
    goto label_14480;
  label_16785:
    decay0_nucltransK(prng_, event_, 0.221, 0.035, 1.0e-1, 0., tclev, thlev, tdlev);
    goto label_14580;
  label_16786:
    decay0_nucltransK(prng_, event_, 0.113, 0.035, 6.0e-1, 0., tclev, thlev, tdlev);
    goto label_15650;
  label_1565:
    decay0_beta(prng_, event_, 1.083, 54., 0., 0., t);
  label_15650:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 93.00) {
      goto label_15651;
    }
    if (p <= 99.62) {
      goto label_15652;
    }
    goto label_15653;
  label_15651:
    decay0_nucltransK(prng_, event_, 1.039, 0.035, 6.4e-4, 0., tclev, thlev, tdlev);
    goto label_52700;
  label_15652:
    decay0_nucltransK(prng_, event_, 0.434, 0.035, 1.6e-2, 0., tclev, thlev, tdlev);
    goto label_11320;
  label_15653:
    decay0_nucltransK(prng_, event_, 0.305, 0.035, 4.0e-2, 0., tclev, thlev, tdlev);
    goto label_12600;
  label_15440:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 81.25) {
      goto label_15441;
    }
    goto label_15442;
  label_15441:
    decay0_nucltransK(prng_, event_, 1.544, 0.035, 9.0e-4, 1.0e-4, tclev, thlev, tdlev);
    return;
  label_15442:
    decay0_nucltransK(prng_, event_, 1.255, 0.035, 1.2e-3, 0.5e-4, tclev, thlev, tdlev);
    goto label_28800;
  label_1458:
    decay0_beta(prng_, event_, 1.190, 54., 0., 0., t);
  label_14580:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 90.44) {
      goto label_14581;
    }
    if (p <= 99.59) {
      goto label_14582;
    }
    if (p <= 99.61) {
      goto label_14583;
    }
    goto label_14584;
  label_14581:
    decay0_nucltransK(prng_, event_, 1.458, 0.035, 7.0e-4, 0.9e-4, tclev, thlev, tdlev);
    return;
  label_14582:
    decay0_nucltransK(prng_, event_, 1.169, 0.035, 1.3e-3, 0., tclev, thlev, tdlev);
    goto label_28800;
  label_14583:
    decay0_nucltransK(prng_, event_, 0.326, 0.035, 3.5e-2, 0., tclev, thlev, tdlev);
    goto label_11320;
  label_14584:
    decay0_nucltransK(prng_, event_, 0.197, 0.035, 1.5e-1, 0., tclev, thlev, tdlev);
    goto label_12600;
  label_14480:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 75.65) {
      goto label_14481;
    }
    goto label_14482;
  label_14481:
    decay0_nucltransK(prng_, event_, 1.448, 0.035, 7.0e-4, 0.9e-4, tclev, thlev, tdlev);
    return;
  label_14482:
    decay0_nucltransK(prng_, event_, 1.160, 0.035, 1.3e-3, 0., tclev, thlev, tdlev);
    goto label_28800;
  label_1260:
    decay0_beta(prng_, event_, 1.388, 54., 0., 0., t);
  label_12600:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 96.99) {
      goto label_12601;
    }
    goto label_12602;
  label_12601:
    decay0_nucltransK(prng_, event_, 1.260, 0.035, 1.2e-3, 0.1e-4, tclev, thlev, tdlev);
    return;
  label_12602:
    decay0_nucltransK(prng_, event_, 0.972, 0.035, 1.8e-3, 0., tclev, thlev, tdlev);
    goto label_28800;
  label_1132:
    decay0_beta(prng_, event_, 1.516, 54., 0., 0., t);
  label_11320:
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 1.132, 0.035, 1.3e-3, 0., tclev, thlev, tdlev);
    return;
  label_527:
    decay0_beta(prng_, event_, 2.121, 54., 0., 0., t);
  label_52700:
    thlev = 917.4;
    decay0_nucltransK(prng_, event_, 0.527, 0.035, 2.4e-1, 0., tclev, thlev, tdlev);
    return;
  label_28800:
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 0.288, 0.035, 4.7e-2, 0., tclev, thlev, tdlev);
    return;
  }
  // end of I135.f

} // end of namespace bxdecay0

// end of I135.cc
// Local Variables: --
// mode: c++ --
// End: --
