// Copyright 2020 F. Mauger
// Copyright 2020 M. Hoballah
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
#include <bxdecay0/dbd_gA.h>

// Standard library:
#include <limits>
#include <stdexcept>
#include <set>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

// This project:
#include <bxdecay0/resource.h>
#include <bxdecay0/utils.h>

// Third party:
#include <gsl/gsl_errno.h>
#include <gsl/gsl_interp2d.h>
#include <gsl/gsl_math.h>
// #include <gsl/gsl_fit.h>
// #include <gsl/gsl_multifit.h>

namespace {

  /// \brief Tabulated kinetic energy model for both emitted electrons:
  struct tabulated_prob_type {
    
    enum sampling_type {
      SAMPLING_UNDEF      = 0, ///< Undefined sampling mode
      SAMPLING_LINEAR     = 1, ///< Linear sampling mode
      SAMPLING_NONLINEAR  = 2  ///< Irregular sampling mode
    };
    
    tabulated_prob_type() = default;

    ~tabulated_prob_type() {      
      return;
    }
    
    // Attributes:
    double              esum_max = -1.0; ///< Maximum sum of kinetic energy, a.k.a. Qbb (unit: MeV)
    sampling_type       e_sampling[2] = {SAMPLING_UNDEF, SAMPLING_UNDEF}; ///< Sampling mode (unused)
    unsigned int        e_nsamples[2] = {0, 0};  ///< Number of kinetic energy samples
    double              e_min[2] = {-1.0, -1.0}; ///< Minimum kinetic energy (unit: MeV)
    double              e_max[2] = {-1.0, -1.0}; ///< Maximum kinetic energy (unit: MeV)
    std::vector<double> e_samples[2];            ///< Kinetic energy samples (unit: MeV)
    std::vector<double> energies;                ///< Sampled kinetic energy (unit: MeV) [ redundant with above arrays ]
    double              energy_step = -1.0;      ///< Kinetic energy step
    unsigned int        nsamples = 0;            // [ redundant with above e_nsamples[0|1] ] 

    // Tabulated probabilities
    std::vector<double> prob;                   ///< p.d.f. 2D-sampled values (not necessarily normalized)
    double              prob_max = -1.0;        ///< Maximum value for the tabulated p.d.f. (unit: arbitrary)

    // Tabulated cumulative probabilities (Malak's work adapted to the new cdf data format)
    std::vector<double>              e1_cprobs;  ///< c.d.f. cumul probs associated to E1 sampling
    std::vector<std::vector<double>> e2_cprobs;  ///< c.d.f. cumul probs associated to E2 sampling for each E1 sample

  };

  /// \brief p.d.f. interpolator
  struct pdf_interpolator_type {
    
    pdf_interpolator_type() = default;

    ~pdf_interpolator_type() {
      if (xacc) {
        gsl_interp_accel_free(xacc);
      }
      if (yacc) {
        gsl_interp_accel_free(yacc);
      }
      if (interp) {
        gsl_interp2d_free(interp);
      }
      return;
    }
    
    // Attributes:
    const gsl_interp2d_type * choice = gsl_interp2d_bilinear; ///< GSL interpolation type
    gsl_interp2d     * interp = nullptr; ///< GSL interpolator
    gsl_interp_accel * xacc = nullptr;   ///< GSL interpolation accelerator for E1 sampling
    gsl_interp_accel * yacc = nullptr;   ///< GSL interpolation accelerator for E2 sampling
    
  };
  
}

namespace bxdecay0 {

  /// \brief PIMPL type
  struct dbd_gA::pimpl_type {
    pimpl_type() = default;
    ~pimpl_type(){}
    // Attributes:
    ::tabulated_prob_type   tab_prob;          ///< Tabulated joint p.d.f. or c.d.f. data
    ::pdf_interpolator_type pdf_interpolator; ///< 2D-interpolator for tabulated p.d.f.
  };
  
  void dbd_gA::pimpl_deleter_type::operator()(dbd_gA::pimpl_type * ptr_) const
  {
    delete ptr_;
    return;
  }
  
  // static
  bool dbd_gA::is_nuclide_supported(const std::string & id_)
  {
    static const std::set<std::string> _sn({"Se82", "Mo100", "Cd116", "Nd150"}); 
    return _sn.count(id_);
  }

  // static
  std::string dbd_gA::process_label(const process_type p_)
  {
    switch (p_) {
    case PROCESS_G0 : return "g0";
    case PROCESS_G2 : return "g2";
    case PROCESS_G22 : return "g22";
    case PROCESS_G4 : return "g4";
    }
    return "";
  }

  dbd_gA::~dbd_gA()
  {
    if (is_initialized()) {
      reset();
    }
    return;
  }

  void dbd_gA::set_debug(bool debug_)
  {
    _debug_ = debug_;
    return;
  }

  bool dbd_gA::is_debug() const
  {
    return _debug_;
  }

  void dbd_gA::set_nuclide(const std::string & nuclide_)
  {
    if (!is_nuclide_supported(nuclide_) and nuclide_ != "Test") {
      throw std::logic_error("bxdecay0::dbd_gA::set_nuclide: Unsupported nuclide '"
                             + nuclide_ + "'!");
    }
    _nuclide_ = nuclide_;
    return;
  }

  void dbd_gA::set_process(const process_type process_)
  {
    if (process_ == PROCESS_UNDEF) {
      throw std::logic_error("bxdecay0::dbd_gA::set_process: Invalid gA process !");
    }
    _process_ = process_;
    return; 
  }

  void dbd_gA::set_shooting(const shooting_type shooting_)
  {
    if (shooting_ == SHOOTING_UNDEF) {
      throw std::logic_error("bxdecay0::dbd_gA::set_shooting: Invalid shooting method !");
    }
    _shooting_ = shooting_;
    return; 
  }

