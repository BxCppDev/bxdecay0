/** test_decay0.cxx
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
#include <exception>
#include <iostream>

// This project:
#include <bxdecay0/bb_utils.h>
#include <bxdecay0/config.h>
#include <bxdecay0/resource.h>
#include <bxdecay0/version.h>

int main()
{
  int error_code = EXIT_SUCCESS;
  try {

    std::clog << "Hello, BxDecay0!" << std::endl;
    std::clog << "Decay0 original author : "
              << "V.I.Tretyak" << std::endl;
    std::clog << "BxDecay0 C++ port      : "
              << "F.Mauger" << std::endl;
    std::clog << "BxDecay0 Licence       : "
              << "GPL 3" << std::endl;
    std::clog << "BxDecay0 version       : " << BXDECAY0_LIB_VERSION << std::endl;
    std::clog << "Decay0 version         : " << BXDECAY0_DECAY0_VERSION << std::endl;
    std::clog << "Resource dir           : '" << bxdecay0::get_resource_dir(true) << "'" << std::endl;

    const std::set<std::string> & dbdIsotopes = bxdecay0::dbd_isotopes();
    for (const auto & dbdIso : dbdIsotopes) {
      std::clog << dbdIso << '\n';
    }
    std::clog << "Bye." << std::endl;

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
