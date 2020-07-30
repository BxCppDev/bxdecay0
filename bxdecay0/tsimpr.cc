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
#include <bxdecay0/tsimpr.h>

// Standard library:
#include <cstdint>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace bxdecay0 {

  double decay0_tsimpr2(func_type f_, double a_, double b_, double h_, void * params_)
  {
    int n     = (int)((b_ - a_) / h_) - 1;
    double fi = f_(a_, params_) - f_(b_, params_);
    double x1 = a_;
    double x2 = a_;
    int ni    = 1;
    do {
      x1 = x2 + h_;
      x2 = x1 + h_;
      fi = fi + 4. * f_(x1, params_) + 2. * f_(x2, params_);
      ni = ni + 2;
    } while (ni < n); // (ni <= n)
    return fi * h_ / 3.;
  }

  double decay0_tsimpr(func_type f_, double a_, double b_, double h_, void * params_)
  {
    double rn = (b_ - a_) / h_;
    rn += 0.25;
    std::size_t n = (std::size_t)rn;
    std::size_t m = n / 2;
    // std::cerr.precision(15);
    // std::cerr << "[debug] " << "rn = " << rn << std::endl;
    // std::cerr << "[debug] " << "n = " << n << std::endl;
    // std::cerr << "[debug] " << "m = " << m << std::endl;
    if (m % 2 != 0) {
      throw std::logic_error("bxdecay0::decay0_tsimpr2: Invalid integration step!");
    }
    double h = (b_ - a_) / (2 * m);
    double s = f_(a_, params_) + f_(b_, params_);
    for (std::size_t j = 1; j <= m - 1; j++) {
      double x2j = a_ + 2 * j * h;
      s += 2 * f_(x2j, params_);
    }
    for (std::size_t j = 1; j <= m; j++) {
      double x2jm1 = a_ + (2 * j - 1) * h;
      s += 4 * f_(x2jm1, params_);
    }
    return s * h / 3.;
  }

} // end of namespace bxdecay0
