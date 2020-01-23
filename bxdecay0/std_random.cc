// bxdecay0/std_random.cc
// Copyright 2017 F. Mauger
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
#include <bxdecay0/std_random.h>

namespace bxdecay0 {

  std_random::std_random(std::default_random_engine & generator_)
    : _generator_(generator_)
    , _ud_(0.0,1.0)
  {
    return;
  }

  double std_random::operator()()
  {
    return _ud_(_generator_);
  }

} // end of namespace bxdecay0
