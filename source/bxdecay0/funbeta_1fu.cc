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
#include <bxdecay0/funbeta_1fu.h>

// Standard library:
#include <iostream>
#include <cmath>
#include <stdexcept>

// Third party:
// - GSL:
#include <gsl/gsl_math.h>

// This project:
#include <bxdecay0/fermi.h>
#include <bxdecay0/particle.h>
#include <bxdecay0/plog69.h>
#include <bxdecay0/divdif.h>

namespace bxdecay0 {

    double decay0_funbeta_1fu(double e_, void * params_)
    {
      const bj69sl2 * pars = static_cast<const bj69sl2 *>(params_);
      const double & Zdtr = pars->Zdtr;
      const double & Qbeta = pars->Qbeta;
      const double & c1 = pars->c1;
      const double & c2 = pars->c2;
      const double & c3 = pars->c3;
      const double & c4 = pars->c4;
      const double * sl2 = pars->sl2;

      static const double emass = decay0_emass();
      double f = 0.0;
      if (e_ > 0.) {
        // allowed spectrum
        double all =
          std::sqrt(e_ * (e_ + 2. * emass)) * (e_ + emass)
          * gsl_pow_2(Qbeta - e_) * decay0_fermi(Zdtr, e_);
        // correction factor 1 (theoretical)
        double w = e_ / emass + 1.;
        double pel = std::sqrt(w * w - 1.);
        double pnu = (Qbeta - e_) / emass;
        // calculation of the screened lambda2 value by interpolation of the table
        // with the help of the divdif CERN function for logarithms of p
        double pellog = std::log(pel) ;
        double scrl2 = decay0_divdif(sl2, BJ69::plog69, 48, pellog, 2);
        double cf1 = gsl_pow_2(pnu) + scrl2 * gsl_pow_2(pel);
        // correction factor 2 (empirical)
        double cf2 = 1.
          + c1 / w
          + c2 * w
          + c3 * gsl_pow_2(w)
          + c4 * gsl_pow_3(w);
        // spectrum with correction
        f = all * cf1 * cf2;
      }
      return f;
    }

} // end of namespace bxdecay0
