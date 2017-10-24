/** ex01.cxx
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
#include <stdexcept>
#include <iostream>
#include <fstream>

// This project:
#include <bxdecay0/std_random.h> // Random number interface
#include <bxdecay0/event.h>      // Generated event model
#include <bxdecay0/bb.h>         // Nuclear decay and double beta decay parameters
#include <bxdecay0/genbbsub.h>   // Main decay generation routine
#include <bxdecay0/version.h>    // Library version

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

    // Output file name:
    std::string foutname("gendecay0.data");

    // Parameters of the decay:
    bxdecay0::bbpars bb_params;
    bb_params.ebb1 = 0.0; // Minimum energy (MeV)
    bb_params.ebb2 = 4.3; // Maximum energy (MeV)
    bb_params.toallevents = 1.0; /* Statistical weight of the event
                                  * with respect to the total energy
                                  * spectrum.
                                  */
    // Mode: double beta decay:
    int i2bbs = bxdecay0::GENBBSUB_I2BBS_DBD;

    // Isotope:
    std::string chnuclide = "Mo100";

    // Daughter's energy level (ground state):
    int ilevel = 0;

    // DBD mode (neutrinoless):
    int modebb = bxdecay0::MODEBB_0NUBB_0_2N;

    // Activity of the decaying source in becquerel:
    double activity = 2.0;

    /***************************************/
    /* Initialization of working resources */
    /***************************************/

    // Output file for generated decay events:
    std::ofstream fout(foutname.c_str());

    // Random generator:
    std::default_random_engine generator(seed);
    bxdecay0::std_random prng(generator);

    // Decay event (collection of generated particles):
    bxdecay0::event decay;

    // Initialize the generator:
    int ier = 0;
    bxdecay0::genbbsub(prng,
                       decay,
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
    decay.reset();

    // Store config/metadata:
    fout << "#!bxdecay0 " << BXDECAY0_LIB_VERSION << std::endl;
    fout << "#@run_start" << std::endl;
    fout << "#@seed=" << seed << std::endl;
    fout << "#@activity=" << activity << ' ' << "Bq" << std::endl;
    fout << "#@nevents=" << nevents << std::endl;
    fout << "#@min_energy=" << bb_params.ebb1 << ' ' << "MeV" << std::endl;
    fout << "#@max_energy=" << bb_params.ebb2 << ' ' << "MeV" << std::endl;
    fout << "#@weight=" << bb_params.toallevents << std::endl;
    fout << "#@type=" << i2bbs << std::endl;
    fout << "#@nuclide=" << chnuclide << std::endl;
    fout << "#@daughter_level=" << ilevel << std::endl;
    fout << "#@mode_bb=" << modebb << std::endl;
    fout << "#" << std::endl;
    fout << "# Format of an event (time in second,  momentum in MeV/c):" << std::endl;
    fout << "#" << std::endl;
    fout << "#   event-time" << std::endl;
    fout << "#   number-of-particles" << std::endl;
    fout << "#   code1 time1 px1 py1 pz1"  << std::endl;
    fout << "#   ..." << std::endl;
    fout << "#   codeN timeN pxN pyN pzN"  << std::endl;
    fout << "#" << std::endl;
    fout << std::endl;

    /**************************/
    /* Decay Event generation */
    /**************************/

    std::exponential_distribution<> decay_timer(activity);
    // Loop on events:
    for (std::size_t ievent = 0; ievent < nevents; ievent++) {

      // Randomize the decay event:
      bxdecay0::genbbsub(prng,
                         decay,
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
      decay.set_time(evtime);

      // Debug dump:
      if (debug) decay.print(std::cerr, "DBD event:", "[debug] ");

      // Store events:
      uint32_t store_flags =
        bxdecay0::event::STORE_EVENT_DECO
        | bxdecay0::event::STORE_EVENT_TIME
        | bxdecay0::particle::STORE_PARTICLE_NAME;
      decay.store(fout, store_flags);

      // Clear the event:
      decay.reset();
    }

    /***************/
    /* Termination */
    /***************/

    fout << "#@run_stop" << std::endl;
    fout.close();

  } catch (std::exception & error) {
    std::cerr << "[error] " << error.what() << std::endl;
    error_code = EXIT_FAILURE;
  } catch (...) {
    std::cerr << "[error] " << "Unexpected exception!" << std::endl;
    error_code = EXIT_FAILURE;
  }
  return error_code;
}