  bool dbd_gA::is_initialized() const
  {
    return _initialized_;
  }

  void dbd_gA::initialize()
  {
    if (is_initialized()) {
      throw std::logic_error("bxdecay0::dbd_gA::initialize: Generator is already initialized!");
    }
    if (_nuclide_.empty()) {
      throw std::logic_error("bxdecay0::dbd_gA::initialize: Missing nuclide!");
    }
    if (_process_ == PROCESS_UNDEF) {
      throw std::logic_error("bxdecay0::dbd_gA::initialize: Missing process!");
    }
    if (_shooting_ == SHOOTING_UNDEF) {
      throw std::logic_error("bxdecay0::dbd_gA::initialize: Missing shooting method!");
    }

    // Build the path of the tabulated p.d.f. resource file:
    if (_shooting_ == SHOOTING_REJECTION) {
      std::ostringstream outs;
      outs << "data/dbd_gA/" << _nuclide_ << '/' << process_label(_process_) << '/'
           << "tab_pdf.data";
      _tabulated_prob_file_path_ = outs.str();
      std::string fres = get_resource(_tabulated_prob_file_path_, true);
      _tabulated_prob_file_path_ = fres;
    } else if (_shooting_ == SHOOTING_INVERSE_TRANSFORM_METHOD) {
      std::ostringstream outs;
      outs << "data/dbd_gA/" << _nuclide_ << '/' << process_label(_process_) << '/'
           << "tab_ocdf.data";
      _tabulated_prob_file_path_ = outs.str();
      std::string fres = get_resource(_tabulated_prob_file_path_, true);
      _tabulated_prob_file_path_ = fres;
    }
    _pimpl_.reset(new pimpl_type);
    
    if (_shooting_ == SHOOTING_REJECTION) {
      _load_tabulated_pdf_();
      _build_pdf_interpolator_();
    }
    if (_shooting_ == SHOOTING_INVERSE_TRANSFORM_METHOD) {
      _load_tabulated_cdf_opt_();
    }
 
    _initialized_ = true;
    return;
  }

  void dbd_gA::_build_pdf_interpolator_()
  {
    auto & pdf_interpolator = _pimpl_->pdf_interpolator;
    unsigned int nx = _pimpl_->tab_prob.e_samples[0].size();
    unsigned int ny = _pimpl_->tab_prob.e_samples[1].size();
    pdf_interpolator.interp = gsl_interp2d_alloc(pdf_interpolator.choice, nx, ny);
    /* initialize interpolation */
    gsl_interp2d_init(pdf_interpolator.interp,
                      _pimpl_->tab_prob.e_samples[0].data(),
                      _pimpl_->tab_prob.e_samples[1].data(),
                      _pimpl_->tab_prob.prob.data(),
                      nx,
                      ny);
    return;
  }

  void dbd_gA::plot_interpolated_pdf(std::ostream & out_, const unsigned int nsamples_) const
  {
    double e1_min = _pimpl_->tab_prob.e_samples[0].front();
    double e1_max = _pimpl_->tab_prob.e_samples[0].back();
    double e1_step = (e1_max - e1_min) / nsamples_;
    double e2_min = _pimpl_->tab_prob.e_samples[1].front();
    double e2_max = _pimpl_->tab_prob.e_samples[1].back();
    double e2_step = (e2_max - e2_min) / nsamples_;
    for (unsigned int i = 0; i < nsamples_; ++i) {
      double xi = e1_min + (i + 0.5) * e1_step;
      for (unsigned int j = 0; j < nsamples_; ++j) {
        double yj = e2_min + (j + 0.5) * e2_step;
        double prob;
        int err_code = gsl_interp2d_eval_e(_pimpl_->pdf_interpolator.interp,
                                           _pimpl_->tab_prob.e_samples[0].data(),
                                           _pimpl_->tab_prob.e_samples[1].data(),
                                           _pimpl_->tab_prob.prob.data(),
                                           xi,
                                           yj,
                                           _pimpl_->pdf_interpolator.xacc,
                                           _pimpl_->pdf_interpolator.yacc,
                                           &prob);
        if (err_code == GSL_EDOM) {
          throw std::logic_error("bxdecay0::dbd_gA::plot_interpolated_pdf: Invalid E1/E2 values for interpolation!");
        }
        out_ <<  xi << ' ' <<  yj << ' ' << prob << std::endl;
      }
      out_ << std::endl;
    }
    
    return;
  }

