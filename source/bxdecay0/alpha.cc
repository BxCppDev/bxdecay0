// Ourselves:
#include <bxdecay0/alpha.h>

// Standard library:
#include <cmath>

// This project:
#include <bxdecay0/i_random.h>
#include <bxdecay0/event.h>

namespace bxdecay0 {

  void decay0_alpha(i_random & prng_, event & event_,
                    double energy_, double tclev_, double thlev_,
                    double & tdlev_)
  {
    randomize_particle(prng_, event_,
                       ALPHA,
                       energy_, energy_,
                       0., M_PI,
                       0., 2.*M_PI,
                       tclev_, thlev_,
                       tdlev_);
    return;
  }

} // end of namespace bxdecay0
