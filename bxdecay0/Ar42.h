#ifndef BXDECAY0_AR42_H
#define BXDECAY0_AR42_H

namespace bxdecay0 {

  class i_random;
  class event;

  void Ar42(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_);

} // end of namespace bxdecay0

#endif // BXDECAY0_AR42_H

// Local Variables: --
// mode: c++ --
// End: --
