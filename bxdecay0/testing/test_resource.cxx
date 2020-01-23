/** test_resource.cxx
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

// This project:
#include <bxdecay0/resource.h>

int main()
{
  int error_code = EXIT_SUCCESS;
  try {

    std::clog << "[info] Resource path: " << bxdecay0::get_resource_dir(true) << std::endl;
    const char * env_key = "BXDECAY0_RESOURCE_DIR";
    setenv(env_key, "/tmp/BxDecay0/resources.d", 1);
    std::clog << "[info] Resource path: " << bxdecay0::get_resource_dir(true) << std::endl;

  } catch (std::exception & error) {
    std::cerr << "[error] " << error.what() << std::endl;
    error_code = EXIT_FAILURE;
  } catch (...) {
    std::cerr << "[error] " << "Unexpected exception!" << std::endl;
    error_code = EXIT_FAILURE;
  }
  return error_code;
}
