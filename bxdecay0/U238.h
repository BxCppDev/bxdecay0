#ifndef BXDECAY0_U238_H
#define BXDECAY0_U238_H

namespace bxdecay0 {

  class i_random;
  class event;

  void U238(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_);

} // end of namespace bxdecay0

#endif // BXDECAY0_U238_H

// Local Variables: --
// mode: c++ --
// End: --
