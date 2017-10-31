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
#include <bxdecay0/funbeta1.h>

// Standard library:
#include <iostream>
#include <cmath>
#include <stdexcept>

// Third party:
// - GSL:
#include <gsl/gsl_math.h>

// This project:
#include <bxdecay0/fermi.h>
#include <bxdecay0/particle_utils.h>

namespace bxdecay0 {

  /// \brief Function to search the maximum of beta spectrum curve by decay0_tgold subroutine
  double decay0_funbeta1(double e_, void * params_)
  {
    const parbeta1 * pars = static_cast<const parbeta1 *>(params_);
    const double & Zdtr   = pars->Zdtr;
    const double & Qbeta  = pars->Qbeta;
    const double & c1     = pars->c1;
    const double & c2     = pars->c2;
    const double & c3     = pars->c3;
    const double & c4     = pars->c4;

    static const double emass = decay0_emass();
    double f = 0.0;
    if (e_ > 0.) {
      // allowed spectrum:
      double all = std::sqrt(e_ * (e_ + 2. * emass)) * (e_ + emass)
        *gsl_pow_2(Qbeta - e_) * decay0_fermi(Zdtr, e_);
      // correction factor:
      double w = e_ / emass + 1.;
      double cf = 1.
        + c1 / w
        + c2 * w
        + c3 * gsl_pow_2(w)
        + c4 * gsl_pow_3(w);
      // spectrum with correction:
      f = all * cf;
    }
    return f;
  }

} // end of namespace bxdecay0
