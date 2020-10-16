#ifndef BXDECAY0_GAUSS_H
#define BXDECAY0_GAUSS_H

// This project:
#include <bxdecay0/common.h>

namespace bxdecay0 {

  /// \brief Gauss quadrature of a function f between min and max
  double decay0_gauss(func_type f_, double min_, double max_, double epsrel_, void * params_);

} // end of namespace bxdecay0

#endif // BXDECAY0_GAUSS_H

// Local Variables: --
// mode: c++ --
// End: --
