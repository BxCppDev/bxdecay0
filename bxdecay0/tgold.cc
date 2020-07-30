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
#include <bxdecay0/tgold.h>

// Standard library:
#include <cmath>
#include <sstream>
#include <stdexcept>

namespace bxdecay0 {

  // From : http://en.wikipedia.org/wiki/Golden_section_search
  // a and c are the current bounds; the minimum is between them.
  // b is a center point
  // f(x,params) is some mathematical function elsewhere defined
  // a corresponds to x1; b corresponds to x2; c corresponds to x3
  // x corresponds to x4
  // minmax = 1 -> Search for minimum
  // minmax = 2 -> Search for maximum
  void decay0_tgold_o(double a_,
                      double b_,
                      double c_,
                      func_type f_,
                      double eps_,
                      int minmax_,
                      double & xextr_,
                      double & fextr_,
                      void * params_)
  {
    double sign = 1.0;
    if (minmax_ == 2) {
      sign = -1.0;
    }
    static double phi    = (1 + std::sqrt(5)) / 2;
    static double resphi = 2 - phi;
    double x;
    if (c_ - b_ > b_ - a_) {
      x = b_ + resphi * (c_ - b_);
    } else {
      x = b_ - resphi * (b_ - a_);
    }
    if (std::abs(c_ - a_) < eps_ * (std::abs(b_) + std::abs(x))) {
      xextr_ = (c_ + a_) / 2;
      fextr_ = f_(xextr_, params_);
      return;
    }
    if (f_(x, params_) == f_(b_, params_)) {
      std::ostringstream message;
      message << "genbb::decay0::decay0_tgold: "
              << "Invalid case : f(x,params_) == f(b,params_) !";
      throw std::logic_error(message.str());
    }
    if (sign * f_(x, params_) < sign * f_(b_, params_)) {
      if (c_ - b_ > b_ - a_) {
        decay0_tgold(b_, x, c_, f_, eps_, minmax_, xextr_, fextr_, params_);
        return;
      }
      decay0_tgold(a_, x, b_, f_, eps_, minmax_, xextr_, fextr_, params_);
      return;

    } else {
      if (c_ - b_ > b_ - a_) {
        decay0_tgold(a_, b_, x, f_, eps_, minmax_, xextr_, fextr_, params_);
        return;
      }
      decay0_tgold(x, b_, c_, f_, eps_, minmax_, xextr_, fextr_, params_);
      return;
    }
    return;
  }

  void decay0_tgold(double a_,
                    double /*b_*/,
                    double c_,
                    func_type f_,
                    double eps_,
                    int minmax_,
                    double & xextr_,
                    double & fextr_,
                    void * params_)
  {
    /*
     * Subroutine tgold determines maximum or minimum of the function f(x) in
     * the interval [a,c] by the gold section method.
     * Call :   external f
     *          call tgold(a,b,f,eps_,minmax_,xextr_,fextr_)
     * Input:   a,c    - beginning and the end of the interval [a,c];
     *          b      - dummy value
     *          f      - name of the external function; should be as
     *                        function f(x), and additional parameters have
     *                        to be transmitted with help of common blocks;
     *          eps_    - desired uncertainty of xextr_ determination;
     *          minmax_ - if minmax_ = 1 minimum of f(x) is searched,
     *                             = 2 maximum of f(x) is searched.
     * Output:  xextr_  - x-point of extremum;
     *          fextr_  - f(xextr_).
     * V.Tretyak, 25.09.1985.
     */
    double qc = 0.61803395;
    double al = a_;
    double bl = c_;
    double xp = al + (bl - al) * qc;
    double xl = bl - (bl - al) * qc;
    double yp = f_(xp, params_);
    double yl = f_(xl, params_);
  label_3:
    if (minmax_ == 1) {
      goto label_4;
    } else if (minmax_ == 2) {
      goto label_5;
    }
  label_4:
    if (yp < yl) {
      goto label_1;
    }
    goto label_6;
  label_5:
    if (yp > yl) {
      goto label_1;
    }
  label_6:
    bl = xp;
    xp = xl;
    yp = yl;
    xl = bl - (bl - al) * qc;
    yl = f_(xl, params_);
    goto label_2;
  label_1:
    al = xl;
    xl = xp;
    yl = yp;
    xp = al + (bl - al) * qc;
    yp = f_(xp, params_);
  label_2:
    if ((bl - al) > eps_) {
      goto label_3;
    }
    xextr_ = 0.5 * (al + bl);
    fextr_ = f_(xextr_, params_);
    return;
  }

} // end of namespace bxdecay0
