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
// decay0_generator.cc

// Ourselves:
#include "bxdecay0_clparser.hpp"

// Standard library:
#include <stdexcept>
#include <sstream>

namespace bxdecay0 {

  cl_parser::cl_parser(int argc_, char ** argv_)
  {
    _args_.reserve(argc_);
    for (int i = 1; i < argc_; i++) {
      _args_.push_back(argv_[i]);
      // std::clog << "Arg #" << i << " : " << _args_.back() << '\n';
    }
    return;
  }
    
  cl_parser::~cl_parser()
  {
    if (_parsing_context_.parse_error) {
      std::cerr << "error: There was some parse error: \n";
      if (! _parsing_context_.error_message.empty()) {
        std::cerr << "\n  " << _parsing_context_.error_message << "\n\n";
      }
      std::cerr << "error: Please check your command line options ! \n";
      std::cerr << "error: Current command line was : \n\n  bxdecay0-run ";
      for (const std::string & tok :_args_) {
        std::cerr << tok << ' ';
      }
      std::cerr << "\n\n";
    }
    if (_parsing_context_.help or _parsing_context_.parse_error) {
      std::cerr << "\n";
      std::cerr << "bxdecay0-run : BxDecay0 decay generator\n";
      std::cerr << "\n";
      std::cerr << "Usage : \n";
      std::cerr << "\n";
      std::cerr << "  bxdecay0-run [options...] [basename]\n";
      std::cerr << "\n";
      std::cerr << "Options : \n";
      std::cerr << "                                                     \n";
      std::cerr << "  --help (-h)                : Print this help then exit      \n";
      std::cerr << "  --logging (-g) STRING      : Set the logging level (default: \"mute\", supported values: \"mute\", \"verbose\", \"debug\")\n";
      std::cerr << "  --seed (-s) INTVAL         : Set the seed for the internal random generator (default: 314159)\n";
      std::cerr << "  --nb-events (-b) INTVAL    : Set the number of generated decay events (default: 1) \n";
      std::cerr << "  --decay-category (-c) NAME : Set the decay category (supported values: \"dbd\" of \"background\")\n";
      std::cerr << "  --nuclide (-N) NAME        : Set the name of the decaying nuclide \n";
      std::cerr << "  --level (-l) INTVAL        : Set the level of the daughter nuclide (default: 0 (g.s.))\n";
      std::cerr << "  --dbd-mode (-m) INTVAL     : Set the double beta decay mode (supported values: [" << DBDMODE_MIN << "," << DBDMODE_MAX << "])\n";
      std::cerr << "  --dbd-emin (-e) REALVAL    : Set the double beta decay minimum sum energy (in MeV, only for some \"dbd\" decay modes)\n";
      std::cerr << "  --dbd-emax (-E) REALVAL    : Set the double beta decay maximum sum energy (in MeV, only for some \"dbd\" decay modes)\n";
      std::cerr << "  --activity (-a) REALVAL    : Set the activity (>0.0, in Bq, default: not set)\n";
      std::cerr << "  --basename (-b) STRING     : Set the basename of output files (default: \"/tmp/bxdecay0-run\")\n";
      std::cerr << "  PGOps' special options :\n";
      std::cerr << "  --pgop-mdl-particle STRING       : [MDL] Set the name of the selected particle (default: \"all\")\n";
      std::cerr << "  --pgop-mdl-rank INTVAL           : [MDL] Set the rank of the target particle (default: -1)\n";
      std::cerr << "  --pgop-mdl-cone-phi REALVAL      : [MDL] Set the longitude of the emission cone (unit: degree, default: 0)\n";
      std::cerr << "  --pgop-mdl-cone-theta REALVAL    : [MDL] Set the colatitude of the emission cone (unit: degree, default: 0)\n";
      std::cerr << "  --pgop-mdl-cone-aperture REALVAL : [MDL] Set the aperture of the emission cone (unit: degree, default: 0)\n";
      std::cerr << "                                                     \n";
      std::cerr << "Parameters : \n";
      std::cerr << "                                                     \n";
      std::cerr << "  basename : the basename of filename for generated events\n";
      std::cerr << "              storage and companion information file.\n";
      std::cerr << "                                                     \n";
      std::cerr << "Examples:                                            \n\n";
      std::cerr << "  The following command generates ten decay events from the Co60 nuclide\n";
      std::cerr << "  and stores them in the '/tmp/genCo60.d0t' file using a very simple ASCII\n";
      std::cerr << "  format. The '/tmp/genCo60.d0m' companion 'key=value' ASCII formatted file\n";
      std::cerr << "  is also created to store associated informations.\n";
      std::cerr << "  Both files are easy to parse from external applications:\n";
      std::cerr << "                                                     \n";
      std::cerr << "    bxdecay0-run -s 314159 -n 10 -c background -N \"Co60\" \"/tmp/genCo60\" \n";
      std::cerr << "                                                     \n";
      std::cerr << "  The following command generates four decay events from the Cs137 nuclide\n";
      std::cerr << "  and stores them in the '/tmp/genCs137.d0t' file using a very simple ASCII\n";
      std::cerr << "  format. The '/tmp/genCs137.d0m' companion 'key=value' ASCII formatted file\n";
      std::cerr << "  is also created to store associated informations. The MDL PGOp algorithm is used\n";
      std::cerr << "  for biasing the momentum direction of the first electron within each event.\n";
      std::cerr << "  The favored emission cone is aligned along the X-axis with a 5° half-aperture.\n";
      std::cerr << "                                                     \n";
      std::cerr << "    bxdecay0-run -s 314159 -n 4 -c background -N \"Cs137+Ba137m\" \\\n";
      std::cerr << "      --pgop-mdl-particle \"e-\" --pgop-mdl-rank 0 \\\n";
      std::cerr << "      --pgop-mdl-cone-phi 0.0 --pgop-mdl-cone-theta 90.0  \\\n";
      std::cerr << "      --pgop-mdl-cone-aperture 5.0  \\\n";
      std::cerr << "      \"/tmp/genCs137\" \n";
      std::cerr << "                                                     \n";
    }
    return;
  }

