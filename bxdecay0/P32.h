#ifndef BXDECAY0_P32_H
#define BXDECAY0_P32_H

namespace bxdecay0 {

  class i_random;
  class event;

  void P32(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_);

} // end of namespace bxdecay0

#endif // BXDECAY0_P32_H

// Local Variables: --
// mode: c++ --
// End: --
