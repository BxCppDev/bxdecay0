#ifndef BXDECAY0_SC48_H
#define BXDECAY0_SC48_H

namespace bxdecay0 {

  class i_random;
  class event;

  void Sc48(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_);

} // end of namespace bxdecay0

#endif // BXDECAY0_SC48_H

// Local Variables: --
// mode: c++ --
// End: --
