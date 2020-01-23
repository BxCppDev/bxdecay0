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
#include <bxdecay0/bb.h>

// Standard library:
#include <cmath>
#include <limits>
#include <iostream>
#include <stdexcept>

// Third party:
// - GSL:
#include <gsl/gsl_math.h>

// This project:
#include <bxdecay0/utils.h>
#include <bxdecay0/i_random.h>
#include <bxdecay0/event.h>
#include <bxdecay0/gauss.h>
#include <bxdecay0/fe1_mods.h>
#include <bxdecay0/fe2_mods.h>
#include <bxdecay0/fe12_mods.h>
#include <bxdecay0/dshelp1.h>
#include <bxdecay0/dgmlt1.h>
#include <bxdecay0/fermi.h>
#include <bxdecay0/tgold.h>

namespace bxdecay0 {

  void enrange::_set_defaults()
  {
    ebb1=0.;  // MeV
    ebb2=4.3; // MeV
    toallevents = 1.0;
    levelE = 0;
    itrans02 = 0;
    chdspin.clear();
    return;
  }

  void enrange::reset()
  {
    _set_defaults();
    return;
  }

  enrange::enrange()
  {
    _set_defaults();
    return;
  }

  /*****************************************************/

  void genbbpar::_set_defaults()
  {
    nevents  = 1;
    ievstart = -1;
    irndmst  = 1;
    iwrfile  = 0;

    chfile.clear();
    icurrent = 0;
    return;
  }

  void genbbpar::reset()
  {
    _set_defaults();
    return;
  }

  genbbpar::genbbpar()
  {
    _set_defaults();
    return;
  }

  /*****************************************************/

  void denrange::_set_defaults()
  {
    dens = std::numeric_limits<double>::quiet_NaN();
    denf = std::numeric_limits<double>::quiet_NaN();
    mode = -1;
    return;
  }

  void denrange::reset()
  {
    _set_defaults();
    return;
  }

  denrange::denrange()
  {
    _set_defaults();
    return;
  }

  /*****************************************************/

  void helpbb::_set_defaults()
  {
    Zd = std::numeric_limits<double>::quiet_NaN();
    Ad = std::numeric_limits<double>::quiet_NaN();
    e0 = std::numeric_limits<double>::quiet_NaN();
    e1 = std::numeric_limits<double>::quiet_NaN();
    return;
  }

  void helpbb::reset()
  {
    _set_defaults();
    return;
  }

  helpbb::helpbb()
  {
    _set_defaults();
    return;
  }



  /*****************************************************/
  void eta_nme::_set_defaults()
  {
    chi_GTw = std::numeric_limits<double>::quiet_NaN();
    chi_Fw  = std::numeric_limits<double>::quiet_NaN();
    chip_GT = std::numeric_limits<double>::quiet_NaN();
    chip_F  = std::numeric_limits<double>::quiet_NaN();
    chip_T  = std::numeric_limits<double>::quiet_NaN();
    chip_P  = std::numeric_limits<double>::quiet_NaN();
    chip_R  = std::numeric_limits<double>::quiet_NaN();
    return;
  }

  void eta_nme::reset()
  {
    _set_defaults();
    return;
  }


  /*
   * 7 NMEs: chi_GTw, chi_Fw, chi'_GT, chi'_F, chi'_T, chi'_P, chi'_R
   */
  eta_nme::eta_nme()
  {
    _set_defaults();
    // std::clog << "WARNING: "
    //           << "genbb::decay0::eta_nme::eta_nme: "
    //           << "NME should be read from an input file "
    //           << "or setup by some way !!!"
    //           << std::endl;
    return;
  }

  /*****************************************************/

