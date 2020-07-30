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
#include <bxdecay0/moller.h>

// Standard library:
#include <cmath>

// Third party:
// - GSL:
#include <gsl/gsl_math.h>

// This project:
#include <bxdecay0/event.h>
#include <bxdecay0/gdrot.h>
#include <bxdecay0/gfang.h>
#include <bxdecay0/i_random.h>
#include <bxdecay0/moller1.h>
#include <bxdecay0/particle.h>
#include <bxdecay0/particle_utils.h>

namespace bxdecay0 {

  void decay0_moller(i_random & prng_,
                     event & event_,
                     double E1,
                     double E2,
                     double teta1,
                     double teta2,
                     double phi1,
                     double phi2,
                     double dcute)
  {
    static double emass = decay0_emass();
    double pe0[3], pe1[3], pe2[3];
    double phi   = phi1 + (phi2 - phi1) * prng_();
    double ctet1 = 1.;
    if (teta1 != 0.)
      ctet1 = std::cos(teta1);
    double ctet2 = -1.;
    if (teta2 != M_PI)
      ctet2 = std::cos(teta2);
    double ctet = ctet1 + (ctet2 - ctet1) * prng_();
    double stet = std::sqrt(1. - ctet * ctet);
    double E    = E1;
    if (E1 != E2)
      E = E1 + (E2 - E1) * prng_();
    double p = std::sqrt(E * (E + 2. * emass));
    pe0[0]   = p * stet * std::cos(phi);
    pe0[1]   = p * stet * std::sin(phi);
    pe0[2]   = p * ctet;
    decay0_moller1(prng_, dcute, pe0, pe1, pe2);

    // Push particles in the preimary event:
    particle part;

    // Positron:
    part.set_code(ELECTRON);
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
