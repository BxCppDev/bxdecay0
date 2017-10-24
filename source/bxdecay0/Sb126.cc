// Ourselves:
#include <bxdecay0/Sb126.h>

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

  // Sb126.f
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

  void Sb126(i_random & prng_,
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
    // Scheme of 126Sb decay (J.Katakura et al., NDS 97(2002)765).
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 27.11.2003. Corrected 2.12.2003, thanks F.Capella.
    thnuc=1.0670e6;
    tdnuc_=tcnuc_-thnuc/std::log(2.)*std::log(prng_());
    tclev=0.;
    pbeta=100.*prng_();
    if (pbeta <=  0.48) goto label_3473;
    if (pbeta <=  2.48) goto label_3450;
    if (pbeta <= 30.28) goto label_3194;
    if (pbeta <= 35.94) goto label_3171;
    if (pbeta <= 43.99) goto label_3071;
    if (pbeta <= 48.02) goto label_2989;
    if (pbeta <= 48.50) goto label_2974;
    if (pbeta <= 49.27) goto label_2840;
    if (pbeta <= 57.04) goto label_2812;
    if (pbeta <= 61.74) goto label_2766;
    if (pbeta <= 77.08) goto label_2497;
    if (pbeta <= 77.94) goto label_2396;
    if (pbeta <= 80.82) goto label_2218;
    goto label_1776;
  label_3473  :
    decay0_beta(prng_, event_, 0.200,52.,0.,0.,t);
    ////    label_34730  :
    thlev=0.;
    decay0_nucltransK(prng_, event_, 0.958,0.032,1.5e-3,0.,tclev,thlev,tdlev);
    goto label_25150;
  label_3450  :
    decay0_beta(prng_, event_, 0.223,52.,0.,0.,t);
    ////    label_34500  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 57.14) goto label_34501;
    goto label_34502;
  label_34501  :
    decay0_nucltransK(prng_, event_, 0.954,0.032,1.5e-3,0.,tclev,thlev,tdlev);
    goto label_24970;
  label_34502  :
    decay0_nucltransK(prng_, event_, 0.639,0.032,3.6e-3,0.,tclev,thlev,tdlev);
    goto label_28120;
  label_3194  :
    decay0_beta(prng_, event_, 0.479,52.,0.,0.,t);
    ////   label_31940  :
    thlev=0.;
    decay0_nucltransK(prng_, event_, 0.697,0.032,3.0e-3,0.,tclev,thlev,tdlev);
    goto label_24970;
  label_3171  :
    decay0_beta(prng_, event_, 0.502,52.,0.,0.,t);
    ////    label_31710  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 62.82) goto label_31711;
    goto label_31712;
  label_31711  :
    decay0_nucltransK(prng_, event_, 0.675,0.032,3.2e-3,0.,tclev,thlev,tdlev);
    goto label_24970;
  label_31712  :
    decay0_nucltransK(prng_, event_, 0.656,0.032,3.4e-3,0.,tclev,thlev,tdlev);
    goto label_25150;
  label_3071  :
    decay0_beta(prng_, event_, 0.602,52.,0.,0.,t);
    ////    label_30710  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 79.86) goto label_30711;
    goto label_30712;
  label_30711  :
    decay0_nucltransK(prng_, event_, 0.574,0.032,5.0e-3,0.,tclev,thlev,tdlev);
    goto label_24970;
  label_30712  :
    decay0_nucltransK(prng_, event_, 0.556,0.032,5.0e-3,0.,tclev,thlev,tdlev);
    goto label_25150;
  label_2989  :
    decay0_beta(prng_, event_, 0.684,52.,0.,0.,t);
    ////    label_29890  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 57.18) goto label_29891;
    if (p <= 90.43) goto label_29892;
    goto label_29893;
  label_29891  :
    decay0_nucltransK(prng_, event_, 1.213,0.032,1.0e-3,0.1e-4,tclev,thlev,tdlev);
    goto label_17760;
  label_29892  :
    decay0_nucltransK(prng_, event_, 0.224,0.032,9.0e-2,0.,tclev,thlev,tdlev);
    goto label_27660;
  label_29893  :
    decay0_nucltransK(prng_, event_, 0.149,0.032,4.0e-1,0.,tclev,thlev,tdlev);
    goto label_28400;
  label_2974  :
    decay0_beta(prng_, event_, 0.699,52.,0.,0.,t);
    ////    label_29740  :
    thlev=0.;
    decay0_nucltransK(prng_, event_, 0.209,0.032,1.3e-1,0.,tclev,thlev,tdlev);
    goto label_27660;
  label_2840  :
    decay0_beta(prng_, event_, 0.833,52.,0.,0.,t);
  label_28400  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 23.73) goto label_28401;
    goto label_28402;
  label_28401  :
    decay0_nucltransK(prng_, event_, 1.477,0.032,4.0e-4,0.3e-4,tclev,thlev,tdlev);
    goto label_13620;
  label_28402  :
    decay0_nucltransK(prng_, event_, 1.064,0.032,1.2e-3,0.,tclev,thlev,tdlev);
    goto label_17760;
  label_2812  :
    decay0_beta(prng_, event_, 0.861,52.,0.,0.,t);
  label_28120  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 83.33) goto label_28121;
    if (p <= 94.44) goto label_28122;
    goto label_28123;
  label_28121  :
    decay0_nucltransK(prng_, event_, 0.593,0.032,5.0e-3,0.,tclev,thlev,tdlev);
    goto label_22180;
  label_28122  :
    decay0_nucltransK(prng_, event_, 0.415,0.032,1.2e-2,0.,tclev,thlev,tdlev);
    goto label_23960;
  label_28123  :
    decay0_nucltransK(prng_, event_, 0.297,0.032,3.0e-2,0.,tclev,thlev,tdlev);
    goto label_25150;
  label_2766  :
    decay0_beta(prng_, event_, 0.907,52.,0.,0.,t);
  label_27660  :
    thlev=0.;
    decay0_nucltransK(prng_, event_, 0.990,0.032,1.5e-3,0.,tclev,thlev,tdlev);
    goto label_17760;
  label_25150  :
    thlev=0.;
    decay0_nucltransK(prng_, event_, 0.297,0.032,4.0e-2,0.,tclev,thlev,tdlev);
    goto label_22180;
  label_2497  :
    decay0_beta(prng_, event_, 1.176,52.,0.,0.,t);
  label_24970  :
    thlev=0.152e-9;
    p=100.*prng_();
    if (p <= 95.56) goto label_24971;
    goto label_24972;
  label_24971  :
    decay0_nucltransK(prng_, event_, 0.721,0.032,1.0e-2,0.,tclev,thlev,tdlev);
    goto label_17760;
  label_24972  :
    decay0_nucltransK(prng_, event_, 0.278,0.032,4.9e-2,0.,tclev,thlev,tdlev);
    goto label_22180;
  label_2396  :
    decay0_beta(prng_, event_, 1.277,52.,0.,0.,t);
  label_23960  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 52.63) goto label_23961;
    goto label_23962;
  label_23961  :
    decay0_nucltransK(prng_, event_, 1.036,0.032,1.3e-3,0.,tclev,thlev,tdlev);
    goto label_13620;
  label_23962  :
    decay0_nucltransK(prng_, event_, 0.620,0.032,5.0e-3,0.,tclev,thlev,tdlev);
    goto label_17760;
  label_2218  :
    decay0_beta(prng_, event_, 1.455,52.,0.,0.,t);
  label_22180  :
    thlev=0.;
    decay0_nucltransK(prng_, event_, 0.857,0.032,8.4e-4,0.,tclev,thlev,tdlev);
    goto label_13620;
  label_1776  :
    decay0_beta(prng_, event_, 1.897,52.,0.,0.,t);
  label_17760  :
    thlev=68.e-12;
    decay0_nucltransK(prng_, event_, 0.415,0.032,1.4e-2,0.,tclev,thlev,tdlev);
    goto label_13620;
  label_13620  :
    thlev=0.;
    decay0_nucltransK(prng_, event_, 0.695,0.032,3.4e-3,0.,tclev,thlev,tdlev);
    goto label_66700;
  label_66700  :
    thlev=0.;
    decay0_nucltransK(prng_, event_, 0.667,0.032,3.8e-3,0.,tclev,thlev,tdlev);
    return;
  }
  // end of Sb126.f




} // end of namespace bxdecay0

// end of Sb126.cc
// Local Variables: --
// mode: c++ --
// End: --