  void bbpars::dump(std::ostream & out_, const std::string & indent_) const
  {
    out_ << indent_ << "|-- enrange : " << "\n";
    out_ << indent_ << "|   |-- ebb1        : " << ebb1 << " (MeV)\n";
    out_ << indent_ << "|   |-- ebb2        : " << ebb2 << " (MeV)\n";
    out_ << indent_ << "|   |-- toallevents : " << toallevents << "\n";
    out_ << indent_ << "|   |-- levelE      : " << levelE << "\n";
    out_ << indent_ << "|   |-- itrans02    : " << itrans02 << "\n";
    out_ << indent_ << "|   `-- chdspin     : '" << chdspin << "'\n";
    out_ << indent_ << "|-- denrange : " << "\n";
    out_ << indent_ << "|   |-- dens        : " << dens << "\n";
    out_ << indent_ << "|   |-- denf        : " << denf << "\n";
    out_ << indent_ << "|   `-- mode        : " << mode << "\n";
    out_ << indent_ << "|-- helpbb : " << "\n";
    out_ << indent_ << "|   |-- Zd          : " << Zd << "\n";
    out_ << indent_ << "|   |-- Ad          : " << Ad << "\n";
    out_ << indent_ << "|   |-- e0          : " << e0 << "\n";
    out_ << indent_ << "|   `-- e1          : " << e1 << "\n";
    out_ << indent_ << "|-- modebb   : " << modebb   << "\n";
    out_ << indent_ << "|-- Qbb      : " << Qbb      << "\n";
    out_ << indent_ << "|-- Edlevel  : " << Edlevel  << "\n";
    out_ << indent_ << "|-- EK       : " << EK       << "\n";
    out_ << indent_ << "|-- Zdbb     : " << Zdbb     << "\n";
    out_ << indent_ << "|-- Adbb     : " << Adbb     << "\n";
    out_ << indent_ << "|-- istartbb : " << istartbb << "\n";
    out_ << indent_ << "|-- spthe1   : [" << SPSIZE  << "]\n";
    out_ << indent_ << "|-- spthe2   : [" << SPSIZE  << "]\n";
    out_ << indent_ << "`-- spmax    : " << spmax << "\n";
    return;
  }

  void bbpars::_set_defaults()
  {
    modebb  = LEGACY_MODEBB_UNDEF;
    Qbb     = std::numeric_limits<double>::quiet_NaN();
    Edlevel = std::numeric_limits<double>::quiet_NaN();
    EK      = std::numeric_limits<double>::quiet_NaN();
    Zdbb    = std::numeric_limits<double>::quiet_NaN();
    Adbb    = std::numeric_limits<double>::quiet_NaN();
    istartbb = 0;
    for (int i = 0; i < (int) bxdecay0::bbpars::SPSIZE; i++) {
      spthe1[i] = 0.0;
      spthe2[i] = 0.0;
    }
    spmax = -1.0;
    return;
  }

  void bbpars::reset()
  {
    this->enrange::reset();
    this->denrange::reset();
    this->helpbb::reset();
    this->eta_nme::reset();
    _set_defaults();
   return;
  }

  bbpars::bbpars()
  {
    this->bbpars::_set_defaults();
    return;
  }

