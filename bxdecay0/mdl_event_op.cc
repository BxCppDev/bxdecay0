/** bxdecay0/mdl_event_op.cc
 *
 * Copyright 2021 François Mauger <mauger@lpccaen.in2p3.fr>
 * Copyright 2021 Normandie Université
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
#include <bxdecay0/mdl_event_op.h>

// Standard library:
#include <cmath>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <set>

namespace bxdecay0 {

  void momentum_direction_lock_event_op::config_type::reset()
  {
    particle_label = "";
    target_particle_rank = 0;
    cone_phi_degree = 0.0;
    cone_theta_degree = 0.0;
    cone_aperture_degree = 0.0;
    cone_aperture2_degree = -1.0;
    error_on_missing_particle = false;
    return;
  }

  momentum_direction_lock_event_op::momentum_direction_lock_event_op(bool debug_)
    : momentum_direction_lock_event_op()
  {
    debug = debug_;
    return;
  }

  void momentum_direction_lock_event_op::reset()
  {
    _active_ = false;
    _code_ = INVALID_PARTICLE;
    _rank_ = -1; // All ranks
    _cone_axis_ = make_vector3(0.0, 0.0, 1.0);
    _cone_angle_ = 0.0;
    _cone_angle2_ = std::numeric_limits<double>::quiet_NaN();
    _error_on_missing_particle_ = false; 
    _phi_direction_   = std::numeric_limits<double>::quiet_NaN();
    _theta_direction_ = std::numeric_limits<double>::quiet_NaN();
    _last_target_index_ = -1;
    return;
  }

  bool momentum_direction_lock_event_op::is_active() const
  {
    return _active_;
  }
  
  void momentum_direction_lock_event_op::activate()
  {
    _active_ = true;
    return;
  }
  
  void momentum_direction_lock_event_op::deactivate()
  {
    _active_ = false;
    return;
  }

  bool momentum_direction_lock_event_op::is_valid() const
  {
    if (std::isnan(_phi_direction_)) return false;
    if (std::isnan(_theta_direction_)) return false;
    return true;
  }

  void momentum_direction_lock_event_op::set(const config_type & config_)
  {
    particle_code code = INVALID_PARTICLE;
    const std::string & particle_label = config_.particle_label;
    if (particle_label == "g" or particle_label == "gamma") {
      code = GAMMA;
    } else if (particle_label == "e+" or particle_label == "positron") {
      code = POSITRON;
    } else if (particle_label == "e-" or particle_label == "electron") {
      code = ELECTRON;
    } else if (particle_label == "n" or particle_label == "neutron") {
      code = NEUTRON;
    } else if (particle_label == "p" or particle_label == "proton") {
      code = PROTON;
    } else if (particle_label == "a" or particle_label == "alpha") {
      code = ALPHA;
    } else if (particle_label == "*" or particle_label == "all") {
    } else {
      throw std::logic_error("bxdecay0::momentum_direction_lock_event_op::set: Invalid particle label '" + particle_label + "'!");      
    }
    if (config_.target_particle_rank < -1) {
      throw std::logic_error("bxdecay0::momentum_direction_lock_event_op::set: Invalid particle rank '" + std::to_string(config_.target_particle_rank) + "'!");      
    }
    double cone_phi       = config_.cone_phi_degree * M_PI / 180.0;
    double cone_theta     = config_.cone_theta_degree * M_PI / 180.0;
    double cone_aperture  = config_.cone_aperture_degree * M_PI / 180.0;
    double cone_aperture2 = std::numeric_limits<double>::quiet_NaN();
    if (std::isnormal(config_.cone_aperture2_degree) and config_.cone_aperture2_degree >= 0.0) {
      cone_aperture2 = config_.cone_aperture_degree * M_PI / 180.0;
    }
    double cx = std::cos(cone_phi) * std::sin(cone_theta);
    double cy = std::sin(cone_phi) * std::sin(cone_theta);
    double cz = std::cos(cone_theta);
    _set_(code,
          config_.target_particle_rank,
          cx,
          cy,
          cz,
          cone_aperture,
          cone_aperture2,
          config_.error_on_missing_particle);
    return;
  }

  void momentum_direction_lock_event_op::set(particle_code code_, 
                                             int rank_,
                                             double cone_axis_x_,
                                             double cone_axis_y_,
                                             double cone_axis_z_,
                                             double cone_aperture_angle_,
                                             bool error_on_missing_particle_)
  { 
    _set_(code_, rank_,
          cone_axis_x_, cone_axis_y_, cone_axis_z_,
          cone_aperture_angle_,
          std::numeric_limits<double>::quiet_NaN(),
          error_on_missing_particle_);
    return;
  }

  void momentum_direction_lock_event_op::set(particle_code code_,
                                             int rank_,
                                             double cone_phi_,
                                             double cone_theta_,
                                             double cone_aperture_angle_,
                                             bool error_on_missing_particle_)
  {
    double cx = std::cos(cone_phi_) * std::sin(cone_theta_);
    double cy = std::sin(cone_phi_) * std::sin(cone_theta_);
    double cz = std::cos(cone_theta_);
    set(code_, rank_,
        cx, cy, cz,
        cone_aperture_angle_,
        error_on_missing_particle_);
    return;
  }

  void momentum_direction_lock_event_op::set_with_aperture_rectangular_cut(particle_code code_, 
                                                                           int rank_,
                                                                           double cone_axis_x_,
                                                                           double cone_axis_y_,
                                                                           double cone_axis_z_,
                                                                           double cone_aperture_angle_,
                                                                           double cone_aperture2_angle_,
                                                                           bool error_on_missing_particle_)
  { 
    _set_(code_, rank_,
          cone_axis_x_, cone_axis_y_, cone_axis_z_,
          cone_aperture_angle_,
          cone_aperture2_angle_,
          error_on_missing_particle_);
    return;
  }
   
  void momentum_direction_lock_event_op::set_with_aperture_rectangular_cut(particle_code code_,
                                                                           int rank_,
                                                                           double cone_phi_,
                                                                           double cone_theta_,
                                                                           double cone_aperture_angle_,
                                                                           double cone_aperture2_angle_,
                                                                           bool error_on_missing_particle_)
  {
    double cx = std::cos(cone_phi_) * std::sin(cone_theta_);
    double cy = std::sin(cone_phi_) * std::sin(cone_theta_);
    double cz = std::cos(cone_theta_);
    set_with_aperture_rectangular_cut(code_, rank_,
                                      cx, cy, cz,
                                      cone_aperture_angle_,
                                      cone_aperture2_angle_,
                                      error_on_missing_particle_);
    return;
  }
 
  void momentum_direction_lock_event_op::_set_(particle_code code_,
                                               int rank_,
                                               double cone_axis_x_,
                                               double cone_axis_y_,
                                               double cone_axis_z_,
                                               double cone_aperture_angle_,
                                               double cone_aperture2_angle_,
                                               bool error_on_missing_particle_)
  {
    if (cone_aperture_angle_ < 0.0) {
      throw std::logic_error("bxdecay0::momentum_direction_lock_event_op::_set_: Invalid negative cone angle!");      
    }
    if (cone_aperture_angle_ >= 2 * M_PI) {
      throw std::logic_error("bxdecay0::momentum_direction_lock_event_op::_set_: Invalid cone angle (>=2 pi)!");      
    }
    _code_ = code_;
    _rank_ = rank_;
    _cone_axis_ = make_vector3(cone_axis_x_, cone_axis_y_, cone_axis_z_);
    _cone_angle_ = cone_aperture_angle_;
    if (std::isnormal(cone_aperture2_angle_) and cone_aperture2_angle_ >= 0.0) {
      if (cone_aperture2_angle_ >= M_PI / 2) {
        throw std::logic_error("bxdecay0::momentum_direction_lock_event_op::_set_: Invalid cone angle 1 for rectangular cut (>=pi/2)!");      
      }
      if (cone_aperture_angle_ >= M_PI / 2) {
        throw std::logic_error("bxdecay0::momentum_direction_lock_event_op::_set_: Invalid cone angle 2 for rectangular cut (>=pi/2)!");      
      }
      _cone_angle2_ = cone_aperture2_angle_;
    } else {
      _cone_angle2_ = std::numeric_limits<double>::quiet_NaN();
    }
    _error_on_missing_particle_ = error_on_missing_particle_;
    _update_internals_();
    activate();
    return;
  }

  void momentum_direction_lock_event_op::_update_internals_()
  {
    double direction_mag = std::sqrt(_cone_axis_.x * _cone_axis_.x +
                                     _cone_axis_.y * _cone_axis_.y +
                                     _cone_axis_.z * _cone_axis_.z);
    if (direction_mag < 1e-15) {
      throw std::logic_error("bxdecay0::momentum_direction_lock_event_op::_update_internals_: Null emission direction!");      
    }
    _phi_direction_ = std::atan2(_cone_axis_.y, _cone_axis_.x);
    _theta_direction_ = std::acos(_cone_axis_.z / direction_mag);
    return;
  }

  int momentum_direction_lock_event_op::get_last_target_index() const
  {
    return _last_target_index_;
  }

  void momentum_direction_lock_event_op::_rotate_event_(i_random & prng_, event & event_)
  {
    _last_target_index_ = -1;
    if (not _active_) {
      if (debug) std::cerr << "[debug] bxdecay0::momentum_direction_lock_event_op::_rotate_event_: MDL is not activated. Pass." << std::endl;
      return;
    }
    if (debug) event_.print(std::cerr, "Original event: ", "[debug] ");
    // First find the target particle of given type (optional) and rank:
    int ref_particle_index = -1;
    int pIndex = 0;
    int pSelectedRank = 0;
    std::set<int> forced_particles;
    for (auto & part : event_.grab_particles()) {
      bool selected = false;
      if ((_code_ == INVALID_PARTICLE) or
          (_code_ != INVALID_PARTICLE and part.get_code() == _code_)) {
        if (debug) std::cerr << "[debug] bxdecay0::momentum_direction_lock_event_op::_rotate_event_: Select particle at index " << pIndex << std::endl;
        selected = true;
      }
      if (selected) {
        if (_rank_ < 0) {
          forced_particles.insert(pIndex);
        } else if (_rank_ >= 0 && pSelectedRank == _rank_) {
          // ref_particle_index = pIndex;
          forced_particles.insert(pIndex);
          break;
        }
        pSelectedRank++;
      }
      pIndex++;
    } // for (auto & part ...)
    size_t fpsize = forced_particles.size();
    if ((_rank_ >= 0) and (fpsize == 1)) {
      ref_particle_index = *forced_particles.begin();      
    }
    if (debug) std::cerr << "[debug] bxdecay0::momentum_direction_lock_event_op::_rotate_event_: #forced_particles="
                         << forced_particles.size() << std::endl;
    if (debug) std::cerr << "[debug] bxdecay0::momentum_direction_lock_event_op::_rotate_event_: ref_particle_index="
                         << ref_particle_index << std::endl;
    if (fpsize == 0) { // and ref_particle_index < 0) {
      if (_error_on_missing_particle_) {
        throw std::logic_error("bxdecay0::momentum_direction_lock_event_op::_rotate_event_: Event has no particle of requested type "
                               + std::to_string(_code_) + " at rank "
                               + std::to_string(_rank_) + "!");       
      }
    }

    // Internal data (could be cached in the object)
    double aperture_angle = _cone_angle_;
    double aperture_x_max = -1.0;
    double aperture_y_max = -1.0;
    if (std::isnormal(_cone_angle2_)) {
      // Compute the angle of aperture of the conical section which contains
      // the rectangular cut:
      aperture_x_max = std::tan(_cone_angle_);
      aperture_y_max = std::tan(_cone_angle2_);
      double aperture_rho_max = std::hypot(aperture_x_max, aperture_y_max);
      aperture_angle = std::atan2(aperture_rho_max, 1.0);
    }

    if ((_rank_ >= 0) and (ref_particle_index >= 0)) {
      // Mode : an unique target ranked particle is forced to be emitted in the cone
      // and all other particles in the event are rotated coherently in ordrer to preserve
      // possible angular correlation between particles momenta.
      
      // Access the current emission direction of the reference particle:
      particle & ref_particle = event_.grab_particles()[ref_particle_index];
      vector3 ref_momentum = make_vector3(ref_particle.get_px(), ref_particle.get_py(), ref_particle.get_pz());
      double ref_p = std::sqrt(ref_momentum.x * ref_momentum.x +
                               ref_momentum.y * ref_momentum.y +
                               ref_momentum.z * ref_momentum.z);
      double ref_theta = std::acos(ref_momentum.z / ref_p);
      double ref_phi   = std::atan2(ref_momentum.y, ref_momentum.x);

      // Randomize a new direction with respect to the cone axis.
      double phiC;
      double thetaC;

      while (true) {
        // Conical envelope with circular section:
        phiC = 2 * M_PI * prng_();
        double cosThetaCMin = std::cos(aperture_angle);
        double cosThetaC = cosThetaCMin + (1.0 - cosThetaCMin) * prng_();
        thetaC = std::acos(cosThetaC);
        if (std::isnormal(_cone_angle2_)) {
          // Apply rectangular cut: accept only (thetaC,phiC) tuples that are in the rectangular aperture window:
          double r = 1.0 / cosThetaC;
          double sinThetaC = std::sqrt(1.0 - cosThetaC*cosThetaC);
          double x = r * sinThetaC;
          double y = x;
          x *= std::cos(phiC);
          y *= std::sin(phiC);
          if (std::abs(x) < aperture_x_max and std::abs(y) < aperture_y_max) {
            break;
          }
        } else {
          break;
        }
      }
      
      // Rotate all particles in the event :
      for (auto & part : event_.grab_particles()) {
        // Fetch the current momentum:
        vector3 p_momentum = make_vector3(part.get_px(), part.get_py(), part.get_pz());
        if (debug) std::cerr << "[debug] bxdecay0::momentum_direction_lock_event_op::_rotate_event_: Original momentum = ";
        print(p_momentum, std::cerr);
        std::cerr << std::endl;
        // Rotate the momentum:
        vector3 new_p = rotate_zyz(p_momentum, 0.0, -ref_theta, -ref_phi);
        if (debug){
          std::cerr << "[debug] bxdecay0::momentum_direction_lock_event_op::_rotate_event_:  -> Normalized momentum = ";
          print(new_p, std::cerr);
          std::cerr << std::endl;
        }
        vector3 new2_p = rotate_zyz(new_p, phiC, thetaC, 0.0);
        if (debug){
          std::cerr << "[debug] bxdecay0::momentum_direction_lock_event_op::_rotate_event_:  -> Rotated momentum = ";
          print(new2_p, std::cerr);
          std::cerr << std::endl;
        }
        // Final rotation align the particle to the emission cone axis:
        vector3 new3_p = rotate_zyz(new2_p, _phi_direction_, _theta_direction_, 0.0);
        if (debug){
          std::cerr << "[debug] bxdecay0::momentum_direction_lock_event_op::_rotate_event_:  -> Final momentum = ";
          print(new3_p, std::cerr);
          std::cerr << std::endl;
        }
        // Update momentum to the new direction:
        new3_p.x = std::abs(new3_p.x) < 1e-15 ? 0.0 : new3_p.x;
        new3_p.y = std::abs(new3_p.y) < 1e-15 ? 0.0 : new3_p.y;
        new3_p.z = std::abs(new3_p.z) < 1e-15 ? 0.0 : new3_p.z;
        part.set_momentum(new3_p.x, new3_p.y, new3_p.z);
      }
      _last_target_index_ = ref_particle_index;
    }
    
    if ((_rank_ < 0) and (fpsize > 0)) {
      // Mode : force all selected particles to be emitted in the requested cone,
      // all other particles are unchanged.
      // This destroys potential angular correlations between emitted particles
      for(auto pForcedIndex : forced_particles) {

        // Randomize a new direction with respect to the cone axis.
        double phiC;
        double thetaC;
        while (true) {
          // Conical envelope with circular section:
          phiC = 2 * M_PI * prng_();
          double cosThetaCMin = std::cos(aperture_angle);
          double cosThetaC = cosThetaCMin + (1.0 - cosThetaCMin) * prng_();
          thetaC = std::acos(cosThetaC);
          if (std::isnormal(_cone_angle2_)) {
            // Apply rectangular cut: accept only (thetaC,phiC) tuples that are in the rectangular aperture window:
            double r = 1.0 / cosThetaC;
            double sinThetaC = std::sqrt(1.0 - cosThetaC*cosThetaC);
            double x = r * sinThetaC;
            double y = x;
            x *= std::cos(phiC);
            y *= std::sin(phiC);
            if (std::abs(x) < aperture_x_max and std::abs(y) < aperture_y_max) {
              break;
            }
          } else {
            break;
          }
        }
        particle & forcedParticle = event_.grab_particles()[pForcedIndex];
        // Fetch the current momentum:
        double pMag = forcedParticle.get_p();
        // Build the momentum in the cone frame:
        vector3 new_p = make_vector3(0.0, 0.0, pMag);
        // Rotate by a random orientation within the cone:
        vector3 new2_p = rotate_zyz(new_p, phiC, thetaC, 0.0);
        if (debug){
          std::cerr << "[debug] bxdecay0::momentum_direction_lock_event_op::_rotate_event_:  -> Rotated momentum = ";
          print(new2_p, std::cerr);
          std::cerr << std::endl;
        }
        // Final rotation align the particle to the emission cone axis:
        vector3 new3_p = rotate_zyz(new2_p, _phi_direction_, _theta_direction_, 0.0);
        if (debug){
          std::cerr << "[debug] bxdecay0::momentum_direction_lock_event_op::_rotate_event_:  -> Final momentum = ";
          print(new3_p, std::cerr);
          std::cerr << std::endl;
        }
        // Update momentum to the new direction:
        new3_p.x = std::abs(new3_p.x) < 1e-15 ? 0.0 : new3_p.x;
        new3_p.y = std::abs(new3_p.y) < 1e-15 ? 0.0 : new3_p.y;
        new3_p.z = std::abs(new3_p.z) < 1e-15 ? 0.0 : new3_p.z;
        forcedParticle.set_momentum(new3_p.x, new3_p.y, new3_p.z); 
      }
    }
    return;
  }
  
  void momentum_direction_lock_event_op::operator()(i_random & prng_, event & event_)
  {
    this->_rotate_event_(prng_, event_);
    return;
  }

  std::string momentum_direction_lock_event_op::name() const
  {
    return std::string("MDL");
  }

  void momentum_direction_lock_event_op::smart_dump(std::ostream & out_,
                                                    const std::string & indent_) const 
  {
    out_ << indent_ << "|-- Name: " << this->name() << '\n';
    out_ << indent_ << "|-- Debug: " << std::boolalpha << debug << '\n';
    out_ << indent_ << "|-- Active: " << std::boolalpha << _active_ << '\n';
    out_ << indent_ << "|-- Code: " << _code_ << '\n';
    out_ << indent_ << "|-- Rank: " << _rank_ << '\n';
    out_ << indent_ << "|-- Cone axis: ";
    print(_cone_axis_, out_);
    out_ << '\n';
    out_ << indent_ << "|-- Cone angle: " << _cone_angle_ << '\n';
    out_ << indent_ << "|-- Cone angle 2: " << ((std::isnormal(_cone_angle2_) and  _cone_angle2_ >= 0.0) ? std::to_string(_cone_angle2_) : "none" ) << '\n';
    out_ << indent_ << "|-- Error on missing particle: " << std::boolalpha << _error_on_missing_particle_ << '\n';
    out_ << indent_ << "|-- Phi direction: " << (_phi_direction_ * 180 / M_PI) << "°" << '\n';
    out_ << indent_ << "|-- Theta direction: " << (_theta_direction_ * 180 / M_PI) << "°" << '\n';
    out_ << indent_ << "`-- Last target particle index: " << _last_target_index_ << '\n';
    
    return;
  }
 
} // end of namespace bxdecay0
