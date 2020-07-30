/** bxdecay0/event.cc
 *
 * Copyright 2017-2020 François Mauger <mauger@lpccaen.in2p3.fr>
 * Copyright 2017-2020 Normandie Université
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

// Ourselves:
#include <bxdecay0/event.h>

// Standard library:
#include <cmath>
#include <limits>
#include <sstream>
#include <stdexcept>

namespace bxdecay0 {

  event::event()
  {
    _time_ = std::numeric_limits<double>::quiet_NaN();
    return;
  }

  bool event::has_generator() const
  {
    return !_generator_.empty();
  }

  void event::set_generator(const std::string & generator_)
  {
    _generator_ = generator_;
    return;
  }

  const std::string & event::get_generator() const
  {
    return _generator_;
  }

  bool event::has_time() const
  {
    return _time_ == _time_;
  }

  void event::set_time(const double time_)
  {
    _time_ = time_;
    return;
  }

  double event::get_time() const
  {
    return _time_;
  }

  void event::add_particle(const particle & p_)
  {
    _particles_.push_back(p_);
    return;
  }

  const std::vector<particle> & event::get_particles() const
  {
    return _particles_;
  }

  std::vector<particle> & event::grab_particles()
  {
    return _particles_;
  }

  particle & event::grab_last_particle()
  {
    if (_particles_.size() == 0) {
      throw std::logic_error("bxdecay0::event::grab_last_particle: Event has no particle yet!");
    }
    return _particles_.back();
  }

  bool event::is_valid() const
  {
    if (_time_ != _time_)
      return false;
    for (const auto & p : _particles_) {
      if (!p.is_valid())
        return false;
    }
    return true;
  }

  void event::shift_particles_time(double delta_time_, const int from_)
  {
    int count = 0;
    for (std::vector<particle>::iterator i = _particles_.begin(); i != _particles_.end(); i++) {
      particle & p = *i;
      if (count >= from_) {
        p.shift_time(delta_time_);
      }
      count++;
    }

    return;
  }

  void event::reset()
  {
    _particles_.clear();
    _time_ = std::numeric_limits<double>::quiet_NaN();
    return;
  }

  void event::print(std::ostream & out_, const std::string & title_, const std::string & indent_) const
  {
    if (!title_.empty()) {
      out_ << indent_ << title_ << "\n";
    }

    out_ << indent_ << "|-- Generator: ";
    if (has_generator()) {
      out_ << "'" << _generator_ << "'";
    } else {
      out_ << "<none>";
    }
    out_ << '\n';

    out_ << indent_ << "|-- Time: ";
    if (has_time()) {
      out_ << _time_ << " [second]";
    } else {
      out_ << "<none>";
    }
    out_ << '\n';
    out_ << indent_ << "|-- Particles: [" << _particles_.size() << "]\n";
    for (std::size_t ip = 0; ip < _particles_.size(); ip++) {
      const particle & p = _particles_[ip];
      out_ << indent_ << "|   " << (ip + 1 == _particles_.size() ? "`-- " : "|-- ") << "Particle #" << ip << ":\n";
      p.print(out_, "", indent_ + "|   " + (ip + 1 == _particles_.size() ? "    " : "|   "));
    }
    out_ << indent_ << "`-- Validity: " << std::boolalpha << is_valid() << std::endl;
    return;
  }

  void event::store(std::ostream & out_, const uint32_t flags_) const
  {
    out_.precision(15);
    if (flags_ & STORE_EVENT_DECO) {
      out_ << "#@event_start" << std::endl;
    }
    if (flags_ & STORE_EVENT_TIME) {
      out_ << _time_ << ' ' << _generator_ << std::endl;
    }
    out_ << _particles_.size() << '\n';
    uint32_t particle_flags = flags_;
    for (const auto & p : _particles_) {
      p.store(out_, particle_flags);
    }
    if (flags_ & STORE_EVENT_DECO) {
      out_ << "#@event_stop\n" << std::endl;
    }
    return;
  }

  void randomize_particle(i_random & prng_,
                          event & event_,
                          const particle_code np_,
                          double e1_,
                          double e2_,
                          double teta1_,
                          double teta2_,
                          double phi1_,
                          double phi2_,
                          double tclev_,
                          double thlev_,
                          double & tdlev_)
  {
    double last_time = 0.0;
    if (event_.get_particles().size() > 0) {
      const particle & last_part = event_.get_particles().back();
      last_time                  = last_part.get_time();
    }

    particle part;
    double pmass = particle_mass_MeV(np_);
    if (std::isnan(pmass)) {
      std::ostringstream message;
      message << "bxdecay0::randomize_particle: "
              << "Unknown mass for particle with ID=" << np_ << " !";
      throw std::logic_error(message.str());
    }
    double phi   = phi1_ + (phi2_ - phi1_) * prng_();
    double ctet1 = 1.;
    if (teta1_ != 0.)
      ctet1 = std::cos(teta1_);
    double ctet2 = -1.;
    if (teta2_ != M_PI)
      ctet2 = std::cos(teta2_);
    double ctet = ctet1 + (ctet2 - ctet1) * prng_();
    double stet = std::sqrt(1. - ctet * ctet);
    double E    = e1_;
    if (e1_ != e2_)
      E = e1_ + (e2_ - e1_) * prng_();
    double p  = std::sqrt(E * (E + 2. * pmass));
    double px = p * stet * std::cos(phi);
    double py = p * stet * std::sin(phi);
    double pz = p * ctet;
    tdlev_    = tclev_;
    if (thlev_ > 0.)
      tdlev_ = tclev_ - thlev_ / std::log(2.) * std::log(prng_());
    part.set_code(np_);
    part.set_time(last_time + tdlev_);
    part.set_momentum(px, py, pz);
    event_.add_particle(part);
    return;
  }

  void decay0_particle(i_random & prng_,
                       event & event_,
                       const particle_code np_,
                       double E1_,
                       double E2_,
                       double teta1_,
                       double teta2_,
                       double phi1_,
                       double phi2_,
                       double tclev_,
                       double thlev_,
                       double & tdlev_)
  {
    randomize_particle(prng_, event_, np_, E1_, E2_, teta1_, teta2_, phi1_, phi2_, tclev_, thlev_, tdlev_);
    return;
  }

} // end of namespace bxdecay0
