#ifndef BXDECAY0_PO212_H
#define BXDECAY0_PO212_H

namespace bxdecay0 {

  class i_random;
  class event;

  void Po212(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_);

} // end of namespace bxdecay0

#endif // BXDECAY0_PO212_H

// Local Variables: --
// mode: c++ --
// End: --
