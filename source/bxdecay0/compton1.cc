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
#include <bxdecay0/compton1.h>

// Standard library:
#include <cmath>

// Third party:
// - GSL:
#include <gsl/gsl_math.h>

// This project:
#include <bxdecay0/i_random.h>
#include <bxdecay0/particle_utils.h>
#include <bxdecay0/gfang.h>
#include <bxdecay0/gdrot.h>

namespace bxdecay0 {

  void decay0_compton1(i_random & prng_,
                       const double * pg0_,
                       double * pg1_, double * pe1_)
  {
    static double emass = decay0_emass();
    bool rotate;
    double egam0 = std::sqrt(gsl_pow_2(pg0_[0])
                             + gsl_pow_2(pg0_[1])
                             + gsl_pow_2(pg0_[2]));
    double ezero=egam0/emass;
    double emini=1.+2.*ezero;
    double emin=1./emini;
    double dsig1=std::log(emini);
    double dsig2=0.5*(1.-emin*emin);
    double dsigt=dsig1+dsig2;
    double brd;
    double br;
    double egam1;
    double t;
    double costh;
    double sinth;
    double cosph;
    double sinph;
    double rej;
    double phi;
    double cosphi;
    double sinphi;

    // Decide which part of f(e)=1/e+e to sample from
  tag_1:
    if (dsig1 < dsigt*prng_()) {
      // Sample from f2(e) distribution
      brd=prng_();
      if(ezero >= (ezero+1.)*prng_()) {
        brd=std::max(brd,prng_());
      }
      br = emin+(1.-emin)*brd;
    }
    else {
      br = emin * std::exp(dsig1*prng_());
    }
    // Scattered photon energy
    egam1 = br * egam0;
    // Calculate rejection function g(e)
    t = emass*(1.-br)/egam1;
    sinth = std::max(0.,t*(2.-t));
    rej = 1.0-(br*sinth)/(1.+br*br);
    if (prng_() > rej) goto tag_1;

    // Generate photon angles with respect to a Z-axis defined
    // along the parent photon; phi is generated isotropically
    sinth = std::sqrt(sinth);
    costh = 1.-t;
    phi = 2.*M_PI*prng_();
    cosphi = std::cos(phi);
    sinphi = std::sin(phi);
    // Polar co-ordinates to momentum components
    pg1_[0] = egam1*sinth*cosphi;
    pg1_[1] = egam1*sinth*sinphi;
    pg1_[2] = egam1*costh;
    // Momentum vector of recoil electron
    pe1_[0] = -pg1_[0];
    pe1_[1] = -pg1_[1];
    pe1_[2] = egam0-pg1_[2];
    // Rotate electron and scattered photon into MRS system
    decay0_gfang(pg0_,costh,sinth,cosph,sinph,rotate);
    if (rotate) {
      decay0_gdrot(pg1_,costh,sinth,cosph,sinph);
      decay0_gdrot(pe1_,costh,sinth,cosph,sinph);
    }
    return;
  }

} // end of namespace bxdecay0
