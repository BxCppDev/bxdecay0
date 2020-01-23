#ifndef BXDECAY0_KR82LOW_H
#define BXDECAY0_KR82LOW_H

namespace bxdecay0 {

  class i_random;
  class event;

  void Kr82low(i_random & prng_,
	       event & event_,
	       const int levelkev_);

} // end of namespace bxdecay0

#endif // BXDECAY0_KR82LOW_H

// Local Variables: --
// mode: c++ --
// End: --
