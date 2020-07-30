// Copyright 2011-2017 F. Mauger
//
// This program is free software: you  can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free  Software Foundation, either  version 3 of the  License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

// Ourselves:
#include <bxdecay0/gauss.h>

// Standard library:
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <sstream>
#include <stdexcept>

// Third party:
// - GSL:
#include <gsl/gsl_errno.h>
#include <gsl/gsl_integration.h>

// This project:
#include <bxdecay0/utils.h>

namespace bxdecay0 {

  double decay0_gauss(func_type f_, double min_, double max_, double epsrel_, void * params_)
  {
    static bool trace = is_trace("gauss");
    /// TRACE if (trace) std::cerr << "[trace] bxdecay0::decay0_gauss: Entering..." << std::endl;
    double result, abserr;
    result = std::numeric_limits<double>::quiet_NaN();
    size_t neval;
    gsl_function F;
    F.function                   = f_;
    F.params                     = params_;
    double epsabs                = 1e-9;
    double epsrel                = epsrel_;
    epsabs                       = 0.0;
    int count                    = 0;
    int status                   = 0;
    gsl_error_handler_t * gsl_eh = gsl_set_error_handler_off();
    while (true) {
      status = gsl_integration_qng(&F, min_, max_, epsabs, epsrel, &result, &abserr, &neval);
      /// TRACE
      // if (trace) {
      //   static std::unique_ptr<std::ofstream> _fdebug;
      //   if (_fdebug.get() == nullptr) {
      //     _fdebug.reset(new std::ofstream("bxdecay0_gauss_debug.dat"));
      //     std::ofstream & fdebug = *_fdebug.get();
      //     fdebug << "#bxdecay0_gauss_debug.dat" << std::endl;
      //     double dx = (max_ - min_) / 10000;
      //     for (double x = min_; x <= max_ + 0.5 * dx; x += dx) {
      //       double fx = f_(x, params_);
      //       fdebug << x << ' ' << fx << std::endl;
      //     }
      //     fdebug.close();
      //   }
      //   std::cerr << "[trace] bxdecay0::decay0_gauss: status = " << status << std::endl;
      //   std::cerr << "[trace] bxdecay0::decay0_gauss: result = " << result << std::endl;
      //   std::cerr << "[trace] bxdecay0::decay0_gauss: abserr = " << abserr << std::endl;
      //   std::cerr << "[trace] bxdecay0::decay0_gauss: neval  = " << neval << std::endl;
      // }
      if (status == 0) {
        break;
      }
      if (status == GSL_ETOL) {
        epsrel *= 10.0;
      }
      count++;
      if (count >= 2) {
        break;
      }
      /// TRACE if (trace) std::cerr << "[trace] bxdecay0::decay0_gauss: GSL_ETOL = " << "retrying..." << std::endl;
    }
    gsl_set_error_handler(gsl_eh);
    if (status != 0) {
      std::ostringstream message;
      message << "bxdecay0::decay0_gauss: "
              << "GSL QNG integration error: '" << gsl_strerror(status) << "' !";
      std::cerr << "[error] " << message.str() << std::endl;
      // throw std::runtime_error(message.str());
    }
    if (result != result) {
      std::ostringstream message;
      message << "bxdecay0::decay0_gauss: "
              << "GSL QNG integration failed: '" << gsl_strerror(status) << "' !";
      std::cerr << "[fatal] " << message.str() << std::endl;
      throw std::logic_error(message.str());
    }
    /// TRACE if (trace) std::cerr << "[trace] bxdecay0::decay0_gauss: Exiting." << std::endl;
    return result;
  }

} // end of namespace bxdecay0
