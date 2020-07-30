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
#include <bxdecay0/PbAtShell.h>

// This project:
#include <bxdecay0/alpha.h>
#include <bxdecay0/beta.h>
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

  void PbAtShell(i_random & prng_,
                 event & event_,
                 const int KLMenergy_,
                 const double tclev_,
                 const double thlev_,
                 double & tdlev_)
  {
    // double t;
    int Lhole;
    int Mhole;
    double p;
    // Subroutine describes in some approximation the deexcitation process in
    // atomic shell of Pb after creation of electron vacation in K, L or M shell.
    // Call : call PbAtShell(KLMenergy,tclev,thlev,tdlev_)
    // Input : KLMenergy_ - binding energy of electron on atomic shell [integer
    // in keV] where the hole was created
    // tclev_ - time of hole creation (sec)
    // thlev_ - hole halflife (sec).
    // Output: tdlev_ - time of decay of hole (sec).
    // It is supposed electron binding energy on Pb K-shell = 88 keV, on L-shell =
    // 15 keV, on M-shell = 3 keV. So, following values of KLMenergy_ are allowed:
    // 88 (hole in K-shell), 15 (in L-shell) and 3 (in M-shell).
    // VIT, 7.07.1995, 22.10.1995.
    Lhole = 0;
    Mhole = 0;
    if (KLMenergy_ == 88)
      goto label_88;
    if (KLMenergy_ == 15) {
      Lhole = 1;
      goto label_15;
    }
    if (KLMenergy_ == 3) {
      Mhole = 1;
      goto label_3;
    }
    goto label_20000;
    // K-shell
  label_88:
    p = 100. * prng_();
    if (p <= 22.)
      goto label_88001;
    goto label_88002;
  label_88001:
    decay0_gamma(prng_, event_, 0.085, tclev_, thlev_, tdlev_); // X ray K-M
    Mhole = Mhole + 1;
    goto label_3;
  label_88002:
    p = 100. * prng_();
    if (p <= 96.) {
      decay0_gamma(prng_, event_, 0.073, tclev_, thlev_, tdlev_); // X ray K-L
    } else {
      decay0_electron(prng_, event_, 0.058, tclev_, thlev_, tdlev_); // Auger electron K-LL
      Lhole = Lhole + 1;
    }
    Lhole = Lhole + 1;
    // L-shell
  label_15:
    for (int i = 1; i <= Lhole; i++) {
      // i = 1, Lhole;
      p = 100. * prng_();
      if (p <= 40.) {
        decay0_gamma(prng_, event_, 0.012, tclev_, thlev_, tdlev_); // X ray L-M
      } else {
        decay0_electron(prng_, event_, 0.009, tclev_, thlev_, tdlev_); // Auger electron L-MM
        Mhole = Mhole + 1;
      }
      Mhole = Mhole + 1;
    }
    // M-shell
  label_3:
    for (int i = 1; i <= Lhole; i++) {
      // i = 1, Mhole;
      decay0_gamma(prng_, event_, 0.003, tclev_, thlev_, tdlev_); // X ray M-inf
    }
    return;
  label_20000:
    // print *,'Pb_At_Shell: wrong hole level [keV] ',KLMenergy_
    return;
  } // end of PbAtShell.f

} // end of namespace bxdecay0

// Local Variables: --
// mode: c++ --
// End: --
