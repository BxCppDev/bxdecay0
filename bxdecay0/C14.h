#ifndef BXDECAY0_C14_H
#define BXDECAY0_C14_H

namespace bxdecay0 {

  class i_random;
  class event;

  void C14(i_random & prng_,
	   event & event_,
	   const double tcnuc_,
	   double & tdnuc_);

} // end of namespace bxdecay0

#endif // BXDECAY0_C14_H

// Local Variables: --
// mode: c++ --
// End: --
