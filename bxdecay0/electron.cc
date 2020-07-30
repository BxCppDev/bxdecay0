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
#include <bxdecay0/electron.h>

// Standard library:
#include <cmath>

// This project:
#include <bxdecay0/event.h>
#include <bxdecay0/i_random.h>

namespace bxdecay0 {

  void decay0_electron(i_random & prng_, event & event_, double energy_, double tclev_, double thlev_, double & tdlev_)
  {
    randomize_particle(prng_, event_, ELECTRON, energy_, energy_, 0., M_PI, 0., 2. * M_PI, tclev_, thlev_, tdlev_);
    return;
  }

} // end of namespace bxdecay0
