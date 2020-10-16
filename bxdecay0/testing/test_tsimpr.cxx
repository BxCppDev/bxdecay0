/** test_tsimpr.cxx
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
#include <bxdecay0/tsimpr.h>

// Standard library:
#include <cmath>

struct f1_params
{
  double A     = 1.0;
  double omega = 1.0;
  double phy   = 0.0;
};

double f1(double x_, void * params_)
{
  const auto * pars      = static_cast<const f1_params *>(params_);
  const double & A       = pars->A;
  const double & omega   = pars->omega;
  const double & phy     = pars->phy;
  // return A * std::cos(omega * x_ + phy);
  return A * x_ * x_;
}

int main()
{
  int error_code = EXIT_SUCCESS;
  try {

    // Function parameters:
    f1_params pars1;
    pars1.A     = 1.0;
    pars1.omega = 1.0;
    pars1.phy   = 0.0;

    // Integration parameters:
    double a = 0.0;
    double b = 1.0;
    // b = M_PI;
    std::size_t m = 1000;
    std::size_t n = 2 * m;       // Number of steps
    double h      = (b - a) / n; // Step
    std::clog << "[info] "
              << "m = " << m << std::endl;
    std::clog << "[info] "
              << "n = " << n << std::endl;
    std::clog << "[info] "
              << "h = " << h << std::endl;

    // Integration:
    double s1 = bxdecay0::decay0_tsimpr(f1, a, b, h, static_cast<void *>(&pars1));
    std::cout.precision(15);
    std::cout << "s1=" << s1 << std::endl;

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
