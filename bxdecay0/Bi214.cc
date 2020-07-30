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
#include <bxdecay0/Bi214.h>

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

  void Bi214(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_)
  {
    double t;
    double tdlev;
    double p;
    double palfa;
    double pbeta;
    double pdecay;
    double tclev;
    double thlev;
    double thnuc;
    // Scheme of Bi214 decay ("Table of Isotopes", 7th ed., 1978).
    // Two-, three- and four-figured labels correspond to energies of
    // 210Tl or 214Po excited levels in keV. Beta-alfa decays to 210Pb
    // are not considered (p=2.8e-3%).
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 13.08.1992, 22.10.1995.
    // VIT, 31.05.2005, updated to NDS 99(2003)649. Not well known alpha decays to
    // 210Tl levels with E>253 keV are omitted.
    thnuc  = 1194.;
    tdnuc_ = tcnuc_ - thnuc / std::log(2.) * std::log(prng_());
    tclev  = 0.;
    pdecay = 100. * prng_();
    if (pdecay <= 0.021)
      goto label_10000; // 0.021% alfa to 210Tl
    goto label_20000;   // 99.979% beta to 214Po
  label_10000:
    palfa = 100. * prng_();
    if (palfa <= 5.86)
      goto label_253; // 5.86%
    if (palfa <= 60.36)
      goto label_63;  // 54.50%
    goto label_10001; // 39.64%
  label_253:
    decay0_alpha(prng_, event_, 5.273, 0., 0., t);
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 0.191, 0.086, 1.3, 0., tclev, thlev, tdlev);
    goto label_63000;
  label_63:
    decay0_alpha(prng_, event_, 5.452, 0., 0., t);
  label_63000:
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 0.063, 0.015, 6.48, 0., tclev, thlev, tdlev);
    return;
  label_10001:
    decay0_alpha(prng_, event_, 5.516, 0., 0., t);
    return;
  label_20000:
    pbeta = 100. * prng_();
    if (pbeta <= 0.001)
      goto label_3184; // 0.001%
    if (pbeta <= 0.002)
      goto label_3160; // 0.001%
    if (pbeta <= 0.003)
      goto label_3143; // 0.001%
    if (pbeta <= 0.008)
      goto label_3082; // 0.005%
    if (pbeta <= 0.012)
      goto label_3054; // 0.004%
    if (pbeta <= 0.017)
      goto label_3014; // 0.005%
    if (pbeta <= 0.024)
      goto label_3003; // 0.007%
    if (pbeta <= 0.034)
      goto label_3000; // 0.010%
    if (pbeta <= 0.043)
      goto label_2986; // 0.009%
    if (pbeta <= 0.060)
      goto label_2979; // 0.017%
    if (pbeta <= 0.102)
      goto label_2941; // 0.042%
    if (pbeta <= 0.104)
      goto label_2935; // 0.002%
    if (pbeta <= 0.105)
      goto label_2929; // 0.001%
    if (pbeta <= 0.128)
      goto label_2922; // 0.023%
    if (pbeta <= 0.129)
      goto label_2920; // 0.001%
    if (pbeta <= 0.134)
      goto label_2897; // 0.005%
    if (pbeta <= 0.145)
      goto label_2894; // 0.011%
    if (pbeta <= 0.156)
      goto label_2880; // 0.011%
    if (pbeta <= 0.170)
      goto label_2870; // 0.014%
    if (pbeta <= 0.184)
      goto label_2861; // 0.014%
    if (pbeta <= 0.186)
      goto label_2827; // 0.002%
    if (pbeta <= 0.222)
      goto label_2786; // 0.036%
    if (pbeta <= 0.258)
      goto label_2770; // 0.036%
    if (pbeta <= 0.819)
      goto label_2729; // 0.561%
    if (pbeta <= 1.097)
      goto label_2719; // 0.278%
    if (pbeta <= 1.151)
      goto label_2699; // 0.054%
    if (pbeta <= 1.204)
      goto label_2698; // 0.053%
    if (pbeta <= 1.467)
      goto label_2695; // 0.263%
    if (pbeta <= 1.594)
      goto label_2662; // 0.127%
    if (pbeta <= 1.615)
      goto label_2631; // 0.021%
    if (pbeta <= 1.699)
      goto label_2605; // 0.084%
    if (pbeta <= 1.752)
      goto label_2545; // 0.053%
    if (pbeta <= 1.892)
      goto label_2508; // 0.140%
    if (pbeta <= 2.085)
      goto label_2505; // 0.193%
    if (pbeta <= 3.417)
      goto label_2482; // 1.332%
    if (pbeta <= 6.232)
      goto label_2448; // 2.815%
    if (pbeta <= 6.312)
      goto label_2423; // 0.080%
    if (pbeta <= 6.872)
      goto label_2293; // 0.560%
    if (pbeta <= 7.073)
      goto label_2266; // 0.201%
    if (pbeta <= 12.802)
      goto label_2204; // 5.729%
    if (pbeta <= 13.635)
      goto label_2193; // 0.833%
    if (pbeta <= 14.056)
      goto label_2148; // 0.421%
    if (pbeta <= 18.323)
      goto label_2119; // 4.267%
    if (pbeta <= 18.419)
      goto label_2088; // 0.096%
    if (pbeta <= 20.623)
      goto label_2017; // 2.204%
    if (pbeta <= 21.995)
      goto label_2011; // 1.372%
    if (pbeta <= 23.137)
      goto label_1995; // 1.142%
    if (pbeta <= 24.730)
      goto label_1890; // 1.593%
    if (pbeta <= 32.923)
      goto label_1847; // 8.193%
    if (pbeta <= 49.996)
      goto label_1764; // 17.073%
    if (pbeta <= 50.109)
      goto label_1743; // 0.113%
    if (pbeta <= 67.963)
      goto label_1730; // 17.854%
    if (pbeta <= 68.113)
      goto label_1713; // 0.150%
    if (pbeta <= 68.834)
      goto label_1661; // 0.721%
    if (pbeta <= 71.789)
      goto label_1543; // 2.955%
    if (pbeta <= 72.600)
      goto label_1415; // 0.811%
    if (pbeta <= 80.042)
      goto label_1378; // 7.442%
    if (pbeta <= 81.745)
      goto label_609; // 1.703%
    goto label_20001; // 18.255%
  label_3184:
    decay0_beta(prng_, event_, 0.088, 84., 0., 0., t);
    //// label_31840  :
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 3.184, 0.093, 4.0e-4, 8.0e-4, tclev, thlev, tdlev);
    return;
  label_3160:
    decay0_beta(prng_, event_, 0.112, 84., 0., 0., t);
    //// label_31600  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 41.)
      goto label_31601; // 41%
    goto label_31602;   // 59%
  label_31601:
    decay0_nucltransK(prng_, event_, 3.160, 0.093, 4.0e-4, 8.0e-4, tclev, thlev, tdlev);
    return;
  label_31602:
    decay0_nucltransK(prng_, event_, 2.551, 0.093, 6.0e-4, 4.6e-4, tclev, thlev, tdlev);
    goto label_60900;
  label_3143:
    decay0_beta(prng_, event_, 0.129, 84., 0., 0., t);
    //// label_31430  :
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 3.143, 0.093, 4.0e-4, 8.0e-4, tclev, thlev, tdlev);
    return;
  label_3082:
    decay0_beta(prng_, event_, 0.190, 84., 0., 0., t);
    //// label_30820  :
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 3.082, 0.093, 4.2e-4, 8.0e-4, tclev, thlev, tdlev);
    return;
  label_3054:
    decay0_beta(prng_, event_, 0.218, 84., 0., 0., t);
    //// label_30540  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 60.0)
      goto label_30541; // 60.0%
    if (p <= 82.9)
      goto label_30542; // 22.9%
    goto label_30543;   // 17.1%
  label_30541:
    decay0_nucltransK(prng_, event_, 3.054, 0.093, 1.0e-3, 8.0e-4, tclev, thlev, tdlev);
    return;
  label_30542:
    decay0_nucltransK(prng_, event_, 2.445, 0.093, 1.5e-3, 5.2e-4, tclev, thlev, tdlev);
    goto label_60900;
  label_30543:
    decay0_nucltransK(prng_, event_, 1.637, 0.093, 3.5e-3, 0.5e-4, tclev, thlev, tdlev);
    goto label_14150;
  label_3014:
    decay0_beta(prng_, event_, 0.258, 84., 0., 0., t);
    //// label_30140  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 0.9)
      goto label_30141; // 0.9%
    if (p <= 27.8)
      goto label_30142; // 26.9%
    if (p <= 41.7)
      goto label_30143; // 13.4%
    if (p <= 61.8)
      goto label_30144; // 20.6%
    goto label_30145;   // 38.2%
  label_30141:
    decay0_nucltransK(prng_, event_, 2.405, 0.093, 3.0e-3, 4.1e-4, tclev, thlev, tdlev);
    goto label_60900;
  label_30142:
    decay0_nucltransK(prng_, event_, 1.636, 0.093, 7.0e-3, 1.2e-4, tclev, thlev, tdlev);
    goto label_13780;
  label_30143:
    decay0_nucltransK(prng_, event_, 1.598, 0.093, 8.0e-3, 1.1e-4, tclev, thlev, tdlev);
    goto label_14150;
  label_30144:
    decay0_nucltransK(prng_, event_, 1.471, 0.093, 9.0e-3, 0.9e-4, tclev, thlev, tdlev);
    goto label_15430;
  label_30145:
    decay0_nucltransK(prng_, event_, 1.285, 0.093, 1.2e-2, 0.5e-4, tclev, thlev, tdlev);
    goto label_17300;
  label_3003:
    decay0_beta(prng_, event_, 0.269, 84., 0., 0., t);
    //// label_30030  :
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 1.156, 0.093, 1.8e-2, 3.0e-6, tclev, thlev, tdlev);
    goto label_18470;
  label_3000:
    decay0_beta(prng_, event_, 0.272, 84., 0., 0., t);
    //// label_30000  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 84.6)
      goto label_30001; // 84.6%
    goto label_30002;   // 15.4%
  label_30001:
    decay0_nucltransK(prng_, event_, 3.000, 0.093, 1.4e-3, 6.5e-4, tclev, thlev, tdlev);
    return;
  label_30002:
    decay0_nucltransK(prng_, event_, 2.391, 0.093, 2.8e-3, 4.0e-4, tclev, thlev, tdlev);
    goto label_60900;
  label_2986:
    decay0_beta(prng_, event_, 0.286, 84., 0., 0., t);
    //// label_29860  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 83.0)
      goto label_29861; // 83.0%
    goto label_29862;   // 17.0%
  label_29861:
    decay0_nucltransK(prng_, event_, 2.377, 0.093, 2.8e-3, 4.0e-4, tclev, thlev, tdlev);
    goto label_60900;
  label_29862:
    decay0_nucltransK(prng_, event_, 1.711, 0.093, 6.0e-3, 1.3e-4, tclev, thlev, tdlev);
    goto label_12750;
  label_2979:
    decay0_beta(prng_, event_, 0.293, 84., 0., 0., t);
    //// label_29790  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 83.6)
      goto label_29791; // 83.6%
    goto label_29792;   // 16.4%
  label_29791:
    decay0_nucltransK(prng_, event_, 2.979, 0.093, 1.4e-3, 6.5e-4, tclev, thlev, tdlev);
    return;
  label_29792:
    decay0_nucltransK(prng_, event_, 2.369, 0.093, 2.8e-3, 4.0e-4, tclev, thlev, tdlev);
    goto label_60900;
  label_2941:
    decay0_beta(prng_, event_, 0.331, 84., 0., 0., t);
    //// label_29410  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 52.1)
      goto label_29411; // 52.1%
    if (p <= 71.7)
      goto label_29412; // 19.6%
    goto label_29413;   // 28.3%
  label_29411:
    decay0_nucltransK(prng_, event_, 2.331, 0.093, 3.0e-3, 3.8e-4, tclev, thlev, tdlev);
    goto label_60900;
  label_29412:
    decay0_nucltransK(prng_, event_, 1.666, 0.093, 7.0e-3, 1.1e-4, tclev, thlev, tdlev);
    goto label_12750;
  label_29413:
    decay0_nucltransK(prng_, event_, 1.279, 0.093, 1.2e-2, 1.5e-5, tclev, thlev, tdlev);
    goto label_16610;
  label_2935:
    decay0_beta(prng_, event_, 0.337, 84., 0., 0., t);
    //// label_29350  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 21.3)
      goto label_29351; // 21.3%
    goto label_29352;   // 78.7%
  label_29351:
    decay0_nucltransK(prng_, event_, 2.935, 0.093, 1.5e-3, 6.3e-4, tclev, thlev, tdlev);
    return;
  label_29352:
    decay0_nucltransK(prng_, event_, 2.325, 0.093, 3.0e-3, 3.7e-4, tclev, thlev, tdlev);
    goto label_60900;
  label_2929:
    decay0_beta(prng_, event_, 0.343, 84., 0., 0., t);
    //// label_29290  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 73.3)
      goto label_29291; // 73.3%
    goto label_29292;   // 26.7%
  label_29291:
    decay0_nucltransK(prng_, event_, 2.929, 0.093, 1.5e-3, 6.2e-4, tclev, thlev, tdlev);
    return;
  label_29292:
    decay0_nucltransK(prng_, event_, 2.319, 0.093, 3.0e-3, 3.7e-4, tclev, thlev, tdlev);
    goto label_60900;
  label_2922:
    decay0_beta(prng_, event_, 0.350, 84., 0., 0., t);
    //// label_29220  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 60.9)
      goto label_29221; // 60.9%
    goto label_29222;   // 39.1%
  label_29221:
    decay0_nucltransK(prng_, event_, 2.922, 0.093, 4.5e-4, 8.0e-4, tclev, thlev, tdlev);
    return;
  label_29222:
    decay0_nucltransK(prng_, event_, 2.312, 0.093, 3.0e-3, 3.7e-4, tclev, thlev, tdlev);
    goto label_60900;
  label_2920:
    decay0_beta(prng_, event_, 0.352, 84., 0., 0., t);
    //// label_29200  :
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 2.310, 0.093, 3.0e-3, 3.7e-4, tclev, thlev, tdlev);
    goto label_60900;
  label_2897:
    decay0_beta(prng_, event_, 0.375, 84., 0., 0., t);
    //// label_28970  :
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 2.287, 0.093, 3.0e-3, 3.6e-4, tclev, thlev, tdlev);
    goto label_60900;
  label_2894:
    decay0_beta(prng_, event_, 0.378, 84., 0., 0., t);
    //// label_28940  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 26.1)
      goto label_28941; // 26.1%
    if (p <= 48.3)
      goto label_28942; // 22.2%
    if (p <= 78.3)
      goto label_28943; // 30.0%
    goto label_28944;   // 21.7%
  label_28941:
    decay0_nucltransK(prng_, event_, 2.894, 0.093, 1.7e-3, 6.1e-4, tclev, thlev, tdlev);
    return;
  label_28942:
    decay0_nucltransK(prng_, event_, 2.284, 0.093, 3.0e-3, 3.6e-4, tclev, thlev, tdlev);
    goto label_60900;
  label_28943:
    decay0_nucltransK(prng_, event_, 1.516, 0.093, 9.0e-3, 6.7e-5, tclev, thlev, tdlev);
    goto label_13780;
  label_28944:
    decay0_nucltransK(prng_, event_, 0.626, 0.093, 7.5e-2, 0., tclev, thlev, tdlev);
    goto label_22660;
  label_2880:
    decay0_beta(prng_, event_, 0.392, 84., 0., 0., t);
    //// label_28800  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 87.6)
      goto label_28801; // 87.6%
    goto label_28802;   // 12.4%
  label_28801:
    decay0_nucltransK(prng_, event_, 2.880, 0.093, 1.7e-3, 6.0e-4, tclev, thlev, tdlev);
    return;
  label_28802:
    decay0_nucltransK(prng_, event_, 2.270, 0.093, 3.0e-3, 3.5e-4, tclev, thlev, tdlev);
    goto label_60900;
  label_2870:
    decay0_beta(prng_, event_, 0.402, 84., 0., 0., t);
    //// label_28700  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 63.5)
      goto label_28701; // 63.5%
    goto label_28702;   // 36.5%
  label_28701:
    decay0_nucltransK(prng_, event_, 2.260, 0.093, 3.0e-3, 3.5e-4, tclev, thlev, tdlev);
    goto label_60900;
  label_28702:
    decay0_nucltransK(prng_, event_, 1.595, 0.093, 8.0e-3, 9.1e-5, tclev, thlev, tdlev);
    goto label_12750;
  label_2861:
    decay0_beta(prng_, event_, 0.411, 84., 0., 0., t);
    //// label_28610  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 2.7)
      goto label_28611; // 2.7%
    if (p <= 41.5)
      goto label_28612; // 38.8%
    goto label_28613;   // 58.5%
  label_28611:
    decay0_nucltransK(prng_, event_, 2.861, 0.093, 1.8e-3, 6.0e-4, tclev, thlev, tdlev);
    return;
  label_28612:
    decay0_nucltransK(prng_, event_, 2.252, 0.093, 3.5e-3, 3.4e-4, tclev, thlev, tdlev);
    goto label_60900;
  label_28613:
    decay0_nucltransK(prng_, event_, 1.014, 0.093, 2.2e-2, 0., tclev, thlev, tdlev);
    goto label_18470;
  label_2827:
    decay0_beta(prng_, event_, 0.445, 84., 0., 0., t);
    //// label_28270  :
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 2.827, 0.093, 1.8e-3, 5.8e-4, tclev, thlev, tdlev);
    return;
  label_2786:
    decay0_beta(prng_, event_, 0.486, 84., 0., 0., t);
    //// label_27860  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 15.4)
      goto label_27861; // 15.4%
    if (p <= 24.4)
      goto label_27862; // 9.0%
    if (p <= 63.6)
      goto label_27863; // 39.2%
    goto label_27864;   // 36.4%
  label_27861:
    decay0_nucltransK(prng_, event_, 2.786, 0.093, 1.8e-3, 5.7e-4, tclev, thlev, tdlev);
    return;
  label_27862:
    decay0_nucltransK(prng_, event_, 2.177, 0.093, 3.5e-3, 3.1e-4, tclev, thlev, tdlev);
    goto label_60900;
  label_27863:
    decay0_nucltransK(prng_, event_, 1.021, 0.093, 1.2e-2, 0., tclev, thlev, tdlev);
    goto label_17640;
  label_27864:
    decay0_nucltransK(prng_, event_, 0.939, 0.093, 1.4e-2, 0., tclev, thlev, tdlev);
    goto label_18470;
  label_2770:
    decay0_beta(prng_, event_, 0.502, 84., 0., 0., t);
    //// label_27700  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 54.6)
      goto label_27701; // 54.6%
    if (p <= 58.5)
      goto label_27702; // 3.9%
    goto label_27703;   // 41.5%
  label_27701:
    decay0_nucltransK(prng_, event_, 2.770, 0.093, 1.8e-3, 5.6e-4, tclev, thlev, tdlev);
    return;
  label_27702:
    decay0_nucltransK(prng_, event_, 2.160, 0.093, 3.5e-3, 3.1e-4, tclev, thlev, tdlev);
    goto label_60900;
  label_27703:
    decay0_nucltransK(prng_, event_, 1.393, 0.093, 1.0e-2, 3.6e-5, tclev, thlev, tdlev);
    goto label_13780;
  label_2729:
    decay0_beta(prng_, event_, 0.543, 84., 0., 0., t);
    //// label_27290  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 1.2)
      goto label_27291; // 1.2%
    if (p <= 6.0)
      goto label_27292; // 4.8%
    if (p <= 71.5)
      goto label_27293; // 65.5%
    if (p <= 79.4)
      goto label_27294; // 7.9%
    if (p <= 82.6)
      goto label_27295; // 3.2%
    if (p <= 85.7)
      goto label_27296; // 3.1%
    goto label_27297;   // 14.3%
  label_27291:
    decay0_nucltransK(prng_, event_, 2.120, 0.093, 3.5e-3, 2.9e-4, tclev, thlev, tdlev);
    goto label_60900;
  label_27292:
    decay0_nucltransK(prng_, event_, 1.067, 0.093, 2.1e-2, 1.4e-7, tclev, thlev, tdlev);
    goto label_16610;
  label_27293:
    decay0_nucltransK(prng_, event_, 0.964, 0.093, 1.4e-2, 0., tclev, thlev, tdlev);
    goto label_17640;
  label_27294:
    decay0_nucltransK(prng_, event_, 0.734, 0.093, 2.7e-2, 0., tclev, thlev, tdlev);
    goto label_19950;
  label_27295:
    decay0_nucltransK(prng_, event_, 0.525, 0.093, 6.0e-2, 0., tclev, thlev, tdlev);
    goto label_22040;
  label_27296:
    decay0_nucltransK(prng_, event_, 0.520, 0.093, 7.0e-2, 0., tclev, thlev, tdlev);
    goto label_22090;
  label_27297:
    decay0_nucltransK(prng_, event_, 0.281, 0.093, 3.3e-1, 0., tclev, thlev, tdlev);
    goto label_24480;
  label_2719:
    decay0_beta(prng_, event_, 0.553, 84., 0., 0., t);
    //// label_27190  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 0.7)
      goto label_27191; // 0.7%
    if (p <= 33.6)
      goto label_27192; // 32.9%
    if (p <= 41.8)
      goto label_27193; // 8.2%
    if (p <= 83.6)
      goto label_27194; // 41.8%
    if (p <= 90.7)
      goto label_27195; // 7.1%
    if (p <= 97.0)
      goto label_27196; // 6.3%
    goto label_27197;   // 3.0%
  label_27191:
    decay0_nucltransK(prng_, event_, 2.719, 0.093, 2.0e-3, 5.4e-4, tclev, thlev, tdlev);
    return;
  label_27192:
    decay0_nucltransK(prng_, event_, 2.110, 0.093, 3.5e-3, 2.9e-4, tclev, thlev, tdlev);
    goto label_60900;
  label_27193:
    decay0_nucltransK(prng_, event_, 1.341, 0.093, 1.0e-2, 2.6e-5, tclev, thlev, tdlev);
    goto label_13780;
  label_27194:
    decay0_nucltransK(prng_, event_, 1.304, 0.093, 1.0e-2, 1.9e-5, tclev, thlev, tdlev);
    goto label_14150;
  label_27195:
    decay0_nucltransK(prng_, event_, 0.976, 0.093, 2.6e-2, 0., tclev, thlev, tdlev);
    goto label_17430;
  label_27196:
    decay0_nucltransK(prng_, event_, 0.709, 0.093, 2.9e-2, 0., tclev, thlev, tdlev);
    goto label_20110;
  label_27197:
    decay0_nucltransK(prng_, event_, 0.600, 0.093, 9.0e-2, 0., tclev, thlev, tdlev);
    goto label_21190;
  label_2699:
    decay0_beta(prng_, event_, 0.573, 84., 0., 0., t);
    //// label_26990  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 5.3)
      goto label_26991; // 5.3%
    goto label_26992;   // 94.7%
  label_26991:
    decay0_nucltransK(prng_, event_, 2.699, 0.093, 2.0e-3, 5.3e-4, tclev, thlev, tdlev);
    return;
  label_26992:
    decay0_nucltransK(prng_, event_, 2.090, 0.093, 4.0e-3, 2.8e-4, tclev, thlev, tdlev);
    goto label_60900;
  label_2698:
    decay0_beta(prng_, event_, 0.574, 84., 0., 0., t);
    //// label_26980  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 29.5)
      goto label_26981; // 29.5%
    if (p <= 44.8)
      goto label_26982; // 15.3%
    if (p <= 63.3)
      goto label_26983; // 18.5%
    if (p <= 76.0)
      goto label_26984; // 12.7%
    goto label_26985;   // 24.0%
  label_26981:
    decay0_nucltransK(prng_, event_, 1.156, 0.093, 1.6e-2, 2.9e-6, tclev, thlev, tdlev);
    goto label_15430;
  label_26982:
    decay0_nucltransK(prng_, event_, 1.038, 0.093, 2.0e-2, 0., tclev, thlev, tdlev);
    goto label_16610;
  label_26983:
    decay0_nucltransK(prng_, event_, 0.935, 0.093, 2.8e-2, 0., tclev, thlev, tdlev);
    goto label_17640;
  label_26984:
    decay0_nucltransK(prng_, event_, 0.688, 0.093, 6.5e-2, 0., tclev, thlev, tdlev);
    goto label_20110;
  label_26985:
    decay0_nucltransK(prng_, event_, 0.494, 0.093, 7.0e-2, 0., tclev, thlev, tdlev);
    goto label_22040;
  label_2695:
    decay0_beta(prng_, event_, 0.577, 84., 0., 0., t);
    //// label_26950  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 11.9)
      goto label_26951; // 11.9%
    if (p <= 15.4)
      goto label_26952; // 3.5%
    if (p <= 17.4)
      goto label_26953; // 2.0%
    if (p <= 48.7)
      goto label_26954; // 30.7%
    if (p <= 57.3)
      goto label_26955; // 9.2%
    if (p <= 59.6)
      goto label_26956; // 2.3%
    if (p <= 72.3)
      goto label_26957; // 12.7%
    if (p <= 82.3)
      goto label_26958; // 10.0%
    if (p <= 88.4)
      goto label_26959; // 6.1%
    if (p <= 90.7)
      goto label_26960; // 2.3%
    goto label_26961;   // 9.3%
  label_26951:
    decay0_nucltransK(prng_, event_, 2.695, 0.093, 2.0e-3, 5.3e-4, tclev, thlev, tdlev);
    return;
  label_26952:
    decay0_nucltransK(prng_, event_, 2.085, 0.093, 4.0e-3, 2.8e-4, tclev, thlev, tdlev);
    goto label_60900;
  label_26953:
    decay0_nucltransK(prng_, event_, 1.420, 0.093, 9.5e-3, 4.2e-5, tclev, thlev, tdlev);
    goto label_12750;
  label_26954:
    decay0_nucltransK(prng_, event_, 1.317, 0.093, 1.2e-2, 2.1e-5, tclev, thlev, tdlev);
    goto label_13780;
  label_26955:
    decay0_nucltransK(prng_, event_, 1.033, 0.093, 2.2e-2, 0., tclev, thlev, tdlev);
    goto label_16610;
  label_26956:
    decay0_nucltransK(prng_, event_, 0.952, 0.093, 2.8e-2, 0., tclev, thlev, tdlev);
    goto label_17430;
  label_26957:
    decay0_nucltransK(prng_, event_, 0.930, 0.093, 1.5e-2, 0., tclev, thlev, tdlev);
    goto label_17640;
  label_26958:
    decay0_nucltransK(prng_, event_, 0.847, 0.093, 1.9e-2, 0., tclev, thlev, tdlev);
    goto label_18470;
  label_26959:
    decay0_nucltransK(prng_, event_, 0.700, 0.093, 3.0e-2, 0., tclev, thlev, tdlev);
    goto label_19950;
  label_26960:
    decay0_nucltransK(prng_, event_, 0.677, 0.093, 7.5e-2, 0., tclev, thlev, tdlev);
    goto label_20170;
  label_26961:
    decay0_nucltransK(prng_, event_, 0.486, 0.093, 8.0e-2, 0., tclev, thlev, tdlev);
    goto label_22090;
  label_2662:
    decay0_beta(prng_, event_, 0.610, 84., 0., 0., t);
    //// label_26620  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 0.2)
      goto label_26621; // 0.2%
    if (p <= 55.0)
      goto label_26622; // 54.8%
    if (p <= 63.7)
      goto label_26623; // 8.7%
    if (p <= 95.6)
      goto label_26624; // 31.9%
    goto label_26625;   // 4.4%
  label_26621:
    decay0_nucltransK(prng_, event_, 2.662, 0.093, 2.0e-3, 5.1e-4, tclev, thlev, tdlev);
    return;
  label_26622:
    decay0_nucltransK(prng_, event_, 2.053, 0.093, 4.0e-3, 2.6e-4, tclev, thlev, tdlev);
    goto label_60900;
  label_26623:
    decay0_nucltransK(prng_, event_, 1.284, 0.093, 1.3e-2, 1.6e-5, tclev, thlev, tdlev);
    goto label_13780;
  label_26624:
    decay0_nucltransK(prng_, event_, 1.119, 0.093, 1.9e-2, 1.2e-6, tclev, thlev, tdlev);
    goto label_15430;
  label_26625:
    decay0_nucltransK(prng_, event_, 0.950, 0.093, 2.8e-2, 0., tclev, thlev, tdlev);
    goto label_17130;
  label_2631:
    decay0_beta(prng_, event_, 0.641, 84., 0., 0., t);
    ////label_26310  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 3.8)
      goto label_26311; // 3.8%
    goto label_26312;   // 96.2%
  label_26311:
    decay0_nucltransK(prng_, event_, 2.631, 0.093, 2.2e-3, 5.0e-4, tclev, thlev, tdlev);
    return;
  label_26312:
    decay0_nucltransK(prng_, event_, 2.022, 0.093, 4.0e-3, 2.5e-4, tclev, thlev, tdlev);
    goto label_60900;
  label_2605:
    decay0_beta(prng_, event_, 0.667, 84., 0., 0., t);
    //// label_26050  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 0.5)
      goto label_26051; // 0.5%
    if (p <= 7.1)
      goto label_26052; // 6.6%
    if (p <= 21.7)
      goto label_26053; // 14.6%
    if (p <= 44.2)
      goto label_26054; // 22.5%
    if (p <= 56.1)
      goto label_26055; // 11.9%
    goto label_26056;   // 43.9%
  label_26051:
    decay0_nucltransK(prng_, event_, 2.605, 0.093, 2.2e-3, 4.9e-4, tclev, thlev, tdlev);
    return;
  label_26052:
    decay0_nucltransK(prng_, event_, 1.995, 0.093, 4.5e-3, 2.4e-4, tclev, thlev, tdlev);
    goto label_60900;
  label_26053:
    decay0_nucltransK(prng_, event_, 1.330, 0.093, 1.1e-2, 2.4e-5, tclev, thlev, tdlev);
    goto label_12750;
  label_26054:
    decay0_nucltransK(prng_, event_, 0.943, 0.093, 2.8e-2, 0., tclev, thlev, tdlev);
    goto label_16610;
  label_26055:
    decay0_nucltransK(prng_, event_, 0.840, 0.093, 4.0e-2, 0., tclev, thlev, tdlev);
    goto label_17640;
  label_26056:
    decay0_nucltransK(prng_, event_, 0.396, 0.093, 1.3e-1, 0., tclev, thlev, tdlev);
    goto label_22090;
  label_2545:
    decay0_beta(prng_, event_, 0.727, 84., 0., 0., t);
    ////label_25450  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 77.4)
      goto label_25451; // 77.4%
    goto label_25452;   // 22.6%
  label_25451:
    decay0_nucltransK(prng_, event_, 1.936, 0.093, 3.0e-3, 2.1e-4, tclev, thlev, tdlev);
    goto label_60900;
  label_25452:
    decay0_nucltransK(prng_, event_, 1.167, 0.093, 1.6e-2, 3.6e-6, tclev, thlev, tdlev);
    goto label_13780;
  label_2508:
    decay0_beta(prng_, event_, 0.764, 84., 0., 0., t);
    ////label_25080  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 49.8)
      goto label_25081; // 49.8%
    if (p <= 84.8)
      goto label_25082; // 35.0%
    if (p <= 93.5)
      goto label_25083; // 8.7%
    goto label_25084;   // 6.5%
  label_25081:
    decay0_nucltransK(prng_, event_, 1.899, 0.093, 5.0e-3, 2.0e-4, tclev, thlev, tdlev);
    goto label_60900;
  label_25082:
    decay0_nucltransK(prng_, event_, 1.130, 0.093, 1.8e-2, 1.6e-6, tclev, thlev, tdlev);
    goto label_13780;
  label_25083:
    decay0_nucltransK(prng_, event_, 0.965, 0.093, 2.6e-2, 0., tclev, thlev, tdlev);
    goto label_15430;
  label_25084:
    decay0_nucltransK(prng_, event_, 0.497, 0.093, 7.0e-2, 0., tclev, thlev, tdlev);
    goto label_20110;
  label_2505:
    decay0_beta(prng_, event_, 0.767, 84., 0., 0., t);
    ////label_25050  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 3.0)
      goto label_25051; // 3.0%
    if (p <= 86.0)
      goto label_25052; // 83.0%
    if (p <= 93.8)
      goto label_25053; // 7.8%
    goto label_25054;   // 6.2%
  label_25051:
    decay0_nucltransK(prng_, event_, 2.505, 0.093, 2.4e-3, 4.5e-4, tclev, thlev, tdlev);
    return;
  label_25052:
    decay0_nucltransK(prng_, event_, 1.896, 0.093, 5.0e-3, 2.0e-4, tclev, thlev, tdlev);
    goto label_60900;
  label_25053:
    decay0_nucltransK(prng_, event_, 1.231, 0.093, 1.4e-2, 9.2e-6, tclev, thlev, tdlev);
    goto label_12750;
  label_25054:
    decay0_nucltransK(prng_, event_, 0.962, 0.093, 2.6e-2, 0., tclev, thlev, tdlev);
    goto label_15430;
  label_2482:
    decay0_beta(prng_, event_, 0.790, 84., 0., 0., t);
    ////label_24820  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 0.1)
      goto label_24821; // 0.1%
    if (p <= 16.7)
      goto label_24822; // 16.6%
    if (p <= 51.0)
      goto label_24823; // 34.3%
    if (p <= 56.9)
      goto label_24824; // 5.9%
    if (p <= 58.3)
      goto label_24825; // 1.4%
    if (p <= 70.7)
      goto label_24826; // 12.4%
    if (p <= 80.9)
      goto label_24827; // 10.2%
    if (p <= 81.4)
      goto label_24828; // 0.5%
    if (p <= 83.5)
      goto label_24829; // 2.1%
    if (p <= 84.8)
      goto label_24830; // 1.3%
    goto label_24831;   // 15.2%
  label_24821:
    decay0_nucltransK(prng_, event_, 2.483, 0.093, 2.5e-3, 4.4e-4, tclev, thlev, tdlev);
    return;
  label_24822:
    decay0_nucltransK(prng_, event_, 1.873, 0.093, 5.0e-3, 1.9e-4, tclev, thlev, tdlev);
    goto label_60900;
  label_24823:
    decay0_nucltransKLM(prng_, event_, 1.208, 0.093, 1.6e-3, 0.017, 2.5e-4, 0.004, 8.0e-5, 6.4e-5, tclev, thlev, tdlev);
    goto label_12750;
  label_24824:
    decay0_nucltransK(prng_, event_, 1.105, 0.093, 1.0e-2, 7.8e-7, tclev, thlev, tdlev);
    goto label_13780;
  label_24825:
    decay0_nucltransKLM(prng_, event_, 0.940, 0.093, 1.4e-2, 0.017, 2.5e-3, 0.004, 5.0e-4, 0., tclev, thlev, tdlev);
    goto label_15430;
  label_24826:
    decay0_nucltransK(prng_, event_, 0.821, 0.093, 3.7e-2, 0., tclev, thlev, tdlev);
    goto label_16610;
  label_24827:
    decay0_nucltransKLM(prng_, event_, 0.753, 0.093, 2.4e-2, 0.017, 4.4e-3, 0.004, 6.0e-4, 0., tclev, thlev, tdlev);
    goto label_17300;
  label_24828:
    decay0_nucltransKLM(prng_, event_, 0.635, 0.093, 3.6e-2, 0.017, 7.0e-3, 0.004, 7.0e-3, 0., tclev, thlev, tdlev);
    goto label_18470;
  label_24829:
    decay0_nucltransKLM(prng_, event_, 0.488, 0.093, 8.9e-3, 0.017, 1.5e-3, 0.004, 4.5e-4, 0., tclev, thlev, tdlev);
    goto label_19950;
  label_24830:
    decay0_nucltransK(prng_, event_, 0.394, 0.093, 1.3e-1, 0., tclev, thlev, tdlev);
    goto label_20880;
  label_24831:
    decay0_nucltransK(prng_, event_, 0.274, 0.093, 3.6e-1, 0., tclev, thlev, tdlev);
    goto label_22090;
  label_2448:
    decay0_beta(prng_, event_, 0.824, 84., 0., 0., t);
  label_24480:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 54.3)
      goto label_24481; // 54.3%
    if (p <= 66.8)
      goto label_24482; // 12.5%
    if (p <= 68.6)
      goto label_24483; // 1.8%
    if (p <= 78.1)
      goto label_24484; // 9.5%
    if (p <= 80.8)
      goto label_24485; // 2.7%
    if (p <= 83.7)
      goto label_24486; // 2.9%
    if (p <= 94.4)
      goto label_24487; // 10.7%
    if (p <= 96.0)
      goto label_24488; // 1.6%
    if (p <= 98.8)
      goto label_24489; // 2.8%
    goto label_24490;   // 1.2%
  label_24481:
    decay0_nucltransK(prng_, event_, 2.448, 0.093, 6.0e-4, 9.4e-4, tclev, thlev, tdlev);
    return;
  label_24482:
    decay0_nucltransK(prng_, event_, 1.838, 0.093, 1.2e-3, 5.3e-4, tclev, thlev, tdlev);
    goto label_60900;
  label_24483:
    decay0_nucltransKLM(prng_, event_, 1.173, 0.093, 4.4e-3, 0.017, 8.3e-4, 0.004, 2.8e-4, 6.2e-6, tclev, thlev, tdlev);
    goto label_12750;
  label_24484:
    decay0_nucltransKLM(prng_, event_, 1.070, 0.093, 2.0e-3, 0.017, 3.1e-4, 0.004, 1.0e-4, 5.5e-6, tclev, thlev, tdlev);
    goto label_13780;
  label_24485:
    decay0_nucltransKLM(prng_, event_, 1.032, 0.093, 2.1e-3, 0.017, 3.3e-4, 0.004, 1.1e-4, 0., tclev, thlev, tdlev);
    goto label_14150;
  label_24486:
    decay0_nucltransKLM(prng_, event_, 0.904, 0.093, 2.7e-3, 0.017, 4.2e-4, 0.004, 1.4e-4, 0., tclev, thlev, tdlev);
    goto label_15430;
  label_24487:
    decay0_nucltransKLM(prng_, event_, 0.786, 0.093, 3.5e-3, 0.017, 5.5e-4, 0.004, 1.9e-4, 0., tclev, thlev, tdlev);
    goto label_16610;
  label_24488:
    decay0_nucltransKLM(prng_, event_, 0.705, 0.093, 4.3e-3, 0.017, 6.9e-4, 0.004, 2.2e-4, 0., tclev, thlev, tdlev);
    goto label_17430;
  label_24489:
    decay0_nucltransKLM(prng_, event_, 0.683, 0.093, 4.6e-3, 0.017, 7.3e-4, 0.004, 2.4e-4, 0., tclev, thlev, tdlev);
    goto label_17640;
  label_24490:
    decay0_nucltransKLM(prng_, event_, 0.453, 0.093, 8.0e-2, 0.017, 1.7e-2, 0.004, 5.6e-3, 0., tclev, thlev, tdlev);
    goto label_19950;
  label_2423:
    decay0_beta(prng_, event_, 0.849, 84., 0., 0., t);
    ////label_24230  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 7.2)
      goto label_24231; // 7.2%
    if (p <= 24.5)
      goto label_24232; // 17.3%
    if (p <= 65.4)
      goto label_24233; // 40.9%
    if (p <= 74.8)
      goto label_24234; // 9.4%
    goto label_24235;   // 25.2%
  label_24231:
    decay0_nucltransK(prng_, event_, 2.423, 0.093, 6.5e-4, 9.2e-4, tclev, thlev, tdlev);
    return;
  label_24232:
    decay0_nucltransK(prng_, event_, 1.814, 0.093, 1.2e-3, 5.1e-4, tclev, thlev, tdlev);
    goto label_60900;
  label_24233:
    decay0_nucltransK(prng_, event_, 1.046, 0.093, 2.8e-3, 1.4e-6, tclev, thlev, tdlev);
    goto label_13780;
  label_24234:
    decay0_nucltransK(prng_, event_, 0.693, 0.093, 5.7e-3, 0., tclev, thlev, tdlev);
    goto label_17300;
  label_24235:
    decay0_nucltransK(prng_, event_, 0.659, 0.093, 3.5e-2, 0., tclev, thlev, tdlev);
    goto label_17640;
  label_2293:
    decay0_beta(prng_, event_, 0.979, 84., 0., 0., t);
    ////label_22930  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 54.6)
      goto label_22931; // 54.6%
    if (p <= 93.2)
      goto label_22932; // 38.6%
    if (p <= 97.9)
      goto label_22933; // 4.7%
    goto label_22934;   // 2.1%
  label_22931:
    decay0_nucltransK(prng_, event_, 2.293, 0.093, 3.0e-3, 3.6e-4, tclev, thlev, tdlev);
    return;
  label_22932:
    decay0_nucltransK(prng_, event_, 1.684, 0.093, 7.0e-3, 1.2e-4, tclev, thlev, tdlev);
    goto label_60900;
  label_22933:
    decay0_nucltransK(prng_, event_, 0.916, 0.093, 1.8e-2, 0., tclev, thlev, tdlev);
    goto label_13780;
  label_22934:
    decay0_nucltransK(prng_, event_, 0.878, 0.093, 2.0e-2, 0., tclev, thlev, tdlev);
    goto label_14150;
  label_2266:
    decay0_beta(prng_, event_, 1.006, 84., 0., 0., t);
  label_22660:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 9.0)
      goto label_22661; // 9.0%
    if (p <= 31.9)
      goto label_22662; // 22.9%
    if (p <= 36.9)
      goto label_22663; // 5.0%
    if (p <= 54.8)
      goto label_22664; // 17.9%
    if (p <= 90.6)
      goto label_22665; // 35.8%
    goto label_22666;   // 9.4%
  label_22661:
    decay0_nucltransK(prng_, event_, 2.266, 0.093, 1.8e-3, 4.4e-4, tclev, thlev, tdlev);
    return;
  label_22662:
    decay0_nucltransK(prng_, event_, 1.657, 0.093, 1.3e-3, 3.9e-4, tclev, thlev, tdlev);
    goto label_60900;
  label_22663:
    decay0_nucltransK(prng_, event_, 0.991, 0.093, 1.3e-2, 0., tclev, thlev, tdlev);
    goto label_12750;
  label_22664:
    decay0_nucltransK(prng_, event_, 0.723, 0.093, 2.8e-2, 0., tclev, thlev, tdlev);
    goto label_15430;
  label_22665:
    decay0_nucltransK(prng_, event_, 0.537, 0.093, 6.0e-2, 0., tclev, thlev, tdlev);
    goto label_17300;
  label_22666:
    decay0_nucltransK(prng_, event_, 0.502, 0.093, 7.0e-2, 0., tclev, thlev, tdlev);
    goto label_17640;
  label_22090:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 82.1)
      goto label_22091; // 82.1%
    goto label_22092;   // 17.9%
  label_22091:
    decay0_nucltransK(prng_, event_, 1.599, 0.093, 8.0e-3, 9.2e-5, tclev, thlev, tdlev);
    goto label_60900;
  label_22092:
    decay0_nucltransK(prng_, event_, 0.934, 0.093, 2.8e-2, 0., tclev, thlev, tdlev);
    goto label_12750;
  label_2204:
    decay0_beta(prng_, event_, 1.068, 84., 0., 0., t);
  label_22040:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 87.9)
      goto label_22041; // 87.9%
    if (p <= 92.2)
      goto label_22042; // 4.3%
    if (p <= 94.2)
      goto label_22043; // 2.0%
    if (p <= 94.5)
      goto label_22044; // 0.3%
    if (p <= 95.3)
      goto label_22045; // 0.8%
    if (p <= 96.9)
      goto label_22046; // 1.6%
    if (p <= 99.0)
      goto label_22047; // 2.1%
    goto label_22048;   // 1.0%
  label_22041:
    decay0_nucltransK(prng_, event_, 2.204, 0.093, 3.5e-3, 3.2e-4, tclev, thlev, tdlev);
    return;
  label_22042:
    decay0_nucltransK(prng_, event_, 1.595, 0.093, 5.5e-3, 9.1e-5, tclev, thlev, tdlev);
    goto label_60900;
  label_22043:
    decay0_nucltransKLM(prng_, event_, 0.826, 0.093, 2.9e-2, 0.017, 5.0e-3, 0.004, 2.0e-3, 0., tclev, thlev, tdlev);
    goto label_13780;
  label_22044:
    decay0_nucltransKLM(prng_, event_, 0.789, 0.093, 3.3e-2, 0.017, 5.7e-3, 0.004, 1.9e-3, 0., tclev, thlev, tdlev);
    goto label_14150;
  label_22045:
    decay0_nucltransKLM(prng_, event_, 0.661, 0.093, 3.3e-2, 0.017, 6.0e-3, 0.004, 2.0e-3, 0., tclev, thlev, tdlev);
    goto label_15430;
  label_22046:
    decay0_nucltransKLM(prng_, event_, 0.543, 0.093, 5.0e-2, 0.017, 1.1e-2, 0.004, 9.0e-3, 0., tclev, thlev, tdlev);
    goto label_17130;
  label_22047:
    decay0_nucltransKLM(prng_, event_, 0.474, 0.093, 7.0e-2, 0.017, 1.5e-2, 0.004, 4.9e-3, 0., tclev, thlev, tdlev);
    goto label_17300;
  label_22048:
    decay0_nucltransKLM(prng_, event_, 0.461, 0.093, 1.4e-1, 0.017, 2.3e-2, 0.004, 7.4e-3, 0., tclev, thlev, tdlev);
    goto label_17430;
  label_2193:
    decay0_beta(prng_, event_, 1.079, 84., 0., 0., t);
    ////label_21930  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 4.1)
      goto label_21931; // 4.1%
    if (p <= 87.2)
      goto label_21932; // 83.1%
    if (p <= 87.8)
      goto label_21933; // 0.6%
    if (p <= 92.5)
      goto label_21934; // 4.7%
    goto label_21935;   // 7.5%
  label_21931:
    decay0_nucltransK(prng_, event_, 2.193, 0.093, 2.0e-3, 4.1e-4, tclev, thlev, tdlev);
    return;
  label_21932:
    decay0_nucltransK(prng_, event_, 1.583, 0.093, 5.4e-3, 8.7e-5, tclev, thlev, tdlev);
    goto label_60900;
  label_21933:
    decay0_nucltransKLM(prng_, event_, 0.918, 0.093, 2.6e-3, 0.017, 4.1e-4, 0.004, 1.4e-4, 0., tclev, thlev, tdlev);
    goto label_12750;
  label_21934:
    decay0_nucltransKLM(prng_, event_, 0.815, 0.093, 1.9e-2, 0.017, 3.6e-3, 0.004, 1.4e-3, 0., tclev, thlev, tdlev);
    goto label_13780;
  label_21935:
    decay0_nucltransKLM(prng_, event_, 0.649, 0.093, 3.4e-2, 0.017, 6.0e-3, 0.004, 3.0e-3, 0., tclev, thlev, tdlev);
    goto label_15430;
  label_2148:
    decay0_beta(prng_, event_, 1.122, 84., 0., 0., t);
    ////label_21480  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 3.2)
      goto label_21481; // 3.2%
    if (p <= 89.0)
      goto label_21482; // 85.8%
    if (p <= 93.1)
      goto label_21483; // 4.1%
    goto label_21484;   // 6.9%
  label_21481:
    decay0_nucltransK(prng_, event_, 2.148, 0.093, 3.5e-3, 3.0e-4, tclev, thlev, tdlev);
    return;
  label_21482:
    decay0_nucltransK(prng_, event_, 1.539, 0.093, 8.0e-3, 1.0e-4, tclev, thlev, tdlev);
    goto label_60900;
  label_21483:
    decay0_nucltransK(prng_, event_, 0.873, 0.093, 3.5e-2, 0., tclev, thlev, tdlev);
    goto label_12750;
  label_21484:
    decay0_nucltransK(prng_, event_, 0.770, 0.093, 4.5e-2, 0., tclev, thlev, tdlev);
    goto label_13780;
  label_2119:
    decay0_beta(prng_, event_, 1.151, 84., 0., 0., t);
  label_21190:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 26.7)
      goto label_21191; // 26.7%
    if (p <= 76.4)
      goto label_21192; // 49.7%
    if (p <= 77.3)
      goto label_21193; // 0.9%
    if (p <= 89.0)
      goto label_21194; // 11.7%
    goto label_21195;   // 11.0%
  label_21191:
    decay0_nucltransK(prng_, event_, 2.119, 0.093, 3.5e-3, 2.9e-4, tclev, thlev, tdlev);
    return;
  label_21192:
    decay0_nucltransK(prng_, event_, 1.509, 0.093, 6.3e-3, 6.5e-5, tclev, thlev, tdlev);
    goto label_60900;
  label_21193:
    decay0_nucltransK(prng_, event_, 0.741, 0.093, 3.1e-2, 0., tclev, thlev, tdlev);
    goto label_13780;
  label_21194:
    decay0_nucltransKLM(prng_, event_, 0.703, 0.093, 4.5e-2, 0.017, 7.6e-3, 0.004, 2.6e-3, 0., tclev, thlev, tdlev);
    goto label_14150;
  label_21195:
    decay0_nucltransKLM(prng_, event_, 0.389, 0.093, 2.1e-1, 0.017, 3.7e-2, 0.004, 1.2e-2, 0., tclev, thlev, tdlev);
    goto label_17300;
  label_2088:
    decay0_beta(prng_, event_, 1.181, 84., 0., 0., t);
  label_20880:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 40.5)
      goto label_20881; // 40.5%
    goto label_20882;   // 59.5%
  label_20881:
    decay0_nucltransK(prng_, event_, 1.479, 0.093, 9.0e-3, 5.7e-5, tclev, thlev, tdlev);
    goto label_60900;
  label_20882:
    decay0_nucltransK(prng_, event_, 0.711, 0.093, 6.0e-2, 0., tclev, thlev, tdlev);
    goto label_13780;
  label_2017:
    decay0_beta(prng_, event_, 1.253, 84., 0., 0., t);
  label_20170:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 0.27)
      goto label_20171; // 0.27%
    if (p <= 98.01)
      goto label_20172; // 97.74%
    if (p <= 99.41)
      goto label_20173; // 1.40%
    if (p <= 99.75)
      goto label_20174; // 0.34%
    goto label_20175;   // 0.25%
  label_20171:
    p = 100. * prng_();
    if (p <= 95.08) { // electron conversion
      decay0_electron(prng_, event_, 1.923, tclev, thlev, tdlev);
      decay0_gamma(prng_, event_, 0.093, 0., 0., tdlev);
    } else { // pair conversion
      decay0_pair(prng_, event_, 0.995, tclev, thlev, tdlev);
    }
    return;
  label_20172:
    decay0_nucltransKLM(prng_, event_, 1.408, 0.093, 3.1e-3, 0.017, 5.7e-4, 0.004, 1.9e-4, 5.7e-5, tclev, thlev, tdlev);
    goto label_60900;
  label_20173:
    decay0_nucltransKLM(prng_, event_, 0.640, 0.093, 1.4e-2, 0.017, 3.7e-3, 0.004, 1.2e-3, 0., tclev, thlev, tdlev);
    goto label_13780;
  label_20174:
    decay0_nucltransKLM(prng_, event_, 0.356, 0.093, 4.6e-2, 0.017, 2.4e-2, 0.004, 8.1e-3, 0., tclev, thlev, tdlev);
    goto label_16610;
  label_20175:
    decay0_nucltransKLM(prng_, event_, 0.253, 0.093, 6.9e-1, 0.017, 1.2e-1, 0.004, 3.8e-2, 0., tclev, thlev, tdlev);
    goto label_17640;
  label_2011:
    decay0_beta(prng_, event_, 1.259, 84., 0., 0., t);
  label_20110:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 3.4)
      goto label_20111; // 3.4%
    if (p <= 94.7)
      goto label_20112; // 91.3%
    if (p <= 98.7)
      goto label_20113; // 4.0%
    goto label_20114;   // 1.3%
  label_20111:
    decay0_nucltransK(prng_, event_, 2.011, 0.093, 2.2e-3, 3.2e-4, tclev, thlev, tdlev);
    return;
  label_20112:
    decay0_nucltransKLM(prng_, event_, 1.402, 0.093, 4.4e-3, 0.017, 7.7e-4, 0.004, 2.3e-4, 3.8e-5, tclev, thlev, tdlev);
    goto label_60900;
  label_20113:
    decay0_nucltransK(prng_, event_, 0.633, 0.093, 4.5e-2, 0., tclev, thlev, tdlev);
    goto label_13780;
  label_20114:
    decay0_nucltransK(prng_, event_, 0.595, 0.093, 5.3e-2, 0., tclev, thlev, tdlev);
    goto label_14150;
  label_1995:
    decay0_beta(prng_, event_, 1.275, 84., 0., 0., t);
  label_19950:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 60.3)
      goto label_19951; // 60.3%
    if (p <= 90.8)
      goto label_19952; // 30.5%
    if (p <= 93.5)
      goto label_19953; // 2.7%
    goto label_19954;   // 6.5%
  label_19951:
    decay0_nucltransKLM(prng_, event_, 1.385, 0.093, 1.3e-3, 0.017, 2.0e-4, 0.004, 6.4e-5, 1.8e-4, tclev, thlev, tdlev);
    goto label_60900;
  label_19952:
    decay0_nucltransKLM(prng_, event_, 0.720, 0.093, 1.1e-2, 0.017, 2.7e-3, 0.004, 9.3e-4, 0., tclev, thlev, tdlev);
    goto label_12750;
  label_19953:
    decay0_nucltransK(prng_, event_, 0.617, 0.093, 6.8e-3, 0., tclev, thlev, tdlev);
    goto label_13780;
  label_19954:
    decay0_nucltransKLM(prng_, event_, 0.333, 0.093, 2.0e-2, 0.017, 3.5e-3, 0.004, 1.1e-3, 0., tclev, thlev, tdlev);
    goto label_16610;
  label_1890:
    decay0_beta(prng_, event_, 1.380, 84., 0., 0., t);
    ////label_18900  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 5.0)
      goto label_18901; // 5.0%
    if (p <= 96.2)
      goto label_18902; // 91.2%
    goto label_18903;   // 3.8%
  label_18901:
    decay0_nucltransK(prng_, event_, 1.890, 0.093, 2.8e-3, 2.6e-4, tclev, thlev, tdlev);
    return;
  label_18902:
    decay0_nucltransKLM(prng_, event_, 1.281, 0.093, 9.5e-3, 0.017, 1.6e-3, 0.004, 5.5e-4, 1.6e-5, tclev, thlev, tdlev);
    goto label_60900;
  label_18903:
    decay0_nucltransKLM(prng_, event_, 0.616, 0.093, 5.6e-3, 0.017, 9.0e-4, 0.004, 3.0e-4, 0., tclev, thlev, tdlev);
    goto label_12750;
  label_1847:
    decay0_beta(prng_, event_, 1.423, 84., 0., 0., t);
  label_18470:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 25.7)
      goto label_18471; // 25.7%
    if (p <= 97.0)
      goto label_18472; // 71.3%
    if (p <= 97.3)
      goto label_18473; // 0.3%
    if (p <= 98.2)
      goto label_18474; // 0.9%
    goto label_18475;   // 1.8%
  label_18471:
    decay0_nucltransK(prng_, event_, 1.847, 0.093, 2.5e-3, 2.4e-4, tclev, thlev, tdlev);
    return;
  label_18472:
    decay0_nucltransKLM(prng_, event_, 1.238, 0.093, 1.0e-2, 0.017, 1.8e-3, 0.004, 5.5e-4, 1.0e-5, tclev, thlev, tdlev);
    goto label_60900;
  label_18473:
    decay0_nucltransKLM(prng_, event_, 0.832, 0.093, 8.2e-3, 0.017, 1.8e-3, 0.004, 6.4e-4, 0., tclev, thlev, tdlev);
    goto label_10150;
  label_18474:
    decay0_nucltransKLM(prng_, event_, 0.573, 0.093, 6.4e-3, 0.017, 1.1e-3, 0.004, 3.4e-4, 0., tclev, thlev, tdlev);
    goto label_12750;
  label_18475:
    decay0_nucltransKLM(prng_, event_, 0.470, 0.093, 8.0e-2, 0.017, 1.6e-2, 0.004, 5.1e-3, 0., tclev, thlev, tdlev);
    goto label_13780;
  label_1764:
    decay0_beta(prng_, event_, 1.505, 84., 0., 0., t);
  label_17640:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 87.61)
      goto label_17641; // 87.61%
    if (p <= 97.01)
      goto label_17642; // 9.40%
    if (p <= 99.06)
      goto label_17643; // 2.05%
    if (p <= 99.97)
      goto label_17644; // 0.91%
    goto label_17645;   // 0.03%
  label_17641:
    decay0_nucltransK(prng_, event_, 1.764, 0.093, 6.0e-3, 1.5e-4, tclev, thlev, tdlev);
    return;
  label_17642:
    decay0_nucltransKLM(prng_, event_, 1.155, 0.093, 1.2e-2, 0.017, 2.0e-3, 0.004, 6.3e-4, 2.8e-6, tclev, thlev, tdlev);
    goto label_60900;
  label_17643:
    decay0_nucltransKLM(prng_, event_, 0.387, 0.093, 1.3e-1, 0.017, 2.8e-2, 0.004, 8.9e-3, 0., tclev, thlev, tdlev);
    goto label_13780;
  label_17644:
    decay0_nucltransKLM(prng_, event_, 0.349, 0.093, 2.9e-1, 0.017, 5.0e-2, 0.004, 1.6e-2, 0., tclev, thlev, tdlev);
    goto label_14150;
  label_17645:
    decay0_nucltransKLM(prng_, event_, 0.221, 0.093, 5.6e-1, 0.017, 1.6e-1, 0.004, 5.4e-2, 0., tclev, thlev, tdlev);
    goto label_15430;
  label_1743:
    decay0_beta(prng_, event_, 1.527, 84., 0., 0., t);
  label_17430:
    thlev = 0.;
    decay0_nucltransKLM(prng_, event_, 1.134, 0.093, 4.7e-3, 0.017, 9.0e-4, 0.004, 2.9e-4, 2.8e-6, tclev, thlev, tdlev);
    goto label_60900;
  label_1730:
    decay0_beta(prng_, event_, 1.540, 84., 0., 0., t);
  label_17300:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 15.66)
      goto label_17301; // 15.66%
    if (p <= 97.92)
      goto label_17302; // 82.26%
    if (p <= 99.55)
      goto label_17303; // 1.63%
    goto label_17304;   // 0.45%
  label_17301:
    decay0_nucltransK(prng_, event_, 1.730, 0.093, 2.7e-3, 1.9e-4, tclev, thlev, tdlev);
    return;
  label_17302:
    decay0_nucltransKLM(prng_, event_, 1.120, 0.093, 1.3e-2, 0.017, 2.2e-3, 0.004, 6.7e-4, 1.2e-6, tclev, thlev, tdlev);
    goto label_60900;
  label_17303:
    decay0_nucltransKLM(prng_, event_, 0.455, 0.093, 1.0e-2, 0.017, 1.7e-3, 0.004, 5.3e-4, 0., tclev, thlev, tdlev);
    goto label_12750;
  label_17304:
    decay0_nucltransKLM(prng_, event_, 0.352, 0.093, 1.6e-1, 0.017, 3.7e-2, 0.004, 1.2e-2, 0., tclev, thlev, tdlev);
    goto label_13780;
  label_1713:
    decay0_beta(prng_, event_, 1.540, 84., 0., 0., t);
  label_17130:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 65.36)
      goto label_17131; // 65.36%
    goto label_17132;   // 34.64%
  label_17131:
    decay0_nucltransK(prng_, event_, 1.104, 0.093, 1.2e-2, 7.6e-7, tclev, thlev, tdlev);
    goto label_60900;
  label_17132:
    decay0_nucltransK(prng_, event_, 0.698, 0.093, 6.0e-2, 0., tclev, thlev, tdlev);
    goto label_10150;
  label_1661:
    decay0_beta(prng_, event_, 1.609, 84., 0., 0., t);
  label_16610:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 78.23)
      goto label_16611; // 78.23%
    goto label_16612;   // 21.77%
  label_16611:
    decay0_nucltransK(prng_, event_, 1.661, 0.093, 3.0e-3, 1.5e-4, tclev, thlev, tdlev);
    return;
  label_16612:
    decay0_nucltransK(prng_, event_, 1.052, 0.093, 1.5e-2, 0., tclev, thlev, tdlev);
    goto label_60900;
  label_1543:
    decay0_beta(prng_, event_, 1.727, 84., 0., 0., t);
  label_15430:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 6.00)
      goto label_15431; // 6.00%
    if (p <= 99.26)
      goto label_15432; // 93.26%
    if (p <= 99.38)
      goto label_15433; // 0.12%
    goto label_15434;   // 0.62%
  label_15431:
    decay0_nucltransK(prng_, event_, 1.543, 0.093, 2.7e-3, 1.1e-4, tclev, thlev, tdlev);
    return;
  label_15432:
    decay0_nucltransKLM(prng_, event_, 0.934, 0.093, 2.0e-2, 0.017, 3.5e-3, 0.004, 1.2e-3, 0., tclev, thlev, tdlev);
    goto label_60900;
  label_15433:
    decay0_nucltransKLM(prng_, event_, 0.528, 0.093, 2.0e-2, 0.017, 6.4e-3, 0.004, 2.1e-3, 0., tclev, thlev, tdlev);
    goto label_10150;
  label_15434:
    decay0_nucltransKLM(prng_, event_, 0.269, 0.093, 3.3e-2, 0.017, 5.8e-3, 0.004, 1.8e-3, 0., tclev, thlev, tdlev);
    goto label_12750;
  label_1415:
    decay0_beta(prng_, event_, 1.855, 84., 0., 0., t);
  label_14150:
    thlev = 99.e-12;
    p     = 100. * prng_();
    if (p <= 28.05)
      goto label_14151; // 28.05%
    goto label_14152;   // 71.95%
  label_14151:
    p = 100. * prng_();
    if (p <= 99.63) { // electron conversion
      decay0_electron(prng_, event_, 1.322, tclev, thlev, tdlev);
      decay0_gamma(prng_, event_, 0.093, 0., 0., tdlev);
    } else { // pair conversion
      decay0_pair(prng_, event_, 0.393, tclev, thlev, tdlev);
    }
    return;
  label_14152:
    decay0_nucltransKLM(prng_, event_, 0.806, 0.093, 8.7e-3, 0.017, 2.0e-3, 0.004, 6.6e-4, 0., tclev, thlev, tdlev);
    goto label_60900;
  label_1378:
    decay0_beta(prng_, event_, 1.892, 84., 0., 0., t);
  label_13780:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 44.47)
      goto label_13781; // 44.47%
    goto label_13782;   // 55.53%
  label_13781:
    decay0_nucltransKLM(prng_, event_, 1.378, 0.093, 3.3e-3, 0.017, 5.9e-4, 0.004, 2.0e-4, 4.8e-5, tclev, thlev, tdlev);
    return;
  label_13782:
    decay0_nucltransKLM(prng_, event_, 0.768, 0.093, 1.3e-2, 0.017, 2.7e-3, 0.004, 9.0e-4, 0., tclev, thlev, tdlev);
    goto label_60900;
  label_12750:
    thlev = 0.;
    decay0_nucltransKLM(prng_, event_, 0.665, 0.093, 4.8e-3, 0.017, 7.7e-4, 0.004, 2.5e-4, 0., tclev, thlev, tdlev);
    goto label_60900;
  label_10150:
    thlev = 0.;
    decay0_nucltransKLM(prng_, event_, 0.406, 0.093, 3.5e-2, 0.017, 1.5e-2, 0.004, 5.1e-3, 0., tclev, thlev, tdlev);
    goto label_60900;
  label_609:
    decay0_beta(prng_, event_, 2.661, 84., 0., 0., t);
  label_60900:
    thlev = 0.;
    decay0_nucltransKLM(prng_, event_, 0.609, 0.093, 1.5e-2, 0.017, 4.2e-3, 0.004, 1.4e-3, 0., tclev, thlev, tdlev);
    return;
  label_20001:
    decay0_beta(prng_, event_, 3.270, 84., 0., 0., t);
    return;
  }
  // end of Bi214.f

} // end of namespace bxdecay0

// end of Bi214.cc
// Local Variables: --
// mode: c++ --
// End: --
