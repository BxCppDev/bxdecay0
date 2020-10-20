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
#include <bxdecay0/beta1.h>

// Standard library:
#include <cmath>

// Third party:
// - GSL:
#include <gsl/gsl_math.h>

// This project:
#include <bxdecay0/event.h>
#include <bxdecay0/funbeta1.h>
#include <bxdecay0/i_random.h>
#include <bxdecay0/particle.h>
#include <bxdecay0/particle_utils.h>
#include <bxdecay0/tgold.h>

namespace bxdecay0 {

  void decay0_beta1(i_random & prng_,
                    event & event_,
                    double Qbeta_,
                    double Zdtr_,
                    double tcnuc_,
                    double thnuc_,
                    double & tdnuc_,
                    double c1_,
                    double c2_,
                    double c3_,
                    double c4_)
  {
    parbeta1 pars1;
    pars1.Zdtr  = Zdtr_;
    pars1.Qbeta = Qbeta_;
    pars1.c1    = c1_;
    pars1.c2    = c2_;
    pars1.c3    = c3_;
    pars1.c4    = c4_;
    decay0_beta1(prng_, event_, tcnuc_, thnuc_, tdnuc_, &pars1);
    return;
  }

  void decay0_beta1(i_random & prng_, event & event_, double tcnuc_, double thnuc_, double & tdnuc_, void * params_)
  {
    // Parameters for function 'decay0_funbeta1'
    const auto * pars1     = static_cast<const parbeta1 *>(params_);
    const double & Zdtr    = pars1->Zdtr;
    const double & Qbeta   = pars1->Qbeta;

    // parbeta1 pars1;
    // pars1.Zdtr  = pars->Zdtr;
    // pars1.Qbeta = pars->Qbeta;
    // pars1.c1    = pars->c1;
    // pars1.c2    = pars->c2;
    // pars1.c3    = pars->c3;
    // pars1.c4    = pars->c4;

    double em;
    double fm;
    decay0_tgold(50.e-6, 0.5 * Qbeta, Qbeta, decay0_funbeta1, 0.001 * Qbeta, 2, em, fm, params_);
    // Rejection method:
    double f;
    double fe;
    double E;
    do {
      E  = 50.e-6 + (Qbeta - 50.e-6) * prng_();
      fe = decay0_funbeta1(E, params_);
      f  = fm * prng_();
    } while (f > fe);
    bxdecay0::particle_code np;
    if (Zdtr >= 0.) {
      np = ELECTRON;
    }
    if (Zdtr < 0.) {
      np = POSITRON;
    }
    // isotropical emission of beta particle is supposed:
    decay0_particle(prng_, event_, np, E, E, 0., M_PI, 0., 2. * M_PI, tcnuc_, thnuc_, tdnuc_);
    return;
  }

} // end of namespace bxdecay0
