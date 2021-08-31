// Copyright 1995-2016 V.I. Tretyak
// Copyright 2011-2017 F. Mauger
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
#include <bxdecay0/genbbsub.h>

// Standard library:
#include <cmath>
#include <limits>
#include <sstream>
#include <stdexcept>

// This project:
#include <bxdecay0/Ac228.h>
#include <bxdecay0/Am241.h>
#include <bxdecay0/Ar39.h>
#include <bxdecay0/Ar42.h>
#include <bxdecay0/As79.h>
#include <bxdecay0/At214.h>
#include <bxdecay0/At214low.h>
#include <bxdecay0/Ba136low.h>
#include <bxdecay0/Ba138low.h>
#include <bxdecay0/Bi207.h>
#include <bxdecay0/Bi208.h>
#include <bxdecay0/Bi210.h>
#include <bxdecay0/Bi212.h>
#include <bxdecay0/Bi214.h>
#include <bxdecay0/C14.h>
#include <bxdecay0/Ca48.h>
#include <bxdecay0/Cd112low.h>
#include <bxdecay0/Cd113.h>
#include <bxdecay0/Co60.h>
#include <bxdecay0/Cs136.h>
#include <bxdecay0/Cs137.h>
#include <bxdecay0/Dy162low.h>
#include <bxdecay0/Dy164low.h>
#include <bxdecay0/Er168low.h>
#include <bxdecay0/Eu147.h>
#include <bxdecay0/Eu152.h>
#include <bxdecay0/Eu154.h>
#include <bxdecay0/Fe58low.h>
#include <bxdecay0/Gd146.h>
#include <bxdecay0/Gd154low.h>
#include <bxdecay0/Gd156low.h>
#include <bxdecay0/Gd158low.h>
#include <bxdecay0/Ge70low.h>
#include <bxdecay0/Ge74low.h>
#include <bxdecay0/Hf176low.h>
#include <bxdecay0/Hf180low.h>
#include <bxdecay0/Hf182.h>
#include <bxdecay0/Hg198low.h>
#include <bxdecay0/I126.h>
#include <bxdecay0/I133.h>
#include <bxdecay0/I134.h>
#include <bxdecay0/I135.h>
#include <bxdecay0/K40.h>
#include <bxdecay0/K42.h>
#include <bxdecay0/Kr81.h>
#include <bxdecay0/Kr82low.h>
#include <bxdecay0/Kr84low.h>
#include <bxdecay0/Kr85.h>
#include <bxdecay0/Mn54.h>
#include <bxdecay0/Mo94low.h>
#include <bxdecay0/Mo96low.h>
#include <bxdecay0/Na22.h>
#include <bxdecay0/Nb96.h>
#include <bxdecay0/Nd142low.h>
#include <bxdecay0/Nd144low.h>
#include <bxdecay0/Ni64low.h>
#include <bxdecay0/Os186low.h>
#include <bxdecay0/Os190low.h>
#include <bxdecay0/P32.h>
#include <bxdecay0/Pa231.h>
#include <bxdecay0/Pa234m.h>
#include <bxdecay0/Pb210.h>
#include <bxdecay0/Pb211.h>
#include <bxdecay0/Pb212.h>
#include <bxdecay0/Pb214.h>
#include <bxdecay0/PbAtShell.h>
#include <bxdecay0/Pd104low.h>
#include <bxdecay0/Pd106low.h>
#include <bxdecay0/Pd108low.h>
#include <bxdecay0/Po210.h>
#include <bxdecay0/Po212.h>
#include <bxdecay0/Po214.h>
#include <bxdecay0/Po214low.h>
#include <bxdecay0/Po218.h>
#include <bxdecay0/Ra222.h>
#include <bxdecay0/Ra222low.h>
#include <bxdecay0/Ra226.h>
#include <bxdecay0/Ra228.h>
#include <bxdecay0/Rb87.h>
#include <bxdecay0/Rh106.h>
#include <bxdecay0/Rn218.h>
#include <bxdecay0/Rn218low.h>
#include <bxdecay0/Rn222.h>
#include <bxdecay0/Ru100low.h>
#include <bxdecay0/Sb125.h>
#include <bxdecay0/Sb126.h>
#include <bxdecay0/Sb133.h>
#include <bxdecay0/Sc48.h>
#include <bxdecay0/Se76low.h>
#include <bxdecay0/Sm148low.h>
#include <bxdecay0/Sm150low.h>
#include <bxdecay0/Sn114low.h>
#include <bxdecay0/Sn116low.h>
#include <bxdecay0/Sn120low.h>
#include <bxdecay0/Sr90.h>
#include <bxdecay0/Ta180mB.h>
#include <bxdecay0/Ta180mEC.h>
#include <bxdecay0/Ta182.h>
#include <bxdecay0/Te122low.h>
#include <bxdecay0/Te124low.h>
#include <bxdecay0/Te133.h>
#include <bxdecay0/Te133m.h>
#include <bxdecay0/Te134.h>
#include <bxdecay0/Th230.h>
#include <bxdecay0/Th234.h>
#include <bxdecay0/Ti48low.h>
#include <bxdecay0/Tl207.h>
#include <bxdecay0/Tl208.h>
#include <bxdecay0/U234.h>
#include <bxdecay0/U238.h>
#include <bxdecay0/Xe128low.h>
#include <bxdecay0/Xe129m.h>
#include <bxdecay0/Xe130low.h>
#include <bxdecay0/Xe131m.h>
#include <bxdecay0/Xe133.h>
#include <bxdecay0/Xe135.h>
#include <bxdecay0/Y88.h>
#include <bxdecay0/Y90.h>
#include <bxdecay0/Yb170low.h>
#include <bxdecay0/Zn65.h>
#include <bxdecay0/Zr92low.h>
#include <bxdecay0/Zr96.h>
#include <bxdecay0/alpha.h>
#include <bxdecay0/bb.h>
#include <bxdecay0/beta.h>
#include <bxdecay0/beta1.h>
#include <bxdecay0/beta2.h>
#include <bxdecay0/beta_1fu.h>
#include <bxdecay0/electron.h>
#include <bxdecay0/event.h>
#include <bxdecay0/gamma.h>
#include <bxdecay0/i_random.h>
#include <bxdecay0/nucltransK.h>
#include <bxdecay0/nucltransKL.h>
#include <bxdecay0/nucltransKLM.h>
#include <bxdecay0/nucltransKLM_Pb.h>
#include <bxdecay0/pair.h>
#include <bxdecay0/pairext1.h>
#include <bxdecay0/particle.h>
#include <bxdecay0/positron.h>
#include <bxdecay0/utils.h>

namespace bxdecay0 {

