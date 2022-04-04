/** test_event.cxx
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
#include <bxdecay0/event.h>
#include <bxdecay0/std_random.h>

int main()
{
  int error_code = EXIT_SUCCESS;
  try {

    bxdecay0::event decay;
    decay.set_time(0.0); // Reference time of the event (in second)
    {
      bxdecay0::particle beta;
      beta.set_code(bxdecay0::ELECTRON);
      beta.set_time(0.0);
      beta.set_momentum(0.0, 0.0, 1.022);
      decay.add_particle(beta);
    }
    {
      bxdecay0::particle gamma;
      gamma.set_code(bxdecay0::GAMMA);
      gamma.set_time(13.4e-12);
      gamma.set_momentum(0.0, 0.511, 0.0);
      decay.add_particle(gamma);
    }
    {
      unsigned int seed = 314159;
      std::default_random_engine generator(seed);
      bxdecay0::std_random prng(generator);
      double tclev      = 0.0;
      double thlev      = 1.0;
      double decay_time = std::numeric_limits<double>::quiet_NaN();
      bxdecay0::randomize_particle(prng,
                                   decay,
                                   bxdecay0::ELECTRON,
                                   0.1,       // MeV
                                   0.7,       // MeV
                                   0.0,       // radian
                                   M_PI,      // radian
                                   0.0,       // radian
                                   2 * M_PI,  // radian
                                   tclev,     // second
                                   thlev,     // second
                                   decay_time // second
                                   );
      std::clog << "[info] decay_time=" << decay_time << " s\n"; 
      bxdecay0::randomize_particle(prng,
                                   decay,
                                   bxdecay0::ELECTRON,
                                   1.0,       // MeV
                                   1.0,       // MeV
                                   0.0,       // radian
                                   0.0,       // radian
                                   0.0,       // radian
                                   0.0,       // radian
                                   tclev,     // second
                                   thlev,     // second
                                   decay_time // second
                                   );
      std::clog << "[info] decay_time=" << decay_time << " s\n"; 
      tclev = decay_time;
      bxdecay0::randomize_particle(prng,
                                   decay,
                                   bxdecay0::POSITRON,
                                   2.0,       // MeV
                                   2.0,       // MeV
                                   0.0,       // radian
                                   0.0,       // radian
                                   0.0,       // radian
                                   0.0,       // radian
                                   tclev,     // second
                                   thlev,     // second
                                   decay_time // second
                                   );
      std::clog << "[info] decay_time=" << decay_time << " s\n"; 
      tclev = 10.0; // Skip from the last particle's time in the event
      thlev = 0.01; // Consider here a short halflife
      bxdecay0::randomize_particle(prng,
                                   decay,
                                   bxdecay0::POSITRON,
                                   2.0,       // MeV
                                   2.0,       // MeV
                                   0.0,       // radian
                                   0.0,       // radian
                                   0.0,       // radian
                                   0.0,       // radian
                                   tclev,     // second
                                   thlev,     // second
                                   decay_time // second
                                   );
      std::clog << "[info] decay_time=" << decay_time << " s\n"; 
    }
    decay.print(std::clog, "Decay with several emitted particles:", "[info] ");
    decay.shift_particles_time(1e-8);
    decay.print(std::clog, "Decay with several emitted particles (shifted):", "[info] ");

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
