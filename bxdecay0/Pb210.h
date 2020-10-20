#ifndef BXDECAY0_PB210_H
#define BXDECAY0_PB210_H

namespace bxdecay0 {

  class i_random;
  class event;

  void Pb210(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_);

} // end of namespace bxdecay0

#endif // BXDECAY0_PB210_H

// Local Variables: --
// mode: c++ --
// End: --