  cl_parser::parse_status_type cl_parser::parse(driver::config_type & config_)
  {
    parse_status_type ps = PS_OK;
    try {
      int iarg = 0;
      while (iarg < _args_.size()) {

        std::string arg = _args_[iarg];
        if (arg[0] == '-') {
          if (arg == "-h" or arg == "--help") {
            _parsing_context_.help = true;
            ps = PS_USAGE;
            break;
          } else if (arg == "-g" or arg == "--logging") {
            std::string token = _args_[++iarg];
            driver::logging_type logging =  driver::logging_from_string(token);
            if (logging == driver::LOGGING_UNDEFINED) {
              throw std::logic_error("bxdecay0::cl_parser::parse: invalid logging level '" + token + "'!");
            }
            config_.logging = logging;
          } else if (arg == "-n" or arg == "--nb-events") {
            std::string token = _args_[++iarg];
            int nb_events = std::stoi(token);
            if (nb_events < 1) {
              throw std::logic_error("bxdecay0::cl_parser::parse: invalid number of events " + std::to_string(nb_events) + "!");
            }
            config_.nb_events = nb_events;
          } else if (arg == "-s" or arg == "--seed") {
            std::string token = _args_[++iarg];
            int seed = std::stoi(token);
            if (seed < 0) {
              throw std::logic_error("bxdecay0::cl_parser::parse: invalid seed " + std::to_string(seed) + "!");
            }
            config_.seed = seed;
          } else if (arg == "-N" or arg == "--nuclide") {
            std::string token = _args_[++iarg];
            config_.nuclide = token;
          } else if (arg == "-l" or arg == "--level") {
            std::string token = _args_[++iarg];
            int level = std::stoi(token);
            if (level < 0) {
              throw std::logic_error("bxdecay0::cl_parser::parse: invalid daughter level " + std::to_string(level) + "!");
            }
            config_.level = level;
          } else if (arg == "-c" or arg == "--decay-category") {
            std::string token = _args_[++iarg];
            if (token == "dbd") {
              config_.decay_category = decay0_generator::DECAY_CATEGORY_DBD;
            } else if (token == "background") {
              config_.decay_category = decay0_generator::DECAY_CATEGORY_BACKGROUND;
            } else {
              throw std::logic_error("bxdecay0::cl_parser::parse: unsupported decay category '" + token + "'!");
            }
          } else if (arg == "-m" or arg == "--dbd-mode") {
            std::string token = _args_[++iarg];
            int dbd_mode = std::stoi(token);
            if (dbd_mode < DBDMODE_MIN or dbd_mode > DBDMODE_MAX) {
              throw std::logic_error("bxdecay0::cl_parser::parse: invalid DBD decay mode " + std::to_string(dbd_mode) + "!");
            }
            config_.dbd_mode = static_cast<dbd_mode_type>(dbd_mode);
          } else if (arg == "-e" or arg == "--dbd-emin") {
            std::string token = _args_[++iarg];
            double dbd_emin = std::stod(token);
            if (dbd_emin < 0.0) {
              throw std::logic_error("bxdecay0::cl_parser::parse: invalid minimum DBD energy " + std::to_string(dbd_emin) + "!");
            }
            config_.energy_min_MeV = dbd_emin;
          } else if (arg == "-E" or arg == "--dbd-emax") {
            std::string token = _args_[++iarg];
            double dbd_emax = std::stod(token);
            if (dbd_emax < 0.0) {
              throw std::logic_error("bxdecay0::cl_parser::parse: invalid maximum DBD energy " + std::to_string(dbd_emax) + "!");
            }
            config_.energy_max_MeV = dbd_emax;
          } else if (arg == "-a" or arg == "--activity") {
            std::string token = _args_[++iarg];
            double activity = std::stod(token);
            if (activity < 0.0) {
              throw std::logic_error("bxdecay0::cl_parser::parse: invalid activity " + token + "!");
            }
            config_.activity_Bq = activity;
          } else if (arg == "-b" or arg == "--basename") {
            std::string token = _args_[++iarg];
            config_.basename = token;
          } else if (arg == "--pgop-mdl-particle") {
            std::string token = _args_[++iarg];
            config_.use_mdl = true;
            config_.mdl_config.particle_label = token;
          } else if (arg == "--pgop-mdl-rank") {
            std::string token = _args_[++iarg];
            config_.use_mdl = true;
            config_.mdl_config.target_particle_rank = std::stoi(token);
          } else if (arg == "--pgop-mdl-cone-phi") {
            std::string token = _args_[++iarg];
            config_.use_mdl = true;
            config_.mdl_config.cone_phi_degree = std::stod(token);
          } else if (arg == "--pgop-mdl-cone-theta") {
            std::string token = _args_[++iarg];
            config_.use_mdl = true;
            config_.mdl_config.cone_theta_degree = std::stod(token);
          } else if (arg == "--pgop-mdl-cone-aperture") {
            std::string token = _args_[++iarg];
            config_.use_mdl = true;
            config_.mdl_config.cone_aperture_degree = std::stod(token);
          } else {
            throw std::logic_error("bxdecay0::cl_parser::parse: unsupported command line option '" + arg + "'!");
          }

        } else {
          if (config_.basename.empty()) {
            config_.basename = arg;
          } else {
            throw std::logic_error("bxdecay0::cl_parser::parse: unrecognized command line parameter '" + arg + "'!");
          }
        }
        iarg++;
      }
    } catch (std::exception & parse_error) {
      _parsing_context_.parse_error = true;
      std::ostringstream eout;
      eout << parse_error.what();
      _parsing_context_.error_message = eout.str();
      ps = PS_ERROR;
    }
    return ps;
  }
 
} // namespace bxdecay0
