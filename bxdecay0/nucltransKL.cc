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
#include <bxdecay0/nucltransKL.h>

// Standard library:
#include <cmath>

// Third party:
// - GSL:
#include <gsl/gsl_math.h>
// nucltransK.cc

// This project:
#include <bxdecay0/electron.h>
#include <bxdecay0/event.h>
#include <bxdecay0/gamma.h>
#include <bxdecay0/i_random.h>
#include <bxdecay0/pair.h>
#include <bxdecay0/particle.h>
#include <bxdecay0/particle_utils.h>

namespace bxdecay0 {

  void decay0_nucltransKL(i_random & prng_,
                          event & event_,
                          const double Egamma_,
                          const double EbindeK_,
                          const double conveK_,
                          const double EbindeL_,
                          const double conveL_,
                          const double convp_,
                          const double tclev_,
                          const double thlev_,
                          double & tdlev_)
  {
    static double emass = decay0_emass();
    double p            = (1. + conveK_ + conveL_ + convp_) * prng_();
    if (p <= 1.) {
      decay0_gamma(prng_, event_, Egamma_, tclev_, thlev_, tdlev_);
    } else if (p <= 1. + conveK_) {
      decay0_electron(prng_, event_, Egamma_ - EbindeK_, tclev_, thlev_, tdlev_);
      // decay0_gamma(prng_,event_,EbindeK_,tdlev_,0.,tdlev_); // for real time
      decay0_gamma(prng_, event_, EbindeK_, 0., 0., tdlev_); // for time shift
    } else if (p <= 1. + conveK_ + conveL_) {
      decay0_electron(prng_, event_, Egamma_ - EbindeL_, tclev_, thlev_, tdlev_);
      // decay0_gamma(prng_,event_,EbindeL_,tdlev_,0.,tdlev_); // for real time
      decay0_gamma(prng_, event_, EbindeL_, 0., 0., tdlev_); // for time shift
    } else {
      decay0_pair(prng_, event_, Egamma_ - 2. * emass, tclev_, thlev_, tdlev_);
    }
    return;
  }

} // end of namespace bxdecay0
