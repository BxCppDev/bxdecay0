// Copyright 1995-2018 V.I. Tretyak
// Copyright 2020 F. Mauger
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
#include <bxdecay0/Dy162low.h>

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

  void Dy162low(i_random & prng_, event & event_, const int levelkev_)
  {
    // Subroutine describes the deexcitation process in Dy162 nucleus
    // after 2b-decay of Er162 to ground and excited 0+ and 2+ levels
    // of Dy162 (NNDC site on 04.02.2018, NDS 108(2007)1807).
    // Call  : call Dy162low(levelkeV)
    // Input : levelkeV - energy of Dy162 level (integer in keV) occupied
    //                    initially; following levels can be occupied:
    //                    0+(gs) -    0 keV,
    //                    2+(1)  -   81 keV,
    //                    2+(2)  -  888 keV,
    //                    0+(1)  - 1400 keV,
    //                    2+(3)  - 1453 keV,
    //                    0+(2)  - 1666 keV,
    //                    2+(4)  - 1728 keV,
    //                    2+(5)  - 1783 keV.
    // Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
    // VIT, 04.02.2018; 9.02.208 - 1783 keV level added.
    double tdlev;
    double p;
    double tclev;
    double thlev;
    tclev = 0.;
    if (levelkev_ == 1783) {
      goto label_1783;
    }
    if (levelkev_ == 1728) {
      goto label_1728;
    }
    if (levelkev_ == 1666) {
      goto label_1666;
    }
    if (levelkev_ == 1453) {
      goto label_1453;
    }
    if (levelkev_ == 1400) {
      goto label_1400;
    }
    if (levelkev_ == 888) {
      goto label_888;
    }
    if (levelkev_ == 81) {
      goto label_81;
    }
    if (levelkev_ == 0) {
      goto label_10000;
    }
    goto label_20000;
  label_1783:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 19.73) {
      goto label_17831;
    }
    if (p <= 36.80) {
      goto label_17832;
    }
    if (p <= 43.73) {
      goto label_17833;
    }
    if (p <= 70.40) {
      goto label_17834;
    }
    goto label_17835;
  label_17831:
    decay0_nucltransK(prng_, event_, 0.820, 0.054, 4.6e-3, 0., tclev, thlev, tdlev);
    goto label_963;
  label_17832:
    decay0_nucltransK(prng_, event_, 0.894, 0.054, 7.0e-3, 0., tclev, thlev, tdlev);
    goto label_888;
  label_17833:
    decay0_nucltransK(prng_, event_, 1.517, 0.054, 1.4e-3, 7.9e-5, tclev, thlev, tdlev);
    goto label_266;
  label_17834:
    decay0_nucltransK(prng_, event_, 1.702, 0.054, 1.7e-3, 1.8e-4, tclev, thlev, tdlev);
    goto label_81;
  label_17835:
    decay0_nucltransK(prng_, event_, 1.783, 0.054, 1.2e-3, 1.9e-4, tclev, thlev, tdlev);
    return;
  label_1728:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 0.45) {
      goto label_17281;
    }
    if (p <= 2.22) {
      goto label_17282;
    }
    if (p <= 3.84) {
      goto label_17283;
    }
    if (p <= 5.81) {
      goto label_17284;
    }
    if (p <= 22.01) {
      goto label_17285;
    }
    if (p <= 72.65) {
      goto label_17286;
    }
    goto label_17287;
  label_17281:
    decay0_nucltransK(prng_, event_, 0.154, 0.054, 0.575, 0., tclev, thlev, tdlev);
    goto label_1574;
  label_17282:
    decay0_nucltransK(prng_, event_, 0.370, 0.054, 1.0e-2, 0., tclev, thlev, tdlev);
    goto label_1358;
  label_17283:
    decay0_nucltransK(prng_, event_, 0.453, 0.054, 6.4e-3, 0., tclev, thlev, tdlev);
    goto label_1276;
  label_17284:
    decay0_nucltransK(prng_, event_, 0.840, 0.054, 6.3e-3, 0., tclev, thlev, tdlev);
    goto label_888;
  label_17285:
    decay0_nucltransK(prng_, event_, 1.463, 0.054, 1.5e-3, 6.1e-5, tclev, thlev, tdlev);
    goto label_266;
  label_17286:
    decay0_nucltransK(prng_, event_, 1.648, 0.054, 1.8e-3, 1.5e-4, tclev, thlev, tdlev);
    goto label_81;
  label_17287:
    decay0_nucltransK(prng_, event_, 1.728, 0.054, 1.2e-3, 1.6e-4, tclev, thlev, tdlev);
    return;
  label_1666:
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 1.586, 0.054, 1.3e-3, 1.0e-4, tclev, thlev, tdlev);
    goto label_81;
  label_1574:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 0.39) {
      goto label_15741;
    }
    if (p <= 0.59) {
      goto label_15742;
    }
    if (p <= 0.75) {
      goto label_15743;
    }
    if (p <= 1.13) {
      goto label_15744;
    }
    if (p <= 1.85) {
      goto label_15745;
    }
    if (p <= 3.50) {
      goto label_15746;
    }
    if (p <= 3.89) {
      goto label_15747;
    }
    if (p <= 4.84) {
      goto label_15748;
    }
    if (p <= 21.23) {
      goto label_15749;
    }
    goto label_15740;
  label_15741:
    decay0_nucltransK(prng_, event_, 0.121, 0.054, 1.357, 0., tclev, thlev, tdlev);
    goto label_1453;
  label_15742:
    decay0_nucltransK(prng_, event_, 0.216, 0.054, 4.0e-2, 0., tclev, thlev, tdlev);
    goto label_1358;
  label_15743:
    decay0_nucltransK(prng_, event_, 0.277, 0.054, 2.1e-2, 0., tclev, thlev, tdlev);
    goto label_1297;
  label_15744:
    decay0_nucltransK(prng_, event_, 0.364, 0.054, 1.1e-2, 0., tclev, thlev, tdlev);
    goto label_1210;
  label_15745:
    decay0_nucltransK(prng_, event_, 0.392, 0.054, 4.4e-2, 0., tclev, thlev, tdlev);
    goto label_1183;
  label_15746:
    decay0_nucltransK(prng_, event_, 0.513, 0.054, 2.1e-2, 0., tclev, thlev, tdlev);
    goto label_1061;
  label_15747:
    decay0_nucltransK(prng_, event_, 0.611, 0.054, 1.3e-2, 0., tclev, thlev, tdlev);
    goto label_963;
  label_15748:
    decay0_nucltransK(prng_, event_, 0.626, 0.054, 7.0e-3, 0., tclev, thlev, tdlev);
    goto label_888;
  label_15749:
    decay0_nucltransK(prng_, event_, 1.026, 0.054, 2.8e-3, 0., tclev, thlev, tdlev);
    goto label_549;
  label_15740:
    decay0_nucltransK(prng_, event_, 1.309, 0.054, 2.8e-3, 2.5e-5, tclev, thlev, tdlev);
    goto label_266;
  label_1453:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 0.52) {
      goto label_14531;
    }
    if (p <= 1.07) {
      goto label_14532;
    }
    if (p <= 2.90) {
      goto label_14533;
    }
    if (p <= 4.01) {
      goto label_14534;
    }
    if (p <= 42.76) {
      goto label_14535;
    }
    if (p <= 98.12) {
      goto label_14536;
    }
    goto label_14537;
  label_14531:
    decay0_nucltransK(prng_, event_, 0.178, 0.054, 6.6e-2, 0., tclev, thlev, tdlev);
    goto label_1276;
  label_14532:
    decay0_nucltransK(prng_, event_, 0.392, 0.054, 2.9e-2, 0., tclev, thlev, tdlev);
    goto label_1061;
  label_14533:
    decay0_nucltransK(prng_, event_, 0.491, 0.054, 1.6e-2, 0., tclev, thlev, tdlev);
    goto label_963;
  label_14534:
    decay0_nucltransK(prng_, event_, 0.565, 0.054, 1.6e-2, 0., tclev, thlev, tdlev);
    goto label_888;
  label_14535:
    decay0_nucltransK(prng_, event_, 1.188, 0.054, 2.2e-3, 4.2e-6, tclev, thlev, tdlev);
    goto label_266;
  label_14536:
    decay0_nucltransK(prng_, event_, 1.373, 0.054, 2.4e-3, 4.1e-5, tclev, thlev, tdlev);
    goto label_81;
  label_14537:
    decay0_nucltransK(prng_, event_, 1.454, 0.054, 1.5e-3, 5.8e-5, tclev, thlev, tdlev);
    return;
  label_1400:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 7.40) {
      goto label_14001;
    }
    if (p <= 99.95) {
      goto label_14002;
    }
    goto label_14003;
  label_14001:
    decay0_nucltransK(prng_, event_, 0.512, 0.054, 1.4e-2, 0., tclev, thlev, tdlev);
    goto label_888;
  label_14002:
    decay0_nucltransK(prng_, event_, 1.320, 0.054, 1.8e-3, 2.3e-5, tclev, thlev, tdlev);
    goto label_81;
  label_14003:
    p = 100. * prng_();
    if (p <= 99.16) {                                             // e0.exe
      decay0_electron(prng_, event_, 1.346, tclev, thlev, tdlev); // conversion to electron
      decay0_gamma(prng_, event_, 0.054, 0., 0., tdlev);
    } else {
      decay0_pair(prng_, event_, 0.378, tclev, thlev, tdlev); // conversion to pair
    }
    return;
  label_1358:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 41.86) {
      goto label_13581;
    }
    goto label_13582;
  label_13581:
    decay0_nucltransK(prng_, event_, 1.092, 0.054, 1.1e-3, 0., tclev, thlev, tdlev);
    goto label_266;
  label_13582:
    decay0_nucltransK(prng_, event_, 1.277, 0.054, 8.6e-4, 5.8e-5, tclev, thlev, tdlev);
    goto label_81;
  label_1297:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 1.58) {
      goto label_12971;
    }
    if (p <= 6.87) {
      goto label_12972;
    }
    if (p <= 24.20) {
      goto label_12973;
    }
    if (p <= 97.94) {
      goto label_12974;
    }
    goto label_12975;
  label_12971:
    decay0_nucltransK(prng_, event_, 0.087, 0.054, 4.1, 0., tclev, thlev, tdlev);
    goto label_1210;
  label_12972:
    decay0_nucltransK(prng_, event_, 0.114, 0.054, 0.216, 0., tclev, thlev, tdlev);
    goto label_1183;
  label_12973:
    decay0_nucltransK(prng_, event_, 0.236, 0.054, 3.2e-2, 0., tclev, thlev, tdlev);
    goto label_1061;
  label_12974:
    decay0_nucltransK(prng_, event_, 0.334, 0.054, 1.3e-2, 0., tclev, thlev, tdlev);
    goto label_963;
  label_12975:
    decay0_nucltransK(prng_, event_, 1.031, 0.054, 1.2e-3, 0., tclev, thlev, tdlev);
    goto label_266;
  label_1276:
    thlev = 20.e-15;
    p     = 100. * prng_();
    if (p <= 57.67) {
      goto label_12761;
    }
    goto label_12762;
  label_12761:
    decay0_nucltransK(prng_, event_, 1.195, 0.054, 9.2e-4, 2.2e-5, tclev, thlev, tdlev);
    goto label_81;
  label_12762:
    decay0_nucltransK(prng_, event_, 1.276, 0.054, 8.6e-4, 5.8e-5, tclev, thlev, tdlev);
    return;
  label_1210:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 2.42) {
      goto label_12101;
    }
    if (p <= 9.61) {
      goto label_12102;
    }
    if (p <= 20.10) {
      goto label_12103;
    }
    if (p <= 50.06) {
      goto label_12104;
    }
    goto label_12105;
  label_12101:
    decay0_nucltransK(prng_, event_, 0.149, 0.054, 0.11, 0., tclev, thlev, tdlev);
    goto label_1061;
  label_12102:
    decay0_nucltransK(prng_, event_, 0.247, 0.054, 2.8e-2, 0., tclev, thlev, tdlev);
    goto label_963;
  label_12103:
    decay0_nucltransK(prng_, event_, 0.322, 0.054, 1.4e-2, 0., tclev, thlev, tdlev);
    goto label_888;
  label_12104:
    decay0_nucltransK(prng_, event_, 0.944, 0.054, 1.5e-3, 0., tclev, thlev, tdlev);
    goto label_266;
  label_12105:
    decay0_nucltransK(prng_, event_, 1.129, 0.054, 1.0e-3, 4.5e-6, tclev, thlev, tdlev);
    goto label_81;
  label_1183:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 0.32) {
      goto label_11831;
    }
    if (p <= 2.69) {
      goto label_11832;
    }
    if (p <= 18.23) {
      goto label_11833;
    }
    goto label_11834;
  label_11831:
    decay0_nucltransK(prng_, event_, 0.122, 0.054, 1.325, 0., tclev, thlev, tdlev);
    goto label_1061;
  label_11832:
    decay0_nucltransK(prng_, event_, 0.220, 0.054, 0.173, 0., tclev, thlev, tdlev);
    goto label_963;
  label_11833:
    decay0_nucltransK(prng_, event_, 0.634, 0.054, 8.5e-3, 0., tclev, thlev, tdlev);
    goto label_549;
  label_11834:
    decay0_nucltransK(prng_, event_, 0.917, 0.054, 3.7e-3, 0., tclev, thlev, tdlev);
    goto label_266;
  label_1061:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 0.18) {
      goto label_10611;
    }
    if (p <= 0.80) {
      goto label_10612;
    }
    if (p <= 1.79) {
      goto label_10613;
    }
    if (p <= 64.34) {
      goto label_10614;
    }
    goto label_10615;
  label_10611:
    decay0_nucltransK(prng_, event_, 0.098, 0.054, 2.53, 0., tclev, thlev, tdlev);
    goto label_963;
  label_10612:
    decay0_nucltransK(prng_, event_, 0.173, 0.054, 0.387, 0., tclev, thlev, tdlev);
    goto label_888;
  label_10613:
    decay0_nucltransK(prng_, event_, 0.512, 0.054, 1.4e-2, 0., tclev, thlev, tdlev);
    goto label_549;
  label_10614:
    decay0_nucltransK(prng_, event_, 0.795, 0.054, 5.0e-3, 0., tclev, thlev, tdlev);
    goto label_266;
  label_10615:
    decay0_nucltransK(prng_, event_, 0.980, 0.054, 3.2e-3, 0., tclev, thlev, tdlev);
    goto label_81;
  label_963:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 16.32) {
      goto label_9631;
    }
    goto label_9632;
  label_9631:
    decay0_nucltransK(prng_, event_, 0.697, 0.054, 6.7e-3, 0., tclev, thlev, tdlev);
    goto label_266;
  label_9632:
    decay0_nucltransK(prng_, event_, 0.882, 0.054, 4.0e-3, 0., tclev, thlev, tdlev);
    goto label_81;
  label_888:
    thlev = 1.97e-12;
    p     = 100. * prng_();
    if (p <= 1.08) {
      goto label_8881;
    }
    if (p <= 52.87) {
      goto label_8882;
    }
    goto label_8883;
  label_8881:
    decay0_nucltransK(prng_, event_, 0.622, 0.054, 8.8e-3, 0., tclev, thlev, tdlev);
    ;
    goto label_266;
  label_8882:
    decay0_nucltransK(prng_, event_, 0.808, 0.054, 4.8e-3, 0., tclev, thlev, tdlev);
    goto label_81;
  label_8883:
    decay0_nucltransK(prng_, event_, 0.888, 0.054, 3.9e-3, 0., tclev, thlev, tdlev);
    return;
  label_549:
    thlev = 18.4e-12;
    decay0_nucltransK(prng_, event_, 0.283, 0.054, 7.7e-2, 0., tclev, thlev, tdlev);
    goto label_266;
  label_266:
    thlev = 0.132e-9;
    decay0_nucltransK(prng_, event_, 0.185, 0.054, 0.307, 0., tclev, thlev, tdlev);
    goto label_81;
  label_81:
    thlev = 2.19e-9;
    decay0_nucltransK(prng_, event_, 0.081, 0.054, 6.14, 0., tclev, thlev, tdlev);
    return;
  label_10000:
    return;
  label_20000:
    // print *, 'Dy162: wrong level [keV] ', levelkev
    return;
  }

} // end of namespace bxdecay0

// end of Dy162low.cc
// Local Variables: --
// mode: c++ --
// End: --
