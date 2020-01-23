#ifndef BXDECAY0_TH234_H
#define BXDECAY0_TH234_H

namespace bxdecay0 {

  class i_random;
  class event;

  void Th234(i_random & prng_,
	     event & event_,
	     const double tcnuc_,
	     double & tdnuc_);

} // end of namespace bxdecay0

#endif // BXDECAY0_TH234_H

// Local Variables: --
// mode: c++ --
// End: --
