/** test_event_reader.cxx
 *
 * Copyright 2020 François Mauger <mauger@lpccaen.in2p3.fr>
 * Copyright 2020 Normandie Université
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
#include <exception>
#include <iostream>

// This project:
#include <bxdecay0/resource.h>
#include <bxdecay0/event.h>
#include <bxdecay0/event_reader.h>

int main(int argc_, char ** argv_)
{
  int error_code = EXIT_SUCCESS;
  try {

    bxdecay0::event_reader::config_type readerConfig;
    // List of input files:
    readerConfig.event_files.push_back(bxdecay0::get_resource_dir(true) + "/samples/Co60/genCo60-1.d0t");
    readerConfig.event_files.push_back(bxdecay0::get_resource_dir(true) + "/samples/Co60/genCo60-2.d0t");
    readerConfig.event_files.push_back(bxdecay0::get_resource_dir(true) + "/samples/Co60/genCo60-3.d0t");
    readerConfig.start_event     = 5;    // Start at first loaded event
    readerConfig.max_nb_events   = 19;   // 0=no limit
    readerConfig.zero_event_time = true; // Force event time to zero

    int verbosity = 0;
    if (argc_ > 1) verbosity = std::stoi(std::string(argv_[1]));
    // The reader:
    bxdecay0::event_reader reader(readerConfig, verbosity);
    while (reader.has_next_event()) {
      bxdecay0::event decayEvent;
      reader.load_next_event(decayEvent);
      if (decayEvent.is_valid()) {
        if (verbosity > 0) decayEvent.print(std::clog, "Decay event with several emitted particles:", "[info] ");
      } else {
        throw std::logic_error("Could not load a valid decay event!");
      }
    }
    std::clog << "[info] Reader is terminated  : " << std::boolalpha << reader.is_terminated() << '\n';
    std::clog << "[info] Loaded events counter : " << reader.get_loaded_event_counter() << '\n';

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
