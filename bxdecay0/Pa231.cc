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
#include <bxdecay0/Pa231.h>

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

  void Pa231(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_)
  {
    // Models for scheme of Pa231 decay:
    //  - http://www.nucleide.org/DDEP_WG/Nuclides/Pa-231_tables.pdf
    //  - http://www.nucleide.org/DDEP_WG/Nuclides/Pa-231_com.pdf
    //  - ENSDF at NNDC site on 11.07.2013
    //  - http://xdb.lbl.gov/Section1/Table_1-1c.htm

    // Halflife time of Pa231
    const double thnuc = 1.03e12; // 32670 y
    tdnuc_             = tcnuc_ - thnuc / std::log(2.) * std::log(prng_());

    // Nuclear transition parameters
    double thlev = 0.0;                               /// input- level halflife (sec).
    double tclev = 0.0;                               /// input - time of creation of level from which
                                                      /// particle will be emitted (sec);
    double tdlev;                                     /// output - time of decay of level (sec)
    double t;                                         /// output - time of decay
    const double AcElectronBindingEnergyK = 0.106855; /// binding energy of electron (MeV) on K-shell
    const double AcElectronBindingEnergyL = 0.018264; /// binding energy of electron (MeV) on L-shell
    const double AcElectronBindingEnergyM = 0.004031; /// binding energy of electron (MeV) on M-shell

    // Probabilities
    double pgamma;
    const double palpha = 100.0 * prng_();
    if (palpha <= 0.0008) {
      // Alpha 4533.0 keV
      decay0_alpha(prng_, event_, 4.5330, 0., 0., t);
      goto level_537000;
    } else if (palpha <= 0.0029) {
      // Alpha 4415.6 keV
      decay0_alpha(prng_, event_, 4.4156, 0., 0., t);
      goto level_656000;
    } else if (palpha <= 0.0061) {
      // Alpha 4761.2 keV
      decay0_alpha(prng_, event_, 4.7612, 0., 0., t);
      goto level_304000;
    } else if (palpha <= 0.0097) {
      // Alpha 4507.6 keV
      decay0_alpha(prng_, event_, 4.5076, 0., 0., t);
      goto level_562000;
    } else if (palpha <= 0.0177) {
      // Alpha 4568.1 keV
      decay0_alpha(prng_, event_, 4.5681, 0., 0., t);
      goto level_501000;
    } else if (palpha <= 0.0327) {
      // Alpha 4599.6 keV
      decay0_alpha(prng_, event_, 4.5996, 0., 0., t);
      goto level_469000;
    } else if (palpha <= 0.0727) {
      // Alpha 4794.1 keV
      decay0_alpha(prng_, event_, 4.7941, 0., 0., t);
      goto level_271000;
    } else if (palpha <= 0.1231) {
      // Alpha 4633.0 keV
      decay0_alpha(prng_, event_, 4.6330, 0., 0., t);
      goto level_435000;
    } else if (palpha <= 0.2011) {
      // Alpha 4630.3 keV
      decay0_alpha(prng_, event_, 4.6303, 0., 0., t);
      goto level_437000;
    } else if (palpha <= 0.2811) {
      // Alpha 4642.5 keV
      decay0_alpha(prng_, event_, 4.6425, 0., 0., t);
      goto level_425000;
    } else if (palpha <= 0.6811) {
      // Alpha 4977.6 keV
      decay0_alpha(prng_, event_, 4.9776, 0., 0., t);
      goto level_84000;
    } else if (palpha <= 1.8811) {
      // Alpha 4712.3 keV
      decay0_alpha(prng_, event_, 4.7123, 0., 0., t);
      goto level_354000;
    } else if (palpha <= 3.2811) {
      // Alpha 4853.5 keV
      decay0_alpha(prng_, event_, 4.8535, 0., 0., t);
      goto level_210000;
    } else if (palpha <= 4.8811) {
      // Alpha 4987.8 keV
      decay0_alpha(prng_, event_, 4.9878, 0., 0., t);
      goto level_74000;
    } else if (palpha <= 6.6811) {
      // Alpha 4680.1 keV
      decay0_alpha(prng_, event_, 4.6801, 0., 0., t);
      goto level_387000;
    } else if (palpha <= 9.4811) {
      // Alpha 5033.8 keV
      decay0_alpha(prng_, event_, 5.0338, 0., 0., t);
      goto level_27000;
    } else if (palpha <= 12.3811) {
      // Alpha 4936.0 keV
      decay0_alpha(prng_, event_, 4.9360, 0., 0., t);
      goto level_126000;
    } else if (palpha <= 20.7811) {
      // Alpha 4736.3 keV
      decay0_alpha(prng_, event_, 4.7363, 0., 0., t);
      goto level_330000;
    } else if (palpha <= 32.4811) {
      // Alpha 5060.7 keV
      decay0_alpha(prng_, event_, 5.0607, 0., 0., t);
      goto level_0000;
    } else if (palpha <= 52.4811) {
      // Alpha 5031.2 keV
      decay0_alpha(prng_, event_, 5.0312, 0., 0., t);
      goto level_29000;
    } else if (palpha <= 74.9811) {
      // Alpha 4952.6 keV
      decay0_alpha(prng_, event_, 4.9526, 0., 0., t);
      goto level_109000;
    } else if (palpha <= 100.2811) {
      // Alpha 5015.1 keV
      decay0_alpha(prng_, event_, 5.0151, 0., 0., t);
      goto level_46000;
    }

    // Ac227 excited states

  level_656000:
    // Level 656.4 keV
    thlev  = 0.0;
    pgamma = 100. * prng_();
    if (pgamma <= 14.62) {
      decay0_gamma(prng_, event_, 0.5823, tclev, thlev, tdlev);
      goto level_74000;
    } else if (pgamma <= 37.26) {
      decay0_gamma(prng_, event_, 0.5719, tclev, thlev, tdlev);
      goto level_84000;
    } else if (pgamma <= 60.84) {
      decay0_gamma(prng_, event_, 0.6101, tclev, thlev, tdlev);
      goto level_46000;
    } else {
      decay0_gamma(prng_, event_, 0.5465, tclev, thlev, tdlev);
      goto level_109000;
    }

  level_562000:
    // Level 562.8 keV
    thlev  = 0.0;
    pgamma = 100. * prng_();
    if (pgamma <= 16.80) {
      decay0_gamma(prng_, event_, 0.53543, tclev, thlev, tdlev);
      goto level_27000;
    } else if (pgamma <= 54.54) {
      decay0_gamma(prng_, event_, 0.51645, tclev, thlev, tdlev);
      goto level_46000;
    } else {
      decay0_gamma(prng_, event_, 0.48866, tclev, thlev, tdlev);
      goto level_74000;
    }

  level_537000:
    // Level 537.0 keV
    thlev  = 0.0;
    pgamma = 100. * prng_();
    if (pgamma <= 47.37) {
      decay0_gamma(prng_, event_, 0.50963, tclev, thlev, tdlev);
      goto level_27000;
    } else {
      decay0_gamma(prng_, event_, 0.49065, tclev, thlev, tdlev);
      goto level_46000;
    }

  level_501000:
    // Level 501.28 keV
    thlev  = 0.0;
    pgamma = 100. * prng_();
    if (pgamma <= 47.95) {
      decay0_gamma(prng_, event_, 0.42714, tclev, thlev, tdlev);
      goto level_74000;
    } else {
      decay0_gamma(prng_, event_, 0.50128, tclev, thlev, tdlev);
      goto level_0000;
    }

  level_469000:
    // Level 469.24 keV
    thlev = 0.0;
    decay0_gamma(prng_, event_, 0.38469, tclev, thlev, tdlev);
    goto level_84000;

  level_437000:
    // Level 437.96 keV
    thlev  = 0.0;
    pgamma = 100. * prng_();
    if (pgamma <= 2.34) {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.410590,
                          AcElectronBindingEnergyK,
                          0.01482,
                          AcElectronBindingEnergyL,
                          0.00264,
                          AcElectronBindingEnergyM,
                          0.000628,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_27000;
    } else if (pgamma <= 8.09) {
      decay0_gamma(prng_, event_, 0.437960, tclev, thlev, tdlev);
      goto level_0000;
    } else if (pgamma <= 16.88) {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.391610,
                          AcElectronBindingEnergyK,
                          0.01636,
                          AcElectronBindingEnergyL,
                          0.00293,
                          AcElectronBindingEnergyM,
                          0.000697,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_46000;
    } else if (pgamma <= 27.11) {
      decay0_gamma(prng_, event_, 0.363820, tclev, thlev, tdlev);
      goto level_74000;
    } else {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.050730,
                          AcElectronBindingEnergyK,
                          0.0,
                          AcElectronBindingEnergyL,
                          18.8,
                          AcElectronBindingEnergyM,
                          4.52,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_387000;
    }

  level_435000:
    // Level 435.19 keV
    thlev  = 0.0;
    pgamma = 100. * prng_();
    if (pgamma <= 5.83) {
      decay0_gamma(prng_, event_, 0.435190, tclev, thlev, tdlev);
      goto level_0000;
    } else {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.407820,
                          AcElectronBindingEnergyK,
                          0.269,
                          AcElectronBindingEnergyL,
                          0.0496,
                          AcElectronBindingEnergyM,
                          0.01187,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_27000;
    }

  level_425000:
    // Level 425.59 keV
    thlev  = 0.0;
    pgamma = 100. * prng_();
    if (pgamma <= 2.85) {
      thlev = 0.0;
      decay0_nucltransKLM(prng_,
                          event_,
                          0.395610,
                          AcElectronBindingEnergyK,
                          0.01601,
                          AcElectronBindingEnergyL,
                          0.00286,
                          AcElectronBindingEnergyM,
                          0.000682,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_29000;
    } else if (pgamma <= 6.44) {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.351450,
                          AcElectronBindingEnergyK,
                          0.0206,
                          AcElectronBindingEnergyL,
                          0.00373,
                          AcElectronBindingEnergyM,
                          0.000891,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_74000;
    } else if (pgamma <= 18.21) {
      decay0_gamma(prng_, event_, 0.398220, tclev, thlev, tdlev);
      goto level_27000;
    } else {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.379240,
                          AcElectronBindingEnergyK,
                          0.25,
                          AcElectronBindingEnergyL,
                          0.052,
                          AcElectronBindingEnergyM,
                          0.0125,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_46000;
    }

  level_387000:
    // Level 387.23 keV
    thlev  = 0.0;
    pgamma = 100. * prng_();
    if (pgamma <= 0.02) {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.387230,
                          AcElectronBindingEnergyK,
                          0.0430,
                          AcElectronBindingEnergyL,
                          0.0254,
                          AcElectronBindingEnergyM,
                          0.00667,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_0000;
    } else if (pgamma <= 0.47) {
      decay0_gamma(prng_, event_, 0.359860, tclev, thlev, tdlev);
      goto level_27000;
    } else if (pgamma <= 5.8) {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.277290,
                          AcElectronBindingEnergyK,
                          0.4,
                          AcElectronBindingEnergyL,
                          0.11,
                          AcElectronBindingEnergyM,
                          0.03,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_109000;
    } else if (pgamma <= 12.68) {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.313090,
                          AcElectronBindingEnergyK,
                          0.22,
                          AcElectronBindingEnergyL,
                          0.070,
                          AcElectronBindingEnergyM,
                          0.0177,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_74000;
    } else if (pgamma <= 23.13) {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.340880,
                          AcElectronBindingEnergyK,
                          0.081,
                          AcElectronBindingEnergyL,
                          0.020,
                          AcElectronBindingEnergyM,
                          0.0050,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_46000;
    } else if (pgamma <= 34.86) {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.302680,
                          AcElectronBindingEnergyK,
                          0.0285,
                          AcElectronBindingEnergyL,
                          0.00527,
                          AcElectronBindingEnergyM,
                          0.001260,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_84000;
    } else if (pgamma <= 47.65) {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.357250,
                          AcElectronBindingEnergyK,
                          0.34,
                          AcElectronBindingEnergyL,
                          0.066,
                          AcElectronBindingEnergyM,
                          0.0159,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_29000;
    } else if (pgamma <= 62.68) {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.260370,
                          AcElectronBindingEnergyK,
                          0.37,
                          AcElectronBindingEnergyL,
                          0.133,
                          AcElectronBindingEnergyM,
                          0.0340,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_126000;
    } else {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.057190,
                          AcElectronBindingEnergyK,
                          0.0,
                          AcElectronBindingEnergyL,
                          108.5,
                          AcElectronBindingEnergyM,
                          29.6,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_330000;
    }

  level_354000:
    // Level 354.5 keV
    thlev  = 0.0;
    pgamma = 100. * prng_();
    if (pgamma <= 3.11) {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.327130,
                          AcElectronBindingEnergyK,
                          0.0240,
                          AcElectronBindingEnergyL,
                          0.00440,
                          AcElectronBindingEnergyM,
                          0.001050,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_27000;
    } else if (pgamma <= 12.25) {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.354500,
                          AcElectronBindingEnergyK,
                          0.0855,
                          AcElectronBindingEnergyL,
                          0.0386,
                          AcElectronBindingEnergyM,
                          0.01003,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_0000;
    } else {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.024460,
                          AcElectronBindingEnergyK,
                          0.0,
                          AcElectronBindingEnergyL,
                          161.3,
                          AcElectronBindingEnergyM,
                          39.0,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_330000;
    }

  level_330000:
    // Level 330.04 keV
    thlev  = 0.0;
    pgamma = 100. * prng_();
    if (pgamma <= 0.39) {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.245490,
                          AcElectronBindingEnergyK,
                          3.70,
                          AcElectronBindingEnergyL,
                          1.143,
                          AcElectronBindingEnergyM,
                          0.293,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_84000;
    } else if (pgamma <= 1.63) {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.255900,
                          AcElectronBindingEnergyK,
                          0.0992,
                          AcElectronBindingEnergyL,
                          0.1216,
                          AcElectronBindingEnergyM,
                          0.0327,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_74000;
    } else if (pgamma <= 3.29) {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.056900,
                          AcElectronBindingEnergyK,
                          0.0,
                          AcElectronBindingEnergyL,
                          28,
                          AcElectronBindingEnergyM,
                          7.1,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_273000;
    } else if (pgamma <= 19.19) {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.283690,
                          AcElectronBindingEnergyK,
                          0.0329,
                          AcElectronBindingEnergyL,
                          0.00614,
                          AcElectronBindingEnergyM,
                          0.001468,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_46000;
    } else if (pgamma <= 38.51) {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.330040,
                          AcElectronBindingEnergyK,
                          0.430,
                          AcElectronBindingEnergyL,
                          0.0836,
                          AcElectronBindingEnergyM,
                          0.0202,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_0000;
    } else if (pgamma <= 60.7) {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.302670,
                          AcElectronBindingEnergyK,
                          0.0285,
                          AcElectronBindingEnergyL,
                          0.00527,
                          AcElectronBindingEnergyM,
                          0.001260,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_27000;
    } else {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.300060,
                          AcElectronBindingEnergyK,
                          0.613,
                          AcElectronBindingEnergyL,
                          0.1146,
                          AcElectronBindingEnergyM,
                          0.0275,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_29000;
    }

  level_304000:
    // Level 304.73 keV
    thlev  = 0.0;
    pgamma = 100. * prng_();
    if (pgamma <= 46.88) {
      decay0_gamma(prng_, event_, 0.258380, tclev, thlev, tdlev);
      goto level_46000;
    } else {
      decay0_gamma(prng_, event_, 0.230590, tclev, thlev, tdlev);
      goto level_74000;
    }

  level_273000:
    // Level 273.14 keV
    thlev  = 0.0;
    pgamma = 100. * prng_();
    if (pgamma <= 1.65) {
      decay0_gamma(prng_, event_, 0.199000, tclev, thlev, tdlev);
      goto level_74000;
    } else if (pgamma <= 8.79) {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.245770,
                          AcElectronBindingEnergyK,
                          0.0455,
                          AcElectronBindingEnergyL,
                          0.00867,
                          AcElectronBindingEnergyM,
                          0.00208,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_27000;
    } else if (pgamma <= 44.5) {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.243160,
                          AcElectronBindingEnergyK,
                          0.56,
                          AcElectronBindingEnergyL,
                          0.176,
                          AcElectronBindingEnergyM,
                          0.0445,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_29000;
    } else {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.273140,
                          AcElectronBindingEnergyK,
                          0.57,
                          AcElectronBindingEnergyL,
                          0.131,
                          AcElectronBindingEnergyM,
                          0.0323,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_0000;
    }

  level_271000:
    // Level 271.29 keV
    thlev  = 0.0;
    pgamma = 100. * prng_();
    if (pgamma <= 43.94) {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.072580,
                          AcElectronBindingEnergyK,
                          0.0,
                          AcElectronBindingEnergyL,
                          6.59,
                          AcElectronBindingEnergyM,
                          1.582,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_198000;
    } else {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.144430,
                          AcElectronBindingEnergyK,
                          0.263,
                          AcElectronBindingEnergyL,
                          1.407,
                          AcElectronBindingEnergyM,
                          0.384,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_126000;
    }

  level_210000:
    // Level 210.78 keV
    thlev  = 0.0;
    pgamma = 100. * prng_();
    if (pgamma <= 17.61) {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.100840,
                          AcElectronBindingEnergyK,
                          0.0,
                          AcElectronBindingEnergyL,
                          7.30,
                          AcElectronBindingEnergyM,
                          2.00,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_109000;
    } else {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.023460,
                          AcElectronBindingEnergyK,
                          0.0,
                          AcElectronBindingEnergyL,
                          182,
                          AcElectronBindingEnergyM,
                          44.1,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_187000;
    }

  level_198000:
    // Level 198.71 keV
    thlev  = 0.0;
    pgamma = 100. * prng_();
    if (pgamma <= 46.68) {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.071850,
                          AcElectronBindingEnergyK,
                          0.0,
                          AcElectronBindingEnergyL,
                          6.79,
                          AcElectronBindingEnergyM,
                          1.630,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_126000;
    } else {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.124570,
                          AcElectronBindingEnergyK,
                          0.285,
                          AcElectronBindingEnergyL,
                          2.75,
                          AcElectronBindingEnergyM,
                          0.752,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_74000;
    }

  level_187000:
    // Level 187.32 keV
    thlev  = 0.0;
    pgamma = 100. * prng_();
    if (pgamma <= 1.07) {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.060460,
                          AcElectronBindingEnergyK,
                          0.0,
                          AcElectronBindingEnergyL,
                          0.327,
                          AcElectronBindingEnergyM,
                          0.0800,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_126000;
    } else if (pgamma <= 29.33) {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.102770,
                          AcElectronBindingEnergyK,
                          0.0,
                          AcElectronBindingEnergyL,
                          6.69,
                          AcElectronBindingEnergyM,
                          1.83,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_84000;
    } else {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.077380,
                          AcElectronBindingEnergyK,
                          0.0,
                          AcElectronBindingEnergyL,
                          5.47,
                          AcElectronBindingEnergyM,
                          1.313,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_109000;
    }

  level_126000:
    // Level 126.86 keV
    thlev  = 0.0;
    pgamma = 100. * prng_();
    if (pgamma <= 38.33) {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.096880,
                          AcElectronBindingEnergyK,
                          0.0,
                          AcElectronBindingEnergyL,
                          8.81,
                          AcElectronBindingEnergyM,
                          2.41,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_29000;
    } else {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.052720,
                          AcElectronBindingEnergyK,
                          0.0,
                          AcElectronBindingEnergyL,
                          16.81,
                          AcElectronBindingEnergyM,
                          4.03,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_74000;
    }

  level_109000:
    // Level 109.94 keV
    thlev  = 0.0;
    pgamma = 100. * prng_();
    if (pgamma <= 0.20) {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.035800,
                          AcElectronBindingEnergyK,
                          0.0,
                          AcElectronBindingEnergyL,
                          1.313,
                          AcElectronBindingEnergyM,
                          0.327,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_74000;
    } else if (pgamma <= 18.06) {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.063590,
                          AcElectronBindingEnergyK,
                          0.0,
                          AcElectronBindingEnergyL,
                          65.1,
                          AcElectronBindingEnergyM,
                          17.8,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_46000;
    } else {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.025390,
                          AcElectronBindingEnergyK,
                          0.0,
                          AcElectronBindingEnergyL,
                          144.6,
                          AcElectronBindingEnergyM,
                          34.9,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_84000;
    }

  level_84000:
    // Level 84.55 kev
    thlev  = 0.0;
    pgamma = 100. * prng_();
    if (pgamma <= 0.62) {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.054570,
                          AcElectronBindingEnergyK,
                          0.0,
                          AcElectronBindingEnergyL,
                          0.430,
                          AcElectronBindingEnergyM,
                          0.1053,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_29000;
    } else if (pgamma <= 26.59) {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.057180,
                          AcElectronBindingEnergyK,
                          0.0,
                          AcElectronBindingEnergyL,
                          108.6,
                          AcElectronBindingEnergyM,
                          29.6,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_27000;
    } else {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.038200,
                          AcElectronBindingEnergyK,
                          0.0,
                          AcElectronBindingEnergyL,
                          66,
                          AcElectronBindingEnergyM,
                          17,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_46000;
    }

  level_74000:
    // Level 74.14 keV
    thlev  = 0.0;
    pgamma = 100. * prng_();
    if (pgamma <= 31.49) {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.074140,
                          AcElectronBindingEnergyK,
                          0.0,
                          AcElectronBindingEnergyL,
                          31.2,
                          AcElectronBindingEnergyM,
                          8.53,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_0000;
    } else {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.044160,
                          AcElectronBindingEnergyK,
                          0.0,
                          AcElectronBindingEnergyL,
                          28.3,
                          AcElectronBindingEnergyM,
                          6.79,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_29000;
    }

  level_46000:
    // Level 46.35 keV
    thlev  = 0.0;
    pgamma = 100. * prng_();
    if (pgamma <= 0.80) {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.046350,
                          AcElectronBindingEnergyK,
                          0.0,
                          AcElectronBindingEnergyL,
                          0.663,
                          AcElectronBindingEnergyM,
                          0.1634,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_0000;
    } else if (pgamma <= 5.57) {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.016370,
                          AcElectronBindingEnergyK,
                          0.0,
                          AcElectronBindingEnergyL,
                          5.06,
                          AcElectronBindingEnergyM,
                          2.68,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_29000;
    } else {
      decay0_nucltransKLM(prng_,
                          event_,
                          0.018980,
                          AcElectronBindingEnergyK,
                          0.0,
                          AcElectronBindingEnergyL,
                          2.35,
                          AcElectronBindingEnergyM,
                          82.7,
                          0.,
                          tclev,
                          thlev,
                          tdlev);
      goto level_27000;
    }

  level_29000:
    // Level 29.98 keV
    thlev = 0.0;
    decay0_nucltransKLM(prng_,
                        event_,
                        0.029980,
                        AcElectronBindingEnergyK,
                        0.0,
                        AcElectronBindingEnergyL,
                        202,
                        AcElectronBindingEnergyM,
                        52,
                        0.,
                        tclev,
                        thlev,
                        tdlev);
    goto level_0000;

  level_27000:
    // Level 27.37 keV
    thlev = 38.3e-9;
    decay0_nucltransKLM(prng_,
                        event_,
                        0.027370,
                        AcElectronBindingEnergyK,
                        0.0,
                        AcElectronBindingEnergyL,
                        3.3,
                        AcElectronBindingEnergyM,
                        0.87,
                        0.,
                        tclev,
                        thlev,
                        tdlev);
    goto level_0000;

  level_0000:
    // Ground state
    return;
  }

} // end of namespace bxdecay0

// end of Pa231.cc
// Local Variables: --
// mode: c++ --
// End: --
