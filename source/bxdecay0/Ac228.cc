// Ourselves:
#include <bxdecay0/Ac228.h>

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

  // Ac228.f
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
  //

  void Ac228(i_random & prng_,
             event & event_,
             const double tcnuc_,
             double & tdnuc_)
  {
    double t;
    double tdlev;
    double p;
    double pbeta;
    double tclev;
    double thlev;
    double thnuc;
    // Scheme of 228Ac decay ("Table of Isotopes", 7th ed., 1978).
    // Two-, three- and four-figured labels correspond to energies of
    // 228Th excited levels in keV.
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 8.08.1992, 22.10.1995.
    thnuc=22068.;
    tdnuc_=tcnuc_-thnuc/std::log(2.)*std::log(prng_());
    tclev=0.;
    pbeta=100.*prng_();
    if (pbeta <=  0.20) goto label_2027;  // 0.20%
    if (pbeta <=  0.40) goto label_2010;  // 0.20%
    if (pbeta <=  0.44) goto label_1965;  // 0.04%
    if (pbeta <=  0.67) goto label_1945;  // 0.23%
    if (pbeta <=  0.77) goto label_1900;  // 0.10%
    if (pbeta <=  0.91) goto label_1893;  // 0.14%
    if (pbeta <=  1.02) goto label_1760;  // 0.11%
    if (pbeta <=  1.31) goto label_1744;  // 0.29%
    if (pbeta <=  2.81) goto label_1724;  // 1.50%
    if (pbeta <=  4.91) goto label_1689;  // 2.10%
    if (pbeta <=  6.41) goto label_1683;  // 1.50%
    if (pbeta <= 11.11) goto label_1646;  // 4.70%
    if (pbeta <= 11.91) goto label_1643;  // 0.80%
    if (pbeta <= 13.11) goto label_1638;  // 1.20%
    if (pbeta <= 13.18) goto label_1547;  // 0.07%
    if (pbeta <= 13.38) goto label_1539;  // 0.20%
    if (pbeta <= 21.38) goto label_1532;  // 8.00%
    if (pbeta <= 21.58) goto label_1489;  // 0.20%
    if (pbeta <= 23.48) goto label_1450;  // 1.90%
    if (pbeta <= 24.98) goto label_1432;  // 1.50%
    if (pbeta <= 25.18) goto label_1344;  // 0.20%
    if (pbeta <= 25.98) goto label_1227;  // 0.80%
    if (pbeta <= 29.58) goto label_1169;  // 3.60%
    if (pbeta <= 34.58) goto label_1154;  // 5.00%
    if (pbeta <= 39.98) goto label_1123;  // 5.40%
    if (pbeta <= 40.08) goto label_1060;  // 0.10%
    if (pbeta <= 42.08) goto label_1022;  // 2.00%
    if (pbeta <= 42.28) goto label_1016;  // 0.20%
    if (pbeta <= 42.38) goto label_979;  // 0.10%
    if (pbeta <= 74.33) goto label_969;  // 31.95%
    if (pbeta <= 74.63) goto label_968;  // 0.30%
    if (pbeta <= 74.86) goto label_944;  // 0.23%
    if (pbeta <= 75.00) goto label_875;  // 0.14%
    if (pbeta <= 75.20) goto label_519;  // 0.20%
    if (pbeta <= 88.20) goto label_396;  // 13.00%
    if (pbeta <= 89.00) goto label_187;   // 0.80%
    goto label_58;  // 11.00%
  label_2027  :
    decay0_beta(prng_, event_, 0.110,90.,0.,0.,t);
    //// -Wunused-label: label_20270  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 31.) goto label_20271;  // 31%
    goto label_20272;  // 69%
  label_20271  :
    decay0_nucltransK(prng_, event_, 1.509,0.110,3.2e-3,0.,tclev,thlev,tdlev);
    goto label_96900;
  label_20272  :
    decay0_nucltransK(prng_, event_, 1.004,0.110,3.0e-3,0.,tclev,thlev,tdlev);
    goto label_10220;
  label_2010  :
    decay0_beta(prng_, event_, 0.127,90.,0.,0.,t);
    //// -Wunused-label: label_20100  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 42.) goto label_20101;  // 42%
    if (p <= 72.) goto label_20102;  // 30%
    goto label_20103;  // 28%
  label_20101  :
    decay0_nucltransK(prng_, event_, 1.952,0.110,2.8e-3,1.6e-4,tclev,thlev,tdlev);
    goto label_58000;
  label_20102  :
    decay0_nucltransK(prng_, event_, 1.823,0.110,7.0e-3,1.7e-4,tclev,thlev,tdlev);
    goto label_18700;
  label_20103  :
    decay0_nucltransK(prng_, event_, 0.920,0.110,0.7e+0,0.,tclev,thlev,tdlev);
    goto label_10910;
  label_1965  :
    decay0_beta(prng_, event_, 0.172,90.,0.,0.,t);
    //// -Wunused-label:  label_19650  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 33.) goto label_19651;  // 33%
    goto label_19652;  // 67%
  label_19651  :
    decay0_nucltransK(prng_, event_, 1.966,0.110,1.2e-3,2.9e-4,tclev,thlev,tdlev);
    goto label_10000;
  label_19652  :
    decay0_nucltransK(prng_, event_, 1.907,0.110,1.8e-3,2.7e-4,tclev,thlev,tdlev);
    goto label_58000;
  label_1945  :
    decay0_beta(prng_, event_, 0.192,90.,0.,0.,t);
    //// -Wunused-label: label_19450  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 31.4) goto label_19451;  // 31.4%
    if (p <= 42.4) goto label_19452;  // 11.0%
    if (p <= 44.3) goto label_19453;  // 1.9%
    if (p <= 75.7) goto label_19454;  // 31.4%
    if (p <= 87.8) goto label_19455;  // 12.1%
    if (p <= 89.0) goto label_19456;  // 1.2%
    if (p <= 94.0) goto label_19457;  // 5.0%
    if (p <= 96.0) goto label_19458;  // 2.0%
    goto label_19459;  // 4.0%
  label_19451  :
    decay0_nucltransK(prng_, event_, 1.887,0.110,3.0e-3,1.3e-4,tclev,thlev,tdlev);
    goto label_58000;
  label_19452  :
    decay0_nucltransK(prng_, event_, 1.758,0.110,1.0e-2,2.0e-4,tclev,thlev,tdlev);
    goto label_18700;
  label_19453  :
    decay0_nucltransK(prng_, event_, 1.549,0.110,1.7e-3,0.6e-4,tclev,thlev,tdlev);
    goto label_39600;
  label_19454  :
    decay0_nucltransK(prng_, event_, 0.975,0.110,4.0e-2,0.,tclev,thlev,tdlev);
    goto label_96900;
  label_19455  :
    decay0_nucltransK(prng_, event_, 0.922,0.110,4.5e-2,0.,tclev,thlev,tdlev);
    goto label_10220;
  label_19456  :
    decay0_nucltransK(prng_, event_, 0.853,0.110,5.5e-2,0.,tclev,thlev,tdlev);
    goto label_10910;
  label_19457  :
    decay0_nucltransK(prng_, event_, 0.791,0.110,6.5e-2,0.,tclev,thlev,tdlev);
    goto label_11540;
  label_19458  :
    decay0_nucltransK(prng_, event_, 0.745,0.110,7.5e-2,0.,tclev,thlev,tdlev);
    goto label_12000;
  label_19459  :
    decay0_nucltransK(prng_, event_, 0.220,0.110,2.1e+0,0.,tclev,thlev,tdlev);
    goto label_17240;
  label_1900  :
    decay0_beta(prng_, event_, 0.237,90.,0.,0.,t);
    //// -Wunused-label: label_19000  :
    thlev=0.;
    p=100.*prng_();
    if (p <=  1.7) goto label_19001;  // 1.7%
    if (p <= 20.7) goto label_19002;  // 19.0%
    if (p <= 21.7) goto label_19003;  // 1.0%
    if (p <= 31.7) goto label_19004;  // 10.0%
    if (p <= 67.9) goto label_19005;  // 36.2%
    goto label_19006;  // 32.1%
  label_19001  :
    decay0_nucltransK(prng_, event_, 1.900,0.110,3.0e-3,1.3e-4,tclev,thlev,tdlev);
    goto label_10000;
  label_19002  :
    decay0_nucltransK(prng_, event_, 1.842,0.110,8.0e-3,2.0e-4,tclev,thlev,tdlev);
    goto label_58000;
  label_19003  :
    decay0_nucltransK(prng_, event_, 1.712,0.110,3.5e-3,0.8e-4,tclev,thlev,tdlev);
    goto label_18700;
  label_19004  :
    decay0_nucltransK(prng_, event_, 1.504,0.110,1.7e-3,0.5e-4,tclev,thlev,tdlev);
    goto label_39600;
  label_19005  :
    decay0_nucltransK(prng_, event_, 0.884,0.110,4.3e-3,0.,tclev,thlev,tdlev);
    goto label_10160;
  label_19006  :
    decay0_nucltransK(prng_, event_, 0.449,0.110,1.6e-2,0.,tclev,thlev,tdlev);
    goto label_14500;
  label_1893  :
    decay0_beta(prng_, event_, 0.244,90.,0.,0.,t);
    //// -Wunused-label: label_18930  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 17.0) goto label_18931;  // 17.0%
    if (p <= 22.6) goto label_18932;  // 5.6%
    if (p <= 38.6) goto label_18933;  // 16.0%
    if (p <= 47.6) goto label_18934;  // 9.0%
    if (p <= 74.8) goto label_18935;  // 27.2%
    if (p <= 76.8) goto label_18936;  // 2.0%
    if (p <= 77.8) goto label_18937;  // 1.0%
    goto label_18938;  // 22.2%
  label_18931  :
    decay0_nucltransK(prng_, event_, 1.835,0.110,6.0e-3,2.0e-4,tclev,thlev,tdlev);
    goto label_58000;
  label_18932  :
    decay0_nucltransK(prng_, event_, 1.706,0.110,1.0e-2,1.0e-4,tclev,thlev,tdlev);
    goto label_18700;
  label_18933  :
    decay0_nucltransK(prng_, event_, 0.940,0.110,1.0e-1,0.,tclev,thlev,tdlev);
    goto label_95200;
  label_18934  :
    decay0_nucltransK(prng_, event_, 0.924,0.110,4.5e-2,0.,tclev,thlev,tdlev);
    goto label_96900;
  label_18935  :
    decay0_nucltransK(prng_, event_, 0.870,0.110,5.2e-2,0.,tclev,thlev,tdlev);
    goto label_10220;
  label_18936  :
    decay0_nucltransK(prng_, event_, 0.739,0.110,3.3e-1,0.,tclev,thlev,tdlev);
    goto label_11540;
  label_18937  :
    decay0_nucltransK(prng_, event_, 0.693,0.110,1.2e-1,0.,tclev,thlev,tdlev);
    goto label_12000;
  label_18938  :
    decay0_nucltransK(prng_, event_, 0.461,0.110,2.8e-1,0.,tclev,thlev,tdlev);
    goto label_14320;
  label_1760  :
    decay0_beta(prng_, event_, 0.377,90.,0.,0.,t);
    //// -Wunused-label: label_17600  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 62.) goto label_17601;  // 62%
    goto label_17602;  // 38%
  label_17601  :
    decay0_nucltransK(prng_, event_, 1.702,0.110,1.4e-3,1.1e-4,tclev,thlev,tdlev);
    goto label_58000;
  label_17602  :
    decay0_nucltransK(prng_, event_, 1.574,0.110,1.7e-3,0.7e-4,tclev,thlev,tdlev);
    goto label_18700;
  label_1744  :
    decay0_beta(prng_, event_, 0.393,90.,0.,0.,t);
    //// -Wunused-label: label_17440  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 32.) goto label_17441;  // 32%
    if (p <= 94.) goto label_17442;  // 62%
    goto label_17443;  // 6%
  label_17441  :
    decay0_nucltransK(prng_, event_, 1.686,0.110,1.4e-3,1.6e-4,tclev,thlev,tdlev);
    goto label_58000;
  label_17442  :
    decay0_nucltransK(prng_, event_, 1.557,0.110,1.7e-3,0.6e-4,tclev,thlev,tdlev);
    goto label_18700;
  label_17443  :
    decay0_nucltransK(prng_, event_, 1.348,0.110,2.0e-3,0.2e-4,tclev,thlev,tdlev);
    goto label_39600;
  label_1724  :
    decay0_beta(prng_, event_, 0.413,90.,0.,0.,t);
  label_17240  :
    thlev=0.;
    p=100.*prng_();
    if (p <=  2.0) goto label_17241;  // 2.0%
    if (p <= 15.0) goto label_17242;  // 13.0%
    if (p <= 15.8) goto label_17243;  // 0.8%
    if (p <= 89.0) goto label_17244;  // 73.2%
    goto label_17245;  // 11.0%
  label_17241  :
    decay0_nucltransK(prng_, event_, 1.724,0.110,3.7e-3,0.7e-4,tclev,thlev,tdlev);
    goto label_10000;
  label_17242  :
    decay0_nucltransK(prng_, event_, 1.666,0.110,1.0e-2,1.2e-4,tclev,thlev,tdlev);
    goto label_58000;
  label_17243  :
    decay0_nucltransK(prng_, event_, 1.537,0.110,4.0e-3,0.4e-4,tclev,thlev,tdlev);
    goto label_18700;
  label_17244  :
    decay0_nucltransK(prng_, event_, 0.755,0.110,6.9e-2,0.,tclev,thlev,tdlev);
    goto label_96900;
  label_17245  :
    decay0_nucltransK(prng_, event_, 0.702,0.110,9.5e-2,0.,tclev,thlev,tdlev);
    goto label_10220;
  label_1689  :
    decay0_beta(prng_, event_, 0.448,90.,0.,0.,t);
    //// -Wunused-label: label_16890  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 72.3) goto label_16891;  // 72.3%
    if (p <= 98.0) goto label_16892;  // 25.7%
    goto label_16893;  // 2.0%
  label_16891  :
    decay0_nucltransK(prng_, event_, 1.631,0.110,7.4e-3,1.2e-4,tclev,thlev,tdlev);
    goto label_58000;
  label_16892  :
    decay0_nucltransK(prng_, event_, 1.502,0.110,1.7e-3,0.5e-4,tclev,thlev,tdlev);
    goto label_18700;
  label_16893  :
    decay0_nucltransK(prng_, event_, 0.666,0.110,7.5e-3,0.,tclev,thlev,tdlev);
    goto label_10220;
  label_1683  :
    decay0_beta(prng_, event_, 0.454,90.,0.,0.,t);
    //// -Wunused-label: label_16830  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 22.) goto label_16831;  // 22%
    if (p <= 90.) goto label_16832;  // 68%
    if (p <= 96.) goto label_16833;  // 6%
    goto label_16834;  // 4%
  label_16831  :
    decay0_nucltransK(prng_, event_, 1.625,0.110,1.5e-3,0.8e-4,tclev,thlev,tdlev);
    goto label_58000;
  label_16832  :
    decay0_nucltransK(prng_, event_, 1.496,0.110,1.7e-3,0.5e-4,tclev,thlev,tdlev);
    goto label_18700;
  label_16833  :
    decay0_nucltransK(prng_, event_, 1.287,0.110,2.2e-3,0.2e-4,tclev,thlev,tdlev);
    goto label_39600;
  label_16834  :
    decay0_nucltransK(prng_, event_, 1.165,0.110,2.6e-3,0.1e-4,tclev,thlev,tdlev);
    goto label_51900;
  label_1646  :
    decay0_beta(prng_, event_, 0.491,90.,0.,0.,t);
    //// -Wunused-label: label_16460  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 75.0) goto label_16461;  // 75.0%
    if (p <= 95.0) goto label_16462;  // 20.0%
    if (p <= 96.0) goto label_16463;  // 1.0%
    if (p <= 96.4) goto label_16464;  // 0.4%
    if (p <= 97.4) goto label_16465;  // 1.0%
    if (p <= 99.5) goto label_16466;  // 2.1%
    goto label_16467;  // 0.5%
  label_16461  :
    decay0_nucltransK(prng_, event_, 1.588,0.110,4.7e-3,0.5e-4,tclev,thlev,tdlev);
    goto label_58000;
  label_16462  :
    decay0_nucltransK(prng_, event_, 1.459,0.110,5.0e-3,0.3e-4,tclev,thlev,tdlev);
    goto label_18700;
  label_16463  :
    decay0_nucltransK(prng_, event_, 0.677,0.110,2.2e-2,0.,tclev,thlev,tdlev);
    goto label_96900;
  label_16464  :
    decay0_nucltransK(prng_, event_, 0.624,0.110,8.0e-3,0.,tclev,thlev,tdlev);
    goto label_10220;
  label_16465  :
    decay0_nucltransK(prng_, event_, 0.555,0.110,1.6e-1,0.,tclev,thlev,tdlev);
    goto label_10910;
  label_16466  :
    decay0_nucltransK(prng_, event_, 0.523,0.110,1.2e-2,0.,tclev,thlev,tdlev);
    goto label_11230;
  label_16467  :
    decay0_nucltransK(prng_, event_, 0.420,0.110,1.8e-2,0.,tclev,thlev,tdlev);
    goto label_12270;
  label_1643  :
    decay0_beta(prng_, event_, 0.494,90.,0.,0.,t);
    //// -Wunused-label: label_16430  :
    thlev=0.;
    p=100.*prng_();
    if (p <=  1.0) goto label_16431;  // 1.0%
    if (p <= 51.7) goto label_16432;  // 50.7%
    if (p <= 61.7) goto label_16433;  // 10.0%
    if (p <= 70.7) goto label_16434;  // 9.0%
    goto label_16435;  // 29.3%
  label_16431  :
    decay0_nucltransK(prng_, event_, 1.315,0.110,1.8e-2,0.6e-4,tclev,thlev,tdlev);
    goto label_32800;
  label_16432  :
    decay0_nucltransK(prng_, event_, 1.247,0.110,2.1e-2,0.4e-4,tclev,thlev,tdlev);
    goto label_39600;
  label_16433  :
    decay0_nucltransK(prng_, event_, 0.675,0.110,7.0e-3,0.,tclev,thlev,tdlev);
    goto label_96900;
  label_16434  :
    decay0_nucltransK(prng_, event_, 0.620,0.110,8.0e-3,0.,tclev,thlev,tdlev);
    goto label_10220;
  label_16435  :
    decay0_nucltransK(prng_, event_, 0.210,0.110,7.9e-2,0.,tclev,thlev,tdlev);
    goto label_14320;
  label_1638  :
    decay0_beta(prng_, event_, 0.499,90.,0.,0.,t);
    //// -Wunused-label: label_16380  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 38.) goto label_16381;  // 38%
    if (p <= 96.) goto label_16382;  // 58%
    goto label_16383;  // 4%
  label_16381  :
    decay0_nucltransK(prng_, event_, 1.638,0.110,4.0e-3,0.5e-4,tclev,thlev,tdlev);
    goto label_10000;
  label_16382  :
    decay0_nucltransK(prng_, event_, 1.581,0.110,1.1e-2,1.1e-4,tclev,thlev,tdlev);
    goto label_58000;
  label_16383  :
    decay0_nucltransK(prng_, event_, 0.516,0.110,1.2e-2,0.,tclev,thlev,tdlev);
    goto label_11230;
  label_1547  :
    decay0_beta(prng_, event_, 0.590,90.,0.,0.,t);
    //// -Wunused-label: label_15470  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 50.) goto label_15471;  // 50%
    if (p <= 86.) goto label_15472;  // 36%
    goto label_15473;  // 14%
  label_15471  :
    decay0_nucltransK(prng_, event_, 1.169,0.110,2.7e-3,0.2e-4,tclev,thlev,tdlev);
    goto label_37800;
  label_15472  :
    decay0_nucltransK(prng_, event_, 0.378,0.110,2.2e-2,0.,tclev,thlev,tdlev);
    goto label_11690;
  label_15473  :
    decay0_nucltransK(prng_, event_, 0.373,0.110,2.2e-2,0.,tclev,thlev,tdlev);
    goto label_11750;
  label_1539  :
    decay0_beta(prng_, event_, 0.598,90.,0.,0.,t);
    //// -Wunused-label: label_15390  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 12.) goto label_15391;  // 12%
    if (p <= 18.) goto label_15392;  // 6%
    if (p <= 32.) goto label_15393;  // 14%
    goto label_15394;  // 68%
  label_15391  :
    decay0_nucltransK(prng_, event_, 1.480,0.110,1.8e-3,0.5e-4,tclev,thlev,tdlev);
    goto label_58000;
  label_15392  :
    decay0_nucltransK(prng_, event_, 1.143,0.110,2.6e-2,0.3e-4,tclev,thlev,tdlev);
    goto label_39600;
  label_15393  :
    decay0_nucltransK(prng_, event_, 1.020,0.110,1.0e-2,0.,tclev,thlev,tdlev);
    goto label_51900;
  label_15394  :
    decay0_nucltransK(prng_, event_, 0.571,0.110,1.5e-1,0.,tclev,thlev,tdlev);
    goto label_96800;
  label_1532  :
    decay0_beta(prng_, event_, 0.605,90.,0.,0.,t);
    //// -Wunused-label: label_15320  :
    thlev=0.;
    p=100.*prng_();
    if (p <=  0.4) goto label_15321;  // 0.4%
    if (p <= 30.7) goto label_15322;  // 30.3%
    if (p <= 46.7) goto label_15323;  // 16.0%
    if (p <= 51.3) goto label_15324;  // 4.6%
    if (p <= 52.3) goto label_15325;  // 1.0%
    if (p <= 53.0) goto label_15326;  // 0.7%
    goto label_15327;  // 47.0%
  label_15321  :
    decay0_nucltransK(prng_, event_, 1.136,0.110,2.8e-3,0.2e-4,tclev,thlev,tdlev);
    goto label_39600;
  label_15322  :
    decay0_nucltransK(prng_, event_, 0.563,0.110,5.0e-2,0.,tclev,thlev,tdlev);
    goto label_96900;
  label_15323  :
    decay0_nucltransK(prng_, event_, 0.509,0.110,6.0e-2,0.,tclev,thlev,tdlev);
    goto label_10220;
  label_15324  :
    decay0_nucltransK(prng_, event_, 0.441,0.110,3.0e-1,0.,tclev,thlev,tdlev);
    goto label_10910;
  label_15325  :
    decay0_nucltransK(prng_, event_, 0.378,0.110,4.5e-1,0.,tclev,thlev,tdlev);
    goto label_11540;
  label_15326  :
    decay0_nucltransK(prng_, event_, 0.357,0.110,1.7e+0,0.,tclev,thlev,tdlev);
    goto label_11750;
  label_15327  :
    decay0_nucltransK(prng_, event_, 0.100,0.020,4.0e+0,0.,tclev,thlev,tdlev);
    goto label_14320;
  label_1489  :
    decay0_beta(prng_, event_, 0.648,90.,0.,0.,t);
    //// -Wunused-label: label_14890  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 22.) goto label_14891;  // 22%
    goto label_14892;  // 78%
  label_14891  :
    decay0_nucltransK(prng_, event_, 0.399,0.110,2.0e-2,0.,tclev,thlev,tdlev);
    goto label_10910;
  label_14892  :
    decay0_nucltransK(prng_, event_, 0.314,0.110,0.6e+0,0.,tclev,thlev,tdlev);
    goto label_11750;
  label_1450  :
    decay0_beta(prng_, event_, 0.687,90.,0.,0.,t);
  label_14500  :
    thlev=0.;
    p=100.*prng_();
    if (p <=  3.0) goto label_14501;  // 3.0%
    if (p <= 15.0) goto label_14502;  // 12.0%
    if (p <= 16.5) goto label_14503;  // 1.5%
    if (p <= 58.0) goto label_14504;  // 41.5%
    if (p <= 82.0) goto label_14505;  // 24.0%
    goto label_14506;  // 18.0%
  label_14501  :
    decay0_nucltransK(prng_, event_, 1.054,0.110,3.2e-2,0.,tclev,thlev,tdlev);
    goto label_39600;
  label_14502  :
    decay0_nucltransK(prng_, event_, 0.498,0.110,4.2e-2,0.,tclev,thlev,tdlev);
    goto label_95200;
  label_14503  :
    decay0_nucltransK(prng_, event_, 0.481,0.110,2.5e-1,0.,tclev,thlev,tdlev);
    goto label_96800;
  label_14504  :
    decay0_nucltransK(prng_, event_, 0.328,0.110,4.4e-2,0.,tclev,thlev,tdlev);
    goto label_11230;
  label_14505  :
    decay0_nucltransK(prng_, event_, 0.282,0.110,1.3e+0,0.,tclev,thlev,tdlev);
    goto label_11690;
  label_14506  :
    decay0_nucltransK(prng_, event_, 0.224,0.110,1.5e+0,0.,tclev,thlev,tdlev);
    goto label_12270;
  label_1432  :
    decay0_beta(prng_, event_, 0.705,90.,0.,0.,t);
  label_14320  :
    thlev=0.;
    p=100.*prng_();
    if (p <=  1.0) goto label_14321;  // 1.0%
    if (p <=  3.0) goto label_14322;  // 2.0%
    if (p <= 64.8) goto label_14323;  // 61.8%
    if (p <= 92.2) goto label_14324;  // 27.4%
    if (p <= 98.2) goto label_14325;  // 6.0%
    if (p <= 99.0) goto label_14326;  // 0.8%
    if (p <= 99.6) goto label_14327;  // 0.6%
    goto label_14328;  // 0.4%
  label_14321  :
    decay0_nucltransK(prng_, event_, 1.374,0.110,1.4e-2,0.7e-4,tclev,thlev,tdlev);
    goto label_58000;
  label_14322  :
    decay0_nucltransK(prng_, event_, 1.245,0.110,2.0e-2,0.4e-4,tclev,thlev,tdlev);
    goto label_18700;
  label_14323  :
    decay0_nucltransK(prng_, event_, 0.463,0.110,4.7e-2,0.,tclev,thlev,tdlev);
    goto label_96900;
  label_14324  :
    decay0_nucltransK(prng_, event_, 0.410,0.110,8.3e-2,0.,tclev,thlev,tdlev);
    goto label_10220;
  label_14325  :
    decay0_nucltransK(prng_, event_, 0.341,0.110,1.2e-1,0.,tclev,thlev,tdlev);
    goto label_10910;
  label_14326  :
    decay0_nucltransK(prng_, event_, 0.308,0.110,3.5e-2,0.,tclev,thlev,tdlev);
    goto label_11230;
  label_14327  :
    decay0_nucltransK(prng_, event_, 0.264,0.110,5.0e-2,0.,tclev,thlev,tdlev);
    goto label_11690;
  label_14328  :
    decay0_nucltransK(prng_, event_, 0.258,0.110,5.0e-2,0.,tclev,thlev,tdlev);
    goto label_11750;
  label_1344  :
    decay0_beta(prng_, event_, 0.793,90.,0.,0.,t);
    //// -Wunused-label: label_13440  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 27.0) goto label_13441;  // 27.0%
    if (p <= 64.5) goto label_13442;  // 37.5%
    if (p <= 95.0) goto label_13443;  // 30.5%
    goto label_13444;  // 5.0%
  label_13441  :
    decay0_nucltransK(prng_, event_, 1.017,0.110,3.5e-3,0.,tclev,thlev,tdlev);
    goto label_32800;
  label_13442  :
    decay0_nucltransK(prng_, event_, 0.948,0.110,3.7e-3,0.,tclev,thlev,tdlev);
    goto label_39600;
  label_13443  :
    decay0_nucltransK(prng_, event_, 0.825,0.110,5.0e-3,0.,tclev,thlev,tdlev);
    goto label_51900;
  label_13444  :
    decay0_nucltransK(prng_, event_, 0.169,0.110,1.4e-1,0.,tclev,thlev,tdlev);
    goto label_11750;
  label_1227  :
    decay0_beta(prng_, event_, 0.910,90.,0.,0.,t);
  label_12270  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 10.) goto label_12271;  // 10%
    if (p <= 68.) goto label_12272;  // 58%
    if (p <= 79.) goto label_12273;  // 11%
    if (p <= 97.) goto label_12274;  // 18%
    goto label_12275;  // 3%
  label_12271  :
    decay0_nucltransK(prng_, event_, 1.040,0.110,3.5e-3,0.,tclev,thlev,tdlev);
    goto label_18700;
  label_12272  :
    decay0_nucltransK(prng_, event_, 0.830,0.110,1.8e-2,0.,tclev,thlev,tdlev);
    goto label_39600;
  label_12273  :
    decay0_nucltransK(prng_, event_, 0.707,0.110,1.0e-1,0.,tclev,thlev,tdlev);
    goto label_51900;
  label_12274  :
    decay0_nucltransK(prng_, event_, 0.204,0.110,9.0e-2,0.,tclev,thlev,tdlev);
    goto label_10220;
  label_12275  :
    decay0_nucltransK(prng_, event_, 0.136,0.110,1.7e+0,0.,tclev,thlev,tdlev);
    goto label_10910;
  label_12000  :
    thlev=0.;
    decay0_nucltransK(prng_, event_, 0.178,0.110,6.0e+1,0.,tclev,thlev,tdlev);
    goto label_10220;
  label_11750  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 67.) goto label_11751;  // 67%
    goto label_11752;  // 33%
  label_11751  :
    decay0_nucltransK(prng_, event_, 0.988,0.110,3.5e-3,0.,tclev,thlev,tdlev);
    goto label_18700;
  label_11752  :
    decay0_nucltransK(prng_, event_, 0.796,0.110,5.2e-3,0.,tclev,thlev,tdlev);
    goto label_37800;
  label_1169  :
    decay0_beta(prng_, event_, 0.968,90.,0.,0.,t);
  label_11690  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 11.0) goto label_11691;  // 11.0%
    if (p <= 38.8) goto label_11692;  // 27.8%
    if (p <= 84.5) goto label_11693;  // 45.7%
    if (p <= 84.8) goto label_11694;  // 0.3%
    if (p <= 93.8) goto label_11695;  // 9.0%
    if (p <= 98.9) goto label_11696;  // 5.1%
    goto label_11697;  // 1.1%
  label_11691  :
    decay0_nucltransK(prng_, event_, 1.110,0.110,2.9e-3,0.1e-4,tclev,thlev,tdlev);
    goto label_58000;
  label_11692  :
    decay0_nucltransK(prng_, event_, 0.840,0.110,1.4e-2,0.,tclev,thlev,tdlev);
    goto label_32800;
  label_11693  :
    decay0_nucltransK(prng_, event_, 0.772,0.110,1.5e-2,0.,tclev,thlev,tdlev);
    goto label_39600;
  label_11694  :
    decay0_nucltransK(prng_, event_, 0.649,0.110,2.4e-2,0.,tclev,thlev,tdlev);
    goto label_51900;
  label_11695  :
    decay0_nucltransK(prng_, event_, 0.200,0.110,9.5e-2,0.,tclev,thlev,tdlev);
    goto label_96900;
  label_11696  :
    decay0_nucltransK(prng_, event_, 0.146,0.110,1.2e+0,0.,tclev,thlev,tdlev);
    goto label_10220;
  label_11697  :
    decay0_nucltransK(prng_, event_, 0.078,0.020,2.2e-1,0.,tclev,thlev,tdlev);
    goto label_10910;
  label_1154  :
    decay0_beta(prng_, event_, 0.983,90.,0.,0.,t);
  label_11540  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 14.9) goto label_11541;  // 14.9%
    if (p <= 25.8) goto label_11542;  // 10.9%
    if (p <= 40.7) goto label_11543;  // 14.9%
    if (p <= 61.4) goto label_11544;  // 20.7%
    if (p <= 84.1) goto label_11545;  // 22.7%
    if (p <= 93.0) goto label_11546;  // 8.9%
    if (p <= 97.0) goto label_11547;  // 4.0%
    goto label_11548;  // 3.0%
  label_11541  :
    decay0_nucltransK(prng_, event_, 1.154,0.110,7.5e-3,0.1e-4,tclev,thlev,tdlev);
    goto label_10000;
  label_11542  :
    decay0_nucltransK(prng_, event_, 1.096,0.110,2.8e-2,0.1e-4,tclev,thlev,tdlev);
    goto label_58000;
  label_11543  :
    decay0_nucltransK(prng_, event_, 0.967,0.110,2.0e-2,0.,tclev,thlev,tdlev);
    goto label_18700;
  label_11544  :
    decay0_nucltransK(prng_, event_, 0.322,0.110,5.2e-1,0.,tclev,thlev,tdlev);
    goto label_83200;
  label_11545  :
    decay0_nucltransK(prng_, event_, 0.279,0.110,1.3e+0,0.,tclev,thlev,tdlev);
    goto label_87500;
  label_11546  :
    decay0_nucltransK(prng_, event_, 0.185,0.110,5.4e+1,0.,tclev,thlev,tdlev);
    goto label_96900;
  label_11547  :
    decay0_nucltransK(prng_, event_, 0.174,0.110,1.4e+0,0.,tclev,thlev,tdlev);
    goto label_97900;
  label_11548  :
    decay0_nucltransK(prng_, event_, 0.138,0.110,4.9e+0,0.,tclev,thlev,tdlev);
    goto label_10160;
  label_1123  :
    decay0_beta(prng_, event_, 1.014,90.,0.,0.,t);
  label_11230  :
    thlev=0.;
    p=100.*prng_();
    if (p <=  1.4) goto label_11231;  // 1.4%
    if (p <=  5.4) goto label_11232;  // 4.0%
    if (p <=  5.6) goto label_11233;  // 0.2%
    if (p <= 73.8) goto label_11234;  // 68.2%
    if (p <= 85.8) goto label_11235;  // 12.0%
    if (p <= 98.1) goto label_11236;  // 12.3%
    goto label_11237;  // 1.9%
  label_11231  :
    decay0_nucltransK(prng_, event_, 1.123,0.110,6.5e-2,0.1e-4,tclev,thlev,tdlev);
    goto label_10000;
  label_11232  :
    decay0_nucltransK(prng_, event_, 1.065,0.110,3.2e-3,0.,tclev,thlev,tdlev);
    goto label_58000;
  label_11233  :
    decay0_nucltransK(prng_, event_, 0.936,0.110,0.1e+0,0.,tclev,thlev,tdlev);
    goto label_18700;
  label_11234  :
    decay0_nucltransK(prng_, event_, 0.795,0.110,1.9e-2,0.,tclev,thlev,tdlev);
    goto label_32800;
  label_11235  :
    decay0_nucltransK(prng_, event_, 0.727,0.110,1.0e-2,0.,tclev,thlev,tdlev);
    goto label_39600;
  label_11236  :
    decay0_nucltransK(prng_, event_, 0.154,0.110,0.2e+0,0.,tclev,thlev,tdlev);
    goto label_96900;
  label_11237  :
    decay0_nucltransK(prng_, event_, 0.100,0.020,3.3e-1,0.,tclev,thlev,tdlev);
    goto label_10220;
  label_10910  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 21.) goto label_10911;  // 21%
    goto label_10912;  // 79%
  label_10911  :
    decay0_nucltransK(prng_, event_, 1.033,0.110,9.5e-3,0.,tclev,thlev,tdlev);
    goto label_58000;
  label_10912  :
    decay0_nucltransK(prng_, event_, 0.904,0.110,2.6e-2,0.,tclev,thlev,tdlev);
    goto label_18700;
  label_1060  :
    decay0_beta(prng_, event_, 1.077,90.,0.,0.,t);
    //// -Wunused-label: label_10600  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 74.) goto label_10601;  // 74%
    if (p <= 87.) goto label_10602;  // 13%
    goto label_10603;  // 13%
  label_10601  :
    decay0_nucltransK(prng_, event_, 1.002,0.110,3.5e-3,0.,tclev,thlev,tdlev);
    goto label_58000;
  label_10602  :
    decay0_nucltransK(prng_, event_, 0.664,0.110,7.0e-3,0.,tclev,thlev,tdlev);
    goto label_39600;
  label_10603  :
    decay0_nucltransK(prng_, event_, 0.541,0.110,1.1e-2,0.,tclev,thlev,tdlev);
    goto label_51900;
  label_1022  :
    decay0_beta(prng_, event_, 1.115,90.,0.,0.,t);
  label_10220  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 73.) goto label_10221;  // 73%
    goto label_10222;  // 27%
  label_10221  :
    decay0_nucltransK(prng_, event_, 0.964,0.110,9.2e-3,0.,tclev,thlev,tdlev);
    goto label_58000;
  label_10222  :
    decay0_nucltransK(prng_, event_, 0.836,0.110,1.4e-2,0.,tclev,thlev,tdlev);
    goto label_18700;
  label_1016  :
    decay0_beta(prng_, event_, 1.121,90.,0.,0.,t);
  label_10160  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 19.) goto label_10161;  // 19%
    if (p <= 66.) goto label_10162;  // 47%
    if (p <= 82.) goto label_10163;  // 16%
    goto label_10164;  // 18%
  label_10161  :
    decay0_nucltransK(prng_, event_, 1.017,0.110,2.4e-2,0.,tclev,thlev,tdlev);
    goto label_10000;
  label_10162  :
    decay0_nucltransK(prng_, event_, 0.958,0.110,3.8e-3,0.,tclev,thlev,tdlev);
    goto label_58000;
  label_10163  :
    decay0_nucltransK(prng_, event_, 0.688,0.110,2.1e-2,0.,tclev,thlev,tdlev);
    goto label_32800;
  label_10164  :
    decay0_nucltransK(prng_, event_, 0.620,0.110,1.4e-1,0.,tclev,thlev,tdlev);
    goto label_39600;
  label_979  :
    decay0_beta(prng_, event_, 1.158,90.,0.,0.,t);
  label_97900  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 35.) goto label_97901;  // 35%
    goto label_97902;  // 65%
  label_97901  :
    decay0_nucltransK(prng_, event_, 0.651,0.110,7.5e-3,0.,tclev,thlev,tdlev);
    goto label_32800;
  label_97902  :
    decay0_nucltransK(prng_, event_, 0.583,0.110,9.5e-3,0.,tclev,thlev,tdlev);
    goto label_39600;
  label_969  :
    decay0_beta(prng_, event_, 1.168,90.,0.,0.,t);
  label_96900  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 37.0) goto label_96901;  // 37.0%
    if (p <= 98.8) goto label_96902;  // 61.8%
    goto label_96903;  // 1.2%
  label_96901  :
    decay0_nucltransK(prng_, event_, 0.969,0.110,1.0e-2,0.,tclev,thlev,tdlev);
    goto label_10000;
  label_96902  :
    decay0_nucltransK(prng_, event_, 0.911,0.110,1.2e-2,0.,tclev,thlev,tdlev);
    goto label_58000;
  label_96903  :
    decay0_nucltransK(prng_, event_, 0.782,0.110,6.8e-2,0.,tclev,thlev,tdlev);
    goto label_18700;
  label_968  :
    decay0_beta(prng_, event_, 1.169,90.,0.,0.,t);
  label_96800  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 22.) goto label_96801;  // 22%
    goto label_96802;  // 78%
  label_96801  :
    decay0_nucltransK(prng_, event_, 0.641,0.110,1.1e-1,0.,tclev,thlev,tdlev);
    goto label_32800;
  label_96802  :
    decay0_nucltransK(prng_, event_, 0.572,0.110,1.3e-1,0.,tclev,thlev,tdlev);
    goto label_39600;
  label_95200  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 91.) goto label_95201;  // 91%
    if (p <= 94.) goto label_95202;  // 3%
    goto label_95203;  // 6%
  label_95201  :
    decay0_nucltransK(prng_, event_, 0.894,0.110,4.2e-3,0.,tclev,thlev,tdlev);
    goto label_58000;
  label_95202  :
    decay0_nucltransK(prng_, event_, 0.624,0.110,1.2e-1,0.,tclev,thlev,tdlev);
    goto label_32800;
  label_95203  :
    decay0_nucltransK(prng_, event_, 0.556,0.110,3.5e-2,0.,tclev,thlev,tdlev);
    goto label_39600;
  label_944  :
    decay0_beta(prng_, event_, 1.193,90.,0.,0.,t);
    //// -Wunused-label: label_94400  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 42.5) goto label_94401;  // 42.5%
    if (p <= 57.5) goto label_94402;  // 15.0%
    goto label_94403;  // 42.5%
  label_94401  :
    decay0_nucltransK(prng_, event_, 0.944,0.110,1.1e-2,0.,tclev,thlev,tdlev);
    goto label_10000;
  label_94402  :
    decay0_nucltransK(prng_, event_, 0.888,0.110,7.5e-1,0.,tclev,thlev,tdlev);
    goto label_58000;
  label_94403  :
    decay0_nucltransK(prng_, event_, 0.616,0.110,8.5e-3,0.,tclev,thlev,tdlev);
    goto label_32800;
  label_875  :
    decay0_beta(prng_, event_, 1.262,90.,0.,0.,t);
  label_87500  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 15.) goto label_87501;  // 15%
    if (p <= 26.) goto label_87502;  // 11%
    if (p <= 60.) goto label_87503;  // 34%
    goto label_87504;  // 40%
  label_87501  :
    decay0_nucltransK(prng_, event_, 0.874,0.110,1.3e-2,0.,tclev,thlev,tdlev);
    goto label_10000;
  label_87502  :
    decay0_nucltransK(prng_, event_, 0.816,0.110,0.5e+0,0.,tclev,thlev,tdlev);
    goto label_58000;
  label_87503  :
    decay0_nucltransK(prng_, event_, 0.546,0.110,1.1e-2,0.,tclev,thlev,tdlev);
    goto label_32800;
  label_87504  :
    decay0_nucltransK(prng_, event_, 0.479,0.110,1.4e-2,0.,tclev,thlev,tdlev);
    goto label_39600;
  label_83200  :
    thlev=0.;
    p=100.*prng_();
    if (p <=  4.) goto label_83201;  // 4%
    if (p <= 27.) goto label_83202;  // 23%
    goto label_83203;  // 73%
  label_83201  :
    decay0_electron(prng_, event_, 0.721,tclev,thlev,tdlev)  ;// only ec
    // decay0_gamma(prng_, event_, 0.110,tdlev,0.,tdlev)  // for real time
    decay0_gamma(prng_, event_, 0.110,0.,0.,tdlev)  ;// for time shift
    goto label_10000;
  label_83202  :
    decay0_nucltransK(prng_, event_, 0.771,0.110,1.7e-2,0.,tclev,thlev,tdlev);
    goto label_58000;
  label_83203  :
    decay0_nucltransK(prng_, event_, 0.504,0.110,1.2e-2,0.,tclev,thlev,tdlev);
    goto label_32800;
  label_519  :
    decay0_beta(prng_, event_, 1.618,90.,0.,0.,t);
  label_51900  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 90.) goto label_51901;  // 90%
    goto label_51902;  // 10%
  label_51901  :
    decay0_nucltransK(prng_, event_, 0.332,0.110,4.7e-1,0.,tclev,thlev,tdlev);
    goto label_18700;
  label_51902  :
    decay0_nucltransK(prng_, event_, 0.141,0.110,0.9e+0,0.,tclev,thlev,tdlev);
    goto label_37800;
  label_396  :
    decay0_beta(prng_, event_, 1.741,90.,0.,0.,t);
  label_39600  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 73.) goto label_39601;  // 73%
    goto label_39602;  // 27%
  label_39601  :
    decay0_nucltransK(prng_, event_, 0.338,0.110,1.0e-2,0.,tclev,thlev,tdlev);
    goto label_58000;
  label_39602  :
    decay0_nucltransK(prng_, event_, 0.209,0.110,7.9e-2,0.,tclev,thlev,tdlev);
    goto label_18700;
  label_37800  :
    thlev=0.;
    decay0_nucltransK(prng_, event_, 0.191,0.110,4.2e-1,0.,tclev,thlev,tdlev);
    goto label_18700;
  label_32800  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 47.) goto label_32801;  // 47%
    goto label_32802;  // 53%
  label_32801  :
    decay0_nucltransK(prng_, event_, 0.328,0.110,4.4e-2,0.,tclev,thlev,tdlev);
    goto label_10000;
  label_32802  :
    decay0_nucltransK(prng_, event_, 0.270,0.110,3.4e-2,0.,tclev,thlev,tdlev);
    goto label_58000;
  label_187  :
    decay0_beta(prng_, event_, 1.950,90.,0.,0.,t);
  label_18700  :
    thlev=0.16e-9;
    decay0_nucltransK(prng_, event_, 0.129,0.020,2.7e+0,0.,tclev,thlev,tdlev);
    goto label_58000;
  label_58  :
    decay0_beta(prng_, event_, 2.079,90.,0.,0.,t);
  label_58000  :
    thlev=0.40e-9;
    decay0_nucltransK(prng_, event_, 0.058,0.020,1.2e+2,0.,tclev,thlev,tdlev);
  label_10000  :
    return;
  }

} // end of namespace bxdecay0

// Local Variables: --
// mode: c++ --
// End: --
