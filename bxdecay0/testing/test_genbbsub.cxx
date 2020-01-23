/** test_genbbsub.cxx
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
#include <iostream>
#include <exception>
#include <cstdlib>
#include <random>
#include <chrono>
#include <limits>

// This project:
#include <bxdecay0/event.h>
#include <bxdecay0/genbbsub.h>
#include <bxdecay0/std_random.h>
#include <bxdecay0/bb.h>

int main()
{
  int error_code = EXIT_SUCCESS;
  try {

    unsigned int seed = 314159;
    std::default_random_engine generator(seed);
    bxdecay0::std_random prng(generator);

    bxdecay0::event decay;
    {
      int i2bbs = bxdecay0::GENBBSUB_I2BBS_DBD;
      std::string chnuclide = "Mo100";
      int ilevel = 0;
      int modebb = bxdecay0::LEGACY_MODEBB_1;
      int istart = bxdecay0::GENBBSUB_ISTART_INIT;
      int ier = 0;
      bxdecay0::bbpars bb_params;
      bb_params.ebb1 = 0.0; // MeV
      bb_params.ebb2 = 4.3; // MeV
      bb_params.toallevents = 1.0; // Weight
      bxdecay0::genbbsub(prng,
                         decay,
                         i2bbs,
                         chnuclide,
                         ilevel,
                         modebb,
                         istart,
                         ier,
                         bb_params);
      if (ier != 0) {
        throw std::logic_error("genbbsub failed!");
      }
    }
    decay.set_time(0.0);
    decay.print(std::clog, "DBD event:", "[info] ");
    decay.store(std::cout);

  } catch (std::exception & error) {
    std::cerr << "[error] " << error.what() << std::endl;
    error_code = EXIT_FAILURE;
  } catch (...) {
    std::cerr << "[error] " << "Unexpected exception!" << std::endl;
    error_code = EXIT_FAILURE;
  }
  return error_code;
}
