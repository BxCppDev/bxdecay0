#ifndef BXDECAY0_PBATSHELL_H
#define BXDECAY0_PBATSHELL_H

namespace bxdecay0 {

  class i_random;
  class event;

  void PbAtShell(i_random & prng_,
                 event & event_,
                 const int KLMenergy_,
                 const double tclev_,
                 const double thlev_,
                 double & tdlev_);

} // end of namespace bxdecay0

#endif // BXDECAY0_PBATSHELL_H

// Local Variables: --
// mode: c++ --
// End: --