  void dbd_gA::_load_tabulated_pdf_()
  {
    bool debug = false;
    // debug = true;
    std::ifstream f_tab_pdf(_tabulated_prob_file_path_.c_str());
    if (! f_tab_pdf) {
      throw std::logic_error("bxdecay0::dbd_gA::_load_tabulated_pdf_: Cannot open file '"
                             + _tabulated_prob_file_path_ + "'!");
    }
    unsigned int nlines = 0;
    bool parsed_esum = false;
    bool parsed_energy_sampling_header = false;
    int prob_index = 0; // Next expected prob sample
    int e2_pdf_count = 0;
    int pdf_count = 0;
    while (f_tab_pdf) {
      std::string raw_line;
      std::getline(f_tab_pdf, raw_line);
      nlines++;
      // if (debug) {
      //   std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_pdf_: raw_line = <" << raw_line << '>' << std::endl;
      // }
      if (raw_line.size() == 0) {
        if (debug) {
          std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_pdf_: Skip blank line." << std::endl;
        }
        continue;
      }
      {
        std::string first_word;
        std::istringstream ins(raw_line);
        ins >> first_word;
        if (first_word[0] == '#') {
          if (debug) {
            std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_pdf_: Skip comment line." << std::endl;
          }
          continue;
        }
      }
     
      // Parse energy sum (Qbb):
      if (!parsed_esum) {
        std::istringstream line_in(raw_line);
        line_in >> _pimpl_->tab_prob.esum_max;
        if (debug) {
          std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_pdf_: esum = " << _pimpl_->tab_prob.esum_max << std::endl;
        }
        if (!line_in) {
          throw std::logic_error("bxdecay0::dbd_gA::_load_tabulated_pdf_: Format error at line #"
                                 + std::to_string(nlines) + "!");
        }
        if (_pimpl_->tab_prob.esum_max <= 0.0) {
          throw std::logic_error("bxdecay0::dbd_gA::_load_tabulated_pdf_: Invalid Esum max value!");
        }
        parsed_esum = true;
        continue;
      }

      // Parse energy sampling header:
      if (! parsed_energy_sampling_header) {
        std::istringstream line_in(raw_line);
        std::string sampling_label;
        line_in >> sampling_label;
        if (debug) {
          std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_pdf_: sampling mode " << sampling_label << std::endl;
        }

        if (sampling_label != "Probability") {
          throw std::logic_error("bxdecay0::dbd_gA::_load_tabulated_pdf_: Unexpected probabibilty sampling '" + sampling_label + "'!");
        }
       
        _pimpl_->tab_prob.e_sampling[0] = tabulated_prob_type::SAMPLING_LINEAR;
        _pimpl_->tab_prob.e_sampling[1] = tabulated_prob_type::SAMPLING_LINEAR;
         
        line_in >> _pimpl_->tab_prob.e_min[0]
                >> _pimpl_->tab_prob.e_max[0]
                >> _pimpl_->tab_prob.energy_step
                >> _pimpl_->tab_prob.nsamples;
        if (!line_in) {
          throw std::logic_error("bxdecay0::dbd_gA::_load_tabulated_pdf_: Format error at line #"
                                 + std::to_string(nlines) + "!");
        }
        if (_pimpl_->tab_prob.e_min[0] < 0.0 or
            _pimpl_->tab_prob.e_min[0] >= _pimpl_->tab_prob.e_max[0]) {
          throw std::logic_error("bxdecay0::dbd_gA::_load_tabulated_pdf_: Invalid E range!");
        }
     
        _pimpl_->tab_prob.e_nsamples[0] = _pimpl_->tab_prob.nsamples;
        _pimpl_->tab_prob.e_nsamples[1] = _pimpl_->tab_prob.nsamples;
        _pimpl_->tab_prob.energies.reserve(_pimpl_->tab_prob.nsamples);
        _pimpl_->tab_prob.e_samples[0].reserve(_pimpl_->tab_prob.nsamples);
        _pimpl_->tab_prob.e_samples[1].reserve(_pimpl_->tab_prob.nsamples);
        _pimpl_->tab_prob.e_min[1] = _pimpl_->tab_prob.e_min[0];
        _pimpl_->tab_prob.e_max[1] = _pimpl_->tab_prob.e_max[0];
        // Recompute E step:
        _pimpl_->tab_prob.energy_step = (_pimpl_->tab_prob.e_max[0] - _pimpl_->tab_prob.e_min[0]) / (_pimpl_->tab_prob.nsamples - 1);
        for (int i = 0; i < (int) _pimpl_->tab_prob.nsamples; i++) {
          double ei = _pimpl_->tab_prob.e_min[0] + i * _pimpl_->tab_prob.energy_step;
          _pimpl_->tab_prob.energies.push_back(ei);
          _pimpl_->tab_prob.e_samples[0].push_back(ei);
          _pimpl_->tab_prob.e_samples[1].push_back(ei);
        }
        if (debug) {
          std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_pdf_: e_min[0] = " << _pimpl_->tab_prob.e_min[0] << " MeV " << std::endl;
          std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_pdf_: e_max[0] = " << _pimpl_->tab_prob.e_max[0] << " MeV " << std::endl;
          std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_pdf : e_min[1] = " << _pimpl_->tab_prob.e_min[1] << " MeV " << std::endl;
          std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_pdf_: e_max[1] = " << _pimpl_->tab_prob.e_max[1] << " MeV " << std::endl;
          std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_pdf_: energy_step = " << _pimpl_->tab_prob.energy_step << " MeV " << std::endl;
          std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_pdf_: nsamples = " << _pimpl_->tab_prob.nsamples << std::endl;
          std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_pdf_: # of energy samples  = " << _pimpl_->tab_prob.energies.size() << std::endl;
          std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_pdf_: min sampled energy   = " << _pimpl_->tab_prob.energies.front() << " MeV" << std::endl;
          std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_pdf_: max sampled energy   = " << _pimpl_->tab_prob.energies.back() << " MeV" << std::endl;
        }
        parsed_energy_sampling_header = true;
        continue;
      }
      
      // Load/parse a line of probabilities:
      {
        unsigned int n1 = _pimpl_->tab_prob.e_nsamples[0];
        unsigned int n2 = _pimpl_->tab_prob.e_nsamples[1];
        if (prob_index == 0) {
          _pimpl_->tab_prob.prob.reserve(n1 * n2);
        }
        unsigned int e2_expected_samples = _pimpl_->tab_prob.nsamples - e2_pdf_count;
        unsigned int e2_sample_count = 0;
        // std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_pdf_: raw_line = <" << raw_line << '>' << std::endl;
        std::istringstream line_in(raw_line);
        while (line_in and !line_in.eof()) {
          std::string word;
          line_in >> word;
          std::istringstream word_in(word);
          double prob;
          word_in >> prob;
          if (!word_in) {
            throw std::logic_error("bxdecay0::dbd_gA::_load_tabulated_pdf_: Format error for prob at line #"
                                   + std::to_string(nlines) + "!");     
          }
          if (prob < 0.0) {
            throw std::logic_error("bxdecay0::dbd_gA::_load_tabulated_pdf_: Invalid p.d.f. value [" + std::to_string(prob) + "] at line #"
                                   + std::to_string(nlines) + "!");
          }
          e2_sample_count++;
          int index1 = prob_index / n2;
          int index2 = prob_index % n2;
          double e1 = _pimpl_->tab_prob.e_samples[0][index1];
          double e2 = _pimpl_->tab_prob.e_samples[1][index2];
          if (e1 + e2 > _pimpl_->tab_prob.esum_max) {
            if (prob > 0.0) {
              throw std::logic_error("bxdecay0::dbd_g::_load_tabulated_pdf_: Invalid p.d.f. value [" + std::to_string(prob) + "] at line #"
                                     + std::to_string(nlines) + "! Should be zero!");
            }
          }
          _pimpl_->tab_prob.prob.push_back(prob);
          prob_index++; // skip to next expected sample
          if (_pimpl_->tab_prob.prob_max < 0.0 or prob > _pimpl_->tab_prob.prob_max) {
            _pimpl_->tab_prob.prob_max = prob;
          }
          line_in >> std::ws;
        }
        // Fill the table with zero probs for the interpolator:
        for (int i = e2_expected_samples; i < _pimpl_->tab_prob.e_nsamples[1]; i++) {
          _pimpl_->tab_prob.prob.push_back(0.0);
          prob_index++; 
        }        
        if (debug) {
          std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_pdf_: expected  E2 cprob count = " << e2_expected_samples << std::endl;
          std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_pdf_: effective E2 cprob count = " << e2_sample_count << std::endl;
        }
        if (e2_sample_count != e2_expected_samples) {
          throw std::logic_error("bxdecay0::dbd_gA::_load_tabulated_pdf_: expected vs effective E2 prob count match issue!");
        }
        if (debug) {
          std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_pdf_: E2 pdf count #"
                    << e2_pdf_count << " has " << e2_sample_count << " p.d.f. samples for E2" << std::endl;
        }
        e2_pdf_count++;
      }    
      f_tab_pdf >> std::ws;
      if (f_tab_pdf.eof()) {
        if (debug) {
          std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_pdf_: End of parsing input." << std::endl;
        }
        break;
      }
    }
    if (debug) {
      std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_pdf_: Energy sampling step = "
                << _pimpl_->tab_prob.energy_step << " MeV" << std::endl;
      std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_pdf_: Minimum sampled energy = "
                << std::to_string(_pimpl_->tab_prob.e_min[0]) << " MeV" << std::endl;
      std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_pdf_: Maximum sampled energy = "
                << std::to_string(_pimpl_->tab_prob.e_max[0]) << " MeV" << std::endl;
      std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_pdf_: Number of probability sampling points = "
                << _pimpl_->tab_prob.prob.size() << std::endl;
      std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_pdf_: Probability sampling is parsed." << std::endl;
    }
    return;
  }
  
