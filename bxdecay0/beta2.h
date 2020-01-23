#ifndef BXDECAY0_BETA2_H
#define BXDECAY0_BETA2_H

namespace bxdecay0 {

  class i_random;
  class event;

  /// \brief Subroutine decay0_beta2 simulates the angles and energy of beta particles emitted in beta decay of nucleus.
  // The decay is considered as forbidden;
  // correction factor to the allowed spectrum shape has one of a form,
  // typical for unique k-forbidden spectra:
  // k=1: cf(e)=pel**2+c1*       pnu**2,
  // k=2: cf(e)=pel**4+c1*pel**2*pnu**2+c2*       pnu**4,
  // k=3: cf(e)=pel**6+c1*pel**4*pnu**2+c2*pel**2*pnu**4+c3*       pnu**6,
  // k=4: cf(e)=pel**8+c1*pel**6*pnu**2+c2*pel**4*pnu**4+c3*pel**2*pnu**6+c4*pnu**8,
  // where pel and pnu are impulses of electron and neutrino:
  // pel=sqrt(w**2-1), pnu=(Qbeta-e)/emass , w=e/emass+1.
  // Input : Qbeta       - beta energy endpoint (MeV; Qbeta>50 eV);
  //         Zdtr        - atomic number of daughter nucleus (Zdtr>0 for e- and
  //                       Zdtr<0 for e+ particles);
  //         tcnuc       - time of creation of nucleus (sec);
  //         thnuc       - nucleus halflife (sec);
  //         kf          - degree of forbiddeness for unique spectra;
  //         c1,c2,c3,c4 - coefficients in correction factor to the allowed spectrum
  //                       shape - see above.
  // Output: tdnuc               - time of decay of nucleus (sec);
  // VIT, 30.07.1992; 15.10.1995; 31.03.2006.
  void decay0_beta2(i_random & prng_, event & event_,
                    double Qbeta_, double Zdtr_,
                    double tcnuc_, double thnuc_, double & tdnuc_,
                    int kf_,
                    double c1_, double c2_, double c3_, double c4_);

  void decay0_beta2(i_random & prng_, event & event_,
                    double tcnuc,double thnuc,
                    double & tdnuc,
                    void * params);

} // end of namespace bxdecay0

#endif // BXDECAY0_BETA2_H

// Local Variables: --
// mode: c++ --
// End: --
