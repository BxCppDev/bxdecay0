// Ourselves:
#include <bxdecay0/nucltransKLM.h>

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

  void decay0_nucltransKLM(i_random & prng_, event & event_,
                           const double Egamma_,
                           const double EbindeK_, const double conveK_,
                           const double EbindeL_, const double conveL_,
                           const double EbindeM_, const double conveM_,
                           const double convp_,
                           const double tclev_, const double thlev_,
                           double & tdlev_)
  {
    static double emass = decay0_emass();
    double pK = 1. + conveK_;
    double pL = pK + conveL_;
    double pM = pL + conveM_;
    double pp = pM + convp_;
    double p = pp * prng_();
    bool debug = false;
    if (debug) std::cerr << "genbb::decay0::decay0_nucltransKLM: Egamma_=" << Egamma_ << std::endl;
    if (p <= 1.) {
      if (debug) std::cerr << "genbb::decay0::decay0_nucltransKLM: " << "gamma" << std::endl;
      decay0_gamma(prng_,event_,Egamma_,tclev_,thlev_,tdlev_);
    } else if (p <= pK) {
      decay0_electron(prng_,event_,Egamma_-EbindeK_,tclev_,thlev_,tdlev_);
      // decay0_gamma(prng_,event_,EbindeK_,tdlev_,0.,tdlev_); //  for real time
      decay0_gamma(prng_,event_,EbindeK_,0.,0.,tdlev_); //  for time shift
      if (debug) std::cerr << "genbb::decay0::decay0_nucltransKLM: " << "eK+gamma" << std::endl;
    } else if (p <= pL) {
      decay0_electron(prng_,event_,Egamma_-EbindeL_,tclev_,thlev_,tdlev_);
      // decay0_gamma(prng_,event_,EbindeL_,tdlev_,0.,tdlev_); // for real time
      decay0_gamma(prng_,event_,EbindeL_,0.,0.,tdlev_); //  for time shift
      if (debug) std::cerr << "genbb::decay0::decay0_nucltransKLM: " << "eL+gamma" << std::endl;
    } else if (p <= pM) {
      decay0_electron(prng_,event_,Egamma_-EbindeM_,tclev_,thlev_,tdlev_);
      // decay0_gamma(prng_,event_,EbindeM_,tdlev_,0.,tdlev_); // for real time
      decay0_gamma(prng_,event_,EbindeM_,0.,0.,tdlev_); //  for time shift
      if (debug) std::cerr << "genbb::decay0::decay0_nucltransKLM: " << "eM+gamma" << std::endl;
    } else {
      decay0_pair(prng_,event_,Egamma_-2.*emass,tclev_,thlev_,tdlev_);
      if (debug) std::cerr << "genbb::decay0::decay0_nucltransKLM: " << "pair" << std::endl;
    }
    return;
  }

} // end of namespace bxdecay0
