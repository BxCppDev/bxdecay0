#ifndef BXDECAY0_BETA_1FU_H
#define BXDECAY0_BETA_1FU_H

namespace bxdecay0 {

  class i_random;
  class event;

  /// \brief Subroutine beta_1fu simulates the angles and energy of beta particles emitted in beta decay of nucleus.
  // The decay is considered as 1st-forbidden
  // unique. Its shape is product of theoretical spectrum shape for allowed
  // decay and two correction factors:
  // 1. theoretical of BJ'1969
  //       cf1(e)=pnu**2+lambda2*pel**2,
  //       where lambda2 is the Coulomb function calculated in BJ'1969,
  //       and pel and pnu are impulses of electron and neutrino:
  //       pel=sqrt(w**2-1), pnu=(Qbeta-e)/emass , w=e/emass+1;
  // 2. empirical correction
  //       cf2(e)=(1+c1/w+c2*w+c3*w**2+c4*w**3).
  // Input : Qbeta       - beta energy endpoint (MeV; Qbeta>50 eV);
  //         Zdtr        - atomic number of daughter nucleus (Zdtr>0 for e- and
  //                       Zdtr<0 for e+ particles);
  //         tcnuc       - time of creation of nucleus (sec);
  //         thnuc       - nucleus halflife (sec);
  //         c1,c2,c3,c4 - coefficients in correction factor to the spectrum
  //                       shape cf2(e)=(1+c1/w+c2*w+c3*w**2+c4*w**3),
  //                       where w=e/emass+1, e - kinetic energy of electron.
  // Output: tdnuc       - time of decay of nucleus (sec);
  // VIT, 24.10.2006.
  void decay0_beta_1fu(i_random & prng_, event & event_,
                       double Qbeta_, double Zdtr_,
                       double tcnuc_, double thnuc_, double & tdnuc_,
                       double c1_, double c2_, double c3_, double c4_);

  void decay0_beta_1fu(i_random & prng_, event & event_,
                       double tcnuc_,double thnuc_, double & tdnuc_,
                       void * params_);

} // end of namespace bxdecay0

#endif // BXDECAY0_BETA_1FU_H

// Local Variables: --
// mode: c++ --
// End: --
