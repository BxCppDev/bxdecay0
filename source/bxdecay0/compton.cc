// Ourselves:
#include <bxdecay0/compton.h>

// Standard library:
#include <cmath>

// Third party:
// - GSL:
#include <gsl/gsl_math.h>

// This project:
#include <bxdecay0/i_random.h>
#include <bxdecay0/event.h>
#include <bxdecay0/particle.h>
#include <bxdecay0/compton1.h>

namespace bxdecay0 {

  void decay0_compton(i_random & prng_, event & event_,
                      const double e1_, const double e2_,
                      const double teta1_, const double teta2_,
                      const double phi1_, const double phi2_)
  {
    //static double emass = decay0_emass();
    double pg0[3], pg1[3], pe1[3];
    double phi=phi1_+(phi2_-phi1_)*prng_();
    double ctet1=1.;
    if (teta1_ != 0.) ctet1=std::cos(teta1_);
    double  ctet2=-1.;
    if (teta2_ != M_PI) ctet2=std::cos(teta2_);
    double ctet=ctet1+(ctet2-ctet1)*prng_();
    double stet=sqrt(1.-ctet*ctet);
    double E=e1_;
    if (e1_ != e2_) E=e1_+(e2_-e1_)*prng_();
    double p=E;
    pg0[0]=p*stet*std::cos(phi);
    pg0[1]=p*stet*std::sin(phi);
    pg0[2]=p*ctet;
    decay0_compton1(prng_,pg0,pg1,pe1);

    particle part;
    part.set_time(0.);

    // Gamma:
    part.set_code(GAMMA);
    part.set_momentum(pg1[0], pg1[1], pg1[2]);
    event_.add_particle(part);

    // Electron:
    part.set_code(ELECTRON);
    part.set_momentum(pe1[0], pe1[1], pe1[2]);
    event_.add_particle(part);

    return;
  }

} // end of namespace bxdecay0
