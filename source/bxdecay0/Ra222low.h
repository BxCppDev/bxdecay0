#ifndef BXDECAY0_RA222LOW_H
#define BXDECAY0_RA222LOW_H

namespace bxdecay0 {

  class i_random;
  class event;

  void Ra222low(i_random & prng_,
		event & event_,
		const int levelkev_);

} // end of namespace bxdecay0

#endif // BXDECAY0_RA222LOW_H

// Local Variables: --
// mode: c++ --
// End: --