  void dbd_gA::_load_tabulated_cdf_opt_()
  {
    bool debug = is_debug();
    debug = false;
    if (debug) {
      std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_cdf_opt_: Loading c.d.f. file = '" << _tabulated_prob_file_path_ << "'" << std::endl;
    }
    std::ifstream f_tab_cdf(_tabulated_prob_file_path_.c_str());
    if (! f_tab_cdf) {
      throw std::logic_error("bxdecay0::dbd_gA::_load_tabulated_cdf_opt_: Cannot open file '"
                             + _tabulated_prob_file_path_ + "'!");
    }
    unsigned int nlines = 0;
    int prob_count = 0;
    bool parsed_esum = false;
    bool parsed_energy_sampling_header = false;
    bool parsed_e1_cdf = false;
    int e2_cdf_count = 0;

    while (f_tab_cdf) {
      std::string raw_line;
      std::getline(f_tab_cdf, raw_line);
      nlines++;
      // if (debug) {
      //   std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_cdf_opt_: raw_line = <" << raw_line << '>' << std::endl;
      // }
      if (raw_line.size() == 0) {
        if (debug) {
          std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_cdf_opt_: Skip blank line." << std::endl;
        }
        continue;
      }
      {
        std::string first_word;
        std::istringstream ins(raw_line);
        ins >> first_word;
        if (first_word[0] == '#') {
          if (debug) {
            std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_cdf_opt_: Skip comment line." << std::endl;
          }
          continue;
        }
      }
      
      // Parse energy sum (Qbb):
      if (!parsed_esum) {
        std::istringstream line_in(raw_line);
        line_in >> _pimpl_->tab_prob.esum_max;
        if (debug) {
          std::cerr << "[devel] bxdecay0::dbd_gA::_load_tabulated_cdf_opt_: esum = " << _pimpl_->tab_prob.esum_max << std::endl;
        }
        if (!line_in) {
          throw std::logic_error("bxdecay0::dbd_gA::_load_tabulated_cdf_opt_: Format error at line #"
                                 + std::to_string(nlines) + "!");
        }
        if (_pimpl_->tab_prob.esum_max <= 0.0) {
          throw std::logic_error("bxdecay0::dbd_gA::_load_tabulated_cdf_opt_: Invalid Esum max value!");
        }
        parsed_esum = true;
        continue;
      }

      // Parse energy sampling header:
      if (! parsed_energy_sampling_header) {
        std::istringstream line_in(raw_line);
        std::string sampling_label;
        line_in >> sampling_label;
        if (debug) {
          std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_cdf_opt_: sampling mode " << sampling_label << std::endl;
        }

        if (sampling_label != "CumulativeProbability") {
          throw std::logic_error("bxdecay0::dbd_gA::_load_tabulated_cdf_opt_: Unexpected probabibilty mode '" + sampling_label + "'!");
        }
        
        _pimpl_->tab_prob.e_sampling[0] = tabulated_prob_type::SAMPLING_LINEAR;
        _pimpl_->tab_prob.e_sampling[1] = tabulated_prob_type::SAMPLING_LINEAR;
        
        line_in >> _pimpl_->tab_prob.e_min[0]
                >> _pimpl_->tab_prob.e_max[0]
                >> _pimpl_->tab_prob.energy_step
                >> _pimpl_->tab_prob.nsamples;
        if (!line_in) {
          throw std::logic_error("bxdecay0::dbd_gA::_load_tabulated_cdf_opt_: Format error at line #"
                                 + std::to_string(nlines) + "!");
        }
        if (_pimpl_->tab_prob.e_min[0] < 0.0 or
            _pimpl_->tab_prob.e_min[0] >= _pimpl_->tab_prob.e_max[0]) {
          throw std::logic_error("bxdecay0::dbd_gA::_load_tabulated_cdf_opt_: Invalid E range!");
        }
     
        _pimpl_->tab_prob.energies.reserve(_pimpl_->tab_prob.nsamples);
        _pimpl_->tab_prob.e_min[1] = _pimpl_->tab_prob.e_min[0];
        _pimpl_->tab_prob.e_max[1] = _pimpl_->tab_prob.e_max[0];
        // Recompute E step:
        _pimpl_->tab_prob.energy_step = (_pimpl_->tab_prob.e_max[0] - _pimpl_->tab_prob.e_min[0]) / (_pimpl_->tab_prob.nsamples - 1);
        for (int i = 0; i < (int) _pimpl_->tab_prob.nsamples; i++) {
          double ei = _pimpl_->tab_prob.e_min[0] + i * _pimpl_->tab_prob.energy_step;
          _pimpl_->tab_prob.energies.push_back(ei);
        }
        
        if (debug) {
          std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_cdf_opt_: e_min[0] = " << _pimpl_->tab_prob.e_min[0] << " MeV " << std::endl;
          std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_cdf_opt_: e_max[0] = " << _pimpl_->tab_prob.e_max[0] << " MeV " << std::endl;
          std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_cdf_opt_: e_min[1] = " << _pimpl_->tab_prob.e_min[1] << " MeV " << std::endl;
          std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_cdf_opt_: e_max[1] = " << _pimpl_->tab_prob.e_max[1] << " MeV " << std::endl;
          std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_cdf_opt_: energy_step  = " << _pimpl_->tab_prob.energy_step << " MeV " << std::endl;
          std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_cdf_opt_: nsamples = " << _pimpl_->tab_prob.nsamples << std::endl;
          std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_cdf_opt_: # of energy samples  = " << _pimpl_->tab_prob.energies.size() << std::endl;
          std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_cdf_opt_: min sampled energy   = " << _pimpl_->tab_prob.energies.front() << " MeV" << std::endl;
          std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_cdf_opt_: max sampled energy   = " << _pimpl_->tab_prob.energies.back() << " MeV" << std::endl;
        }
        parsed_energy_sampling_header = true;
        continue;
      }

      // Parse E1 cumulative probability sampling:
      if ( ! parsed_e1_cdf) {
        std::istringstream line_iss(raw_line);
        load_optimized_cdf_array(raw_line, _pimpl_->tab_prob.e1_cprobs);
        parsed_e1_cdf = true;
        // Prepare the number of e2 energy samples for a c.d.f. probs line:
        _pimpl_->tab_prob.e2_cprobs.reserve(_pimpl_->tab_prob.e1_cprobs.size());
        if (debug) {
          std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_cdf_opt_: # of energy samples  = " << _pimpl_->tab_prob.e1_cprobs.size() << std::endl;
          std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_cdf_opt_: min sampled cprob   = " << _pimpl_->tab_prob.e1_cprobs.front() << std::endl;
          std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_cdf_opt_: max sampled cprob   = " << _pimpl_->tab_prob.e1_cprobs.back() << std::endl;
        }
        continue;
      }
      
      // Load/parse a line of E2 cumulative probabilities per E1 sample:
      {
        {
          static std::vector<double> empty;
          _pimpl_->tab_prob.e2_cprobs.push_back(empty);
        }
        std::vector<double> & cdf_probs = _pimpl_->tab_prob.e2_cprobs.back();
        unsigned int e2_expected_samples = _pimpl_->tab_prob.nsamples - e2_cdf_count;
        cdf_probs.reserve(e2_expected_samples);
        load_optimized_cdf_array(raw_line, cdf_probs);

        if (debug) {
          std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_cdf_opt_: expected  E2 cprob count  = " << e2_expected_samples << std::endl;
          std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_cdf_opt_: effective E2 cprob count = " << cdf_probs.size() << std::endl;
        }
        if (cdf_probs.size() != e2_expected_samples) {
          throw std::logic_error("bxdecay0::dbd_gA::_load_tabulated_cdf_opt_: expected vs effective E2 cprob count match issue!");
        }
        e2_cdf_count++;
        if (debug) {
          std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_cdf_opt_: E2 cdf count #" << e2_cdf_count << " has " << cdf_probs.size() << " c.d.f. samples for E2" << std::endl;
          std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_cdf_opt_:  - min cumul prob = " << cdf_probs.front() << std::endl;
          std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_cdf_opt_:  - max cumul prob = " << cdf_probs.back() << std::endl;
        }
      }
      
      f_tab_cdf >> std::ws;
      if (f_tab_cdf.eof()) {
        if (debug) {
          std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_cdf_: End of parsing input." << std::endl;
        }
        break;
      }
    } // while getline loop
    if (debug) {
      std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_cdf_opt_: Energy sampling step = "
                << std::to_string(_pimpl_->tab_prob.energy_step) << " MeV" << std::endl;
      std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_cdf_opt_: Minimum sampled energy = "
                << std::to_string(_pimpl_->tab_prob.e_min[0]) << " MeV" << std::endl;
      std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_cdf_opt_: Maximum sampled energy = "
                << std::to_string(_pimpl_->tab_prob.e_max[0]) << " MeV" << std::endl;
      std::cerr << "[debug] bxdecay0::dbd_gA::_load_tabulated_cdf_opt_: Cumulative probability sampling is parsed." << std::endl;
    }
    return;
  }
   
