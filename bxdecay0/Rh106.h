#ifndef BXDECAY0_RH106_H
#define BXDECAY0_RH106_H

namespace bxdecay0 {

  class i_random;
  class event;

  void Rh106(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_);

} // end of namespace bxdecay0

#endif // BXDECAY0_RH106_H

// Local Variables: --
// mode: c++ --
// End: --
