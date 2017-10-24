// Ourselves:
#include <bxdecay0/funbeta.h>

// Standard library:
#include <iostream>
#include <cmath>
#include <stdexcept>

// Third party:
// - GSL:
#include <gsl/gsl_math.h>

// This project:
#include <bxdecay0/fermi.h>
#include <bxdecay0/particle.h>

namespace bxdecay0 {

  /// \brief Function to search the maximum of beta spectrum curve by decay0_tgold subroutine.
  double decay0_funbeta(double E_, void * params_)
  {
    const parbeta * pars = static_cast<const parbeta *>(params_);
    const double & Qbeta = pars->Qbeta;
    const double & Zdtr = pars->Zdtr;
    double f = 0.0;
    static const double emass = decay0_emass();
    if (E_ > 0.) {
      f = std::sqrt(E_ * (E_ + 2. * emass))
        * (E_ + emass)
        * gsl_pow_2(Qbeta - E_)
        * decay0_fermi(Zdtr, E_);
    }
    return f;
  }

} // end of namespace bxdecay0
