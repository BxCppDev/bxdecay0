#ifndef BXDECAY0_CO60_H
#define BXDECAY0_CO60_H

namespace bxdecay0 {

  class i_random;
  class event;

  void Co60(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_);

} // end of namespace bxdecay0

#endif // BXDECAY0_CO60_H

// Local Variables: --
// mode: c++ --
// End: --
