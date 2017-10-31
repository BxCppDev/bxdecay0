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
#include <bxdecay0/utils.h>

// Standard library:
#include <iostream>

namespace bxdecay0 {

  const std::map<std::string, bool> & traces()
  {
    static bool devel = false;
    // devel = true;
    static std::map<std::string, bool> _t;
    if (_t.size() == 0) {
      if (devel) std::cerr << "[devel] bxdecay0::traces: " << "Populating trace map..." << std::endl;
      _t["bxdecay0"] = false;
      _t["genbbsub"] = false;
      _t["bb"] = false;
      _t["gauss"] = false;
      _t["fe12"] = false;
      _t["fermi"] = false;
      {
        const char * env_key = "BXDECAY0_TRACE";
        if (std::getenv(env_key) && std::string(std::getenv(env_key)) == "1") {
          _t["bxdecay0"] = true;
        }
      }
      {
        const char * env_key = "BXDECAY0_TRACE_GENBBSUB";
        if (std::getenv(env_key) && std::string(std::getenv(env_key)) == "1") {
          _t["genbbsub"] = true;
        }
      }
      {
        const char * env_key = "BXDECAY0_TRACE_BB";
        if (devel) std::cerr << "[devel] bxdecay0::traces: BXDECAY0_TRACE_BB='" << std::getenv(env_key) << "'" << std::endl;
        if (std::getenv(env_key) && std::string(std::getenv(env_key)) == "1") {
          if (devel) std::cerr << "[devel] bxdecay0::traces: " << "Activate BB trace." << std::endl;
          _t["bb"] = true;
        } else {
          if (devel) std::cerr << "[devel] bxdecay0::traces: " << "Don't activate BB trace." << std::endl;
        }
      }
      {
        const char * env_key = "BXDECAY0_TRACE_GAUSS";
        if (std::getenv(env_key) && std::string(std::getenv(env_key)) == "1") {
          _t["gauss"] = true;
        }
      }
      {
        const char * env_key = "BXDECAY0_TRACE_FE12";
        if (std::getenv(env_key) && std::string(std::getenv(env_key)) == "1") {
          _t["fe12"] = true;
        }
      }
      {
        const char * env_key = "BXDECAY0_TRACE_FERMI";
        if (std::getenv(env_key) && std::string(std::getenv(env_key)) == "1") {
          _t["fermi"] = true;
        }
      }
       for (auto p : _t) {
        if (devel) std::cerr << "[devel] bxdecay0::traces: "
                             << "Topic '" << p.first << "' -> trace = " << std::boolalpha
                             << p.second << std::endl;
      }
    }
    return _t;
  }

  bool is_trace(const std::string & label_)
  {
    const std::map<std::string, bool> & tr = traces();
    if (tr.count(label_)) {
      bool t = tr.find(label_)->second;
      if (t) return true;
    }
    return false;
  }

  bool name_starts_with(const std::string & name_,
                        const std::string & prefix_)
  {
    std::size_t len = prefix_.size();
    if (name_.size() < len) return false;
    if (name_.substr(0, prefix_.size()) == prefix_) return true;
    return false;
  }

} // end of namespace bxdecay0
