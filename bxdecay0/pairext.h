#ifndef BXDECAY0_PAIREXT_H
#define BXDECAY0_PAIREXT_H 1

namespace bxdecay0 {

  class i_random;
  class event;

  // To sample the momentum of initial gamma quantum for PAIREXT1 subroutine
  // and store the momenta of created positron and electron in common/genevent/.
  // Call  :
  //         call pairext(E1,E2,teta1,teta2,phi1,phi2,Z)
  // Input : E1,E2       - range of kinetic energy of gamma (MeV);
  //         teta1,teta2 - range of teta angle (radians);
  //         phi1,phi2   - range of phi  angle (radians);
  //         Z           - atomic number of target nuclei;
  // Output: see description of common/genevent/. Times emission of scattered
  //         e+ and e- are supposed to be 0.
  // VIT, 12.03.1998.
  void decay0_pairext(i_random & prng_,
                      event & event_,
                      double e1_,
                      double e2_,
                      double teta1_,
                      double teta2_,
                      double phi1_,
                      double phi2_,
                      double Z_);

} // end of namespace bxdecay0

#endif // BXDECAY0_PAIREXT_H

// Local Variables: --
// mode: c++ --
// End: --
