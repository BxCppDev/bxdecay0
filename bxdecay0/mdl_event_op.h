/** \file bxdecay0/mdl_event_op.h
 *  \brief Momentum direction Lock (MDL) event operation 
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

#ifndef BXDECAY0_MDL_EVENT_OP_H
#define BXDECAY0_MDL_EVENT_OP_H

// Standard library:
#include <string>
#include <vector>

// This project:
#include <bxdecay0/i_random.h>
#include <bxdecay0/event.h>
#include <bxdecay0/utils.h>

namespace bxdecay0 {

  /// \brief Momentum direction lock (MDL) post-generation event operation
  ///
  /// If possible,  select a specific  (target) particle by type  at a
  /// given  rank  in  the  event  and  rotate  the  full  event  (all
  /// particles) in such  a way the target particle is  emitted in the
  /// chosen emission cone of which the axis and angle of aperture are
  /// specified.
  ///
  /// If a specific  particle rank is not defined,  then all particles
  /// of the selected  type(s) will have their momentum  forced in the
  /// emission  cone.   This  last  mode  destroys   possible  angular
  /// correlation between emitted particles.
  class momentum_direction_lock_event_op
    : public i_event_op
  {
    
  public:

    /// \brief Configuration parameters for UI:
    struct config_type
    {
      void reset();
      std::string particle_label = ""; //!< Label/name of the selected particle(s)
      int    target_particle_rank = -1; //!< Rank of the target particle
      double cone_phi_degree = 0.0;      //!< longitude (degree)
      double cone_theta_degree = 0.0;    //!< colatitude (degree)
      double cone_aperture_degree = 0.0; //!< aperture (degree)
      bool   error_on_missing_particle = false;
    };
    
    momentum_direction_lock_event_op() = default;
    
    momentum_direction_lock_event_op(bool debug_);

    ~momentum_direction_lock_event_op() override = default;

  public:

    bool is_active() const;
   
    void activate();

    void deactivate();
    
    bool is_valid() const;

    /// Set the configuration parameters of the MDL event op
    void set(const config_type & config_);

    /// Set the configuration parameters of the MDL event op and activate it
    void set(particle_code code_, int rank_,
             double cone_axis_x_, double cone_axis_y_, double cone_axis_z_,
             double cone_aperture_angle_,
             bool error_on_missing_particle_);

    /// Set the configuration parameters of the MDL event op and activate it
    void set(particle_code code_, int rank_,
             double cone_phi_, double cone_theta_, double cone_aperture_angle_,
             bool error_on_missing_particle_);
    
    void reset();

    int get_last_target_index() const;
    
    std::string name() const override;

    void operator()(i_random & prng_, event & event_) override;

    void smart_dump(std::ostream & out_, const std::string & indent_) const override;
   
  private:

    void _update_internals_();

    void _rotate_event_(i_random & prng_, event & event_);

  public:

    bool debug = false; //!< Debug activation flag for specific prints (do not use in production code)
   
  private:
    
    // Configuration parameters:
    bool    _active_ = false; //!< Activation flag
    particle_code _code_ = INVALID_PARTICLE; //!< Code of the reference particle of which the momentum should be forced, if not specified, all types of particles are selected.
    int     _rank_ = -1; //!< Rank of the reference/target particle (in the optional specified code above) of which the momentum should be forced (0 : first particle, 1: second particle..., -1 : all particles of a selected type)
    vector3 _cone_axis_; //!< Emission cone axis (default along the Z-axis (0, 0, 1))
    double  _cone_angle_ = 0.0; //!< Emission cone angle (unit: radians)
    bool    _error_on_missing_particle_ = false; //!< Throw exception if reference particle is missing (otherwise, ignore and pass)

    // Internal precomputed data (set by update): 
    double _phi_direction_   = std::numeric_limits<double>::quiet_NaN();
    double _theta_direction_ = std::numeric_limits<double>::quiet_NaN();

    // Intermediate results at each invocation of the operation:
    int  _last_target_index_ = -1; //!< Index of the found target particle at last invocation
    
  };

} // end of namespace bxdecay0

#endif // BXDECAY0_MDL_EVENT_OP_H

// Local Variables: --
// mode: c++ --
// End: --
