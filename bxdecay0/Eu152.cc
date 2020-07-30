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
#include <bxdecay0/Eu152.h>

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

  void Eu152(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_)
  {
    double t;
    double tdlev;
    double p;
    double pbeta;
    double pdecay;
    double pec;
    double pKLM;
    double tclev;
    double thlev;
    double thnuc;
    // Scheme of 152Eu decay ("Table of Isotopes", 8th ed., 1996 and
    // NDS 79(1996)1).
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 16.11.1996.
    // VIT, approximate electron capture from K, L or M shells, 27.12.2006.
    // VIT, correction to the 1fnu shape for Qbeta=1.474, 13.11.2007.
    thnuc  = 4.273413e8;
    tdnuc_ = tcnuc_ - thnuc / std::log(2.) * std::log(prng_());
    tclev  = 0.;
    pdecay = 100. * prng_();
    if (pdecay <= 72.08)
      goto label_1; // EC to 152Sm
    goto label_2;   // b- to 152Gd
    // approximate electron capture from K (82%), L (14%) or M (4%) shell
  label_1:
    pKLM = 100. * prng_();
    if (pKLM <= 82.)
      decay0_gamma(prng_, event_, 0.047, 0., 0., tdlev);
    if (pKLM > 82. && pKLM <= 96.)
      decay0_gamma(prng_, event_, 0.008, 0., 0., tdlev);
    if (pKLM > 96.)
      decay0_gamma(prng_, event_, 0.001, 0., 0., tdlev);
    pec = 100. * prng_();
    if (pec <= 0.071)
      goto label_1769;
    if (pec <= 0.118)
      goto label_1757;
    if (pec <= 0.180)
      goto label_1730;
    if (pec <= 1.416)
      goto label_1650;
    if (pec <= 1.445)
      goto label_1613;
    if (pec <= 4.292)
      goto label_1579;
    if (pec <= 38.592)
      goto label_1530;
    if (pec <= 39.883)
      goto label_1372;
    if (pec <= 40.744)
      goto label_1293;
    if (pec <= 64.629)
      goto label_1234;
    if (pec <= 94.069)
      goto label_1086;
    if (pec <= 94.152)
      goto label_1041;
    if (pec <= 94.471)
      goto label_1023;
    if (pec <= 96.179)
      goto label_810;
    if (pec <= 97.359)
      goto label_366;
    goto label_122;
  label_1769:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 15.21)
      goto label_17691;
    if (p <= 25.62)
      goto label_17692;
    if (p <= 65.65)
      goto label_17693;
    if (p <= 88.07)
      goto label_17694;
    if (p <= 99.28)
      goto label_17695;
    goto label_17696;
  label_17691:
    decay0_nucltransK(prng_, event_, 1.769, 0.047, 8.0e-4, 0.9e-4, tclev, thlev, tdlev);
    return;
  label_17692:
    decay0_nucltransK(prng_, event_, 1.647, 0.047, 4.0e-4, 0.5e-4, tclev, thlev, tdlev);
    goto label_122;
  label_17693:
    decay0_nucltransK(prng_, event_, 0.959, 0.047, 2.5e-3, 0., tclev, thlev, tdlev);
    goto label_810;
  label_17694:
    decay0_nucltransK(prng_, event_, 0.806, 0.047, 1.4e-3, 0., tclev, thlev, tdlev);
    goto label_963;
  label_17695:
    decay0_nucltransK(prng_, event_, 0.536, 0.047, 1.0e-2, 0., tclev, thlev, tdlev);
    goto label_1234;
  label_17696:
    decay0_nucltransK(prng_, event_, 0.239, 0.047, 1.0e-1, 0., tclev, thlev, tdlev);
    goto label_1530;
  label_1757:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 0.43)
      goto label_17571;
    if (p <= 14.38)
      goto label_17572;
    if (p <= 81.12)
      goto label_17573;
    if (p <= 85.46)
      goto label_17574;
    goto label_17575;
  label_17571:
    decay0_nucltransK(prng_, event_, 1.635, 0.047, 3.5e-4, 0.5e-4, tclev, thlev, tdlev);
    goto label_122;
  label_17572:
    decay0_nucltransK(prng_, event_, 1.390, 0.047, 5.0e-4, 0.2e-4, tclev, thlev, tdlev);
    goto label_366;
  label_17573:
    decay0_nucltransK(prng_, event_, 0.671, 0.047, 1.1e-2, 0., tclev, thlev, tdlev);
    goto label_1086;
  label_17574:
    decay0_nucltransK(prng_, event_, 0.523, 0.047, 3.5e-3, 0., tclev, thlev, tdlev);
    goto label_1234;
  label_17575:
    decay0_nucltransK(prng_, event_, 0.386, 0.047, 7.0e-3, 0., tclev, thlev, tdlev);
    goto label_1372;
  label_1730:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 11.26)
      goto label_17301;
    if (p <= 66.17)
      goto label_17302;
    if (p <= 79.35)
      goto label_17303;
    goto label_17304;
  label_17301:
    decay0_nucltransK(prng_, event_, 1.608, 0.047, 4.0e-4, 0.8e-4, tclev, thlev, tdlev);
    goto label_122;
  label_17302:
    decay0_nucltransK(prng_, event_, 1.364, 0.047, 5.3e-4, 0.3e-4, tclev, thlev, tdlev);
    goto label_366;
  label_17303:
    decay0_nucltransK(prng_, event_, 0.644, 0.047, 2.2e-3, 0., tclev, thlev, tdlev);
    goto label_1086;
  label_17304:
    decay0_nucltransK(prng_, event_, 0.496, 0.047, 4.0e-3, 0., tclev, thlev, tdlev);
    goto label_1234;
  label_1650:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 30.00)
      goto label_16501;
    if (p <= 31.85)
      goto label_16502;
    if (p <= 34.02)
      goto label_16503;
    if (p <= 86.93)
      goto label_16504;
    if (p <= 99.47)
      goto label_16505;
    goto label_16506;
  label_16501:
    decay0_nucltransK(prng_, event_, 0.769, 0.047, 8.0e-3, 0., tclev, thlev, tdlev);
    goto label_122;
  label_16502:
    decay0_nucltransK(prng_, event_, 0.769, 0.047, 8.0e-3, 0., tclev, thlev, tdlev);
    goto label_810;
  label_16503:
    decay0_nucltransK(prng_, event_, 0.769, 0.047, 8.0e-3, 0., tclev, thlev, tdlev);
    goto label_963;
  label_16504:
    decay0_nucltransK(prng_, event_, 0.769, 0.047, 8.0e-3, 0., tclev, thlev, tdlev);
    goto label_1086;
  label_16505:
    decay0_nucltransK(prng_, event_, 0.769, 0.047, 8.0e-3, 0., tclev, thlev, tdlev);
    goto label_1234;
  label_16506:
    decay0_nucltransK(prng_, event_, 0.769, 0.047, 8.0e-3, 0., tclev, thlev, tdlev);
    goto label_1293;
  label_1613:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 71.28)
      goto label_16131;
    if (p <= 94.09)
      goto label_16132;
    goto label_16133;
  label_16131:
    decay0_nucltransK(prng_, event_, 0.906, 0.047, 2.8e-3, 0., tclev, thlev, tdlev);
    goto label_707;
  label_16132:
    decay0_nucltransK(prng_, event_, 0.572, 0.047, 2.8e-3, 0., tclev, thlev, tdlev);
    goto label_1041;
  label_16133:
    decay0_nucltransK(prng_, event_, 0.391, 0.047, 7.0e-3, 0., tclev, thlev, tdlev);
    goto label_1222;
  label_1579:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 24.04)
      goto label_15791;
    if (p <= 92.32)
      goto label_15792;
    if (p <= 96.69)
      goto label_15793;
    if (p <= 97.13)
      goto label_15794;
    if (p <= 98.06)
      goto label_15795;
    if (p <= 98.26)
      goto label_15796;
    if (p <= 99.79)
      goto label_15797;
    goto label_15798;
  label_15791:
    decay0_nucltransK(prng_, event_, 1.458, 0.047, 4.5e-4, 0.4e-4, tclev, thlev, tdlev);
    goto label_122;
  label_15792:
    decay0_nucltransK(prng_, event_, 1.213, 0.047, 6.2e-4, 0.1e-4, tclev, thlev, tdlev);
    goto label_366;
  label_15793:
    decay0_nucltransK(prng_, event_, 0.769, 0.047, 1.5e-3, 0., tclev, thlev, tdlev);
    goto label_810;
  label_15794:
    decay0_nucltransK(prng_, event_, 0.616, 0.047, 7.0e-3, 0., tclev, thlev, tdlev);
    goto label_963;
  label_15795:
    decay0_nucltransK(prng_, event_, 0.557, 0.047, 3.0e-3, 0., tclev, thlev, tdlev);
    goto label_1023;
  label_15796:
    decay0_nucltransK(prng_, event_, 0.538, 0.047, 9.5e-3, 0., tclev, thlev, tdlev);
    goto label_1041;
  label_15797:
    decay0_nucltransK(prng_, event_, 0.494, 0.047, 4.0e-3, 0., tclev, thlev, tdlev);
    goto label_1086;
  label_15798:
    decay0_nucltransK(prng_, event_, 0.208, 0.047, 3.5e-2, 0., tclev, thlev, tdlev);
    goto label_1372;
  label_1530:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 84.56)
      goto label_15301;
    if (p <= 84.80)
      goto label_15302;
    if (p <= 85.32)
      goto label_15303;
    if (p <= 86.97)
      goto label_15304;
    if (p <= 98.22)
      goto label_15305;
    goto label_15306;
  label_15301:
    decay0_nucltransK(prng_, event_, 1.408, 0.047, 5.0e-4, 0.3e-4, tclev, thlev, tdlev);
    goto label_122;
  label_15302:
    decay0_nucltransK(prng_, event_, 0.719, 0.047, 2.0e-3, 0., tclev, thlev, tdlev);
    goto label_810;
  label_15303:
    decay0_nucltransK(prng_, event_, 0.566, 0.047, 1.4e-2, 0., tclev, thlev, tdlev);
    goto label_963;
  label_15304:
    decay0_nucltransK(prng_, event_, 0.489, 0.047, 1.4e-2, 0., tclev, thlev, tdlev);
    goto label_1041;
  label_15305:
    decay0_nucltransK(prng_, event_, 0.444, 0.047, 5.7e-3, 0., tclev, thlev, tdlev);
    goto label_1086;
  label_15306:
    decay0_nucltransK(prng_, event_, 0.296, 0.047, 1.5e-2, 0., tclev, thlev, tdlev);
    goto label_1234;
  label_1372:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 19.62)
      goto label_13721;
    if (p <= 88.70)
      goto label_13722;
    if (p <= 90.70)
      goto label_13723;
    if (p <= 90.81)
      goto label_13724;
    if (p <= 98.82)
      goto label_13725;
    goto label_13726;
  label_13721:
    decay0_nucltransK(prng_, event_, 1.250, 0.047, 1.6e-3, 0.1e-4, tclev, thlev, tdlev);
    goto label_122;
  label_13722:
    decay0_nucltransK(prng_, event_, 1.005, 0.047, 2.6e-3, 0., tclev, thlev, tdlev);
    goto label_366;
  label_13723:
    decay0_nucltransK(prng_, event_, 0.665, 0.047, 6.3e-3, 0., tclev, thlev, tdlev);
    goto label_707;
  label_13724:
    decay0_nucltransK(prng_, event_, 0.561, 0.047, 3.5e-3, 0., tclev, thlev, tdlev);
    goto label_810;
  label_13725:
    decay0_nucltransK(prng_, event_, 0.331, 0.047, 1.2e-2, 0., tclev, thlev, tdlev);
    goto label_1041;
  label_13726:
    decay0_nucltransK(prng_, event_, 0.286, 0.047, 6.6e-2, 0., tclev, thlev, tdlev);
    goto label_1086;
  label_1293:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 16.39)
      goto label_12931;
    if (p <= 22.12)
      goto label_12932;
    if (p <= 64.58)
      goto label_12933;
    if (p <= 68.91)
      goto label_12934;
    if (p <= 88.66)
      goto label_12935;
    if (p <= 89.98)
      goto label_12936;
    goto label_12937;
  label_12931:
    decay0_nucltransK(prng_, event_, 1.293, 0.047, 1.3e-3, 0.1e-4, tclev, thlev, tdlev);
    return;
  label_12932:
    decay0_nucltransK(prng_, event_, 1.171, 0.047, 1.6e-3, 0., tclev, thlev, tdlev);
    goto label_122;
  label_12933:
    decay0_nucltransK(prng_, event_, 0.926, 0.047, 3.0e-3, 0., tclev, thlev, tdlev);
    goto label_366;
  label_12934:
    decay0_nucltransK(prng_, event_, 0.482, 0.047, 2.0e-2, 0., tclev, thlev, tdlev);
    goto label_810;
  label_12935:
    decay0_nucltransK(prng_, event_, 0.329, 0.047, 1.2e-2, 0., tclev, thlev, tdlev);
    goto label_963;
  label_12936:
    decay0_nucltransK(prng_, event_, 0.270, 0.047, 7.9e-2, 0., tclev, thlev, tdlev);
    goto label_1023;
  label_12937:
    decay0_nucltransK(prng_, event_, 0.252, 0.047, 2.3e-2, 0., tclev, thlev, tdlev);
    goto label_1041;
  label_1234:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 76.33)
      goto label_12341;
    if (p <= 99.76)
      goto label_12342;
    if (p <= 99.78)
      goto label_12343;
    goto label_12344;
  label_12341:
    decay0_nucltransK(prng_, event_, 1.112, 0.047, 2.0e-3, 0.2e-4, tclev, thlev, tdlev);
    goto label_122;
  label_12342:
    decay0_nucltransK(prng_, event_, 0.867, 0.047, 3.5e-3, 0., tclev, thlev, tdlev);
    goto label_366;
  label_12343:
    decay0_nucltransK(prng_, event_, 0.423, 0.047, 2.7e-2, 0., tclev, thlev, tdlev);
    goto label_810;
  label_12344:
    decay0_nucltransK(prng_, event_, 0.148, 0.047, 5.8e-1, 0., tclev, thlev, tdlev);
    goto label_1086;
  label_1222:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 80.65)
      goto label_12221;
    goto label_12222;
  label_12221:
    decay0_nucltransK(prng_, event_, 0.855, 0.047, 1.6e-3, 0., tclev, thlev, tdlev);
    goto label_366;
  label_12222:
    decay0_nucltransK(prng_, event_, 0.515, 0.047, 3.7e-3, 0., tclev, thlev, tdlev);
    goto label_707;
  label_1086:
    thlev = 0.85e-12;
    p     = 100. * prng_();
    if (p <= 40.36)
      goto label_10861;
    if (p <= 98.77)
      goto label_10862;
    if (p <= 99.86)
      goto label_10863;
    goto label_10864;
  label_10861:
    decay0_nucltransK(prng_, event_, 1.086, 0.047, 2.1e-3, 0., tclev, thlev, tdlev);
    return;
  label_10862:
    decay0_nucltransK(prng_, event_, 0.964, 0.047, 2.7e-3, 0., tclev, thlev, tdlev);
    goto label_122;
  label_10863:
    decay0_nucltransK(prng_, event_, 0.719, 0.047, 5.2e-3, 0., tclev, thlev, tdlev);
    goto label_366;
  label_10864:
    decay0_nucltransK(prng_, event_, 0.275, 0.047, 1.0e-1, 0., tclev, thlev, tdlev);
    goto label_810;
  label_1041:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 71.23)
      goto label_10411;
    goto label_10412;
  label_10411:
    decay0_nucltransK(prng_, event_, 0.919, 0.047, 1.2e-3, 0., tclev, thlev, tdlev);
    goto label_122;
  label_10412:
    decay0_nucltransK(prng_, event_, 0.675, 0.047, 2.3e-3, 0., tclev, thlev, tdlev);
    goto label_366;
  label_1023:
    thlev = 6.7e-12;
    p     = 100. * prng_();
    if (p <= 35.73)
      goto label_10231;
    if (p <= 91.56)
      goto label_10232;
    if (p <= 92.40)
      goto label_10233;
    goto label_10234;
  label_10231:
    decay0_nucltransK(prng_, event_, 0.901, 0.047, 3.1e-3, 0., tclev, thlev, tdlev);
    goto label_122;
  label_10232:
    decay0_nucltransK(prng_, event_, 0.656, 0.047, 5.7e-2, 0., tclev, thlev, tdlev);
    goto label_366;
  label_10233:
    decay0_nucltransK(prng_, event_, 0.316, 0.047, 4.8e-2, 0., tclev, thlev, tdlev);
    goto label_707;
  label_10234:
    decay0_nucltransK(prng_, event_, 0.213, 0.047, 1.7e-1, 0., tclev, thlev, tdlev);
    goto label_810;
  label_963:
    thlev = 28.2e-15;
    p     = 100. * prng_();
    if (p <= 45.143)
      goto label_96301;
    if (p <= 99.994)
      goto label_96302;
    if (p <= 99.995)
      goto label_96303;
    goto label_96304;
  label_96301:
    decay0_nucltransK(prng_, event_, 0.963, 0.047, 1.1e-3, 0., tclev, thlev, tdlev);
    return;
  label_96302:
    decay0_nucltransK(prng_, event_, 0.842, 0.047, 1.4e-3, 0., tclev, thlev, tdlev);
    goto label_122;
  label_96303:
    decay0_nucltransK(prng_, event_, 0.279, 0.047, 1.8e-2, 0., tclev, thlev, tdlev);
    goto label_685;
  label_96304:
    decay0_nucltransK(prng_, event_, 0.153, 0.047, 8.7e-2, 0., tclev, thlev, tdlev);
    goto label_810;
  label_810:
    thlev = 7.2e-12;
    p     = 100. * prng_();
    if (p <= 21.66)
      goto label_81001;
    if (p <= 78.06)
      goto label_81002;
    if (p <= 99.21)
      goto label_81003;
    goto label_81004;
  label_81001:
    decay0_nucltransK(prng_, event_, 0.810, 0.047, 4.0e-3, 0., tclev, thlev, tdlev);
    return;
  label_81002:
    decay0_nucltransK(prng_, event_, 0.689, 0.047, 4.3e-2, 0., tclev, thlev, tdlev);
    goto label_122;
  label_81003:
    decay0_nucltransK(prng_, event_, 0.444, 0.047, 1.8e-2, 0., tclev, thlev, tdlev);
    goto label_366;
  label_81004:
    decay0_nucltransK(prng_, event_, 0.126, 0.047, 1.0e-0, 0., tclev, thlev, tdlev);
    goto label_685;
  label_707:
    thlev = 10.1e-12;
    decay0_nucltransK(prng_, event_, 0.340, 0.047, 3.8e-4, 0., tclev, thlev, tdlev);
    goto label_366;
  label_685:
    thlev = 6.2e-12;
    p     = 100. * prng_();
    if (p <= 1.43)
      goto label_68501;
    goto label_68502;
  label_68501:
    decay0_electron(prng_, event_, 0.638, tclev, thlev, tdlev);
    decay0_gamma(prng_, event_, 0.047, 0., 0., tdlev);
    return;
  label_68502:
    decay0_nucltransK(prng_, event_, 0.563, 0.047, 9.5e-3, 0., tclev, thlev, tdlev);
    goto label_122;
  label_366:
    thlev = 57.7e-12;
    decay0_nucltransK(prng_, event_, 0.245, 0.047, 1.1e-1, 0., tclev, thlev, tdlev);
    goto label_122;
  label_122:
    thlev = 1.428e-9;
    decay0_nucltransK(prng_, event_, 0.122, 0.047, 1.2e-0, 0., tclev, thlev, tdlev);
    return;
  label_2:
    pbeta = 100. * prng_();
    if (pbeta <= 0.071)
      goto label_1692;
    if (pbeta <= 6.421)
      goto label_1643;
    if (pbeta <= 6.778)
      goto label_1606;
    if (pbeta <= 15.339)
      goto label_1434;
    if (pbeta <= 15.981)
      goto label_1318;
    if (pbeta <= 16.063)
      goto label_1282;
    if (pbeta <= 65.291)
      goto label_1123;
    if (pbeta <= 66.325)
      goto label_1109;
    if (pbeta <= 67.395)
      goto label_931;
    if (pbeta <= 70.748)
      goto label_755;
    goto label_344;
  label_1692:
    decay0_beta(prng_, event_, 0.126, 64., 0., 0., t);
    ////label_16920  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 84.03)
      goto label_16921;
    goto label_16922;
  label_16921:
    decay0_nucltransK(prng_, event_, 1.348, 0.050, 1.5e-3, 0.2e-4, tclev, thlev, tdlev);
    goto label_34400;
  label_16922:
    decay0_nucltransK(prng_, event_, 0.937, 0.050, 3.2e-3, 0., tclev, thlev, tdlev);
    goto label_75500;
  label_1643:
    decay0_beta(prng_, event_, 0.175, 64., 0., 0., t);
    ////label_16430  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 89.21)
      goto label_16431;
    if (p <= 94.47)
      goto label_16432;
    if (p <= 96.83)
      goto label_16433;
    if (p <= 99.75)
      goto label_16434;
    if (p <= 99.76)
      goto label_16435;
    goto label_16436;
  label_16431:
    decay0_nucltransK(prng_, event_, 1.299, 0.050, 7.5e-4, 0.3e-4, tclev, thlev, tdlev);
    goto label_34400;
  label_16432:
    decay0_nucltransK(prng_, event_, 0.713, 0.050, 2.2e-3, 0., tclev, thlev, tdlev);
    goto label_93100;
  label_16433:
    decay0_nucltransK(prng_, event_, 0.534, 0.050, 4.5e-3, 0., tclev, thlev, tdlev);
    goto label_11090;
  label_16434:
    decay0_nucltransK(prng_, event_, 0.520, 0.050, 1.8e-2, 0., tclev, thlev, tdlev);
    goto label_11230;
  label_16435:
    decay0_nucltransK(prng_, event_, 0.325, 0.050, 1.3e-2, 0., tclev, thlev, tdlev);
    goto label_13180;
  label_16436:
    decay0_nucltransK(prng_, event_, 0.209, 0.050, 4.0e-2, 0., tclev, thlev, tdlev);
    goto label_14340;
  label_1606:
    decay0_beta(prng_, event_, 0.212, 64., 0., 0., t);
    ////label_16060  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 7.64)
      goto label_16061;
    if (p <= 40.86)
      goto label_16062;
    if (p <= 72.09)
      goto label_16063;
    if (p <= 91.36)
      goto label_16064;
    if (p <= 95.35)
      goto label_16065;
    if (p <= 99.99)
      goto label_16066;
    goto label_16067;
  label_16061:
    decay0_nucltransK(prng_, event_, 1.606, 0.050, 1.2e-3, 0.5e-4, tclev, thlev, tdlev);
    return;
  label_16062:
    decay0_nucltransK(prng_, event_, 1.261, 0.050, 2.7e-3, 0.5e-4, tclev, thlev, tdlev);
    goto label_34400;
  label_16063:
    decay0_nucltransK(prng_, event_, 0.990, 0.050, 3.0e-3, 0., tclev, thlev, tdlev);
    goto label_61500;
  label_16064:
    decay0_nucltransK(prng_, event_, 0.675, 0.050, 7.6e-3, 0., tclev, thlev, tdlev);
    goto label_93100;
  label_16065:
    decay0_nucltransK(prng_, event_, 0.558, 0.050, 1.1e-2, 0., tclev, thlev, tdlev);
    goto label_10480;
  label_16066:
    decay0_nucltransK(prng_, event_, 0.496, 0.050, 9.7e-2, 0., tclev, thlev, tdlev);
    goto label_11090;
  label_16067:
    decay0_nucltransK(prng_, event_, 0.482, 0.050, 5.0e-3, 0., tclev, thlev, tdlev);
    goto label_11230;
  label_1434:
    decay0_beta(prng_, event_, 0.384, 64., 0., 0., t);
  label_14340:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 71.07)
      goto label_14341;
    if (p <= 90.54)
      goto label_14342;
    if (p <= 96.87)
      goto label_14343;
    if (p <= 99.99)
      goto label_14344;
    goto label_14345;
  label_14341:
    decay0_nucltransK(prng_, event_, 1.090, 0.050, 2.3e-3, 0., tclev, thlev, tdlev);
    goto label_34400;
  label_14342:
    decay0_nucltransK(prng_, event_, 0.679, 0.050, 6.9e-3, 0., tclev, thlev, tdlev);
    goto label_75500;
  label_14343:
    decay0_nucltransK(prng_, event_, 0.503, 0.050, 1.4e-2, 0., tclev, thlev, tdlev);
    goto label_93100;
  label_14344:
    decay0_nucltransK(prng_, event_, 0.325, 0.050, 6.3e-2, 0., tclev, thlev, tdlev);
    goto label_11090;
  label_14345:
    decay0_nucltransK(prng_, event_, 0.115, 0.050, 1.4e-0, 0., tclev, thlev, tdlev);
    goto label_13180;
  label_1318:
    decay0_beta(prng_, event_, 0.500, 64., 0., 0., t);
  label_13180:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 6.87)
      goto label_13181;
    if (p <= 62.27)
      goto label_13182;
    if (p <= 76.12)
      goto label_13183;
    if (p <= 77.39)
      goto label_13184;
    if (p <= 84.76)
      goto label_13185;
    if (p <= 92.35)
      goto label_13186;
    if (p <= 92.79)
      goto label_13187;
    goto label_13188;
  label_13181:
    decay0_nucltransK(prng_, event_, 1.318, 0.050, 1.6e-3, 0.1e-4, tclev, thlev, tdlev);
    return;
  label_13182:
    decay0_nucltransK(prng_, event_, 0.974, 0.050, 5.6e-3, 0., tclev, thlev, tdlev);
    goto label_34400;
  label_13183:
    decay0_nucltransK(prng_, event_, 0.703, 0.050, 6.0e-3, 0., tclev, thlev, tdlev);
    goto label_61500;
  label_13184:
    decay0_nucltransK(prng_, event_, 0.563, 0.050, 1.0e-2, 0., tclev, thlev, tdlev);
    goto label_75500;
  label_13185:
    decay0_nucltransK(prng_, event_, 0.388, 0.050, 4.5e-1, 0., tclev, thlev, tdlev);
    goto label_93100;
  label_13186:
    decay0_nucltransK(prng_, event_, 0.271, 0.050, 8.4e-2, 0., tclev, thlev, tdlev);
    goto label_10480;
  label_13187:
    decay0_nucltransK(prng_, event_, 0.209, 0.050, 5.0e-1, 0., tclev, thlev, tdlev);
    goto label_11090;
  label_13188:
    decay0_nucltransK(prng_, event_, 0.195, 0.050, 4.9e-2, 0., tclev, thlev, tdlev);
    goto label_11230;
  label_1282:
    decay0_beta(prng_, event_, 0.536, 64., 0., 0., t);
    ////label_12820  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 58.41)
      goto label_12821;
    if (p <= 98.13)
      goto label_12822;
    goto label_12823;
  label_12821:
    decay0_nucltransK(prng_, event_, 0.527, 0.050, 9.4e-2, 0., tclev, thlev, tdlev);
    goto label_75500;
  label_12822:
    decay0_nucltransK(prng_, event_, 0.352, 0.050, 3.8e-2, 0., tclev, thlev, tdlev);
    goto label_93100;
  label_12823:
    decay0_nucltransK(prng_, event_, 0.172, 0.050, 3.7e-1, 0., tclev, thlev, tdlev);
    goto label_11090;
  label_1123:
    decay0_beta(prng_, event_, 0.695, 64., 0., 0., t);
  label_11230:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 93.11)
      goto label_11231;
    if (p <= 99.26)
      goto label_11232;
    goto label_11233;
  label_11231:
    decay0_nucltransK(prng_, event_, 0.779, 0.050, 1.9e-3, 0., tclev, thlev, tdlev);
    goto label_34400;
  label_11232:
    decay0_nucltransK(prng_, event_, 0.368, 0.050, 9.7e-3, 0., tclev, thlev, tdlev);
    goto label_75500;
  label_11233:
    decay0_nucltransK(prng_, event_, 0.193, 0.050, 5.0e-2, 0., tclev, thlev, tdlev);
    goto label_93100;
  label_1109:
    decay0_beta(prng_, event_, 0.709, 64., 0., 0., t);
  label_11090:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 50.00)
      goto label_11091;
    if (p <= 97.50)
      goto label_11092;
    goto label_11093;
  label_11091:
    decay0_nucltransK(prng_, event_, 1.109, 0.050, 2.2e-3, 0., tclev, thlev, tdlev);
    return;
  label_11092:
    decay0_nucltransK(prng_, event_, 0.765, 0.050, 5.2e-3, 0., tclev, thlev, tdlev);
    goto label_34400;
  label_11093:
    decay0_nucltransK(prng_, event_, 0.494, 0.050, 1.5e-2, 0., tclev, thlev, tdlev);
    goto label_61500;
  label_10480:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 0.88)
      goto label_10481;
    if (p <= 65.79)
      goto label_10482;
    if (p <= 83.77)
      goto label_10483;
    goto label_10484;
  label_10481:
    decay0_electron(prng_, event_, 0.998, tclev, thlev, tdlev);
    decay0_gamma(prng_, event_, 0.050, 0., 0., tdlev);
    return;
  label_10482:
    decay0_nucltransK(prng_, event_, 0.703, 0.050, 6.0e-3, 0., tclev, thlev, tdlev);
    goto label_34400;
  label_10483:
    decay0_electron(prng_, event_, 0.383, tclev, thlev, tdlev);
    decay0_gamma(prng_, event_, 0.050, 0., 0., tdlev);
    goto label_61500;
  label_10484:
    decay0_nucltransK(prng_, event_, 0.117, 0.050, 1.4e-0, 0., tclev, thlev, tdlev);
    goto label_93100;
  label_931:
    decay0_beta(prng_, event_, 0.887, 64., 0., 0., t);
  label_93100:
    thlev = 7.3e-12;
    p     = 100. * prng_();
    if (p <= 12.40)
      goto label_93101;
    if (p <= 90.91)
      goto label_93102;
    if (p <= 99.55)
      goto label_93103;
    goto label_93104;
  label_93101:
    decay0_nucltransK(prng_, event_, 0.931, 0.050, 3.2e-3, 0., tclev, thlev, tdlev);
    return;
  label_93102:
    decay0_nucltransK(prng_, event_, 0.586, 0.050, 2.4e-2, 0., tclev, thlev, tdlev);
    goto label_34400;
  label_93103:
    decay0_nucltransK(prng_, event_, 0.315, 0.050, 5.2e-2, 0., tclev, thlev, tdlev);
    goto label_61500;
  label_93104:
    decay0_nucltransK(prng_, event_, 0.175, 0.050, 3.5e-1, 0., tclev, thlev, tdlev);
    goto label_75500;
  label_755:
    decay0_beta(prng_, event_, 1.063, 64., 0., 0., t);
  label_75500:
    thlev = 7.3e-12;
    decay0_nucltransK(prng_, event_, 0.411, 0.050, 2.4e-2, 0., tclev, thlev, tdlev);
    goto label_34400;
  label_61500:
    thlev = 37.e-12;
    p     = 100. * prng_();
    if (p <= 11.35)
      goto label_61501;
    goto label_61502;
  label_61501:
    decay0_electron(prng_, event_, 0.565, tclev, thlev, tdlev);
    decay0_gamma(prng_, event_, 0.050, 0., 0., tdlev);
    return;
  label_61502:
    decay0_nucltransK(prng_, event_, 0.271, 0.050, 8.3e-2, 0., tclev, thlev, tdlev);
    goto label_34400;
    // correction to the 1st forbidden non-unique shape in accordance with
    // L.M.Langer et al., PR 119(1960)1308
  label_344:
    decay0_beta1(prng_, event_, 1.474, 64., 0., 0., t, 0., -0.4026, 0.0928, 0.);
  label_34400:
    thlev = 31.9e-12;
    decay0_nucltransK(prng_, event_, 0.344, 0.050, 4.0e-2, 0., tclev, thlev, tdlev);
    return;
  }
  // end of Eu152.f

} // end of namespace bxdecay0

// end of Eu152.cc
// Local Variables: --
// mode: c++ --
// End: --
