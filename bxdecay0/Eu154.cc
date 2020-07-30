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
#include <bxdecay0/Eu154.h>

// Standard library:
#include <cmath>
#include <sstream>

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

  void Eu154(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_)
  {
    double t;
    double tdlev;
    double p;
    double pbeta;
    double pdecay;
    double tclev;
    double thlev;
    double thnuc;
    // Scheme of 154Eu decay ("Table of Isotopes", 8th ed., 1996 and
    // NDS 69(1993)507).
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 13.11.1996.
    // VIT, correction to the 1fnu shape for Qbeta=1.846, 13.11.2007.
    thnuc  = 2.711670e8;
    tdnuc_ = tcnuc_ - thnuc / std::log(2.) * std::log(prng_());
    tclev  = 0.;
    pdecay = 100. * prng_();
    if (pdecay <= 0.020) {
      goto label_1; // 0.020% EC to 154Sm
    }
    goto label_2;   // 99.980% b- to 154Gd
  label_1:
    decay0_gamma(prng_, event_, 0.049, 0., 0., tdlev);
    if (pdecay <= 0.005) {
      goto label_267;
    }
    goto label_82;
  label_267:
    thlev = 172.e-12;
    decay0_nucltransK(prng_, event_, 0.185, 0.047, 2.7e-1, 0., tclev, thlev, tdlev);
    goto label_82;
  label_82:
    thlev = 3.02e-9;
    decay0_nucltransK(prng_, event_, 0.082, 0.047, 4.9 + 0, 0., tclev, thlev, tdlev);
    return;
  label_2:
    pbeta = 100. * prng_();
    if (pbeta <= 0.019) {
      goto label_1839;
    }
    if (pbeta <= 0.087) {
      goto label_1797;
    }
    if (pbeta <= 28.587) {
      goto label_1720;
    }
    if (pbeta <= 29.417) {
      goto label_1661;
    }
    if (pbeta <= 29.564) {
      goto label_1646;
    }
    if (pbeta <= 31.174) {
      goto label_1617;
    }
    if (pbeta <= 31.271) {
      goto label_1560;
    }
    if (pbeta <= 31.571) {
      goto label_1531;
    }
    if (pbeta <= 31.679) {
      goto label_1418;
    }
    if (pbeta <= 67.879) {
      goto label_1398;
    }
    if (pbeta <= 68.599) {
      goto label_1264;
    }
    if (pbeta <= 68.909) {
      goto label_1252;
    }
    if (pbeta <= 85.610) {
      goto label_1128;
    }
    if (pbeta <= 89.110) {
      goto label_996;
    }
    if (pbeta <= 89.810) {
      goto label_815;
    }
    if (pbeta <= 90.000) {
      goto label_371;
    }
    goto label_123;
  label_1839:
    decay0_beta(prng_, event_, 0.130, 64., 0., 0., t);
    ////label_18390  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 4.0) {
      goto label_18391;
    }
    if (p <= 6.8) {
      goto label_18392;
    }
    if (p <= 38.1) {
      goto label_18393;
    }
    if (p <= 87.8) {
      goto label_18394;
    }
    if (p <= 94.0) {
      goto label_18395;
    }
    goto label_18396;
  label_18391:
    decay0_nucltransK(prng_, event_, 1.839, 0.050, 1.0e-3, 1.0e-4, tclev, thlev, tdlev);
    return;
  label_18392:
    decay0_nucltransK(prng_, event_, 1.717, 0.050, 1.1e-3, 0.7e-4, tclev, thlev, tdlev);
    goto label_12300;
  label_18393:
    decay0_nucltransK(prng_, event_, 1.023, 0.050, 3.8e-3, 0., tclev, thlev, tdlev);
    goto label_81500;
  label_18394:
    decay0_nucltransK(prng_, event_, 0.790, 0.050, 5.0e-3, 0., tclev, thlev, tdlev);
    goto label_10480;
  label_18395:
    decay0_nucltransK(prng_, event_, 0.193, 0.050, 2.8e-1, 0., tclev, thlev, tdlev);
    goto label_16460;
  label_18396:
    decay0_nucltransK(prng_, event_, 0.063, 0.050, 1.4e+1, 0., tclev, thlev, tdlev);
    goto label_17750;
  label_1797:
    decay0_beta(prng_, event_, 0.172, 64., 0., 0., t);
    ////label_17970  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 2.4) {
      goto label_17971;
    }
    if (p <= 4.0) {
      goto label_17972;
    }
    if (p <= 15.3) {
      goto label_17973;
    }
    if (p <= 58.7) {
      goto label_17974;
    }
    if (p <= 77.0) {
      goto label_17975;
    }
    if (p <= 82.0) {
      goto label_17976;
    }
    if (p <= 91.6) {
      goto label_17977;
    }
    if (p <= 99.9) {
      goto label_17978;
    }
    goto label_17979;
  label_17971:
    decay0_nucltransK(prng_, event_, 1.674, 0.050, 5.0e-4, 0.9e-4, tclev, thlev, tdlev);
    goto label_12300;
  label_17972:
    decay0_nucltransK(prng_, event_, 1.426, 0.050, 6.0e-4, 0.4e-4, tclev, thlev, tdlev);
    goto label_37100;
  label_17973:
    decay0_nucltransK(prng_, event_, 0.982, 0.050, 1.2e-3, 0., tclev, thlev, tdlev);
    goto label_81500;
  label_17974:
    decay0_nucltransK(prng_, event_, 0.801, 0.050, 1.8e-3, 0., tclev, thlev, tdlev);
    goto label_99600;
  label_17975:
    decay0_nucltransK(prng_, event_, 0.669, 0.050, 2.5e-3, 0., tclev, thlev, tdlev);
    goto label_11280;
  label_17976:
    decay0_nucltransK(prng_, event_, 0.556, 0.050, 1.1e-2, 0., tclev, thlev, tdlev);
    goto label_12410;
  label_17977:
    decay0_nucltransK(prng_, event_, 0.533, 0.050, 4.0e-3, 0., tclev, thlev, tdlev);
    goto label_12640;
  label_17978:
    decay0_nucltransK(prng_, event_, 0.393, 0.050, 3.0e-2, 0., tclev, thlev, tdlev);
    goto label_14040;
  label_17979:
    decay0_nucltransK(prng_, event_, 0.266, 0.050, 2.0e-2, 0., tclev, thlev, tdlev);
    goto label_15310;
  label_17750:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 19.6) {
      goto label_17751;
    }
    if (p <= 62.3) {
      goto label_17752;
    }
    if (p <= 79.4) {
      goto label_17753;
    }
    if (p <= 88.4) {
      goto label_17754;
    }
    if (p <= 92.2) {
      goto label_17755;
    }
    if (p <= 98.7) {
      goto label_17756;
    }
    goto label_17757;
  label_17751:
    decay0_nucltransK(prng_, event_, 1.776, 0.050, 1.0e-3, 0.8e-4, tclev, thlev, tdlev);
    return;
  label_17752:
    decay0_nucltransK(prng_, event_, 1.652, 0.050, 1.6e-3, 0.6e-4, tclev, thlev, tdlev);
    goto label_12300;
  label_17753:
    decay0_nucltransK(prng_, event_, 1.405, 0.050, 1.4e-3, 0.2e-4, tclev, thlev, tdlev);
    goto label_37100;
  label_17754:
    decay0_nucltransK(prng_, event_, 1.095, 0.050, 2.3e-3, 0., tclev, thlev, tdlev);
    goto label_68100;
  label_17755:
    decay0_nucltransK(prng_, event_, 0.960, 0.050, 3.0e-3, 0., tclev, thlev, tdlev);
    goto label_81500;
  label_17756:
    decay0_nucltransK(prng_, event_, 0.728, 0.050, 6.0e-3, 0., tclev, thlev, tdlev);
    goto label_10480;
  label_17757:
    decay0_nucltransK(prng_, event_, 0.648, 0.050, 1.4e-2, 0., tclev, thlev, tdlev);
    goto label_11280;
  label_1720:
    decay0_beta(prng_, event_, 0.249, 64., 0., 0., t);
    ////label_17200  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 6.272) {
      goto label_17201;
    }
    if (p <= 9.404) {
      goto label_17202;
    }
    if (p <= 79.950) {
      goto label_17203;
    }
    if (p <= 97.361) {
      goto label_17204;
    }
    if (p <= 98.150) {
      goto label_17205;
    }
    if (p <= 98.362) {
      goto label_17206;
    }
    if (p <= 98.594) {
      goto label_17207;
    }
    if (p <= 98.629) {
      goto label_17208;
    }
    if (p <= 98.665) {
      goto label_17209;
    }
    if (p <= 98.674) {
      goto label_17210;
    }
    if (p <= 99.513) {
      goto label_17211;
    }
    if (p <= 99.986) {
      goto label_17212;
    }
    goto label_17213;
  label_17201:
    decay0_nucltransK(prng_, event_, 1.596, 0.050, 5.0e-4, 0.7e-4, tclev, thlev, tdlev);
    goto label_12300;
  label_17202:
    decay0_nucltransK(prng_, event_, 0.904, 0.050, 1.4e-3, 0., tclev, thlev, tdlev);
    goto label_81500;
  label_17203:
    decay0_nucltransK(prng_, event_, 0.723, 0.050, 2.2e-3, 0., tclev, thlev, tdlev);
    goto label_99600;
  label_17204:
    decay0_nucltransK(prng_, event_, 0.592, 0.050, 3.3e-3, 0., tclev, thlev, tdlev);
    goto label_11280;
  label_17205:
    decay0_nucltransK(prng_, event_, 0.478, 0.050, 1.6e-2, 0., tclev, thlev, tdlev);
    goto label_12410;
  label_17206:
    decay0_nucltransK(prng_, event_, 0.468, 0.050, 3.5e-2, 0., tclev, thlev, tdlev);
    goto label_12520;
  label_17207:
    decay0_nucltransK(prng_, event_, 0.322, 0.050, 9.0e-2, 0., tclev, thlev, tdlev);
    goto label_13980;
  label_17208:
    decay0_nucltransK(prng_, event_, 0.305, 0.050, 9.5e-2, 0., tclev, thlev, tdlev);
    goto label_14140;
  label_17209:
    decay0_nucltransK(prng_, event_, 0.301, 0.050, 1.6e-2, 0., tclev, thlev, tdlev);
    goto label_14180;
  label_17210:
    decay0_nucltransK(prng_, event_, 0.209, 0.050, 3.0e-1, 0., tclev, thlev, tdlev);
    goto label_15100;
  label_17211:
    decay0_nucltransK(prng_, event_, 0.188, 0.050, 5.5e-2, 0., tclev, thlev, tdlev);
    goto label_15310;
  label_17212:
    decay0_nucltransK(prng_, event_, 0.160, 0.050, 4.5e-1, 0., tclev, thlev, tdlev);
    goto label_15600;
  label_17213:
    decay0_nucltransK(prng_, event_, 0.058, 0.050, 1.2e-0, 0., tclev, thlev, tdlev);
    goto label_16610;
  label_1661:
    decay0_beta(prng_, event_, 0.308, 64., 0., 0., t);
  label_16610:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 6.03) {
      goto label_16611;
    }
    if (p <= 8.84) {
      goto label_16612;
    }
    if (p <= 75.84) {
      goto label_16613;
    }
    if (p <= 79.11) {
      goto label_16614;
    }
    if (p <= 89.76) {
      goto label_16615;
    }
    if (p <= 94.78) {
      goto label_16616;
    }
    if (p <= 95.18) {
      goto label_16617;
    }
    if (p <= 98.45) {
      goto label_16618;
    }
    goto label_16619;
  label_16611:
    decay0_nucltransK(prng_, event_, 1.538, 0.050, 1.2e-3, 0.4e-4, tclev, thlev, tdlev);
    goto label_12300;
  label_16612:
    decay0_nucltransK(prng_, event_, 1.290, 0.050, 1.8e-3, 0.1e-4, tclev, thlev, tdlev);
    goto label_37100;
  label_16613:
    decay0_nucltransK(prng_, event_, 0.845, 0.050, 4.0e-3, 0., tclev, thlev, tdlev);
    goto label_81500;
  label_16614:
    decay0_nucltransK(prng_, event_, 0.665, 0.050, 7.0e-3, 0., tclev, thlev, tdlev);
    goto label_99600;
  label_16615:
    decay0_nucltransK(prng_, event_, 0.613, 0.050, 1.2e-2, 0., tclev, thlev, tdlev);
    goto label_10480;
  label_16616:
    decay0_nucltransK(prng_, event_, 0.533, 0.050, 1.2e-2, 0., tclev, thlev, tdlev);
    goto label_11280;
  label_16617:
    decay0_nucltransK(prng_, event_, 0.420, 0.050, 1.4e-1, 0., tclev, thlev, tdlev);
    goto label_12410;
  label_16618:
    decay0_nucltransK(prng_, event_, 0.397, 0.050, 3.5e-2, 0., tclev, thlev, tdlev);
    goto label_12640;
  label_16619:
    decay0_nucltransK(prng_, event_, 0.130, 0.050, 1.0e-0, 0., tclev, thlev, tdlev);
    goto label_15310;
  label_1646:
    decay0_beta(prng_, event_, 0.323, 64., 0., 0., t);
  label_16460:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 1.26) {
      goto label_16461;
    }
    if (p <= 2.57) {
      goto label_16462;
    }
    if (p <= 3.97) {
      goto label_16463;
    }
    if (p <= 6.77) {
      goto label_16464;
    }
    if (p <= 51.79) {
      goto label_16465;
    }
    if (p <= 56.52) {
      goto label_16466;
    }
    if (p <= 82.63) {
      goto label_16467;
    }
    if (p <= 84.79) {
      goto label_16468;
    }
    if (p <= 89.70) {
      goto label_16469;
    }
    if (p <= 91.41) {
      goto label_16470;
    }
    if (p <= 95.37) {
      goto label_16471;
    }
    if (p <= 99.02) {
      goto label_16472;
    }
    goto label_16473;
  label_16461:
    decay0_nucltransK(prng_, event_, 1.523, 0.050, 1.2e-3, 0.4e-4, tclev, thlev, tdlev);
    goto label_12300;
  label_16462:
    decay0_nucltransK(prng_, event_, 1.275, 0.050, 1.8e-3, 0.1e-4, tclev, thlev, tdlev);
    goto label_37100;
  label_16463:
    decay0_nucltransK(prng_, event_, 0.928, 0.050, 3.5e-3, 0., tclev, thlev, tdlev);
    goto label_71800;
  label_16464:
    decay0_nucltransK(prng_, event_, 0.830, 0.050, 5.7e-3, 0., tclev, thlev, tdlev);
    goto label_81500;
  label_16465:
    decay0_nucltransK(prng_, event_, 0.650, 0.050, 7.3e-3, 0., tclev, thlev, tdlev);
    goto label_99600;
  label_16466:
    decay0_nucltransK(prng_, event_, 0.598, 0.050, 1.4e-2, 0., tclev, thlev, tdlev);
    goto label_10480;
  label_16467:
    decay0_nucltransK(prng_, event_, 0.518, 0.050, 1.3e-2, 0., tclev, thlev, tdlev);
    goto label_11280;
  label_16468:
    decay0_nucltransK(prng_, event_, 0.394, 0.050, 8.5e-3, 0., tclev, thlev, tdlev);
    goto label_12520;
  label_16469:
    decay0_nucltransK(prng_, event_, 0.382, 0.050, 3.4e-2, 0., tclev, thlev, tdlev);
    goto label_12640;
  label_16470:
    decay0_nucltransK(prng_, event_, 0.368, 0.050, 9.0e-3, 0., tclev, thlev, tdlev);
    goto label_12770;
  label_16471:
    decay0_nucltransK(prng_, event_, 0.352, 0.050, 3.5e-2, 0., tclev, thlev, tdlev);
    goto label_12940;
  label_16472:
    decay0_nucltransK(prng_, event_, 0.242, 0.050, 3.5e-2, 0., tclev, thlev, tdlev);
    goto label_14040;
  label_16473:
    decay0_nucltransK(prng_, event_, 0.228, 0.050, 1.4e-1, 0., tclev, thlev, tdlev);
    goto label_14180;
  label_1617:
    decay0_beta(prng_, event_, 0.352, 64., 0., 0., t);
    ////label_16170  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 43.76) {
      goto label_16171;
    }
    if (p <= 97.79) {
      goto label_16172;
    }
    if (p <= 97.80) {
      goto label_16173;
    }
    if (p <= 98.37) {
      goto label_16174;
    }
    if (p <= 99.00) {
      goto label_16175;
    }
    if (p <= 99.43) {
      goto label_16176;
    }
    if (p <= 99.73) {
      goto label_16177;
    }
    if (p <= 99.85) {
      goto label_16178;
    }
    goto label_16179;
  label_16171:
    decay0_nucltransK(prng_, event_, 1.494, 0.050, 5.6e-4, 0.5e-4, tclev, thlev, tdlev);
    goto label_12300;
  label_16172:
    decay0_nucltransK(prng_, event_, 1.246, 0.050, 7.6e-4, 0.2e-4, tclev, thlev, tdlev);
    goto label_37100;
  label_16173:
    decay0_nucltransK(prng_, event_, 0.801, 0.050, 1.8e-3, 0., tclev, thlev, tdlev);
    goto label_81500;
  label_16174:
    decay0_nucltransK(prng_, event_, 0.621, 0.050, 2.8e-3, 0., tclev, thlev, tdlev);
    goto label_99600;
  label_16175:
    decay0_nucltransK(prng_, event_, 0.569, 0.050, 3.5e-3, 0., tclev, thlev, tdlev);
    goto label_10480;
  label_16176:
    decay0_nucltransK(prng_, event_, 0.488, 0.050, 5.0e-3, 0., tclev, thlev, tdlev);
    goto label_11280;
  label_16177:
    decay0_nucltransK(prng_, event_, 0.481, 0.050, 5.0e-3, 0., tclev, thlev, tdlev);
    goto label_11360;
  label_16178:
    decay0_nucltransK(prng_, event_, 0.375, 0.050, 4.0e-2, 0., tclev, thlev, tdlev);
    goto label_12410;
  label_16179:
    decay0_nucltransK(prng_, event_, 0.219, 0.050, 2.0e-1, 0., tclev, thlev, tdlev);
    goto label_13980;
  label_1560:
    decay0_beta(prng_, event_, 0.409, 64., 0., 0., t);
  label_15600:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 90.61) {
      goto label_15601;
    }
    if (p <= 90.62) {
      goto label_15602;
    }
    if (p <= 92.94) {
      goto label_15603;
    }
    if (p <= 98.83) {
      goto label_15604;
    }
    goto label_15605;
  label_15601:
    decay0_nucltransK(prng_, event_, 1.189, 0.050, 1.1e-3, 0.1e-4, tclev, thlev, tdlev);
    goto label_37100;
  label_15602:
    decay0_nucltransK(prng_, event_, 0.563, 0.050, 6.0e-2, 0., tclev, thlev, tdlev);
    goto label_99600;
  label_15603:
    decay0_nucltransK(prng_, event_, 0.296, 0.050, 1.6e-2, 0., tclev, thlev, tdlev);
    goto label_12640;
  label_15604:
    decay0_nucltransK(prng_, event_, 0.283, 0.050, 1.7e-2, 0., tclev, thlev, tdlev);
    goto label_12770;
  label_15605:
    decay0_nucltransK(prng_, event_, 0.163, 0.050, 5.0e-1, 0., tclev, thlev, tdlev);
    goto label_13980;
  label_1531:
    decay0_beta(prng_, event_, 0.438, 64., 0., 0., t);
  label_15310:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 0.99) {
      goto label_15311;
    }
    if (p <= 4.80) {
      goto label_15312;
    }
    if (p <= 12.06) {
      goto label_15313;
    }
    if (p <= 52.17) {
      goto label_15314;
    }
    if (p <= 82.25) {
      goto label_15315;
    }
    if (p <= 90.87) {
      goto label_15316;
    }
    if (p <= 91.69) {
      goto label_15317;
    }
    if (p <= 95.70) {
      goto label_15318;
    }
    if (p <= 96.26) {
      goto label_15319;
    }
    if (p <= 96.75) {
      goto label_15320;
    }
    if (p <= 98.55) {
      goto label_15321;
    }
    if (p <= 99.59) {
      goto label_15322;
    }
    goto label_15323;
  label_15311:
    decay0_nucltransK(prng_, event_, 1.531, 0.050, 1.1e-3, 0.4e-4, tclev, thlev, tdlev);
    return;
  label_15312:
    decay0_nucltransK(prng_, event_, 1.408, 0.050, 3.7e-3, 0.2e-4, tclev, thlev, tdlev);
    goto label_12300;
  label_15313:
    decay0_nucltransK(prng_, event_, 1.161, 0.050, 2.2e-3, 0.1e-4, tclev, thlev, tdlev);
    goto label_37100;
  label_15314:
    decay0_nucltransK(prng_, event_, 0.851, 0.050, 3.9e-3, 0., tclev, thlev, tdlev);
    goto label_68100;
  label_15315:
    decay0_nucltransK(prng_, event_, 0.716, 0.050, 1.3e-2, 0., tclev, thlev, tdlev);
    goto label_81500;
  label_15316:
    decay0_nucltransK(prng_, event_, 0.535, 0.050, 2.5e-2, 0., tclev, thlev, tdlev);
    goto label_99600;
  label_15317:
    decay0_nucltransK(prng_, event_, 0.484, 0.050, 1.6e-2, 0., tclev, thlev, tdlev);
    goto label_10480;
  label_15318:
    decay0_nucltransK(prng_, event_, 0.404, 0.050, 2.8e-2, 0., tclev, thlev, tdlev);
    goto label_11280;
  label_15319:
    decay0_nucltransK(prng_, event_, 0.290, 0.050, 1.8e-2, 0., tclev, thlev, tdlev);
    goto label_12410;
  label_15320:
    decay0_nucltransK(prng_, event_, 0.280, 0.050, 1.9e-2, 0., tclev, thlev, tdlev);
    goto label_12520;
  label_15321:
    decay0_nucltransK(prng_, event_, 0.267, 0.050, 8.0e-2, 0., tclev, thlev, tdlev);
    goto label_12640;
  label_15322:
    decay0_nucltransK(prng_, event_, 0.238, 0.050, 1.2e-1, 0., tclev, thlev, tdlev);
    goto label_12940;
  label_15323:
    decay0_nucltransK(prng_, event_, 0.117, 0.050, 2.0e-1, 0., tclev, thlev, tdlev);
    goto label_14140;
  label_15100:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 20.) {
      goto label_15101;
    }
    goto label_15102;
  label_15101:
    decay0_nucltransK(prng_, event_, 1.510, 0.050, 6.0e-4, 0.5e-4, tclev, thlev, tdlev);
    return;
  label_15102:
    decay0_nucltransK(prng_, event_, 1.387, 0.050, 6.5e-4, 0.3e-4, tclev, thlev, tdlev);
    goto label_12300;
  label_1418:
    decay0_beta(prng_, event_, 0.551, 64., 0., 0., t);
  label_14180:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 11.51) {
      goto label_14181;
    }
    if (p <= 20.34) {
      goto label_14182;
    }
    if (p <= 68.31) {
      goto label_14183;
    }
    if (p <= 69.27) {
      goto label_14184;
    }
    if (p <= 90.86) {
      goto label_14185;
    }
    if (p <= 91.87) {
      goto label_14186;
    }
    if (p <= 95.71) {
      goto label_14187;
    }
    if (p <= 96.56) {
      goto label_14188;
    }
    if (p <= 97.71) {
      goto label_14189;
    }
    if (p <= 98.30) {
      goto label_14190;
    }
    if (p <= 98.94) {
      goto label_14191;
    }
    if (p <= 99.45) {
      goto label_14192;
    }
    goto label_14193;
  label_14181:
    decay0_nucltransK(prng_, event_, 1.418, 0.050, 1.4e-3, 0.2e-4, tclev, thlev, tdlev);
    return;
  label_14182:
    decay0_nucltransK(prng_, event_, 1.295, 0.050, 1.6e-3, 0.1e-4, tclev, thlev, tdlev);
    goto label_12300;
  label_14183:
    decay0_nucltransK(prng_, event_, 1.047, 0.050, 2.5e-3, 0., tclev, thlev, tdlev);
    goto label_37100;
  label_14184:
    decay0_nucltransK(prng_, event_, 0.737, 0.050, 5.5e-3, 0., tclev, thlev, tdlev);
    goto label_68100;
  label_14185:
    decay0_nucltransK(prng_, event_, 0.603, 0.050, 3.8e-2, 0., tclev, thlev, tdlev);
    goto label_81500;
  label_14186:
    decay0_nucltransK(prng_, event_, 0.422, 0.050, 1.4e-1, 0., tclev, thlev, tdlev);
    goto label_99600;
  label_14187:
    decay0_nucltransK(prng_, event_, 0.371, 0.050, 3.2e-2, 0., tclev, thlev, tdlev);
    goto label_10480;
  label_14188:
    decay0_nucltransK(prng_, event_, 0.290, 0.050, 6.5e-2, 0., tclev, thlev, tdlev);
    goto label_11280;
  label_14189:
    decay0_nucltransK(prng_, event_, 0.236, 0.050, 1.2e-1, 0., tclev, thlev, tdlev);
    goto label_11820;
  label_14190:
    decay0_nucltransK(prng_, event_, 0.177, 0.050, 6.0e-2, 0., tclev, thlev, tdlev);
    goto label_12410;
  label_14191:
    decay0_nucltransK(prng_, event_, 0.167, 0.050, 7.0e-2, 0., tclev, thlev, tdlev);
    goto label_12520;
  label_14192:
    decay0_nucltransK(prng_, event_, 0.124, 0.050, 1.2e-0, 0., tclev, thlev, tdlev);
    goto label_12940;
  label_14193:
    decay0_nucltransK(prng_, event_, 0.123, 0.050, 1.2e-0, 0., tclev, thlev, tdlev);
    goto label_12960;
  label_14140:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 21.22) {
      goto label_14141;
    }
    if (p <= 97.01) {
      goto label_14142;
    }
    if (p <= 99.68) {
      goto label_14143;
    }
    if (p <= 99.79) {
      goto label_14144;
    }
    goto label_14145;
  label_14141:
    decay0_nucltransK(prng_, event_, 1.414, 0.050, 6.1e-4, 0.4e-4, tclev, thlev, tdlev);
    return;
  label_14142:
    decay0_nucltransK(prng_, event_, 1.291, 0.050, 7.2e-4, 0.2e-4, tclev, thlev, tdlev);
    goto label_12300;
  label_14143:
    decay0_nucltransK(prng_, event_, 0.599, 0.050, 3.5e-3, 0., tclev, thlev, tdlev);
    goto label_81500;
  label_14144:
    decay0_nucltransK(prng_, event_, 0.167, 0.050, 4.0e-1, 0., tclev, thlev, tdlev);
    goto label_12520;
  label_14145:
    decay0_nucltransK(prng_, event_, 0.120, 0.050, 1.8e-1, 0., tclev, thlev, tdlev);
    goto label_12940;
  label_14040:
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 1.033, 0.050, 1.1e-3, 0., tclev, thlev, tdlev);
    goto label_37100;
  label_1398:
    decay0_beta(prng_, event_, 0.571, 64., 0., 0., t);
  label_13980:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 96.877) {
      goto label_13981;
    }
    if (p <= 99.338) {
      goto label_13982;
    }
    if (p <= 99.876) {
      goto label_13983;
    }
    if (p <= 99.896) {
      goto label_13984;
    }
    if (p <= 99.902) {
      goto label_13985;
    }
    if (p <= 99.929) {
      goto label_13986;
    }
    goto label_13987;
  label_13981:
    decay0_nucltransK(prng_, event_, 1.274, 0.050, 7.4e-4, 0.2e-4, tclev, thlev, tdlev);
    goto label_12300;
  label_13982:
    decay0_nucltransK(prng_, event_, 0.582, 0.050, 3.4e-3, 0., tclev, thlev, tdlev);
    goto label_81500;
  label_13983:
    decay0_nucltransK(prng_, event_, 0.401, 0.050, 7.0e-2, 0., tclev, thlev, tdlev);
    goto label_99600;
  label_13984:
    decay0_nucltransK(prng_, event_, 0.270, 0.050, 2.2e-2, 0., tclev, thlev, tdlev);
    goto label_11280;
  label_13985:
    decay0_nucltransK(prng_, event_, 0.260, 0.050, 2.3e-2, 0., tclev, thlev, tdlev);
    goto label_11360;
  label_13986:
    decay0_nucltransK(prng_, event_, 0.156, 0.050, 9.0e-2, 0., tclev, thlev, tdlev);
    goto label_12410;
  label_13987:
    decay0_nucltransK(prng_, event_, 0.146, 0.050, 9.5e-2, 0., tclev, thlev, tdlev);
    goto label_12520;
  label_12960:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 0.73) {
      goto label_12961;
    }
    if (p <= 73.72) {
      goto label_12962;
    }
    if (p <= 74.45) {
      goto label_12963;
    }
    if (p <= 78.83) {
      goto label_12964;
    }
    goto label_12965;
  label_12961:
    decay0_electron(prng_, event_, 1.245, tclev, thlev, tdlev); // only ec
    decay0_gamma(prng_, event_, 0.050, 0., 0., tdlev);
    return;
  label_12962:
    decay0_nucltransK(prng_, event_, 1.173, 0.050, 2.2e-3, 0., tclev, thlev, tdlev);
    goto label_12300;
  label_12963:
    decay0_electron(prng_, event_, 0.565, tclev, thlev, tdlev); // only ec
    decay0_gamma(prng_, event_, 0.050, 0., 0., tdlev);
    goto label_68100;
  label_12964:
    decay0_nucltransK(prng_, event_, 0.480, 0.050, 1.6e-2, 0., tclev, thlev, tdlev);
    goto label_81500;
  label_12965:
    decay0_nucltransK(prng_, event_, 0.299, 0.050, 6.0e-2, 0., tclev, thlev, tdlev);
    goto label_99600;
  label_12940:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 0.51) {
      goto label_12941;
    }
    if (p <= 47.79) {
      goto label_12942;
    }
    if (p <= 83.25) {
      goto label_12943;
    }
    goto label_12944;
  label_12941:
    decay0_nucltransK(prng_, event_, 1.294, 0.050, 1.8e-3, 0.1e-4, tclev, thlev, tdlev);
    return;
  label_12942:
    decay0_nucltransK(prng_, event_, 1.171, 0.050, 2.2e-3, 0.1e-4, tclev, thlev, tdlev);
    goto label_12300;
  label_12943:
    decay0_nucltransK(prng_, event_, 0.923, 0.050, 3.5e-3, 0., tclev, thlev, tdlev);
    goto label_37100;
  label_12944:
    decay0_nucltransK(prng_, event_, 0.112, 0.050, 1.7e-0, 0., tclev, thlev, tdlev);
    goto label_11820;
  label_12770:
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 0.906, 0.050, 1.4e-3, 0., tclev, thlev, tdlev);
    goto label_37100;
  label_1264:
    decay0_beta(prng_, event_, 0.705, 64., 0., 0., t);
  label_12640:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 30.09) {
      goto label_12641;
    }
    if (p <= 95.92) {
      goto label_12642;
    }
    if (p <= 97.76) {
      goto label_12643;
    }
    goto label_12644;
  label_12641:
    decay0_nucltransK(prng_, event_, 1.141, 0.050, 2.1e-3, 0., tclev, thlev, tdlev);
    goto label_12300;
  label_12642:
    decay0_nucltransK(prng_, event_, 0.893, 0.050, 3.7e-3, 0., tclev, thlev, tdlev);
    goto label_37100;
  label_12643:
    decay0_nucltransK(prng_, event_, 0.546, 0.050, 1.2e-2, 0., tclev, thlev, tdlev);
    goto label_71800;
  label_12644:
    decay0_nucltransK(prng_, event_, 0.267, 0.050, 9.5e-2, 0., tclev, thlev, tdlev);
    goto label_99600;
  label_1252:
    decay0_beta(prng_, event_, 0.717, 64., 0., 0., t);
  label_12520:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 3.76) {
      goto label_12521;
    }
    if (p <= 80.51) {
      goto label_12522;
    }
    goto label_12523;
  label_12521:
    decay0_nucltransK(prng_, event_, 1.252, 0.050, 3.5e-3, 0., tclev, thlev, tdlev);
    return;
  label_12522:
    decay0_nucltransK(prng_, event_, 1.129, 0.050, 9.1e-4, 0.1e-4, tclev, thlev, tdlev);
    goto label_12300;
  label_12523:
    decay0_nucltransK(prng_, event_, 0.881, 0.050, 1.5e-3, 0., tclev, thlev, tdlev);
    goto label_37100;
  label_12410:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 54.62) {
      goto label_12411;
    }
    if (p <= 99.02) {
      goto label_12412;
    }
    if (p <= 99.68) {
      goto label_12413;
    }
    goto label_12414;
  label_12411:
    decay0_nucltransK(prng_, event_, 1.241, 0.050, 7.7e-4, 0.2e-4, tclev, thlev, tdlev);
    return;
  label_12412:
    decay0_nucltransK(prng_, event_, 1.118, 0.050, 9.3e-4, 0.1e-4, tclev, thlev, tdlev);
    goto label_12300;
  label_12413:
    decay0_nucltransK(prng_, event_, 0.561, 0.050, 4.0e-3, 0., tclev, thlev, tdlev);
    goto label_68100;
  label_12414:
    decay0_nucltransK(prng_, event_, 0.426, 0.050, 7.0e-3, 0., tclev, thlev, tdlev);
    goto label_81500;
  label_11820:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 0.21) {
      goto label_11821;
    }
    if (p <= 84.00) {
      goto label_11822;
    }
    if (p <= 84.84) {
      goto label_11823;
    }
    goto label_11824;
  label_11821:
    decay0_electron(prng_, event_, 1.132, tclev, thlev, tdlev);
    decay0_gamma(prng_, event_, 0.050, 0., 0., tdlev);
    return;
  label_11822:
    decay0_nucltransK(prng_, event_, 1.059, 0.050, 2.5e-3, 0., tclev, thlev, tdlev);
    goto label_12300;
  label_11823:
    decay0_electron(prng_, event_, 0.451, tclev, thlev, tdlev);
    decay0_gamma(prng_, event_, 0.050, 0., 0., tdlev);
    goto label_68100;
  label_11824:
    decay0_nucltransK(prng_, event_, 0.367, 0.050, 3.3e-2, 0., tclev, thlev, tdlev);
    goto label_81500;
  label_11360:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 71.94) {
      goto label_11361;
    }
    goto label_11362;
  label_11361:
    decay0_nucltransK(prng_, event_, 1.136, 0.050, 2.2e-3, 0., tclev, thlev, tdlev);
    return;
  label_11362:
    decay0_nucltransK(prng_, event_, 1.013, 0.050, 2.8e-3, 0., tclev, thlev, tdlev);
    goto label_12300;
  label_1128:
    decay0_beta(prng_, event_, 0.841, 64., 0., 0., t);
  label_11280:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 79.629) {
      goto label_11281;
    }
    if (p <= 99.855) {
      goto label_11282;
    }
    if (p <= 99.938) {
      goto label_11283;
    }
    if (p <= 99.987) {
      goto label_11284;
    }
    goto label_11285;
  label_11281:
    decay0_nucltransK(prng_, event_, 1.005, 0.050, 2.8e-3, 0., tclev, thlev, tdlev);
    goto label_12300;
  label_11282:
    decay0_nucltransK(prng_, event_, 0.757, 0.050, 5.2e-3, 0., tclev, thlev, tdlev);
    goto label_37100;
  label_11283:
    decay0_nucltransK(prng_, event_, 0.312, 0.050, 5.5e-2, 0., tclev, thlev, tdlev);
    goto label_81500;
  label_11284:
    decay0_nucltransK(prng_, event_, 0.132, 0.050, 9.5e-1, 0., tclev, thlev, tdlev);
    goto label_99600;
  label_11285:
    decay0_nucltransK(prng_, event_, 0.080, 0.050, 6.0e-0, 0., tclev, thlev, tdlev);
    goto label_10480;
  label_10480:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 23.98) {
      goto label_10481;
    }
    if (p <= 86.75) {
      goto label_10482;
    }
    if (p <= 90.58) {
      goto label_10483;
    }
    goto label_10484;
  label_10481:
    decay0_nucltransK(prng_, event_, 0.925, 0.050, 3.3e-3, 0., tclev, thlev, tdlev);
    goto label_12300;
  label_10482:
    decay0_nucltransK(prng_, event_, 0.677, 0.050, 5.1e-2, 0., tclev, thlev, tdlev);
    goto label_37100;
  label_10483:
    decay0_nucltransK(prng_, event_, 0.330, 0.050, 4.5e-2, 0., tclev, thlev, tdlev);
    goto label_71800;
  label_10484:
    decay0_nucltransK(prng_, event_, 0.232, 0.050, 1.4e-1, 0., tclev, thlev, tdlev);
    goto label_81500;
  label_996:
    decay0_beta(prng_, event_, 0.973, 64., 0., 0., t);
  label_99600:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 46.43) {
      goto label_99601;
    }
    if (p <= 98.59) {
      goto label_99602;
    }
    if (p <= 99.95) {
      goto label_99603;
    }
    if (p <= 99.98) {
      goto label_99604;
    }
    goto label_99605;
  label_99601:
    decay0_nucltransK(prng_, event_, 0.996, 0.050, 2.8e-3, 0., tclev, thlev, tdlev);
    return;
  label_99602:
    decay0_nucltransK(prng_, event_, 0.873, 0.050, 3.7e-3, 0., tclev, thlev, tdlev);
    goto label_12300;
  label_99603:
    decay0_nucltransK(prng_, event_, 0.625, 0.050, 8.0e-3, 0., tclev, thlev, tdlev);
    goto label_37100;
  label_99604:
    decay0_nucltransK(prng_, event_, 0.315, 0.050, 5.2e-2, 0., tclev, thlev, tdlev);
    goto label_68100;
  label_99605:
    decay0_nucltransK(prng_, event_, 0.181, 0.050, 3.5e-1, 0., tclev, thlev, tdlev);
    goto label_81500;
  label_815:
    decay0_beta(prng_, event_, 1.154, 64., 0., 0., t);
  label_81500:
    thlev = 6.9e-12;
    p     = 100. * prng_();
    if (p <= 17.86) {
      goto label_81501;
    }
    if (p <= 80.18) {
      goto label_81502;
    }
    if (p <= 99.75) {
      goto label_81503;
    }
    goto label_81504;
  label_81501:
    decay0_nucltransK(prng_, event_, 0.816, 0.050, 4.3e-3, 0., tclev, thlev, tdlev);
    return;
  label_81502:
    decay0_nucltransK(prng_, event_, 0.692, 0.050, 4.6e-2, 0., tclev, thlev, tdlev);
    goto label_12300;
  label_81503:
    decay0_nucltransK(prng_, event_, 0.444, 0.050, 1.9e-2, 0., tclev, thlev, tdlev);
    goto label_37100;
  label_81504:
    decay0_nucltransK(prng_, event_, 0.135, 0.050, 8.7e-1, 0., tclev, thlev, tdlev);
    goto label_68100;
  label_71800:
    thlev = 7.8e-12;
    decay0_nucltransK(prng_, event_, 0.347, 0.050, 3.9e-2, 0., tclev, thlev, tdlev);
    goto label_37100;
  label_68100:
    thlev = 4.0e-12;
    p     = 100. * prng_();
    if (p <= 2.06) {
      goto label_68101;
    }
    goto label_68102;
  label_68101:
    decay0_electron(prng_, event_, 0.631, tclev, thlev, tdlev);
    decay0_gamma(prng_, event_, 0.050, 0., 0., tdlev);
    return;
  label_68102:
    decay0_nucltransK(prng_, event_, 0.558, 0.050, 1.1e-2, 0., tclev, thlev, tdlev);
    goto label_12300;
  label_371:
    decay0_beta(prng_, event_, 1.598, 64., 0., 0., t);
  label_37100:
    thlev = 45.2e-12;
    decay0_nucltransK(prng_, event_, 0.248, 0.050, 1.1e-1, 0., tclev, thlev, tdlev);
    goto label_12300;
    // correction to the 1st forbidden non-unique shape in accordance with
    // L.M.Langer et al., PR 119(1960)1308
  label_123:
    decay0_beta1(prng_, event_, 1.846, 64., 0., 0., t, 0., -0.2280, 0.04465, 0.);
  label_12300:
    thlev = 1.186e-9;
    decay0_nucltransK(prng_, event_, 0.123, 0.050, 1.2e-0, 0., tclev, thlev, tdlev);
    return;
  }
  // end of Eu154.f

} // end of namespace bxdecay0

// end of Eu154.cc
// Local Variables: --
// mode: c++ --
// End: --
