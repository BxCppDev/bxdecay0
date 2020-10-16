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
#include <bxdecay0/As79.h>

// Standard library:
#include <cmath>
#include <sstream>
#include <stdexcept>

// This project:
#include <bxdecay0/PbAtShell.h>
#include <bxdecay0/alpha.h>
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
#include <bxdecay0/particle.h>
#include <bxdecay0/positron.h>

namespace bxdecay0 {

  void As79(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_)
  {
    double t;
    double tdlev;
    double p;
    double pbeta;
    double tclev;
    double thlev;
    double thnuc;
    // Model for scheme of As79+Se79m decay ("Table of Isotopes", 8th ed.,
    // 1998 and Nucl. Data Sheets 96(2002)1).
    // Input : tcnuc - time of creation of nucleus (sec)
    // Output: tdnuc - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 1.10.2004.
    thnuc  = 540.6;
    tdnuc_ = tcnuc_ - thnuc / std::log(2.) * std::log(prng_());
    tclev  = 0.;
    pbeta  = 100. * prng_();
    if (pbeta <= 0.24) {
      goto label_1089;
    }
    if (pbeta <= 0.67) {
      goto label_1080;
    }
    if (pbeta <= 2.43) {
      goto label_975;
    }
    if (pbeta <= 2.69) {
      goto label_572;
    }
    if (pbeta <= 3.79) {
      goto label_528;
    }
    if (pbeta <= 5.24) {
      goto label_365;
    }
    goto label_96;
  label_1089:
    decay0_beta(prng_, event_, 1.192, 34., 0., 0., t);
    //// label_10890  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 53.70) {
      goto label_10891;
    }
    goto label_10892;
  label_10891:
    decay0_nucltransK(prng_, event_, 0.993, 0.013, 4.0e-4, 0., tclev, thlev, tdlev);
    goto label_96000;
  label_10892:
    decay0_nucltransK(prng_, event_, 0.724, 0.013, 8.5e-4, 0., tclev, thlev, tdlev);
    goto label_36500;
  label_1080:
    decay0_beta(prng_, event_, 1.201, 34., 0., 0., t);
    //// label_10800  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 68.97) {
      goto label_10801;
    }
    goto label_10802;
  label_10801:
    decay0_nucltransK(prng_, event_, 0.715, 0.013, 8.5e-4, 0., tclev, thlev, tdlev);
    goto label_36500;
  label_10802:
    decay0_nucltransK(prng_, event_, 0.552, 0.013, 1.5e-3, 0., tclev, thlev, tdlev);
    goto label_52800;
  label_975:
    decay0_beta(prng_, event_, 1.306, 34., 0., 0., t);
    ///// label_97500  :
    thlev = 0.;
    p     = 100. * prng_();
    if (p <= 79.37) {
      goto label_97501;
    }
    if (p <= 94.45) {
      goto label_97502;
    }
    goto label_97503;
  label_97501:
    decay0_nucltransK(prng_, event_, 0.879, 0.013, 5.5e-4, 0., tclev, thlev, tdlev);
    goto label_96000;
  label_97502:
    decay0_nucltransK(prng_, event_, 0.447, 0.013, 2.5e-3, 0., tclev, thlev, tdlev);
    goto label_52800;
  label_97503:
    decay0_nucltransK(prng_, event_, 0.402, 0.013, 3.2e-3, 0., tclev, thlev, tdlev);
    goto label_57200;
  label_572:
    decay0_beta(prng_, event_, 1.709, 34., 0., 0., t);
  label_57200:
    thlev = 1.6e-11;
    p     = 100. * prng_();
    if (p <= 95.33) {
      goto label_57201;
    }
    goto label_57202;
  label_57201:
    decay0_nucltransK(prng_, event_, 0.476, 0.013, 1.0e-3, 0., tclev, thlev, tdlev);
    goto label_96000;
  label_57202:
    decay0_nucltransK(prng_, event_, 0.207, 0.013, 1.8e-2, 0., tclev, thlev, tdlev);
    goto label_36500;
  label_528:
    decay0_beta(prng_, event_, 1.753, 34., 0., 0., t);
  label_52800:
    thlev = 3.1e-12;
    decay0_nucltransK(prng_, event_, 0.432, 0.013, 2.7e-3, 0., tclev, thlev, tdlev);
    goto label_96000;
  label_365:
    decay0_beta(prng_, event_, 1.916, 34., 0., 0., t);
  label_36500:
    thlev = 9.4e-11;
    decay0_nucltransK(prng_, event_, 0.365, 0.013, 2.0e-3, 0., tclev, thlev, tdlev);
    return;
  label_96:
    decay0_beta(prng_, event_, 2.185, 34., 0., 0., t);
  label_96000:
    thlev = 235.2;
    p     = 100. * prng_();
    if (p <= 99.944) {
      goto label_96001;
    }
    goto label_96002;
  label_96001:
    decay0_nucltransK(prng_, event_, 0.096, 0.013, 9.39, 0., tclev, thlev, tdlev); // IT to Se79 (gs)
    return;
  label_96002:
    decay0_beta(prng_, event_, 0.247, 35., tclev, thlev, tdlev); // beta to Br79 (gs)
    return;
  }
  // end of As79.f

} // end of namespace bxdecay0

// end of As79.cc
// Local Variables: --
// mode: c++ --
// End: --
