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
#include <bxdecay0/Co60.h>

// Standard library:
#include <cmath>

// Third party:
#include <gsl/gsl_math.h>

// This project:
#include <bxdecay0/i_random.h>
#include <bxdecay0/event.h>
#include <bxdecay0/alpha.h>
#include <bxdecay0/gamma.h>
#include <bxdecay0/electron.h>
#include <bxdecay0/pair.h>
#include <bxdecay0/particle.h>
#include <bxdecay0/nucltransK.h>
#include <bxdecay0/nucltransKL.h>
#include <bxdecay0/nucltransKLM.h>
#include <bxdecay0/nucltransKLM_Pb.h>
#include <bxdecay0/beta.h>
#include <bxdecay0/beta2.h>

namespace bxdecay0
{

  void Co60(i_random & prng_,
            event & event_,
            const double tcnuc_,
            double & tdnuc_)
  {
    //static const double pi = M_PI;
    static const double twopi = 2 * M_PI;
    //double twopi = 2 * M_PI;
    double t;
    double tdlev;
    double cg;
    double cK;
    double cp;
    //double ctet;
    double EbindK;
    double Egamma;
    double p;
    double pbeta;
    double tclev;
    double thlev;
    double thnuc;
    particle * ipg1173 = 0;
    particle * ipg1333 = 0;
    // Scheme of Co60 decay ("Table of Isotopes", 7th ed., 1978).
    // Four-figured labels correspond to energies of 60Ni excited
    // levels in keV.
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
    // VIT, 3.08.1992, 22.10.1995.
    // Updated to NDS 100(2003)347, VIT, 16.10.2006
    // angular correlation of 1173 and 1333 keV gammas, L.Pandola + VIT, 18.10.2006
    // 2nd forbidden unique shape for beta decay to 1333 keV level, VIT, 27.10.2006.
    thnuc = 0.166344192e+09;
    tdnuc_ = tcnuc_ - thnuc / std::log (2.) * std::log (prng_ ());
    tclev = 0.;
    pbeta = 100. * prng_ ();
    //DT_TRACER_MESSAGE(10001,"pbeta = " << pbeta);
    if (pbeta <= 99.880)
      goto label_2506;      // 99.880%
    goto label_1333;        // 0.120%
  label_2506:
    decay0_beta (prng_, event_, 0.318, 28., 0., 0., t);
    thlev = 0.3e-12;
    p = 100. * prng_ ();
    //DT_TRACER_MESSAGE(10001,"p1 = " << p);
    if (p <= 0.000002)
      goto label_25061;     // 0.000002%
    if (p <= 99.992449)
      goto label_25062;     // 99.992447%
    goto label_25063;       // 0.007551%
  label_25061:
    decay0_nucltransK (prng_, event_, 2.506, 0.008, 8.6e-5,
                       0., tclev, thlev, tdlev);
    return;
    // longer code for angular correlation of gammas 1173 and 1333 keV
  label_25062:
    Egamma = 1.173;
    EbindK = 0.008;
    cg = 1.;
    cK = 1.7e-4;
    cp = 6.2e-6;
    p = prng_ () * (cg + cK + cp);
    //DT_TRACER_MESSAGE(10001,"p2 = " << p);
    if (p <= cg) {
      decay0_gamma (prng_, event_, Egamma, tclev, thlev, tdlev);
      ipg1173 = &event_.grab_last_particle();
    } else if (p <= cg + cK) {
      decay0_electron (prng_, event_, Egamma - EbindK, tclev, thlev,
                       tdlev);
      decay0_gamma (prng_, event_, EbindK, 0., 0., tdlev);
    } else {
      decay0_pair (prng_, event_, Egamma - 1.022, tclev, thlev,
                   tdlev);
    }
    goto label_13330;
  label_25063:
    decay0_nucltransK (prng_, event_, 0.347, 0.008, 5.5e-3, 0., tclev,
                       thlev, tdlev);
    goto label_2159;
  label_2159:
    thlev = 0.;
    p = 100. * prng_ ();
    //DT_TRACER_MESSAGE(10001,"p3 = " << p);
    if (p <= 13.64)
      goto label_21591;   // 13.64%
    goto label_21592;     // 86.36%
  label_21591:
    decay0_nucltransK (prng_, event_, 2.159, 0.008, 4.9e-5, 3.9e-4,
                       tclev, thlev, tdlev);
    return;
  label_21592:
    decay0_nucltransK (prng_, event_, 0.826, 0.008, 3.3e-4, 0., tclev,
                       thlev, tdlev);
    goto label_13330;
    // change to the 2nd forbidden unique shape in accordance with
    // H.Daniel, RMP 40(1968)659 and J.L.Wolfson, Can. J. Phys. 34(1956)256
    // cf(e) = pel**4 + c1*pel**2*pnu**2 + c2*pnu**4,
  label_1333:
    decay0_beta2 (prng_, event_, 1.491, 28., 0., 0., t, 2, 3.333333, 1.,
                  0., 0.);
  label_13330:
    thlev = 0.9e-12;
    ////// decay0_nucltransK(prng_, event_, 1.333,0.008,1.3e-4,3.4e-5,tclev,thlev,tdlev)
    // longer code for angular correlation of gammas 1173 and 1333 keV
    Egamma = 1.333;
    EbindK = 0.008;
    cg = 1.;
    cK = 1.3e-4;
    cp = 3.4e-5;
    p = prng_ () * (cg + cK + cp);
    //DT_TRACER_MESSAGE(10001,"p4 = " << p);
    if (p <= cg) {
      decay0_gamma (prng_, event_, Egamma, tclev, thlev, tdlev);
      ipg1333 = &event_.grab_last_particle();
    } else if (p <= cg + cK) {
      decay0_electron (prng_, event_, Egamma - EbindK, tclev, thlev, tdlev);
      decay0_gamma (prng_, event_, EbindK, 0., 0., tdlev);
    } else {
      decay0_pair (prng_, event_, Egamma - 1.022, tclev, thlev,
                   tdlev);
    }
    // Angular correlation between gammas 1173 and 1333 keV, L.Pandola + VIT
    if (ipg1333 != 0 && ipg1173 != 0) {
      double p1333 = ipg1333->get_p();
      double p1173 = ipg1173->get_p();
      //DT_TRACER_MESSAGE(10001,"gammas 1173 and 1333 correlation");
      // Coefficients in formula 1+a2*ctet**2+a4*ctet**4 are from:
      // R.D.Evans, "The Atomic Nucleus", Krieger Publ. Comp., 1985, p. 240 (4(2)2(2)0 cascade).
      // They correspond to coefficients in formula 1+a2*p2+a4*p4, a2=0.1020, a4=0.0091 in
      // K.Siegbahn, "Alpha-, Beta- and Gamma-Ray Spectroscopy", North-Holland Publ. Comp., 1968, p. 1033.
      double  a2 = 1. / 8.;
      double  a4 = 1. / 24.;
      // Rejection method :
      double phi1, ctet1, stet1;
      double phi2, ctet2, stet2;
      double ctet;
    label_1:
      //twopi=6.2831853;//XXX
      phi1 = twopi * prng_ ();
      ctet1 = 1. - 2. * prng_ ();
      stet1 = std::sqrt (1. - ctet1 * ctet1);
      phi2 = twopi * prng_ ();
      ctet2 = 1. - 2. * prng_ ();
      stet2 = std::sqrt (1. - ctet2 * ctet2);
      ctet = ctet1 * ctet2 + stet1 * stet2 * std::cos (phi1 - phi2);
      double pcor=prng_ ();
      //DT_TRACER_MESSAGE(10001,"pcor = " << pcor);
      if (pcor * (1. + std::abs (a2) + std::abs (a4)) >
          1. + a2 * gsl_pow_2(ctet) + a4 * gsl_pow_4(ctet)) {
        goto label_1;
      }
      ipg1333->set_momentum(p1333 * stet1 * cos (phi1),
                            p1333 * stet1 * sin (phi1),
                            p1333 * ctet1);
      ipg1173->set_momentum(p1173 * stet2 * cos (phi2),
                            p1173 * stet2 * sin (phi2),
                            p1173 * ctet2);
    }
    return;
  }

} // end of namespace bxdecay0

// end of Co60.cc
// Local Variables: --
// mode: c++ --
// End: --
