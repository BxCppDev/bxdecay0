#ifndef BXDECAY0_COMPTON1_H
#define BXDECAY0_COMPTON1_H

namespace bxdecay0 {

  class i_random;

  /// \brief Simulates photon-electron Compton scattering.
  // Call  :
  //         dimension pg0(3),pg1(3),pe1(3)
  //         call compton1(pg0,pg1,pe1)
  // Input : pg0 - momentum of initial gamma quantum (in MRS);
  // Output: pg1 - momentum of scattered gamma quantum (in MRS);
  //         pe1 - momentum of recoil electron (in MRS).
  //
  // VIT, 07.12.1995 from GEANT subroutine GCOMP by G.Patrick, L.Urban.
  void decay0_compton1(i_random & prng_,
                       const double * pg0_,
                       double * pg1_, double * pe1_);

} // end of namespace bxdecay0

#endif // BXDECAY0_COMPTON1_H

// Local Variables: --
// mode: c++ --
// End: --
