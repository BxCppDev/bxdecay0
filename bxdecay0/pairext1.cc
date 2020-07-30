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
#include <bxdecay0/pairext1.h>

// Standard library:
#include <cmath>
#include <iostream>

// Third party:
// - GSL:
#include <gsl/gsl_math.h>

// This project:
#include <bxdecay0/event.h>
#include <bxdecay0/gdrot.h>
#include <bxdecay0/gfang.h>
#include <bxdecay0/i_random.h>
#include <bxdecay0/particle.h>

namespace bxdecay0 {

  void decay0_pairext1(i_random & prng_, double Z_, const double * pg0_, double * pe1_, double * pe2_)
  {
    static double emass = decay0_emass();
    double Eel1;
    double Eel2;
    double pel1;
    double pel2;
    double x;
    double d;
    double alfa, beta, w1;
    double umax, u;
    double theta, sinth, costh;
    double phi, cosphi, sinphi;
    double r1, r2;
    double dmax;
    double dsig1;
    double dsig2;
    double bpar;
    double z3;
    double f;
    double aZ2;
    double fcoulomb;
    double x0;
    double dx;
    double dmin;
    double f10, f20;
    double f1, f2;
    double screj;
    double cosal;
    double sinal;
    double cosbt;
    double sinbt;
    int irej;
    bool rotate = false;
    double Egam = std::sqrt(gsl_pow_2(pg0_[0]) + gsl_pow_2(pg0_[1]) + gsl_pow_2(pg0_[2]));
    // If not enough energy, no pair production
    if (Egam < 2. * emass)
      goto tag_4;
    // For photons <2.1 MeV approximate the electron energy by sampling
    // from a uniform distribution in the interval [emass,Egam/2]
    if (Egam <= 2.1) {
      Eel1 = emass + prng_() * (0.5 * Egam - emass);
      x    = Eel1 / Egam;
      goto tag_2;
    }
    // Calculate some constants
    z3 = std::pow(Z_, 1. / 3.);
    f  = 8. / 3. * std::log(Z_);
    if (Egam > 50.) {
      aZ2      = gsl_pow_2(Z_ / 137.036);
      fcoulomb = aZ2 * (1. / (1. + aZ2) + 0.20206 - 0.0369 * aZ2 + 0.0083 * gsl_pow_2(aZ2) - 0.002 * gsl_pow_3(aZ2));
      f        = f + 8. * fcoulomb;
    }
    x0   = emass / Egam;
    dx   = 0.5 - x0;
    dmin = 544. * x0 / z3;
    if (dmin <= 1.) {
      f10 = 42.392 - 7.796 * dmin + 1.961 * gsl_pow_2(dmin) - f;
      f20 = 41.405 - 5.828 * dmin + 0.8945 * gsl_pow_2(dmin) - f;
    } else {
      f10 = 42.24 - 8.368 * std::log(dmin + 0.952) - f;
      f20 = f10;
    }
    // Calculate limit for screening variable, DELTA, to ensure
    // that screening rejection functions always remain positive
    dmax  = exp((42.24 - f) / 8.368) - 0.952;
    dsig1 = dx * dx * f10 / 3.;
    dsig2 = 0.5 * f20;
    bpar  = dsig1 / (dsig1 + dsig2);
    // Decide which screening rejection function to use and
    // sample the electron/photon fractional energy
  tag_1:
    r1 = prng_();
    r2 = prng_();
    if (r1 < bpar) {
      x    = 0.5 - dx * std::pow(r2, (1. / 3.));
      irej = 1;
    } else {
      x    = x0 + dx * r2;
      irej = 2;
    }
    // Calculate DELTA ensuring positivity
    d = 0.25 * dmin / (x * (1. - x));
    if (d >= dmax)
      goto tag_1;
    // Calculate F1 and F2 functions. F10 and F20 are the F1
    // and F2 functions calculated for the DELTA=DELTA minimum.
    if (d <= 1.) {
      f1 = 42.392 - 7.796 * d + 1.961 * gsl_pow_2(d) - f;
      f2 = 41.405 - 5.828 * d + 0.8945 * gsl_pow_2(d) - f;
    } else {
      f1 = 42.24 - 8.368 * std::log(d + 0.952) - f;
      f2 = f1;
    }
    if (irej == 1)
      screj = f1 / f10;
    if (irej == 2)
      screj = f2 / f20;
    // Accept or reject on basis of random variate
    if (prng_() > screj)
      goto tag_1;
    Eel1 = x * Egam;
    // Generate electron decay angles with respect to a Z-axis defined
    // along the parent photon. PHI is generated isotropically.
  tag_2:
    alfa = 0.625;
    d    = 0.13 * (0.8 + 1.3 / Z_) * (100. + 1. / Eel1) * (1. + x);
    w1   = 9. / (9. + d);
    umax = Eel1 * M_PI / emass;
  tag_3:
    beta = alfa;
    if (prng_() > w1)
      beta = 3. * alfa;
    r1 = prng_();
    u  = -(std::log(prng_() * r1)) / beta;
    if (u >= umax)
      goto tag_3;
    theta  = u * emass / Eel1;
    sinth  = std::sin(theta);
    costh  = std::cos(theta);
    phi    = 2. * M_PI * prng_();
    cosphi = std::cos(phi);
    sinphi = std::sin(phi);

    // Momentum components of first electron
    pel1    = std::sqrt((Eel1 + emass) * (Eel1 - emass));
    pe1_[0] = pel1 * sinth * cosphi;
    pe1_[1] = pel1 * sinth * sinphi;
    pe1_[2] = pel1 * costh;

    // Momentum vector of second electron. Recoil momentum of
    // target nucleus/electron is ignored.
    Eel2 = Egam - Eel1;
    pel2 = std::sqrt((Eel2 + emass) * (Eel2 - emass));
    // correction for conservation of x and y components of momentum
    sinth   = sinth * pel1 / pel2;
    costh   = std::sqrt(std::max(0., 1. - sinth * sinth));
    pe2_[0] = -pel2 * sinth * cosphi;
    pe2_[1] = -pel2 * sinth * sinphi;
    pe2_[2] = pel2 * costh;
    // Rotate tracks to MRS
    decay0_gfang(pg0_, cosal, sinal, cosbt, sinbt, rotate);
    if (rotate) {
      decay0_gdrot(pe1_, cosal, sinal, cosbt, sinbt);
      decay0_gdrot(pe2_, cosal, sinal, cosbt, sinbt);
    }
    return;
  tag_4:
    std::cerr << "e+e- pair is not created: Egamma < 1.022 MeV" << std::endl;
    return;
  }

} // end of namespace bxdecay0

// Local Variables: --
// mode: c++ --
// End: --
