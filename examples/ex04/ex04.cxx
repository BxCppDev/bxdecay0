/** ex04.cxx
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
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>

// This project:
#include <bxdecay0/bb.h>         // Nuclear decay and double beta decay parameters
#include <bxdecay0/event.h>      // Generated event model
#include <bxdecay0/genbbsub.h>   // Main decay generation routine
#include <bxdecay0/std_random.h> // Random number interface

int main()
{
  int error_code = EXIT_SUCCESS;
  try {

    /****************************/
    /* Configuration parameters */
    /****************************/

    // Debug flag:
    bool debug = true;

    // Random seed:
    unsigned int seed = 314159;

    // Number of generated events:
    std::size_t nevents = 100;

    // Parameters of the decay:
    bxdecay0::bbpars bb_params;
    bb_params.ebb1        = 0.0; // Minimum energy (MeV)
    bb_params.ebb2        = 4.3; // Maximum energy (MeV)
    bb_params.toallevents = 1.0; /* Statistical weight of the event
                                  * with respect to the total energy
                                  * spectrum.
                                  */

    // Mode: double beta decay:
    int i2bbs = bxdecay0::GENBBSUB_I2BBS_DBD;

    // Isotope:
    std::string chnuclide = "Mo100";

    // Daughter's energy level (0 = ground state):
    int ilevel = 0;

    // DBD mode (neutrinoless):
    int modebb = bxdecay0::LEGACY_MODEBB_1; // 0vbb

    // Activity of the decaying source in becquerel:
    double activity = 2.0;

    /***************************************/
    /* Initialization of working resources */
    /***************************************/

    // Random generator:
    std::default_random_engine generator(seed);
    bxdecay0::std_random prng(generator);

    // Decay event (collection of generated particles):
    bxdecay0::event gendecay;

    // Initialize the generator:
    int ier = 0;
    bxdecay0::genbbsub(prng,
                       gendecay,
                       i2bbs,
                       chnuclide,
                       ilevel,
                       modebb,
                       bxdecay0::GENBBSUB_ISTART_INIT,
                       ier,
                       bb_params);
    if (ier != 0) {
      throw std::logic_error("genbbsub initialization !");
    }
    gendecay.reset();

    /**************************/
    /* Decay Event generation */
    /**************************/

    std::exponential_distribution<> decay_timer(activity);

    // Loop on events:
    for (std::size_t ievent = 0; ievent < nevents; ievent++) {

      // Randomize the decay event:
      bxdecay0::genbbsub(prng,
                         gendecay,
                         i2bbs,
                         chnuclide,
                         ilevel,
                         modebb,
                         bxdecay0::GENBBSUB_ISTART_GENERATE,
                         ier,
                         bb_params);
      if (ier != 0) {
        throw std::logic_error("genbbsub failed!");
      }

      // Force the time of the decay:
      double evtime = decay_timer(generator);
      gendecay.set_time(evtime);

      // Debug dump:
      if (debug) {
        gendecay.print(std::cerr, "DBD event:", "[debug] ");
      }

      // Clear the event:
      gendecay.reset();
    }

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