  void dbd_gA::reset()
  {
    if (!is_initialized()) {
      throw std::logic_error("bxdecay0::dbd_gA::reset: Generator is not initialized!");
    }
    _initialized_ = false;

    // Clean the working structure:
    _pimpl_.reset();
    _tabulated_prob_file_path_.clear();
    
    // Reset configuration:
    _nuclide_.clear();
    _process_ = PROCESS_UNDEF;
    _shooting_ = SHOOTING_UNDEF;
    return;
  }

  void dbd_gA::print(std::ostream & out_,
                     const std::string & title_,
                     const std::string & indent_) const
  {
    if (!title_.empty()) {
      out_ << indent_ << title_ << "\n";
    }
    static const std::string tag = "|-- ";
    static const std::string last_tag = "`-- ";
    static const std::string skip_tag = "|   ";
    out_ << indent_ << tag << "Nuclide : '" << _nuclide_ << "'" << std::endl;
    out_ << indent_ << tag << "Process : '" << process_label(_process_) << "'" <<  std::endl;
    out_ << indent_ << tag << "Tabulated prob file path : '" << _tabulated_prob_file_path_ << "'" <<  std::endl;
    if (is_initialized()) {
      if (_shooting_ == SHOOTING_REJECTION) { 
        out_ << indent_ << tag << "Tabulated p.d.f : " << std::endl;
        out_ << indent_ << skip_tag << tag << "esum(max) = " << _pimpl_->tab_prob.esum_max << " MeV" << std::endl;
        for (int i = 0; i < 2; i++) {
          out_ << indent_ << skip_tag << tag << "e" << i+1 << "(nsamples) = " << _pimpl_->tab_prob.e_nsamples[i] << std::endl;
          out_ << indent_ << skip_tag << tag << "e" << i+1 << "(min) = " << _pimpl_->tab_prob.e_min[i] << " MeV" << std::endl;
          out_ << indent_ << skip_tag << tag << "e" << i+1 << "(max) = " << _pimpl_->tab_prob.e_max[i] << " MeV" << std::endl;
        }
        out_ << indent_ << skip_tag << last_tag << "Prob(max) = " << _pimpl_->tab_prob.prob_max << std::endl;
        out_ << indent_ << tag << "P.d.f Interpolator : " << std::endl;
        out_ << indent_ << skip_tag << last_tag << "Name : '" << gsl_interp2d_name(_pimpl_->pdf_interpolator.interp) << "'" << std::endl;
      } else if (_shooting_ == SHOOTING_INVERSE_TRANSFORM_METHOD) {
        out_ << indent_ << tag << "Tabulated c.d.f : " << std::endl;
        out_ << indent_ << skip_tag << tag << "esum(max) = " << _pimpl_->tab_prob.esum_max << " MeV" << std::endl;
        for (int i = 0; i < 2; i++) {
          out_ << indent_ << skip_tag << tag << "e" << i+1 << "(nsamples) = " << _pimpl_->tab_prob.e_nsamples[i] << std::endl;
          out_ << indent_ << skip_tag << tag << "e" << i+1 << "(min) = " << _pimpl_->tab_prob.e_min[i] << " MeV" << std::endl;
          out_ << indent_ << skip_tag << tag << "e" << i+1 << "(max) = " << _pimpl_->tab_prob.e_max[i] << " MeV" << std::endl;
        }
        out_ << indent_ << skip_tag << tag << "# e1/e2 energy prob samples = " << _pimpl_->tab_prob.energies.size() << std::endl;
        out_ << indent_ << skip_tag << tag << "e1/e2 energy_step           = " << _pimpl_->tab_prob.energy_step << " MeV" << std::endl;
        out_ << indent_ << skip_tag << tag << "# c.d.f. prob e1 sampled energies = " << _pimpl_->tab_prob.e1_cprobs.size() << std::endl;
        out_ << indent_ << skip_tag << last_tag << "# c.d.f. prob e2 sampled energies = " << _pimpl_->tab_prob.e2_cprobs.size() << std::endl;
      }
    }
    out_ << indent_  << last_tag << "Initialized : " << std::boolalpha << _initialized_ << std::endl;
    return;
  }

