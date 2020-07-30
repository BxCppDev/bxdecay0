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
#include <bxdecay0/funbeta.h>

// Standard library:
#include <cmath>
#include <iostream>
#include <stdexcept>

// Third party:
// - GSL:
#include <gsl/gsl_math.h>

// This project:
#include <bxdecay0/fermi.h>
#include <bxdecay0/particle.h>

namespace bxdecay0 {

  /// \brief Function to search the maximum of beta spectrum curve by decay0_tgold subroutine.
  double decay0_funbeta(double E_, void * params_)
  {
    const parbeta * pars      = static_cast<const parbeta *>(params_);
    const double & Qbeta      = pars->Qbeta;
    const double & Zdtr       = pars->Zdtr;
    double f                  = 0.0;
    static const double emass = decay0_emass();
    if (E_ > 0.) {
      f = std::sqrt(E_ * (E_ + 2. * emass)) * (E_ + emass) * gsl_pow_2(Qbeta - E_) * decay0_fermi(Zdtr, E_);
    }
    return f;
  }

} // end of namespace bxdecay0
