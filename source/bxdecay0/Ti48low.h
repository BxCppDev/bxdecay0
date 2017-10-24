#ifndef BXDECAY0_TI48LOW_H
#define BXDECAY0_TI48LOW_H

namespace bxdecay0 {

  class i_random;
  class event;

  void Ti48low(i_random & prng_,
	       event & event_,
	       const int levelkev_);

} // end of namespace bxdecay0

#endif // BXDECAY0_TI48LOW_H

// Local Variables: --
// mode: c++ --
// End: --
