#ifndef BXDECAY0_HF182_H
#define BXDECAY0_HF182_H

namespace bxdecay0 {

  class i_random;
  class event;

  void Hf182(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_);

} // end of namespace bxdecay0

#endif // BXDECAY0_HF182_H

// Local Variables: --
// mode: c++ --
// End: --
