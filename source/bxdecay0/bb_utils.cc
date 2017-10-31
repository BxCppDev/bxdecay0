// Copyright 2013-2017 F. Mauger
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
// decay0_generator.cc

// Ourselves:
#include <bxdecay0/bb_utils.h>

// Standard library:
#include <iostream>
#include <fstream>
#include <sstream>

// This project:
#include <bxdecay0/resource.h>

namespace bxdecay0 {

  const std::map<modebb_type,dbd_record> & decay0_dbd_modes()
  {
    bool trace = false;
    static std::map<modebb_type,dbd_record> _dbd_modes_dict;
    if (_dbd_modes_dict.size() == 0) {
      std::string filename = get_resource("data/dbd_modes.lis", true);
      std::ifstream fin(filename.c_str());
      if (!fin) {
        throw std::logic_error("bxdecay0::get_dbd_modes: Cannot open resource file '" + filename + "'!");
      }
      while (fin) {
        std::string line;
        std::getline(fin, line);
        if (trace) std::cerr << "[trace] line = " << line << std::endl;
        std::string first_word;
        {
          // Skip comment and blank lines:
          std::istringstream line_iss(line);
          line_iss >> std::ws >> first_word;
          if (first_word.empty()) continue;
          if (first_word[0] == '#') continue;
        }
        dbd_record record;
        record.modebb = MODEBB_UNDEF;
        record.description = "";
        std::istringstream parse_iss(line);
        int modebb;
        parse_iss >> modebb;
        if (!parse_iss) {
          throw std::logic_error("bxdecay0::get_dbd_modes: Invalid format for file '" + filename + "'!");
        }
        record.modebb = static_cast<modebb_type>(modebb);
        std::getline(parse_iss, record.description);
        if (trace) {
          std::cerr << "[trace] modebb      = " << record.modebb << std::endl;
          std::cerr << "[trace] description = " << record.description << std::endl;
        }
        if (record.modebb > 0 && ! record.description.empty()) {
          _dbd_modes_dict[record.modebb] = record;
        }
        fin >> std::ws;
        if (fin.eof()) {
          break;
        }
      }
    }
    return _dbd_modes_dict;
  }

  std::string decay0_dbd_mode_description(const modebb_type modebb_)
  {
    const std::map<modebb_type,dbd_record> & m = decay0_dbd_modes();
    return m.find(modebb_)->second.description;
  }

  const std::set<modebb_type> & decay0_dbd_modes_with_esum_range()
  {
    static std::set<modebb_type> _dbd_modes_wer_dict;
    if (_dbd_modes_wer_dict.size() == 0) {
      _dbd_modes_wer_dict.insert(MODEBB_4);
      _dbd_modes_wer_dict.insert(MODEBB_5);
      _dbd_modes_wer_dict.insert(MODEBB_6);
      _dbd_modes_wer_dict.insert(MODEBB_8);
      _dbd_modes_wer_dict.insert(MODEBB_10);
      _dbd_modes_wer_dict.insert(MODEBB_13);
    }
    return _dbd_modes_wer_dict;
  }

  bool decay0_supports_esum_range(const modebb_type modebb_)
  {
    return decay0_dbd_modes_with_esum_range().count(modebb_);
  }

} // end of namespace bxdecay0
