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
#include <fstream>
#include <iostream>
#include <sstream>

// This project:
#include <bxdecay0/resource.h>

namespace {
  std::set<std::string> _init_dbd_isotopes()
  {
    std::string filename = bxdecay0::get_resource("description/dbd_isotopes.lis", true);
    std::ifstream fin(filename.c_str());
    if (!fin) {
      throw std::logic_error("bxdecay0::dbd_isotopes: Cannot open resource file '" + filename + "'!");
    }

    std::set<std::string> tmp_isotopes;
    while (fin) {
      std::string line;
      std::getline(fin, line);
      std::string first_word;
      {
        // Skip comment and blank lines:
        std::istringstream line_iss(line);
        line_iss >> std::ws >> first_word;
        if (first_word.empty()) {
          continue;
        }
        if (first_word[0] == '#') {
          continue;
        }
      }
      // Isotope:
      std::string dbd_isotope = first_word;
      tmp_isotopes.insert(dbd_isotope);
      fin >> std::ws;
      if (fin.eof()) {
          break;
      }
    }
    return tmp_isotopes; 
  }

  std::set<std::string> _init_background_isotopes()
  {
    std::string filename = bxdecay0::get_resource("description/background_isotopes.lis", true);
    std::ifstream fin(filename.c_str());
    if (!fin) {
      throw std::logic_error("bxdecay0::background_isotopes: Cannot open resource file '" + filename + "'!");
    }

    std::set<std::string> tmp_isotopes;
    while (fin) {
      std::string line;
      std::getline(fin, line);
      std::string first_word;
      {
        // Skip comment and blank lines:
        std::istringstream line_iss(line);
        line_iss >> std::ws >> first_word;
        if (first_word.empty()) {
          continue;
        }
        if (first_word[0] == '#') {
          continue;
        }
      }
      // Isotope:
      std::string background_isotope = first_word;
      tmp_isotopes.insert(background_isotope);
      fin >> std::ws;
      if (fin.eof()) {
        break;
      }
    }
    return tmp_isotopes;
  }

  std::map<bxdecay0::dbd_mode_type, bxdecay0::dbd_record> _init_dbd_modes(bool trace)
  {
    std::string filename = bxdecay0::get_resource("description/dbd_modes.lis", true);
    std::ifstream fin(filename.c_str());
    if (!fin) {
      throw std::logic_error("bxdecay0::dbd_modes: Cannot open resource file '" + filename + "'!");
    }

    std::map<bxdecay0::dbd_mode_type, bxdecay0::dbd_record> tmp_dbd_modes;
    while (fin) {
      std::string line;
      std::getline(fin, line);
      if (trace) {
        std::cerr << "[trace] line = " << line << std::endl;
      }
      std::string first_word;
      {
        // Skip comment and blank lines:
        std::istringstream line_iss(line);
        line_iss >> std::ws >> first_word;
        if (first_word.empty()) {
          continue;
        }
        if (first_word[0] == '#') {
          continue;
        }
      }
      bxdecay0::dbd_record record;
      record.dbd_mode    = bxdecay0::DBDMODE_UNDEF;
      record.description = "";
      std::istringstream parse_iss(line);

      // Mode:
      int dbd_mode;
      parse_iss >> dbd_mode >> std::ws;
      if (!parse_iss) {
        throw std::logic_error("bxdecay0::get_dbd_modes: Invalid format for file '" + filename
                               + "'! Cannot decode BB mode!");
      }
      record.dbd_mode = static_cast<bxdecay0::dbd_mode_type>(dbd_mode);

      // Label:
      std::string unique_label;
      parse_iss >> unique_label >> std::ws;
      record.unique_label = unique_label;

      // Legacy Decay0 mode:
      int legacy_modebb;
      parse_iss >> legacy_modebb >> std::ws;
      if (!parse_iss) {
        throw std::logic_error("bxdecay0::get_dbd_modes: Invalid format for file '" + filename
                               + "'! Cannot decode legacy Decay0 mode");
      }
      if (legacy_modebb >= 0) {
        record.legacy_modebb = static_cast<bxdecay0::legacy_modebb_type>(legacy_modebb);
      } else {
        record.legacy_modebb = bxdecay0::LEGACY_MODEBB_NA;
      }

      // Description:
      std::getline(parse_iss, record.description);
      if (trace) {
        std::cerr << "[trace] DBD mode = " << record.dbd_mode << std::endl;
        std::cerr << "[trace] Decay0 legacy BB mode = " << record.legacy_modebb << std::endl;
        std::cerr << "[trace] Description = " << record.description << std::endl;
      }
      if (record.dbd_mode > 0 && !record.description.empty()) {
        tmp_dbd_modes[record.dbd_mode] = record;
      }
      fin >> std::ws;
      if (fin.eof()) {
        break;
      }
    }
    return tmp_dbd_modes;
  }
}


