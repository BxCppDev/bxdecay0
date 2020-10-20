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
#include <bxdecay0/moller1.h>

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
#include <bxdecay0/particle.h>
#include <bxdecay0/particle_utils.h>

namespace bxdecay0 {

  void decay0_moller1(i_random & prng_, const double dcute_, const double * pe0_, double * pe1_, double * pe2_)
  {
    static double emass = decay0_emass();
    bool rotate;
    double phi;
    double cosphi;
    double sinphi;
    double costh;
    double sinth;
    double eel;
    double tel;
    double pel;
    double cosph;
    double sinph;

    double p  = std::sqrt(gsl_pow_2(pe0_[0]) + gsl_pow_2(pe0_[1]) + gsl_pow_3(pe0_[2]));
    double xe = std::sqrt(gsl_pow_2(p) + gsl_pow_2(emass));
    // double te = xe-emass;
    double gam  = xe / emass;
    double gam2 = gam * gam;
    double t    = gam - 1.;
    double x    = dcute_ / (t * emass);
    if (x >= 0.5) {
      for (int i = 0; i < 3; i++) {
        pe2_[i] = pe0_[i];
        pe1_[i] = 0.;
      }
      return;
    }
    double cc = 1. - 2. * x;
  tag_1:
    double e     = x / (1. - cc * prng_());
    double b1    = 4. / (9. * gam2 - 10. * gam + 5.);
    double b2    = t * t * b1;
    double b3    = (2. * gam2 + 2. * gam - 1.) * b1;
    double e1    = 1. - e;
    double screj = b2 * e * e - b3 * e / e1 + b1 * gam2 / (e1 * e1);
    if (prng_() > screj) {
      goto tag_1;
    }
    eel   = (t * e + 1.) * emass;
    tel   = eel - emass;
    pel   = std::sqrt(std::abs((eel + emass) * tel));
    costh = (xe * eel + emass * (tel - xe)) / (p * pel);
    if (costh >= 1.) {
      costh = 1.;
      sinth = 0.;
    } else if (costh <= -1.) {
      costh = -1.;
      sinth = 0.;
    } else {
      sinth = std::sqrt((1. + costh) * (1. - costh));
    }
    phi    = 2. * M_PI * prng_();
    cosphi = std::cos(phi);
    sinphi = std::sin(phi);
    // Polar co-ordinates to momentum components:
    pe2_[0] = pel * sinth * cosphi;
    pe2_[1] = pel * sinth * sinphi;
    pe2_[2] = pel * costh;
    pe1_[0] = -pe2_[0];
    pe1_[1] = -pe2_[1];
    pe1_[2] = p - pe2_[2];
    // Rotate to MRS
    decay0_gfang(pe0_, costh, sinth, cosph, sinph, rotate);
    if (rotate) {
      decay0_gdrot(pe1_, costh, sinth, cosph, sinph);
      decay0_gdrot(pe2_, costh, sinth, cosph, sinph);
    }
    return;
  }

} // end of namespace bxdecay0
