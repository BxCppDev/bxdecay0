#ifndef BXDECAY0_BETA1_H
#define BXDECAY0_BETA1_H

namespace bxdecay0 {

  class i_random;
  class event;

  /// \brief Subroutine decay0_beta1 simulates the angles and energy of beta particles emitted in beta decay of nucleus.
  // The decay is considered as forbidden;
  // correction factor to the allowed spectrum shape has a form
  // typical for empirical corrections:
  // cf(e)=(1+c1/w+c2*w+c3*w**2+c4*w**3), w=e/emass+1.
  // Input : Qbeta       - beta energy endpoint (MeV; Qbeta>50 eV);
  //         Zdtr        - atomic number of daughter nucleus (Zdtr>0 for e- and
  //                       Zdtr<0 for e+ particles);
  //         tcnuc       - time of creation of nucleus (sec);
  //         thnuc       - nucleus halflife (sec);
  //         c1,c2,c3,c4 - coefficients in correction factor to the allowed spectrum
  //                       shape cf(e)=(1+c1/w+c2*w+c3*w**2+c4*w**3),
  //                       where w=e/emass+1, e - kinetic energy of electron.               .
  // Output: tdnuc               - time of decay of nucleus (sec);
  // VIT, 30.07.1992; 15.10.1995; 31.03.2006.
  void decay0_beta1(i_random & prng_, event & event_,
                    double Qbeta_, double Zdtr_,
                    double tcnuc_, double thnuc_, double & tdnuc_,
                    double c1_, double c2_, double c3_, double c4_);

  void decay0_beta1(i_random & prng_, event & event_,
                    double tcnuc_, double thnuc_,
                    double & tdnuc_,
                    void * params_);

} // end of namespace bxdecay0

#endif // BXDECAY0_BETA1_H

// Local Variables: --
// mode: c++ --
// End: --
