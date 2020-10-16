#ifndef BXDECAY0_MOLLER1_H
#define BXDECAY0_MOLLER1_H 1

namespace bxdecay0 {

  class i_random;

  /// \brief Simulates electron-electron Moller scattering.
  //         dimension pe0(3),pe1(3),pe2(3)
  // Input : pe0   - momentum of initial electron (in MRS);
  //         dcute - minimal energy of delta ray to be borned;
  //                 if energy of initial electron < dcute/2
  //                 delta rays are not produced;
  // Output: pe1   - momentum of 1 scattered electron (in MRS);
  //         pe2   - momentum of 2 scattered electron (in MRS).
  // VIT, 07.12.1995 from GEANT subroutine GDRAY by D.Ward, L.Urban.
  void decay0_moller1(i_random & prng_, const double dcute_, const double * pe0_, double * pe1_, double * pe2_);

} // end of namespace bxdecay0

#endif // BXDECAY0_MOLLER1_H

// Local Variables: --
// mode: c++ --
// End: --
