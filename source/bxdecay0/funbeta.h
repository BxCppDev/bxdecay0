#ifndef BXDECAY0_FUNBETA_H
#define BXDECAY0_FUNBETA_H 1

namespace bxdecay0 {

  struct parbeta
  {
    double Zdtr;
    double Qbeta;
  };

  double decay0_funbeta(double energy_, void * params_);

} // end of namespace bxdecay0

#endif // BXDECAY0_FUNBETA_H

// Local Variables: --
// mode: c++ --
// End: --
