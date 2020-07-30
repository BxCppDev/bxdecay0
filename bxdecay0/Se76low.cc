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
#include <bxdecay0/Se76low.h>

// Standard library:
#include <cmath>
#include <sstream>
#include <stdexcept>

// Third party:
#include <gsl/gsl_math.h>

// This project:
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

  void Se76low(i_random & prng_, event & event_, const int levelkev_)
  {
    // static const double pi = M_PI;
    static const double twopi = 2 * M_PI;
    // double t;
    double tdlev;
    double cg;
    double cK;
    // double ctet;
    double EbindK;
    double Egamma;
    double p;
    double tclev;
    double thlev;
    particle * ipg563 = nullptr;
    particle * ipg559 = nullptr;
    // Subroutine describes the deexcitation process in Se76 nucleus
    // after 2b-decay of Ge76 to ground and excited 0+ and 2+ levels
    // of Se76 ("Table of Isotopes", 7th ed., 1978).
    // Call : call Se76low(levelkev_)
    // Input : levelkev_ - energy of Se76 level (integer in keV) occupied
    // initially
    // 0+(gs) - 0 keV,
    // 2+(1) - 559 keV,
    // 0+(1) - 1122 keV,
    // 2+(2) - 1216 keV.
    // Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
    // VIT, 19.07.1993, 22.10.1995.
    // Luciano Pandola, 25.10.2006: angular correlation of 563 and 559 keV gamma
    // quanta if 1122 keV level is populated.
    tclev = 0.;
    if (levelkev_ == 1216) {
      goto label_1216;
    }
    if (levelkev_ == 1122) {
      goto label_1122;
    }
    if (levelkev_ == 559) {
      goto label_559;
    }
    if (levelkev_ == 0) {
      goto label_10000;
    }
    goto label_20000;
  label_1216:
    thlev = 3.4e-12;
    p     = 100. * prng_();
    if (p <= 36.) {
      goto label_12161;
    }
    goto label_12162;
  label_12161:
    decay0_nucltransK(prng_, event_, 1.216, 0.013, 4.3e-4, 0.1e-4, tclev, thlev, tdlev);
    return;
  label_12162:
    decay0_nucltransK(prng_, event_, 0.657, 0.013, 2.1e-3, 0., tclev, thlev, tdlev);
    goto label_559;
  label_1122:
    thlev = 11.e-12;
    // decay0_nucltransK(prng_, event_, 0.563,0.013,2.0e-3,0.,tclev,thlev,tdlev)
    Egamma = 0.563;
    EbindK = 0.013;
    cg     = 1.;
    cK     = 2.0e-3;
    p      = prng_() * (cg + cK);
    if (p <= cg) { /* CARE */
      decay0_gamma(prng_, event_, Egamma, tclev, thlev, tdlev);
      ipg563 = &event_.grab_last_particle();
      /* CARE */
    } else {
      decay0_electron(prng_, event_, Egamma - EbindK, tclev, thlev, tdlev);
      decay0_gamma(prng_, event_, EbindK, 0., 0., tdlev);
    } /* CARE */;
    goto label_559;
  label_559:
    thlev = 12.3e-12;
    // decay0_nucltransK(prng_, event_, 0.559,0.013,2.0e-3,0.,tclev,thlev,tdlev)
    Egamma = 0.559;
    EbindK = 0.013;
    cg     = 1.;
    cK     = 2.0e-3;
    p      = prng_() * (cg + cK);
    if (p <= cg) {
      decay0_gamma(prng_, event_, Egamma, tclev, thlev, tdlev);
      ipg559 = &event_.grab_last_particle();
    } else {
      decay0_electron(prng_, event_, Egamma - EbindK, tclev, thlev, tdlev);
      decay0_gamma(prng_, event_, EbindK, 0., 0., tdlev);
    } /* CARE */
    // Angular correlation between gammas 559 and 563 keV, L.Pandola + VIT
    if (ipg559 != nullptr && ipg563 != nullptr) {
      double p559 = ipg559->get_p();
      double p563 = ipg563->get_p();
      // Coefficients in formula 1+a2*ctet**2+a4*ctet**4 are from:
      // R.D.Evans, "The Atomic Nucleus", Krieger Publ. Comp., 1985, p. 240,
      // 0(2)2(2)0 cascade.
      double a2 = -3.0;
      double a4 = 4.0;
      // Rejection method :
      double phi1, ctet1, stet1;
      double phi2, ctet2, stet2;
      double ctet;
    label_1:
      phi1  = twopi * prng_();
      ctet1 = 1. - 2. * prng_();
      stet1 = std::sqrt(1. - ctet1 * ctet1);
      phi2  = twopi * prng_();
      ctet2 = 1. - 2. * prng_();
      stet2 = std::sqrt(1. - ctet2 * ctet2);
      ctet  = ctet1 * ctet2 + stet1 * stet2 * cos(phi1 - phi2);
      if (prng_() * (1. + std::abs(a2) + std::abs(a4)) > 1. + a2 * gsl_pow_2(ctet) + a4 * gsl_pow_4(ctet)) {
        goto label_1;
      }
      ipg559->set_momentum(p559 * stet1 * cos(phi1), p559 * stet1 * sin(phi1), p559 * ctet1);
      ipg563->set_momentum(p563 * stet2 * cos(phi2), p563 * stet2 * sin(phi2), p563 * ctet2);
    }
    return;
  label_10000:
    return;
  label_20000 : {
    std::ostringstream message;
    message << "genbb::decay0::Se76low: Wrong energy level El=" << levelkev_ << " [keV] !";
    throw std::logic_error(message.str());
  }
    return;
  }

} // end of namespace bxdecay0

// end of Se76low.cc
// Local Variables: --
// mode: c++ --
// End: --
