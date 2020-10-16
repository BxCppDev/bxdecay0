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
#include <bxdecay0/gfang.h>

// Standard library:
#include <cmath>

// Third party:
// - GSL:
#include <gsl/gsl_math.h>

namespace bxdecay0 {

  void decay0_gfang(const double * p_,
                    double & costh_,
                    double & sinth_,
                    double & cosph_,
                    double & sinph_,
                    bool & rotate_)
  {
    static const double one = 1.0;
    // additional (as compared with original GFANG) normalization
    double pfull = std::sqrt(gsl_pow_2(p_[0]) + gsl_pow_2(p_[1]) + gsl_pow_2(p_[2]));
    double dux   = p_[0] / pfull;
    double duy   = p_[1] / pfull;
    double duz   = p_[2] / pfull;
    rotate_      = true;
    if (std::abs(duz) >= 0.85) {
      double dsith2 = gsl_pow_2(dux) + gsl_pow_2(duy);
      if (dsith2 > 0.) {
        double sduz  = (duz > 0) ? one : -one;
        costh_       = sduz * std::sqrt(one - dsith2);
        double dsith = std::sqrt(dsith2);
        sinth_       = dsith;
        cosph_       = dux / dsith;
        sinph_       = duy / dsith;
      } else if (duz > 0.) {
        rotate_ = false;
        costh_  = 1.;
        sinth_  = 0.;
        cosph_  = 1.;
        sinph_  = 0.;
      } else {
        costh_ = -1.;
        sinth_ = 0.;
        cosph_ = 1.;
        sinph_ = 0.;
      }
    } else {
      costh_       = duz;
      double dsith = std::sqrt((one + duz) * (one - duz));
      sinth_       = dsith;
      double dnorm = one / std::sqrt(gsl_pow_2(dux) + gsl_pow_2(duy));
      cosph_       = dux * dnorm;
      sinph_       = duy * dnorm;
    }
    return;
  }

} // end of namespace bxdecay0
