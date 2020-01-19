/** test_bb.cxx
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
#include <iomanip>
#include <exception>
#include <cstdlib>

// This project:
#include <bxdecay0/bb_utils.h>

int main()
{
  int error_code = EXIT_SUCCESS;
  try {

    const auto & dbd_isotopes = bxdecay0::dbd_isotopes();
    std::clog << "Supported DBD isotopes: " << std::endl;
    for (const auto & name : dbd_isotopes) {
      std::clog << name << std::endl;
    }
    std::clog << std::endl;
    
    const auto & background_isotopes = bxdecay0::background_isotopes();
    std::clog << "Supported Background isotopes: " << std::endl;
    for (const auto & name : background_isotopes) {
      std::clog << name << std::endl;
    }
    std::clog << std::endl;
     
    const auto & dbd_modes = bxdecay0::dbd_modes();
    std::clog << "Supported DBD modes: " << std::endl;
    for (const auto & rec : dbd_modes) {
      std::clog << '[' << std::setw(2) << rec.first << "] " << std::setw(20) << rec.second.unique_label << " : "
                << '{' << std::setw(2) << rec.second.legacy_modebb << "} : " << rec.second.description << std::endl;
    }
    std::clog << std::endl;
    
  } catch (std::exception & error) {
    std::cerr << "[error] " << error.what() << std::endl;
    error_code = EXIT_FAILURE;
  } catch (...) {
    std::cerr << "[error] " << "Unexpected exception!" << std::endl;
    error_code = EXIT_FAILURE;
  }
  return error_code;
}
