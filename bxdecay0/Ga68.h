#ifndef BXDECAY0_GA68_H
#define BXDECAY0_GA68_H

namespace bxdecay0 {

  class i_random;
  class event;

  void Ga68(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_);

} // end of namespace bxdecay0

#endif // BXDECAY0_GA68_H

// Local Variables: --
// mode: c++ --
// End: --
