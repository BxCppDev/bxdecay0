#ifndef BXDECAY0_FUNBETA2_H
#define BXDECAY0_FUNBETA2_H

// This project:
#include <bxdecay0/funbeta1.h>

namespace bxdecay0 {

  struct parbeta2 : public parbeta1
  {
    int kf;
  };

  double decay0_funbeta2(double e_, void * params_);

} // namespace bxdecay0

#endif // BXDECAY0_FUNBETA2_H

// Local Variables: --
// mode: c++ --
// End: --