  void dbd_gA::shoot_e1_e2(i_random & prng_, double & e1_, double & e2_)
  {
    e1_ = std::numeric_limits<double>::quiet_NaN();
    e2_ = std::numeric_limits<double>::quiet_NaN();

    if (_shooting_ == SHOOTING_REJECTION) {
      _shoot_e1_e2_rejection_(prng_, e1_, e2_);
    }
    if (_shooting_ == SHOOTING_INVERSE_TRANSFORM_METHOD) {
      _shoot_e1_e2_inverse_transform_method_(prng_, e1_, e2_);
    }
    
    return;
  }

  void dbd_gA::shoot_cos_theta(i_random & prng_, const double e1_, const double e2_, double & cos12_)
  {
    static const double emass = decay0_emass(); //MeV
    static const double twopi = 2. * M_PI;
    double p1 = std::sqrt(e1_ * (e1_ + 2. * emass));
    double p2 = std::sqrt(e2_ * (e2_ + 2. * emass));
    double b1 = p1 / (e1_ + emass);
    double b2 = p2 / (e2_ + emass);
    // Sampling the angles with angular correlation:
    double a = 1.;
    double b = -b1 * b2;
    double c = 0.;
    // Rejection method:
    double pmax = a + std::abs(b) + c;
    double cos12;  
    double p;
    do {
      p = pmax * prng_();
      cos12 = 1. - 2. * prng_();
    } while (p > a + b * cos12 + c * gsl_pow_2(cos12));
    cos12_ = cos12;
    return;
  }
   
