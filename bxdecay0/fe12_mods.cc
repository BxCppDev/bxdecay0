// Copyright 1995-2016 V.I. Tretyak
// Copyright 2011-2017 F. Mauger
//
// This program is free software: you  can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free  Software Foundation, either  version 3 of the  License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

// Ourselves:
#include <bxdecay0/fe12_mods.h>

// Standard library:
#include <cmath>

// Third party:
// - GSL:
#include <gsl/gsl_math.h>

// This project:
#include <bxdecay0/bb.h>
#include <bxdecay0/fermi.h>
#include <bxdecay0/particle.h>
#include <bxdecay0/particle_utils.h>
#include <bxdecay0/utils.h>

namespace bxdecay0 {

  double decay0_fe12_mod4(double e2_, void * params_)
  {
    /// TRACE static bool trace = is_trace("fe12");
    static double emass = decay0_emass();
    const bbpars * pars = static_cast<const bbpars *>(params_);
    const double & Zd   = pars->Zd;
    const double & e0   = pars->e0;
    const double & e1   = pars->e1;
    if (e2_ > e0 - e1) {
      return 0.0;
    }
    /// TRACE if (trace) std::cerr << "[trace] bxdecay0::decay0_fe12_mod4: e0 = " << e0 << std::endl;
    /// TRACE if (trace) std::cerr << "[trace] bxdecay0::decay0_fe12_mod4: e1 = " << e1 << std::endl;
    /// TRACE if (trace) std::cerr << "[trace] bxdecay0::decay0_fe12_mod4: e2 = " << e2_ << std::endl;
    /// TRACE if (trace) std::cerr << "[trace] bxdecay0::decay0_fe12_mod4: Zd = " << Zd << std::endl;
    double p1 = std::sqrt(e1 * (e1 + 2. * emass));
    double p2 = std::sqrt(e2_ * (e2_ + 2. * emass));
    /// TRACE if (trace) std::cerr << "[trace] bxdecay0::decay0_fe12_mod4: p1 = " << p1 << std::endl;
    /// TRACE if (trace) std::cerr << "[trace] bxdecay0::decay0_fe12_mod4: p2 = " << p2 << std::endl;
    double f1 = bxdecay0::decay0_fermi(Zd, e1);
    /// TRACE if (trace) std::cerr << "[trace] bxdecay0::decay0_fe12_mod4: f1 = " << f1 << std::endl;
    double res = (e1 + emass) * p1 * bxdecay0::decay0_fermi(Zd, e1) * (e2_ + emass) * p2
                 * bxdecay0::decay0_fermi(Zd, e2_) * gsl_pow_5(e0 - e1 - e2_);
    /// TRACE if (trace) std::cerr << "[trace] bxdecay0::decay0_fe12_mod4: res = " << res << std::endl;
    return res;
  }

  double decay0_fe12_mod5(double e2_, void * params_)
  {
    static double emass = decay0_emass();
    const bbpars * pars = static_cast<const bbpars *>(params_);
    const double & Zd   = pars->Zd;
    const double & e0   = pars->e0;
    const double & e1   = pars->e1;
    if (e2_ > e0 - e1) {
      return 0.0;
    }
    double p1 = std::sqrt(e1 * (e1 + 2. * emass));
    double p2 = std::sqrt(e2_ * (e2_ + 2. * emass));
    return (e1 + emass) * p1 * bxdecay0::decay0_fermi(Zd, e1) * (e2_ + emass) * p2 * bxdecay0::decay0_fermi(Zd, e2_)
           * (e0 - e1 - e2_);
  }

  double decay0_fe12_mod6(double e2_, void * params_)
  {
    static double emass = decay0_emass();
    const bbpars * pars = static_cast<const bbpars *>(params_);
    const double & Zd   = pars->Zd;
    const double & e0   = pars->e0;
    const double & e1   = pars->e1;
    if (e2_ > e0 - e1) {
      return 0.0;
    }
    double p1 = std::sqrt(e1 * (e1 + 2. * emass));
    double p2 = std::sqrt(e2_ * (e2_ + 2. * emass));
    return (e1 + emass) * p1 * bxdecay0::decay0_fermi(Zd, e1) * (e2_ + emass) * p2 * bxdecay0::decay0_fermi(Zd, e2_)
           * gsl_pow_3(e0 - e1 - e2_);
  }

