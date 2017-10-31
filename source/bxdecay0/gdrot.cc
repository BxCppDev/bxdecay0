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
#include <bxdecay0/gdrot.h>

// Standard library:
#include <cmath>

namespace bxdecay0 {

  void decay0_gdrot(double * p_,
                    const double costh_, const double sinth_,
                    const double cosph_, const double sinph_)
  {
    double p1 = p_[0];
    double p2 = p_[1];
    double p3 = p_[2];
    p_[0] =  p1*costh_*cosph_ - p2*sinph_ + p3*sinth_*cosph_;
    p_[1] =  p1*costh_*sinph_ + p2*cosph_ + p3*sinth_*sinph_;
    p_[2] = -p1*sinth_                    + p3*costh_;
    return;
  }

} // end of namespace bxdecay0
