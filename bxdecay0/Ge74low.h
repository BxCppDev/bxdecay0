#ifndef BXDECAY0_GE74LOW_H
#define BXDECAY0_GE74LOW_H

namespace bxdecay0 {

  class i_random;
  class event;

  void Ge74low(i_random & prng_,
	       event & event_,
	       const int levelkev_);

} // end of namespace bxdecay0

#endif // BXDECAY0_GE74LOW_H

// Local Variables: --
// mode: c++ --
// End: --
