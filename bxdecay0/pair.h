#ifndef BXDECAY0_PAIR_H
#define BXDECAY0_PAIR_H 1

namespace bxdecay0 {

  class i_random;
  class event;

  // Generation of e+e- pair in zero-approximation to real subroutine for
  // INTERNAL pair creation:
  //    1) energy of e+ is equal to the energy of e-;
  //    2) e+ and e- are emitted in the same direction.
  // Call  :
  //         call pair(Epair,tclev,thlev,tdlev)
  // Input:  epair - kinetic energy of e+e- pair (MeV);
  //         tclev - time of creation of level from which pair will be
  //                 emitted (sec);
  //         thlev - level halflife (sec).
  // Output: tdlev - time of decay of level (sec);
  void decay0_pair(i_random & prng_, event & event_,
                   double epair_, double tclev_, double thlev_,
                   double & tdlev_);

} // end of namespace bxdecay0

#endif // BXDECAY0_PAIR_H

// Local Variables: --
// mode: c++ --
// End: --