  void dbd_gA::_shoot_e1_e2_rejection_(i_random & prng_, double & e1_, double & e2_)
  {
    while (true) {
      double r1 = prng_();
      double r2 = prng_();
      if (r1 + r2 > 1.0) {
        r1 = 1.0 - r1;
        r2 = 1.0 - r2;
      }
      // Beware: E1 or E2 < emin is not taken into account (low energy cut):
      double e1 = _pimpl_->tab_prob.e_samples[0].front() + r1 * (_pimpl_->tab_prob.e_samples[0].back() - _pimpl_->tab_prob.e_samples[0].front());
      double e2 = _pimpl_->tab_prob.e_samples[1].front() + r2 * (_pimpl_->tab_prob.e_samples[1].back() - _pimpl_->tab_prob.e_samples[1].front());
      double ptest = prng_() * _pimpl_->tab_prob.prob_max * 1.00001;
      double p = gsl_interp2d_eval(_pimpl_->pdf_interpolator.interp,
                                   _pimpl_->tab_prob.e_samples[0].data(),
                                   _pimpl_->tab_prob.e_samples[1].data(),
                                   _pimpl_->tab_prob.prob.data(),
                                   e1,
                                   e2,
                                   _pimpl_->pdf_interpolator.xacc,
                                   _pimpl_->pdf_interpolator.yacc);
      if (ptest < p and (e1 + e2 < _pimpl_->tab_prob.esum_max)) {
        e1_ = e1;
        e2_ = e2;
        break;
      }
    }
    return;
  }
  
  void dbd_gA::_shoot_e1_e2_inverse_transform_method_(i_random & prng_, double & e1_, double & e2_)
  {
    bool debug = is_debug();
    debug = false;
    e1_ = 0.0;
    e2_ = 0.0;
    double e1_rand = prng_();
    int ie1_found = -1;
    for (unsigned int ie1 = 0; ie1 < _pimpl_->tab_prob.e1_cprobs.size(); ie1++) {
      if (e1_rand <= _pimpl_->tab_prob.e1_cprobs[ie1]) {
        ie1_found = ie1;
        break;
      }
    }
    if (ie1_found == -1) {
      throw std::logic_error("bxdecay0::dbd_gA::_shoot_inverse_transform_method_: Cound not find the E1 c.d.f. sample!"); 
    }
    if (debug) {
      std::cerr << "[debug] bxdecay0::dbd_gA::_shoot_inverse_transform_method_: Found the E1 c.d.f. sample #" << ie1_found << " < " << _pimpl_->tab_prob.e1_cprobs.size() << std::endl;
      std::cerr.precision(16);
      std::cerr << "[debug] bxdecay0::dbd_gA::_shoot_inverse_transform_method_:  - min prob = " << _pimpl_->tab_prob.e1_cprobs[ie1_found-1] << std::endl;
      std::cerr << "[debug] bxdecay0::dbd_gA::_shoot_inverse_transform_method_:  - max prob = " << _pimpl_->tab_prob.e1_cprobs[ie1_found] << std::endl;
      std::cerr << "[debug] bxdecay0::dbd_gA::_shoot_inverse_transform_method_:  - prob     = " << e1_rand << std::endl;
    }
    const std::vector<double> & sampled_e2cdf = _pimpl_->tab_prob.e2_cprobs[ie1_found];
    int je2_found = -1;
    double e2_rand = prng_();
    for (unsigned int je2 = 0; je2 < sampled_e2cdf.size(); je2++) {
      if (e2_rand <= sampled_e2cdf[je2]) {
        je2_found = je2;
        break;
      }
    }
    if (je2_found == -1) {
      throw std::logic_error("bxdecay0::dbd_gA::_shoot_inverse_transform_method_: Cound not find the E2 c.d.f. sample!"); 
    }
    if (debug) {
      std::cerr << "[debug] bxdecay0::dbd_gA::_shoot_inverse_transform_method_: Found the E2 c.d.f. sample #" << je2_found << " < " << sampled_e2cdf.size() << std::endl;
      std::cerr.precision(16);
      std::cerr << "[debug] bxdecay0::dbd_gA::_shoot_inverse_transform_method_:  - min prob = " << sampled_e2cdf[je2_found-1] << std::endl;
      std::cerr << "[debug] bxdecay0::dbd_gA::_shoot_inverse_transform_method_:  - max prob = " << sampled_e2cdf[je2_found] << std::endl;
      std::cerr << "[debug] bxdecay0::dbd_gA::_shoot_inverse_transform_method_:  - prob     = " << e2_rand << std::endl;
    }
    
    // E1 sampling:
    double e1_max = _pimpl_->tab_prob.energies[ie1_found];
    double cprob1_max = _pimpl_->tab_prob.e1_cprobs[ie1_found];
    double cprob1_min = 0.0;
    double e1_min = 0.0;
    if (ie1_found > 0) {
      e1_min = _pimpl_->tab_prob.energies[ie1_found - 1];
      cprob1_min = _pimpl_->tab_prob.e1_cprobs[ie1_found - 1];
    }
    double re1 = (e1_rand - cprob1_min) / (cprob1_max - cprob1_min);
    e1_ = e1_min + (e1_max - e1_min) * re1;
    // e1_ = e1_max;
    // if (e1_ < 0.0) {
    //   std::cerr << "[trace] ie1_found=" << ie1_found << std::endl;
    //   std::cerr << "[trace] e1_rand=" << e1_rand << std::endl;
    //   std::cerr << "[trace] cprob1_min=" << cprob1_min << std::endl;
    //   std::cerr << "[trace] cprob1_max=" << cprob1_max << std::endl;
    //   std::cerr << "[trace] re1=" << re1 << std::endl;
    // }

    // E2 sampling:
    double e2_max = _pimpl_->tab_prob.energies[je2_found];
    double cprob2_max = sampled_e2cdf[je2_found];
    double cprob2_min = 0.0;
    double e2_min = 0.0;
    if (je2_found > 0) {
      e2_min = _pimpl_->tab_prob.energies[je2_found - 1];
      cprob2_min = sampled_e2cdf[je2_found - 1];
    }
    double re2 = (e2_rand - cprob2_min) / (cprob2_max - cprob2_min);
    e2_ = e2_min + (e2_max - e2_min) * re2;
    // e2_ = e2_max;
    // if (e2_ < 0.0) {
    //   std::cerr << "[trace] je2_found=" << je2_found << std::endl;
    //   std::cerr << "[trace] e2_rand=" << e2_rand << std::endl;
    //   std::cerr << "[trace] cprob2_min=" << cprob2_min << std::endl;
    //   std::cerr << "[trace] cprob2_max=" << cprob2_max << std::endl;
    //   std::cerr << "[trace] re2=" << re2 << std::endl;
    // }
    
    return;
  }
 
