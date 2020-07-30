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
#include <bxdecay0/fe1_mods.h>

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

namespace bxdecay0 {

  double decay0_fe1_mod1(double e1_, void * params_)
  {
    static double emass = decay0_emass();
    const bbpars * pars = static_cast<const bbpars *>(params_);
    const double & Zdbb = pars->Zd;
    const double & e0   = pars->e0;
    if (e1_ > e0) {
      return 0.0;
    }
    double e2 = e0 - e1_;
    double p1 = std::sqrt(e1_ * (e1_ + 2. * emass));
    double p2 = std::sqrt(e2 * (e2 + 2. * emass));
    return (e1_ + emass) * p1 * bxdecay0::decay0_fermi(Zdbb, e1_) * (e2 + emass) * p2
           * bxdecay0::decay0_fermi(Zdbb, e2);
  }

  double decay0_fe1_mod2(double e1_, void * params_)
  {
    static double emass = decay0_emass();
    const bbpars * pars = static_cast<const bbpars *>(params_);
    const double & Zdbb = pars->Zd;
    const double & e0   = pars->e0;
    if (e1_ > e0) {
      return 0.0;
    }
    double e2 = e0 - e1_;
    double p1 = std::sqrt(e1_ * (e1_ + 2. * emass));
    double p2 = std::sqrt(e2 * (e2 + 2. * emass));
    return (e1_ + emass) * p1 * bxdecay0::decay0_fermi(Zdbb, e1_) * (e2 + emass) * p2 * bxdecay0::decay0_fermi(Zdbb, e2)
           * gsl_pow_2(e0 - 2. * e1_);
  }

  double decay0_fe1_mod3(double e1_, void * params_)
  {
    static double emass = decay0_emass();
    const bbpars * pars = static_cast<const bbpars *>(params_);
    const double & Zdbb = pars->Zd;
    const double & e0   = pars->e0;
    if (e1_ > e0) {
      return 0.0;
    }
    double e2 = e0 - e1_;
    double p1 = std::sqrt(e1_ * (e1_ + 2. * emass));
    double p2 = std::sqrt(e2 * (e2 + 2. * emass));
    return p1 * bxdecay0::decay0_fermi(Zdbb, e1_) * p2 * bxdecay0::decay0_fermi(Zdbb, e2)
           * (2. * gsl_pow_2(p1 * p2)
              + 9. * ((e1_ + emass) * (e2 + emass) + gsl_pow_2(emass)) * (gsl_pow_2(p1) + gsl_pow_2(p2)));
  }

  double decay0_fe1_mod7(double e1_, void * params_)
  {
    static double emass = decay0_emass();
    const bbpars * pars = static_cast<const bbpars *>(params_);
    const double & Zdbb = pars->Zd;
    const double & e0   = pars->e0;
    if (e1_ > e0) {
      return 0.0;
    }
    double e2 = e0 - e1_;
    double p1 = std::sqrt(e1_ * (e1_ + 2. * emass));
    double p2 = std::sqrt(e2 * (e2 + 2. * emass));
    return p1 * bxdecay0::decay0_fermi(Zdbb, e1_) * p2 * bxdecay0::decay0_fermi(Zdbb, e2)
           * ((e1_ + emass) * (e2 + emass) + gsl_pow_2(emass)) * (gsl_pow_2(p1) + gsl_pow_2(p2));
  }

  double decay0_fe1_mod10(double e1_, void * params_)
  {
    static double emass = decay0_emass();
    const bbpars * pars = static_cast<const bbpars *>(params_);
    const double & Zdbb = pars->Zd;
    const double & e0   = pars->e0;
    if (e1_ > e0) {
      return 0.0;
    }
    double p1 = std::sqrt(e1_ * (e1_ + 2. * emass));
    return (e1_ + emass) * p1 * bxdecay0::decay0_fermi(Zdbb, e1_) * gsl_pow_5(e0 - e1_);
  }

  double decay0_fe1_mod17(double e1_, void * params_)
  {
    static double emass = decay0_emass();
    const bbpars * pars = static_cast<const bbpars *>(params_);
    const double & Zdbb = pars->Zd;
    const double & e0   = pars->e0;
    if (e1_ > e0) {
      return 0.0;
    }
    double e2 = e0 - e1_;
    double p1 = std::sqrt(e1_ * (e1_ + 2. * emass));
    double p2 = std::sqrt(e2 * (e2 + 2. * emass));
    return (e1_ + emass) * p1 * bxdecay0::decay0_fermi(Zdbb, e1_) * (e2 + emass) * p2
           * bxdecay0::decay0_fermi(Zdbb, e2);
  }

  double decay0_fe1_mod18(double e1_, void * params_)
  {
    static double emass    = decay0_emass();
    const bbpars * pars    = static_cast<const bbpars *>(params_);
    const double & Zdbb    = pars->Zd;
    const double & Adbb    = pars->Ad;
    const double & e0      = pars->e0;
    const double & chi_GTw = pars->chi_GTw;
    const double & chi_Fw  = pars->chi_Fw;
    const double & chip_GT = pars->chip_GT;
    const double & chip_F  = pars->chip_F;
    const double & chip_T  = pars->chip_T;
    const double & chip_P  = pars->chip_P;
    const double & chip_R  = pars->chip_R;
    if (e1_ > e0) {
      return 0.0;
    }
    double e2 = e0 - e1_;
    double p1 = std::sqrt(e1_ * (e1_ + 2. * emass));
    double p2 = std::sqrt(e2 * (e2 + 2. * emass));
    // total energies in the units of electron mass
    double et0  = e0 / emass + 1.;
    double et1  = e1_ / emass + 1.;
    double et2  = e2 / emass + 1.;
    double a1   = (et1 * et2 - 1.) * gsl_pow_2(et1 - et2) / (2. * et1 * et2);
    double a2   = -2. * gsl_pow_2(et1 - et2) / (9. * et1 * et2);
    double a3   = 2. * (et1 * et2 - 1.) / (81. * et1 * et2);
    double r    = 3.107526e-3 * std::pow(Adbb, (1. / 3.));
    double rksi = 3. / 137.036 * Zdbb + r * et0;
    double a4   = 8. * (et1 * et2 + 1.) / (r * r * et1 * et2);
    double a5   = -8. * (rksi * (et1 * et2 + 1.) - 2. * r * et0) / (3. * r * r * et1 * et2);
    double a6   = 2. * ((rksi * rksi + 4. * r * r) * (et1 * et2 + 1.) - 4. * rksi * r * et0) / (9. * r * r * et1 * et2);
    // double chi_1plus =chip_GT+3.*chip_F-6.*chip_T;
    double chi_1minus = chip_GT - 3. * chip_F - 6. * chip_T;
    double chi_2plus  = chi_GTw + chi_Fw - chi_1minus / 9.;
    double a_eta      = a1 * gsl_pow_2(chi_2plus) + a2 * chi_2plus * chi_1minus + a3 * gsl_pow_2(chi_1minus)
                   + a4 * gsl_pow_2(chip_R) + a5 * chip_R * chip_P + a6 * gsl_pow_2(chip_P);
    return (e1_ + emass) * p1 * bxdecay0::decay0_fermi(Zdbb, e1_) * (e2 + emass) * p2 * bxdecay0::decay0_fermi(Zdbb, e2)
           * a_eta;
  }

} // end of namespace bxdecay0
