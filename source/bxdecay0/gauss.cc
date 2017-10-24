
// Ourselves:
#include <bxdecay0/gauss.h>

// Standard library:
#include <iostream>
#include <cmath>
#include <sstream>
#include <stdexcept>

// Third party:
// - GSL:
#include <gsl/gsl_errno.h>
#include <gsl/gsl_integration.h>

namespace bxdecay0 {

  double decay0_gauss(func_type f_,
                      double min_, double max_, double epsrel_,
                      void * params_)
  {
    // bool devel = false;
    // if (devel) {
    //   std::cerr << "[devel] bxdecay0::decay0_gauss: Entering..." << std::endl;
    // }
    double result, abserr;
    size_t neval;
    gsl_function F;
    F.function = f_;
    F.params   = params_;
    double epsabs = 1e-9;
    double epsrel = epsrel_;
    epsabs = 0.0;
    int count = 0;
    int status = 0;
    gsl_error_handler_t * gsl_eh = gsl_set_error_handler_off();
    while (true) {
      status = gsl_integration_qng(&F, min_, max_, epsabs, epsrel,
                                   &result, &abserr, &neval);
      // if (devel) {
      //   std::cerr << "[devel] bxdecay0::decay0_gauss: status = " << status << std::endl;
      //   std::cerr << "[devel] bxdecay0::decay0_gauss: result = " << result << std::endl;
      //   std::cerr << "[devel] bxdecay0::decay0_gauss: abserr = " << abserr << std::endl;
      //   std::cerr << "[devel] bxdecay0::decay0_gauss: neval  = " << neval << std::endl;
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
      // if (devel) {
      //   std::cerr << "[devel] bxdecay0::decay0_gauss: GSL_ETOL = " << "retrying..." << std::endl;
      // }
    }
    gsl_set_error_handler(gsl_eh);
    if (status != 0) {
      std::ostringstream message;
      message << "bxdecay0::decay0_gauss: "
              << "GSL QNG integration error '"
              << gsl_strerror(status)
              << "' !";
      std::cerr << "[warning] " << message.str() << std::endl;
      // throw std::runtime_error(message.str());
    }
    // if (devel) {
    //   std::cerr << "[devel] bxdecay0::decay0_gauss: Exiting." << std::endl;
    // }
    return result;
  }

} // end of namespace bxdecay0
