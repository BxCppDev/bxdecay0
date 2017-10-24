#ifndef BXDECAY0_AR39_H
#define BXDECAY0_AR39_H

namespace bxdecay0 {

  class i_random;
  class event;

  void Ar39(i_random & prng_,
	    event & event_,
            const double tcnuc_,
	    double & tdnuc_);

} // end of namespace bxdecay0

#endif // BXDECAY0_AR39_H

// Local Variables: --
// mode: c++ --
// End: --