  /*********************************************************************/
  void decay0_bb(i_random & prng_, event & event_, void * params_)
  {
    static bool trace = is_trace("bb");
    if (trace) std::cerr << "[trace] bxdecay0::bb: Entering..." << std::endl;
    bbpars * pars = static_cast<bbpars *>(params_);
    if (trace) {
      pars->dump(std::cerr, "[trace] ");
    }
    // From enrange:
    double & ebb1 = pars->ebb1;
    double & ebb2 = pars->ebb2;
    double & toallevents = pars->toallevents;
    //int    & levelE = pars->levelE;
    //std::string & chdspin = pars->chdspin;
    //double & lhelp = pars->levelE;
    //std::string & chhelp =  = pars->chdspin;

    // From denrange:
    double & dens = pars->dens;
    double & denf = pars->denf;
    int    & mode = pars->mode;

    // From helpbb:
    double & Zd = pars->Zd;
    double & Ad = pars->Ad;
    double & e0 = pars->e0;
    double & e1 = pars->e1;

    // From eta_nme:
    const double & chi_GTw = pars->chi_GTw;
    const double & chi_Fw  = pars->chi_Fw;
    const double & chip_GT = pars->chip_GT;
    const double & chip_F  = pars->chip_F;
    const double & chip_T  = pars->chip_T;
    const double & chip_P  = pars->chip_P;
    const double & chip_R  = pars->chip_R;

    // From bbpars:
    const int      modebb = pars->modebb;
    const double & Qbb = pars->Qbb;
    const double & Edlevel = pars->Edlevel;
    const double & EK = pars->EK;
    const double & Zdbb = pars->Zdbb;
    const double & Adbb = pars->Adbb;
    int          & istartbb = pars->istartbb;
    double       * spthe1 = pars->spthe1;
    double       * spthe2 = pars->spthe2;
    double       & spmax = pars->spmax;

    // Constants:
    static const double pi    = M_PI;
    static const double twopi = 2. * pi;
    static const double emass = decay0_emass();
    static const double emass2 = emass * emass;

    // Decay parameters :
    Zd = Zdbb;
    Ad = Adbb;

    double t; // time
    double relerr;

    int imax;

    if (Zdbb >= 0.) {
      e0 = Qbb - Edlevel;
    }
    if (Zdbb < 0.) {
      e0 = Qbb - Edlevel - 4. * emass;
    }
    if (modebb == LEGACY_MODEBB_9 || modebb == LEGACY_MODEBB_10) {
      e0 = Qbb - Edlevel - EK - 2. * emass;
    }
    if (modebb == LEGACY_MODEBB_11 || modebb == LEGACY_MODEBB_12) {
      e0 = Qbb - Edlevel - 2. * EK;
    }
    if (modebb == LEGACY_MODEBB_9) {
      // fixed energies of e+ and X-ray; no angular correlation
      decay0_particle(prng_,event_,POSITRON,e0,e0,0.,pi,0.,twopi,0.,0.,t);
      decay0_particle(prng_,event_,GAMMA,EK,EK,0.,pi,0.,twopi,0.,0.,t);
      if (trace) std::cerr << "[trace] bxdecay0::bb: Exiting." << std::endl;
      return;
    }
    if (modebb == LEGACY_MODEBB_11) {
      // one gamma and two X-rays with fixed energies; no angular correlation
      decay0_particle(prng_,event_,GAMMA,e0,e0,0.,pi,0.,twopi,0.,0.,t);
      decay0_particle(prng_,event_,GAMMA,EK,EK,0.,pi,0.,twopi,0.,0.,t);
      decay0_particle(prng_,event_,GAMMA,EK,EK,0.,pi,0.,twopi,0.,0.,t);
      if (trace) std::cerr << "[trace] bxdecay0::bb: Exiting." << std::endl;
      return;
    }
    if (modebb == LEGACY_MODEBB_12) {
      // fixed energies of two X-rays; no angular correlation
      decay0_particle(prng_,event_,GAMMA,EK,EK,0.,pi,0.,twopi,0.,0.,t);
      decay0_particle(prng_,event_,GAMMA,EK,EK,0.,pi,0.,twopi,0.,0.,t);
      if (trace) std::cerr << "[trace] bxdecay0::bb: Exiting." << std::endl;
      if (trace) std::cerr << "[trace] bxdecay0::bb: Exiting." << std::endl;
      return;
    }

    // If already initialized, skip
    if (istartbb == 0) {
      if (trace) std::cerr << "[trace] bxdecay0::bb: Initializing the kinematics..." << std::endl;
      // Initializing the kinematics:
      // calculate the theoretical energy spectrum of first particle with step
      // of 1 keV and find its maximum
      // Calculation of theoretical spectrum:
      if (ebb1 < 0.) {
        ebb1 = 0.;
      }
      if (ebb2 > e0) {
        ebb2 = e0;
      }
      if (trace) std::cerr << "[trace] bxdecay0::bb: ebb1 = " << ebb1 << std::endl;
      if (trace) std::cerr << "[trace] bxdecay0::bb: ebb2 = " << ebb2 << std::endl;
      spmax = -1.; // Initialize
      //double b2amin=+1.e20; // coefficients in angular correlation
      //double b2amax=-1.e20; // for eta-h term of 2b0nu
      relerr = 1.e-4;
      //relerr = 1.e-3;
      imax = (int) (e0 * 1000.);
      if (trace) std::cerr << "[trace] bxdecay0::bb: e0   = " << e0 << std::endl;
      if (trace) std::cerr << "[trace] bxdecay0::bb: imax = " << imax << std::endl;
      for (int i = 1; i <= imax; i++) {
        e1 = i / 1000.;
        if (trace) std::cerr << "[trace] bxdecay0::bb: => e1 = " << e1 << std::endl;
        double e1h = e1;
        spthe1[i-1] = 0.;
        if (modebb == LEGACY_MODEBB_1) {
          spthe1[i-1] = decay0_fe1_mod1(e1h,params_);
        }
        if (modebb == LEGACY_MODEBB_2) {
          spthe1[i-1] = decay0_fe1_mod2(e1h,params_);
        }
        if (modebb == LEGACY_MODEBB_3) {
          spthe1[i-1] = decay0_fe1_mod3(e1h,params_);
        }
        double elow  = std::max(1.e-4, ebb1 - e1 + 1.e-4);
        double ehigh = std::max(1.e-4, ebb2 - e1 + 1.e-4);
        if (trace) std::cerr << "[trace] bxdecay0::bb: elow  = " << elow << std::endl;
        if (trace) std::cerr << "[trace] bxdecay0::bb: ehigh = " << ehigh << std::endl;
        if (trace) std::cerr << "[trace] bxdecay0::bb: relerr = " << relerr << std::endl;
        // print *,'e1,elow,ehigh=',e1,elow,ehigh
        if (modebb == LEGACY_MODEBB_4 && e1 < e0) {
          if (trace) std::cerr << "[trace] bxdecay0::bb: Calling decay0_gauss( decay0_fe12_mod4,...)... " << std::endl;
           spthe1[i-1] = decay0_gauss(decay0_fe12_mod4,elow,ehigh,relerr,params_);
        }
        if (modebb == LEGACY_MODEBB_5 && e1 < e0) {
          spthe1[i-1] = decay0_gauss(decay0_fe12_mod5,elow,ehigh,relerr,params_);
        }
        if (modebb == LEGACY_MODEBB_6 && e1 < e0) {
          spthe1[i-1] = decay0_gauss(decay0_fe12_mod6,elow,ehigh,relerr,params_);
        }
        if (modebb == LEGACY_MODEBB_7) {
          spthe1[i-1] = decay0_fe1_mod7(e1h,params_);
        }
        if (modebb == LEGACY_MODEBB_8 && e1 < e0) {
          spthe1[i-1] = decay0_gauss(decay0_fe12_mod8,elow,ehigh,relerr,params_);
        }
        if (modebb == LEGACY_MODEBB_10) {
          spthe1[i-1] = decay0_fe1_mod10(e1h,params_);
        }
        if (modebb == LEGACY_MODEBB_13 && e1 < e0) {
          spthe1[i-1] = decay0_gauss(decay0_fe12_mod13,elow,ehigh,relerr,params_);
        }
        if (modebb == LEGACY_MODEBB_14 && e1 < e0) {
          spthe1[i-1] = decay0_gauss(decay0_fe12_mod14,elow,ehigh,relerr,params_);
        }
        if (modebb == LEGACY_MODEBB_15 && e1 < e0) {
          spthe1[i-1] = decay0_gauss(decay0_fe12_mod15,elow,ehigh,relerr,params_);
        }
        if (modebb == LEGACY_MODEBB_16 && e1 < e0) {
          spthe1[i-1] = decay0_gauss(decay0_fe12_mod16,elow,ehigh,relerr,params_);
        }
        if (modebb == LEGACY_MODEBB_17) {
          spthe1[i-1] = decay0_fe1_mod17(e1h,params_);
        }
        if (modebb == LEGACY_MODEBB_18) {
          spthe1[i-1] = decay0_fe1_mod18(e1h,params_);
        }
        if (modebb == LEGACY_MODEBB_19 && e1 < e0) {
          spthe1[i-1] = decay0_gauss(decay0_fe12_mod19,elow,ehigh,relerr,params_);
        }
        if (trace) std::cerr << "[trace] bxdecay0::bb: spthe1[" << (i-1) << "] = " << spthe1[i-1] << std::endl;

        if (spthe1[i-1] > spmax) {
          spmax = spthe1[i-1];
          if (trace) std::cerr << "[trace] bxdecay0::bb: Updating spmax = " << spmax << std::endl;
       }
      }
      if (trace) std::cerr << "[trace] bxdecay0::bb: zeroing spthe1[" << (imax) << "...]" << std::endl;
      for (int i = imax + 1; i <= (int) bbpars::SPSIZE; i++) {
        spthe1[i-1] = 0.;
      }
      // Calculation of theoretical spectrum is done.
      // if (TRACE) {
      //   // Store the spthe1 spectrum:
      //   std::ofstream f_spthe1;
      //   f_spthe1.open("/tmp/th-e1-spectrum.dat");
      //   for (int i = 0; i < (int) bbpars::SPSIZE; i++) {
      //     f_spthe1 << i << ' ' << spthe1[i] << std::endl;
      //   }
      // }
      toallevents = 1.;
      if (modebb == LEGACY_MODEBB_4 || modebb == LEGACY_MODEBB_5 || modebb == LEGACY_MODEBB_6
          || modebb == LEGACY_MODEBB_8 || modebb == LEGACY_MODEBB_13 || modebb == LEGACY_MODEBB_14
          || modebb == LEGACY_MODEBB_15 || modebb == LEGACY_MODEBB_16 || modebb == LEGACY_MODEBB_19
          ) {
        mode = modebb;
        dens = 0.;
        denf = e0;
        double d_el[2];
        double r1 = decay0_dgmlt1(decay0_dshelp1,0.,denf,8,8,d_el,params_);
        dens = ebb1;
        denf = ebb2;
        double r2 = decay0_dgmlt1(decay0_dshelp1,0.,denf,8,8,d_el,params_);
        toallevents = r1 / r2;
      } else if (modebb == LEGACY_MODEBB_10) {
        toallevents = decay0_gauss(decay0_fe1_mod10,1.e-4,e0+1.e-4,relerr,params_)
          /decay0_gauss(decay0_fe1_mod10,ebb1+1.e-4,ebb2+1.e-4,relerr,params_);
      }
      if (modebb == LEGACY_MODEBB_20) {
        double emax=e0/4.;
        double tmax=emax/emass;
        double pmax=std::sqrt(tmax*(tmax+2.));
        spmax=gsl_pow_4((tmax+1.)*pmax*decay0_fermi(Zdbb,emax));
      }
      istartbb = 1;
      if (trace) std::cerr << "[trace] bxdecay0::bb: Initializing the kinematics done." << std::endl;
    } else {
      if (trace) std::cerr << "[trace] bxdecay0::bb: Skip the initialization of the kinematics." << std::endl;
    }
    // Starting the generation:
  label_1 :
    if (modebb == LEGACY_MODEBB_20) {
      double t0=e0/emass;
  label_4 :
      double t1=prng_()*t0;
      double t2=prng_()*t0;
      double t3=prng_()*t0;
      double t4=t0-t1-t2-t3;
      if (t4 < 0.) goto label_4;
      double p1=std::sqrt(t1*(t1+2.));
      double p2=std::sqrt(t2*(t2+2.));
      double p3=std::sqrt(t3*(t3+2.));
      double p4=std::sqrt(t4*(t4+2.));
      double r=(t1+1.)*p1*decay0_fermi(Zdbb,t1*emass)
         *(t2+1.)*p2*decay0_fermi(Zdbb,t2*emass)
         *(t3+1.)*p3*decay0_fermi(Zdbb,t3*emass)
         *(t4+1.)*p4*decay0_fermi(Zdbb,t4*emass);
      double rr=prng_()*spmax;
      if (rr > r) goto label_4;
      // Isotropical emission of 4 electrons:
      double t;
      decay0_particle(prng_,event_,ELECTRON,
                      t1*emass,t1*emass,
                      0.,pi,0.,twopi,0.,0.,t);
      decay0_particle(prng_,event_,ELECTRON,
                      t2*emass,t2*emass,
                      0.,pi,0.,twopi,0.,0.,t);
      decay0_particle(prng_,event_,ELECTRON,
                      t3*emass,t3*emass,
                      0.,pi,0.,twopi,0.,0.,t);
      decay0_particle(prng_,event_,ELECTRON,
                      t4*emass,t4*emass,
                      0.,pi,0.,twopi,0.,0.,t);
      if (trace) std::cerr << "[trace] bxdecay0::bb: Exiting." << std::endl;
      return;
    }
    // Rejection method :
    int k;
    if (modebb != LEGACY_MODEBB_10) {
      e1 = ebb2 * prng_();
    }
    if (modebb == LEGACY_MODEBB_10) {
      e1 = ebb1 + (ebb2 - ebb1) * prng_();
    }
    k = (int) (e1 * 1000.);
    if (k < 1) {
      k = 1;
    }
    if (spmax * prng_() > spthe1[k - 1]) goto label_1;

    // second e-/e+ or X-ray
    double e2;
    e2 = std::numeric_limits<double>::quiet_NaN();
    if (modebb == LEGACY_MODEBB_1 || modebb == LEGACY_MODEBB_2 || modebb == LEGACY_MODEBB_3 ||
        modebb == LEGACY_MODEBB_7 || modebb == LEGACY_MODEBB_17 || modebb == LEGACY_MODEBB_18) {
      // modes with no emission of other particles beside of two e-/e+:
      // energy of second e-/e+ is calculated
      e2 = e0 - e1;
    }
    else if (modebb == LEGACY_MODEBB_4 || modebb == LEGACY_MODEBB_5 || modebb == LEGACY_MODEBB_6 ||
             modebb == LEGACY_MODEBB_8 || modebb == LEGACY_MODEBB_13 || modebb == LEGACY_MODEBB_14 ||
             modebb == LEGACY_MODEBB_15 || modebb == LEGACY_MODEBB_16 || modebb == LEGACY_MODEBB_19) {
      // something else is emitted - energy of second e-/e+ is random
      double re2s = std::max(0., ebb1 - e1);
      double re2f = ebb2 - e1;
      double f2max = -1.;
      int ke2s = std::max(1, (int) (re2s * 1000.));
      int ke2f = (int) (re2f * 1000.);
      for (int ke2 = ke2s; ke2 <= ke2f; ke2++) {
        e2 = ke2 / 1000.;
        // if (modebb == LEGACY_MODEBB_4)  spthe2[ke2-1] = decay0_fe2_mod4(e2,params_);
        if (modebb == LEGACY_MODEBB_5)  spthe2[ke2-1] = decay0_fe2_mod5(e2,params_);
        if (modebb == LEGACY_MODEBB_6)  spthe2[ke2-1] = decay0_fe2_mod6(e2,params_);
        if (modebb == LEGACY_MODEBB_8)  spthe2[ke2-1] = decay0_fe2_mod8(e2,params_);
        if (modebb == LEGACY_MODEBB_13) spthe2[ke2-1] = decay0_fe2_mod13(e2,params_);
        if (modebb == LEGACY_MODEBB_14) spthe2[ke2-1] = decay0_fe2_mod14(e2,params_);
        if (modebb == LEGACY_MODEBB_15) spthe2[ke2-1] = decay0_fe2_mod15(e2,params_);
        if (modebb == LEGACY_MODEBB_16) spthe2[ke2-1] = decay0_fe2_mod16(e2,params_);
        // if (modebb == LEGACY_MODEBB_19) spthe2[ke2-1] = decay0_fe2_mod19(e2,params_);
        if (spthe2[ke2-1] > f2max) f2max = spthe2[ke2-1];
      }
      double e2max;
      if(modebb == LEGACY_MODEBB_4) {
        decay0_tgold(re2s, 0.5* (re2s+re2f), re2f, decay0_fe2_mod4, 1.e-3, 2, e2max, f2max, params_);
      }
      if(modebb == LEGACY_MODEBB_19) {
        decay0_tgold(re2s, 0.5* (re2s+re2f), re2f, decay0_fe2_mod19, 1.e-3, 2, e2max, f2max, params_);
      }
      // Rejection method :
      double fe2;
      fe2 = 0.0;
      e2 = std::numeric_limits<double>::quiet_NaN();
      do {
        e2 = re2s + (re2f - re2s) * prng_();
        if (modebb == LEGACY_MODEBB_4)  fe2 = decay0_fe2_mod4(e2,params_);
        if (modebb == LEGACY_MODEBB_5)  fe2 = decay0_fe2_mod5(e2,params_);
        if (modebb == LEGACY_MODEBB_6)  fe2 = decay0_fe2_mod6(e2,params_);
        if (modebb == LEGACY_MODEBB_8)  fe2 = decay0_fe2_mod8(e2,params_);
        if (modebb == LEGACY_MODEBB_13) fe2 = decay0_fe2_mod13(e2,params_);
        if (modebb == LEGACY_MODEBB_14) fe2 = decay0_fe2_mod14(e2,params_);
        if (modebb == LEGACY_MODEBB_15) fe2 = decay0_fe2_mod15(e2,params_);
        if (modebb == LEGACY_MODEBB_16) fe2 = decay0_fe2_mod16(e2,params_);
        if (modebb == LEGACY_MODEBB_19) fe2 = decay0_fe2_mod19(e2,params_);
      } while (f2max * prng_() > fe2);
    } else if (modebb == LEGACY_MODEBB_10) {
      // c energy of X-ray is fixed; no angular correlation
      // c          allevents=allevents+1.
      // c          if (e1 < ebb1 || e1.gt.ebb2) go to 1
      decay0_particle(prng_,event_,POSITRON,e1,e1,0.,pi,0.,twopi,0.,0.,t);
      decay0_particle(prng_,event_,GAMMA,EK,EK,0.,pi,0.,twopi,0.,0.,t);
      if (trace) std::cerr << "[trace] bxdecay0::bb: Exiting." << std::endl;
      return;
    }
    if (e2 != e2) {
      throw std::runtime_error("bxdecay0::decay0_bb: Undefined e2 or fe2 ! This is a bug!");
    }
    double p1 = std::sqrt(e1 * (e1 + 2. * emass));
    double p2 = std::sqrt(e2 * (e2 + 2. * emass));
    double b1 = p1 / (e1 + emass);
    double b2 = p2 / (e2 + emass);
    // sampling the angles with angular correlation
    double a = 1.;
    double b = -b1 * b2;
    double c = 0.;
    if (modebb == LEGACY_MODEBB_2) {
      b = b1 * b2;
    }
    if (modebb == LEGACY_MODEBB_3) {
      double w1 = e1 + emass;
      double w2 = e2 + emass;
      a = 3. * (w1*w2+emass2) * (gsl_pow_2(p1) + gsl_pow_2(p2));
      b = -p1 * p2 * (gsl_pow_2(w1+w2) + 4. * (w1 * w2 + gsl_pow_2(emass)));
      c = 2. * gsl_pow_2(p1 * p2);
    }
    if (modebb == LEGACY_MODEBB_7) {
      double w1 = e1 + emass;
      double w2 = e2 + emass;
      a = 5. * (w1 * w2 + emass2) * (gsl_pow_2(p1) + gsl_pow_2(p2))
        - gsl_pow_2(p1 * p2);
      b = -p1 * p2 * (10. * (w1 * w2 + emass2) + gsl_pow_2(p1) + gsl_pow_2(p2));
      c = 3. * gsl_pow_2(p1 * p2);
    }
    if (modebb == LEGACY_MODEBB_8) {
      b = b1 * b2 / 3.;
    }
    if (modebb == LEGACY_MODEBB_15) {
      a = 9.* gsl_pow_2(e0-e1-e2) + 21. * gsl_pow_2(e2-e1);
      b = -b1 * b2 * (9. * gsl_pow_2(e0-e1-e2) - 7. * gsl_pow_2(e2-e1));
    }
    if (modebb == LEGACY_MODEBB_16) {
      b = b1 * b2 / 3.;
    }
    if (modebb == LEGACY_MODEBB_17) {
      b = b1 * b2;
    }
    if (modebb == LEGACY_MODEBB_18) {
      double et0 = e0 / emass + 1.; // total energies in the units of electron mass
      double et1 = e1 / emass + 1.;
      double et2 = e2 / emass + 1.;
      double a1 = (et1 * et2 - 1.) * gsl_pow_2(et1 - et2) / (2. * et1 * et2);
      double a2 = -2. * gsl_pow_2(et1 - et2) / (9. * et1 * et2);
      double a3 = 2. * (et1 * et2 - 1.) / (81. * et1 * et2);
      double r = 3.107526e-3 * std::pow(Adbb, (1./3.));
      double rksi = 3. / 137.036 * Zdbb + r * et0;
      double a4 = 8. * (et1 * et2 + 1.) / (gsl_pow_2(r) * et1 * et2);
      double a5 = -8. * (rksi * (et1 * et2 + 1.) - 2. * r * et0)
        / (3. * gsl_pow_2(r) * et1 * et2);
      double a6 = 2. * ((gsl_pow_2(rksi) + 4. * gsl_pow_2(r))
                        * (et1 * et2 + 1.) - 4. * rksi * r *et0)
        /      (9. * gsl_pow_2(r) * et1 * et2);
      //double chi_1plus  = chip_GT + 3. * chip_F - 6. * chip_T;
      double chi_1minus = chip_GT - 3. * chip_F - 6. * chip_T;
      double chi_2plus  = chi_GTw + chi_Fw - chi_1minus / 9.;
      double a_eta  =
        a1 * gsl_pow_2(chi_2plus)
        + a2 * chi_2plus * chi_1minus
        + a3 * gsl_pow_2(chi_1minus)
        + a4 * gsl_pow_2(chip_R)
        + a5 * chip_R * chip_P
        + a6 * gsl_pow_2(chip_P);
      double b_eta =
        gsl_pow_2(et1 - et2) * gsl_pow_2(chi_2plus) / 2.
        -4. * gsl_pow_2(chi_1minus) / 81.
        +8. * gsl_pow_2(rksi * chip_P / 6. - chip_R) / gsl_pow_2(r)
        -8. * std::pow(chip_P,(2 / 9.));
      if (a_eta != 0.) {
        b = b_eta / a_eta * b1 * b2;
      }
    }
    double romaxt = a + std::abs(b) + c;
    double phi1;
    double ctet1;
    double stet1;
    double phi2;
    double ctet2;
    double stet2;
    double ctet;
    do {
      phi1 = twopi * prng_();
      ctet1 = 1. - 2. * prng_();
      stet1 = std::sqrt(1. - ctet1 * ctet1);
      phi2 = twopi * prng_();
      ctet2 = 1. - 2. * prng_();
      stet2 = std::sqrt(1. - ctet2 * ctet2);
      ctet = ctet1 * ctet2 + stet1 * stet2 * std::cos(phi1 - phi2);
    }
    while (romaxt * prng_() > a + b * ctet + c * gsl_pow_2(ctet));

    particle part;
    part.set_time(0.);
    if (Zdbb >= 0.) part.set_code(ELECTRON); // b-b-
    if (Zdbb < 0.) part.set_code(POSITRON);  // b+b+

    // First electron/positron :
    part.set_momentum(p1 * stet1 * std::cos(phi1),
                      p1 * stet1 * std::sin(phi1),
                      p1 * ctet1);
    event_.add_particle(part);

    // Second electron/positron :
    part.set_momentum(p2 * stet2 * std::cos(phi2),
                      p2 * stet2 * std::sin(phi2),
                      p2 * ctet2);
    event_.add_particle(part);
    if (trace) std::cerr << "[trace] bxdecay0::bb: Exiting." << std::endl;
    return;
  }

} // end of namespace bxdecay0
