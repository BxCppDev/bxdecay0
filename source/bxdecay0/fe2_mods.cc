// Ourselves:
#include <bxdecay0/fe2_mods.h>

// Standard library:
#include <cmath>

// Third party:
// - GSL:
#include <gsl/gsl_math.h>

// This project:
#include <bxdecay0/bb.h>
#include <bxdecay0/particle.h>
#include <bxdecay0/particle_utils.h>
#include <bxdecay0/fermi.h>

namespace bxdecay0 {

  double decay0_fe2_mod4(double e2_, void * params_)
  {
    static double emass = decay0_emass();
    const bbpars * pars = static_cast<const bbpars *>(params_);
    const double & Zdbb = pars->Zd;
    const double & e0   = pars->e0;
    const double & e1   = pars->e1;
    if (e2_ > e0 - e1) return 0.0;
    double p2 = std::sqrt(e2_*(e2_+2.*emass));
    return (e2_ + emass) * p2 * bxdecay0::decay0_fermi(Zdbb,e2_)
      * gsl_pow_5(e0-e1-e2_);
  }

  double decay0_fe2_mod5(double e2_, void * params_)
  {
    static double emass = decay0_emass();
    const bbpars * pars = static_cast<const bbpars *>(params_);
    const double & Zdbb = pars->Zd;
    const double & e0   = pars->e0;
    const double & e1   = pars->e1;
    if (e2_ > e0 - e1) return 0.0;
    double p2 = std::sqrt(e2_*(e2_+2.*emass));
    return (e2_ + emass) * p2 * bxdecay0::decay0_fermi(Zdbb,e2_)
      * (e0-e1-e2_);
  }

  double decay0_fe2_mod6(double e2_, void * params_)
  {
    static double emass = decay0_emass();
    const bbpars * pars = static_cast<const bbpars *>(params_);
    const double & Zdbb = pars->Zd;
    const double & e0   = pars->e0;
    const double & e1   = pars->e1;
    if (e2_ > e0 - e1) return 0.0;
    double p2 = std::sqrt(e2_*(e2_+2.*emass));
    return (e2_ + emass) * p2 * bxdecay0::decay0_fermi(Zdbb,e2_)
      * gsl_pow_3(e0-e1-e2_);
  }

  double decay0_fe2_mod8(double e2_, void * params_)
  {
    static double emass = decay0_emass();
    const bbpars * pars = static_cast<const bbpars *>(params_);
    const double & Zdbb = pars->Zd;
    const double & e0   = pars->e0;
    const double & e1   = pars->e1;
    if (e2_ > e0 - e1) return 0.0;
    double p2 = std::sqrt(e2_*(e2_+2.*emass));
    return (e2_+emass) * p2 * bxdecay0::decay0_fermi(Zdbb,e2_)
      * gsl_pow_7(e0-e1-e2_) * gsl_pow_2(e1-e2_);
  }

  double decay0_fe2_mod13(double e2_, void * params_)
  {
    static double emass = decay0_emass();
    const bbpars * pars = static_cast<const bbpars *>(params_);
    const double & Zdbb = pars->Zd;
    const double & e0   = pars->e0;
    const double & e1   = pars->e1;
    if (e2_ > e0 - e1) return 0.0;
    double p2 = std::sqrt(e2_*(e2_+2.*emass));
    return (e2_+emass) * p2 * bxdecay0::decay0_fermi(Zdbb,e2_)
      * gsl_pow_7(e0-e1-e2_);
  }

  double decay0_fe2_mod14(double e2_, void * params_)
  {
    static double emass = decay0_emass();
    const bbpars * pars = static_cast<const bbpars *>(params_);
    const double & Zdbb = pars->Zd;
    const double & e0   = pars->e0;
    const double & e1   = pars->e1;
    if (e2_ > e0 - e1) return 0.0;
    double p2 = std::sqrt(e2_*(e2_+2.*emass));
    return (e2_+emass) * p2*bxdecay0::decay0_fermi(Zdbb,e2_)
      * gsl_pow_2(e0-e1-e2_);
  }

  double decay0_fe2_mod15(double e2_, void * params_)
  {
    static double emass = decay0_emass();
    const bbpars * pars = static_cast<const bbpars *>(params_);
    const double & Zdbb = pars->Zd;
    const double & e0   = pars->e0;
    const double & e1   = pars->e1;
    if (e2_ > e0 - e1) return 0.0;
    double p2 = std::sqrt(e2_*(e2_+2.*emass));
    return (e2_+emass) * p2 * bxdecay0::decay0_fermi(Zdbb,e2_)
      * gsl_pow_5(e0-e1-e2_)
      * (9. * gsl_pow_2(e0-e1-e2_) + 21. * gsl_pow_2(e2_-e1));
  }

  double decay0_fe2_mod16(double e2_, void * params_)
  {
    static double emass = decay0_emass();
    const bbpars * pars = static_cast<const bbpars *>(params_);
    const double & Zdbb = pars->Zd;
    const double & e0   = pars->e0;
    const double & e1   = pars->e1;
    if (e2_ > e0 - e1) return 0.0;
    double p2 = std::sqrt(e2_*(e2_+2.*emass));
    return (e2_+emass) * p2 * bxdecay0::decay0_fermi(Zdbb,e2_)
      * gsl_pow_5(e0-e1-e2_) * gsl_pow_2(e2_-e1);
  }

} // end of namespace bxdecay0
