// Copyright 1995-2016 V.I. Tretyak
// Copyright 2011-2020 F. Mauger
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
#include <bxdecay0/Gd156low.h>

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

  void Gd156low(i_random & prng_,
                event & event_,
                const int levelkev_)
  {
    //double t;
    double tdlev;
    double p;
    double tclev;
    double thlev;
    // Subroutine describes the deexcitation process in Gd156 nucleus
    // after 2b-decay of Dy156 to ground and excited 0+ and 2+ levels
    // of Gd156 (NNDC site on 21.12.2010
    // Call : call Gd156low(levelkev_)
    // Input : levelkev_ - energy of Gd156 level (integer in keV) occupied
    // initially
    // 0+(gs) - 0 keV,
    // 2+(1) - 89 keV,
    // 0+(1) - 1050 keV,
    // 2+(2) - 1129 keV,
    // 2+(3) - 1154 keV,
    // 0+(2) - 1168 keV,
    // 2+(4) - 1258 keV,
    // 0+(3) - 1715 keV,
    // 2+(5) - 1771 keV,
    // 2+(6) - 1828 keV,
    // 0+(4) - 1851 keV,
    // 2+(7) - 1915 keV,
    // 1-() - 1946 keV,
    // 0-() - 1952 keV,
    // 0+(5) - 1989 keV,
    // 2+(8) - 2004 keV.
    // Output: // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 23.12.2010.
    tclev=0.;
    if (levelkev_ == 2004) goto label_2004;
    if (levelkev_ == 1989) goto label_1989;
    if (levelkev_ == 1952) goto label_1952;
    if (levelkev_ == 1946) goto label_1946;
    if (levelkev_ == 1915) goto label_1915;
    if (levelkev_ == 1851) goto label_1851;
    if (levelkev_ == 1828) goto label_1828;
    if (levelkev_ == 1771) goto label_1771;
    if (levelkev_ == 1715) goto label_1715;
    if (levelkev_ == 1258) goto label_1258;
    if (levelkev_ == 1168) goto label_1168;
    if (levelkev_ == 1154) goto label_1154;
    if (levelkev_ == 1129) goto label_1129;
    if (levelkev_ == 1050) goto label_1050;
    if (levelkev_ ==  89) goto label_89;
    if (levelkev_ ==  0) goto label_10000;
    goto label_20000;
  label_2004  :
    thlev=0.;
    p=100.*prng_();
    if (p <=  6.1) goto label_20041;
    if (p <= 39.5) goto label_20042;
    if (p <= 53.8) goto label_20043;
    if (p <= 81.5) goto label_20044;
    if (p <= 94.1) goto label_20045;
    if (p <= 97.0) goto label_20046;
    goto label_20047;
  label_20041  :
    decay0_nucltransK(prng_, event_, 0.684,0.050,2.4e-3,0.,tclev,thlev,tdlev);
    goto label_1320;
  label_20042  :
    decay0_nucltransK(prng_, event_, 0.728,0.050,2.1e-3,0.,tclev,thlev,tdlev);
    goto label_1276;
  label_20043  :
    decay0_nucltransK(prng_, event_, 0.756,0.050,7.2e-3,0.,tclev,thlev,tdlev);
    goto label_1248;
  label_20044  :
    decay0_nucltransK(prng_, event_, 0.761,0.050,1.9e-3,0.,tclev,thlev,tdlev);
    goto label_1243;
  label_20045  :
    decay0_nucltransK(prng_, event_, 0.850,0.050,5.4e-3,0.,tclev,thlev,tdlev);
    goto label_1154;
  label_20046  :
    decay0_nucltransK(prng_, event_, 0.874,0.050,6.5e-3,0.,tclev,thlev,tdlev);
    goto label_1129;
  label_20047  :
    decay0_nucltransK(prng_, event_, 1.715,0.050,1.1e-3,0.,tclev,thlev,tdlev);
    goto label_288;
  label_1989  :
    thlev=0.;
    decay0_nucltransK(prng_, event_, 1.900,0.050,7.9e-4,2.4e-4,tclev,thlev,tdlev);
    goto label_89;
  label_1952  :
    thlev=0.;
    p=100.*prng_();
    if (p <=  5.5) goto label_19521;
    if (p <=  9.3) goto label_19522;
    goto label_19523;
  label_19521  :
    decay0_nucltransK(prng_, event_, 0.586,0.050,1.7e-2,0.,tclev,thlev,tdlev);
    goto label_1367;
  label_19522  :
    decay0_nucltransK(prng_, event_, 0.633,0.050,7.8e-3,0.,tclev,thlev,tdlev);
    goto label_1320;
  label_19523  :
    decay0_nucltransK(prng_, event_, 0.710,0.050,1.1e-2,0.,tclev,thlev,tdlev);
    goto label_1243;
  label_1946  :
    thlev=30.e-15;
    p=100.*prng_();
    if (p <=  2.8) goto label_19461;
    if (p <= 60.7) goto label_19462;
    goto label_19463;
  label_19461  :
    decay0_nucltransK(prng_, event_, 0.688,0.050,2.4e-3,0.,tclev,thlev,tdlev);
    goto label_1258;
  label_19462  :
    decay0_nucltransK(prng_, event_, 1.857,0.050,3.9e-4,4.7e-4,tclev,thlev,tdlev);
    goto label_89;
  label_19463  :
    decay0_nucltransK(prng_, event_, 1.946,0.050,3.6e-4,5.4e-4,tclev,thlev,tdlev);
    return;
  label_1915  :
    thlev=0.;
    p=100.*prng_();
    if (p <=  0.64) goto label_19151;
    if (p <=  4.06) goto label_19152;
    if (p <= 13.31) goto label_19153;
    if (p <= 17.90) goto label_19154;
    if (p <= 22.04) goto label_19155;
    if (p <= 26.03) goto label_19156;
    goto label_19157;
  label_19151  :
    decay0_nucltransK(prng_, event_, 0.376,0.050,9.2e-3,0.,tclev,thlev,tdlev);
    goto label_1539;
  label_19152  :
    decay0_nucltransK(prng_, event_, 0.548,0.050,3.9e-3,0.,tclev,thlev,tdlev);
    goto label_1367;
  label_19153  :
    decay0_nucltransK(prng_, event_, 0.639,0.050,2.8e-3,0.,tclev,thlev,tdlev);
    goto label_1276;
  label_19154  :
    decay0_nucltransK(prng_, event_, 0.657,0.050,1.8e-2,0.,tclev,thlev,tdlev);
    goto label_1258;
  label_19155  :
    decay0_nucltransK(prng_, event_, 0.667,0.050,1.0e-2,0.,tclev,thlev,tdlev);
    goto label_1248;
  label_19156  :
    decay0_nucltransK(prng_, event_, 0.672,0.050,2.5e-3,0.,tclev,thlev,tdlev);
    goto label_1243;
  label_19157  :
    decay0_nucltransK(prng_, event_, 1.826,0.050,1.1e-3,2.4e-4,tclev,thlev,tdlev);
    goto label_89;
  label_1851  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 13.2) goto label_18511;
    if (p <= 25.7) goto label_18512;
    if (p <= 34.6) goto label_18513;
    if (p <= 40.0) goto label_18514;
    if (p <= 99.7) goto label_18515;
    goto label_18516;
  label_18511  :
    decay0_nucltransK(prng_, event_, 0.485,0.050,5.1e-3,0.,tclev,thlev,tdlev);
    goto label_1367;
  label_18512  :
    decay0_nucltransK(prng_, event_, 0.609,0.050,3.1e-3,0.,tclev,thlev,tdlev);
    goto label_1243;
  label_18513  :
    decay0_nucltransK(prng_, event_, 0.697,0.050,6.2e-3,0.,tclev,thlev,tdlev);
    goto label_1154;
  label_18514  :
    decay0_nucltransK(prng_, event_, 0.722,0.050,5.7e-3,0.,tclev,thlev,tdlev);
    goto label_1129;
  label_18515  :
    decay0_nucltransK(prng_, event_, 1.763,0.050,9.0e-4,1.8e-4,tclev,thlev,tdlev);
    goto label_89;
  label_18516  :
    p=100.*prng_();
    if (p <= 91.7) {  ;// e0.exe
      decay0_electron(prng_, event_, 1.801,tclev,thlev,tdlev)  ;// conversion to electron
      decay0_gamma(prng_, event_, 0.050,0.,0.,tdlev);
    } else {;
      decay0_pair(prng_, event_, 0.829,tclev,thlev,tdlev)  ;// conversion to pair
    };
    return;
  label_1828  :
    thlev=0.;
    p=100.*prng_();
    if (p <=  0.28) goto label_18281;
    if (p <=  3.37) goto label_18282;
    if (p <= 14.51) goto label_18283;
    if (p <= 28.57) goto label_18284;
    if (p <= 48.82) goto label_18285;
    if (p <= 71.88) goto label_18286;
    goto label_18287;
  label_18281  :
    decay0_nucltransK(prng_, event_, 0.366,0.050,3.3e-2,0.,tclev,thlev,tdlev);
    goto label_1462;
  label_18282  :
    decay0_nucltransK(prng_, event_, 0.570,0.050,1.4e-2,0.,tclev,thlev,tdlev);
    goto label_1258;
  label_18283  :
    decay0_nucltransK(prng_, event_, 0.580,0.050,1.4e-2,0.,tclev,thlev,tdlev);
    goto label_1248;
  label_18284  :
    decay0_nucltransK(prng_, event_, 0.674,0.050,6.6e-3,0.,tclev,thlev,tdlev);
    goto label_1154;
  label_18285  :
    decay0_nucltransK(prng_, event_, 0.698,0.050,9.0e-3,0.,tclev,thlev,tdlev);
    goto label_1129;
  label_18286  :
    decay0_nucltransK(prng_, event_, 0.778,0.050,4.8e-3,0.,tclev,thlev,tdlev);
    goto label_1050;
  label_18287  :
    decay0_nucltransK(prng_, event_, 1.739,0.050,1.3e-3,1.9e-4,tclev,thlev,tdlev);
    goto label_89;
  label_1771  :
    thlev=0.42e-12;
    p=100.*prng_();
    if (p <=  0.10) goto label_17711;
    if (p <=  1.08) goto label_17712;
    if (p <=  7.61) goto label_17713;
    if (p <=  9.76) goto label_17714;
    if (p <= 10.50) goto label_17715;
    goto label_17716;
  label_17711  :
    decay0_nucltransK(prng_, event_, 0.232,0.050,3.1e-2,0.,tclev,thlev,tdlev);
    goto label_1539;
  label_17712  :
    decay0_nucltransK(prng_, event_, 0.405,0.050,7.7e-3,0.,tclev,thlev,tdlev);
    goto label_1367;
  label_17713  :
    decay0_nucltransK(prng_, event_, 0.495,0.050,4.8e-3,0.,tclev,thlev,tdlev);
    goto label_1276;
  label_17714  :
    decay0_nucltransK(prng_, event_, 0.513,0.050,2.4e-2,0.,tclev,thlev,tdlev);
    goto label_1258;
  label_17715  :
    decay0_nucltransK(prng_, event_, 0.529,0.050,4.2e-3,0.,tclev,thlev,tdlev);
    goto label_1243;
  label_17716  :
    decay0_nucltransK(prng_, event_, 1.682,0.050,1.4e-3,1.6e-4,tclev,thlev,tdlev);
    goto label_89;
  label_1715  :
    thlev=2.6e-12;
    p=100.*prng_();
    if (p <=  6.97) goto label_17151;
    if (p <= 74.65) goto label_17152;
    if (p <= 74.72) goto label_17153;
    if (p <= 77.43) goto label_17154;
    if (p <= 77.54) goto label_17155;
    if (p <= 99.88) goto label_17156;
    goto label_17157;
  label_17151  :
    decay0_nucltransK(prng_, event_, 0.349,0.050,1.1e-2,0.,tclev,thlev,tdlev);
    goto label_1367;
  label_17152  :
    decay0_nucltransK(prng_, event_, 0.473,0.050,5.4e-3,0.,tclev,thlev,tdlev);
    goto label_1243;
  label_17153  :
    decay0_electron(prng_, event_, 0.497,tclev,thlev,tdlev)  ;// only conversion to electron
    decay0_gamma(prng_, event_, 0.050,0.,0.,tdlev);
    goto label_1168;
  label_17154  :
    decay0_nucltransK(prng_, event_, 0.586,0.050,9.4e-3,0.,tclev,thlev,tdlev);
    goto label_1129;
  label_17155  :
    decay0_electron(prng_, event_, 0.616,tclev,thlev,tdlev)  ;// only conversion to electron
    decay0_gamma(prng_, event_, 0.050,0.,0.,tdlev);
    goto label_1050;
  label_17156  :
    decay0_nucltransK(prng_, event_, 1.625,0.050,1.1e-3,1.2e-4,tclev,thlev,tdlev);
    goto label_89;
  label_17157  :
    decay0_electron(prng_, event_, 1.665,tclev,thlev,tdlev)  ;// only conversion to electron
    decay0_gamma(prng_, event_, 0.050,0.,0.,tdlev);
    return;
  label_1539  :
    thlev=20.e-15;
    p=100.*prng_();
    if (p <=  0.2) goto label_15391;
    if (p <= 51.6) goto label_15392;
    goto label_15393;
  label_15391  :
    decay0_nucltransK(prng_, event_, 0.385,0.050,8.6e-3,0.,tclev,thlev,tdlev);
    goto label_1154;
  label_15392  :
    decay0_nucltransK(prng_, event_, 1.251,0.050,7.6e-4,0.5e-4,tclev,thlev,tdlev);
    goto label_288;
  label_15393  :
    decay0_nucltransK(prng_, event_, 1.450,0.050,5.9e-4,1.7e-4,tclev,thlev,tdlev);
    goto label_89;
  label_1462  :
    thlev=0.;
    p=100.*prng_();
    if (p <=  0.16) goto label_14621;
    if (p <=  0.76) goto label_14622;
    if (p <=  1.00) goto label_14623;
    if (p <= 27.32) goto label_14624;
    if (p <= 89.98) goto label_14625;
    goto label_14626;
  label_14621  :
    decay0_nucltransK(prng_, event_, 0.165,0.050,4.9e-1,0.,tclev,thlev,tdlev);
    goto label_1298;
  label_14622  :
    decay0_nucltransK(prng_, event_, 0.204,0.050,2.1e-1,0.,tclev,thlev,tdlev);
    goto label_1258;
  label_14623  :
    decay0_nucltransK(prng_, event_, 0.333,0.050,3.4e-2,0.,tclev,thlev,tdlev);
    goto label_1129;
  label_14624  :
    decay0_nucltransK(prng_, event_, 0.878,0.050,3.7e-3,0.,tclev,thlev,tdlev);
    goto label_585;
  label_14625  :
    decay0_nucltransK(prng_, event_, 1.174,0.050,3.2e-3,0.,tclev,thlev,tdlev);
    goto label_288;
  label_14626  :
    decay0_nucltransK(prng_, event_, 1.373,0.050,1.5e-3,0.,tclev,thlev,tdlev);
    goto label_89;
  label_1367  :
    thlev=17.e-15;
    p=100.*prng_();
    if (p <=  0.05) goto label_13671;
    if (p <= 64.74) goto label_13672;
    goto label_13673;
  label_13671  :
    decay0_nucltransK(prng_, event_, 0.237,0.050,2.9e-2,0.,tclev,thlev,tdlev);
    goto label_1129;
  label_13672  :
    decay0_nucltransK(prng_, event_, 1.278,0.050,7.3e-4,0.6e-4,tclev,thlev,tdlev);
    goto label_89;
  label_13673  :
    decay0_nucltransK(prng_, event_, 1.367,0.050,6.5e-4,1.1e-4,tclev,thlev,tdlev);
    return;
  label_1320  :
    thlev=3.9e-12;
    p=100.*prng_();
    if (p <=  0.22) goto label_13201;
    goto label_13202;
  label_13201  :
    decay0_nucltransK(prng_, event_, 0.190,0.050,5.2e-2,0.,tclev,thlev,tdlev);
    goto label_1129;
  label_13202  :
    decay0_nucltransK(prng_, event_, 1.231,0.050,7.8e-4,0.,tclev,thlev,tdlev);
    goto label_89;
  label_1298  :
    thlev=1.6e-12;
    p=100.*prng_();
    if (p <=  0.07) goto label_12981;
    if (p <=  0.84) goto label_12982;
    if (p <=  6.41) goto label_12983;
    if (p <= 50.74) goto label_12984;
    goto label_12985;
  label_12981  :
    decay0_nucltransK(prng_, event_, 0.144,0.050,6.8e-1,0.,tclev,thlev,tdlev);
    goto label_1154;
  label_12982  :
    decay0_nucltransK(prng_, event_, 0.168,0.050,4.0e-1,0.,tclev,thlev,tdlev);
    goto label_1129;
  label_12983  :
    decay0_nucltransK(prng_, event_, 0.713,0.050,5.8e-3,0.,tclev,thlev,tdlev);
    goto label_585;
  label_12984  :
    decay0_nucltransK(prng_, event_, 1.010,0.050,1.7e-2,0.,tclev,thlev,tdlev);
    goto label_288;
  label_12985  :
    decay0_nucltransK(prng_, event_, 1.209,0.050,1.9e-3,0.,tclev,thlev,tdlev);
    goto label_89;
  label_1276  :
    thlev=0.098e-12;
    p=100.*prng_();
    if (p <= 31.0) goto label_12761;
    goto label_12762;
  label_12761  :
    decay0_nucltransK(prng_, event_, 0.988,0.050,1.2e-3,0.,tclev,thlev,tdlev);
    goto label_288;
  label_12762  :
    decay0_nucltransK(prng_, event_, 1.187,0.050,8.3e-4,0.,tclev,thlev,tdlev);
    goto label_89;
  label_1258  :
    thlev=1.54e-12;
    p=100.*prng_();
    if (p <= 50.8) goto label_12581;
    if (p <= 86.8) goto label_12582;
    goto label_12583;
  label_12581  :
    decay0_nucltransK(prng_, event_, 0.970,0.050,3.0e-3,0.,tclev,thlev,tdlev);
    goto label_288;
  label_12582  :
    decay0_nucltransK(prng_, event_, 1.169,0.050,3.1e-3,0.,tclev,thlev,tdlev);
    goto label_89;
  label_12583  :
    decay0_nucltransK(prng_, event_, 1.258,0.050,1.7e-3,0.,tclev,thlev,tdlev);
    return;
  label_1248  :
    thlev=0.58e-12;
    p=100.*prng_();
    if (p <= 21.3) goto label_12481;
    goto label_12482;
  label_12481  :
    decay0_nucltransK(prng_, event_, 0.960,0.050,3.0e-3,0.,tclev,thlev,tdlev);
    goto label_288;
  label_12482  :
    decay0_nucltransK(prng_, event_, 1.159,0.050,2.1e-3,0.,tclev,thlev,tdlev);
    goto label_89;
  label_1243  :
    thlev=31.e-15;
    p=100.*prng_();
    if (p <= 50.7) goto label_12431;
    goto label_12432;
  label_12431  :
    decay0_nucltransK(prng_, event_, 1.154,0.050,8.8e-4,0.,tclev,thlev,tdlev);
    goto label_89;
  label_12432  :
    decay0_nucltransK(prng_, event_, 1.243,0.050,7.7e-4,0.4e-4,tclev,thlev,tdlev);
    return;
  label_1168  :
    thlev=5.e-12;
    p=100.*prng_();
    if (p <=  0.18) goto label_11681;
    if (p <= 99.95) goto label_11682;
    goto label_11683;
  label_11681  :
    decay0_electron(prng_, event_, 0.069,tclev,thlev,tdlev)  ;// only conversion to electron
    decay0_gamma(prng_, event_, 0.050,0.,0.,tdlev);
    goto label_1050;
  label_11682  :
    decay0_nucltransK(prng_, event_, 1.079,0.050,2.4e-3,0.,tclev,thlev,tdlev);
    goto label_89;
  label_11683  :
    decay0_electron(prng_, event_, 1.118,tclev,thlev,tdlev)  ;// only conversion to electron
    decay0_gamma(prng_, event_, 0.050,0.,0.,tdlev);
    return;
  label_1154  :
    thlev=0.568e-12;
    p=100.*prng_();
    if (p <=  1.89) goto label_11541;
    if (p <= 51.90) goto label_11542;
    goto label_11543;
  label_11541  :
    decay0_nucltransK(prng_, event_, 0.866,0.050,3.8e-3,0.,tclev,thlev,tdlev);
    goto label_288;
  label_11542  :
    decay0_nucltransK(prng_, event_, 1.065,0.050,2.4e-3,0.,tclev,thlev,tdlev);
    goto label_89;
  label_11543  :
    decay0_nucltransK(prng_, event_, 1.154,0.050,2.1e-3,0.,tclev,thlev,tdlev);
    return;
  label_1129  :
    thlev=1.59e-12;
    p=100.*prng_();
    if (p <= 24.3) goto label_11291;
    if (p <= 83.8) goto label_11292;
    goto label_11293;
  label_11291  :
    decay0_nucltransK(prng_, event_, 0.841,0.050,4.0e-3,0.,tclev,thlev,tdlev);
    goto label_288;
  label_11292  :
    decay0_nucltransK(prng_, event_, 1.041,0.050,1.4e-2,0.,tclev,thlev,tdlev);
    goto label_89;
  label_11293  :
    decay0_nucltransK(prng_, event_, 1.129,0.050,2.2e-3,0.,tclev,thlev,tdlev);
    return;
  label_1050  :
    thlev=1.8e-12;
    p=100.*prng_();
    if (p <= 99.4) goto label_10501;
    goto label_10502;
  label_10501  :
    decay0_nucltransK(prng_, event_, 0.961,0.050,3.0e-3,0.,tclev,thlev,tdlev);
    goto label_89;
  label_10502  :
    decay0_electron(prng_, event_, 1.000,tclev,thlev,tdlev)  ;// only conversion to electron
    decay0_gamma(prng_, event_, 0.050,0.,0.,tdlev);
    return;
  label_585  :
    thlev=15.8e-12;
    decay0_nucltransK(prng_, event_, 0.297,0.050,6.3e-2,0.,tclev,thlev,tdlev);
    goto label_288;
  label_288  :
    thlev=111.9e-12;
    decay0_nucltransK(prng_, event_, 0.199,0.050,2.3e-1,0.,tclev,thlev,tdlev);
    goto label_89;
  label_89  :
    thlev=2.21e-9;
    decay0_nucltransK(prng_, event_, 0.089,0.050,3.93,0.,tclev,thlev,tdlev);
    return;
  label_10000  :
    return;
  label_20000  :
    // print *,'Gd156: wrong level [keV] ',levelkev_
    return;
  }
  // end of Gd156low.f

} // end of namespace bxdecay0

// end of Gd156low.cc
// Local Variables: --
// mode: c++ --
// End: --
