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
#include <bxdecay0/pair.h>

// Standard library:
#include <cmath>

// This project:
#include <bxdecay0/i_random.h>
#include <bxdecay0/event.h>

namespace bxdecay0 {


  void decay0_pair(i_random & prng_, event & event_,
                   double epair_, double tclev_, double thlev_,
                   double & tdlev_)
  {
    double phi=2.*M_PI*prng_();
    double ctet=-1.+2.*prng_();
    double teta=std::acos(ctet);
    double E=0.5*epair_;
    randomize_particle(prng_,event_,ELECTRON,E,E,teta,teta,phi,phi,tclev_,thlev_,tdlev_);
    randomize_particle(prng_,event_,POSITRON,E,E,teta,teta,phi,phi,    0.,    0.,tdlev_); // for time shift
    return;
  }

} // end of namespace bxdecay0
