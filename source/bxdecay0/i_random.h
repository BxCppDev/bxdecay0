/** \file bxdecay0/i_random.h
 *  \brief Interface for uniform deviates pseudo-random number generator functor
 *
 * Copyright 2017 François Mauger <mauger@lpccaen.in2p3.fr>
 * Copyright 2017 Normandie Université
 *
 * This file is part of BxDecay0.
 *
 * BxDecay0 is free software: you  can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free  Software Foundation, either  version 3 of the  License, or
 * (at your option) any later version.
 *
 * BxDecay0 is distributed  in the hope that it will  be useful, but
 * WITHOUT  ANY   WARRANTY;  without  even  the   implied  warranty  of
 * MERCHANTABILITY or  FITNESS FOR A  PARTICULAR PURPOSE.  See  the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with BxDecay0.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BXDECAY0_I_RANDOM_H
#define BXDECAY0_I_RANDOM_H

namespace bxdecay0 {

  /// \brief Interface for random number generator classes with
  //         uniform deviates distribution in [0;1).
  struct i_random
  {
    virtual double operator()() = 0;
  };

} // end of namespace bxdecay0

#endif // BXDECAY0_I_RANDOM_H

// Local Variables: --
// mode: c++ --
// End: --
