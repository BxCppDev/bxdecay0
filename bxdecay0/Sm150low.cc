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
#include <bxdecay0/Sm150low.h>

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

  void Sm150low(i_random & prng_, event & event_, const int levelkev_)
  {
    // double t;
    double tdlev;
    double p;
    double tclev;
    double thlev;
    // Subroutine describes the deexcitation process in Sm150 nucleus
    // after 2b-decay of Nd150 to ground and excited 0+ and 2+ levels
    // of Sm150 ("Table of Isotopes", 7th ed., 1978).
    // Call : call Sm150low(levelkev_)
    // Input : levelkev_ - energy of Sm150 level (integer in keV) occupied
    // initially
    // 0+(gs) - 0 keV,
    // 2+(1) - 334 keV,
    // 0+(1) - 740 keV,
    // 2+(2) - 1046 keV,
    // 2+(3) - 1194 keV,
    // 0+(2) - 1256 keV.
    // Output: // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 28.06.1993, 22.10.1995; 23.09.2008;
    // VIT, 18.06.2018: angular correlation between 334 and 407 keV gammas in deexcitation
    // of 740 keV level;
    // VIT, 30.06.2018: update to NNDC and NDS 114(2013)435.
    int npg334 = -1;
    int npg407 = -1;
    double Egamma;
    double EbindK;
    double cg;
    double cK;
    tclev = 0.;
    if (levelkev_ == 1256) {
      goto label_1256;
    }
    if (levelkev_ == 1194) {
      goto label_1194;
    }
    if (levelkev_ == 1046) {
      goto label_1046;
    }
    if (levelkev_ == 740) {
      goto label_740;
    }
    if (levelkev_ == 334) {
      goto label_334;
    }
    if (levelkev_ == 0) {
      goto label_10000;
    }
    goto label_20000;
  label_1256:
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 8.44) {
      goto label_12561;
    }
    if (p <= 18.89) {
      goto label_12562;
    }
    if (p <= 99.28) {
      goto label_12563;
    }
    goto label_12564;
  label_12561:
    decay0_nucltransK(prng_, event_, 0.209, 0.047, 1.79e-1, 0., tclev, thlev, tdlev);
    goto label_1046;
  label_12562:
    // only ec in 0+ -> 0+
    decay0_electron(prng_, event_, 0.515 - 0.047, tclev, thlev, tdlev);
    decay0_gamma(prng_, event_, 0.047, 0., 0., tdlev);
    goto label_740;
  label_12563:
    decay0_nucltransK(prng_, event_, 0.922, 0.047, 3.0e-3, 0., tclev, thlev, tdlev);
    goto label_334;
  label_12564:
    // only ec in 0+ -> 0+
    decay0_electron(prng_, event_, 1.256 - 0.047, tclev, thlev, tdlev);
    decay0_gamma(prng_, event_, 0.047, 0., 0., tdlev);
    return;
  label_1194:
    thlev = 1.3e-12;
    p     = 100. * prng_();
    if (p <= 0.13) {
      goto label_11941;
    }
    if (p <= 1.14) {
      goto label_11942;
    }
    if (p <= 3.04) {
      goto label_11943;
    }
    if (p <= 44.05) {
      goto label_11944;
    }
    goto label_11945;
  label_11941:
    decay0_nucltransK(prng_, event_, 0.148, 0.047, 5.6e-1, 0., tclev, thlev, tdlev);
    goto label_1046;
  label_11942:
    decay0_nucltransK(prng_, event_, 0.420, 0.047, 2.1e-2, 0., tclev, thlev, tdlev);
    goto label_773;
  label_11943:
    decay0_nucltransK(prng_, event_, 0.453, 0.047, 1.7e-2, 0., tclev, thlev, tdlev);
    goto label_740;
  label_11944:
    decay0_nucltransK(prng_, event_, 0.860, 0.047, 4.5e-3, 0., tclev, thlev, tdlev);
    goto label_334;
  label_11945:
    decay0_nucltransK(prng_, event_, 1.194, 0.047, 1.7e-3, 5.1e-6, tclev, thlev, tdlev);
    return;
  label_1046:
    thlev = 0.86e-12;
    p     = 100. * prng_();
    if (p <= 2.26) {
      goto label_10461;
    }
    if (p <= 92.68) {
      goto label_10462;
    }
    goto label_10463;
  label_10461:
    decay0_nucltransK(prng_, event_, 0.306, 0.047, 5.3e-2, 0., tclev, thlev, tdlev);
    goto label_740;
  label_10462:
    decay0_nucltransK(prng_, event_, 0.712, 0.047, 7.1e-3, 0., tclev, thlev, tdlev);
    goto label_334;
  label_10463:
    decay0_nucltransK(prng_, event_, 1.046, 0.047, 2.3e-3, 0., tclev, thlev, tdlev);
    return;
  label_773:
    thlev = 6.5e-12;
    decay0_nucltransK(prng_, event_, 0.439, 0.047, 1.8e-2, 0., tclev, thlev, tdlev);
    goto label_334;
  label_740:
    thlev = 19.7e-12;
    p     = 100. * prng_();
    // the following line is corrected in accordance with ToI'1998 and Nucl.
    // Data Sheets 75(1995)827 (real page is 856)
    // VIT, 23.09.2008
    // if (p <= 92.) goto label_74001
    if (p <= 1.35) {
      goto label_74001;
    }
    goto label_74002;
  label_74001:
    // only ec in 0+ -> 0+
    decay0_electron(prng_, event_, 0.740 - 0.047, tclev, thlev, tdlev);
    decay0_gamma(prng_, event_, 0.047, 0., 0., tdlev);
    return;
  label_74002:
    Egamma = 0.407;
    EbindK = 0.047;
    cg     = 1.0;
    cK     = 2.3e-2;
    p      = prng_() * (cg + cK);
    if (p <= cg) {
      decay0_gamma(prng_, event_, Egamma, tclev, thlev, tdlev);
      npg407 = event_.get_particles().size() - 1;
    } else {
      decay0_electron(prng_, event_, Egamma - EbindK, tclev, thlev, tdlev);
      decay0_gamma(prng_, event_, EbindK, 0., 0., tdlev);
    }
    // decay0_nucltransK(prng_, event_, 0.407,0.047,2.0e-2,0.,tclev,thlev,tdlev);
    goto label_334;
  label_334:
    thlev  = 48.4e-12;
    Egamma = 0.334;
    EbindK = 0.047;
    cg     = 1.0;
    cK     = 4.1e-2;
    p      = prng_() * (cg + cK);
    if (p <= cg) {
      decay0_gamma(prng_, event_, Egamma, tclev, thlev, tdlev);
      npg334 = event_.get_particles().size() - 1;
    } else {
      decay0_electron(prng_, event_, Egamma - EbindK, tclev, thlev, tdlev);
      decay0_gamma(prng_, event_, EbindK, 0., 0., tdlev);
    }
    // Angular correlation between gammas 407 and 334 keV
    if (npg407 >= 0 && npg334 >= 0) {
      particle & g407 = event_.grab_particles()[npg407];
      particle & g334 = event_.grab_particles()[npg334];
      double p407     = g407.get_p();
      double p334     = g334.get_p();
      // Coefficients in formula 1+a2*ctet**2+a4*ctet**4 are from:
      // R.D.Evans, "The Atomic Nucleus", Krieger Publ. Comp., 1985, p. 240,
      // 0(2)2(2)0 cascade.
      double a2    = -3.0;
      double a4    = 4.0;
      double twopi = 2 * M_PI;
    label_1:
      double phi1     = twopi * prng_();
      double ctet1    = 1. - 2. * prng_();
      double stet1    = std::sqrt(1. - ctet1 * ctet1);
      double phi2     = twopi * prng_();
      double ctet2    = 1. - 2. * prng_();
      double stet2    = std::sqrt(1. - ctet2 * ctet2);
      double ctet     = ctet1 * ctet2 + stet1 * stet2 * std::cos(phi1 - phi2);
      double ctet_sqr = ctet * ctet;
      if (prng_() * (1. + abs(a2) + abs(a4)) > 1. + a2 * ctet_sqr + a4 * ctet_sqr * ctet_sqr) {
        goto label_1;
      }
      g407.set_px(p407 * stet1 * std::cos(phi1));
      g407.set_py(p407 * stet1 * std::sin(phi1));
      g407.set_pz(p407 * ctet1);
      g334.set_px(p334 * stet2 * std::cos(phi2));
      g334.set_py(p334 * stet2 * std::sin(phi2));
      g334.set_pz(p334 * ctet2);
    }
    return;
  label_10000:
    return;
  label_20000:
    // print *,'Sm150: wrong level [keV] ',levelkev_
    return;
  }
  // end of Sm150low.f

} // end of namespace bxdecay0

// end of Sm150low.cc
// Local Variables: --
// mode: c++ --
// End: --
