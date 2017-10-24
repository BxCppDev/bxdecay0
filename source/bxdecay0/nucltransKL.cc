// Ourselves:
#include <bxdecay0/nucltransKL.h>

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

  void decay0_nucltransKL(i_random & prng_, event & event_,
                          const double Egamma_,const double EbindeK_,const double conveK_,
                          const double EbindeL_,const double conveL_,const double convp_,
                          const double tclev_, const double thlev_,double & tdlev_)
  {
    static double emass = decay0_emass();
    double p=(1.+conveK_+conveL_+convp_)*prng_();
    if(p <= 1.) {
      decay0_gamma(prng_,event_,Egamma_,tclev_,thlev_,tdlev_);
    } else if(p <= 1.+conveK_) {
      decay0_electron(prng_,event_,Egamma_-EbindeK_,tclev_,thlev_,tdlev_);
      // decay0_gamma(prng_,event_,EbindeK_,tdlev_,0.,tdlev_); // for real time
      decay0_gamma(prng_,event_,EbindeK_,0.,0.,tdlev_); // for time shift
    } else if(p <= 1.+conveK_+conveL_) {
      decay0_electron(prng_,event_,Egamma_-EbindeL_,tclev_,thlev_,tdlev_);
      //decay0_gamma(prng_,event_,EbindeL_,tdlev_,0.,tdlev_); // for real time
      decay0_gamma(prng_,event_,EbindeL_,0.,0.,tdlev_); // for time shift
    } else {
      decay0_pair(prng_,event_,Egamma_-2.*emass,tclev_,thlev_,tdlev_);
    }
    return;
  }

} // end of namespace bxdecay0
