/** \file bxdecay0/std_random.h
 *  \brief Functor wrapping a standard random number generator
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

#ifndef BXDECAY0_STD_RANDOM_H
#define BXDECAY0_STD_RANDOM_H

// Standard library:
#include <random>

// This project:
#include <bxdecay0/i_random.h>

namespace bxdecay0 {

  /// \brief Wrapper functor for a standard random number generator
  class std_random : public i_random
  {
  public:
    /// Constructor
    std_random(std::default_random_engine & generator_);

    /// Main operator
    virtual double operator()();

  private:
    std::default_random_engine & _generator_;    ///< Handle to a default random engine
    std::uniform_real_distribution<double> _ud_; ///< Uniform deviates distribution
  };

} // end of namespace bxdecay0

#endif // BXDECAY0_STD_RANDOM_H

// Local Variables: --
// mode: c++ --
// End: --
