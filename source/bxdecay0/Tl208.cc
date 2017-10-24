// Ourselves:
#include <bxdecay0/Tl208.h>

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

  // Tl208.f
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

  void Tl208(i_random & prng_,
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
    // Scheme of Tl208 decay ("Table of Isotopes", 7th ed., 1978).
    // Four-figured labels correspond to energies of 208Pb excited
    // levels in keV.
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 27.07.1992, 22.10.1995.
    // VIT, 11.05.2005, updated to NDS 47(1986)797 (last NDS issue for A=208).
    // VIT, 4.02.2009, updated to NDS 108(2007)1583
    // LM conversion electrons
    thnuc=183.18;
    tdnuc_=tcnuc_-thnuc/std::log(2.)*std::log(prng_());
    tclev=0.;
    pbeta=100.*prng_();
    if (pbeta <=  0.052) goto label_4481;  // 0.052%
    if (pbeta <=  0.069) goto label_4383;  // 0.017%
    if (pbeta <=  0.113) goto label_4358;  // 0.044%
    if (pbeta <=  0.118) goto label_4323;  // 0.005%
    if (pbeta <=  0.219) goto label_4296;  // 0.101%
    if (pbeta <=  0.221) goto label_4262;  // 0.002%
    if (pbeta <=  0.448) goto label_4180;  // 0.227%
    if (pbeta <=  0.623) goto label_4125;  // 0.175%
    if (pbeta <=  0.630) goto label_3996;  // 0.007%
    if (pbeta <=  3.810) goto label_3961;  // 3.180%
    if (pbeta <=  3.856) goto label_3946;  // 0.046%
    if (pbeta <=  4.486) goto label_3920;  // 0.630%
    if (pbeta <= 28.686) goto label_3708;  // 24.200%
    if (pbeta <= 50.886) goto label_3475;  // 22.200%
    goto label_3198;  // 49.114%
  label_4481  :
    decay0_beta(prng_, event_, 0.518,82.,0.,0.,t);
    thlev=0.;
    decay0_nucltransKLM_Pb(prng_, event_, 1.283,0.088,7.75e-3,0.015,1.27e-3,
                           0.004,0.41e-3,2.3e-5,tclev,thlev,tdlev);
    goto label_31980;
  label_4383  :
    decay0_beta(prng_, event_, 0.616,82.,0.,0.,t);
    thlev=0.;
    // decay0_nucltransK(prng_, event_, 1.185,0.088,1.1e-2,0.3e-4,tclev,thlev,tdlev)
    decay0_nucltransKLM_Pb(prng_, event_, 1.185,0.088,9.49e-3,0.015,1.56e-3,
                           0.004,0.47e-3,4.9e-6,tclev,thlev,tdlev);
    goto label_31980;
  label_4358  :
    decay0_beta(prng_, event_, 0.641,82.,0.,0.,t);
    thlev=0.;
    p=100.*prng_();
    if (p <=  4.55) goto label_43581;  // 4.55%
    if (p <= 29.55) goto label_43582;  // 25.00%
    goto label_43583;  // 70.45%
  label_43581  :
    decay0_nucltransKLM_Pb(prng_, event_, 1.744,0.088,3.56e-3,0.015,0.58e-3,
                           0.004,0.17e-3,2.6e-4,tclev,thlev,tdlev);
    goto label_26150;
  label_43582  :
    decay0_nucltransKLM_Pb(prng_, event_, 1.161,0.088,9.99e-3,0.015,1.64e-3,
                           0.004,0.51e-3,2.6e-6,tclev,thlev,tdlev);
    goto label_31980;
  label_43583  :
    decay0_nucltransKLM_Pb(prng_, event_, 0.883,0.088,20.13e-3,0.015,3.33e-3,
                           0.004,1.02e-3,0.,tclev,thlev,tdlev);
    goto label_34750;
  label_4323  :
    decay0_beta(prng_, event_, 0.676,82.,0.,0.,t);
    thlev=0.;
    // decay0_nucltransK(prng_, event_, 1.126,0.088,1.1e-2,0.3e-4,tclev,thlev,tdlev)
    decay0_nucltransKLM_Pb(prng_, event_, 1.126,0.088,1.69e-3,0.015,0.26e-3,
                           0.004,0.08e-3,2.1e-6,tclev,thlev,tdlev);
    goto label_31980;
  label_4296  :
    decay0_beta(prng_, event_, 0.703,82.,0.,0.,t);
    thlev=0.;
    p=100.*prng_();
    if (p <= 87.23) goto label_42961;  // 87.23%
    goto label_42962;  // 12.77%
  label_42961  :
    decay0_nucltransKLM_Pb(prng_, event_, 0.821,0.088,2.43e-2,0.015,0.40e-2,
                           0.004,0.12e-2,0.,tclev,thlev,tdlev);
    goto label_34750;
  label_42962  :
    decay0_nucltransKLM_Pb(prng_, event_, 0.588,0.088,5.78e-2,0.015,0.97e-2,
                           0.004,0.29e-2,0.,tclev,thlev,tdlev);
    goto label_37080;
  label_4262  :
    decay0_beta(prng_, event_, 0.737,82.,0.,0.,t);
    thlev=0.;
    // decay0_nucltransK(prng_, event_, 1.648,0.088,1.1e-2,0.3e-4,tclev,thlev,tdlev)
    decay0_nucltransKLM_Pb(prng_, event_, 1.648,0.088,4.11e-3,0.015,0.67e-3,
                           0.004,0.20e-3,0.19e-3,tclev,thlev,tdlev);
    goto label_26150;
  label_4180  :
    decay0_beta(prng_, event_, 0.819,82.,0.,0.,t);
    thlev=0.;
    p=100.*prng_();
    if (p <= 90.31) goto label_41801;  // 90.31%
    goto label_41802;  // 9.69%
  label_41801  :
    decay0_nucltransKLM_Pb(prng_, event_, 0.983,0.088,1.53e-2,0.015,0.25e-2,
                           0.004,0.08e-2,0.,tclev,thlev,tdlev);
    goto label_31980;
  label_41802  :
    decay0_nucltransKLM_Pb(prng_, event_, 0.705,0.088,3.60e-2,0.015,0.60e-2,
                           0.004,0.18e-2,0.,tclev,thlev,tdlev);
    goto label_34750;
  label_4125  :
    decay0_beta(prng_, event_, 0.874,82.,0.,0.,t);
    thlev=0.;
    p=100.*prng_();
    if (p <= 96.15) goto label_41251;  // 96.15%
    goto label_41252;  // 3.85%
  label_41251  :
    decay0_nucltransKLM_Pb(prng_, event_, 0.928,0.088,1.77e-2,0.015,0.29e-2,
                           0.004,0.10e-2,0.,tclev,thlev,tdlev);
    goto label_31980;
  label_41252  :
    decay0_nucltransKLM_Pb(prng_, event_, 0.650,0.088,4.45e-2,0.015,0.75e-2,
                           0.004,0.22e-2,0.,tclev,thlev,tdlev);
    goto label_34750;
  label_3996  :
    decay0_beta(prng_, event_, 1.003,82.,0.,0.,t);
    thlev=0.;
    // decay0_nucltransK(prng_, event_, 1.381,0.088,8.0e-3,0.6e-4,tclev,thlev,tdlev)
    decay0_nucltransKLM_Pb(prng_, event_, 1.381,0.088,6.43e-3,0.015,1.05e-3,
                           0.004,0.32e-3,0.05e-3,tclev,thlev,tdlev);
    goto label_26150;
  label_3961  :
    decay0_beta(prng_, event_, 1.038,82.,0.,0.,t);
    thlev=0.;
    p=100.*prng_();
    if (p <= 51.25) goto label_39611;  // 51.25%
    if (p <= 64.82) goto label_39612;  // 13.57%
    goto label_39613;  // 35.18%
  label_39611  :
    decay0_nucltransKLM_Pb(prng_, event_, 0.763,0.088,2.93e-2,0.015,0.49e-2,
                           0.004,0.14e-2,0.,tclev,thlev,tdlev);
    goto label_31980;
  label_39612  :
    decay0_nucltransKLM_Pb(prng_, event_, 0.486,0.088,9.54e-2,0.015,1.61e-2,
                           0.004,0.49e-2,0.,tclev,thlev,tdlev);
    goto label_34750;
  label_39613  :
    decay0_nucltransKLM_Pb(prng_, event_, 0.253,0.088,51.60e-2,0.015,8.83e-2,
                           0.004,2.57e-2,0.,tclev,thlev,tdlev);
    goto label_37080;
  label_3946  :
    decay0_beta(prng_, event_, 1.053,82.,0.,0.,t);
    thlev=0.;
    // decay0_nucltransK(prng_, event_, 0.749,0.088,3.5e-2,0.,tclev,thlev,tdlev)
    decay0_nucltransKLM_Pb(prng_, event_, 0.749,0.088,3.08e-2,0.015,0.51e-2,
                           0.004,0.16e-2,0.,tclev,thlev,tdlev);
    goto label_31980;
  label_3920  :
    decay0_beta(prng_, event_, 1.079,82.,0.,0.,t);
    thlev=0.;
    p=100.*prng_();
    if (p <= 39.49) goto label_39201;  // 39.49%
    goto label_39202;  // 60.51%
  label_39201  :
    decay0_nucltransKLM_Pb(prng_, event_, 0.722,0.088,3.20e-2,0.015,0.54e-2,
                           0.004,0.16e-2,0.,tclev,thlev,tdlev);
    goto label_31980;
  label_39202  :
    decay0_nucltransKLM_Pb(prng_, event_, 0.211,0.088,9.22e-1,0.015,1.59e-1,
                           0.004,0.45e-1,0.,tclev,thlev,tdlev);
    goto label_37080;
  label_3708  :
    decay0_beta(prng_, event_, 1.291,82.,0.,0.,t);
  label_37080  :
    thlev=0.;
    p=100.*prng_();
    if (p <=  1.66) goto label_37081;  // 1.66%
    if (p <= 97.95) goto label_37082;  // 96.29%
    goto label_37083;  // 2.05%
  label_37081  :
    decay0_nucltransKLM_Pb(prng_, event_, 1.094,0.088,4.49e-3,0.015,0.84e-3,
                           0.004,0.27e-3,0.,tclev,thlev,tdlev);
    goto label_26150;
  label_37082  :
    decay0_nucltransKLM_Pb(prng_, event_, 0.511,0.088,8.42e-2,0.015,1.42e-2,
                           0.004,0.43e-2,0.,tclev,thlev,tdlev);
    goto label_31980;
  label_37083  :
    decay0_nucltransKLM_Pb(prng_, event_, 0.233,0.088,5.47e-1,0.015,1.16e-1,
                           0.004,0.37e-1,0.,tclev,thlev,tdlev);
    goto label_34750;
  label_3475  :
    decay0_beta(prng_, event_, 1.524,82.,0.,0.,t);
  label_34750  :
    thlev=4.e-12;
    p=100.*prng_();
    if (p <= 55.95) goto label_34751;  // 55.95%
    goto label_34752;  // 44.05%
  label_34751  :
    decay0_nucltransKLM_Pb(prng_, event_, 0.861,0.088,2.17e-2,0.015,0.36e-2,
                           0.004,0.11e-2,0.,tclev,thlev,tdlev);
    goto label_26150;
  label_34752  :
    decay0_nucltransKLM_Pb(prng_, event_, 0.277,0.088,4.36e-1,0.015,0.75e-1,
                           0.004,0.22e-1,0.,tclev,thlev,tdlev);
    goto label_31980;
  label_3198  :
    decay0_beta(prng_, event_, 1.801,82.,0.,0.,t);
  label_31980  :
    thlev=294.e-12;
    // decay0_nucltransK(prng_, event_, 0.583,0.088,2.1e-2,0.,tclev,thlev,tdlev)
    decay0_nucltransKLM_Pb(prng_, event_, 0.583,0.088,1.51e-2,0.015,0.41e-2,
                           0.004,0.13e-2,0.,tclev,thlev,tdlev);
    goto label_26150;
  label_26150  :
    thlev=16.7e-12;
    // decay0_nucltransK(prng_, event_, 2.615,0.088,8.5e-3,4.3e-4,tclev,thlev,tdlev)
    // change in accordance with NNDC-ENSDF on 19.12.2006
    // decay0_nucltransK(prng_, event_, 2.615,0.088,2.47e-3,4.3e-4,tclev,thlev,tdlev)
    decay0_nucltransKLM_Pb(prng_, event_, 2.615,0.088,1.71e-3,0.015,0.29e-3,
                           0.004,0.10e-3,0.37e-3,tclev,thlev,tdlev);
    return;
  }
  // end of Tl208.f

} // end of namespace bxdecay0

// end of Tl208.cc
// Local Variables: --
// mode: c++ --
// End: --
