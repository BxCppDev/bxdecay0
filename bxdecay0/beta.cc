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
#include <bxdecay0/beta.h>

// Standard library:
#include <cmath>

// Third party:
// - GSL:
#include <gsl/gsl_math.h>

// This project:
#include <bxdecay0/event.h>
#include <bxdecay0/funbeta.h>
#include <bxdecay0/i_random.h>
#include <bxdecay0/particle.h>
#include <bxdecay0/particle_utils.h>
#include <bxdecay0/tgold.h>

namespace bxdecay0 {

  void decay0_beta(i_random & prng_,
                   event & event_,
                   double Qbeta_,
                   double Zdtr_,
                   double tcnuc_,
                   double thnuc_,
                   double & tdnuc_)
  {
    parbeta pars;
    pars.Zdtr  = Zdtr_;
    pars.Qbeta = Qbeta_;
    decay0_beta(prng_, event_, tcnuc_, thnuc_, tdnuc_, &pars);
    return;
  }

  void decay0_beta(i_random & prng_, event & event_, double tcnuc_, double thnuc_, double & tdnuc_, void * params_)
  {
    // Parameters for function 'decay0_funbeta'
    const parbeta * pars = static_cast<const parbeta *>(params_);
    const double & Zdtr  = pars->Zdtr;
    const double & Qbeta = pars->Qbeta;
    double em, fm;
    decay0_tgold(50.e-6, 0.5 * Qbeta, Qbeta, decay0_funbeta, 0.001 * Qbeta, 2, em, fm, params_);
    // Rejection method:
    double f, fe, E;
    do {
      E  = 50.e-6 + (Qbeta - 50.e-6) * prng_();
      fe = decay0_funbeta(E, params_);
      f  = fm * prng_();
    } while (f > fe);
    bxdecay0::particle_code np;
    if (Zdtr >= 0.)
      np = ELECTRON;
    if (Zdtr < 0.)
      np = POSITRON;
    // isotropical emission of beta particle is supposed
    decay0_particle(prng_, event_, np, E, E, 0., M_PI, 0., 2. * M_PI, tcnuc_, thnuc_, tdnuc_);
    return;
  }

} // end of namespace bxdecay0
