#ifndef BXDECAY0_BETA_H
#define BXDECAY0_BETA_H

namespace bxdecay0 {

  class i_random;
  class event;

  /// \brief Subroutine decay0_beta simulates the angles and energy of beta particles emitted in beta decay of nucleus.
  /// The decay is considered as allowed.
  /// Only Coulomb correction to the shape of energy spectrum is taken
  /// into consideration.
  // Input : Qbeta    - beta energy endpoint (MeV; Qbeta>50 eV);
  //         Zdtr     - atomic number of daughter nucleus (Zdtr>0 for e- and
  //                    Zdtr<0 for e+ particles);
  //         tcnuc - time of creation of nucleus (sec);
  //         thnuc - nucleus halflife (sec).
  // Output: tdnuc - time of decay of nucleus (sec);
  // VIT, 30.07.1992; 15.10.1995.
  void decay0_beta(i_random & prng_, event & event_,
                   double Qbeta_, double Zdtr_,
                   double tcnuc_, double thnuc_, double & tdnuc_);

  void decay0_beta(i_random & prng_, event & event_,
                   double tcnuc_, double thnuc_, double & tdnuc_,
                   void * params_);

} // end of namespace bxdecay0

#endif // BXDECAY0_BETA_H

// Local Variables: --
// mode: c++ --
// End: --
