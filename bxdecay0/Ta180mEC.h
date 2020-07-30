#ifndef BXDECAY0_TA180MEC_H
#define BXDECAY0_TA180MEC_H

namespace bxdecay0 {

  class i_random;
  class event;

  void Ta180mEC(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_);

} // end of namespace bxdecay0

#endif // BXDECAY0_TA180MEC_H

// Local Variables: --
// mode: c++ --
// End: --
