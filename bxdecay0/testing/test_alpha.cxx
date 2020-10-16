/** test_alpha.cxx
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
 *
 */

// Standard library:
#include <chrono>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <limits>
#include <random>

// This project:
#include <bxdecay0/alpha.h>
#include <bxdecay0/event.h>
#include <bxdecay0/std_random.h>

int main()
{
  int error_code = EXIT_SUCCESS;
  try {

    bxdecay0::event decay;
    decay.set_time(0.0);
    {
      unsigned int seed = 314159;
      // seed = std::chrono::system_clock::now().time_since_epoch().count();
      std::default_random_engine generator(seed);
      bxdecay0::std_random prng(generator);
      double tclev      = 0.0;
      double thlev      = 1.0;
      double decay_time = std::numeric_limits<double>::quiet_NaN();
      bxdecay0::decay0_alpha(prng,
                             decay,
                             7.832,     // MeV
                             tclev,     // second
                             thlev,     // second
                             decay_time // second
      );
    }
    decay.print(std::clog, "Decay with one emitted alpha:", "[info] ");

  } catch (std::exception & error) {
    std::cerr << "[error] " << error.what() << std::endl;
    error_code = EXIT_FAILURE;
  } catch (...) {
    std::cerr << "[error] "
              << "Unexpected exception!" << std::endl;
    error_code = EXIT_FAILURE;
  }
  return error_code;
}
