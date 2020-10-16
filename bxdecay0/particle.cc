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
#include <bxdecay0/particle.h>

// Standard library:
#include <cmath>
#include <limits>
#include <stdexcept>

namespace bxdecay0 {

  particle::particle()
  {
    _code_ = INVALID_PARTICLE;
    _time_ = std::numeric_limits<double>::quiet_NaN();
    for (double & i : _momentum_) {
      i = std::numeric_limits<double>::quiet_NaN();
    }
    return;
  }

  bool particle::is_alpha() const
  {
    return _code_ == ALPHA;
  }

  bool particle::is_gamma() const
  {
    return _code_ == GAMMA;
  }

  bool particle::is_positron() const
  {
    return _code_ == POSITRON;
  }

  bool particle::is_electron() const
  {
    return _code_ == ELECTRON;
  }

  bool particle::is_neutron() const
  {
    return _code_ == NEUTRON;
  }

  bool particle::is_proton() const
  {
    return _code_ == PROTON;
  }

  bool particle::has_code() const
  {
    return _code_ != INVALID_PARTICLE;
  }

  void particle::set_code(const particle_code code_)
  {
    _code_ = code_;
    return;
  }

  particle_code particle::get_code() const
  {
    return _code_;
  }

  bool particle::has_time() const
  {
    return !std::isnan(_time_);
  }

  void particle::set_time(const double time_)
  {
    _time_ = time_;
    return;
  }

  void particle::shift_time(const double delay_)
  {
    if (has_time()) {
      _time_ += delay_;
    } else {
      set_time(delay_);
    }
    return;
  }

  double particle::get_time() const
  {
    return _time_;
  }

  void particle::set_px(const double px_)
  {
    _momentum_[0] = px_;
    return;
  }

  double particle::get_px() const
  {
    return _momentum_[0];
  }

  void particle::set_py(const double py_)
  {
    _momentum_[1] = py_;
    return;
  }

  double particle::get_py() const
  {
    return _momentum_[1];
  }

  void particle::set_pz(const double pz_)
  {
    _momentum_[2] = pz_;
    return;
  }

  double particle::get_pz() const
  {
    return _momentum_[2];
  }

  bool particle::has_momentum() const
  {
    if (std::isnan(_momentum_[0])) {
      return false;
    }
    if (std::isnan(_momentum_[1])) {
      return false;
    }
    if (std::isnan(_momentum_[2])) {
      return false;
    }
    return true;
  }

  void particle::set_momentum(const double px_, const double py_, const double pz_)
  {
    set_px(px_);
    set_py(py_);
    set_pz(pz_);
    return;
  }

  double particle::get_p() const
  {
    return std::sqrt(_momentum_[0] * _momentum_[0] + _momentum_[1] * _momentum_[1] + _momentum_[2] * _momentum_[2]);
  }

  bool particle::is_valid() const
  {
    if (!has_code()) {
      return false;
    }
    if (!has_time()) {
      return false;
    }
    if (!has_momentum()) {
      return false;
    }
    return true;
  }

  void particle::reset()
  {
    for (double & i : _momentum_) {
      i = std::numeric_limits<double>::quiet_NaN();
    }
    _time_ = std::numeric_limits<double>::quiet_NaN();
    _code_ = INVALID_PARTICLE;
    return;
  }

  void particle::print(std::ostream & out_, const std::string & title_, const std::string & indent_) const
  {
    if (!title_.empty()) {
      out_ << indent_ << title_ << "\n";
    }
    out_ << indent_ << "|-- Code: '" << geant3_particle_name(_code_) << "'\n";
    out_ << indent_ << "|-- Time: " << _time_ << " [second]\n";
    out_ << indent_ << "|-- Momentum * c: "
         << "[MeV]\n";
    out_ << indent_ << "|   |-- Px: " << _momentum_[0] << "\n";
    out_ << indent_ << "|   |-- Py: " << _momentum_[1] << "\n";
    out_ << indent_ << "|   `-- Pz: " << _momentum_[2] << "\n";
    out_ << indent_ << "`-- Validity: " << std::boolalpha << is_valid() << std::endl;
    return;
  }

  void particle::store(std::ostream & out_, const uint32_t flags_) const
  {
    out_.precision(15);
    out_ << _code_ << ' ';
    out_ << ' ' << _time_;
    out_ << ' ' << _momentum_[0];
    out_ << ' ' << _momentum_[1];
    out_ << ' ' << _momentum_[2];
    if ((flags_ & STORE_PARTICLE_NAME) != 0U) {
      out_ << ' ' << geant3_particle_name(_code_);
    }
    out_ << '\n';
    return;
  }

} // end of namespace bxdecay0
