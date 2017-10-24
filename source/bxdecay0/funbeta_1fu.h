#ifndef BXDECAY0_FUNBETA_1FU_H
#define BXDECAY0_FUNBETA_1FU_H

// This project:
#include <bxdecay0/funbeta1.h>

namespace bxdecay0 {

  struct bj69sl2
    : public parbeta1
  {
    double sl2[48];
  };

  /// \brief Function to search the maximum of beta spectrum curve by decay0_tgold subroutine.
  // VIT, 26.10.2006.
  double decay0_funbeta_1fu(double e_, void * params_);

} // end of namespace decay0

#endif // BXDECAY0_FUNBETA_1FU_H

// Local Variables: --
// mode: c++ --
// End: --
