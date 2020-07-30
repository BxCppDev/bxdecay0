// C++ port of the CERNLIB divdif routine
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
#include <bxdecay0/divdif.h>

// Standard library:
#include <cmath>
#include <sstream>
#include <stdexcept>

namespace bxdecay0 {

  // From CERNLIB: 2006/src/packlib/kernlib/kernnum/e105fort/divdif.F
  double decay0_divdif(const double * F_, const double * A_, int NN_, double X_, int MM_)
  {
    double T[20], D[20];
    bool EXTRA;
    const int MMAX = 10;
    // C  START.  FIND SUBSCRIPT IX OF X IN ARRAY A.
    if ((NN_ < 2) || (MM_ < 1)) {
      std::ostringstream message;
      message << "genbb::decay0::decay0_divdif: "
              << "Invalid parameters (" << NN_ << "/" << MM_ << ") !";
      throw std::logic_error(message.str());
    }
    int N     = NN_;
    int M     = std::min(MM_, MMAX);
    M         = std::min(M, N - 1);
    int MPLUS = M + 1;
    int IX    = 0;
    int IY    = N + 1;
    int MID;

    if (A_[0] > A_[N - 1]) {
      goto tag_4;
    }
    //     (SEARCH INCREASING ARGUMENTS.)
  tag_1:
    MID = (IX + IY) / 2;
    if (X_ >= A_[MID - 1]) {
      goto tag_2;
    }
    IY = MID;
    goto tag_3;
    //        (IF TRUE.)
  tag_2:
    IX = MID;
  tag_3:
    if (IY - IX > 1) {
      goto tag_1;
    }
    goto tag_7;
    //     (SEARCH DECREASING ARGUMENTS.)
  tag_4:
    MID = (IX + IY) / 2;
    if (X_ <= A_[MID - 1]) {
      goto tag_5;
    }
    IY = MID;
    goto tag_6;
    //        (IF TRUE.)
  tag_5:
    IX = MID;
  tag_6:
    if (IY - IX > 1) {
      goto tag_4;
    }
    //
    //  COPY REORDERED INTERPOLATION POINTS INTO (T(I),D(I)), SETTING
    //  *EXTRA* TO TRUE IF M+2 POINTS TO BE USED.
  tag_7:
    int NPTS = M + 2 - (M % 2);
    int IP   = 0;
    int L    = 0;
    goto tag_9;
  tag_8:
    L = -L;
    if (L >= 0) {
      L = L + 1;
    }
  tag_9:
    int ISUB = IX + L;
    if ((1 <= ISUB) && (ISUB <= N)) {
      goto tag_10;
    }
    //        (SKIP POINT.)
    NPTS = MPLUS;
    goto tag_11;
    //        (INSERT POINT.)
  tag_10:
    IP++;
    T[IP - 1] = A_[ISUB - 1];
    D[IP - 1] = F_[ISUB - 1];
  tag_11:
    if (IP < NPTS) {
      goto tag_8;
    }
    EXTRA = (NPTS != MPLUS);
    //
    //  REPLACE D BY THE LEADING DIAGONAL OF A DIVIDED-DIFFERENCE TABLE, SUP-
    //  PLEMENTED BY AN EXTRA LINE IF *EXTRA* IS TRUE.
    for (int localL = 1; localL <= M; localL++) {
      if (!EXTRA) {
        goto tag_12;
      }
      ISUB     = MPLUS - localL;
      D[M + 1] = (D[M + 1] - D[M - 1]) / (T[M + 1] - T[ISUB - 1]);
    tag_12:
      int I = MPLUS;
      for (int J = localL; J <= M; J++) {
        ISUB     = I - localL;
        D[I - 1] = (D[I - 1] - D[I - 2]) / (T[I - 1] - T[ISUB - 1]);
        I        = I - 1;
      }
    }
    //
    //  EVALUATE THE NEWTON INTERPOLATION FORMULA AT X, AVERAGING TWO VALUES
    //  OF LAST DIFFERENCE IF *EXTRA* IS TRUE.
    double SUM = D[MPLUS - 1];
    if (EXTRA) {
      SUM = 0.5 * (SUM + D[M + 1]);
    }
    int J = M;
    for (int localL = 1; localL <= M; localL++) {
      SUM = D[J - 1] + (X_ - T[J - 1]) * SUM;
      J--;
    }
    return SUM;
  }

} // end of namespace bxdecay0
