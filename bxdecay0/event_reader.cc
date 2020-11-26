// bxdecay0/event_reader.cc
// Copyright 2020 F. Mauger
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
#include <bxdecay0/event_reader.h>

// Standard library:
#include <stdexcept>
#include <string>
#include <fstream>

namespace bxdecay0 {

  struct event_reader::pimpl_type
  {
    pimpl_type(event_reader & reader_);
    
    event_reader & reader;        ///< Parent event reader
    int current_file_index = -1;  
    int last_event_in_file_index = -1;
    int parsed_event_counter = 0;
    int loaded_event_counter = 0;
    int begin_event_file_index = -1;
    int begin_event_in_file_index = -1;
    int end_event_file_index = -1;
    int end_event_in_file_index = -1;
    std::unique_ptr<std::ifstream> fin;
  };

  event_reader::pimpl_type::pimpl_type(event_reader & reader_)
    : reader(reader_)
  {
    return;
  }
  
  event_reader::event_reader(int verbosity_)
  {
    _verbosity_ = verbosity_;
    _pimpl_.reset(new pimpl_type(*this));
    return;
  }

  event_reader::event_reader(const config_type & config_, int verbosity_)
    : event_reader(verbosity_)
  {
    if (is_trace()) std::cerr << "[trace] bxdecay0::event_reader::ctor: Entering...\n";
    set_configuration(config_);
    if (is_trace()) std::cerr << "[trace] bxdecay0::event_reader::ctor: Exiting...\n";
    return;
  }

  event_reader::~event_reader()
  {
    if (is_terminated()) {
      std::clog << "======================================================== \n";
      std::clog << "BxDecay0 event reader report \n";
      std::clog << "======================================================== \n";
      std::clog << "Begin event file index    : " << _pimpl_->begin_event_file_index << "\n";
      std::clog << "Begin event in file index : " << _pimpl_->begin_event_in_file_index << "\n";
      std::clog << "End event file index      : " << _pimpl_->end_event_file_index << "\n";
      std::clog << "End event in file index   : " << _pimpl_->end_event_in_file_index << "\n";
      std::clog << "Parsed events counter     : " << _pimpl_->parsed_event_counter << "\n";
      std::clog << "Loaded events counter     : " << _pimpl_->loaded_event_counter << "\n";
      std::clog << "======================================================== \n\n";
     }
    _pimpl_.reset();
    return;
  }

  void event_reader::set_verbosity(int verbosity_)
  {
    _verbosity_ = verbosity_ < 0 ? 0 : verbosity_;
    return;
  }

  int event_reader::get_verbosity() const
  {
    return _verbosity_;
  }
 
  /// Check if the reader runs in debug mode
  bool event_reader::is_info() const
  {
    return _verbosity_ > 0;
  }
 
  /// Check if the reader runs in debug mode
  bool event_reader::is_debug() const
  {
    return _verbosity_ > 1;
  }
 
  /// Check if the reader runs in trace mode
  bool event_reader::is_trace() const
  {
    return _verbosity_ > 2;
  }
  
  bool event_reader::is_configured() const
  {
    return _configured_;
  }

  bool event_reader::is_terminated() const
  {
    return _terminated_;
  }
  
  void event_reader::set_configuration(const config_type & config_)
  {
    if (is_trace()) std::cerr << "[trace] bxdecay0::event_reader::set_configuration: Entering...\n";
    if (is_configured()) {
      throw std::range_error("bxdecay0::event_reader::set_configuration: Reader is already configured!");
    }
    // Sanity checks:
    if (config_.event_files.size() == 0) {
      throw std::range_error("bxdecay0::event_reader::set_configuration: Missing input event file(s)!");
    }
    if (config_.start_event < 0) {
      throw std::range_error("bxdecay0::event_reader::set_configuration: Invalid start event index!");
    }
    if (config_.max_nb_events < 0) {
      throw std::range_error("bxdecay0::event_reader::set_configuration: Invalid maximum number of events!");
    }
    _config_ = config_;
    _at_configure_();
    _configured_ = true;
    if (is_trace()) std::cerr << "[trace] bxdecay0::event_reader::set_configuration: Exiting...\n";
    return;
  }

  void event_reader::reset_configuration()
  {
    if (is_trace()) std::cerr << "[trace] bxdecay0::event_reader::reset_configuration: Entering...\n";
    if (! is_configured()) {
      throw std::range_error("bxdecay0::event_reader::reset_configuration: Reader inot already configured!");
    }
    _configured_ = false;
    _at_unconfigure_();
    {
      config_type dummy;
      _config_ = dummy;
    }
    if (is_trace()) std::cerr << "[trace] bxdecay0::event_reader::reset_configuration: Exiting...\n";
    return;
  }

