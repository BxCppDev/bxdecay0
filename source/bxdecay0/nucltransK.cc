// Ourselves:
#include <bxdecay0/nucltransK.h>

// Standard library:
#include <cmath>

// Third party:
// - GSL:
#include <gsl/gsl_math.h>
// nucltransK.cc

// This project:
#include <bxdecay0/i_random.h>
#include <bxdecay0/event.h>
#include <bxdecay0/particle.h>
#include <bxdecay0/particle_utils.h>
#include <bxdecay0/gamma.h>
#include <bxdecay0/pair.h>
#include <bxdecay0/electron.h>

namespace bxdecay0 {

  void decay0_nucltransK(i_random & prng_, event & event_,
                         const double Egamma_,const double Ebinde_,
                         const double conve_,const double convp_,const double tclev_,
                         const double thlev_,double & tdlev_)
  {
    static double emass = decay0_emass();
    double p=(1.+conve_+convp_)*prng_();
    if (p <= 1.)  {
      decay0_gamma(prng_,event_,Egamma_,tclev_,thlev_,tdlev_);
    } else if (p <= 1.+conve_)  {
      decay0_electron(prng_,event_,Egamma_-Ebinde_,tclev_,thlev_,tdlev_);
      //      decay0_gamma(Ebinde_,tdlev_,0.,tdlev_); // for real time
      decay0_gamma(prng_,event_,Ebinde_,0.,0.,tdlev_); // for time shift
    } else {
      decay0_pair(prng_,event_,Egamma_-2.*emass,tclev_,thlev_,tdlev_);
    }
    return;
  }

} // end of namespace bxdecay0
