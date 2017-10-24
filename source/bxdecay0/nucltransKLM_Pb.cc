// Ourselves:
#include <bxdecay0/nucltransKLM_Pb.h>

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

  void decay0_nucltransKLM_Pb(i_random & prng_, event & event_,
                              const double Egamma_,
                              const double EbindeK_, const double conveK_,
                              const double EbindeL_, const double conveL_,
                              const double EbindeM_, const double conveM_,
                              const double convp_,
                              const double tclev_, const double thlev_,
                              double & tdlev_)
  {
    static double emass = decay0_emass();
    double p=(1.+conveK_+conveL_+conveM_+convp_)*prng_();
    if (p <= 1.) {
      decay0_gamma(prng_,event_,Egamma_,tclev_,thlev_,tdlev_);
    } else if (p <= 1.+conveK_) {
      decay0_electron(prng_,event_,Egamma_-EbindeK_,tclev_,thlev_,tdlev_);
      // decay0_gamma(Eprng_,event_,bindeK,tdlev_,0.,tdlev_) // for real time
      // decay0_gamma(prng_,event_,EbindeK_,0.,0.,tdlev_) // for time shift
      // emission of two X rays with E(X1)+E(X2)=EbindeK_ instead of one
      // with E(X)=EbindeK_; probabilities are from ToI'98, Appendix F.5.a (Table 7a).
      // VIT, 4.02.2009.
      double p1=100.*prng_();
      // 73.9% - E(X1)=74 keV, 21.3% - E(X1)=85 keV
      if (p1 <= 73.9) {
        decay0_gamma(prng_,event_,0.074,0.,0.,tdlev_);
        decay0_gamma(prng_,event_,0.014,0.,0.,tdlev_);
      } else if (p1 <= 95.2) {
        decay0_gamma(prng_,event_,0.085,0.,0.,tdlev_);
        decay0_gamma(prng_,event_,0.003,0.,0.,tdlev_);
      }
      // in 4.8% few low energy particles are emitted; they are neglected
    } else if (p <= 1.+conveK_+conveL_) {
      decay0_electron(prng_,event_,Egamma_-EbindeL_,tclev_,thlev_,tdlev_);
      // decay0_gamma(prng_,event_,EbindeL_,tdlev_,0.,tdlev_); // for real time
      decay0_gamma(prng_,event_,EbindeL_,0.,0.,tdlev_); // for time shift
    } else if (p <= 1.+conveK_+conveL_+conveM_) {
      decay0_electron(prng_,event_,Egamma_-EbindeM_,tclev_,thlev_,tdlev_);
      // decay0_gamma(prng_,event_,EbindeM_,tdlev_,0.,tdlev_); // for real time
      decay0_gamma(prng_,event_,EbindeM_,0.,0.,tdlev_); // for time shift
    } else {
      decay0_pair(prng_,event_,Egamma_-2.*emass,tclev_,thlev_,tdlev_);
    }
    return;
  }

} // end of namespace bxdecay0decay0