  // static
  void dbd_gA::export_to_event(i_random & prng_,
                               const double e1_,
                               const double e2_,
                               const double cos12_,
                               event & ev_)
  {
    // Clear the target eventd
    ev_.reset();
    ev_.set_generator("dbd_gA"); // Useful information (not mandatory)
    ev_.set_time(0.0); // Default decay time set to zero (unit: second)
     
    // Fill the event with two beta particles and the proper
    // kinematics and randomize the emission direction...
    // See "bxdecay0/event.h" and "bxdecay0/particle.h".
    static const double emass = decay0_emass(); //MeV
    static const double twopi = 2. * M_PI;
    double p1 = std::sqrt(e1_ * (e1_ + 2. * emass));
    double p2 = std::sqrt(e2_ * (e2_ + 2. * emass));
    double b1 = p1 / (e1_ + emass);
    double b2 = p2 / (e2_ + emass);
    double p1x = 0.0;
    double p1y = 0.0;
    double p1z = p1;
    vector3 vp1 = make_vector3(p1x, p1y, p1z);
    double sin12 = std::sqrt(1.0 - cos12_);
    double p2x = 0.0;
    double p2y = p2 * sin12;
    double p2z = p2 * cos12_;
    vector3 vp2 = make_vector3(p2x, p2y, p2z);
    // Isotropic randomization of the rotation:
    double phi = twopi * prng_();
    double theta = std::acos(-1.0 + 2 * prng_());
    double psi = twopi * prng_();
    vector3 rvp1 = rotate_zyz(vp1, phi, theta, psi);
    vector3 rvp2 = rotate_zyz(vp2, phi, theta, psi);
    // Built the particles:
    particle particle;
    particle.set_time(0.);
    particle.set_code(ELECTRON);
    // First electron :
    particle.set_momentum(rvp1.x,
                          rvp1.y,
                          rvp1.z);
    ev_.add_particle(particle);
    // Second electron :
    particle.set_momentum(rvp2.x,
                          rvp2.y,
                          rvp2.z);
    ev_.add_particle(particle);
    return;
  }

  void dbd_gA::shoot(i_random & prng_, event & ev_)
  {
    double e1, e2, cos12;
    this->shoot_e1_e2(prng_, e1, e2);
    this->shoot_cos_theta(prng_, e1, e2, cos12);
    export_to_event(prng_, e1, e2, cos12, ev_);
    return;
  }

  void load_optimized_cdf_array(const std::string & in_str_, std::vector<double> & tab_cprobs_)
  {
    bool debug = false;
    // debug = true;
    tab_cprobs_.clear();
    if (debug) {
      std::cerr << "[debug] input string : <" << in_str_ << '>' << std::endl;
    }
    std::istringstream in(in_str_);
    if (!in) {
      throw std::logic_error("bxdecay0::load_optimized_cdf_array: Cannot read input stream !");
    }
    int cur9 = -1;
    double bias9 = 0.0;
    in >> std::ws;
    int token_count = 0;
    while (in) {
      double cprob = 0.0;
      std::string token;
      in >> token;
      token_count++;
      if (debug) {
        std::cerr << "[debug] Token #" << token_count << " : " << token << std::endl;
      }
      if (token[0] == '^') {
        std::string cur9str = token.substr(1);
        int this_cur9 = std::atoi(cur9str.c_str());
        if (this_cur9 > cur9) {
          cur9 = this_cur9;
          bias9 = 1.0 - std::pow(10, -cur9);
        }
        continue;
      } else if (token == "!1") {
        cprob = 1.0;
      } else {
        double digits;
        std::istringstream din(token);
        din >> digits;
        if (!din) {
          throw std::logic_error("bxdecay0::load_optimized_cdf_array: Format error at token '" + std::to_string(token_count) + "'!");   
        }
        cprob = bias9 + digits * std::pow(10, -(cur9 + 1));
      }
      if (debug) {
        std::cerr.precision(16);
        std::cerr << "[debug] cprob #" << token_count << " = " << cprob << std::endl;
      }
      tab_cprobs_.push_back(cprob);
      in >> std::ws;
      if (in.eof()) {
        break;
      }
    }
    return;    
  }

} // end of namespace bxdecay0
