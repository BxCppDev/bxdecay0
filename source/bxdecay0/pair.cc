// Ourselves:
#include <bxdecay0/pair.h>

// Standard library:
#include <cmath>

// This project:
#include <bxdecay0/i_random.h>
#include <bxdecay0/event.h>

namespace bxdecay0 {


  void decay0_pair(i_random & prng_, event & event_,
                   double epair_, double tclev_, double thlev_,
                   double & tdlev_)
  {
    double phi=2.*M_PI*prng_();
    double ctet=-1.+2.*prng_();
    double teta=std::acos(ctet);
    double E=0.5*epair_;
    randomize_particle(prng_,event_,ELECTRON,E,E,teta,teta,phi,phi,tclev_,thlev_,tdlev_);
    randomize_particle(prng_,event_,POSITRON,E,E,teta,teta,phi,phi,    0.,    0.,tdlev_); // for time shift
    return;
  }

} // end of namespace bxdecay0