  const event_reader::config_type & event_reader::get_configuration() const
  {
    return _config_;
  }

  int event_reader::get_current_file_index() const
  {
    return _pimpl_->current_file_index;
  }

  int event_reader::get_last_event_in_file_index() const
  {
    return _pimpl_->last_event_in_file_index;
  }

  int event_reader::get_parsed_event_counter() const
  {
    return _pimpl_->parsed_event_counter;
  }

  int event_reader::get_loaded_event_counter() const
  {
    return _pimpl_->loaded_event_counter;
  }

  bool event_reader::has_next_event() const
  {
    if (not is_configured()) return false;
    if (is_terminated()) return false;
    auto mutable_this = const_cast<event_reader*>(this);
    return mutable_this->_check_next_event_();
  }
   
  bool event_reader::_check_next_event_()
  {
    if (is_trace()) std::cerr << "[trace] bxdecay0::event_reader::_check_next_event_: Entering...\n";
    if (not _pimpl_->fin) {
      if (is_trace()) std::cerr << "[trace] bxdecay0::event_reader::_check_next_event_: No input file stream!\n";
      return false;
    }
    if (is_debug()) std::cerr << "[debug] bxdecay0::event_reader::_check_next_event_: Reading ws...\n";
    *(_pimpl_->fin) >> std::ws;
    if (_pimpl_->fin->eof()) {
      if (is_debug()) std::cerr << "[debug] bxdecay0::event_reader::_check_next_event_: fin->EOF\n";
      _close_current_file_();
      if (not is_terminated()) {
        if (is_debug()) std::cerr << "[debug] bxdecay0::event_reader::_check_next_event_: Reader is not terminated\n";
        _open_new_file_();
      } else {
        if (is_debug()) std::cerr << "[debug] bxdecay0::event_reader::_check_next_event_: Reader is terminated\n";
        if (is_trace()) std::cerr << "[trace] bxdecay0::event_reader::_check_next_event_: Exiting...\n";
        return false;
      }
    } else {
      if (is_debug()) std::cerr << "[debug] bxdecay0::event_reader::_check_next_event_: One more event is expected\n";
      if (is_trace()) std::cerr << "[trace] bxdecay0::event_reader::_check_next_event_: Exiting...\n";
      return true;
    }
    if (is_trace()) std::cerr << "[trace] bxdecay0::event_reader::_check_next_event_: Exiting...\n";
    return not _terminated_;
  }
  
  void event_reader::load_next_event(event & evt_)
  {
    if (is_trace()) std::cerr << "[trace] bxdecay0::event_reader::load_next_event: Entering...\n";
    if (_terminated_) {
      throw std::logic_error("bxdecay0::event_reader::load_next_event: Reader is terminated!");
    }
    if (is_debug()) std::cerr << "[debug] bxdecay0::event_reader::load_next_event: Event reset\n";
    evt_.reset();
    while (! evt_.is_valid()) {
      if (not _pimpl_->fin) {
        if (is_debug()) std::cerr << "[debug] bxdecay0::event_reader::load_next_event: Forcing input file opening...\n";
        _open_new_file_();
      }
      std::ifstream & fin = *(_pimpl_->fin);
      int evId = -1;
      double evTime = 0.0;
      std::string decayGenName;
      int nbParticles = 0;
      if (is_debug()) std::cerr << "[debug] bxdecay0::event_reader::load_next_event: Parsing event header...\n";
      fin >> evId >> std::ws >> evTime >> std::ws >> decayGenName >> std::ws;
      if (_config_.zero_event_time) evTime = 0.0;
      fin >> nbParticles >> std::ws;
      if (!fin) {
        throw std::runtime_error("bxdecay0::event_reader::load_next_event: Invalid/corrupted event format!");
      }
      evt_.set_time(evTime);
      evt_.set_generator(decayGenName);
      for (int iPart = 0; iPart < nbParticles; iPart++) {
        if (is_debug()) std::cerr << "[debug] bxdecay0::event_reader::load_next_event: Parsing particle #" << iPart << " ...\n";
        int partCode = (int) INVALID_PARTICLE;
        double partTime, px, py, pz;
        fin >> partCode >> std::ws >> partTime >> std::ws >> px >> std::ws >> py >> std::ws >> pz >> std::ws;
        if (!fin) {
          throw std::runtime_error("bxdecay0::event_reader::load_next_event: Invalid/corrupted particle format!");
        }
        particle part;
        part.set_code(static_cast<particle_code>(partCode));
        part.set_time(partTime);
        part.set_px(px);
        part.set_py(py);
        part.set_pz(pz);
        evt_.add_particle(part);
      }
      if (is_debug()) std::cerr << "[debug] bxdecay0::event_reader::load_next_event: Updating counters...\n";
      _pimpl_->last_event_in_file_index++;
      _pimpl_->parsed_event_counter++;
      _pimpl_->end_event_file_index = _pimpl_->current_file_index;
      _pimpl_->end_event_in_file_index = _pimpl_->last_event_in_file_index;
      if (_pimpl_->parsed_event_counter <= _config_.start_event) {
        if (is_debug()) std::cerr << "[debug] bxdecay0::event_reader::load_next_event: Skipping event up to the starting index...\n";
        evt_.reset();
      } else if ((_config_.max_nb_events > 0) and (_pimpl_->parsed_event_counter == _config_.start_event + _config_.max_nb_events)) {
        if (is_debug()) std::cerr << "[debug] bxdecay0::event_reader::load_next_event: Maximum number of events reached.\n";
        _terminated_ = true;
        _close_current_file_();
        break;
      }

      if (is_debug()) std::cerr << "[debug] bxdecay0::event_reader::load_next_event: Reading ws...\n";
      fin >> std::ws;
      if (fin.eof()) {
        _close_current_file_();
        if (not is_terminated()) {
          if (is_debug()) std::cerr << "[debug] bxdecay0::event_reader::load_next_event: Reader is not terminated\n";
          _open_new_file_();
        } else {
          if (is_debug()) std::cerr << "[debug] bxdecay0::event_reader::load_next_event: Reader is terminated\n";
        }
      }
    } // while
    _pimpl_->loaded_event_counter++;
    if (_pimpl_->begin_event_file_index < 0) {
      _pimpl_->begin_event_file_index = _pimpl_->current_file_index;
      _pimpl_->begin_event_in_file_index = _pimpl_->last_event_in_file_index;
    }
     
    if (is_trace()) std::cerr << "[trace] bxdecay0::event_reader::load_next_event: Exiting...\n";
    return;
  }

