#ifndef BXDECAY0_NUCLTRANSK_H
#define BXDECAY0_NUCLTRANSK_H

// This project:
#include <bxdecay0/common.h>

namespace bxdecay0 {

  class i_random;
  class event;

  // Subroutine nucltransK choise one of the three concurent processes
  // by which the transition from one nuclear state to another is
  // occured: gamma-ray emission, internal conversion and internal
  // pair creation. Conversion electrons are emitted only with one fixed energy
  // (usually with Egamma-E(K)_binding_energy).
  // Call  : common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100)
  //         call nucltransK(Egamma,Ebinde,conve,convp,tclev,thlev,tdlev)
  // Input : Egamma - gamma-ray energy (MeV) [=difference in state energies];
  //         Ebinde - binding energy of electron (MeV);
  //         conve  - internal electron conversion coefficient [=Nelectron/Ngamma];
  //         convp  - pair conversion coefficient [=Npair/Ngamma];
  //         tclev  - time of creation of level from which particle will be
  //                  emitted (sec);
  //         thlev  - level halflife (sec).
  // Output: tdlev               - time of decay of level (sec);
  //         tevst               - time of event's start (sec);
  // VIT, 27.07.1992; 15.10.1995.
  void decay0_nucltransK(i_random & prng_, event & event_,
                         const double Egamma_, const double Ebinde_,
                         const double conve_, const double convp_, const double tclev_,
                         const double thlev_, double & tdlev_);

} // end of namespace bxdecay0

#endif // BXDECAY0_NUCLTRANSK_H

// Local Variables: --
// mode: c++ --
// End: --
