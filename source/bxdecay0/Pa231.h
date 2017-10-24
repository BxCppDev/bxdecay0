#ifndef BXDECAY0_PA231_H
#define BXDECAY0_PA231_H

namespace bxdecay0 {

  class i_random;
  class event;

  void Pa231(i_random & prng_,
	     event & event_,
	     const double tcnuc_,
	     double & tdnuc_);

} // end of namespace bxdecay0

#endif // BXDECAY0_PA231_H

// Local Variables: --
// mode: c++ --
// End: --
