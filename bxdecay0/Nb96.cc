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
#include <bxdecay0/Nb96.h>

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

  void Nb96(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_)
  {
    double t;
    double tdlev;
    double p;
    double pbeta;
    double tclev;
    double thlev;
    double thnuc;
    // Scheme of Nb96 decay (NDS 68(1993)165 and ENSDF at NNDC site on 13.11.2007).
    // Three-figured labels correspond to energies of 96Mo excited
    // levels in keV.
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 7.05.1998
    thnuc  = 8.406e4;
    tdnuc_ = tcnuc_ - thnuc / std::log(2.) * std::log(prng_());
    tclev  = 0.;
    pbeta  = 100. * prng_();
    if (pbeta <= 0.024)
      goto label_2975;
    if (pbeta <= 0.524)
      goto label_2876;
    if (pbeta <= 1.014)
      goto label_2755;
    if (pbeta <= 3.314)
      goto label_2441;
    goto label_2439;
  label_2975:
    decay0_beta(prng_, event_, 0.212, 42., 0., 0., t);
    ////    label_29750  :
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 1.347, 0.020, 4.3e-4, 0.3e-4, tclev, thlev, tdlev);
    goto label_16280;
  label_2876:
    decay0_beta(prng_, event_, 0.311, 42., 0., 0., t);
    ////    label_28760  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 93.26)
      goto label_28761;
    goto label_28762;
  label_28761:
    decay0_nucltransK(prng_, event_, 0.435, 0.020, 5.4e-3, 0., tclev, thlev, tdlev);
    goto label_24410;
  label_28762:
    decay0_nucltransK(prng_, event_, 0.120, 0.020, 1.5e-1, 0., tclev, thlev, tdlev);
    goto label_27550;
  label_2755:
    decay0_beta(prng_, event_, 0.432, 42., 0., 0., t);
  label_27550:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 75.63)
      goto label_27551;
    if (p <= 86.64)
      goto label_27552;
    goto label_27553;
  label_27551:
    decay0_nucltransK(prng_, event_, 1.127, 0.020, 5.2e-4, 0.1e-5, tclev, thlev, tdlev);
    goto label_16280;
  label_27552:
    decay0_nucltransK(prng_, event_, 0.316, 0.020, 1.2e-2, 0., tclev, thlev, tdlev);
    goto label_24390;
  label_27553:
    decay0_nucltransKLM(prng_, event_, 0.314, 0.020, 1.1e-2, 0.003, 1.3e-3, 0.001, 4.2e-4, 0., tclev, thlev, tdlev);
    goto label_24410;
  label_2441:
    decay0_beta(prng_, event_, 0.746, 42., 0., 0., t);
  label_24410:
    thlev = 0.;
    decay0_nucltransK(prng_, event_, 0.813, 0.020, 1.3e-3, 0., tclev, thlev, tdlev);
    goto label_16280;
  label_2439:
    decay0_beta(prng_, event_, 0.748, 42., 0., 0., t);
  label_24390:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 11.20)
      goto label_24391;
    if (p <= 69.87)
      goto label_24392;
    if (p <= 96.89)
      goto label_24393;
    goto label_24394;
  label_24391:
    decay0_nucltransKLM(prng_, event_, 0.811, 0.020, 1.1e-3, 0.003, 1.3e-4, 0.001, 2.2e-5, 0., tclev, thlev, tdlev);
    goto label_16280;
  label_24392:
    decay0_nucltransKLM(prng_, event_, 0.569, 0.020, 2.6e-3, 0.003, 2.8e-4, 0.001, 5.8e-5, 0., tclev, thlev, tdlev);
    goto label_18700;
  label_24393:
    decay0_nucltransKLM(prng_, event_, 0.460, 0.020, 5.3e-3, 0.003, 6.4e-4, 0.001, 1.3e-4, 0., tclev, thlev, tdlev);
    goto label_19780;
  label_24394:
    decay0_nucltransKLM(prng_, event_, 0.219, 0.020, 3.2e-2, 0.003, 4.0e-3, 0.001, 1.4e-3, 0., tclev, thlev, tdlev);
    goto label_22190;
  label_22190:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 11.19)
      goto label_22191;
    if (p <= 36.94)
      goto label_22192;
    if (p <= 44.75)
      goto label_22193;
    if (p <= 68.44)
      goto label_22194;
    if (p <= 80.66)
      goto label_22195;
    goto label_22196;
  label_22191:
    decay0_nucltransK(prng_, event_, 1.441, 0.020, 4.3e-4, 0.5e-4, tclev, thlev, tdlev);
    goto label_77800;
  label_22192:
    decay0_nucltransKLM(prng_, event_, 0.722, 0.020, 1.5e-3, 0.003, 1.7e-4, 0.001, 3.6e-5, 0., tclev, thlev, tdlev);
    goto label_14980;
  label_22193:
    decay0_nucltransKLM(prng_, event_, 0.593, 0.020, 2.3e-3, 0.003, 2.6e-4, 0.001, 5.2e-5, 0., tclev, thlev, tdlev);
    goto label_16260;
  label_22194:
    decay0_nucltransKLM(prng_, event_, 0.591, 0.020, 2.4e-3, 0.003, 2.8e-4, 0.001, 4.9e-5, 0., tclev, thlev, tdlev);
    goto label_16280;
  label_22195:
    decay0_nucltransKLM(prng_, event_, 0.350, 0.020, 1.0e-2, 0.003, 1.2e-3, 0.001, 5.0e-4, 0., tclev, thlev, tdlev);
    goto label_18700;
  label_22196:
    decay0_nucltransKLM(prng_, event_, 0.241, 0.020, 2.1e-2, 0.003, 2.4e-3, 0.001, 4.9e-4, 0., tclev, thlev, tdlev);
    goto label_19780;
  label_19780:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 71.90)
      goto label_19781;
    if (p <= 92.93)
      goto label_19782;
    if (p <= 95.95)
      goto label_19783;
    if (p <= 99.81)
      goto label_19784;
    goto label_19785;
  label_19781:
    decay0_nucltransK(prng_, event_, 1.200, 0.020, 4.6e-4, 7.7e-6, tclev, thlev, tdlev);
    goto label_77800;
  label_19782:
    decay0_nucltransK(prng_, event_, 0.481, 0.020, 4.5e-3, 0., tclev, thlev, tdlev);
    goto label_14980;
  label_19783:
    decay0_nucltransKLM(prng_, event_, 0.353, 0.020, 1.0e-2, 0.003, 1.2e-3, 0.001, 7.0e-4, 0., tclev, thlev, tdlev);
    goto label_16260;
  label_19784:
    decay0_nucltransKLM(prng_, event_, 0.350, 0.020, 1.0e-2, 0.003, 1.2e-3, 0.001, 5.0e-4, 0., tclev, thlev, tdlev);
    goto label_16280;
  label_19785:
    decay0_nucltransKLM(prng_, event_, 0.109, 0.020, 1.7e-1, 0.003, 2.0e-2, 0.001, 4.2e-3, 0., tclev, thlev, tdlev);
    goto label_18700;
  label_18700:
    thlev = 6.4e-12;
    p     = 100. * prng_();
    if (p <= 88.61)
      goto label_18701;
    if (p <= 93.45)
      goto label_18702;
    goto label_18703;
  label_18701:
    decay0_nucltransK(prng_, event_, 1.091, 0.020, 5.6e-4, 0., tclev, thlev, tdlev);
    goto label_77800;
  label_18702:
    decay0_nucltransKLM(prng_, event_, 0.372, 0.020, 1.0e-2, 0.003, 1.3e-3, 0.001, 4.3e-4, 0., tclev, thlev, tdlev);
    goto label_14980;
  label_18703:
    decay0_nucltransKLM(prng_, event_, 0.241, 0.020, 2.1e-2, 0.003, 2.4e-3, 0.001, 7.8e-4, 0., tclev, thlev, tdlev);
    goto label_16280;
  label_16280:
    thlev = 1.2e-12;
    decay0_nucltransKLM(prng_, event_, 0.850, 0.020, 1.0e-3, 0.003, 1.1e-4, 0.001, 2.3e-5, 0., tclev, thlev, tdlev);
    goto label_77800;
  label_16260:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 11.72)
      goto label_16261;
    if (p <= 98.63)
      goto label_16262;
    goto label_16263;
  label_16261:
    decay0_nucltransK(prng_, event_, 1.626, 0.020, 2.8e-4, 1.3e-4, tclev, thlev, tdlev);
    return;
  label_16262:
    decay0_nucltransKLM(prng_, event_, 0.848, 0.020, 1.0e-3, 0.003, 1.1e-4, 0.001, 2.3e-5, 0., tclev, thlev, tdlev);
    goto label_77800;
  label_16263:
    decay0_nucltransKLM(prng_, event_, 0.128, 0.020, 1.1e-1, 0.003, 1.3e-2, 0.001, 2.7e-3, 0., tclev, thlev, tdlev);
    goto label_14980;
  label_14980:
    thlev = 0.78e-12;
    p     = 100. * prng_();
    if (p <= 32.43)
      goto label_14981;
    goto label_14982;
  label_14981:
    decay0_nucltransK(prng_, event_, 1.498, 0.020, 3.3e-4, 0.8e-4, tclev, thlev, tdlev);
    return;
  label_14982:
    decay0_nucltransKLM(prng_, event_, 0.720, 0.020, 1.5e-3, 0.003, 1.7e-4, 0.001, 3.5e-5, 0., tclev, thlev, tdlev);
    goto label_77800;
  label_77800:
    thlev = 3.67e-12;
    decay0_nucltransKLM(prng_, event_, 0.778, 0.020, 1.2e-3, 0.003, 1.4e-3, 0.001, 2.9e-5, 0., tclev, thlev, tdlev);
    return;
  }
  // end of Nb96.f

} // end of namespace bxdecay0

// end of Nb96.cc
// Local Variables: --
// mode: c++ --
// End: --
