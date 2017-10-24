// Ourselves:
#include <bxdecay0/pairext.h>

// Standard library:
#include <cmath>

// Third party:
// - GSL:
#include <gsl/gsl_math.h>

// This project:
#include <bxdecay0/i_random.h>
#include <bxdecay0/event.h>
#include <bxdecay0/particle.h>
#include <bxdecay0/particle_utils.h>
#include <bxdecay0/pairext1.h>

namespace bxdecay0 {

  void decay0_pairext(i_random & prng_, event & event_,
                      double e1_,double e2_,
                      double teta1_,double teta2_,
                      double phi1_,double phi2_,double Z_)
  {
    double pg0[3], pe1[3], pe2[3];
    double phi=phi1_+(phi2_-phi1_)*prng_();
    double ctet1=1.;
    if (teta1_ != 0.) ctet1=std::cos(teta1_);
    double ctet2=-1.;
    if (teta2_ != M_PI) ctet2=std::cos(teta2_);
    double ctet=ctet1+(ctet2-ctet1)*prng_();
    double stet=std::sqrt(1.-ctet*ctet);
    double E=e1_;
    if (e1_ != e2_) E=e1_+(e2_-e1_)*prng_();
    double p=E;
    pg0[0]=p*stet*std::cos(phi);
    pg0[1]=p*stet*std::sin(phi);
    pg0[2]=p*ctet;
    decay0_pairext1(prng_, Z_, pg0, pe1, pe2);
    // to fix GEANT numbers of emitted particles but to select the momentum
    // randomly
    if(prng_() < 0.5) {
      double x1=pe1[0];
      double x2=pe1[1];
      double x3=pe1[2];
      pe1[0]=pe2[0];
      pe1[1]=pe2[1];
      pe1[2]=pe2[2];
      pe2[0]=x1;
      pe2[1]=x2;
      pe2[2]=x3;
    }
    particle part;
    // Positron:
    part.set_code(POSITRON);
    part.set_time(0.);
    part.set_momentum(pe1[0], pe1[1], pe1[2]);
    event_.add_particle(part);

    // Electron:
    part.set_code(ELECTRON);
    part.set_time(0.);
    part.set_momentum(pe2[0], pe2[1], pe2[2]);
    event_.add_particle(part);

    return;
  }

} // end of namespace bxdecay0
