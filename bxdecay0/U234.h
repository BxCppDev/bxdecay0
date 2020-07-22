#ifndef BXDECAY0_U234_H
#define BXDECAY0_U234_H

namespace bxdecay0 {

  class i_random;
  class event;

  void U234(i_random & prng_,
             event & event_,
             const double tcnuc_,
             double & tdnuc_);

} // end of namespace bxdecay0

#endif // BXDECAY0_U234_H

// Local Variables: --
// mode: c++ --
// End: --
