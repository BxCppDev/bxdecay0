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
#include <bxdecay0/plog69.h>

// Standard library:
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>

namespace bxdecay0 {

  const double BJ69::plog69[48] = {
    -2.302585,
    -1.609438,
    -1.203973,
    -0.9162907,
    -0.6931472,
    -0.5108256,
    -0.3566750,
    -0.2231435,
    -0.1053605,
    0.0000000,
    0.1823216,
    0.3364722,
    0.4700036,
    0.5877866,
    0.6931472,
    0.7884574,
    0.8754688,
    0.9555114,
    1.029619,
    1.098612,
    1.163151,
    1.223776,
    1.280934,
    1.335001,
    1.386294,
    1.504077,
    1.609438,
    1.704748,
    1.791759,
    1.871802,
    1.945910,
    2.014903,
    2.079442,
    2.197225,
    2.302585,
    2.397895,
    2.484907,
    2.564949,
    2.639057,
    2.890372,
    2.995732,
    3.218876,
    3.401197,
    3.555348,
    3.688879,
    3.806663,
    3.912023
  };

} // end of namespace bxdecay0
