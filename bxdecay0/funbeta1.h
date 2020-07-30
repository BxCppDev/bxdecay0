#ifndef BXDECAY0_FUNBETA1_H
#define BXDECAY0_FUNBETA1_H

// This project:
#include <bxdecay0/funbeta.h>

namespace bxdecay0 {

  struct parbeta1 : public parbeta
  {
    double c1;
    double c2;
    double c3;
    double c4;
  };

  double decay0_funbeta1(double e_, void * params_);

} // namespace bxdecay0

#endif // BXDECAY0_FUNBETA1_H

// Local Variables: --
// mode: c++ --
// End: --
