#ifndef BXDECAY0_MOLLER_H
#define BXDECAY0_MOLLER_H 1

namespace bxdecay0 {

  class i_random;
  class event;

  /// \brief To sample the momentum of initial electron for MOLLER1 subroutine and store the momenta of scattered electron and delta ray
  // Input : E1,E2       - range of kinetic energy of gamma (MeV);
  //         teta1,teta2 - range of teta angle (radians);
  //         phi1,phi2   - range of phi  angle (radians);
  //         dcute       - lower energy threshold for emitted delta ray (MeV);
  // Output: see description of primary_event. Times emission of scattered
  //         electron and delta ray are supposed to be 0.
  // VIT, 11.12.1995.
  void decay0_moller(i_random & prng_, event & event_,
                     double E1_, double E2_,
                     double teta1_, double teta2_,
                     double phi1_, double phi2_,
                     double dcute_);

} // end of namespace bxdecay0

#endif // BXDECAY0_MOLLER_H

// Local Variables: --
// mode: c++ --
// End: --
