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
#include <bxdecay0/Te133.h>

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

  void Te133(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_)
  {
    double t;
    double tdlev;
    double p;
    double pbeta;
    double tclev;
    double thlev;
    double thnuc;
    // Model for scheme of Te133 decay (S.Rab, Nucl. Data Sheets
    // 75(1995)491).
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 14.12.2003.
    thnuc  = 750.;
    tdnuc_ = tcnuc_ - thnuc / std::log(2.) * std::log(prng_());
    tclev  = 0.;
    pbeta  = 100. * prng_();
    if (pbeta <= 0.13)
      goto label_2936;
    if (pbeta <= 0.60)
      goto label_2866;
    if (pbeta <= 0.86)
      goto label_2825;
    if (pbeta <= 1.29)
      goto label_2808;
    if (pbeta <= 2.34)
      goto label_2768;
    if (pbeta <= 2.52)
      goto label_2661;
    if (pbeta <= 2.70)
      goto label_2597;
    if (pbeta <= 4.86)
      goto label_2542;
    if (pbeta <= 5.24)
      goto label_2526;
    if (pbeta <= 5.60)
      goto label_2493;
    if (pbeta <= 6.20)
      goto label_2467;
    if (pbeta <= 6.75)
      goto label_2417;
    if (pbeta <= 6.86)
      goto label_2393;
    if (pbeta <= 7.00)
      goto label_2364;
    if (pbeta <= 7.26)
      goto label_2284;
    if (pbeta <= 7.72)
      goto label_2266;
    if (pbeta <= 8.96)
      goto label_2255;
    if (pbeta <= 9.95)
      goto label_2225;
    if (pbeta <= 11.27)
      goto label_2210;
    if (pbeta <= 13.53)
      goto label_2194;
    if (pbeta <= 15.90)
      goto label_2136;
    if (pbeta <= 16.97)
      goto label_2054;
    if (pbeta <= 17.31)
      goto label_2040;
    if (pbeta <= 18.70)
      goto label_2025;
    if (pbeta <= 28.99)
      goto label_1718;
    if (pbeta <= 30.31)
      goto label_1671;
    if (pbeta <= 33.78)
      goto label_1564;
    if (pbeta <= 34.97)
      goto label_1374;
    if (pbeta <= 47.93)
      goto label_1333;
    if (pbeta <= 51.20)
      goto label_1313;
    if (pbeta <= 51.40)
      goto label_1240;
    if (pbeta <= 79.41)
      goto label_720;
    goto label_312;
  label_2936:
    decay0_beta(prng_, event_, 0.001, 53., 0., 0., t);
    ////    label_29360  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 72.87)
      goto label_29361;
    if (p <= 92.25)
      goto label_29362;
    goto label_29363;
  label_29361:
    decay0_nucltransK(prng_, event_, 2.624, 0.033, 1.5e-4, 5.1e-4, tclev, thlev, tdlev);
    goto label_31200;
  label_29362:
    decay0_nucltransK(prng_, event_, 2.148, 0.033, 3.0e-4, 2.9e-4, tclev, thlev, tdlev);
    goto label_78700;
  label_29363:
    decay0_nucltransK(prng_, event_, 1.372, 0.033, 1.0e-3, 0.7e-4, tclev, thlev, tdlev);
    goto label_15640;
  label_2866:
    decay0_beta(prng_, event_, 0.054, 53., 0., 0., t);
    ////    label_28660  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 74.63)
      goto label_28661;
    if (p <= 94.67)
      goto label_28662;
    goto label_28663;
  label_28661:
    decay0_nucltransK(prng_, event_, 2.554, 0.033, 1.8e-4, 4.9e-4, tclev, thlev, tdlev);
    goto label_31200;
  label_28662:
    decay0_nucltransK(prng_, event_, 2.079, 0.033, 3.2e-4, 2.7e-4, tclev, thlev, tdlev);
    goto label_78700;
  label_28663:
    decay0_nucltransK(prng_, event_, 1.493, 0.033, 7.5e-4, 0.9e-4, tclev, thlev, tdlev);
    goto label_13740;
  label_2825:
    decay0_beta(prng_, event_, 0.095, 53., 0., 0., t);
    ////    label_28250  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 60.94)
      goto label_28251;
    goto label_28252;
  label_28251:
    decay0_nucltransK(prng_, event_, 2.825, 0.033, 1.3e-4, 5.9e-4, tclev, thlev, tdlev);
    return;
  label_28252:
    decay0_nucltransK(prng_, event_, 2.106, 0.033, 3.2e-4, 2.7e-4, tclev, thlev, tdlev);
    goto label_72000;
  label_2808:
    decay0_beta(prng_, event_, 0.112, 53., 0., 0., t);
    ////    label_28080  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 46.23)
      goto label_28081;
    if (p <= 63.26)
      goto label_28082;
    if (p <= 92.46)
      goto label_28083;
    goto label_28084;
  label_28081:
    decay0_nucltransK(prng_, event_, 2.496, 0.033, 2.0e-4, 4.7e-4, tclev, thlev, tdlev);
    goto label_31200;
  label_28082:
    decay0_nucltransK(prng_, event_, 1.244, 0.033, 1.1e-3, 0.4e-4, tclev, thlev, tdlev);
    goto label_15640;
  label_28083:
    decay0_nucltransK(prng_, event_, 1.137, 0.033, 1.5e-3, 0.2e-4, tclev, thlev, tdlev);
    goto label_16710;
  label_28084:
    decay0_nucltransK(prng_, event_, 0.341, 0.033, 3.0e-2, 0., tclev, thlev, tdlev);
    goto label_24670;
  label_2768:
    decay0_beta(prng_, event_, 0.152, 53., 0., 0., t);
    ////    label_27680  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 24.57)
      goto label_27681;
    if (p <= 28.07)
      goto label_27682;
    if (p <= 42.25)
      goto label_27683;
    if (p <= 71.55)
      goto label_27684;
    if (p <= 82.89)
      goto label_27685;
    if (p <= 88.56)
      goto label_27686;
    if (p <= 91.49)
      goto label_27687;
    goto label_27688;
  label_27681:
    decay0_nucltransK(prng_, event_, 2.456, 0.033, 2.0e-4, 4.4e-4, tclev, thlev, tdlev);
    goto label_31200;
  label_27682:
    decay0_nucltransK(prng_, event_, 2.049, 0.033, 1.2e-3, 2.5e-4, tclev, thlev, tdlev);
    goto label_72000;
  label_27683:
    decay0_nucltransK(prng_, event_, 1.455, 0.033, 1.0e-3, 0.8e-4, tclev, thlev, tdlev);
    goto label_13130;
  label_27684:
    decay0_nucltransK(prng_, event_, 0.743, 0.033, 5.0e-3, 0., tclev, thlev, tdlev);
    goto label_20250;
  label_27685:
    decay0_nucltransK(prng_, event_, 0.544, 0.033, 2.0e-4, 0., tclev, thlev, tdlev);
    goto label_22250;
  label_27686:
    decay0_nucltransK(prng_, event_, 0.485, 0.033, 1.0e-2, 0., tclev, thlev, tdlev);
    goto label_22840;
  label_27687:
    decay0_nucltransK(prng_, event_, 0.302, 0.033, 4.5e-2, 0., tclev, thlev, tdlev);
    goto label_24670;
  label_27688:
    decay0_nucltransK(prng_, event_, 0.171, 0.033, 2.0e-1, 0., tclev, thlev, tdlev);
    goto label_25970;
  label_2661:
    decay0_beta(prng_, event_, 0.259, 53., 0., 0., t);
    ////    label_26610  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 43.10)
      goto label_26611;
    if (p <= 47.70)
      goto label_26612;
    if (p <= 82.18)
      goto label_26613;
    goto label_26614;
  label_26611:
    decay0_nucltransK(prng_, event_, 2.661, 0.033, 1.5e-4, 5.2e-4, tclev, thlev, tdlev);
    return;
  label_26612:
    decay0_nucltransK(prng_, event_, 2.349, 0.033, 2.2e-4, 3.9e-4, tclev, thlev, tdlev);
    goto label_31200;
  label_26613:
    decay0_nucltransK(prng_, event_, 0.943, 0.033, 2.5e-3, 0., tclev, thlev, tdlev);
    goto label_17180;
  label_26614:
    decay0_nucltransK(prng_, event_, 0.620, 0.033, 6.5e-3, 0., tclev, thlev, tdlev);
    goto label_20400;
  label_2597:
    decay0_beta(prng_, event_, 0.323, 53., 0., 0., t);
  label_25970:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 20.00)
      goto label_25971;
    if (p <= 23.21)
      goto label_25972;
    if (p <= 73.21)
      goto label_25973;
    if (p <= 80.00)
      goto label_25974;
    if (p <= 88.93)
      goto label_25975;
    if (p <= 91.07)
      goto label_25976;
    goto label_25977;
  label_25971:
    decay0_nucltransK(prng_, event_, 2.597, 0.033, 1.6e-4, 5.1e-4, tclev, thlev, tdlev);
    return;
  label_25972:
    decay0_nucltransK(prng_, event_, 2.286, 0.033, 2.3e-4, 3.5e-4, tclev, thlev, tdlev);
    goto label_31200;
  label_25973:
    decay0_nucltransK(prng_, event_, 1.683, 0.033, 5.0e-4, 0.6e-4, tclev, thlev, tdlev);
    goto label_91500;
  label_25974:
    decay0_nucltransK(prng_, event_, 1.290, 0.033, 1.0e-3, 0.5e-4, tclev, thlev, tdlev);
    goto label_13070;
  label_25975:
    decay0_nucltransK(prng_, event_, 1.285, 0.033, 1.0e-3, 0.5e-4, tclev, thlev, tdlev);
    goto label_13130;
  label_25976:
    decay0_nucltransK(prng_, event_, 1.224, 0.033, 1.0e-3, 0.1e-4, tclev, thlev, tdlev);
    goto label_13740;
  label_25977:
    decay0_nucltransK(prng_, event_, 0.572, 0.033, 9.0e-3, 0., tclev, thlev, tdlev);
    goto label_20250;
  label_2542:
    decay0_beta(prng_, event_, 0.378, 53., 0., 0., t);
    ////    label_25420  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 23.06)
      goto label_25421;
    if (p <= 63.19)
      goto label_25422;
    if (p <= 73.34)
      goto label_25423;
    if (p <= 75.37)
      goto label_25424;
    if (p <= 77.40)
      goto label_25425;
    if (p <= 84.78)
      goto label_25426;
    if (p <= 90.32)
      goto label_25427;
    if (p <= 94.47)
      goto label_25428;
    goto label_25429;
  label_25421:
    decay0_nucltransK(prng_, event_, 2.542, 0.033, 1.6e-4, 4.8e-4, tclev, thlev, tdlev);
    return;
  label_25422:
    decay0_nucltransK(prng_, event_, 2.230, 0.033, 2.5e-4, 3.2e-4, tclev, thlev, tdlev);
    goto label_31200;
  label_25423:
    decay0_nucltransK(prng_, event_, 1.822, 0.033, 5.0e-4, 1.8e-4, tclev, thlev, tdlev);
    goto label_72000;
  label_25424:
    decay0_nucltransK(prng_, event_, 1.755, 0.033, 5.5e-4, 1.6e-4, tclev, thlev, tdlev);
    goto label_78700;
  label_25425:
    decay0_nucltransK(prng_, event_, 1.302, 0.033, 1.0e-3, 0.5e-4, tclev, thlev, tdlev);
    goto label_12400;
  label_25426:
    decay0_nucltransK(prng_, event_, 1.209, 0.033, 1.4e-3, 0.3e-4, tclev, thlev, tdlev);
    goto label_13330;
  label_25427:
    decay0_nucltransK(prng_, event_, 0.978, 0.033, 2.5e-3, 0., tclev, thlev, tdlev);
    goto label_15640;
  label_25428:
    decay0_nucltransK(prng_, event_, 0.488, 0.033, 1.2e-2, 0., tclev, thlev, tdlev);
    goto label_20540;
  label_25429:
    decay0_nucltransK(prng_, event_, 0.332, 0.033, 3.5e-2, 0., tclev, thlev, tdlev);
    goto label_22100;
  label_2526:
    decay0_beta(prng_, event_, 0.394, 53., 0., 0., t);
    ////    label_25260  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 3.97)
      goto label_25261;
    if (p <= 37.30)
      goto label_25262;
    if (p <= 78.57)
      goto label_25263;
    if (p <= 86.51)
      goto label_25264;
    if (p <= 90.48)
      goto label_25265;
    goto label_25266;
  label_25261:
    decay0_nucltransK(prng_, event_, 2.526, 0.033, 1.7e-4, 5.7e-4, tclev, thlev, tdlev);
    return;
  label_25262:
    decay0_nucltransK(prng_, event_, 2.214, 0.033, 2.5e-4, 3.1e-4, tclev, thlev, tdlev);
    goto label_31200;
  label_25263:
    decay0_nucltransK(prng_, event_, 1.807, 0.033, 5.0e-4, 1.8e-4, tclev, thlev, tdlev);
    goto label_72000;
  label_25264:
    decay0_nucltransK(prng_, event_, 1.738, 0.033, 5.5e-4, 1.5e-4, tclev, thlev, tdlev);
    goto label_78700;
  label_25265:
    decay0_nucltransK(prng_, event_, 1.286, 0.033, 1.0e-3, 0.5e-4, tclev, thlev, tdlev);
    goto label_12400;
  label_25266:
    decay0_nucltransK(prng_, event_, 0.854, 0.033, 3.5e-3, 0., tclev, thlev, tdlev);
    goto label_16710;
  label_2493:
    decay0_beta(prng_, event_, 0.427, 53., 0., 0., t);
    ////    label_24930  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 8.93)
      goto label_24931;
    if (p <= 48.72)
      goto label_24932;
    if (p <= 65.81)
      goto label_24933;
    goto label_24934;
  label_24931:
    decay0_nucltransK(prng_, event_, 2.181, 0.033, 2.5e-4, 3.4e-4, tclev, thlev, tdlev);
    goto label_31200;
  label_24932:
    decay0_nucltransK(prng_, event_, 1.773, 0.033, 5.0e-4, 0.9e-4, tclev, thlev, tdlev);
    goto label_72000;
  label_24933:
    decay0_nucltransK(prng_, event_, 1.706, 0.033, 6.0e-4, 1.3e-4, tclev, thlev, tdlev);
    goto label_78700;
  label_24934:
    decay0_nucltransK(prng_, event_, 0.928, 0.033, 2.8e-3, 0., tclev, thlev, tdlev);
    goto label_15640;
  label_2467:
    decay0_beta(prng_, event_, 0.453, 53., 0., 0., t);
  label_24670:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 61.38)
      goto label_24671;
    if (p <= 65.12)
      goto label_24672;
    if (p <= 78.59)
      goto label_24673;
    if (p <= 95.36)
      goto label_24674;
    goto label_24675;
  label_24671:
    decay0_nucltransK(prng_, event_, 2.467, 0.033, 1.8e-4, 5.2e-4, tclev, thlev, tdlev);
    return;
  label_24672:
    decay0_nucltransK(prng_, event_, 2.155, 0.033, 3.0e-4, 3.0e-4, tclev, thlev, tdlev);
    goto label_31200;
  label_24673:
    decay0_nucltransK(prng_, event_, 1.680, 0.033, 5.0e-4, 1.3e-4, tclev, thlev, tdlev);
    goto label_78700;
  label_24674:
    decay0_nucltransK(prng_, event_, 1.228, 0.033, 1.2e-3, 0.4e-4, tclev, thlev, tdlev);
    goto label_12400;
  label_24675:
    decay0_nucltransK(prng_, event_, 0.242, 0.033, 8.0e-2, 0., tclev, thlev, tdlev);
    goto label_22250;
  label_2417:
    decay0_beta(prng_, event_, 0.503, 53., 0., 0., t);
    ////    label_24170  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 34.48)
      goto label_24171;
    if (p <= 52.63)
      goto label_24172;
    if (p <= 63.52)
      goto label_24173;
    if (p <= 68.06)
      goto label_24174;
    if (p <= 73.69)
      goto label_24175;
    if (p <= 95.46)
      goto label_24176;
    goto label_24177;
  label_24171:
    decay0_nucltransK(prng_, event_, 2.417, 0.033, 2.0e-4, 4.2e-4, tclev, thlev, tdlev);
    return;
  label_24172:
    decay0_nucltransK(prng_, event_, 2.106, 0.033, 3.0e-4, 2.7e-4, tclev, thlev, tdlev);
    goto label_31200;
  label_24173:
    decay0_nucltransK(prng_, event_, 1.697, 0.033, 5.0e-4, 1.3e-4, tclev, thlev, tdlev);
    goto label_72000;
  label_24174:
    decay0_nucltransK(prng_, event_, 1.630, 0.033, 5.2e-4, 1.2e-4, tclev, thlev, tdlev);
    goto label_78700;
  label_24175:
    decay0_nucltransK(prng_, event_, 1.503, 0.033, 7.0e-4, 0.3e-4, tclev, thlev, tdlev);
    goto label_91500;
  label_24176:
    decay0_nucltransK(prng_, event_, 1.110, 0.033, 1.8e-3, 0.1e-4, tclev, thlev, tdlev);
    goto label_13070;
  label_24177:
    decay0_nucltransK(prng_, event_, 0.207, 0.033, 1.2e-1, 0., tclev, thlev, tdlev);
    goto label_22100;
  label_2393:
    decay0_beta(prng_, event_, 0.527, 53., 0., 0., t);
    ////    label_23930  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 11.32)
      goto label_23931;
    if (p <= 64.16)
      goto label_23932;
    if (p <= 82.08)
      goto label_23933;
    goto label_23934;
  label_23931:
    decay0_nucltransK(prng_, event_, 2.393, 0.033, 2.0e-4, 4.1e-4, tclev, thlev, tdlev);
    return;
  label_23932:
    decay0_nucltransK(prng_, event_, 2.081, 0.033, 3.0e-4, 2.6e-4, tclev, thlev, tdlev);
    goto label_31200;
  label_23933:
    decay0_nucltransK(prng_, event_, 0.722, 0.033, 5.0e-3, 0., tclev, thlev, tdlev);
    goto label_16710;
  label_23934:
    decay0_nucltransK(prng_, event_, 0.183, 0.033, 1.7e-1, 0., tclev, thlev, tdlev);
    goto label_22100;
  label_2364:
    decay0_beta(prng_, event_, 0.556, 53., 0., 0., t);
    ////    label_23640  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 18.52)
      goto label_23641;
    if (p <= 62.96)
      goto label_23642;
    goto label_23643;
  label_23641:
    decay0_nucltransK(prng_, event_, 2.363, 0.033, 2.0e-4, 4.0e-4, tclev, thlev, tdlev);
    return;
  label_23642:
    decay0_nucltransK(prng_, event_, 1.124, 0.033, 1.8e-3, 0.3e-4, tclev, thlev, tdlev);
    goto label_12400;
  label_23643:
    decay0_nucltransK(prng_, event_, 1.051, 0.033, 2.0e-3, 0., tclev, thlev, tdlev);
    goto label_13130;
  label_2284:
    decay0_beta(prng_, event_, 0.636, 53., 0., 0., t);
  label_22840:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 5.77)
      goto label_22841;
    if (p <= 34.62)
      goto label_22842;
    if (p <= 53.85)
      goto label_22843;
    goto label_22844;
  label_22841:
    decay0_nucltransK(prng_, event_, 1.972, 0.033, 3.5e-4, 1.7e-4, tclev, thlev, tdlev);
    goto label_31200;
  label_22842:
    decay0_nucltransK(prng_, event_, 1.564, 0.033, 6.0e-4, 0.4e-4, tclev, thlev, tdlev);
    goto label_72000;
  label_22843:
    decay0_nucltransK(prng_, event_, 0.971, 0.033, 2.5e-3, 0., tclev, thlev, tdlev);
    goto label_13130;
  label_22844:
    decay0_nucltransK(prng_, event_, 0.910, 0.033, 3.0e-3, 0., tclev, thlev, tdlev);
    goto label_13740;
  label_2266:
    decay0_beta(prng_, event_, 0.654, 53., 0., 0., t);
    ////    label_22660  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 52.17)
      goto label_22661;
    if (p <= 64.34)
      goto label_22662;
    if (p <= 90.43)
      goto label_22663;
    goto label_22664;
  label_22661:
    decay0_nucltransK(prng_, event_, 2.266, 0.033, 2.5e-4, 3.5e-4, tclev, thlev, tdlev);
    return;
  label_22662:
    decay0_nucltransK(prng_, event_, 1.027, 0.033, 2.2e-3, 0., tclev, thlev, tdlev);
    goto label_12400;
  label_22663:
    decay0_nucltransK(prng_, event_, 0.934, 0.033, 2.8e-3, 0., tclev, thlev, tdlev);
    goto label_13330;
  label_22664:
    decay0_nucltransK(prng_, event_, 0.702, 0.033, 5.5e-3, 0., tclev, thlev, tdlev);
    goto label_15640;
  label_2255:
    decay0_beta(prng_, event_, 0.665, 53., 0., 0., t);
    ////    label_22550  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 16.92)
      goto label_22551;
    if (p <= 23.45)
      goto label_22552;
    if (p <= 40.37)
      goto label_22553;
    if (p <= 44.40)
      goto label_22554;
    if (p <= 54.07)
      goto label_22555;
    if (p <= 79.05)
      goto label_22556;
    if (p <= 88.72)
      goto label_22557;
    goto label_22558;
  label_22551:
    decay0_nucltransK(prng_, event_, 2.255, 0.033, 3.0e-4, 3.8e-4, tclev, thlev, tdlev);
    return;
  label_22552:
    decay0_nucltransK(prng_, event_, 1.944, 0.033, 3.5e-4, 2.1e-4, tclev, thlev, tdlev);
    goto label_31200;
  label_22553:
    decay0_nucltransK(prng_, event_, 1.535, 0.033, 6.0e-4, 1.0e-4, tclev, thlev, tdlev);
    goto label_72000;
  label_22554:
    decay0_nucltransK(prng_, event_, 1.468, 0.033, 6.5e-4, 0.9e-4, tclev, thlev, tdlev);
    goto label_78700;
  label_22555:
    decay0_nucltransK(prng_, event_, 1.015, 0.033, 2.3e-3, 0., tclev, thlev, tdlev);
    goto label_12400;
  label_22556:
    decay0_nucltransK(prng_, event_, 0.942, 0.033, 2.7e-3, 0., tclev, thlev, tdlev);
    goto label_13130;
  label_22557:
    decay0_nucltransK(prng_, event_, 0.922, 0.033, 2.8e-3, 0., tclev, thlev, tdlev);
    goto label_13330;
  label_22558:
    decay0_nucltransK(prng_, event_, 0.691, 0.033, 5.5e-3, 0., tclev, thlev, tdlev);
    goto label_15640;
  label_2225:
    decay0_beta(prng_, event_, 0.695, 53., 0., 0., t);
  label_22250:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 19.00)
      goto label_22251;
    if (p <= 29.28)
      goto label_22252;
    if (p <= 35.32)
      goto label_22253;
    if (p <= 35.84)
      goto label_22254;
    if (p <= 47.67)
      goto label_22255;
    if (p <= 53.02)
      goto label_22256;
    if (p <= 79.79)
      goto label_22257;
    if (p <= 84.97)
      goto label_22258;
    if (p <= 96.80)
      goto label_22259;
    goto label_22260;
  label_22251:
    decay0_nucltransK(prng_, event_, 2.225, 0.033, 3.0e-4, 3.2e-4, tclev, thlev, tdlev);
    return;
  label_22252:
    decay0_nucltransK(prng_, event_, 1.913, 0.033, 4.5e-4, 2.0e-4, tclev, thlev, tdlev);
    goto label_31200;
  label_22253:
    decay0_nucltransK(prng_, event_, 1.505, 0.033, 7.5e-4, 0.9e-4, tclev, thlev, tdlev);
    goto label_72000;
  label_22254:
    decay0_nucltransK(prng_, event_, 1.438, 0.033, 8.5e-4, 0.8e-4, tclev, thlev, tdlev);
    goto label_78700;
  label_22255:
    decay0_nucltransK(prng_, event_, 1.310, 0.033, 9.0e-4, 0.1e-4, tclev, thlev, tdlev);
    goto label_91500;
  label_22256:
    decay0_nucltransK(prng_, event_, 0.912, 0.033, 3.0e-3, 0., tclev, thlev, tdlev);
    goto label_13130;
  label_22257:
    decay0_nucltransK(prng_, event_, 0.852, 0.033, 2.5e-3, 0., tclev, thlev, tdlev);
    goto label_13740;
  label_22258:
    decay0_nucltransK(prng_, event_, 0.554, 0.033, 9.5e-3, 0., tclev, thlev, tdlev);
    goto label_16710;
  label_22259:
    decay0_nucltransK(prng_, event_, 0.507, 0.033, 1.2e-2, 0., tclev, thlev, tdlev);
    goto label_17180;
  label_22260:
    decay0_nucltransK(prng_, event_, 0.200, 0.033, 1.4e-1, 0., tclev, thlev, tdlev);
    goto label_20250;
  label_2210:
    decay0_beta(prng_, event_, 0.710, 53., 0., 0., t);
  label_22100:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 46.12)
      goto label_22101;
    if (p <= 53.21)
      goto label_22102;
    if (p <= 61.23)
      goto label_22103;
    if (p <= 73.93)
      goto label_22104;
    goto label_22105;
  label_22101:
    decay0_nucltransK(prng_, event_, 2.210, 0.033, 2.9e-4, 3.6e-4, tclev, thlev, tdlev);
    return;
  label_22102:
    decay0_nucltransK(prng_, event_, 1.898, 0.033, 4.5e-4, 2.0e-4, tclev, thlev, tdlev);
    goto label_31200;
  label_22103:
    decay0_nucltransK(prng_, event_, 1.490, 0.033, 7.5e-4, 0.9e-4, tclev, thlev, tdlev);
    goto label_72000;
  label_22104:
    decay0_nucltransK(prng_, event_, 0.903, 0.033, 3.0e-3, 0., tclev, thlev, tdlev);
    goto label_13070;
  label_22105:
    decay0_nucltransK(prng_, event_, 0.646, 0.033, 6.5e-3, 0., tclev, thlev, tdlev);
    goto label_15640;
  label_2194:
    decay0_beta(prng_, event_, 0.726, 53., 0., 0., t);
    ////    label_21940  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 25.07)
      goto label_21941;
    if (p <= 78.72)
      goto label_21942;
    if (p <= 92.79)
      goto label_21943;
    if (p <= 94.72)
      goto label_21944;
    if (p <= 97.36)
      goto label_21945;
    goto label_21946;
  label_21941:
    decay0_nucltransK(prng_, event_, 2.194, 0.033, 3.0e-4, 3.1e-4, tclev, thlev, tdlev);
    return;
  label_21942:
    decay0_nucltransK(prng_, event_, 1.882, 0.033, 4.5e-4, 1.9e-4, tclev, thlev, tdlev);
    goto label_31200;
  label_21943:
    decay0_nucltransK(prng_, event_, 1.474, 0.033, 7.5e-4, 0.9e-4, tclev, thlev, tdlev);
    goto label_72000;
  label_21944:
    decay0_nucltransK(prng_, event_, 0.886, 0.033, 3.0e-3, 0., tclev, thlev, tdlev);
    goto label_13070;
  label_21945:
    decay0_nucltransK(prng_, event_, 0.881, 0.033, 3.0e-3, 0., tclev, thlev, tdlev);
    goto label_13130;
  label_21946:
    decay0_nucltransK(prng_, event_, 0.860, 0.033, 3.4e-3, 0., tclev, thlev, tdlev);
    goto label_13330;
  label_2136:
    decay0_beta(prng_, event_, 0.784, 53., 0., 0., t);
    ////    label_21360  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 57.73)
      goto label_21361;
    if (p <= 69.61)
      goto label_21362;
    if (p <= 75.10)
      goto label_21363;
    if (p <= 79.32)
      goto label_21364;
    if (p <= 80.12)
      goto label_21365;
    if (p <= 82.23)
      goto label_21366;
    if (p <= 86.03)
      goto label_21367;
    if (p <= 89.41)
      goto label_21368;
    if (p <= 94.94)
      goto label_21369;
    goto label_21370;
  label_21361:
    decay0_nucltransK(prng_, event_, 2.136, 0.033, 3.0e-4, 2.9e-4, tclev, thlev, tdlev);
    return;
  label_21362:
    decay0_nucltransK(prng_, event_, 1.824, 0.033, 5.0e-4, 1.7e-4, tclev, thlev, tdlev);
    goto label_31200;
  label_21363:
    decay0_nucltransK(prng_, event_, 1.417, 0.033, 1.0e-3, 0.8e-4, tclev, thlev, tdlev);
    goto label_72000;
  label_21364:
    decay0_nucltransK(prng_, event_, 1.350, 0.033, 1.2e-3, 0.7e-4, tclev, thlev, tdlev);
    goto label_78700;
  label_21365:
    decay0_nucltransK(prng_, event_, 1.222, 0.033, 1.0e-3, 0.1e-4, tclev, thlev, tdlev);
    goto label_91500;
  label_21366:
    decay0_nucltransK(prng_, event_, 0.897, 0.033, 3.0e-3, 0., tclev, thlev, tdlev);
    goto label_12400;
  label_21367:
    decay0_nucltransK(prng_, event_, 0.829, 0.033, 3.7e-3, 0., tclev, thlev, tdlev);
    goto label_13070;
  label_21368:
    decay0_nucltransK(prng_, event_, 0.824, 0.033, 3.7e-3, 0., tclev, thlev, tdlev);
    goto label_13130;
  label_21369:
    decay0_nucltransK(prng_, event_, 0.803, 0.033, 4.0e-3, 0., tclev, thlev, tdlev);
    goto label_13330;
  label_21370:
    decay0_nucltransK(prng_, event_, 0.763, 0.033, 3.2e-3, 0., tclev, thlev, tdlev);
    goto label_13740;
  label_2054:
    decay0_beta(prng_, event_, 0.866, 53., 0., 0., t);
  label_20540:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 12.21)
      goto label_20541;
    if (p <= 24.15)
      goto label_20542;
    if (p <= 31.12)
      goto label_20543;
    if (p <= 47.69)
      goto label_20544;
    if (p <= 58.15)
      goto label_20545;
    if (p <= 67.74)
      goto label_20546;
    if (p <= 84.31)
      goto label_20547;
    if (p <= 94.77)
      goto label_20548;
    goto label_20549;
  label_20541:
    decay0_nucltransK(prng_, event_, 2.054, 0.033, 4.0e-4, 2.5e-4, tclev, thlev, tdlev);
    return;
  label_20542:
    decay0_nucltransK(prng_, event_, 1.742, 0.033, 5.0e-4, 1.5e-4, tclev, thlev, tdlev);
    goto label_31200;
  label_20543:
    decay0_nucltransK(prng_, event_, 1.334, 0.033, 1.2e-3, 0.6e-4, tclev, thlev, tdlev);
    goto label_72000;
  label_20544:
    decay0_nucltransK(prng_, event_, 1.267, 0.033, 1.3e-3, 0.5e-4, tclev, thlev, tdlev);
    goto label_78700;
  label_20545:
    decay0_nucltransK(prng_, event_, 0.813, 0.033, 3.8e-3, 0., tclev, thlev, tdlev);
    goto label_12400;
  label_20546:
    decay0_nucltransK(prng_, event_, 0.746, 0.033, 4.5e-3, 0., tclev, thlev, tdlev);
    goto label_13070;
  label_20547:
    decay0_nucltransK(prng_, event_, 0.741, 0.033, 4.5e-3, 0., tclev, thlev, tdlev);
    goto label_13130;
  label_20548:
    decay0_nucltransK(prng_, event_, 0.720, 0.033, 5.0e-3, 0., tclev, thlev, tdlev);
    goto label_13330;
  label_20549:
    decay0_nucltransK(prng_, event_, 0.680, 0.033, 4.0e-3, 0., tclev, thlev, tdlev);
    goto label_13740;
  label_2040:
    decay0_beta(prng_, event_, 0.880, 53., 0., 0., t);
  label_20400:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 6.87)
      goto label_20401;
    if (p <= 12.09)
      goto label_20402;
    if (p <= 23.08)
      goto label_20403;
    if (p <= 75.28)
      goto label_20404;
    goto label_20405;
  label_20401:
    decay0_nucltransK(prng_, event_, 1.320, 0.033, 9.5e-4, 0.1e-4, tclev, thlev, tdlev);
    goto label_72000;
  label_20402:
    decay0_nucltransK(prng_, event_, 1.254, 0.033, 1.2e-3, 0.5e-4, tclev, thlev, tdlev);
    goto label_78700;
  label_20403:
    decay0_nucltransK(prng_, event_, 0.727, 0.033, 5.0e-3, 0., tclev, thlev, tdlev);
    goto label_13130;
  label_20404:
    decay0_nucltransK(prng_, event_, 0.667, 0.033, 6.0e-3, 0., tclev, thlev, tdlev);
    goto label_13740;
  label_20405:
    decay0_nucltransK(prng_, event_, 0.369, 0.033, 2.5e-2, 0., tclev, thlev, tdlev);
    goto label_16710;
  label_2025:
    decay0_beta(prng_, event_, 0.895, 53., 0., 0., t);
  label_20250:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 4.60)
      goto label_20251;
    if (p <= 25.61)
      goto label_20252;
    if (p <= 40.94)
      goto label_20253;
    if (p <= 47.75)
      goto label_20254;
    if (p <= 54.00)
      goto label_20255;
    if (p <= 64.79)
      goto label_20256;
    goto label_20257;
  label_20251:
    decay0_nucltransK(prng_, event_, 2.025, 0.033, 3.5e-4, 2.2e-4, tclev, thlev, tdlev);
    return;
  label_20252:
    decay0_nucltransK(prng_, event_, 1.713, 0.033, 5.0e-4, 1.4e-4, tclev, thlev, tdlev);
    goto label_31200;
  label_20253:
    decay0_nucltransK(prng_, event_, 1.306, 0.033, 1.2e-3, 0.6e-4, tclev, thlev, tdlev);
    goto label_72000;
  label_20254:
    decay0_nucltransK(prng_, event_, 1.239, 0.033, 1.3e-3, 0.5e-4, tclev, thlev, tdlev);
    goto label_78700;
  label_20255:
    decay0_nucltransK(prng_, event_, 0.718, 0.033, 1.4e-3, 0., tclev, thlev, tdlev);
    goto label_13070;
  label_20256:
    decay0_nucltransK(prng_, event_, 0.713, 0.033, 5.0e-3, 0., tclev, thlev, tdlev);
    goto label_13130;
  label_20257:
    decay0_nucltransK(prng_, event_, 0.461, 0.033, 1.5e-2, 0., tclev, thlev, tdlev);
    goto label_15640;
  label_1718:
    decay0_beta(prng_, event_, 1.202, 53., 0., 0., t);
  label_17180:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 30.02)
      goto label_17181;
    if (p <= 35.59)
      goto label_17182;
    if (p <= 45.41)
      goto label_17183;
    if (p <= 81.39)
      goto label_17184;
    if (p <= 81.97)
      goto label_17185;
    if (p <= 85.56)
      goto label_17186;
    if (p <= 94.43)
      goto label_17187;
    if (p <= 96.88)
      goto label_17188;
    if (p <= 99.43)
      goto label_17189;
    goto label_17190;
  label_17181:
    decay0_nucltransK(prng_, event_, 1.718, 0.033, 6.0e-4, 1.4e-4, tclev, thlev, tdlev);
    return;
  label_17182:
    decay0_nucltransK(prng_, event_, 1.406, 0.033, 1.2e-3, 0.7e-4, tclev, thlev, tdlev);
    goto label_31200;
  label_17183:
    decay0_nucltransK(prng_, event_, 0.998, 0.033, 2.4e-3, 0., tclev, thlev, tdlev);
    goto label_72000;
  label_17184:
    decay0_nucltransK(prng_, event_, 0.931, 0.033, 2.7e-3, 0., tclev, thlev, tdlev);
    goto label_78700;
  label_17185:
    decay0_nucltransK(prng_, event_, 0.803, 0.033, 1.1e-3, 0., tclev, thlev, tdlev);
    goto label_91500;
  label_17186:
    decay0_nucltransK(prng_, event_, 0.478, 0.033, 1.3e-2, 0., tclev, thlev, tdlev);
    goto label_12400;
  label_17187:
    decay0_nucltransK(prng_, event_, 0.410, 0.033, 2.0e-2, 0., tclev, thlev, tdlev);
    goto label_13070;
  label_17188:
    decay0_nucltransK(prng_, event_, 0.405, 0.033, 2.0e-2, 0., tclev, thlev, tdlev);
    goto label_13130;
  label_17189:
    decay0_nucltransK(prng_, event_, 0.384, 0.033, 2.5e-2, 0., tclev, thlev, tdlev);
    goto label_13330;
  label_17190:
    decay0_nucltransK(prng_, event_, 0.344, 0.033, 3.0e-2, 0., tclev, thlev, tdlev);
    goto label_13740;
  label_1671:
    decay0_beta(prng_, event_, 1.249, 53., 0., 0., t);
  label_16710:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 9.59)
      goto label_16711;
    if (p <= 15.22)
      goto label_16712;
    if (p <= 28.40)
      goto label_16713;
    if (p <= 71.54)
      goto label_16714;
    if (p <= 78.73)
      goto label_16715;
    if (p <= 83.94)
      goto label_16716;
    goto label_16717;
  label_16711:
    decay0_nucltransK(prng_, event_, 1.671, 0.033, 5.0e-4, 0.7e-4, tclev, thlev, tdlev);
    return;
  label_16712:
    decay0_nucltransK(prng_, event_, 1.359, 0.033, 1.2e-3, 0.7e-4, tclev, thlev, tdlev);
    goto label_31200;
  label_16713:
    decay0_nucltransK(prng_, event_, 0.952, 0.033, 2.6e-3, 0., tclev, thlev, tdlev);
    goto label_72000;
  label_16714:
    decay0_nucltransK(prng_, event_, 0.884, 0.033, 3.2e-3, 0., tclev, thlev, tdlev);
    goto label_78700;
  label_16715:
    decay0_nucltransK(prng_, event_, 0.432, 0.033, 1.8e-2, 0., tclev, thlev, tdlev);
    goto label_12400;
  label_16716:
    decay0_nucltransK(prng_, event_, 0.359, 0.033, 3.0e-2, 0., tclev, thlev, tdlev);
    goto label_13130;
  label_16717:
    decay0_nucltransK(prng_, event_, 0.338, 0.033, 3.5e-2, 0., tclev, thlev, tdlev);
    goto label_13330;
  label_1564:
    decay0_beta(prng_, event_, 1.356, 53., 0., 0., t);
  label_15640:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 28.18)
      goto label_15641;
    if (p <= 92.95)
      goto label_15642;
    if (p <= 96.86)
      goto label_15643;
    if (p <= 97.85)
      goto label_15644;
    if (p <= 98.46)
      goto label_15645;
    if (p <= 98.83)
      goto label_15646;
    goto label_15647;
  label_15641:
    decay0_nucltransK(prng_, event_, 1.252, 0.033, 1.3e-3, 0.5e-4, tclev, thlev, tdlev);
    goto label_31200;
  label_15642:
    decay0_nucltransK(prng_, event_, 0.844, 0.033, 3.5e-3, 0., tclev, thlev, tdlev);
    goto label_72000;
  label_15643:
    decay0_nucltransK(prng_, event_, 0.778, 0.033, 4.2e-3, 0., tclev, thlev, tdlev);
    goto label_78700;
  label_15644:
    decay0_nucltransK(prng_, event_, 0.324, 0.033, 3.7e-2, 0., tclev, thlev, tdlev);
    goto label_12400;
  label_15645:
    decay0_nucltransK(prng_, event_, 0.251, 0.033, 7.5e-2, 0., tclev, thlev, tdlev);
    goto label_13130;
  label_15646:
    decay0_nucltransK(prng_, event_, 0.231, 0.033, 8.5e-2, 0., tclev, thlev, tdlev);
    goto label_13330;
  label_15647:
    decay0_nucltransK(prng_, event_, 0.191, 0.033, 1.5e-1, 0., tclev, thlev, tdlev);
    goto label_13740;
  label_1374:
    decay0_beta(prng_, event_, 1.546, 53., 0., 0., t);
  label_13740:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 56.13)
      goto label_13741;
    if (p <= 14.62)
      goto label_13742;
    goto label_13743;
  label_13741:
    decay0_nucltransK(prng_, event_, 1.062, 0.033, 1.5e-3, 0., tclev, thlev, tdlev);
    goto label_31200;
  label_13742:
    decay0_nucltransK(prng_, event_, 0.654, 0.033, 4.5e-3, 0., tclev, thlev, tdlev);
    goto label_72000;
  label_13743:
    decay0_nucltransK(prng_, event_, 0.587, 0.033, 8.5e-3, 0., tclev, thlev, tdlev);
    goto label_78700;
  label_1333:
    decay0_beta(prng_, event_, 1.587, 53., 0., 0., t);
  label_13330:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 74.49)
      goto label_13331;
    if (p <= 94.05)
      goto label_13332;
    if (p <= 96.28)
      goto label_13333;
    if (p <= 99.83)
      goto label_13334;
    goto label_13335;
  label_13331:
    decay0_nucltransK(prng_, event_, 1.333, 0.033, 1.2e-3, 0.6e-4, tclev, thlev, tdlev);
    return;
  label_13332:
    decay0_nucltransK(prng_, event_, 1.021, 0.033, 2.3e-3, 0., tclev, thlev, tdlev);
    goto label_31200;
  label_13333:
    decay0_nucltransK(prng_, event_, 0.614, 0.033, 7.0e-3, 0., tclev, thlev, tdlev);
    goto label_72000;
  label_13334:
    decay0_nucltransK(prng_, event_, 0.546, 0.033, 9.5e-3, 0., tclev, thlev, tdlev);
    goto label_78700;
  label_13335:
    decay0_nucltransK(prng_, event_, 0.418, 0.033, 1.5e-2, 0., tclev, thlev, tdlev);
    goto label_91500;
  label_1313:
    decay0_beta(prng_, event_, 1.607, 53., 0., 0., t);
  label_13130:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 17.45)
      goto label_13131;
    if (p <= 91.78)
      goto label_13132;
    if (p <= 95.27)
      goto label_13133;
    goto label_13134;
  label_13131:
    decay0_nucltransK(prng_, event_, 1.313, 0.033, 9.0e-4, 0., tclev, thlev, tdlev);
    return;
  label_13132:
    decay0_nucltransK(prng_, event_, 1.001, 0.033, 2.5e-3, 0., tclev, thlev, tdlev);
    goto label_31200;
  label_13133:
    decay0_nucltransK(prng_, event_, 0.593, 0.033, 8.5e-3, 0., tclev, thlev, tdlev);
    goto label_72000;
  label_13134:
    decay0_nucltransK(prng_, event_, 0.526, 0.033, 1.2e-2, 0., tclev, thlev, tdlev);
    goto label_78700;
  label_13070:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 33.13)
      goto label_13071;
    if (p <= 75.46)
      goto label_13072;
    if (p <= 81.59)
      goto label_13073;
    if (p <= 82.76)
      goto label_13074;
    if (p <= 84.66)
      goto label_13075;
    goto label_13076;
  label_13071:
    decay0_nucltransK(prng_, event_, 1.307, 0.033, 1.2e-3, 0.5e-4, tclev, thlev, tdlev);
    return;
  label_13072:
    decay0_nucltransK(prng_, event_, 0.995, 0.033, 2.5e-3, 0., tclev, thlev, tdlev);
    goto label_31200;
  label_13073:
    decay0_nucltransK(prng_, event_, 0.588, 0.033, 8.5e-3, 0., tclev, thlev, tdlev);
    goto label_72000;
  label_13074:
    decay0_nucltransK(prng_, event_, 0.520, 0.033, 8.5e-3, 0., tclev, thlev, tdlev);
    goto label_78700;
  label_13075:
    decay0_nucltransK(prng_, event_, 0.394, 0.033, 2.0e-2, 0., tclev, thlev, tdlev);
    goto label_91300;
  label_13076:
    decay0_nucltransK(prng_, event_, 0.392, 0.033, 2.2e-2, 0., tclev, thlev, tdlev);
    goto label_91500;
  label_1240:
    decay0_beta(prng_, event_, 1.680, 53., 0., 0., t);
  label_12400:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 24.03)
      goto label_12401;
    if (p <= 81.24)
      goto label_12402;
    if (p <= 86.27)
      goto label_12403;
    goto label_12404;
  label_12401:
    decay0_nucltransK(prng_, event_, 1.240, 0.033, 1.2e-3, 0., tclev, thlev, tdlev);
    return;
  label_12402:
    decay0_nucltransK(prng_, event_, 0.928, 0.033, 2.7e-3, 0., tclev, thlev, tdlev);
    goto label_31200;
  label_12403:
    decay0_nucltransK(prng_, event_, 0.520, 0.033, 1.2e-2, 0., tclev, thlev, tdlev);
    goto label_72000;
  label_12404:
    decay0_nucltransK(prng_, event_, 0.453, 0.033, 1.5e-2, 0., tclev, thlev, tdlev);
    goto label_78700;
  label_91500:
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 0.915, 0.033, 2.8e-3, 0., tclev, thlev, tdlev);
    return;
  label_91300:
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 0.913, 0.033, 2.0e-3, 0., tclev, thlev, tdlev);
    return;
  label_78700:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 78.49)
      goto label_78701;
    if (p <= 91.28)
      goto label_78702;
    goto label_78703;
  label_78701:
    decay0_nucltransK(prng_, event_, 0.787, 0.033, 3.0e-3, 0., tclev, thlev, tdlev);
    return;
  label_78702:
    decay0_nucltransK(prng_, event_, 0.475, 0.033, 1.2e-2, 0., tclev, thlev, tdlev);
    goto label_31200;
  label_78703:
    decay0_nucltransK(prng_, event_, 0.067, 0.033, 4.9, 0., tclev, thlev, tdlev);
    goto label_72000;
  label_720:
    decay0_beta(prng_, event_, 2.200, 53., 0., 0., t);
  label_72000:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 24.72)
      goto label_72001;
    goto label_72002;
  label_72001:
    decay0_nucltransK(prng_, event_, 0.720, 0.033, 5.0e-3, 0., tclev, thlev, tdlev);
    return;
  label_72002:
    decay0_nucltransK(prng_, event_, 0.408, 0.033, 2.0e-2, 0., tclev, thlev, tdlev);
    goto label_31200;
  label_312:
    decay0_beta(prng_, event_, 2.608, 53., 0., 0., t);
  label_31200:
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 0.312, 0.033, 3.5e-2, 0., tclev, thlev, tdlev);
    return;
    return;
  }
  // end of Te133.f

} // end of namespace bxdecay0

// end of Te133.cc
// Local Variables: --
// mode: c++ --
// End: --
