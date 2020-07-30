// C++ port of the CERNLIB dgmlt2 routine
//
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
#include <bxdecay0/dgmlt2.h>

// Standard library:
#include <cmath>
#include <sstream>
#include <stdexcept>

namespace bxdecay0 {

  // double X[6];
  double decay0_dgmlt2(fsub2_type FSUB2_, double A_, double B_, int NI_, int NG_, double * X_, void * params_)
  {
    static const double W[14] = {0.171324492379170345,
                                 0.360761573048138608,
                                 0.467913934572691047,
                                 0.467913934572691047,
                                 0.360761573048138608,
                                 0.171324492379170345,
                                 0.101228536290376259,
                                 0.222381034453374471,
                                 0.313706645877887287,
                                 0.362683783378361983,
                                 0.362683783378361983,
                                 0.313706645877887287,
                                 0.222381034453374471,
                                 0.101228536290376259};
    static const double T[14] = {
        -0.932469514203152028,
        -0.661209386466264514,
        -0.238619186083196909,
        0.238619186083196909,
        0.661209386466264514,
        0.932469514203152028,
        -0.960289856497536232,
        -0.796666477413626740,
        -0.525532409916328986,
        -0.18343464245649805,
        0.183434642495649805,
        0.525532409916328986,
        0.796666477413626740,
        0.960289856497536232,
    };
    double V[64];
    double U[64];
    double F[64];
    if (NI_ <= 0) {
      std::ostringstream message;
      message << "genbb::decay0::decay0_dgmlt2: "
              << "Invalid NI parameter (" << NI_ << ") !";
      throw std::logic_error(message.str());
    }
    int M0 = NG_;
    if (M0 != 8)
      M0 = 6;
    int I0 = 0;
    if (M0 == 8)
      I0 = 6;
    double D  = (B_ - A_) / NI_;
    double R  = 0.5 * D;
    double RA = R + A_;
    int MV    = (M0 * NI_ - 1) % 64 + 1;
    double S  = 0.0;
    int J     = 0;
    for (int I = 1 + I0; I <= M0 + I0; I++) {
      double RTA = R * T[I - 1] + RA;
      for (int K = 1; K <= NI_; K++) {
        J        = J + 1;
        V[J - 1] = W[I - 1];
        U[J - 1] = RTA + (K - 1) * D;
        if (J == MV) {
          FSUB2_(MV, U, F, X_, params_);
          for (J = 1; J <= MV; J++) {
            S += V[J - 1] * F[J - 1];
          }
          MV = 64;
          J  = 0;
        }
      }
    }
    return R * S;
  }

} // end of namespace bxdecay0
