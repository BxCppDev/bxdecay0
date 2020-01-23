#ifndef BXDECAY0_GD146_H
#define BXDECAY0_GD146_H

namespace bxdecay0 {

  class i_random;
  class event;

  void Gd146(i_random & prng_,
	     event & event_,
             const double tcnuc_,
             double & tdnuc_);

} // end of namespace bxdecay0

#endif // BXDECAY0_GD146_H

// Local Variables: --
// mode: c++ --
// End: --
