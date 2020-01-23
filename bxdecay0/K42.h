#ifndef BXDECAY0_K42_H
#define BXDECAY0_K42_H

namespace bxdecay0 {

  class i_random;
  class event;

  void K42(i_random & prng_,
	   event & event_,
	   const double tcnuc_,
	   double & tdnuc_);

} // end of namespace bxdecay0

#endif // BXDECAY0_K42_H

// Local Variables: --
// mode: c++ --
// End: --
