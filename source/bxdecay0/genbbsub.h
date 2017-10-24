// -*- mode: c++; -*-
/// \file bxdecay0/genbbsub.h
/* Author(s):     Francois Mauger <mauger@lpccaen.in2p3.fr>
 * Creation date: 2013-05-05
 * Last modified: 2017-06-03
 *
 * License:
 * Copyright 2013-2017 F. Mauger
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * Description:
 *
 *   Interface function with GENBB/Decay0 generator
 *
 */

#ifndef BXDECAY0_GENBBSUB_H
#define BXDECAY0_GENBBSUB_H 1

// Standard library:
#include <string>
#include <cmath>

namespace bxdecay0 {

  class i_random;
  class event;

  struct bbpars;

  enum genbbsub_i2bbs_type {
    GENBBSUB_I2BBS_DBD        = 1, ///< Double beta decay mode
    GENBBSUB_I2BBS_BACKGROUND = 2  ///< Background/calibration decay mode
  };

  enum genbbsub_start_type {
    GENBBSUB_ISTART_INIT              = -1, ///< Initialize only
    GENBBSUB_ISTART_INIT_GENERATE_ONE =  0, ///< Initialize and generate one event
    GENBBSUB_ISTART_GENERATE          =  1  ///< Generate one event
  };

  /// Main decay0 C++ port interface function
  void genbbsub(i_random & prng_,
                event & event_,
                const int i2bbs_,
                const std::string & chnuclide_,
                const int ilevel_,
                const int modebb_,
                const int istart_,
                int & ier_,
                bbpars & bb_params_);

} // end of namespace bxdecay0

#endif // BXDECAY0_GENBBSUB_H

// Local Variables: --
// mode: c++ --
// End: --
