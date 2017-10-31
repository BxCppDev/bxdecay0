/** \file bxdecay0/resource.h
 *  \brief Resource file locators
 *
 * Copyright 2017 François Mauger <mauger@lpccaen.in2p3.fr>
 * Copyright 2017 Normandie Université
 *
 * This file is part of BxDecay0.
 *
 * BxDecay0 is free software: you  can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free  Software Foundation, either  version 3 of the  License, or
 * (at your option) any later version.
 *
 * BxDecay0 is distributed  in the hope that it will  be useful, but
 * WITHOUT  ANY   WARRANTY;  without  even  the   implied  warranty  of
 * MERCHANTABILITY or  FITNESS FOR A  PARTICULAR PURPOSE.  See  the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with BxDecay0.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BXDECAY0_RESOURCE_H
#define BXDECAY0_RESOURCE_H

// Standard library:
#include <string>

namespace bxdecay0 {

  //! Return URL, i.e. a path, to the  base directory where resource files are installed
  //! \param overriden_env If set this flag trigger the search for the
  //!        environment variable BXDECAY0_RESOURCE_DIR as a directory path on the filesystem
  //!        as an alternative base directory for resources in place of the
  //!        standard installation path
  std::string get_resource_dir(bool overriden_env = false);

  //! Return URL, i.e. a path, to named resource
  //! By default the encoded resource root, determined at compile time
  //! is used to search for the resource. This can be overriden by setting
  //! the BXDECAY0_RESOURCE_DIR environment variable to a path holding custom
  //! resources.
  //! \param rname name of resource, given as a path relative to
  //!        resource root.
  //! \param overriden_env flag to allow path overriding by the BXDECAY0_RESOURCE_DIR environment variable.
  std::string get_resource(const std::string& rname, bool overriden_env = false);

} // end of namespace bxdecay0

#endif // BXDECAY0_RESOURCE_H

// Local Variables: --
// mode: c++ --
// End: --