  void genbbsub(i_random & prng_,
                event & event_,
                const int i2bbs_,
                const std::string & chnuclide_,
                const int ilevel_,
                const int modebb_,
                const int istart_,
                int & ier_,
                bbpars & bb_params_)
  {
    static bool trace = is_trace("genbbsub");
    if (trace) {
      std::cerr << "[debug] bxdecay0::genbbsub: Entering..." << std::endl;
    }
    double tdnuc;
    double tdnuc1;
    int npfull0;

    static const double emass = decay0_emass();
    if (modebb_ != bb_params_.modebb) {
      bb_params_.modebb = modebb_;
    }

    // Error code :
    ier_ = 0;

    if (istart_ != GENBBSUB_ISTART_GENERATE) {
      if (trace) {
        std::cerr << "[debug] bxdecay0::genbbsub: Initialization stage of the generator..." << std::endl;
      }
      // Double/quadruple beta decay mode
      if (i2bbs_ == GENBBSUB_I2BBS_DBD) {
        if (trace) {
          std::cerr << "[debug] bxdecay0::genbbsub: Setting initial DBD parameters..." << std::endl;
        }
        if (name_starts_with(chnuclide_, "Ca40")) {
          bb_params_.Qbb  = 0.194;
          bb_params_.Zdbb = -18.;
          bb_params_.Adbb = 40.;
          bb_params_.EK   = 0.003;
          if (ilevel_ < 0 || ilevel_ > 0) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          bb_params_.levelE   = 0;
          bb_params_.itrans02 = 0;
        } else if (name_starts_with(chnuclide_, "Ca46")) {
          bb_params_.Qbb  = 0.988; // was 0.989
          bb_params_.Zdbb = 22.;
          bb_params_.Adbb = 46.;
          bb_params_.EK   = 0.;
          if (ilevel_ < 0 || ilevel_ > 1) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          if (ilevel_ == 0) {
            bb_params_.levelE = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.levelE = 889;
          }
          if (ilevel_ == 0) {
            bb_params_.itrans02 = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.itrans02 = 2;
          }
        } else if (name_starts_with(chnuclide_, "Ca48")) {
          bb_params_.Qbb  = 4.268; // was 4.267
          bb_params_.Zdbb = 22.;
          bb_params_.Adbb = 48.;
          bb_params_.EK   = 0.;
          if (ilevel_ < 0 || ilevel_ > 2) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          if (ilevel_ == 0) {
            bb_params_.levelE = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.levelE = 984;
          }
          if (ilevel_ == 2) {
            bb_params_.levelE = 2421;
          }
          if (ilevel_ == 0) {
            bb_params_.itrans02 = 0;
          }
          if (ilevel_ == 1 || ilevel_ == 2) {
            bb_params_.itrans02 = 2;
          }
        } else if (name_starts_with(chnuclide_, "Ni58")) {
          bb_params_.Qbb  = 1.926;
          bb_params_.Zdbb = -26.;
          bb_params_.Adbb = 58.;
          bb_params_.EK   = 0.007;
          if (ilevel_ < 0 || ilevel_ > 2) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          if (ilevel_ == 0) {
            bb_params_.levelE = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.levelE = 811;
          }
          if (ilevel_ == 2) {
            bb_params_.levelE = 1675;
          }
          if (ilevel_ == 0) {
            bb_params_.itrans02 = 0;
          }
          if (ilevel_ == 1 || ilevel_ == 2) {
            bb_params_.itrans02 = 2;
          }
        } else if (name_starts_with(chnuclide_, "Zn64")) {
          bb_params_.Qbb  = 1.095;
          bb_params_.Zdbb = -28.;
          bb_params_.Adbb = 64.;
          bb_params_.EK   = 0.008;
          if (ilevel_ != 0) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          bb_params_.levelE   = 0;
          bb_params_.itrans02 = 0;
        } else if (name_starts_with(chnuclide_, "Zn70")) {
          bb_params_.Qbb  = 0.997;
          bb_params_.Zdbb = 32.;
          bb_params_.Adbb = 70.;
          bb_params_.EK   = 0.;
          if (ilevel_ != 0) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          bb_params_.levelE   = 0;
          bb_params_.itrans02 = 0;
        } else if (name_starts_with(chnuclide_, "Ge76")) {
          bb_params_.Qbb  = 2.039;
          bb_params_.Zdbb = 34.;
          bb_params_.Adbb = 76.;
          bb_params_.EK   = 0.;
          if (ilevel_ < 0 || ilevel_ > 3) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          if (ilevel_ == 0) {
            bb_params_.levelE = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.levelE = 559;
          }
          if (ilevel_ == 2) {
            bb_params_.levelE = 1122;
          }
          if (ilevel_ == 3) {
            bb_params_.levelE = 1216;
          }
          if (ilevel_ == 0 || ilevel_ == 2) {
            bb_params_.itrans02 = 0;
          }
          if (ilevel_ == 1 || ilevel_ == 3) {
            bb_params_.itrans02 = 2;
          }
        } else if (name_starts_with(chnuclide_, "Se74")) {
          bb_params_.Qbb  = 1.209;
          bb_params_.Zdbb = -32.;
          bb_params_.Adbb = 74.;
          bb_params_.EK   = 0.011;
          if (ilevel_ < 0 || ilevel_ > 2) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          if (ilevel_ == 0) {
            bb_params_.levelE = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.levelE = 596;
          }
          if (ilevel_ == 2) {
            bb_params_.levelE = 1204;
          }
          if (ilevel_ == 0) {
            bb_params_.itrans02 = 0;
          }
          if (ilevel_ == 1 || ilevel_ == 2) {
            bb_params_.itrans02 = 2;
          }
        } else if (name_starts_with(chnuclide_, "Se82")) {
          bb_params_.Qbb  = 2.998; // was 2.996
          bb_params_.Zdbb = 36.;
          bb_params_.Adbb = 82.;
          bb_params_.EK   = 0.;
          if (ilevel_ < 0 || ilevel_ > 9) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          if (ilevel_ == 0) {
            bb_params_.levelE = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.levelE = 777;
          }
          if (ilevel_ == 2) {
            bb_params_.levelE = 1475;
          }
          if (ilevel_ == 3) {
            bb_params_.levelE = 1488;
          }
          if (ilevel_ == 4) {
            bb_params_.levelE = 1957;
          }
          if (ilevel_ == 5) {
            bb_params_.levelE = 2172;
          }
          if (ilevel_ == 6) {
            bb_params_.levelE = 2450;
          }
          if (ilevel_ == 7) {
            bb_params_.levelE = 2480;
          }
          if (ilevel_ == 8) {
            bb_params_.levelE = 2656;
          }
          if (ilevel_ == 9) {
            bb_params_.levelE = 2945;
          }
          if (ilevel_ == 0) {
            bb_params_.itrans02 = 0;
          }
          bb_params_.itrans02 = 0;
          if (ilevel_ == 0 || ilevel_ == 3 || ilevel_ == 5 || ilevel_ == 6) {
            bb_params_.itrans02 = 0;
          }
          if (ilevel_ == 1 || ilevel_ == 2 || ilevel_ == 4 || ilevel_ == 7 || ilevel_ == 8 || ilevel_ == 9) {
            bb_params_.itrans02 = 2;
          }
        } else if (name_starts_with(chnuclide_, "Sr84")) {
          bb_params_.Qbb  = 1.790;
          bb_params_.Zdbb = -36.;
          bb_params_.Adbb = 84.;
          bb_params_.EK   = 0.014;
          if (ilevel_ < 0 || ilevel_ > 1) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          if (ilevel_ == 0) {
            bb_params_.levelE = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.levelE = 882;
          }
          if (ilevel_ == 0) {
            bb_params_.itrans02 = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.itrans02 = 2;
          }
        } else if (name_starts_with(chnuclide_, "Zr94")) {
          bb_params_.Qbb  = 1.145; // was 1.142
          bb_params_.Zdbb = 42.;
          bb_params_.Adbb = 94.;
          bb_params_.EK   = 0.;
          if (ilevel_ < 0 || ilevel_ > 1) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          if (ilevel_ == 0) {
            bb_params_.levelE = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.levelE = 871;
          }
          if (ilevel_ == 0) {
            bb_params_.itrans02 = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.itrans02 = 2;
          }
        } else if (name_starts_with(chnuclide_, "Zr96")) {
          bb_params_.Qbb  = 3.356; // was 3.349
          bb_params_.Zdbb = 42.; // Molybdenum
          bb_params_.Adbb = 96.;
          bb_params_.EK   = 0.;
          if (modebb_ == LEGACY_MODEBB_20) {
            // Quadruple beta decay:
            if (ilevel_ != 0) {
              std::cerr << "[error] "
                        << "bxdecay0::genbbsub: "
                        << "Only ground state daughter's level is supported for quadruple beta decay of '" << chnuclide_ << "'! \n";
              ier_ = 1;
              if (trace) {
                std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
              }
              return;
            }
            bb_params_.Qbb  = 0.635;
            bb_params_.Zdbb = 44.; // Rhutenium
          } else {
            if (ilevel_ < 0 || ilevel_ > 9) {
              std::cerr << "[error] "
                        << "bxdecay0::genbbsub: "
                        << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
              ier_ = 1;
              if (trace) {
                std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
              }
              return;
            }
            if (ilevel_ == 0) {
              bb_params_.levelE = 0;
            }
            if (ilevel_ == 1) {
              bb_params_.levelE = 778;
            }
            if (ilevel_ == 2) {
              bb_params_.levelE = 1148;
            }
            if (ilevel_ == 3) {
              bb_params_.levelE = 1498;
            }
            if (ilevel_ == 4) {
              bb_params_.levelE = 1626;
            }
            if (ilevel_ == 5) {
              bb_params_.levelE = 2096;
            }
            if (ilevel_ == 6) {
              bb_params_.levelE = 2426;
            }
            if (ilevel_ == 7) {
              bb_params_.levelE = 2623;
            }
            if (ilevel_ == 8) {
              bb_params_.levelE = 2700;
            }
            if (ilevel_ == 9) {
              bb_params_.levelE = 2713;
            }
          }
          if (ilevel_ == 0 || ilevel_ == 2 || ilevel_ == 7) {
            bb_params_.itrans02 = 0;
          }
          if (ilevel_ == 1 || ilevel_ == 3 || ilevel_ == 4 || ilevel_ == 5 || ilevel_ == 6 || ilevel_ == 8 ||
              // we suppose here that 2713 keV level is 2+
              ilevel_ == 9) {
            bb_params_.itrans02 = 2;
          }
        } else if (name_starts_with(chnuclide_, "Mo92")) {
          bb_params_.Qbb  = 1.650; // was 1.652;
          bb_params_.Zdbb = -40.;
          bb_params_.Adbb = 92.;
          bb_params_.EK   = 0.018;
          if (ilevel_ < 0 || ilevel_ > 2) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          if (ilevel_ == 0) {
            bb_params_.levelE = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.levelE = 934;
          }
          if (ilevel_ == 2) {
            bb_params_.levelE = 1383;
          }
          if (ilevel_ == 0 || ilevel_ == 2) {
            bb_params_.itrans02 = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.itrans02 = 2;
          }
        } else if (name_starts_with(chnuclide_, "Mo100")) {
          bb_params_.Qbb  = 3.034;
          bb_params_.Zdbb = 44.;
          bb_params_.Adbb = 100.;
          bb_params_.EK   = 0.;
          if (ilevel_ < 0 || ilevel_ > 4) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          if (ilevel_ == 0) {
            bb_params_.levelE = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.levelE = 540;
          }
          if (ilevel_ == 2) {
            bb_params_.levelE = 1130;
          }
          if (ilevel_ == 3) {
            bb_params_.levelE = 1362;
          }
          if (ilevel_ == 4) {
            bb_params_.levelE = 1741;
          }
          if (ilevel_ == 0 || ilevel_ == 2 || ilevel_ == 4) {
            bb_params_.itrans02 = 0;
          }
          if (ilevel_ == 1 || ilevel_ == 3) {
            bb_params_.itrans02 = 2;
          }
        } else if (name_starts_with(chnuclide_, "Ru96")) {
          bb_params_.Qbb  = 2.715;
          bb_params_.Zdbb = -42.;
          bb_params_.Adbb = 96.;
          bb_params_.EK   = 0.020;
          if (ilevel_ < 0 || ilevel_ > 9) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          if (ilevel_ == 0) {
            bb_params_.levelE = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.levelE = 778;
          }
          if (ilevel_ == 2) {
            bb_params_.levelE = 1148;
          }
          if (ilevel_ == 3) {
            bb_params_.levelE = 1498;
          }
          if (ilevel_ == 4) {
            bb_params_.levelE = 1626;
          }
          if (ilevel_ == 5) {
            bb_params_.levelE = 2096;
          }
          if (ilevel_ == 6) {
            bb_params_.levelE = 2426;
          }
          if (ilevel_ == 7) {
            bb_params_.levelE = 2623;
          }
          if (ilevel_ == 8) {
            bb_params_.levelE = 2700;
          }
          if (ilevel_ == 9) {
            bb_params_.levelE = 2713;
          }
          if (ilevel_ == 0 || ilevel_ == 2 || ilevel_ == 7) {
            bb_params_.itrans02 = 0;
          }
          if (ilevel_ == 1 || ilevel_ == 3 || ilevel_ == 4 || ilevel_ == 5 || ilevel_ == 6 || ilevel_ == 8 ||
              // we suppose here that 2713 keV level is 2+
              ilevel_ == 9) {
            bb_params_.itrans02 = 2;
          }
          if (ilevel_ == 8) {
            bb_params_.EK = 0.003;
          }
          if (ilevel_ == 9) {
            bb_params_.EK = 0.002;
          }
        } else if (name_starts_with(chnuclide_, "Ru104")) {
          bb_params_.Qbb  = 1.299; // was 1.301
          bb_params_.Zdbb = 46.;
          bb_params_.Adbb = 104.;
          bb_params_.EK   = 0.;
          if (ilevel_ < 0 || ilevel_ > 1) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          if (ilevel_ == 0) {
            bb_params_.levelE = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.levelE = 556;
          }
          if (ilevel_ == 0) {
            bb_params_.itrans02 = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.itrans02 = 2;
          }
        } else if (name_starts_with(chnuclide_, "Cd106")) {
          bb_params_.Qbb  = 2.775;
          bb_params_.Zdbb = -46.;
          bb_params_.Adbb = 106.;
          bb_params_.EK   = 0.024;
          if (ilevel_ < 0 || ilevel_ > 5) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          if (ilevel_ == 0) {
            bb_params_.levelE = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.levelE = 512;
          }
          if (ilevel_ == 2) {
            bb_params_.levelE = 1128;
          }
          if (ilevel_ == 3) {
            bb_params_.levelE = 1134;
          }
          if (ilevel_ == 4) {
            bb_params_.levelE = 1562;
          }
          if (ilevel_ == 5) {
            bb_params_.levelE = 1706;
          }
          if (ilevel_ == 0 || ilevel_ == 3 || ilevel_ == 5) {
            bb_params_.itrans02 = 0;
          }
          if (ilevel_ == 1 || ilevel_ == 2 || ilevel_ == 4) {
            bb_params_.itrans02 = 2;
          }
        } else if (name_starts_with(chnuclide_, "Cd108")) {
          bb_params_.Qbb  = 0.272;
          bb_params_.Zdbb = -46.;
          bb_params_.Adbb = 108.;
          bb_params_.EK   = 0.024;
          if (ilevel_ != 0) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          bb_params_.levelE   = 0;
          bb_params_.itrans02 = 0;
        } else if (name_starts_with(chnuclide_, "Cd114")) {
          bb_params_.Qbb  = 0.545; // was 0.543;
          bb_params_.Zdbb = 50.;
          bb_params_.Adbb = 114.;
          bb_params_.EK   = 0.;
          if (ilevel_ != 0) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          bb_params_.levelE   = 0;
          bb_params_.itrans02 = 0;
        } else if (name_starts_with(chnuclide_, "Cd116")) {
          bb_params_.Qbb  = 2.813;
          bb_params_.Zdbb = 50.;
          bb_params_.Adbb = 116.;
          bb_params_.EK   = 0.;
          if (ilevel_ < 0 || ilevel_ > 5) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          if (ilevel_ == 0) {
            bb_params_.levelE = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.levelE = 1294;
          }
          if (ilevel_ == 2) {
            bb_params_.levelE = 1757;
          }
          if (ilevel_ == 3) {
            bb_params_.levelE = 2027;
          }
          if (ilevel_ == 4) {
            bb_params_.levelE = 2112;
          }
          if (ilevel_ == 5) {
            bb_params_.levelE = 2225;
          }
          if (ilevel_ == 0 || ilevel_ == 2 || ilevel_ == 3) {
            bb_params_.itrans02 = 0;
          }
          if (ilevel_ == 1 || ilevel_ == 4 || ilevel_ == 5) {
            bb_params_.itrans02 = 2;
          }
        } else if (name_starts_with(chnuclide_, "Sn112")) {
          bb_params_.Qbb  = 1.920;
          bb_params_.Zdbb = -48.;
          bb_params_.Adbb = 112.;
          bb_params_.EK   = 0.027;
          if (ilevel_ < 0 || ilevel_ > 6) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          if (ilevel_ == 0) {
            bb_params_.levelE = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.levelE = 618;
          }
          if (ilevel_ == 2) {
            bb_params_.levelE = 1224;
          }
          if (ilevel_ == 3) {
            bb_params_.levelE = 1312;
          }
          if (ilevel_ == 4) {
            bb_params_.levelE = 1433;
          }
          if (ilevel_ == 5) {
            bb_params_.levelE = 1469;
          }
          if (ilevel_ == 6) {
            bb_params_.levelE = 1871;
          }
          if (ilevel_ == 0 || ilevel_ == 2 || ilevel_ == 4 || ilevel_ == 6) {
            bb_params_.itrans02 = 0;
          }
          if (ilevel_ == 1 || ilevel_ == 3 || ilevel_ == 5) {
            bb_params_.itrans02 = 2;
          }
        } else if (name_starts_with(chnuclide_, "Sn122")) {
          bb_params_.Qbb  = 0.373;
          bb_params_.Zdbb = 52.;
          bb_params_.Adbb = 122.;
          bb_params_.EK   = 0.;
          if (ilevel_ != 0) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          bb_params_.levelE   = 0;
          bb_params_.itrans02 = 0;
        } else if (name_starts_with(chnuclide_, "Sn124")) {
          bb_params_.Qbb  = 2.291;
          bb_params_.Zdbb = 52.;
          bb_params_.Adbb = 124.;
          bb_params_.EK   = 0.;
          if (ilevel_ < 0 || ilevel_ > 8) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          if (ilevel_ == 0) {
            bb_params_.levelE = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.levelE = 603;
          }
          if (ilevel_ == 2) {
            bb_params_.levelE = 1326;
          }
          if (ilevel_ == 3) {
            bb_params_.levelE = 1657;
          }
          if (ilevel_ == 4) {
            bb_params_.levelE = 1883;
          }
          if (ilevel_ == 5) {
            bb_params_.levelE = 2039;
          }
          if (ilevel_ == 6) {
            bb_params_.levelE = 2092;
          }
          if (ilevel_ == 7) {
            bb_params_.levelE = 2153;
          }
          if (ilevel_ == 8) {
            bb_params_.levelE = 2182;
          }
          if (ilevel_ == 0 || ilevel_ == 3 || ilevel_ == 4 || ilevel_ == 7) {
            bb_params_.itrans02 = 0;
          }
          if (ilevel_ == 1 || ilevel_ == 2 || ilevel_ == 5 || ilevel_ == 6 || ilevel_ == 8) {
            bb_params_.itrans02 = 2;
          }
        } else if (name_starts_with(chnuclide_, "Te120")) {
          bb_params_.Qbb  = 1.730;
          bb_params_.Zdbb = -50.;
          bb_params_.Adbb = 120.;
          bb_params_.EK   = 0.029;
          if (ilevel_ < 0 || ilevel_ > 1) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          if (ilevel_ == 0) {
            bb_params_.levelE = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.levelE = 1171;
          }
          if (ilevel_ == 0) {
            bb_params_.itrans02 = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.itrans02 = 2;
          }
        } else if (name_starts_with(chnuclide_, "Te128")) {
          bb_params_.Qbb  = 0.867;
          bb_params_.Zdbb = 54.;
          bb_params_.Adbb = 128.;
          bb_params_.EK   = 0.;
          if (ilevel_ < 0 || ilevel_ > 1) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          if (ilevel_ == 0) {
            bb_params_.levelE = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.levelE = 443;
          }
          if (ilevel_ == 0) {
            bb_params_.itrans02 = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.itrans02 = 2;
          }
        } else if (name_starts_with(chnuclide_, "Te130")) {
          bb_params_.Qbb  = 2.528;
          bb_params_.Zdbb = 54.;
          bb_params_.Adbb = 130.;
          bb_params_.EK   = 0.;
          if (ilevel_ < 0 || ilevel_ > 3) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          if (ilevel_ == 0) {
            bb_params_.levelE = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.levelE = 536;
          }
          if (ilevel_ == 2) {
            bb_params_.levelE = 1122;
          }
          if (ilevel_ == 3) {
            bb_params_.levelE = 1794;
          }
          if (ilevel_ == 0 || ilevel_ == 3) {
            bb_params_.itrans02 = 0;
          }
          if (ilevel_ == 1 || ilevel_ == 2) {
            bb_params_.itrans02 = 2;
          }
        } else if (name_starts_with(chnuclide_, "Xe136")) {
          bb_params_.Qbb  = 2.458;
          bb_params_.Zdbb = 56.; // Baryum
          bb_params_.Adbb = 136.;
          bb_params_.EK   = 0.;
          if (modebb_ == LEGACY_MODEBB_20) {
            // Quadruple beta decay:
            if (ilevel_ != 0) {
              std::cerr << "[error] "
                        << "bxdecay0::genbbsub: "
                        << "Only ground state daughter's level is supported for quadruple beta decay of '" << chnuclide_ << "'! \n";
              ier_ = 1;
              if (trace) {
                std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
              }
              return;
            }
            bb_params_.Qbb  = 0.079;
            bb_params_.Zdbb = 58.; // Cerium
          } else {
            if (ilevel_ < 0 || ilevel_ > 9) {
              std::cerr << "[error] "
                        << "bxdecay0::genbbsub: "
                        << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
              ier_ = 1;
              if (trace) {
                std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
              }
              return;
            }
            if (ilevel_ == 0) {
              bb_params_.levelE = 0;
            }
            if (ilevel_ == 1) {
              bb_params_.levelE = 819;
            }
            if (ilevel_ == 2) {
              bb_params_.levelE = 1551;
            }
            if (ilevel_ == 3) {
              bb_params_.levelE = 1579;
            }
            if (ilevel_ == 4) {
              bb_params_.levelE = 2080;
            }
            if (ilevel_ == 5) {
              bb_params_.levelE = 2129;
            }
            if (ilevel_ == 6) {
              bb_params_.levelE = 2141;
            }
            if (ilevel_ == 7) {
              bb_params_.levelE = 2223;
            }
            if (ilevel_ == 8) {
              bb_params_.levelE = 2315;
            }
            if (ilevel_ == 9) {
              bb_params_.levelE = 2400;
            }
          }
          if (ilevel_ == 0 || ilevel_ == 3 || ilevel_ == 6 || ilevel_ == 8) {
            bb_params_.itrans02 = 0;
          }
          if (ilevel_ == 1 || ilevel_ == 2 || ilevel_ == 4 || ilevel_ == 5 || ilevel_ == 7 || ilevel_ == 9) {
            bb_params_.itrans02 = 2;
          }
        } else if (name_starts_with(chnuclide_, "Ce136")) {
          bb_params_.Qbb  = 2.379;
          bb_params_.Zdbb = -56.;
          bb_params_.Adbb = 136.;
          bb_params_.EK   = 0.037;
          if (ilevel_ < 0 || ilevel_ > 9) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          if (ilevel_ == 0) {
            bb_params_.levelE = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.levelE = 819;
          }
          if (ilevel_ == 2) {
            bb_params_.levelE = 1551;
          }
          if (ilevel_ == 3) {
            bb_params_.levelE = 1579;
          }
          if (ilevel_ == 4) {
            bb_params_.levelE = 2080;
          }
          if (ilevel_ == 5) {
            bb_params_.levelE = 2129;
          }
          if (ilevel_ == 6) {
            bb_params_.levelE = 2141;
          }
          if (ilevel_ == 7) {
            bb_params_.levelE = 2223;
          }
          if (ilevel_ == 8) {
            bb_params_.levelE = 2315;
          }
          if (ilevel_ == 9) {
            bb_params_.levelE = 2400;
          }
          if (ilevel_ == 0 || ilevel_ == 3 || ilevel_ == 6 || ilevel_ == 8) {
            bb_params_.itrans02 = 0;
          }
          if (ilevel_ == 1 || ilevel_ == 2 || ilevel_ == 4 || ilevel_ == 5 || ilevel_ == 7 || ilevel_ == 9) {
            bb_params_.itrans02 = 2;
          }
          // only 2L capture is allowed energetically for 2400 keV level
          if (ilevel_ == 9) {
            bb_params_.EK = 0.006;
          }
        } else if (name_starts_with(chnuclide_, "Ce138")) {
          bb_params_.Qbb  = 0.691; // was 0.693
          bb_params_.Zdbb = -56.;
          bb_params_.Adbb = 138.;
          bb_params_.EK   = 0.037;
          if (ilevel_ != 0) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          bb_params_.levelE   = 0;
          bb_params_.itrans02 = 0;
        } else if (name_starts_with(chnuclide_, "Ce142")) {
          bb_params_.Qbb  = 1.417;
          bb_params_.Zdbb = 60.;
          bb_params_.Adbb = 142.;
          bb_params_.EK   = 0.;
          if (ilevel_ != 0) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          bb_params_.levelE   = 0;
          bb_params_.itrans02 = 0;
        } else if (name_starts_with(chnuclide_, "Nd148")) {
          bb_params_.Qbb  = 1.928;
          bb_params_.Zdbb = 62.;
          bb_params_.Adbb = 148.;
          bb_params_.EK   = 0.;
          if (ilevel_ < 0 || ilevel_ > 5) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          // Modified in 2018-12-05:
          if (ilevel_ == 0) {
            bb_params_.levelE = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.levelE = 550;
          }
          if (ilevel_ == 2) {
            bb_params_.levelE = 1424;
          }
          if (ilevel_ == 3) {
            bb_params_.levelE = 1454;
          }
          if (ilevel_ == 4) {
            bb_params_.levelE = 1664;
          }
          if (ilevel_ == 5) {
            bb_params_.levelE = 1921;
          }
          if (ilevel_ == 0 || ilevel_ == 2 || ilevel_ == 5) {
            bb_params_.itrans02 = 0;
          }
          if (ilevel_ == 1 || ilevel_ == 3 || ilevel_ == 4) {
            bb_params_.itrans02 = 2;
          }
        } else if (name_starts_with(chnuclide_, "Nd150")) {
          bb_params_.Qbb  = 3.371;
          bb_params_.Zdbb = 62.; // Samarium
          bb_params_.Adbb = 150.;
          bb_params_.EK   = 0.;
          if (modebb_ == LEGACY_MODEBB_20) {
            // Quadruple beta decay:
            if (ilevel_ != 0) {
              std::cerr << "[error] "
                        << "bxdecay0::genbbsub: "
                        << "Only ground state daughter's level is supported for quadruple beta decay of '" << chnuclide_ << "'! \n";
              ier_ = 1;
              if (trace) {
                std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
              }
              return;
            }
            bb_params_.Qbb  = 2.085;
            bb_params_.Zdbb = 64.; // Gadolinium
          } else {
            if (ilevel_ < 0 || ilevel_ > 5) {
              std::cerr << "[error] "
                        << "bxdecay0::genbbsub: "
                        << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
              ier_ = 1;
              if (trace) {
                std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
              }
              return;
            }
            if (ilevel_ == 0) {
              bb_params_.levelE = 0;
            }
            if (ilevel_ == 1) {
              bb_params_.levelE = 334;
            }
            if (ilevel_ == 2) {
              bb_params_.levelE = 740;
            }
            if (ilevel_ == 3) {
              bb_params_.levelE = 1046;
            }
            if (ilevel_ == 4) {
              bb_params_.levelE = 1194;
            }
            if (ilevel_ == 5) {
              bb_params_.levelE = 1256;
            }
          }
          if (ilevel_ == 0 || ilevel_ == 2 || ilevel_ == 5) {
            bb_params_.itrans02 = 0;
          }
          if (ilevel_ == 1 || ilevel_ == 3 || ilevel_ == 4) {
            bb_params_.itrans02 = 2;
          }
        } else if (name_starts_with(chnuclide_, "Sm144")) {
          // New in 2018-12-05:
          bb_params_.Qbb  = 1.782;
          bb_params_.Zdbb = -60.;
          bb_params_.Adbb = 144.;
          bb_params_.EK   = 0.044;
          if (ilevel_ < 0 || ilevel_ > 2) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          if (ilevel_ == 0) {
            bb_params_.levelE = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.levelE = 697;
          }
          if (ilevel_ == 2) {
            bb_params_.levelE = 1561;
          }
          if (ilevel_ == 0) {
            bb_params_.itrans02 = 0;
          }
          if (ilevel_ == 1 || ilevel_ == 2) {
            bb_params_.itrans02 = 2;
          }
        } else if (name_starts_with(chnuclide_, "Sm154")) {
          // New in 2018-12-05:
          bb_params_.Qbb  = 1.251;
          bb_params_.Zdbb = 64.;
          bb_params_.Adbb = 154.;
          bb_params_.EK   = 0.050;
          if (ilevel_ < 0 || ilevel_ > 5) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          if (ilevel_ == 0) {
            bb_params_.levelE = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.levelE = 123;
          }
          if (ilevel_ == 2) {
            bb_params_.levelE = 681;
          }
          if (ilevel_ == 3) {
            bb_params_.levelE = 815;
          }
          if (ilevel_ == 4) {
            bb_params_.levelE = 996;
          }
          if (ilevel_ == 5) {
            bb_params_.levelE = 112;
          }
          if (ilevel_ == 0 || ilevel_ == 2 || ilevel_ == 5) {
            bb_params_.itrans02 = 0;
          }
          if (ilevel_ == 1 || ilevel_ == 3 || ilevel_ == 4) {
            bb_params_.itrans02 = 2;
          }
        } else if (name_starts_with(chnuclide_, "Dy156")) {
          bb_params_.Qbb  = 2.006;
          bb_params_.Zdbb = -64.;
          bb_params_.Adbb = 156.;
          bb_params_.EK   = 0.050;
          if (ilevel_ < 0 || ilevel_ > 15) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          if (ilevel_ == 0) {
            bb_params_.levelE = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.levelE = 89;
          }
          if (ilevel_ == 2) {
            bb_params_.levelE = 1050;
          }
          if (ilevel_ == 3) {
            bb_params_.levelE = 1129;
          }
          if (ilevel_ == 4) {
            bb_params_.levelE = 1154;
          }
          if (ilevel_ == 5) {
            bb_params_.levelE = 1168;
          }
          if (ilevel_ == 6) {
            bb_params_.levelE = 1258;
          }
          if (ilevel_ == 7) {
            bb_params_.levelE = 1715;
          }
          if (ilevel_ == 8) {
            bb_params_.levelE = 1771;
          }
          if (ilevel_ == 9) {
            bb_params_.levelE = 1828;
          }
          if (ilevel_ == 10) {
            bb_params_.levelE = 1851;
          }
          if (ilevel_ == 11) {
            bb_params_.levelE = 1915;
          }
          if (ilevel_ == 12) {
            bb_params_.levelE = 1946;
          }
          if (ilevel_ == 13) {
            bb_params_.levelE = 1952;
          }
          if (ilevel_ == 14) {
            bb_params_.levelE = 1989;
          }
          if (ilevel_ == 15) {
            bb_params_.levelE = 2004;
          }
          if (ilevel_ == 0 || ilevel_ == 2 || ilevel_ == 5 || ilevel_ == 7 || ilevel_ == 10 || ilevel_ == 14) {
            bb_params_.itrans02 = 0;
          }
          if (ilevel_ == 1 || ilevel_ == 3 || ilevel_ == 4 || ilevel_ == 6 || ilevel_ == 8 || ilevel_ == 9
              || ilevel_ == 11 || ilevel_ == 15) {
            bb_params_.itrans02 = 2;
          }
          if (ilevel_ >= 11 && ilevel_ <= 13) {
            bb_params_.EK = 0.029;
          }
          if (ilevel_ == 14) {
            bb_params_.EK = 0.008;
          }
          if (ilevel_ == 15) {
            bb_params_.EK = 0.004;
          }
        } else if (name_starts_with(chnuclide_, "Dy158")) {
          bb_params_.Qbb  = 0.282; // was 0.283
          bb_params_.Zdbb = -64.;
          bb_params_.Adbb = 156.;
          bb_params_.EK   = 0.050;
          if (ilevel_ < 0 || ilevel_ > 2) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          if (ilevel_ == 0) {
            bb_params_.levelE = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.levelE = 80;
          }
          if (ilevel_ == 2) {
            bb_params_.levelE = 261;
          }
          if (ilevel_ == 0) {
            bb_params_.itrans02 = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.itrans02 = 2;
          }
          if (ilevel_ == 2) {
            bb_params_.EK = 0.008;
          }
        } else if (name_starts_with(chnuclide_, "Er162")) {
          // New in 2018-12-05:
          bb_params_.Qbb  = 1.847;
          bb_params_.Zdbb = -66.;
          bb_params_.Adbb = 162.;
          bb_params_.EK   = 0.054;
          if (ilevel_ < 0 || ilevel_ > 7) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          // KL capture - approximation (in fact, X rays energies should be 54 and 9 keV, but not 31.5 keV both)
          if (ilevel_ == 7) {
            bb_params_.EK = 0.0315;
          }
          if (ilevel_ == 0) {
            bb_params_.levelE = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.levelE = 81;
          }
          if (ilevel_ == 2) {
            bb_params_.levelE = 888;
          }
          if (ilevel_ == 3) {
            bb_params_.levelE = 1400;
          }
          if (ilevel_ == 4) {
            bb_params_.levelE = 1453;
          }
          if (ilevel_ == 5) {
            bb_params_.levelE = 1666;
          }
          if (ilevel_ == 6) {
            bb_params_.levelE = 1728;
          }
          if (ilevel_ == 7) {
            bb_params_.levelE = 1783;
          }
          if (ilevel_ == 0 || ilevel_ == 3 || ilevel_ == 5) {
            bb_params_.itrans02 = 0;
          }
          if (ilevel_ == 1 || ilevel_ == 2 || ilevel_ == 4 || ilevel_ == 6 || ilevel_ == 7) {
            bb_params_.itrans02 = 2;
          }
        } else if (name_starts_with(chnuclide_, "Er164")) {
          // New in 2018-12-05:
          bb_params_.Qbb  = 0.025;
          bb_params_.Zdbb = -66.;
          bb_params_.Adbb = 164.;
          bb_params_.EK   = 0.009;
          if (ilevel_ != 0) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          bb_params_.levelE   = 0;
          bb_params_.itrans02 = 0;
        } else if (name_starts_with(chnuclide_, "Er170")) {
          // New in 2018-12-05:
          bb_params_.Qbb  = 0.655;
          bb_params_.Zdbb = 70.;
          bb_params_.Adbb = 174.;
          bb_params_.EK   = 0.061;
          if (ilevel_ < 0 || ilevel_ > 1) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          if (ilevel_ == 0) {
            bb_params_.levelE = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.levelE = 84;
          }
          if (ilevel_ == 0) {
            bb_params_.itrans02 = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.itrans02 = 2;
          }
        } else if (name_starts_with(chnuclide_, "Yb168")) {
          // New in 2018-12-05:
          bb_params_.Qbb  = 1.409;
          bb_params_.Zdbb = -68.;
          bb_params_.Adbb = 168.;
          bb_params_.EK   = 0.057;
          if (ilevel_ < 0 || ilevel_ > 4) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          if (ilevel_ == 0) {
            bb_params_.levelE = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.levelE = 80;
          }
          if (ilevel_ == 2) {
            bb_params_.levelE = 821;
          }
          if (ilevel_ == 3) {
            bb_params_.levelE = 1217;
          }
          if (ilevel_ == 4) {
            bb_params_.levelE = 1276;
          }
          if (ilevel_ == 0 || ilevel_ == 3) {
            bb_params_.itrans02 = 0;
          }
          if (ilevel_ == 1 || ilevel_ == 2 || ilevel_ == 4) {
            bb_params_.itrans02 = 2;
          }
        } else if (name_starts_with(chnuclide_, "Yb176")) {
          // New in 2018-12-05:
          bb_params_.Qbb  = 1.085;
          bb_params_.Zdbb = 72.;
          bb_params_.Adbb = 176.;
          bb_params_.EK   = 0.065;
          if (ilevel_ < 0 || ilevel_ > 1) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          if (ilevel_ == 0) {
            bb_params_.levelE = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.levelE = 88;
          }
          if (ilevel_ == 0) {
            bb_params_.itrans02 = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.itrans02 = 2;
          }
        } else if (name_starts_with(chnuclide_, "W180")) {
          bb_params_.Qbb  = 0.143;
          bb_params_.Zdbb = -72.;
          bb_params_.Adbb = 180.;
          bb_params_.EK   = 0.065;
          if (ilevel_ < 0 || ilevel_ > 0) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          bb_params_.levelE   = 0;
          bb_params_.itrans02 = 0;
        } else if (name_starts_with(chnuclide_, "W186")) {
          bb_params_.Qbb  = 0.491; // was 0.492
          bb_params_.Zdbb = 76.;
          bb_params_.Adbb = 186.;
          bb_params_.EK   = 0.;
          if (ilevel_ < 0 || ilevel_ > 1) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          if (ilevel_ == 0) {
            bb_params_.levelE = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.levelE = 137;
          }
          if (ilevel_ == 0) {
            bb_params_.itrans02 = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.itrans02 = 2;
          }
        } else if (name_starts_with(chnuclide_, "Os184")) {
          bb_params_.Qbb  = 1.453; // was 1.451
          bb_params_.Zdbb = -74.;
          bb_params_.Adbb = 184.;
          bb_params_.EK   = 0.070;
          if (ilevel_ < 0 || ilevel_ > 7) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          if (ilevel_ == 0) {
            bb_params_.levelE = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.levelE = 111;
          }
          if (ilevel_ == 2) {
            bb_params_.levelE = 903;
          }
          if (ilevel_ == 3) {
            bb_params_.levelE = 1002;
          }
          if (ilevel_ == 4) {
            bb_params_.levelE = 1121;
          }
          if (ilevel_ == 5) {
            bb_params_.levelE = 1322;
          }
          if (ilevel_ == 6) {
            bb_params_.levelE = 1386;
          }
          if (ilevel_ == 7) {
            bb_params_.levelE = 1431;
          }
          if (ilevel_ == 0 || ilevel_ == 3 || ilevel_ == 5) {
            bb_params_.itrans02 = 0;
          }
          if (ilevel_ == 1 || ilevel_ == 2 || ilevel_ == 4 || ilevel_ == 6 || ilevel_ == 7) {
            bb_params_.itrans02 = 2;
          }
          // for decay to 1386 keV level, electron captures from LL or higher atomic shells are possible
          if (ilevel_ == 6) {
            bb_params_.EK = 0.012;
          }
          // for decay to 1431 keV level, electron captures from LM, MM or higher atomic shells are possible
          if (ilevel_ == 7) {
            bb_params_.EK = 0.;
          }
        } else if (name_starts_with(chnuclide_, "Os192")) {
          bb_params_.Qbb  = 0.406; // was 0.408
          bb_params_.Zdbb = 78.;
          bb_params_.Adbb = 192.;
          bb_params_.EK   = 0.;
          if (ilevel_ < 0 || ilevel_ > 1) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          if (ilevel_ == 0) {
            bb_params_.levelE = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.levelE = 317;
          }
          if (ilevel_ == 0) {
            bb_params_.itrans02 = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.itrans02 = 2;
          }
        } else if (name_starts_with(chnuclide_, "Pt190")) {
          bb_params_.Qbb  = 1.401; // was 1.384
          bb_params_.Zdbb = -76.;
          bb_params_.Adbb = 190.;
          bb_params_.EK   = 0.074;
          if (ilevel_ < 0 || ilevel_ > 5) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          if (ilevel_ == 0) {
            bb_params_.levelE = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.levelE = 187;
          }
          if (ilevel_ == 2) {
            bb_params_.levelE = 558;
          }
          if (ilevel_ == 3) {
            bb_params_.levelE = 912;
          }
          if (ilevel_ == 4) {
            bb_params_.levelE = 1115;
          }
          if (ilevel_ == 5) {
            bb_params_.levelE = 1382;
          }
          if (ilevel_ == 0 || ilevel_ == 3 || ilevel_ == 5) {
            bb_params_.itrans02 = 0;
          }
          if (ilevel_ == 1 || ilevel_ == 2 || ilevel_ == 4) {
            bb_params_.itrans02 = 2;
          }
          // for decay to 1382 keV level, electron captures from N or higher atomic shells are possible
          if (ilevel_ == 5) {
            bb_params_.EK = 0.;
          }
        } else if (name_starts_with(chnuclide_, "Pt198")) {
          bb_params_.Qbb  = 1.050; // was 1.049
          bb_params_.Zdbb = 80.;
          bb_params_.Adbb = 198.;
          bb_params_.EK   = 0.;
          if (ilevel_ < 0 || ilevel_ > 1) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          if (ilevel_ == 0) {
            bb_params_.levelE = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.levelE = 412;
          }
          if (ilevel_ == 0) {
            bb_params_.itrans02 = 0;
          }
          if (ilevel_ == 1) {
            bb_params_.itrans02 = 2;
          }
        } else if (name_starts_with(chnuclide_, "Bi214")) {
          bb_params_.Qbb  = 2.179; // was 2.180
          bb_params_.Zdbb = 85.;
          bb_params_.Adbb = 214.;
          bb_params_.EK   = 0.;
          if (ilevel_ != 0) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          bb_params_.levelE   = 0;
          bb_params_.itrans02 = 0;
        } else if (name_starts_with(chnuclide_, "Pb214")) {
          bb_params_.Qbb  = 4.287; // was 4.289
          bb_params_.Zdbb = 84.;
          bb_params_.Adbb = 214.;
          bb_params_.EK   = 0.;
          if (ilevel_ != 0) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          bb_params_.levelE   = 0;
          bb_params_.itrans02 = 0;
        } else if (name_starts_with(chnuclide_, "Po218")) {
          bb_params_.Qbb  = 3.140; // was 3.141
          bb_params_.Zdbb = 86.;
          bb_params_.Adbb = 218.;
          bb_params_.EK   = 0.;
          if (ilevel_ != 0) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          bb_params_.levelE   = 0;
          bb_params_.itrans02 = 0;
        } else if (name_starts_with(chnuclide_, "Rn222")) {
          bb_params_.Qbb  = 2.052;
          bb_params_.Zdbb = 88.;
          bb_params_.Adbb = 222.;
          bb_params_.EK   = 0.;
          if (ilevel_ != 0) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          bb_params_.levelE   = 0;
          bb_params_.itrans02 = 0;
        } else {
          std::cerr << "[error] "
                    << "bxdecay0::genbbsub: "
                    << "Unknown double beta nuclide '" << chnuclide_ << "' ! \n";
          ier_ = 1;
          if (trace) {
            std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
          }
          return;
        }
        if (trace) {
          std::cerr << "[debug] bxdecay0::genbbsub: Done." << std::endl;
        }
        if (bb_params_.itrans02 == 0) {
          bb_params_.chdspin = "0+";
        }
        if (bb_params_.itrans02 == 2) {
          bb_params_.chdspin = "2+";
        }
        if (bb_params_.itrans02 == 0 && name_starts_with(chnuclide_, "Bi214")) {
          bb_params_.chdspin = "1-";
        }
        if (bb_params_.modebb < LEGACY_MODEBB_MIN || bb_params_.modebb > LEGACY_MODEBB_MAX) {
          std::cerr << "[error] "
                    << "bxdecay0::genbbsub: "
                    << "Unknown double beta mode (" << bb_params_.modebb << ") ! \n";
          ier_ = 1;
          if (trace) {
            std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
          }
          return;
        }
        dbd_mode_type dbd_mode  = dbd_mode_from_legacy_modebb(static_cast<legacy_modebb_type>(bb_params_.modebb));
        std::string modebb_desc = dbd_mode_description(dbd_mode);
        // (1) Checking the consistency of data: energy
        {
          if (trace) {
            std::cerr << "[debug] bxdecay0::genbbsub: (1) Checking the consistency of data: energy..." << std::endl;
          }
          double El = bb_params_.levelE / 1000.;
          double e0;
          e0 = std::numeric_limits<double>::quiet_NaN();
          if (bb_params_.Zdbb >= 0.) {
            e0 = bb_params_.Qbb;
          }
          if (bb_params_.Zdbb < 0.) {
            e0 = bb_params_.Qbb - 4. * emass;
          }
          if (bb_params_.modebb == LEGACY_MODEBB_9 || bb_params_.modebb == LEGACY_MODEBB_10) {
            e0 = bb_params_.Qbb - bb_params_.EK - 2. * emass;
          }
          if (bb_params_.modebb == LEGACY_MODEBB_11 || bb_params_.modebb == LEGACY_MODEBB_12) {
            e0 = bb_params_.Qbb - 2. * bb_params_.EK;
          }
          if (e0 != e0) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Undefined e0 ! Bug!"
                      << "\n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          if (e0 <= El) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Not enough energy for transition to this level : "
                      << "Full energy release and Elevel : e0=" << e0 << " <= El=" << El << "\n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          if (trace) {
            std::cerr << "[debug] bxdecay0::genbbsub: (1) Checking the consistency of data: energy is done."
                      << std::endl;
          }
        }
        // (2) spin of level and mode of decay
        {
          if (trace) {
            std::cerr << "[debug] bxdecay0::genbbsub: (2) Spin of level and mode of decay..." << std::endl;
          }
          int m     = bb_params_.modebb;
          bool m_ok = false;
          // Fix #21 : missing check for mode==20 (quadruple beta decay)
          if (!m_ok && bb_params_.itrans02 == 0
              && (m == 1 || m == 2 || m == 3 || m == 4 || m == 5 || m == 6 || m == 9 || m == 10 || m == 11 || m == 12
                  || m == 13 || m == 14 || m == 15 || m == 17 || m == 18 || m == 19 || m == 20)) {
            m_ok = true;
          }
          if (!m_ok && bb_params_.itrans02 == 2
              && (m == 3 || m == 7 || m == 8 || m == 9 || m == 10 || m == 11 || m == 12 || m == 16)) {
            m_ok = true;
          }
          if (!m_ok) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Decay mode '" << modebb_desc << "' and spin '" << bb_params_.chdspin
                      << "' of daughter nucleus level " << bb_params_.itrans02 << " are inconsistent ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          if (trace) {
            std::cerr << "[debug] bxdecay0::genbbsub: (2) Spin of level and mode of decay is done." << std::endl;
          }
        }
        // (3) nuclide and mode of decay
        {
          if (trace) {
            std::cerr << "[debug] bxdecay0::genbbsub: (3) Nuclide and mode of decay..." << std::endl;
          }
          if (bb_params_.Zdbb >= 0.
              && (bb_params_.modebb == 9 || bb_params_.modebb == 10 || bb_params_.modebb == 11
                  || bb_params_.modebb == 12)) {
            std::cerr << "[error] "
                      << "bxdecay0::genbbsub: "
                      << "Decay mode '" << modebb_desc << "' and nuclide '" << chnuclide_ << "'  "
                      << "are inconsistent ! \n";
            ier_ = 1;
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
            }
            return;
          }
          if (trace) {
            std::cerr << "[debug] bxdecay0::genbbsub: (3) Nuclide and mode of decay is done." << std::endl;
          }
        }
        if (trace) {
          std::cerr << "[debug] bxdecay0::genbbsub: Setting initial DBD parameters is done." << std::endl;
        }
      }
     
      // (4) quadruple beta decay
      if (bb_params_.modebb == 20) {
        
        if (trace) {
          std::cerr << "[debug] bxdecay0::genbbsub: (4) Quadruple beta decay..." << std::endl;
        }
        ier_ = 1;
        if (chnuclide_ == "Zr96" || chnuclide_ == "Xe136" || chnuclide_ == "Nd150") {
          ier_ = 0;
        }
        if (ier_ != 0) {
          std::cerr << "[error] "
                    << "bxdecay0::genbbsub: "
                    << "4 beta decay is foreseen only for Zr96, Xe136 or Nd150 (g.s. to g.s.) !\n";
          if (trace) {
            std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
          }
          return;
        }

        /// check ilevel == 0       
        if (trace) {
          std::cerr << "[debug] bxdecay0::genbbsub: (4) Quadruple beta decay is done." << std::endl;
        }
      }

      if (i2bbs_ == GENBBSUB_I2BBS_BACKGROUND) {
        if (trace) {
          std::cerr << "[debug] bxdecay0::genbbsub: Checking background decays..." << std::endl;
        }
        if (name_starts_with(chnuclide_, "Ac228")) {
        } else if (name_starts_with(chnuclide_, "Am241")) {
        } else if (name_starts_with(chnuclide_, "Ar39")) {
        } else if (name_starts_with(chnuclide_, "Ar42")) {
        } else if (name_starts_with(chnuclide_, "As79")) {
        } else if (name_starts_with(chnuclide_, "Bi207")) {
        } else if (name_starts_with(chnuclide_, "Bi208")) {
        } else if (name_starts_with(chnuclide_, "Bi210")) {
        } else if (name_starts_with(chnuclide_, "Bi212")) {
        } else if (name_starts_with(chnuclide_, "Bi214")) {
        } else if (name_starts_with(chnuclide_, "C14")) {
        } else if (name_starts_with(chnuclide_, "Ca48")) {
        } else if (name_starts_with(chnuclide_, "Cd113")) {
        } else if (name_starts_with(chnuclide_, "Co60")) {
        } else if (name_starts_with(chnuclide_, "Cs136")) {
        } else if (name_starts_with(chnuclide_, "Cs137")) {
        } else if (name_starts_with(chnuclide_, "Eu147")) {
        } else if (name_starts_with(chnuclide_, "Eu152")) {
        } else if (name_starts_with(chnuclide_, "Eu154")) {
        } else if (name_starts_with(chnuclide_, "Gd146")) {
        } else if (name_starts_with(chnuclide_, "Hf182")) {
        } else if (name_starts_with(chnuclide_, "I126")) {
        } else if (name_starts_with(chnuclide_, "I133")) {
        } else if (name_starts_with(chnuclide_, "I134")) {
        } else if (name_starts_with(chnuclide_, "I135")) {
        } else if (name_starts_with(chnuclide_, "K40")) {
        } else if (name_starts_with(chnuclide_, "K42")) {
        } else if (name_starts_with(chnuclide_, "Kr81")) {
        } else if (name_starts_with(chnuclide_, "Kr85")) {
        } else if (name_starts_with(chnuclide_, "Mn54")) {
        } else if (name_starts_with(chnuclide_, "Na22")) {
        } else if (name_starts_with(chnuclide_, "P32")) {
        } else if (name_starts_with(chnuclide_, "Pa231")) {
        } else if (name_starts_with(chnuclide_, "Pa234m")) {
        } else if (name_starts_with(chnuclide_, "Pb210")) {
        } else if (name_starts_with(chnuclide_, "Pb211")) {
        } else if (name_starts_with(chnuclide_, "Pb212")) {
        } else if (name_starts_with(chnuclide_, "Pb214")) {
        } else if (name_starts_with(chnuclide_, "Po210")) {
        } else if (name_starts_with(chnuclide_, "Po214")) {
        } else if (name_starts_with(chnuclide_, "Po218")) {
        } else if (name_starts_with(chnuclide_, "Ra226")) {
        } else if (name_starts_with(chnuclide_, "Ra228")) {
        } else if (name_starts_with(chnuclide_, "Rb87")) {
        } else if (name_starts_with(chnuclide_, "Rh106")) {
        } else if (name_starts_with(chnuclide_, "Rn222")) { // Added 2020-07-17
        } else if (name_starts_with(chnuclide_, "Sb125")) {
        } else if (name_starts_with(chnuclide_, "Sb126")) {
        } else if (name_starts_with(chnuclide_, "Sb133")) {
        } else if (name_starts_with(chnuclide_, "Sr90")) {
        } else if (name_starts_with(chnuclide_, "Ta180m")) { // 'Ta180m-B-' and 'Ta180m-EC' 
        } else if (name_starts_with(chnuclide_, "Ta182")) {
        } else if (name_starts_with(chnuclide_, "Te133m")) {
        } else if (name_starts_with(chnuclide_, "Te133")) {
        } else if (name_starts_with(chnuclide_, "Te134")) {
        } else if (name_starts_with(chnuclide_, "Th230")) {
        } else if (name_starts_with(chnuclide_, "Th234")) {
        } else if (name_starts_with(chnuclide_, "Tl207")) {
        } else if (name_starts_with(chnuclide_, "Tl208")) {
        } else if (name_starts_with(chnuclide_, "U234")) {
        } else if (name_starts_with(chnuclide_, "U238")) {
        } else if (name_starts_with(chnuclide_, "Xe129m")) {
        } else if (name_starts_with(chnuclide_, "Xe131m")) {
        } else if (name_starts_with(chnuclide_, "Xe133")) {
        } else if (name_starts_with(chnuclide_, "Xe135")) {
        } else if (name_starts_with(chnuclide_, "Y88")) {
        } else if (name_starts_with(chnuclide_, "Y90")) {
        } else if (name_starts_with(chnuclide_, "Zn65")) {
        } else if (name_starts_with(chnuclide_, "Zr96")) {
        } else {
          std::cerr << "[error] "
                    << "bxdecay0::genbbsub: "
                    << "Unknown background & source nuclide '" << chnuclide_ << "' !\n";
          ier_ = 1;
          if (trace) {
            std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
          }
          return;
        }
        if (trace) {
          std::cerr << "[debug] bxdecay0::genbbsub: Checking background decays is done." << std::endl;
        }
      }

      /* The code for output ASCII file has not been ported in C++ */

      bb_params_.istartbb = 0;
      if (istart_ == GENBBSUB_ISTART_INIT) {
        if (i2bbs_ == 1) {
          if (trace) {
            std::cerr << "[debug] bxdecay0::genbbsub: Initializing DBD process..." << std::endl;
          }
          // Compute daughter level in MeV :
          bb_params_.Edlevel = bb_params_.levelE / 1000.;
          if (trace) {
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: DBD parameters (before init):" << std::endl;
            }
            bb_params_.dump(std::cerr, "[debug] ");
          }
          decay0_bb(prng_, event_, &bb_params_);
          if (trace) {
            std::cerr << "[debug] bxdecay0::genbbsub: Initializing DBD process is done." << std::endl;
          }
          if (trace) {
            if (trace) {
              std::cerr << "[debug] bxdecay0::genbbsub: DBD parameters (after init):" << std::endl;
            }
            bb_params_.dump(std::cerr, "[debug] ");
          }
        }
        // istart_ = GENBBSUB_ISTART_GENERATE;
        if (trace) {
          std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
        }
        return;
      }
      // istart_ = GENBBSUB_ISTART_GENERATE;
    }

    /*********************
     * Double beta decay *
     *********************/
    event_.set_generator(chnuclide_);
    if (i2bbs_ == GENBBSUB_I2BBS_DBD) {
      event_.set_time(0.0);
      if (trace) {
        std::cerr << "[debug] bxdecay0::genbbsub: Generating DBD emitted particles..." << std::endl;
      }
      decay0_bb(prng_, event_, &bb_params_);
      if (trace) {
        std::cerr << "[debug] bxdecay0::genbbsub: Process de-excitation particles..." << std::endl;
      }
      if (name_starts_with(chnuclide_, "Ca48")) {
        Ti48low(prng_, event_, bb_params_.levelE);
      }
      if (name_starts_with(chnuclide_, "Ni58")) {
        Fe58low(prng_, event_, bb_params_.levelE);
      }
      if (name_starts_with(chnuclide_, "Ge76")) {
        Se76low(prng_, event_, bb_params_.levelE);
      }
      if (name_starts_with(chnuclide_, "Zn64")) {
        Ni64low(prng_, event_, bb_params_.levelE);
      }
      if (name_starts_with(chnuclide_, "Zn70")) {
        Ge70low(prng_, event_, bb_params_.levelE);
      }
      if (name_starts_with(chnuclide_, "Se74")) {
        Ge74low(prng_, event_, bb_params_.levelE);
      }
      if (name_starts_with(chnuclide_, "Se82")) {
        Kr82low(prng_, event_, bb_params_.levelE);
      }
      if (name_starts_with(chnuclide_, "Sr84")) {
        Kr84low(prng_, event_, bb_params_.levelE);
      }
      if (name_starts_with(chnuclide_, "Zr94")) {
        Mo94low(prng_, event_, bb_params_.levelE);
      }
      if (name_starts_with(chnuclide_, "Zr96")) {
        Mo96low(prng_, event_, bb_params_.levelE);
      }
      if (name_starts_with(chnuclide_, "Mo92")) {
        Zr92low(prng_, event_, bb_params_.levelE);
      }
      if (name_starts_with(chnuclide_, "Mo100")) {
        Ru100low(prng_, event_, bb_params_.levelE);
      }
      if (name_starts_with(chnuclide_, "Ru96")) {
        Mo96low(prng_, event_, bb_params_.levelE);
      }
      if (name_starts_with(chnuclide_, "Ru104")) {
        Pd104low(prng_, event_, bb_params_.levelE);
      }
      if (name_starts_with(chnuclide_, "Cd106")) {
        Pd106low(prng_, event_, bb_params_.levelE);
      }
      if (name_starts_with(chnuclide_, "Cd108")) {
        Pd108low(prng_, event_, bb_params_.levelE);
      }
      if (name_starts_with(chnuclide_, "Cd114")) {
        Sn114low(prng_, event_, bb_params_.levelE);
      }
      if (name_starts_with(chnuclide_, "Cd116")) {
        Sn116low(prng_, event_, bb_params_.levelE);
      }
      if (name_starts_with(chnuclide_, "Sn112")) {
        Cd112low(prng_, event_, bb_params_.levelE);
      }
      if (name_starts_with(chnuclide_, "Sn122")) {
        Te122low(prng_, event_, bb_params_.levelE);
      }
      if (name_starts_with(chnuclide_, "Sn124")) {
        Te124low(prng_, event_, bb_params_.levelE);
      }
      if (name_starts_with(chnuclide_, "Te120")) {
        Sn120low(prng_, event_, bb_params_.levelE);
      }
      if (name_starts_with(chnuclide_, "Te128")) {
        Xe128low(prng_, event_, bb_params_.levelE);
      }
      if (name_starts_with(chnuclide_, "Te130")) {
        Xe130low(prng_, event_, bb_params_.levelE);
      }
      if (name_starts_with(chnuclide_, "Xe136")) {
        Ba136low(prng_, event_, bb_params_.levelE);
      }
      if (name_starts_with(chnuclide_, "Ce136")) {
        Ba136low(prng_, event_, bb_params_.levelE);
      }
      if (name_starts_with(chnuclide_, "Ce138")) {
        Ba138low(prng_, event_, bb_params_.levelE);
      }
      if (name_starts_with(chnuclide_, "Ce142")) {
        Nd142low(prng_, event_, bb_params_.levelE);
      }
      if (name_starts_with(chnuclide_, "Nd148")) {
        Sm148low(prng_, event_, bb_params_.levelE);
      }
      if (name_starts_with(chnuclide_, "Nd150")) {
        Sm150low(prng_, event_, bb_params_.levelE);
      }
      if (name_starts_with(chnuclide_, "Sm144")) {
        Nd144low(prng_, event_, bb_params_.levelE); // New 2018-12-05
      }
      if (name_starts_with(chnuclide_, "Sm154")) {
        Gd154low(prng_, event_, bb_params_.levelE); // New 2018-12-05
      }
      if (name_starts_with(chnuclide_, "Dy156")) {
        Gd156low(prng_, event_, bb_params_.levelE);
      }
      if (name_starts_with(chnuclide_, "Dy158")) {
        Gd158low(prng_, event_, bb_params_.levelE);
      }
      if (name_starts_with(chnuclide_, "Er162")) {
        Dy162low(prng_, event_, bb_params_.levelE); // New 2018-12-05
      }
      if (name_starts_with(chnuclide_, "Er164")) {
        Dy164low(prng_, event_, bb_params_.levelE); // New 2018-12-05
      }
      if (name_starts_with(chnuclide_, "Er170")) {
        Yb170low(prng_, event_, bb_params_.levelE); // New 2018-12-05
      }
      if (name_starts_with(chnuclide_, "Yb168")) {
        Er168low(prng_, event_, bb_params_.levelE); // New 2018-12-05
      }
      if (name_starts_with(chnuclide_, "Yb176")) {
        Hf176low(prng_, event_, bb_params_.levelE); // New 2018-12-05
      }
      if (name_starts_with(chnuclide_, "W180")) {
        Hf180low(prng_, event_, bb_params_.levelE);
      }
      if (name_starts_with(chnuclide_, "W186")) {
        Os186low(prng_, event_, bb_params_.levelE);
      }
      if (name_starts_with(chnuclide_, "Pt190")) {
        Os190low(prng_, event_, bb_params_.levelE);
      }
      if (name_starts_with(chnuclide_, "Pt198")) {
        Hg198low(prng_, event_, bb_params_.levelE);
      }
      if (name_starts_with(chnuclide_, "Bi214")) {
        At214low(prng_, event_, 0);
        npfull0 = event_.get_particles().size();
        At214(prng_, event_, 0., tdnuc1);
        event_.shift_particles_time(tdnuc1, npfull0);
      }
      if (name_starts_with(chnuclide_, "Pb214")) {
        Po214low(prng_, event_, 0);
        npfull0 = event_.get_particles().size();
        Po214(prng_, event_, 0., tdnuc1);
        event_.shift_particles_time(tdnuc1, npfull0);
      }
      if (name_starts_with(chnuclide_, "Po218")) {
        Rn218low(prng_, event_, 0);
        npfull0 = event_.get_particles().size();
        Rn218(prng_, event_, 0., tdnuc1);
        event_.shift_particles_time(tdnuc1, npfull0);
        npfull0 = event_.get_particles().size();
        Po214(prng_, event_, 0., tdnuc1);
        event_.shift_particles_time(tdnuc1, npfull0);
      }
      if (name_starts_with(chnuclide_, "Rn222")) {
        Ra222low(prng_, event_, 0);
        npfull0 = event_.get_particles().size();
        Ra222(prng_, event_, 0., tdnuc1);
        event_.shift_particles_time(tdnuc1, npfull0);
        npfull0 = event_.get_particles().size();
        Rn218(prng_, event_, 0., tdnuc1);
        event_.shift_particles_time(tdnuc1, npfull0);
        npfull0 = event_.get_particles().size();
        Po214(prng_, event_, 0., tdnuc1);
        event_.shift_particles_time(tdnuc1, npfull0);
      }
      if (trace) {
        std::cerr << "[debug] bxdecay0::genbbsub: DBD emitted particles are done." << std::endl;
      }
    }

    /***************
     * Backgrounds *
     ***************/
    if (i2bbs_ == 2) {
      if (trace) {
        std::cerr << "[debug] bxdecay0::genbbsub: Generating background emitted particles..." << std::endl;
      }
      if (name_starts_with(chnuclide_, "Ac228")) {
        Ac228(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Am241")) {
        Am241(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Ar39")) {
        Ar39(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Ar42")) {
        Ar42(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "As79")) {
        As79(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Bi207")) {
        Bi207(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Bi208")) {
        Bi208(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Bi210")) {
        Bi210(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Bi212")) {
        Bi212(prng_, event_, 0., tdnuc);
        npfull0 = event_.get_particles().size();
        if (!event_.get_particles().front().is_alpha()) {
          Po212(prng_, event_, 0., tdnuc1);
          event_.shift_particles_time(tdnuc1, npfull0);
        }
      }
      if (name_starts_with(chnuclide_, "Bi214")) {
        Bi214(prng_, event_, 0., tdnuc);
        npfull0 = event_.get_particles().size();
        if (!event_.get_particles().front().is_alpha()) {
          Po214(prng_, event_, 0., tdnuc1);
          event_.shift_particles_time(tdnuc1, npfull0);
        }
      }
      if (name_starts_with(chnuclide_, "Ca48")) {
        Ca48(prng_, event_, 0., tdnuc);
        npfull0 = event_.get_particles().size();
        Sc48(prng_, event_, 0., tdnuc1);
        event_.shift_particles_time(tdnuc1, npfull0);
      }
      if (name_starts_with(chnuclide_, "C14")) {
        C14(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Cd113")) {
        Cd113(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Co60")) {
        Co60(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Cs136")) {
        Cs136(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Cs137")) {
        Cs137(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Eu147")) {
        Eu147(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Eu152")) {
        Eu152(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Eu154")) {
        Eu154(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Gd146")) {
        Gd146(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Hf182")) {
        Hf182(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "I126")) {
        I126(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "I133")) {
        I133(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "I134")) {
        I134(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "I135")) {
        I135(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "K40")) {
        K40(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "K42")) {
        K42(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Kr81")) {
        Kr81(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Kr85")) {
        Kr85(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Mn54")) {
        Mn54(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Na22")) {
        Na22(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "P32")) {
        P32(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Pa231")) {
        Pa231(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Pa234m")) {
        Pa234m(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Pb210")) {
        Pb210(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Pb211")) {
        Pb211(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Pb212")) {
        Pb212(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Pb214")) {
        Pb214(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Po210")) {
        Po210(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Po214")) {
        Po214(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Po218")) {
        Po218(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Ra226")) {
        Ra226(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Ra228")) {
        Ra228(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Rb87")) {
        Rb87(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Rh106")) {
        Rh106(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Rn222")) {
        Rn222(prng_, event_, 0., tdnuc); // Added 2020-07-17
      }
      if (name_starts_with(chnuclide_, "Sb125")) {
        Sb125(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Sb126")) {
        Sb126(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Sb133")) {
        Sb133(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Sr90")) {
        Sr90(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Ta180m-B-")) {
        Ta180mB(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Ta180m-EC")) {
        Ta180mEC(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Ta182")) {
        Ta182(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Te133")) {
        Te133(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Te133m")) {
        Te133m(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Te134")) {
        Te134(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Th230")) {
        Th230(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Th234")) {
        Th234(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Tl207")) {
        Tl207(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Tl208")) {
        Tl208(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "U234")) {
        U234(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "U238")) {
        U238(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Xe129m")) {
        Xe129m(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Xe131m")) {
        Xe131m(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Xe133")) {
        Xe133(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Xe135")) {
        Xe135(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Y88")) {
        Y88(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Y90")) {
        Y90(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Zn65")) {
        Zn65(prng_, event_, 0., tdnuc);
      }
      if (name_starts_with(chnuclide_, "Zr96")) {
        Zr96(prng_, event_, 0., tdnuc);
        npfull0 = event_.get_particles().size();
        Nb96(prng_, event_, 0., tdnuc1);
        event_.shift_particles_time(tdnuc1, npfull0);
      }
      // tevst=tdnuc;
      // 2015-11-29: FM+XG: force reference decay time to 0
      // was:
      // event_.set_time(tdnuc);
      // now:
      event_.set_time(0.0);

      /* The following cases have not been ported in C++ (will they ever be ?)
       * - Artificial
       * - Compton
       * - Moller
       * - E+E- external
       */
      if (trace) {
        std::cerr << "[debug] bxdecay0::genbbsub: Background emitted particles are done." << std::endl;
      }
    }

    if (trace) {
      std::cerr << "[debug] bxdecay0::genbbsub: Exiting." << std::endl;
    }
    return;
  }

} // end of namespace bxdecay0
