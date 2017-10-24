#ifndef BXDECAY0_TE134_H
#define BXDECAY0_TE134_H

namespace bxdecay0 {

  class i_random;
  class event;

  void Te134(i_random & prng_,
	     event & event_,
	     const double tcnuc_,
	     double & tdnuc_);

} // end of namespace bxdecay0

#endif // BXDECAY0_TE134_H

// Local Variables: --
// mode: c++ --
// End: --
