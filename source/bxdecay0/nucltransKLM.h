#ifndef BXDECAY0_NUCLTRANSKLM_H
#define BXDECAY0_NUCLTRANSKLM_H

// This project:
#include <bxdecay0/common.h>

namespace bxdecay0 {

  class i_random;
  class event;

  // Subroutine nucltransKLM choises one of the three concurent processes
  // by which the transition from one nuclear state to another is
  // occured: gamma-ray emission, internal conversion and internal
  // pair creation. Conversion electrons are emitted with three fixed energies:
  // Egamma-E(K)_binding_energy, Egamma-E(L)_binding_energy and
  // Egamma-E(M)_binding_energy).
  // Call  : common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100)
  //         call nucltransKLM(Egamma,EbindeK,conveK,EbindeL,conveL,
  //                           EbindeM,conveM,convp,tclev,thlev,tdlev)
  // Input:  Egamma  - gamma-ray energy (MeV) [=difference in state energies];
  //         EbindeK - binding energy of electron (MeV) on K-shell;
  //         conveK  - internal conversion coefficient [=Nelectron/Ngamma] from
  //                   K-shell;
  //         EbindeL - binding energy of electron (MeV) on L-shell;
  //         conveL  - internal conversion coefficient [=Nelectron/Ngamma] from
  //                   L-shell;
  //         EbindeM - binding energy of electron (MeV) on M-shell;
  //         convem  - internal conversion coefficient [=Nelectron/Ngamma] from
  //                   M-shell;
  //         convp   - pair conversion coefficient [=Npair/Ngamma];
  //         tclev   - time of creation of level from which particle will be
  //                   emitted (sec);
  //         thlev   - level halflife (sec).
  // Output: tdlev               - time of decay of level (sec);
  // VIT, 4.01.2007.
  void decay0_nucltransKLM(i_random & prng_, event & event_,
			   const double Egamma_,
			   const double EbindeK_, const double conveK_,
			   const double EbindeL_, const double conveL_,
			   const double EbindeM_, const double conveM_,
			   const double convp_,
			   const double tclev_, const double thlev_,
			   double & tdlev_);

} // end of namespace bxdecay0

#endif // BXDECAY0_NUCLTRANSKLM_H
