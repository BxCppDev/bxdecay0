#ifndef BXDECAY0_AT214_H
#define BXDECAY0_AT214_H

namespace bxdecay0 {

  class i_random;
  class event;

  void At214(i_random & prng_,
	     event & event_,
	     const double tcnuc_,
	     double & tdnuc_);

} // end of namespace bxdecay0

#endif // BXDECAY0_AT214_H

// Local Variables: --
// mode: c++ --
// End: --
