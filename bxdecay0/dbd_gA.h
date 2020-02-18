/// \file bxdecay0/dbd_gA.h
/* Author(s):     Francois Mauger <mauger@lpccaen.in2p3.fr>
 *
 * Creation date: 2020-02-05
 * Last modified: 2020-02-05
 *
 * License:
 * Copyright 2020-2020 F. Mauger
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 * Description:
 *
 *   C++ DBD event generator with support for the gA processes.
 *
 */

#ifndef BXDECAY0_DBD_GA_H
#define BXDECAY0_DBD_GA_H

// Standard library:
#include <string>
#include <iostream>
#include <memory>

// This project:
#include <bxdecay0/i_random.h>
#include <bxdecay0/event.h>

/// Nested namespace of the bxdecay0 library
namespace bxdecay0 {

  class event;
  
  /// \brief Decay0/GENBB generator
  class dbd_gA
  {
  public:

    /// \brief gA process
    enum process_type {
      PROCESS_UNDEF, ///< Undefined process
      PROCESS_G0,    ///< g0 process
      PROCESS_G2,    ///< g2 process
      PROCESS_G22,   ///< g22 process
      PROCESS_G4,    ///< g4 process
    };
    
    /// \brief The shooting method
    enum shooting_type {
      SHOOTING_UNDEF,    ///< Undefined E1/E2 randomization method
      SHOOTING_REJECTION ///< Von Neumann rejection sampling method
      //, SHOOTING_XXX   ///< Specify another sampling method
    };

    /// Check is a nuclide is supported
    static bool is_nuclide_supported(const std::string & id_);

    /// Return the label associated to a given process
    static std::string process_label(const process_type);

    /// Constructor
    dbd_gA() = default;

    /// Destructor
    ~dbd_gA();

    /// Set the DBD emitter nuclide
    void set_nuclide(const std::string & nuclide_);

    /// Set the process
    void set_process(const process_type process_);

    /// Set the shooting method
    void set_shooting(const shooting_type shooting_);

    /// Randomize kinetic energies of both electrons (unit: MeV)
    void shoot_e1_e2(i_random & prng_, double & e1_, double & e2_);

    /// Randomize the cosine of the angle between the emitted electrons' impulsions
    void shoot_cos_theta(i_random & prng_, const double e1_, const double e2_, double & theta_);

    /// Check if the generator is initialized
    bool is_initialized() const;

    /// Initialize the generator
    void initialize();

    /// Terminate the generator
    void reset();

    /// Smart print
    void print(std::ostream & out_ = std::clog,
               const std::string & title_ = "",
               const std::string & indent_ = "") const;

    /// Interpolated sample of the p.d.f. for plotting
    void plot_interpolated_pdf(std::ostream & out_, const unsigned int nsamples_ = 100) const;

    /// Build a "event" object from randomized kinematic quantities
    static void export_to_event(i_random & prng_,
                                const double e1_,
                                const double e2_,
                                const double cos12_,
                                event & ev_);

    
  private:

    void _load_tabulated_pdf_();
    
    void _build_pdf_interpolator_();
    
    void _shoot_rejection_(i_random & prng_, double & e1_, double & e2_);
   
  private:

    // Configuration:
    std::string  _nuclide_; ///< DBD emitter nuclide
    process_type _process_ = PROCESS_UNDEF; ///< Process
    shooting_type _shooting_ = SHOOTING_UNDEF; ///< Shooting method
      
    // Working data:
    bool _initialized_ = false; ///< Initialization flag
    std::string _tabulated_pdf_file_path_; ///< Effective path for the tabulated p.d.f. file

    // The machinery for tabulated p.d.f. management and interpolation
    // is hidden using the "PIMPL" idiom.
    // See also :
    // - https://cpppatterns.com/patterns/pimpl.html
    // - https://stackoverflow.com/questions/9954518/stdunique-ptr-with-an-incomplete-type-wont-compile
    struct pimpl_type;
    struct pimpl_deleter_type { void operator()(pimpl_type*) const; };
    std::unique_ptr<pimpl_type, pimpl_deleter_type> _pimpl_; ///< Private implementation

  };

} // end of namespace bxdecay0

#endif // BXDECAY0_DBD_GA_H

// Local Variables: --
// mode: c++ --
// End: --