  void event_reader::_at_configure_()
  {
    if (is_trace()) std::cerr << "[trace] bxdecay0::event_reader::_at_configure_: Entering...\n";
    _open_new_file_();
    if (is_trace()) std::cerr << "[trace] bxdecay0::event_reader::_at_configure_: Exiting...\n";
    return;
  }
    
  void event_reader::_open_new_file_()
  {
    if (is_trace()) std::cerr << "[trace] bxdecay0::event_reader::_open_new_file_: Entering...\n";
    if (_terminated_) {
      throw std::logic_error("bxdecay0::event_reader::_open_new_file_: Cannot open a new file! Reader is terminated!");
    }
    int new_file_index = _pimpl_->current_file_index + 1;
    std::string filename = _config_.event_files[new_file_index];
    if (is_debug()) std::cerr << "[debug] bxdecay0::event_reader::_open_new_file_: Opening new file '" << filename << "'\n";
    _pimpl_->fin.reset(new std::ifstream(filename));
    if (! *_pimpl_->fin) {
      throw std::runtime_error("bxdecay0::event_reader::_open_new_file_: Cannot open new file '" + filename + "'!");
    }
    _pimpl_->current_file_index++;
    _pimpl_->last_event_in_file_index = -1;
    (*_pimpl_->fin) >> std::ws;
    if (_pimpl_->fin->eof()) {
      if (is_debug()) std::cerr << "[debug] bxdecay0::event_reader::_open_new_file_: Detected EOF!\n";
      _close_current_file_();
      if (not is_terminated()) {
        if (is_debug()) std::cerr << "[debug] bxdecay0::event_reader::_open_new_file_: Detected EOF!\n";
        _open_new_file_();
      }
    }
    if (is_trace()) std::cerr << "[trace] bxdecay0::event_reader::_open_new_file_: Exiting...\n";
    return;
  }

  void event_reader::_close_current_file_()
  {
    if (is_trace()) std::cerr << "[trace] bxdecay0::event_reader::_close_current_file_: Entering...\n";
    if (_pimpl_->fin) {
      _pimpl_->fin->close();
      _pimpl_->fin.reset();
      if (_pimpl_->current_file_index + 1 == _config_.event_files.size()) {
        if (is_debug()) std::cerr << "[debug] bxdecay0::event_reader::_close_current_file_: set the terminated flag\n";
        _terminated_ = true;
        _pimpl_->current_file_index = -1;
      }
      _pimpl_->last_event_in_file_index = -1;
    }
    if (is_trace()) std::cerr << "[trace] bxdecay0::event_reader::_close_current_file_: Exiting...\n";
    return;
  }
   
  void event_reader::_at_unconfigure_()
  {
    if (is_trace()) std::cerr << "[trace] bxdecay0::event_reader::_at_unconfigure_: Entering...\n";
    _close_current_file_();
    if (is_trace()) std::cerr << "[trace] bxdecay0::event_reader::_at_unconfigure_: Exiting...\n";
    return;
  }

} // end of namespace bxdecay0
