#ifndef BXDECAY0_RB87_H
#define BXDECAY0_RB87_H

namespace bxdecay0 {

  class i_random;
  class event;

  void Rb87(i_random & prng_,
	    event & event_,
	    const double tcnuc_,
	    double & tdnuc_);

} // end of namespace bxdecay0

#endif // BXDECAY0_RB87_H

// Local Variables: --
// mode: c++ --
// End: --
