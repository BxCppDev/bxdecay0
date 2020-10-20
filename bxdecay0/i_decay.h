/// \file bxdecay0/i_decay_generator.h
/* Author(s):     Francois Mauger <mauger@lpccaen.in2p3.fr>
 * Creation date: 2017-06-11
 * Last modified: 2017-06-11
 *
 * License:
 * Copyright 2017 F. Mauger
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 * Description:
 *
 *   C++ Decay event generator.interface
 *
 */

#ifndef BXDECAY0_I_DECAY_GENERATOR_H
#define BXDECAY0_I_DECAY_GENERATOR_H

namespace bxdecay0 {

  /// \brief Decay generator interface
  class i_decay_generator
  {
  public:
    i_decay_generator()
    {}

    virtual ~i_decay_generator()
    {}

    /// Check if a next event is available
    virtual bool has_next() const = 0;

    /// Shoot a decay event
    virtual void shoot(i_random & prng_, event & event_) = 0;
  };

} // end of namespace bxdecay0

#endif // BXDECAY0_I_DECAY_GENERATOR_H

// Local Variables: --
// mode: c++ --
// End: --
