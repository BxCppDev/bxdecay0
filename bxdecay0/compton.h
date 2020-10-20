#ifndef BXDECAY0_COMPTON_H
#define BXDECAY0_COMPTON_H

namespace bxdecay0 {

  class i_random;
  class event;

  /// \brief To sample the momentum of initial gamma quantum for COMPTON1 subroutine and store the momenta of scattered
  /// gamma and electron in primary_event.
  // Input : E1,E2       - range of kinetic energy of gamma (MeV);
  //         teta1,teta2 - range of teta angle (radians);
  //         phi1,phi2   - range of phi  angle (radians);
  // Output: see description of primary_event. Times emission of scattered
  //         gamma quantum and electron are supposed to be 0.
  // VIT, 11.12.1995.
  void decay0_compton(i_random & prng_,
                      event & event_,
                      double e1_,
                      double e2_,
                      double teta1_,
                      double teta2_,
                      double phi1_,
                      double phi2_);

} // end of namespace bxdecay0

#endif // BXDECAY0_COMPTON_H

// Local Variables: --
// mode: c++ --
// End: --
