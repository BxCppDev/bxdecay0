/** ex03.cxx
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
#include <bxdecay0/version.h>          // Library version
#include <bxdecay0/std_random.h>       // Random number interface
#include <bxdecay0/event.h>            // Generated event model
#include <bxdecay0/decay0_generator.h> // Main decay0 generator

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
    std::size_t nevents = 10;

    // Output file name:
    std::string fout_name("bxdecay_ex03.data");

    // Parameters of the decay:

    // Isotope:
    std::string nuclide = "Co60";

    // Activity of the decaying source (becquerel):
    double activity = 2.0;

    // The random generator:
    std::default_random_engine generator(seed);
    bxdecay0::std_random prng(generator);

    // The event generator:
    bxdecay0::decay0_generator decay0;

    // Configuration:
    decay0.set_debug(false);
    decay0.set_decay_category(bxdecay0::decay0_generator::DECAY_CATEGORY_BACKGROUND);
    decay0.set_decay_isotope(nuclide);

    // Initialization;
    decay0.initialize(prng);

    // Print:
    decay0.smart_dump(std::clog, "Decay0 Background generator: ", "[info] ");

    /***************************************/
    /* Initialization of working resources */
    /***************************************/

    // Output file for generated decay events:
    std::ofstream fout(fout_name.c_str());

    // Store format options:
    uint32_t store_flags =
      bxdecay0::event::STORE_EVENT_DECO
      | bxdecay0::event::STORE_EVENT_TIME
      | bxdecay0::particle::STORE_PARTICLE_NAME;

    // Store config/metadata in the file header:
    fout << "#!bxdecay0 " << BXDECAY0_LIB_VERSION << std::endl;
    fout << "#@run_info_start" << std::endl;
    fout << "#@seed=" << seed << std::endl;
    fout << "#@activity=" << activity << ' ' << "Bq" << std::endl;
    fout << "#@nevents=" << nevents << std::endl;
    fout << "#@category=" << decay0.get_decay_category() << std::endl;
    fout << "#@nuclide=" << decay0.get_decay_isotope() << std::endl;
    fout << "#@run_info_stop" << std::endl;
    fout << "#" << std::endl;
    fout << "# Format of an event (time in second,  momentum in MeV/c):" << std::endl;
    fout << "#" << std::endl;
    fout << "#   #@event_start" << std::endl;
    fout << "#   event-time nuclide" << std::endl;
    fout << "#   number-of-particles" << std::endl;
    fout << "#   code1 time1 px1 py1 pz1 name"  << std::endl;
    fout << "#   ..." << std::endl;
    fout << "#   codeN timeN pxN pyN pzN name"  << std::endl;
    fout << "#   #@event_stop" << std::endl;
    fout << "#" << std::endl;
    fout << std::endl;

    /**************************/
    /* Decay Event generation */
    /**************************/

    // Random engine for the event time:
    std::exponential_distribution<> decay_timer(activity);

    // Generated decay event (collection of generated particles):
    bxdecay0::event gendecay;

    // Loop on events:
    for (std::size_t ievent = 0; ievent < nevents; ievent++) {

      // Randomize the decay event:
      decay0.shoot(prng, gendecay);

      // Force the time of the decay:
      double evtime = decay_timer(generator);
      gendecay.set_time(evtime);

      // Debug dump:
      if (debug) gendecay.print(std::cerr, "DBD event:", "[debug] ");

      // Store the event:
      gendecay.store(fout, store_flags);

      // Clear the event:
      gendecay.reset();
    }

    /***************/
    /* Termination */
    /***************/

    fout.close();

    // terminate the generator:
    decay0.reset();

  } catch (std::exception & error) {
    std::cerr << "[error] " << error.what() << std::endl;
    error_code = EXIT_FAILURE;
  } catch (...) {
    std::cerr << "[error] " << "Unexpected exception!" << std::endl;
    error_code = EXIT_FAILURE;
  }
  return error_code;
}
