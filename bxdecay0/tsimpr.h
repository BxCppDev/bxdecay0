#ifndef BXDECAY0_TSIMPR_H
#define BXDECAY0_TSIMPR_H 1

// This project:
#include <bxdecay0/common.h>

namespace bxdecay0 {

  // Function decay0_tsimpr calculates the value of integral of function f from a to b
  // with step h using Simpson's formula.
  // (b-a)/h must be equal 2*m where m is integer.
  // Function f must be decribed as external in main program.
  // VIT, DLP KINR, 20.11.1984.
  double decay0_tsimpr(func_type f_, double a_, double b_, double h_, void * params_);

} // end of namespace bxdecay0

#endif // BXDECAY0_TSIMPR_H

// Local Variables: --
// mode: c++ --
// End: --
