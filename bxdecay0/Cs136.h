#ifndef BXDECAY0_CS136_H
#define BXDECAY0_CS136_H

namespace bxdecay0 {

  class i_random;
  class event;

  void Cs136(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_);

} // end of namespace bxdecay0

#endif // BXDECAY0_CS136_H

// Local Variables: --
// mode: c++ --
// End: --