namespace bxdecay0 {

  const std::set<std::string> & dbd_isotopes()
  {
    static const std::set<std::string> _dbd_isotopes(::_init_dbd_isotopes());
    return _dbd_isotopes;
  }

  const std::set<std::string> & background_isotopes()
  {
    static const std::set<std::string> _background_isotopes(::_init_background_isotopes());
    return _background_isotopes;
  }

  const std::map<dbd_mode_type, dbd_record> & dbd_modes()
  {
    const bool trace = false;
    static const std::map<dbd_mode_type, dbd_record> _dbd_modes_dict(::_init_dbd_modes(trace));
    return _dbd_modes_dict;
  }

  dbd_mode_type dbd_mode_from_label(const std::string & label_)
  {
    const std::map<dbd_mode_type, dbd_record> & m = dbd_modes();
    for (const auto & p : m) {
      if (p.second.unique_label == label_) {
        return p.first;
      }
    }
    return DBDMODE_UNDEF;
  }

  dbd_mode_type dbd_mode_from_legacy_modebb(const legacy_modebb_type legacy_modebb_)
  {
    const std::map<dbd_mode_type, dbd_record> & m = dbd_modes();
    for (const auto & p : m) {
      if (p.second.legacy_modebb == legacy_modebb_) {
        return p.first;
      }
    }
    return DBDMODE_UNDEF;
  }

  std::string dbd_mode_label(const dbd_mode_type dbd_mode_)
  {
    const std::map<dbd_mode_type, dbd_record> & m = dbd_modes();
    return m.find(dbd_mode_)->second.unique_label;
  }

  std::string dbd_mode_description(const dbd_mode_type dbd_mode_)
  {
    const std::map<dbd_mode_type, dbd_record> & m = dbd_modes();
    return m.find(dbd_mode_)->second.description;
  }

  legacy_modebb_type dbd_legacy_mode(const dbd_mode_type dbd_mode_)
  {
    const std::map<dbd_mode_type, dbd_record> & m = dbd_modes();
    return m.find(dbd_mode_)->second.legacy_modebb;
  }

  const std::set<dbd_mode_type> & dbd_modes_with_esum_range()
  {
    static const std::set<dbd_mode_type> _dbd_modes_wer_dict = {
      DBDMODE_4,  // 2NUBB
      DBDMODE_5,  // MAJORON M1
      DBDMODE_6,  // MAJORON M3
      DBDMODE_8,  // 2NUBB
      DBDMODE_10, // 2NU
      DBDMODE_13, // MAJORON M7
      DBDMODE_14, // MAJORON M2
      DBDMODE_15,
      DBDMODE_16,
      DBDMODE_19
    };
    return _dbd_modes_wer_dict;
  }

  bool dbd_supports_esum_range(const dbd_mode_type dbd_mode_)
  {
    return dbd_modes_with_esum_range().count(dbd_mode_) != 0U;
  }

} // end of namespace bxdecay0