  double decay0_fe12_mod8(double e2_, void * params_)
  {
    static double emass = decay0_emass();
    const bbpars * pars = static_cast<const bbpars *>(params_);
    const double & Zd   = pars->Zd;
    const double & e0   = pars->e0;
    const double & e1   = pars->e1;
    if (e2_ > e0 - e1) {
      return 0.0;
    }
    double p1 = std::sqrt(e1 * (e1 + 2. * emass));
    double p2 = std::sqrt(e2_ * (e2_ + 2. * emass));
    return (e1 + emass) * p1 * bxdecay0::decay0_fermi(Zd, e1) * (e2_ + emass) * p2 * bxdecay0::decay0_fermi(Zd, e2_)
           * gsl_pow_7(e0 - e1 - e2_) * gsl_pow_2(e1 - e2_);
  }

  double decay0_fe12_mod13(double e2_, void * params_)
  {
    static double emass = decay0_emass();
    const bbpars * pars = static_cast<const bbpars *>(params_);
    const double & Zd   = pars->Zd;
    const double & e0   = pars->e0;
    const double & e1   = pars->e1;
    if (e2_ > e0 - e1) {
      return 0.0;
    }
    double p1 = std::sqrt(e1 * (e1 + 2. * emass));
    double p2 = std::sqrt(e2_ * (e2_ + 2. * emass));
    return (e1 + emass) * p1 * bxdecay0::decay0_fermi(Zd, e1) * (e2_ + emass) * p2 * bxdecay0::decay0_fermi(Zd, e2_)
           * gsl_pow_7(e0 - e1 - e2_);
  }

  double decay0_fe12_mod14(double e2_, void * params_)
  {
    static double emass = decay0_emass();
    const bbpars * pars = static_cast<const bbpars *>(params_);
    const double & Zd   = pars->Zd;
    const double & e0   = pars->e0;
    const double & e1   = pars->e1;
    if (e2_ > e0 - e1) {
      return 0.0;
    }
    double p1 = std::sqrt(e1 * (e1 + 2. * emass));
    double p2 = std::sqrt(e2_ * (e2_ + 2. * emass));
    return (e1 + emass) * p1 * bxdecay0::decay0_fermi(Zd, e1) * (e2_ + emass) * p2 * bxdecay0::decay0_fermi(Zd, e2_)
           * gsl_pow_2(e0 - e1 - e2_);
  }

  double decay0_fe12_mod15(double e2_, void * params_)
  {
    static double emass = decay0_emass();
    const bbpars * pars = static_cast<const bbpars *>(params_);
    const double & Zd   = pars->Zd;
    const double & e0   = pars->e0;
    const double & e1   = pars->e1;
    if (e2_ > e0 - e1) {
      return 0.0;
    }
    double p1 = std::sqrt(e1 * (e1 + 2. * emass));
    double p2 = std::sqrt(e2_ * (e2_ + 2. * emass));
    return (e1 + emass) * p1 * bxdecay0::decay0_fermi(Zd, e1) * (e2_ + emass) * p2 * bxdecay0::decay0_fermi(Zd, e2_)
           * gsl_pow_5(e0 - e1 - e2_) * (9. * gsl_pow_2(e0 - e1 - e2_) + 21. * gsl_pow_2(e2_ - e1));
  }

  double decay0_fe12_mod16(double e2_, void * params_)
  {
    static double emass = decay0_emass();
    const bbpars * pars = static_cast<const bbpars *>(params_);
    const double & Zd   = pars->Zd;
    const double & e0   = pars->e0;
    const double & e1   = pars->e1;
    if (e2_ > e0 - e1) {
      return 0.0;
    }
    double p1 = std::sqrt(e1 * (e1 + 2. * emass));
    double p2 = std::sqrt(e2_ * (e2_ + 2. * emass));
    return (e1 + emass) * p1 * bxdecay0::decay0_fermi(Zd, e1) * (e2_ + emass) * p2 * bxdecay0::decay0_fermi(Zd, e2_)
           * gsl_pow_5(e0 - e1 - e2_) * gsl_pow_2(e2_ - e1);
  }

  double decay0_fe12_mod19(double e2_, void * params_)
  {
    static double emass = decay0_emass();
    const bbpars * pars = static_cast<const bbpars *>(params_);
    const double & Zd   = pars->Zd;
    const double & e0   = pars->e0;
    const double & e1   = pars->e1;
    if (e2_ > e0 - e1) {
      return 0.0;
    }
    double p1 = std::sqrt(e1 * (e1 + 2. * emass));
    double p2 = std::sqrt(e2_ * (e2_ + 2. * emass));
    return (e1 + emass) * p1 * bxdecay0::decay0_fermi(Zd, e1) * (e2_ + emass) * p2 * bxdecay0::decay0_fermi(Zd, e2_)
           * gsl_pow_4(e0 - e1 - e2_);
  }

} // end of namespace bxdecay0
