#ifndef BXDECAY0_K40_H
#define BXDECAY0_K40_H

namespace bxdecay0 {

  class i_random;
  class event;

  void K40(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_);

} // end of namespace bxdecay0

#endif // BXDECAY0_K40_H

// Local Variables: --
// mode: c++ --
// End: --
