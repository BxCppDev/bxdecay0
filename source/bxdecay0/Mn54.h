#ifndef BXDECAY0_MN54_H
#define BXDECAY0_MN54_H

namespace bxdecay0 {

  class i_random;
  class event;

  void Mn54(i_random & prng_,
	    event & event_,
	    const double tcnuc_,
	    double & tdnuc_);

} // end of namespace bxdecay0

#endif // BXDECAY0_MN54_H

// Local Variables: --
// mode: c++ --
// End: --
