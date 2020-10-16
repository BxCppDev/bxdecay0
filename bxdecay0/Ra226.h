#ifndef BXDECAY0_RA226_H
#define BXDECAY0_RA226_H

namespace bxdecay0 {

  class i_random;
  class event;

  void Ra226(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_);

} // end of namespace bxdecay0

#endif // BXDECAY0_RA226_H

// Local Variables: --
// mode: c++ --
// End: --
