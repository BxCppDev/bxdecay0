/** test_fermi.cxx
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
#include <bxdecay0/fermi.h>

// Standard library:
#include <cmath>

/**
 * Example:
 * \code
 * $ bxdecay0-test_fermi  > fermi.data
 * $ gnuplot
 * gnuplot> set grid
 * gnuplot> plot 'fermi.data' title "Z=42" with lines
 * \endcode
 */
int main()
{
  int error_code = EXIT_SUCCESS;
  try {

    double z       = 42.0;
    double emin    = 0.020; // MeV
    double emax    = 3.5;   // MeV
    double delta_e = 0.010; // MeV

    for (double energy = emin; energy < emax; energy += delta_e) {
      std::cout << energy << ' ' << bxdecay0::decay0_fermi(z, energy) << std::endl;
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
