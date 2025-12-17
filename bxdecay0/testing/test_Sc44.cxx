/** test_Sc44.cxx
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
#include <bxdecay0/bb.h>
#include <bxdecay0/event.h>
#include <bxdecay0/genbbsub.h>
#include <bxdecay0/std_random.h>
#include <bxdecay0/Sc44.h>

int main()
{
  int error_code = EXIT_SUCCESS;
  try {

    unsigned int seed = 314159;
    std::default_random_engine generator(seed);
    bxdecay0::std_random prng(generator);

    bxdecay0::event decay;
    double t_creation = 0.0;
    double t_decay    = 0.0;
    bxdecay0::Sc44(prng, decay, t_creation, t_decay);

    decay.set_time(t_decay);
    decay.print(std::clog, "Sc-44 event:", "[info] ");
    decay.store(std::cout);

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